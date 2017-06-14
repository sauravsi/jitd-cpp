#ifndef JITD_CPP_
#define JITD_CPP_

#include "jitd.h"
#include <vector>
#include "cog.h"
#include "cogTypes.h"
#include "policy.h"
#include "binarySearch.h"
#include "binarySearch.cpp"

using namespace std;

template <class T>
jitd<T>::jitd(policy<T>* pl): root(0), p(pl){}

template <class T>
jitd<T>::jitd(cog* &r, policy<T>* pl): root(r), p(pl){}

template <class T>
cog* jitd<T>::getRoot(){
	return root;
}

template <class T>
void jitd<T>::insert(T* &data, int size){
	p->beforeInsert(root);
	vector<T> dataArray;
	for(int i = 0; i < size; i++){
		dataArray.push_back(*(data + i));
	}
	cog* arraynode = new arrayNode<T>(dataArray);
	if(root == 0){
		root = arraynode;
	}
	else {
		cog* concatnode = new concatNode(arraynode, root);
		root = concatnode;
	}
	p->afterInsert(root);
}

template <class T>
vector<T> jitd<T>::scan(T low, T high){
	if(high < low){
		T temp = low;
		low = high;
		high = temp;
	}
	p->beforeRootIterator(root);
	vector<T> result = scan(root, low, high);
	return result;
}

template <class T>
vector<T> jitd<T>::scan(cog* &node, T low, T high){
	p->beforeIterator(node);
	switch(node->getType()){
		case ARRAY:{
					vector<T> result;
					for(int i = 0; i < ((arrayNode<T>*)node)->data.size(); i++){
						if((((arrayNode<T>*)node)->data[i] >= low && ((arrayNode<T>*)node)->data[i] < high)||( ((arrayNode<T>*)node)->data[i]==low && low == high )){
							result.push_back(((arrayNode<T>*)node)->data[i]);
						}
					}
					p->afterIterator(node);
					return result;
				}
		case SORTED_ARRAY:{

					vector<T> result;
					int n = ((sortedarrayNode<T>*)node)->data.size();
					int l = binarySearch<T>(((sortedarrayNode<T>*)node)->data,0,n,low);
					if(l < n && l >= 0) {
						for(int i = l; i < ((sortedarrayNode<T>*)node)->data.size(); i++){
							if((((sortedarrayNode<T>*)node)->data[i] >= low && ((sortedarrayNode<T>*)node)->data[i] < high)||( ((sortedarrayNode<T>*)node)->data[i]==low && low == high )){
								result.push_back(((sortedarrayNode<T>*)node)->data[i]);
							}
						}
					}
					p->afterIterator(node);
					return result;
				}
		case BTREE:{
					const T k = ((btreeNode<T>*)node)->getKey();
					if(k < high && low <= k){
						vector<T> l = scan(((btreeNode<T>*)node)->left, low, high);
						vector<T> r = scan(((btreeNode<T>*)node)->right, low, high);
						vector<T> result;
						for (int i = 0; i < l.size(); i++){
							result.push_back(l[i]);
						}
						for (int i = 0; i < r.size(); i++){
							result.push_back(r[i]);
						}
						p->afterIterator(node);
						return result;
					}
					else if(low > k){
						vector<T> result = scan(((btreeNode<T>*)node)->right, low, high);
						p->afterIterator(node);
						return result;
					}
					else{
						vector<T> result = scan(((btreeNode<T>*)node)->left, low, high);
						p->afterIterator(node);
						return result;
					}
				}
		case CONCAT:{
					vector<T> l = scan(((concatNode*)node)->left, low, high);
					vector<T> r = scan(((concatNode*)node)->right, low, high);
					vector<T> result;
					for (int i = 0; i < l.size(); i++){
						result.push_back(l[i]);
					}
					for (int i = 0; i < r.size(); i++){
						result.push_back(r[i]);
					}
					p->afterIterator(node);
					return result;
				}
	}
}
#endif /* JITD_CPP_ */

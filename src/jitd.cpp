#ifndef JITD_CPP_
#define JITD_CPP_

#include "jitd.h"
#include <vector>
#include "cog.h"
#include "cogTypes.h"
#include "policy.h"

using namespace std;

template <class T>
jitd<T>::jitd(policy<T>* pl): root(0), p(pl){}

template <class T>
cog* jitd<T>::getRoot(){
	return root;
}

template <class T>
void jitd<T>::insert(T* data, int size){
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
					vector<T> data = ((arrayNode<T>*)node)->getData();
					vector<T> result;
					for(int i = 0; i < data.size(); i++){
						if((data[i] >= low && data[i] < high)||( data[i]==low && low == high )){
							result.push_back(data[i]);
						}
					}
					p->afterIterator(node);
					return result;
				}
		case SORTED_ARRAY:{
					vector<T> data = ((sortedarrayNode<T>*)node)->getData();
					vector<T> result;
					for(int i = 0; i < data.size(); i++){
						if((data[i] >= low && data[i] < high)||( data[i]==low && low == high )){
							result.push_back(data[i]);
						}
					}
					p->afterIterator(node);
					return result;
				}
		case BTREE:{
					T k = ((btreeNode<T>*)node)->getKey();
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

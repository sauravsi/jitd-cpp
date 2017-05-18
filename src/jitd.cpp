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
	p->beforeRootIterator(root);
	return scan(root, low, high);
}

template <class T>
vector<T> jitd<T>::scan(cog* node, T low, T high){
	cog* it = node;
	p->beforeIterator(it);
	switch(it->getType()){
		case ARRAY:{
					vector<T> data = ((arrayNode<T>*)it)->getData();
					vector<T> result;
					for(int i = 0; i < data.size(); i++){
						if(data[i] >= low && data[i] < high){
							result.push_back(data[i]);
						}
					}
					return result;
				}
		case SORTED_ARRAY:{
					vector<T> data = ((sortedarrayNode<T>*)it)->getData();
					vector<T> result;
					for(int i = 0; i < data.size(); i++){
						if(data[i] >= low && data[i] < high){
							result.push_back(data[i]);
						}
					}
					return result;
				}
		case BTREE:{
					T k = ((btreeNode<T>*)it)->getKey();
					if(high <= k){
						return scan(((btreeNode<T>*)it)->getLeft(), low, high);
					}
					else if(low > k){
						return scan(((btreeNode<T>*)it)->getRight(), low, high);
					}
					else{
						vector<T> l = scan(((btreeNode<T>*)it)->getLeft(), low, high);
						vector<T> r = scan(((btreeNode<T>*)it)->getRight(), low, high);
						vector<T> result;
						for (int i = 0; i < l.size(); i++){
							result.push_back(l[i]);
						}
						for (int i = 0; i < r.size(); i++){
							result.push_back(r[i]);
						}
						return result;
					}
				}
		case CONCAT:{
					vector<T> l = scan(((concatNode*)it)->getLeft(), low, high);
					vector<T> r = scan(((concatNode*)it)->getRight(), low, high);
					vector<T> result;
					for (int i = 0; i < l.size(); i++){
						result.push_back(l[i]);
					}
					for (int i = 0; i < r.size(); i++){
						result.push_back(r[i]);
					}
					return result;
				}
	}
}

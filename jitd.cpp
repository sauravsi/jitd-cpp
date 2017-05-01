#include <iostream>
#include <stdlib.h>
#include <vector>

#define ARRAY 0
#define SORTED_ARRAY 1
#define CONCAT 2
#define BTREE 3

using namespace std;

class cog {
	protected:
		const int type;
	public:
		cog (int t);
		const int getType();
};

template <class T>
class arrayNode: public cog {
	private:
		vector<T> data;
	public:
		arrayNode( T* d, int s);
		arrayNode(vector<T> d);
		vector<T> getData();
		int getSize();
};

template <class T>
class sortedarrayNode: public cog {
	private:
		vector<T> data;
	public:
		sortedarrayNode( T* d, int s);
		sortedarrayNode( vector<T> d);
		vector<T> getData();
		int getSize();
};

class concatNode: public cog {
	private:
		cog* left;
		cog* right;
	public:
		concatNode( cog* l, cog* r );
		cog* getLeft();
		cog* getRight();
};

template <class T>
class btreeNode: public cog {
	private:
		const T key;
		cog* left;
		cog* right;
	public:
		btreeNode( T k, cog* l, cog* r );
		const T getKey();
		cog* getLeft();
		cog* getRight();
};

template <class T>
class policy {
	public:
		virtual void beforeInsert (cog* &root);
		virtual void afterInsert (cog* &root);
		virtual void beforeDelete (cog* &root);
		virtual void afterDelete (cog* &root);
		virtual void beforeRootIterator (cog* &root);
		virtual void beforeIterator	(cog* &node);
		virtual void idle (cog* &root);
};

template <class T>
class crackPolicy: public policy<T> {
	private:
		int minSize;
	public:
		crackPolicy(int s);
		void beforeIterator	(cog* &node);
};

template <class T>
class jitd {
	private:
		cog* root;
		policy<T>* p;
	public:
		jitd(policy<T>* pl);
		cog* getRoot();
		void insert(T* data, int size);
		vector<T> scan(T low, T high);
		vector<T> scan(cog* node, T low, T high);
};

cog::cog (int t): type(t) {}
const int cog::getType(){
	return type;
}

template <class T>
arrayNode<T>::arrayNode( T* d ,int s)
: cog(ARRAY){
	for(int i = 0; i < s; i++){
		data.push_back(d[i]);
	}
}

template <class T>
arrayNode<T>::arrayNode(vector<T> d)
: cog(ARRAY), data(d){}

template <class T>
vector<T> arrayNode<T>::getData(){
	return data;
}

template <class T>
int arrayNode<T>::getSize(){
	return data.size();
}

template <class T>
sortedarrayNode<T>::sortedarrayNode( T* d, int s)
: cog(SORTED_ARRAY){
	for(int i = 0; i < s; i++){
		data.push_back(d[i]);
	}
}

template <class T>
sortedarrayNode<T>::sortedarrayNode(vector<T> d)
: cog(SORTED_ARRAY), data(d){}

template <class T>
vector<T> sortedarrayNode<T>::getData(){
	return data;
}

template <class T>
int sortedarrayNode<T>::getSize(){
	return data.size();
}

concatNode::concatNode( cog* l, cog* r )
: cog(CONCAT),
left(l),
right(r)
{}

cog* concatNode::getLeft(){
	return left;
}

cog* concatNode::getRight(){
	return right;
}

template <class T>
btreeNode<T>::btreeNode( T k, cog* l, cog* r )
: cog(BTREE),
key(k),
left(l),
right(r)
{}

template <class T>
const T btreeNode<T>::getKey(){
	return key;
}

template <class T>
cog* btreeNode<T>::getLeft(){
	return left;
}

template <class T>
cog* btreeNode<T>::getRight(){
	return right;
}

template <class T>
void policy<T>::beforeInsert (cog* &root){}

template <class T>
void policy<T>::afterInsert (cog* &root){}

template <class T>
void policy<T>::beforeDelete (cog* &root){}

template <class T>
void policy<T>::afterDelete (cog* &root){}

template <class T>
void policy<T>::beforeRootIterator (cog* &root){}

template <class T>
void policy<T>::beforeIterator	(cog* &node){}

template <class T>
void policy<T>::idle (cog* &root){}

template <class T>
crackPolicy<T>::crackPolicy(int s): minSize(s) {}

template <class T>
void crackPolicy<T>::beforeIterator (cog* &node){
	switch(node->getType()){
		case ARRAY:{
					if(((arrayNode<T>*)node)->getSize() >= minSize){
						vector<T> data = ((arrayNode<T>*)node)->getData();
						vector<T> left;
						vector<T> right;
						T min = data[0];
						T max = data[0];
						T key = data[0];
						for(int i = 0; i < data.size(); i++){
							if(data[i] <= min){
								min = data[i];
							}
							else if(data[i] >= max){
								max = data[i];
							}
							else {
								key = data[i];
								break;
							}
						}

						for (int i = 0; i < data.size(); i++){
							if(data[i] > key){
								right.push_back(data[i]);
							}
							else left.push_back(data[i]);
						}
						
						if(left.size() != 0 && right.size() != 0){
							cog* l = new arrayNode<T>(left);
							cog* r = new arrayNode<T>(right);
							node = new btreeNode<T>(key, l, r);
						}
					}
					return;
				}
		case SORTED_ARRAY:{
					if(((sortedarrayNode<T>*)node)->getSize() >= minSize){
						vector<T> data = ((sortedarrayNode<T>*)node)->getData();
						T key = data[data.size()/2];
						vector<T> left;
						vector<T> right;
						for (int i = 0; i < data.size(); i++){
							if(data[i] > key){
								right.push_back(data[i]);
							}
							else left.push_back(data[i]);
						}
						if(left.size() != 0 && right.size() != 0){
							cog* l = new sortedarrayNode<T>(left);
							cog* r = new sortedarrayNode<T>(right);
							node = new btreeNode<T>(key, l, r);
						}
					}
					return;
				}
	}
}

template <class T>
jitd<T>::jitd(policy<T>* pl): root(NULL), p(pl){}

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
	if(root == NULL){
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


// template <class T>
// class readQuery {
// 	public:
// 		T low;
// 		T high;
// };

// class workload {
// 	public:
// 		double duration;
// 		double probability;
// 		double distribution;
// }

// vector<query> workloadGenerator(vector<workload> w){
// 	vector<query> q;
// 	for(int i = 0; i < w.size(); i++){
		
// 	}
// }




int main() {
	crackPolicy<int>* p = new crackPolicy<int>(3);
	jitd<int> myJitd(p);
	int list[] = {5,2,7,3,9,4,2,3};
	myJitd.insert(list, 8);
	vector<int> result = myJitd.scan(3,6);
    for(int i = 0; i<result.size(); i++){
        cout << result[i] << endl;
    }
	return 0;
}

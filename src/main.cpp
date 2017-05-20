#include <iostream>
#include <vector>
#include "jitd.h"
#include "jitd.cpp"
#include "crackPolicy.h"
#include "crackPolicy.cpp"
#include "cogTypes.h"

using namespace std;

void printTree(cog* it,int depth){
	switch(it->getType()){
		case ARRAY:
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "(" << it->getReadcount() << ")" << "ARRAY:" << ((arrayNode<int>*)it)->getSize() << endl;
			return;
		case SORTED_ARRAY:
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "(" << it->getReadcount() << ")" << "SORTED_ARRAY:" << ((sortedarrayNode<int>*)it)->getSize() << endl;
			return;
		case BTREE:
			printTree(((btreeNode<int>*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "(" << it->getReadcount() << ")" << "BTREE:" << ((btreeNode<int>*)it)->getKey() << "{" << endl;
			printTree(((btreeNode<int>*)it)->right, depth+1);
			return;
		case CONCAT:
			printTree(((btreeNode<int>*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "(" << it->getReadcount() << ")" << "CONCAT:" << "{" <<  endl;
			printTree(((btreeNode<int>*)it)->right, depth+1);
			return;
	}
}

int main() {
	crackPolicy<int>* p = new crackPolicy<int>(3);
	jitd<int> myJitd(p);
	int list[] = {5,2,7,3,9,4,2,3,5,7,8,9,0,3,343,54,232,5452};
	myJitd.insert(list, (sizeof(list)/sizeof(int)));
	vector<int> result = myJitd.scan(3,5);
    for(int i = 0; i<result.size(); i++){
        cout << result[i] << endl;
    }
    printTree(myJitd.getRoot(),0);
    result = myJitd.scan(5,70);
    for(int i = 0; i<result.size(); i++){
        cout << result[i] << endl;
    }
    printTree(myJitd.getRoot(),0);


    return 0;
}

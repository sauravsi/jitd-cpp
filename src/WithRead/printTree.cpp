#include "printTree.h"
#include "cog.h"
#include "cogTypes.h"
#include <iostream>

using namespace std;

void printTree(cog* it,int depth){
	switch(it->getType()){
		case ARRAY:{
				for (int i = 0; i < depth; ++i){
					cout << "\t";
				}
				vector<int> arrdata = ((arrayNode<int>*)it)->getData();
				cout << "(" << it->getReadcount() << ")" ;
				cout << "ARRAY:" << ((arrayNode<int>*)it)->getSize() << "{" << arrdata[0];
				for (int i = 1; i < arrdata.size(); ++i){
					cout << "," << arrdata[i];
				}
				cout << "}" << endl;
				return;
			}
		case SORTED_ARRAY:{
				for (int i = 0; i < depth; ++i){
					cout << "\t";
				}
				vector<int> arrdata = ((sortedarrayNode<int>*)it)->getData();
				cout << "(" << it->getReadcount() << ")" ;
				cout << "SORTED_ARRAY:" << ((sortedarrayNode<int>*)it)->getSize() << "{" << arrdata[0];
				for (int i = 1; i < arrdata.size(); ++i){
					cout << "," << arrdata[i];
				}
				cout << "}" << endl;
				return;
			}
		case BTREE:
			printTree(((btreeNode<int>*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "(" << it->getReadcount() << ")" ;
			cout << "BTREE:" << ((btreeNode<int>*)it)->getKey() << "{" << endl;
			printTree(((btreeNode<int>*)it)->right, depth+1);
			return;
		case CONCAT:
			printTree(((concatNode*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "(" << it->getReadcount() << ")" ;
			cout << "CONCAT:" << "{" <<  endl;
			printTree(((concatNode*)it)->right, depth+1);
			return;
	}
}
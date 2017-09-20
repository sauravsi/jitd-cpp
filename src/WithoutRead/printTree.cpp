#include "printTree.h"
#include "cog.h"
#include "cogTypes.h"
#include "data.h"
#include <iostream>

using namespace std;

void printTree(cog* it,int depth){
	switch(it->getType()){
		case ARRAY:{
				for (int i = 0; i < depth; ++i){
					cout << "\t";
				}
				cout << "ARRAY:" << ((arrayNode<data>*)it)->getSize() << "{" << ((arrayNode<data>*)it)->data->at(0).key;
				for (int i = 1; i < ((arrayNode<data>*)it)->getSize() ; ++i){
					cout << "," << ((arrayNode<data>*)it)->data->at(i).key;
				}
				cout << "}" << endl;
				return;
			}
		case SORTED_ARRAY:{
				for (int i = 0; i < depth; ++i){
					cout << "\t";
				}
				cout << "SORTED_ARRAY:" << ((sortedarrayNode<data>*)it)->getSize() << "{" << ((sortedarrayNode<data>*)it)->data->at(0).key;
				for (int i = 1; i < ((sortedarrayNode<data>*)it)->getSize(); ++i){
					cout << "," << ((sortedarrayNode<data>*)it)->data->at(i).key;
				}
				cout << "}" << endl;
				return;
			}
		case BTREE:
			printTree(((btreeNode<data>*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "BTREE:" << ((btreeNode<data>*)it)->getKey().key << "{" << endl;
			printTree(((btreeNode<data>*)it)->right, depth+1);
			return;
		case CONCAT:
			printTree(((concatNode*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "CONCAT:" << "{" <<  endl;
			printTree(((concatNode*)it)->right, depth+1);
			return;
	}
}


void printTreeInt(cog* it,int depth){
	switch(it->getType()){
		case ARRAY:{
				for (int i = 0; i < depth; ++i){
					cout << "\t";
				}
				cout << "ARRAY:" << ((arrayNode<int>*)it)->getSize() << "{" << ((arrayNode<int>*)it)->data->at(0);
				for (int i = 1; i < ((arrayNode<int>*)it)->getSize() ; ++i){
					cout << "," << ((arrayNode<int>*)it)->data->at(i);
				}
				cout << "}" << endl;
				return;
			}
		case SORTED_ARRAY:{
				for (int i = 0; i < depth; ++i){
					cout << "\t";
				}
				cout << "SORTED_ARRAY:" << ((sortedarrayNode<int>*)it)->getSize() << "{" << ((sortedarrayNode<int>*)it)->data->at(0);
				for (int i = 1; i < ((sortedarrayNode<int>*)it)->getSize(); ++i){
					cout << "," << ((sortedarrayNode<int>*)it)->data->at(i);
				}
				cout << "}" << endl;
				return;
			}
		case BTREE:
			printTreeInt(((btreeNode<int>*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "BTREE:" << ((btreeNode<int>*)it)->getKey() << "{" << endl;
			printTreeInt(((btreeNode<int>*)it)->right, depth+1);
			return;
		case CONCAT:
			printTreeInt(((concatNode*)it)->left, depth+1);
			for (int i = 0; i < depth; ++i){
				cout << "\t";
			}
			cout << "CONCAT:" << "{" <<  endl;
			printTreeInt(((concatNode*)it)->right, depth+1);
			return;
	}
}
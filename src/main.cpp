#include <iostream>
#include <vector>
#include "jitd.h"
#include "jitd.cpp"
#include "policyTypes.h"
#include "cogTypes.h"

using namespace std;

void printTree(cog* it,int depth){
	switch(it->getType()){
		case ARRAY:{
				for (int i = 0; i < depth; ++i){
					cout << "\t";
				}
				vector<int> arrdata = ((arrayNode<int>*)it)->getData();
				cout << "(" << it->getReadcount() << ")" << "ARRAY:" << ((arrayNode<int>*)it)->getSize() << "{" << arrdata[0];
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
				cout << "(" << it->getReadcount() << ")" << "SORTED_ARRAY:" << ((sortedarrayNode<int>*)it)->getSize() << "{" << arrdata[0];
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
	policy<int>* p1 = new crackPolicy<int>(3);
	policy<int>* p2 = new sortPolicy<int>();
	policy<int>* p3 = new splayPolicy<int>();
	vector<policy<int>* > policies;
	policies.push_back(p1);
	policies.push_back(p2);
	policies.push_back(p3);
	hybridPolicy<int>* p = new hybridPolicy<int>(policies);
	jitd<int> myJitd(p);
	int list[] = {5,2,7,3,9,4,2,3,5,7,8,9,0};
	
	myJitd.insert(list, (sizeof(list)/sizeof(int)));
	printTree(myJitd.getRoot(),0);
    
	cout << "scan(3,3)" << endl;
    vector<int> result = myJitd.scan(3,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "scan(5,5)" << endl;
    result = myJitd.scan(5,5);
    printTree(myJitd.getRoot(),0);

    cout << "scan(2,2)" << endl;
    result = myJitd.scan(2,2);
    printTree(myJitd.getRoot(),0);

    cout << "scan(3,3)" << endl;
    result = myJitd.scan(3,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "scan(3,3)" << endl;
    result = myJitd.scan(3,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "scan(2,2)" << endl;
    result = myJitd.scan(2,2);
    printTree(myJitd.getRoot(),0);
    
    cout << "scan(2,2)" << endl;
    result = myJitd.scan(2,2);
    printTree(myJitd.getRoot(),0);
    
    cout << "scan(9,9)" << endl;
    result = myJitd.scan(9,9);
    printTree(myJitd.getRoot(),0);

    cout << "scan(3,3)" << endl;
    result = myJitd.scan(3,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "scan(2,2)" << endl;
    result = myJitd.scan(2,2);
    printTree(myJitd.getRoot(),0);
    
    // for (int i = 0; i < result.size(); ++i){
    // 	cout << result[i] << endl;
    // }

    return 0;
}

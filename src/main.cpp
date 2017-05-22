#include <iostream>
#include <vector>

#define READCOUNT
#undef READCOUNT

#include "jitd.h"
#include "jitd.cpp"
#include "policyTypes.h"
#include "cogTypes.h"
#include "printTree.h"

using namespace std;

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
    
	cout << "---scan(2,3)---" << endl;
    vector<int> result = myJitd.scan(2,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "---scan(5,5)---" << endl;
    result = myJitd.scan(5,5);
    printTree(myJitd.getRoot(),0);

    cout << "---scan(2,2)---" << endl;
    result = myJitd.scan(2,2);
    printTree(myJitd.getRoot(),0);

    cout << "---scan(3,3)---" << endl;
    result = myJitd.scan(3,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "---scan(3,3)---" << endl;
    result = myJitd.scan(3,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "---scan(2,2)---" << endl;
    result = myJitd.scan(2,2);
    printTree(myJitd.getRoot(),0);
    
    cout << "---scan(2,3)---" << endl;
    result = myJitd.scan(2,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "---scan(9,9)---" << endl;
    result = myJitd.scan(9,9);
    printTree(myJitd.getRoot(),0);

    cout << "---scan(3,3)---" << endl;
    result = myJitd.scan(3,3);
    printTree(myJitd.getRoot(),0);
    
    cout << "---scan(2,2)---" << endl;
    result = myJitd.scan(2,2);
    printTree(myJitd.getRoot(),0);
    
    // for (int i = 0; i < result.size(); ++i){
    // 	cout << result[i] << endl;
    // }

    return 0;
}

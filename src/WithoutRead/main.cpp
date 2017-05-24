#include <iostream>
#include <vector>
#include <tuple>

#include "jitd.h"
#include "jitd.cpp"
#include "policyTypes.h"
#include "cogTypes.h"
#include "printTree.h"
#include "dataGenerator.h"
#include "queryGenerator.h"

using namespace std;

int main() {
    policy<int>* p1 = new crackPolicy<int>(3);
    policy<int>* p2 = new sortPolicy<int>();
    vector<policy<int>* > policies;
    policies.push_back(p1);
    policies.push_back(p2);
    hybridPolicy<int>* p = new hybridPolicy<int>(policies);
    jitd<int> myJitd(p);

    int dataSeed = 80;
    int dataMin = 0;
    int dataMax = 9;
    const int dataSize = 1000;

    int list[dataSize] = {};
    dataGenerator(dataSeed, dataMin, dataMax, list, dataSize);

    int querySeed = 44;
    int rangeSize = 3;
    int queryCount = 1000;
    double hhDataRange = 0.2;
    double hhProbability = 0.8;

    vector<tuple<int,int> > queries = queryGenerator(querySeed, queryCount, dataMin, dataMax, rangeSize, hhDataRange, hhProbability);

    myJitd.insert(list, (sizeof(list)/sizeof(int)));
    printTree(myJitd.getRoot(),0);
    
    for (int i = 0; i < queries.size(); ++i)
    {
        cout << "---scan(" << get<0>(queries[i]) << "," << get<1>(queries[i]) << ")---" << endl;
        vector<int> result = myJitd.scan(get<0>(queries[i]), get<1>(queries[i]));
    }
    printTree(myJitd.getRoot(),0);
    // for (int i = 0; i < result.size(); ++i){
    //  cout << result[i] << endl;
    // }

    return 0;
}


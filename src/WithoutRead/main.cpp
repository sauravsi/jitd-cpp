#include <iostream>
#include <vector>
#include <tuple>

#include "jitd.h"
#include "jitd.cpp"
#include "policyTypes.h"
#include "cogTypes.h"
#include "tester.h"

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
    int dataSize = 1000;

    int querySeed = 44;
    int rangeSize = 3;
    int queryCount = 10;
    double hhDataRange = 0.2;
    double hhProbability = 0.8;

    tester myTester(dataSeed, querySeed, &myJitd);
    myTester.insert(1, dataSize, dataMin, dataMax);
    myTester.printJitd();
    myTester.scan(queryCount, dataMin, dataMax, rangeSize, hhDataRange, hhProbability);
    myTester.printJitd();
    vector<unsigned int> runtimes = myTester.getRuntimes();
    for (int i = 0; i < runtimes.size(); ++i){
        cout << runtimes[i]<< ",";
    }

    cout << endl;

    // printTree(myJitd.getRoot(),0);
    // for (int i = 0; i < result.size(); ++i){
    //  cout << result[i] << endl;
    // }

    return 0;
}


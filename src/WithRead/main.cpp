#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#include "jitd.h"
#include "jitd.cpp"
#include "policyTypes.h"
#include "cogTypes.h"
#include "tester.h"
#include "getLine.h"

#include "splayPolicy.h"
#include "splayPolicy.cpp"

#define DATASEED 80
#define QUERYSEED 44

using namespace std;

int main() {

	vector<policy<int>* > policies;
	vector<string> line;
    line = getLine();
    string pol("policy");
    if(line[0].compare(pol) == 0){
        string crack("crack");
        string sort("sort");
        string splay("splay");
        for (int i = 1; i < line.size(); ++i) {
            if(line[i].compare(crack) == 0) {
                int s = stoi(line[++i]);
                policy<int>* p1 = new crackPolicy<int>(s);
                policies.push_back(p1);
            }
            else if(line[i].compare(sort) == 0) {
                policy<int>* p2 = new sortPolicy<int>();
                policies.push_back(p2);
            }
            else if(line[i].compare(splay) == 0) {
                policy<int>* p3 = new splayPolicy<int>();
                policies.push_back(p3);
            }
        }
    }
    else {
        return 0;
    }
    hybridPolicy<int>* p = new hybridPolicy<int>(policies);
	jitd<int> myJitd(p);
    tester myTester(DATASEED, QUERYSEED, &myJitd);
    
    string end("end");
    string insert("insert");
    string scan("scan");
    do{
        line = getLine();
        if(line[0].compare(insert) == 0){
            int queryCount = stoi(line[1]);
            int dataMin = stoi(line[2]);
            int dataMax = stoi(line[3]);
            int dataSize = stoi(line[4]);
            myTester.insert(queryCount, dataSize, dataMin, dataMax);
        }
        else if(line[0].compare(scan) == 0){
            int queryCount = stoi(line[1]);
            int dataMin = stoi(line[2]);
            int dataMax = stoi(line[3]);
            int rangeSize = stoi(line[4]);
            double hhDataRange = stod(line[5]);
            double hhProbability = stod(line[6]);    
            myTester.scan(queryCount, dataMin, dataMax, rangeSize, hhDataRange, hhProbability);
        }
    } while(line[0].compare(end) != 0);    
    vector<unsigned int> runtimes = myTester.getRuntimes();
    cout << "RUNTIMES:" << endl << runtimes[0];
    for (int i = 1; i < runtimes.size(); ++i){
        cout << "," << runtimes[i];
    }
    cout << endl;
    // for (int i = 0; i < result.size(); ++i){
    // 	cout << result[i] << endl;
    // }

    return 0;
}

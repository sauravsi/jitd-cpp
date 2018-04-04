#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <chrono>

#include "jitd.h"
#include "jitd.cpp"
#include "policyTypes.h"
#include "cogTypes.h"
#include "tester.h"
#include "treeBuilder.h"
#include "getLine.h"
#include "data.h"
#include "printTree.h"
#include "randUniform.h"
#include "queryGenerator.h"

#define DATASEED 99
#define QUERYSEED 76

using namespace std;



int main(int argc, char* argv[]) {
    using clock = std::chrono::steady_clock;
    if(argc < 2){
        cout << "Please enter testscript file" << endl;
        return -1;
    }
    vector<policy<data>* > policies;
    vector<string> line;
    ifstream ifile(argv[1]);
    line = getLine(ifile);
    string pol("policy");
    string tb("testbench");
    if(line[0].compare(pol) == 0){
        string crack("crack");
        string sort("sort");
        for (int i = 1; i < line.size(); ++i) {
            if(line[i].compare(crack) == 0) {
                int s = stoi(line[++i]);
                policy<data>* p1 = new crackPolicy<data>(s);
                policies.push_back(p1);
            }
            else if(line[i].compare(sort) == 0) {
                policy<data>* p2 = new sortPolicy<data>();
                policies.push_back(p2);
            }
        }
    }
    else if(line[0].compare(tb) == 0){
        int dataMin = stoi(line[1]);
        int dataMax = stoi(line[2]);
        int dataSize = stoi(line[3]);
        int crackThreshold = stoi(line[4]);
        int scanPerIter = stoi(line[5]);
        treeBuilder* myTree = new treeBuilder(DATASEED, dataMin, dataMax, dataSize);
        randUniform generator(QUERYSEED, dataMin, dataMax);
        vector<policy<int>* > pls;
        hybridPolicy<int>* p = new hybridPolicy<int>(pls);
        jitd<int> myJitd(myTree->root, p);
        vector<tuple<int,int> > dataV = queryGenerator(QUERYSEED, scanPerIter, dataMin, dataMax, 1, 0.0 , 0.0);
        vector<int> v;
        for (int i = 0; i < scanPerIter; ++i){
            v.push_back(get<0>(dataV[i]));
            // cout << v[i] << ",";
        }
        // cout << endl;
        clock::time_point start = clock::now();
        for (int i = 0; i < scanPerIter; ++i){
            vector<int>* result = new vector<int>();
            myJitd.scan(myTree->root,v[i],v[i],*result);
        }
        clock::time_point end = clock::now();
        clock::duration execution_time1 = end - start;
        start = clock::now();
        for (int i = 0; i < scanPerIter; ++i){
            vector<int>* result = new vector<int>();
        }
        end = clock::now();
        clock::duration execution_time2 = end - start;
        unsigned long int avg_runtime = (chrono::duration_cast<chrono::nanoseconds>(execution_time1 - execution_time2).count())/scanPerIter;
        cout << "c\t0\t" << 0 << '\t' << avg_runtime << endl;
        //while(((arrayNode<int>*)*(myTree->pq.top()))->getSize()>crackThreshold){
        bool thresholdReached = false;
        while(!thresholdReached){
            int listSize = myTree->dfc.size();
            for(int i = 0; i < listSize; i++){
                int arrSize = ((arrayNode<int>*)*(myTree->dfc.front()))->getSize();
                if(arrSize <= crackThreshold){
                    thresholdReached = true;
                }
                unsigned long int cracking_time = myTree->crackDepthFirst();
                if(cracking_time > 0){
                    start = clock::now();
                    for (int i = 0; i < scanPerIter; ++i){
                        vector<int>* result = new vector<int>();
                        myJitd.scan(myTree->root,v[i],v[i],*result);
                        delete result;
                    }
                    end = clock::now();
                    execution_time1 = end - start;
                    start = clock::now();
                    for (int i = 0; i < scanPerIter; ++i){
                        vector<int>* result = new vector<int>();
                        delete result;
                    }
                    end = clock::now();
                    execution_time2 = end - start;
                    avg_runtime = (chrono::duration_cast<chrono::nanoseconds>(execution_time1 - execution_time2).count())/scanPerIter;
                    cout << "c\t" << arrSize << '\t' << cracking_time << '\t' << avg_runtime << endl;
                }
            }
        }
        while(myTree->uncracked.size()>0){
            auto temp = myTree->uncracked.top();
            myTree->dfc.push(temp);
            myTree->uncracked.pop();
        }
        while(myTree->dfc.size()>0){
            int arrSize = ((arrayNode<int>*)*(myTree->dfc.front()))->getSize();
            unsigned long int sorting_time = myTree->sortDepthFirst();
            clock::time_point start = clock::now();
            for (int i = 0; i < scanPerIter; ++i){
                vector<int>* result = new vector<int>();
                myJitd.scan(myTree->root,v[i],v[i],*result);
                delete result;
            }
            clock::time_point end = clock::now();
            clock::duration execution_time1 = end - start;
            start = clock::now();
            for (int i = 0; i < scanPerIter; ++i){
                vector<int>* result = new vector<int>();
                delete result;
            }
            end = clock::now();
            clock::duration execution_time2 = end - start;
            unsigned long int avg_runtime = (chrono::duration_cast<chrono::nanoseconds>(execution_time1 - execution_time2).count())/scanPerIter;
            cout << "s\t" << arrSize << '\t' << sorting_time << '\t' << avg_runtime << endl;
        }
        // do{
        //     cout << ((arrayNode<int>*)*(myTree->pq.top()))->getSize() << endl;
        //     myTree->pq.pop();
        // }while(myTree->pq.size()>0);
        
        // printTreeInt(myTree->root,0);

        return 0;

    }
    else {
        return 0;
    }
    hybridPolicy<data>* p = new hybridPolicy<data>(policies);
    jitd<data> myJitd(p);
    tester myTester(DATASEED, QUERYSEED, &myJitd);
    
    string end("end");
    string insert("insert");
    string scan("scan");
    do{
        line = getLine(ifile);
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
    cout << "RUNTIMES:" << endl << myTester.runtimes[0] << "\t" << myTester.maptimes[0];
    for (int i = 1; i < myTester.runtimes.size(); ++i){
        cout << endl << myTester.runtimes[i] << "\t" << myTester.maptimes[i];
    }
    cout << endl;
    // for (int i = 0; i < result.size(); ++i){
    //  cout << result[i] << endl;
    // }

    return 0;
}

#include "tester.h"

#include <chrono>
#include <vector>
#include <tuple>
#include <map>
#include <iostream>

#include "jitd.h"
#include "jitd.cpp"
#include "dataGenerator.h"
#include "queryGenerator.h"
#include "printTree.h"
#include "data.h"

using namespace std;

tester::tester(int insert_seed, int scan_seed, jitd<data>* mj):myJitd(mj), i_seed(insert_seed), s_seed(scan_seed){}

void tester::insert(int queryCount, int dataSize, int dataMin, int dataMax){
	for (int i = 0; i < queryCount; ++i){
		data* list;
    	list = (data*)calloc(dataSize, sizeof(data));
    	vector<pair<int,int> > list2;
    	dataGenerator(i_seed, dataMin, dataMax, dataSize, list, &list2);
		using clock = std::chrono::steady_clock;
		clock::time_point start = clock::now();
		myJitd->insert(list, dataSize);
		clock::time_point end = clock::now();
		clock::duration execution_time = end - start;
		runtimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());
		i_seed++;
		// insert in other datastructures
		
		start = clock::now();
		mapOfData.insert(list2.begin(), list2.end());
		end = clock::now();
		execution_time = end - start;
		maptimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());



		// cout << "INSERT---------" << endl;
		// printJitd();
	}
}

void tester::scan(int queryCount, int dataMin, int dataMax, int rangeSize, double hhDataRange, double hhProbability){
	vector<tuple<int,int> > queries = queryGenerator(s_seed, queryCount, dataMin, dataMax, rangeSize, hhDataRange, hhProbability);
	for (int i = 0; i < queries.size(); ++i){
		using clock = std::chrono::steady_clock;
		data low(get<0>(queries[i]),get<0>(queries[i]));
		data high(get<1>(queries[i]),get<1>(queries[i]));
		vector<data>* result = new vector<data>();
		clock::time_point start = clock::now();
		myJitd->scan(low,high,*result);
		clock::time_point end = clock::now();
		clock::duration execution_time = end - start;
		runtimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());
		//scan in other datastructures
		vector<pair<int,int> >* result2 = new vector<pair<int,int> >;
		start = clock::now();
		for(map<int,int>::iterator it = mapOfData.find(get<0>(queries[i])); it != mapOfData.end() && it->first <= get<1>(queries[i]); it++){
			result2->push_back(*it);
		}
		end = clock::now();
		execution_time = end - start;
		maptimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());




		// cout << "SCAN----------" << endl;
		// printJitd();
	}
	s_seed++;
}

void tester::printJitd(){
	printTree(myJitd->getRoot(),0);
}
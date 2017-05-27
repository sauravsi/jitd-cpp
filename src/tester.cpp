#include "tester.h"

#include <chrono>
#include <vector>
#include <tuple>

#include "jitd.h"
#include "jitd.cpp"
#include "dataGenerator.h"
#include "queryGenerator.h"
#include "printTree.h"

using namespace std;

tester::tester(int insert_seed, int scan_seed, jitd<int>* mj):myJitd(mj), i_seed(insert_seed), s_seed(scan_seed){}

void tester::insert(int queryCount, int dataSize, int dataMin, int dataMax){
	for (int i = 0; i < queryCount; ++i){
		int* list;
    	list = (int*)calloc(dataSize, sizeof(int));
    	dataGenerator(i_seed, dataMin, dataMax, list, dataSize);
		using clock = std::chrono::steady_clock;
		clock::time_point start = clock::now();
		myJitd->insert(list, dataSize);
		clock::time_point end = clock::now();
		clock::duration execution_time = end - start;
		runtimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());
		i_seed++;
	}
}

void tester::scan(int queryCount, int dataMin, int dataMax, int rangeSize, double hhDataRange, double hhProbability){
	vector<tuple<int,int> > queries = queryGenerator(s_seed, queryCount, dataMin, dataMax, rangeSize, hhDataRange, hhProbability);
	for (int i = 0; i < queries.size(); ++i){
		using clock = std::chrono::steady_clock;
		clock::time_point start = clock::now();
		myJitd->scan(get<0>(queries[i]),get<1>(queries[i]));
		clock::time_point end = clock::now();
		clock::duration execution_time = end - start;
		runtimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());
	}
	s_seed++;
}

vector<unsigned int> tester::getRuntimes(){
	return runtimes;
}

void tester::printJitd(){
	printTree(myJitd->getRoot(),0);
}
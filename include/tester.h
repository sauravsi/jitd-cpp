#ifndef TESTER_H_
#define TESTER_H_

#include "jitd.h"
#include "data.h"
#include <map>
#include <vector>

using namespace std;

class tester {
	private:
		jitd<data>* myJitd;
		int i_seed;
		int s_seed;
		map<int, int> mapOfData;
	public:
		vector<unsigned long int> runtimes;
		vector<unsigned long int> maptimes;
		tester(int insert_seed, int scan_seed, jitd<data>* mj);
		void insert(int queryCount, int dataSize, int dataMin, int dataMax);
		void scan(int queryCount, int dataMin, int dataMax, int rangeSize, double hhDataRange, double hhProbability);
		void printJitd();
};


#endif /* TESTER_H_ */
#ifndef TESTER_H_
#define TESTER_H_

#include "jitd.h"
#include "data.h"
#include <vector>

using namespace std;

class tester {
	private:
		jitd<data>* myJitd;
		vector<unsigned long int> runtimes;
		int i_seed;
		int s_seed;
	public:
		tester(int insert_seed, int scan_seed, jitd<data>* mj);
		void insert(int queryCount, int dataSize, int dataMin, int dataMax);
		void scan(int queryCount, int dataMin, int dataMax, int rangeSize, double hhDataRange, double hhProbability);
		vector<unsigned long int> getRuntimes();
		void printJitd();
};


#endif /* TESTER_H_ */
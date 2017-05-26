#ifndef TESTER_H_
#define TESTER_H_

#include "jitd.h"
#include <vector>

using namespace std;

class tester {
	private:
		jitd<int>* myJitd;
		vector<unsigned int> runtimes;
		int i_seed;
		int s_seed;
	public:
		tester(int insert_seed, int scan_seed, jitd<int>* mj);
		void insert(int queryCount, int dataSize, int dataMin, int dataMax);
		void scan(int queryCount, int dataMin, int dataMax, int rangeSize, double hhDataRange, double hhProbability);
		vector<unsigned int> getRuntimes();
};


#endif /* TESTER_H_ */
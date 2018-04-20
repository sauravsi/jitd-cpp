#ifndef TESTER_H_
#define TESTER_H_

#include "jitd.h"
#include "data.h"
#include "cog.h"
#include "cogTypes.h"
#include "policy.h"
#include <vector>
#include <queue>

using namespace std;

auto PriorityFunction = [](cog**& a, cog**& b){
	if((*a)->getType() != (*b)->getType()){ // maybe assert?
		return (bool)0;
	}
	if((*a)->getType() == ARRAY){
		return ((arrayNode<data>*)*a)->getSize() < ((arrayNode<data>*)*b)->getSize(); // sorts pq in decending order of array size
	}
	if((*a)->getType() == SORTED_ARRAY){
		return ((sortedarrayNode<data>*)*a)->getSize() < ((sortedarrayNode<data>*)*b)->getSize();
	}
};

class tester {
	private:
		jitd<data>* myJitd;
		int i_seed;
		int s_seed;
		priority_queue<cog**, vector<cog**>, decltype(PriorityFunction)> arrayCogs;
		priority_queue<cog**, vector<cog**>, decltype(PriorityFunction)> crackedArrayCogs;
		priority_queue<cog**, vector<cog**>, decltype(PriorityFunction)> sortedArrayCogs;
	public:
		vector<char> opType;
		vector<unsigned long int> arraySizes;
		vector<unsigned long int> opTimes;
		vector<unsigned long int> scanTimes;
		tester(int insert_seed, int scan_seed, jitd<data>* mj);
		void insert(int queryCount, int dataSize, int dataMin, int dataMax);
		void scan(int queryCount, int dataMin, int dataMax, int rangeSize, double hhDataRange, double hhProbability, int opInterval, int crackThreshold);
		void printJitd();
};


#endif /* TESTER_H_ */
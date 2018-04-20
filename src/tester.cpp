#include "tester.h"

#include <chrono>
#include <vector>
#include <tuple>
#include <iostream>

#include "jitd.h"
#include "jitd.cpp"
#include "data.h"
#include "cog.h"
#include "cogTypes.h"
#include "dataGenerator.h"
#include "queryGenerator.h"
#include "printTree.h"
#include "policy.h"
#include "policyTypes.h"

using namespace std;

// SORT POLICY

void sortTransform (cog** node){
	switch((*node)->getType()){
		case ARRAY:{
					vector<data>* v = ((arrayNode<data>*)*node)->data;
					delete *node;
					sort(v->begin(), v->end());
					*node = new sortedarrayNode<data>(*v);
				}
	}
}

// CRACK POLICY

int partition(vector<data> &input, int p, int r)
{
    data pivot = input[r];
    
    while ( p < r )
    {
        while ( input[p] < pivot )
            p++;
        
        while ( input[r] > pivot )
            r--;
        
        if ( input[p] == input[r] )
            p++;
        else if ( p < r ) {
            data tmp = input[p];
            input[p] = input[r];
            input[r] = tmp;
        }
    }
    
    return r;
}

int quick_select(vector<data> &input, int p, int r, int k)
{
    if ( p == r ) return p;
    int j = partition(input, p, r);
    int length = j - p + 1;
    if ( length == k ) return j;
    else if ( k < length ) return quick_select(input, p, j - 1, k);
    else  return quick_select(input, j + 1, r, k - length);
}

void crackTransform (cog** node, int minSize){
	switch((*node)->getType()){
		case ARRAY:{
					if(((arrayNode<data>*)*node)->getSize() >= minSize){
						int key_index = quick_select(*(((arrayNode<data>*)*node)->data),0,((arrayNode<data>*)*node)->data->size()-1,((arrayNode<data>*)*node)->data->size()/2);
						data key = ((arrayNode<data>*)*node)->data->at(key_index);
						vector<data>* left = new vector<data>();
						vector<data>* right = new vector<data>();
						left->reserve(key_index+1);
						right->reserve(((arrayNode<data>*)*node)->getSize()-left->capacity());
						for(typename vector<data>::iterator it = ((arrayNode<data>*)*node)->data->begin(); it != ((arrayNode<data>*)*node)->data->end(); it++){
							if(*it > key){
								right->push_back(*it);
							}
							else left->push_back(*it);
						}
						if(left->size() != 0 && right->size() != 0){
							cog* l = new arrayNode<data>(*left);
							cog* r = new arrayNode<data>(*right);
							delete ((arrayNode<data>*)*node)->data;
							delete *node;
							*node = new btreeNode<data>(key, l, r);
						}
					}
					return;
				}
	}
}

// TESTER CODE

tester::tester(int insert_seed, int scan_seed, jitd<data>* mj):myJitd(mj), i_seed(insert_seed), s_seed(scan_seed), arrayCogs(PriorityFunction), crackedArrayCogs(PriorityFunction), sortedArrayCogs(PriorityFunction){}

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
		opType.push_back('i');
		arraySizes.push_back(dataSize);
		opTimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());
		i_seed++;
		cog* myCog = myJitd->getRoot();
		cog** newArray;
		if(myCog->getType() == ARRAY){
			newArray = &myCog;
		}
		else if(myCog->getType() == CONCAT){
			newArray = &(((concatNode*)myCog)->left);
		}
		if(((cog*)*newArray)->getType() == ARRAY){
			arrayCogs.push(newArray);
			cout << "pq size updated:" << arrayCogs.size() << endl;
		}
		// insert in other datastructures

		// cout << "INSERT---------" << endl;
		// printJitd();
	}
}

void tester::scan(int queryCount, int dataMin, int dataMax, int rangeSize, double hhDataRange, double hhProbability, int opInterval, int crackThreshold){
	vector<tuple<int,int> > queries = queryGenerator(s_seed, queryCount, dataMin, dataMax, rangeSize, hhDataRange, hhProbability);
	int operationCounter = 0;
	do{
		cout << "pq size:" << arrayCogs.size() << endl;
		if(operationCounter%opInterval == 0){
			operationCounter = 0;
			unsigned long int totalScanTime = 0;
			for (int i = 0; i < queries.size(); ++i){
				using clock = std::chrono::steady_clock;
				data low(get<0>(queries[i]),get<0>(queries[i]));
				data high(get<1>(queries[i]),get<1>(queries[i]));
				vector<data>* result = new vector<data>();
				clock::time_point start = clock::now();
				myJitd->scan(low,high,*result);
				clock::time_point end = clock::now();
				clock::duration execution_time = end - start;
				totalScanTime+= chrono::duration_cast<chrono::nanoseconds>(execution_time).count();
			}
			unsigned long int averageScanTime = totalScanTime/queries.size();
			scanTimes.push_back(averageScanTime);
		}
		// CRACK or SORT
		// crackPolicy<data>* cp = new crackPolicy<data>(crackThreshold);
		// sortPolicy<data>* sp = new sortPolicy<data>();

		if (arrayCogs.size() > 0){
			cog** myCog = arrayCogs.top();
			arrayCogs.pop();
			if(((cog*)*myCog)->getType() == ARRAY){
				int myCogSize = ((arrayNode<data>*)*myCog)->getSize();
				if(myCogSize > crackThreshold){
					using clock = std::chrono::steady_clock;
					clock::time_point start = clock::now();
					crackTransform(myCog, crackThreshold);
					clock::time_point end = clock::now();
					clock::duration execution_time = end - start;
					if(((cog*)*myCog)->getType() == BTREE){
						cog** l = &(((btreeNode<data>*)*myCog)->left);
						cog** r = &(((btreeNode<data>*)*myCog)->right);
						if(((cog*)*l)->getType() == ARRAY){
							arrayCogs.push(l);
							cout << "pq size updated:" << arrayCogs.size() << endl;
						}
						if(((cog*)*r)->getType() == ARRAY){
							arrayCogs.push(r);
							cout << "pq size updated:" << arrayCogs.size() << endl;
						}
						operationCounter++;
						opType.push_back('c');
						arraySizes.push_back(myCogSize);
						opTimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());
						continue;
					}
				}
				else{
					crackedArrayCogs.push(myCog);
				}
			}
		}
		if(crackedArrayCogs.size() > 0){
			using clock = std::chrono::steady_clock;
			
			cog** myCog = sortedArrayCogs.top();
			sortedArrayCogs.pop();
			if(((cog*)*myCog)->getType() == SORTED_ARRAY){
				int myCogSize = ((sortedarrayNode<data>*)*myCog)->getSize();
				
				clock::time_point start = clock::now();
				sortTransform(myCog);
				clock::time_point end = clock::now();
				clock::duration execution_time = end - start;
		
				if(((cog*)*myCog)->getType() == SORTED_ARRAY){
					sortedArrayCogs.push(myCog);
					operationCounter++;
					opType.push_back('s');
					arraySizes.push_back(myCogSize);
					opTimes.push_back(chrono::duration_cast<chrono::nanoseconds>(execution_time).count());
					continue;
				}
			}
		}
		// after op
	}while(arrayCogs.size() > 0 || crackedArrayCogs.size() > 0);
	s_seed++;
}

void tester::printJitd(){
	printTree(myJitd->getRoot(),0);
}
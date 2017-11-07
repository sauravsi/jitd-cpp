#ifndef TREEBUILDER_H_
#define TREEBUILDER_H_

#include <queue>
#include <vector>
#include "cog.h"
#include "cogTypes.h"

using namespace std;

template<class T>
struct Comp{
    bool operator()(cog** lhs, cog** rhs){
        if((*lhs)->getType()== ARRAY && (*rhs)->getType() == ARRAY)
        return ((arrayNode<T>*)*lhs)->getSize() < ((arrayNode<T>*)*rhs)->getSize();
    }
};

class treeBuilder {
	public:
		cog* root;
		priority_queue<cog**, vector<cog**>, Comp<int>> pq;
		priority_queue<cog**, vector<cog**>, Comp<int>> uncracked;
		treeBuilder(int seed, int min, int max, int n);
		unsigned long int crackLargest();
		unsigned long int sortLargest();

};


#endif
#ifndef SORTPOLICY_CPP_
#define SORTPOLICY_CPP_

#include "sortPolicy.h"
#include <vector>
#include <algorithm>
#include "cog.h"
#include "cogTypes.h"

using namespace std;

template <class T>
void sortPolicy<T>::beforeIterator (cog* &node){
	switch(node->getType()){
		case ARRAY:{
					vector<T> data = ((arrayNode<T>*)node)->getData();
					sort(data.begin(), data.end());
					node = new sortedarrayNode<T>(data);
				}
	}
}

#endif /* SORTPOLICY_CPP_ */
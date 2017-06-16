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
					sort(((arrayNode<T>*)node)->data.begin(), ((arrayNode<T>*)node)->data.end());
					delete node;
					node = new sortedarrayNode<T>(((arrayNode<T>*)node)->data);
				}
	}
}

#endif /* SORTPOLICY_CPP_ */
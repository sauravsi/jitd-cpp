#ifndef SORTPOLICY_CPP_
#define SORTPOLICY_CPP_

#include "sortPolicy.h"
#include <vector>
#include "cog.h"
#include "cogTypes.h"

using namespace std;

template <class T>
void sortPolicy<T>::beforeIterator (cog* &node){
	switch(node->getType()){
		case ARRAY:{
					vector<T> data = ((arrayNode<T>*)node)->getData();
					int n = data.size();
					for(int i = 0; i < n; i++){
						for(int j = i+1; j < n; j++){
							if(data[i] > data[j]){
								T temp = data[i];
								data[i] = data[j];
								data[j] = temp;
							}
						}
					}
					node = new sortedarrayNode<T>(data);
				}
	}
}

#endif /* SORTPOLICY_CPP_ */
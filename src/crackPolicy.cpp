#ifndef CRACKPOLICY_CPP_
#define CRACKPOLICY_CPP_

#include "crackPolicy.h"
#include <vector>
#include "cog.h"
#include "cogTypes.h"

using namespace std;

template <class T>
crackPolicy<T>::crackPolicy(int s): minSize(s) {}

template <class T>
void crackPolicy<T>::beforeIterator (cog* &node){
	switch(node->getType()){
		case ARRAY:{
					if(((arrayNode<T>*)node)->getSize() >= minSize){
						vector<T>* left = new vector<T>();
						vector<T>* right = new vector<T>();
						T max =((arrayNode<T>*)node)->data->at(0);
						T key =((arrayNode<T>*)node)->data->at(0);
						for(int i = 0; i <((arrayNode<T>*)node)->getSize(); i++){
							if(max <((arrayNode<T>*)node)->data->at(i)){
								key = max;
								max =((arrayNode<T>*)node)->data->at(i);
								break;
							}
							else if(((arrayNode<T>*)node)->data->at(i) < max){
								key =((arrayNode<T>*)node)->data->at(i);
								break;
							}
						}

						if(key == max){
							return;
						}

						for (int i = 0; i <((arrayNode<T>*)node)->getSize(); i++){
							if(((arrayNode<T>*)node)->data->at(i) > key){
								right->push_back(((arrayNode<T>*)node)->data->at(i));
							}
							else left->push_back(((arrayNode<T>*)node)->data->at(i));
						}
						if(left->size() != 0 && right->size() != 0){
							cog* l = new arrayNode<T>(*left);
							cog* r = new arrayNode<T>(*right);
							delete ((arrayNode<T>*)node)->data;
							delete node;
							node = new btreeNode<T>(key, l, r);
						}
					}
					return;
				}
	}
}

#endif /* CRACKPOLICY_CPP_ */
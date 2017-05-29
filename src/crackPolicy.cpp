#ifndef CRACKPOLICY_CPP_
#define CRACKPOLICY_CPP_

#include "crackPolicy.h"
#include <vector>
#include <iostream>
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
						vector<T> data = ((arrayNode<T>*)node)->getData();
						vector<T> left;
						vector<T> right;
						T max = data[0];
						T key = data[0];
						for(int i = 0; i < data.size(); i++){
							if(max < data[i]){
								key = max;
								max = data[i];
								break;
							}
							else if(data[i] < max){
								key = data[i];
								break;
							}
						}

						if(key == max){
							return;
						}

						for (int i = 0; i < data.size(); i++){
							if(data[i] > key){
								right.push_back(data[i]);
							}
							else left.push_back(data[i]);
						}
						cout << "CRACKED!!::" << key << endl;
						if(left.size() != 0 && right.size() != 0){
							cog* l = new arrayNode<T>(left);
							cog* r = new arrayNode<T>(right);
							node = new btreeNode<T>(key, l, r);
						}
						cout << "new key::"<<((btreeNode<T>*)node)->getKey() << endl;
					}
					return;
				}
		case SORTED_ARRAY:{
					if(((sortedarrayNode<T>*)node)->getSize() >= minSize){
						vector<T> data = ((sortedarrayNode<T>*)node)->getData();
						T key = data[data.size()/2];
						vector<T> left;
						vector<T> right;
						for (int i = 0; i < data.size(); i++){
							if(data[i] > key){
								right.push_back(data[i]);
							}
							else left.push_back(data[i]);
						}
						if(left.size() != 0 && right.size() != 0){
							cog* l = new sortedarrayNode<T>(left);
							cog* r = new sortedarrayNode<T>(right);
							node = new btreeNode<T>(key, l, r);
						}
					}
					return;
				}
	}
}

#endif /* CRACKPOLICY_CPP_ */
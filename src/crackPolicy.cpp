#ifndef CRACKPOLICY_CPP_
#define CRACKPOLICY_CPP_

#include "crackPolicy.h"
#include <vector>
#include "cog.h"
#include "cogTypes.h"

using namespace std;

template <class T>
int partition(vector<T> &input, int p, int r)
{
    T pivot = input[r];
    
    while ( p < r )
    {
        while ( input[p] < pivot )
            p++;
        
        while ( input[r] > pivot )
            r--;
        
        if ( input[p] == input[r] )
            p++;
        else if ( p < r ) {
            T tmp = input[p];
            input[p] = input[r];
            input[r] = tmp;
        }
    }
    
    return r;
}

template <class T>
int quick_select(vector<T> &input, int p, int r, int k)
{
    if ( p == r ) return p;
    int j = partition(input, p, r);
    int length = j - p + 1;
    if ( length == k ) return j;
    else if ( k < length ) return quick_select(input, p, j - 1, k);
    else  return quick_select(input, j + 1, r, k - length);
}

template <class T>
crackPolicy<T>::crackPolicy(int s): minSize(s) {}

template <class T>
void crackPolicy<T>::beforeIterator (cog* &node){
	switch(node->getType()){
		case ARRAY:{
					if(((arrayNode<T>*)node)->getSize() >= minSize){
						int key_index = quick_select(*(((arrayNode<T>*)node)->data),0,((arrayNode<T>*)node)->data->size()-1,((arrayNode<T>*)node)->data->size()/2);
						T key = ((arrayNode<T>*)node)->data->at(key_index);
						vector<T>* left = new vector<T>();
						vector<T>* right = new vector<T>();
						left->reserve(key_index+1);
						right->reserve(((arrayNode<T>*)node)->getSize()-left->capacity());
						for(typename vector<T>::iterator it = ((arrayNode<T>*)node)->data->begin(); it != ((arrayNode<T>*)node)->data->end(); it++){
							if(*it > key){
								right->push_back(*it);
							}
							else left->push_back(*it);
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
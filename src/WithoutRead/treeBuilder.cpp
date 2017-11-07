#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>
#include "treeBuilder.h"
#include "cog.h"
#include "cogTypes.h"
#include "randUniform.h"

using namespace std;

treeBuilder::treeBuilder(int seed, int min, int max, int n){
	vector<int>* data = new vector<int>();
	randUniform generator(seed, min, max);
    for(int i = 0; i < n; i++){
    	int x = generator.getRand();
        data->push_back(x);
    }
    cog* temp = new arrayNode<int>(*data);
    root = temp;
    pq.push(&root);
}


template <class T>
int partition(vector<int> &input, int p, int r)
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
int quick_select(vector<int> &input, int p, int r, int k)
{
    if ( p == r ) return p;
    int j = partition<int>(input, p, r);
    int length = j - p + 1;
    if ( length == k ) return j;
    else if ( k < length ) return quick_select<int>(input, p, j - 1, k);
    else  return quick_select<int>(input, j + 1, r, k - length);
}


unsigned long int treeBuilder::crackLargest(){
	using clock = std::chrono::steady_clock;
	cog** node = pq.top();
	pq.pop();
            
	// CRACK
	clock::time_point start = clock::now();
	int key_index = (rand()%((arrayNode<int>*)*node)->getSize());
	// int key_index = quick_select<int>(*(((arrayNode<int>*)*node)->data),0,((arrayNode<int>*)*node)->data->size()-1,((arrayNode<int>*)*node)->data->size()/2);
	int key = ((arrayNode<int>*)*node)->data->at(key_index);
	vector<int>* left = new vector<int>();
	vector<int>* right = new vector<int>();
	left->reserve(key_index+1);
	right->reserve(((arrayNode<int>*)*node)->getSize()-left->capacity());
	for(typename vector<int>::iterator it = ((arrayNode<int>*)*node)->data->begin(); it != ((arrayNode<int>*)*node)->data->end(); it++){
		if(*it > key){
			right->push_back(*it);
		}
		else left->push_back(*it);
	}
	if(left->size() != 0 && right->size() != 0){
		cog* l = new arrayNode<int>(*left);
		cog* r = new arrayNode<int>(*right);
		delete ((arrayNode<int>*)*node)->data;
		//delete (arrayNode<int>*)*node;
		*node = new btreeNode<int>(key, l, r);
		clock::time_point end = clock::now();
        clock::duration execution_time = end - start;
		pq.push(&(((btreeNode<int>*)*node)->left));
		pq.push(&(((btreeNode<int>*)*node)->right));
		return chrono::duration_cast<chrono::nanoseconds>(execution_time).count();
	}
	else {
		uncracked.push(node);
		return 0;
	}
}


unsigned long int treeBuilder::sortLargest(){
	using clock = std::chrono::steady_clock;
	cog** node = pq.top();
	clock::time_point start = clock::now();
	vector<int>* v = ((arrayNode<int>*)*node)->data;
	sort(v->begin(), v->end());
	//delete (arrayNode<int>*)*node;
	*node = new sortedarrayNode<int>(*v);
	clock::time_point end = clock::now();
    clock::duration execution_time = end - start;
	pq.pop();
	return chrono::duration_cast<chrono::nanoseconds>(execution_time).count();
}


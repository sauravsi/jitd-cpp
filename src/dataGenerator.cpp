#include "randUniform.h"
#include "dataGenerator.h"
#include "data.h"

using namespace std;

void dataGenerator(int seed, int min, int max, int length, data d[], vector<pair<int,int> >* v){
    randUniform generator(seed, min, max);
    for(int i = 0; i < length; i++){
    	int x = generator.getRand();
        d[i].key = x;
        d[i].value = x;
        v->push_back(make_pair(x,x));
    }
}

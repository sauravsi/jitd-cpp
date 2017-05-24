#include "randUniform.h"
#include "dataGenerator.h"

void dataGenerator(int seed, int min, int max, int data[], int length){
    randUniform generator(seed, min, max);
    for(int i = 0; i < length; i++){
        data[i] = generator.getRand();
    }
}

#include "cog.h"

using namespace std;

cog::cog (int t): type(t), readcount(0) {}

cog::cog (int t, int r): type(t), readcount(r) {}

const int cog::getType(){
	return type;
}

int cog::getReadcount(){
	return readcount;
}

void cog::setReadcount(int x){
	readcount = x;
}

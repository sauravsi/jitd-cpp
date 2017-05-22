#ifndef COG_CPP_
#ifndef READCOUNT
#define COG_CPP_

#include "cogWithoutRead.h"

using namespace std;

cog::cog (int t): type(t) {}

const int cog::getType(){
	return type;
}
#endif
#endif
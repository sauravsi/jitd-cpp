#include "cog.h"

using namespace std;

cog::cog (int t): type(t) {}

const int cog::getType(){
	return type;
}

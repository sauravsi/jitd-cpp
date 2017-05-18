#ifndef CONCATNODE_H_
#define CONCATNODE_H_

#include "cog.h"

class concatNode: public cog {
	private:
		cog* left;
		cog* right;
	public:
		concatNode( cog* l, cog* r );
		cog* getLeft();
		cog* getRight();
};

#endif /* CONCATNODE_H_ */

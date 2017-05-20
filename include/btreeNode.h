#ifndef BTREENODE_H_
#define BTREENODE_H_

#include "cog.h"

template <class T>
class btreeNode: public cog {
	private:
		const T key;
	public:
		cog* left;
		cog* right;
		btreeNode( T k, cog* l, cog* r );
		const T getKey();
		cog* getLeft();
		cog* getRight();
};

#endif /* BTREENODE_H_ */

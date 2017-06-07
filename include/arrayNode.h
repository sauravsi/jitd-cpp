#ifndef ARRAYNODE_H_
#define ARRAYNODE_H_

#include <vector>
#include "cog.h"

using namespace std;

template <class T>
class arrayNode: public cog {
	private:
		vector<T> data;
	public:
		arrayNode( T* &d, int s);
		arrayNode(vector<T> &d);
		vector<T> getData();
		int getSize();
};

#endif /* ARRAYNODE_H_ */

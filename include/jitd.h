#ifndef JITD_H_
#define JITD_H_

#include <vector>

#include "policy.h"
#include "policy.cpp"

template <class T>
class jitd {
	private:
		cog* root;
		policy<T>* p;
	public:
		jitd(policy<T>* pl);
		jitd(cog* &r, policy<T>* pl);
		cog* getRoot();
		void insert(T* &data, int size);
		vector<T> scan(T low, T high);
		vector<T> scan(cog* &node, T low, T high);
};

#endif /* JITD_H_ */

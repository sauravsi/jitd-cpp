#ifndef JITD_H_
#define JITD_H_

#include <vector>

#include "policy.h"
#include "policy.cpp"

template <class T>
class jitd {
	private:
		
		policy<T>* p;
	public:
		cog* root;
		jitd(policy<T>* pl);
		jitd(cog* &r, policy<T>* pl);
		void insert(T* &data, int size);
		void scan(T low, T high, vector<T> &result);
		void scan(cog* &node, T low, T high, vector<T> &result);
};

#endif /* JITD_H_ */

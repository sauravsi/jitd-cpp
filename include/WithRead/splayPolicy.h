#ifndef SPLAYPOLICY_H_
#ifdef READCOUNT
#define SPLAYPOLICY_H_
#define READCOUNT

#include "cog.h"
#include "policy.h"
#include "policy.cpp"

template <class T>
class splayPolicy: public policy<T> {
	private:
		unsigned int nodeReadcount;
	public:
		splayPolicy();
		void afterInsert(cog* &node);
		void beforeIterator	(cog* &node);
		void afterIterator	(cog* &node);
};

#endif
#endif /* SPLAYPOLICY_H_ */
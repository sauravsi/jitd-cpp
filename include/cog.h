#ifndef COG_H_
#define COG_H_

class cog {
	protected:
		const int type;
		unsigned int readcount;
	public:
		cog (int t);
		cog (int t, unsigned int r);
		const int getType();
		unsigned int getReadcount();
		void setReadcount(unsigned int x);
};

#endif /* COG_H_ */

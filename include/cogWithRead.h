#ifndef COG_H_
#ifdef READCOUNT
#define COG_H_

class cog {
	protected:
		const int type;
		unsigned int readcount;
		
	public:
		cog (int t);
		const int getType();
		
		cog (int t, unsigned int r);
		unsigned int getReadcount();
		void setReadcount(unsigned int x);
};

#endif
#endif /* COG_H_ */

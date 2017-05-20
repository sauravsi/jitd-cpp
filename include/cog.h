#ifndef COG_H_
#define COG_H_

class cog {
	protected:
		const int type;
		int readcount;
	public:
		cog (int t);
		cog (int t, int r);
		const int getType();
		int getReadcount();
		void setReadcount(int x);
};

#endif /* COG_H_ */

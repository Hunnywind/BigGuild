#pragma once
#include "Pooling.h"
using namespace Homura;

class ID
{
	friend CPool<ID>;
public:
	operator int(void)
	{
		return mID;
	}
private:
	ID(void)
	{
		mID = mIDCount++;
	}
private:
	static int mIDCount;
	int mID;
};


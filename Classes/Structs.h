#pragma once
#include "Enum.h"
struct Properties
{
	int level;
	int exp;
	int expToLevelUp;
	int activity;
	std::string name;
	int type1;
	int type2;

	int skill1;
	int skill2;
	int skill3;

	int feature1;
	int feature2;
	int feature3;

	Properties() : level(1), exp(0), expToLevelUp(0), activity(0), name("MISSINGNO"),
		type1(TypeList::TYPE_DEFAULT), type2(TypeList::TYPE_DEFAULT),
		skill1(0), skill2(0), skill3(0),
		feature1(0), feature2(0), feature3(0){}
};

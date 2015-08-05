#pragma once
#include "Enum.h"
#include <vector>

struct Ability
{
	int skill1;
	int skill2;
	int skill3;

	int feature1;
	int feature2;
	int feature3;

	Ability() : skill1(0), skill2(0), skill3(0),
		feature1(0), feature2(0), feature3(0)
	{}
};

struct BasicInfo
{
	int dex;
	int level;
	int exp;
	int expToLevelUp;
	int grade;

	std::string name;
	TypeList type1;
	TypeList type2;

	BasicInfo() : dex(0),level(0), exp(0), expToLevelUp(0), grade(1),
		name("MISSINGNO"), type1(TypeList::TYPE_DEFAULT), type2(TypeList::TYPE_DEFAULT)
	{ }
};

struct Mission
{
	int id;
	MissionCondition preCondition;

	int rewardExp;
	int rewardRes;
	TypeList rewardEggType;
	
	int requirementRes;
	int memberMaxCount;
	int gradeMax;
	int gradeMin;

	std::string name;

	float time;
	float resTime;

	std::vector<int> MemberID;

	Mission() : id(0) ,preCondition(MissionCondition::STAN_BY),
		rewardExp(0), rewardRes(0), rewardEggType(TypeList::TYPE_DEFAULT),
		requirementRes(0), memberMaxCount(0), gradeMax(0), gradeMin(0),
		name("Hard Mission"), time(0), resTime(0)
	{ }

	bool operator==(const Mission& _rhs)
	{
		if (this->id == _rhs.id)
			return true;
		else
			return false;
	}
};
#pragma once
#include "Enum.h"


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
	int level;
	int exp;
	int expToLevelUp;

	std::string name;
	TypeList type1;
	TypeList type2;

	BasicInfo() : level(0), exp(0), expToLevelUp(0),
		name("MISSINGNO"), type1(TypeList::TYPE_DEFAULT), type2(TypeList::TYPE_DEFAULT)
	{ }
};

struct Mission
{
	int id;

	MissionCondition preCondition;
	int level;
	int rewardExp;
	int rewardRes;
	TypeList rewardEggType;
	
	std::string name;
	float time;
	float resTime;
	int requirementRes;

	int Enemy[5];
	int EnemySkillNumber[5];

	Mission() : id(0) ,preCondition(MissionCondition::STAN_BY),
		level(0), rewardExp(0), rewardRes(0), rewardEggType(TypeList::TYPE_DEFAULT),
		name("Hard Mission"), time(0), resTime(0), requirementRes(0)
	{ }

	bool operator==(const Mission& _rhs)
	{
		if (this->id == _rhs.id)
			return true;
		else
			return false;
	}
};
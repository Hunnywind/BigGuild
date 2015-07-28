#include "MissionManager.h"
#include "Member.h"
#include "Enum.h"
#include "Structs.h"
#include "ui/CocosGUI.h"



MissionManager::MissionManager()
{
	this->init();
}
MissionManager* MissionManager::getInstance()
{
	static MissionManager* instance = NULL;

	if (NULL == instance)
		instance = new MissionManager();

	return instance;
}
bool MissionManager::init()
{
	this->scheduleUpdate();
	this->addMission(0);
	this->addMission(0);
	this->addMission(0);
	this->addMission(0);
	this->addMission(0);
	this->addMission(0);
	this->addMission(0);
	this->addMission(0);
	return true;
}

void MissionManager::update(float delta)
{
	std::list<Mission>::iterator iter = MissionList.begin();
	for (iter = MissionList.begin(); iter != MissionList.end(); iter++)
	{
		if (MissionCondition::PROGRESS == iter->preCondition)
		{
			iter->resTime -= delta;
			if (0 >= iter->resTime)
			{
				iter->preCondition = MissionCondition::COMPLETION;
			}
		}
	}
}

void MissionManager::addMission(int dex)
{
	// json
	Mission mission;
	for (int i = 0; i < 5; i++)
	{
		mission.Enemy[i] = i;
		mission.EnemySkillNumber[i] = 2;
	}
	MissionList.push_back(mission);
}

Mission MissionManager::getMission(int num)
{
	std::list<Mission>::iterator iter = MissionList.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	return *iter;
}
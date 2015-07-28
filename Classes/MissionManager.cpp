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
	this->addSTANBY(0);
	this->addSTANBY(0);
	this->addSTANBY(0);
	this->addSTANBY(0);
	this->addSTANBY(0);
	this->addSTANBY(0);
	this->addSTANBY(0);
	this->addSTANBY(0);
	return true;
}

void MissionManager::update(float delta)
{
	std::list<Mission>::iterator iter = STANBY_List.begin();
	for (iter = STANBY_List.begin(); iter != STANBY_List.end(); iter++)
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

void MissionManager::addSTANBY(int dex)
{
	// json
	Mission mission;
	for (int i = 0; i < 5; i++)
	{
		mission.Enemy[i] = i;
		mission.EnemySkillNumber[i] = 2;
	}
	STANBY_List.push_back(mission);
}

Mission MissionManager::getSTANBY(int num)
{
	std::list<Mission>::iterator iter = STANBY_List.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	return *iter;
}

Mission MissionManager::getPreSTANBY()
{
	std::list<Mission>::iterator iter = STANBY_List.begin();
	for (int i = 0; i < DetailNum; i++)
	{
		iter++;
	}
	return *iter;
}

void MissionManager::moveToPROGRESS(int num)
{
	std::list<Mission>::iterator iter = STANBY_List.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	PROGRESS_List.push_back(*iter);
	
	std::list<Mission>::iterator findIter = find(STANBY_List.begin(), STANBY_List.end(), *iter);
	STANBY_List.erase(findIter);
}
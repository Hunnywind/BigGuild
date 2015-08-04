#include "MissionManager.h"
#include "Member.h"
#include "Enum.h"
#include "Structs.h"
#include "ui/CocosGUI.h"



MissionManager::MissionManager()
{
	this->init();
	this->retain();
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
	pool.initialize(5000);
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
	if (PROGRESS_List.size() == 0)
		return;

	std::list<Mission>::iterator iter = PROGRESS_List.begin();
	for (iter = PROGRESS_List.begin(); iter != PROGRESS_List.end(); iter++)
	{
		if (MissionCondition::PROGRESS == iter->preCondition)
		{
			iter->resTime -= delta;
			if (0 >= iter->resTime)
			{
				iter->preCondition = MissionCondition::COMPLETION;
				COMPLETE_List.push_back(*iter);

				std::list<Mission>::iterator findIter = find(PROGRESS_List.begin(), PROGRESS_List.end(), *iter);
				PROGRESS_List.erase(findIter);
				break;
			}
		}
	}
}

int MissionManager::getMissionSize(MissionCondition con)
{
	switch (con)
	{
	case MissionCondition::STAN_BY:
		return STANBY_List.size();
	case MissionCondition::PROGRESS:
		return PROGRESS_List.size();
	case MissionCondition::COMPLETION:
		return COMPLETE_List.size();
	}
}

void MissionManager::addSTANBY(int dex)
{
	// json
	Mission mission;

	mission.time = //3600 * RandomHelper::random_int(0, 5)
		+ 60 * RandomHelper::random_int(0, 30);
	mission.resTime = mission.time;
	mission.id = *(pool.newData());
	mission.gradeMax = 5;
	mission.gradeMin = 3;
	STANBY_List.push_back(mission);
}

Mission MissionManager::getMission(MissionCondition con,int num)
{
	std::list<Mission>::iterator iter;
	STANBY_List.begin();
	switch (con)
	{
	case MissionCondition::STAN_BY:
		iter = STANBY_List.begin();
		break;
	case MissionCondition::PROGRESS:
		iter = PROGRESS_List.begin();
		break;
	case MissionCondition::COMPLETION:
		iter = COMPLETE_List.begin();
		break;
	}
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

void MissionManager::moveToPROGRESS()
{
	std::list<Mission>::iterator iter = STANBY_List.begin();
	for (int i = 0; i < DetailNum; i++)
	{
		iter++;
	}
	iter->preCondition = MissionCondition::PROGRESS;
	PROGRESS_List.push_back(*iter);
	
	std::list<Mission>::iterator findIter = find(STANBY_List.begin(), STANBY_List.end(), *iter);
	STANBY_List.erase(findIter);
}

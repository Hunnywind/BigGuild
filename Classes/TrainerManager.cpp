#include "TrainerManager.h"
#include "Trainer.h"
#include "Enum.h"
#include "Structs.h"
#include "ui/CocosGUI.h"


TrainerManager::TrainerManager()
{
	this->init();
}
TrainerManager* TrainerManager::getInstance()
{
	static TrainerManager* instance = NULL;

	if (NULL == instance)
		instance = new TrainerManager();

	return instance;
}
bool TrainerManager::init()
{
	pool.initialize(5000);


	this->initTrainerLayer();

	this->addTrainer(0);

	return true;
}

void TrainerManager::initTrainerLayer()
{
	TrainerLayer = Layer::create();
	TrainerLayer->retain();
}

void TrainerManager::addTrainer(int dex)
{

}


void TrainerManager::changeMode(GameMode mode)
{
	std::list<Trainer*>::iterator iter = TrainerList.begin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int support_y = 0;
	int revision = 0;
	switch (mode)
	{
	case GameMode::MAIN_MODE:
	{
		break;
	}
	case GameMode::MEMBER_MODE:
	{

		
		break;
	}
	case GameMode::DETAIL_MEMBER_MODE:
	{

		break;
	}
	case GameMode::MISSION_MODE:
	{
		break;
	}
	case GameMode::DETAIL_MISSION_MODE:
	{
		break;
	}
	}
}



void TrainerManager::setTrainerMission(int num)
{
	std::list<Trainer*>::iterator iter = TrainerList.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	(*iter)->setMission(MissionCondition::PROGRESS);
}

MissionCondition TrainerManager::getTrainerM_Condition(int num)
{
	std::list<Trainer*>::iterator iter = TrainerList.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	return (*iter)->getM_Condition();
}
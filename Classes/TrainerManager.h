#pragma once

#include "cocos2d.h"
#include <list>
#include "Enum.h"
#include "Structs.h"
#include "Pooling.h"
#include "ID.h"

USING_NS_CC;
class Trainer;


class TrainerManager
{
public:
	~TrainerManager(){}
	static TrainerManager* getInstance();

	void initTrainerLayer();
	Layer* getTrainerLayer() { return TrainerLayer; }

	bool init();
	void addTrainer(int dex);

	void cleanMode(GameMode mode);
	void changeMode(GameMode mode);

	int getTrainerSize() { return TrainerList.size(); }

	void setTrainerMission(int num);

	MissionCondition getTrainerM_Condition(int num);
	std::list<Trainer*> getTrainerList() { return TrainerList; }
private:
	TrainerManager();

	Layer* TrainerLayer;
	std::list<Trainer*> TrainerList;

	CPool<ID> pool;
};

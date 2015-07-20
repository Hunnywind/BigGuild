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
	return true;
}

void MissionManager::addMission(int dex)
{

}
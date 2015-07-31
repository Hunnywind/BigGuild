#include "MainScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "MemberScene.h"
#include "MissionScene.h"
#include "MenuManager.h"
#include "MissionManager.h"

Scene* MainScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();
	this->initLayer();
	this->initMenu();
	this->initMission();
	return true;
}

void MainScene::initLayer()
{
	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer, 0, "LAYER_MENU");

	auto MapLayer = Layer::create();
	MapLayer->addChild(MapManager::getInstance()->getTilemap());
	this->addChild(MapLayer, 0, "LAYER_MAP");

	auto MemberLayer = Layer::create();
	MemberLayer->addChild(GuildMemberManager::getInstance()->getMemberLayer());
	this->addChild(MemberLayer,0,"LAYER_MEMBER");

	auto MissionLayer = Layer::create();
	MissionLayer->addChild(MissionManager::getInstance());
	this->addChild(MissionLayer, 1, "LAYER_MISSION");

}

void MainScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());

}

void MainScene::initMission()
{
	int maxSize = MissionManager::getInstance()->getMissionSize(MissionCondition::PROGRESS);
	if (0 == maxSize)
		return;

	Layer *missionLayer = (Layer*)this->getChildByName("LAYER_MISSION");

	Mission firstMission = MissionManager::getInstance()->getMission(MissionCondition::PROGRESS, 0);
	auto sButton = Sprite::create("res/MissionButton.png");
	sButton->setAnchorPoint(Point(0, 0));
	missionLayer->addChild(sButton);

	auto missionName = Label::createWithSystemFont(firstMission.name, "Thonburi", 24, Size::ZERO,
		TextHAlignment::LEFT);
	missionName->setColor(Color3B(0, 0, 0));
	missionName->setPosition(10, 10);
	missionName->setAnchorPoint(Point(0, 0));
	missionLayer->addChild(missionName, 1);

	int missionRestime = firstMission.resTime;
	int missionResHour10 = 0;
	int missionResHour = 0;
	int missionResMinute10 = 0;
	int missionResMinute = 0;

	missionResHour10 = missionRestime / 36000;
	missionResHour = (missionRestime - missionResHour10 * 36000) / 3600;
	missionResMinute10 = (missionRestime - missionResHour10 * 36000
		- missionResHour * 3600) / 600;
	missionResMinute = (missionRestime - missionResHour10 * 36000
		- missionResHour * 3600 - missionResMinute10 * 600)
		/ 60;

	char l_hour10[5] = { 0 };
	itoa(missionResHour10, l_hour10, 10);

	char l_hour[5] = { 0 };
	itoa(missionResHour, l_hour, 10);

	char l_middle[10] = " : ";

	char l_minute10[5] = { 0 };
	itoa(missionResMinute10, l_minute10, 10);

	char l_minute[5] = { 0 };
	itoa(missionResMinute, l_minute, 10);

	strcat(l_hour10, l_hour);
	strcat(l_minute10, l_minute);
	strcat(l_middle, l_minute10);


	auto label_hour = Label::createWithSystemFont(l_hour10, "Thonburi", 24);
	label_hour->setColor(Color3B(0, 0, 0));
	label_hour->setPosition(200, 20);

	auto label_minute = Label::createWithSystemFont(l_middle, "Thonburi", 24);
	label_minute->setColor(Color3B(0, 0, 0));
	label_minute->setPosition(240, 20);


	missionLayer->addChild(label_hour, 1, "TIME_HOUR");
	missionLayer->addChild(label_minute, 1, "TIME_MINUTE");
}

void MainScene::update(float delta)
{
	int maxSize = MissionManager::getInstance()->getMissionSize(MissionCondition::PROGRESS);
	if (0 == maxSize)
	{
		return;
	}

	Mission firstMission = MissionManager::getInstance()->getMission(MissionCondition::PROGRESS, 0);

	int missionRestime = firstMission.resTime;
	int missionResHour10 = 0;
	int missionResHour = 0;
	int missionResMinute10 = 0;
	int missionResMinute = 0;

	missionResHour10 = missionRestime / 36000;
	missionResHour = (missionRestime - missionResHour10 * 36000) / 3600;
	missionResMinute10 = (missionRestime - missionResHour10 * 36000
		- missionResHour * 3600) / 600;
	missionResMinute = (missionRestime - missionResHour10 * 36000
		- missionResHour * 3600 - missionResMinute10 * 600)
		/ 60;

	char l_hour10[5] = { 0 };
	itoa(missionResHour10, l_hour10, 10);

	char l_hour[5] = { 0 };
	itoa(missionResHour, l_hour, 10);

	char l_middle[10] = " : ";

	char l_minute10[5] = { 0 };
	itoa(missionResMinute10, l_minute10, 10);

	char l_minute[5] = { 0 };
	itoa(missionResMinute, l_minute, 10);

	strcat(l_hour10, l_hour);
	strcat(l_minute10, l_minute);
	strcat(l_middle, l_minute10);

	dynamic_cast<Label*>(this->getChildByName("LAYER_MISSION")->getChildByName("TIME_HOUR"))
		->setString(l_hour10);
	dynamic_cast<Label*>(this->getChildByName("LAYER_MISSION")->getChildByName("TIME_MINUTE"))
		->setString(l_middle);
}

void MainScene::gameCallback(Ref *sender)
{
	//auto item = (MenuItem*)sender;

	//this->getChildByName("LAYER_MEMBER")->removeChild(GuildMemberManager::getInstance()->getMemberLayer(), false);
	//this->getChildByName("LAYER_MAP")->removeChild(MapManager::getInstance()->getTilemap(), false);
	//
	//if ("MISSION_FUNCTION" == item->getName())
	//{
	//	GuildMemberManager::getInstance()->rememberPosition();
	//	GuildMemberManager::getInstance()->changeMode(GameMode::MISSION_MODE);
	//	Director::getInstance()->replaceScene(MissionScene::createScene());
	//}
	//if ("MEMBER_FUNCTION" == item->getName())
	//{
	//	GuildMemberManager::getInstance()->rememberPosition();
	//	GuildMemberManager::getInstance()->changeMode(GameMode::MEMBER_MODE);
	//	Director::getInstance()->replaceScene(MemberScene::createScene());
	//}
}
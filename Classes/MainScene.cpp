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

	Mission firstMission = MissionManager::getInstance()->getMission(MissionCondition::PROGRESS, 0);
	auto sButton = Sprite::create("res/MissionButton.png");
	sButton->setAnchorPoint(Point(0, 0));
	this->getChildByName("LAYER_MISSION")->addChild(sButton);

	auto missionName = Label::createWithSystemFont(firstMission.name, "Thonburi", 24, Size::ZERO,
		TextHAlignment::LEFT);
	missionName->setColor(Color3B(0, 0, 0));
	missionName->setPosition(10, 10);
	missionName->setAnchorPoint(Point(0, 0));
	this->getChildByName("LAYER_MISSION")->addChild(missionName,1);

	int missionRestime = firstMission.resTime;
	int missionResHour;
	int missionResMinute;

	missionResHour = (missionRestime / 3600);
	missionRestime = (missionRestime % 3600);

	missionResMinute = (missionRestime / 60);
	missionRestime = (missionResMinute % 60);

	char time[20];
	sprintf(time, "%02d : %02d", missionResHour, missionResMinute);

	Label *label_time = Label::createWithSystemFont(time, "Thonburi", 24);
	label_time->setColor(Color3B(0, 0, 0));
	label_time->setPosition(220.0f, 20.0f);

	this->getChildByName("LAYER_MISSION")->addChild(label_time, 1, "TIME");
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
	int missionResHour;
	int missionResMinute;

	missionResHour = (missionRestime / 3600);
	missionRestime = (missionRestime % 3600);

	missionResMinute = (missionRestime / 60);
	missionRestime = (missionResMinute % 60);

	char time[20];
	sprintf(time, "%02d : %02d", missionResHour, missionResMinute);

	Label *label_time = (Label*)this->getChildByName("LAYER_MISSION")->getChildByName("TIME");
	label_time->setString(time);
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
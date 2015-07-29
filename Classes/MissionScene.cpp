#include "MissionScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "Structs.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "DetailScene.h"
#include "MissionManager.h"
#include "MenuManager.h"
#include "MissionDetailScene.h"

Scene* MissionScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MissionScene::create();
	scene->addChild(layer);

	return scene;
}

bool MissionScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	this->initLayer();
	this->initMenu();
	this->initButton();
	return true;
}

void MissionScene::initLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer, 0, "LAYER_MENU");

	ui::ScrollView *MissionScroll = ui::ScrollView::create();
	MissionScroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	MissionScroll->setAnchorPoint(Point(0, 0));
	MissionScroll->setContentSize(Size(480, 280));
	MissionScroll->setBounceEnabled(true);
	MissionScroll->setInnerContainerSize(Size(480, MissionManager::getInstance()->getSTANBYSize()
		* 40));
	this->addChild(MissionScroll, 0, "MISSION_SCROLLVIEW");



}

void MissionScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());
}

void MissionScene::initButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int MemberNum = 10;
	int MissionNum = MissionManager::getInstance()->getSTANBYSize();
	int revision = 0;
	/*
	for (int i = 0; i < MissionNum; i++)
	{
		auto menuitem = ui::Button::create("res/MissionButton.png");
		menuitem->addTouchEventListener(CC_CALLBACK_2(MissionScene::buttonCallback, this));
		menuitem->setAnchorPoint(Point(0, 0));
		menuitem->setTag(ButtonList.size());
		menuitem->setName("DETAIL_FUNCTION");
		this->getChildByName("SCROLLVIEW")->addChild(menuitem);
		if (4 > MissionNum)
		{
			revision = 4 - MissionNum;
		}
		menuitem->setPositionY(MissionNum
			* 40 + visibleSize.height / 2 - 40 * i - 40 + revision * 40);
		ButtonList.push_back(menuitem);

		auto label = Label::createWithSystemFont("Lv", "Thonburi", 24);
		CCLOG("x:%f, y:%f", label->getAnchorPoint().x, label->getAnchorPoint().y);
		label->setColor(Color3B(0, 0, 0));
		label->setPosition(64.0f, 16.0f);
		menuitem->addChild(label,1);

		BasicInfo Info = GuildMemberManager::getInstance()->getBasicInfo(i);

		char cLevel[5] = { 0 };
		itoa(Info.level, cLevel, 10);
		auto level = Label::create(cLevel, "Thonburi", 24);
		level->setColor(Color3B(0, 0, 0));
		level->setPosition(90.0f, 16.0f);
		menuitem->addChild(level, 1);

		auto name = Label::create(Info.name, "Thonburi", 24);
		name->setColor(Color3B(0, 0, 0));
		name->setPosition(180.0f, 16.0f);
		menuitem->addChild(name, 1);

		auto type1 = Sprite::createWithSpriteFrameName(
			GuildMemberManager::getInstance()->getTypeFilename(Info.type1));
		type1->setScale(1.4f, 1.4f);
		type1->setPosition(280.0f, 18.0f);
		menuitem->addChild(type1, 1);
		
		if (TypeList::TYPE_DEFAULT == Info.type2)
			continue;

		auto type2 = Sprite::createWithSpriteFrameName(
			GuildMemberManager::getInstance()->getTypeFilename(Info.type2));
		type2->setScale(1.4f, 1.4f);
		type2->setPosition(360.0f, 18.0f);
		menuitem->addChild(type2, 1);
	}
	*/


	int hour10 = 0;
	int hour = 0;
	int minute10 = 0;
	int minute = 0;
	int sec = 0;

	for (int i = 0; i < MissionNum; i++)
	{
		Mission mission = MissionManager::getInstance()->getSTANBY(i);

		auto menuitem = ui::Button::create("res/MissionButton.png");
		menuitem->addTouchEventListener(CC_CALLBACK_2(MissionScene::MissionButtonCallback, this));
		menuitem->setAnchorPoint(Point(0, 0));
		menuitem->setTag(MissionButtonList.size());
		menuitem->setName("MISSION_FUNCTION");
		this->getChildByName("MISSION_SCROLLVIEW")->addChild(menuitem);

		if (8 > MissionNum)
		{
			revision = 7 - MissionNum;
		}

		menuitem->setPositionY(MissionNum
			* 40 - 40 * i - 40 + revision * 40);
		MissionButtonList.push_back(menuitem);

		auto missionName = Label::createWithSystemFont(mission.name, "Thonburi", 24, Size::ZERO,
			TextHAlignment::LEFT);
		missionName->setColor(Color3B(0, 0, 0));
		missionName->setPosition(110, 20);
		menuitem->addChild(missionName);
		
		auto stimer = Sprite::create("res/ic_time.png");
		stimer->setAnchorPoint(Point(0, 0));
		menuitem->addChild(stimer);
		stimer->setPosition(Point(350, 5));

		// time setting
		hour10 = 0;
		hour = 0;
		minute10 = 0;
		minute = 0;
		sec = mission.time;

		while (36000 <= sec)
		{
			hour10++;
			sec -= 36000;
		}
		while (3600 <= sec)
		{
			hour++;
			sec -= 3600;
		}
		while (600 <= sec)
		{
			minute10++;
			sec -= 600;
		}
		while (60 <= sec)
		{
			minute++;
			sec -= 60;
		}

		char l_hour10[5] = { 0 };
		itoa(hour10, l_hour10, 10);

		char l_hour[5] = { 0 };
		itoa(hour, l_hour, 10);

		char l_middle[10] = " : ";

		char l_minute10[5] = { 0 };
		itoa(minute10, l_minute10, 10);

		char l_minute[5] = { 0 };
		itoa(minute, l_minute, 10);

		strcat(l_hour10, l_minute);
		strcat(l_minute10, l_minute);
		strcat(l_middle, l_minute10);


		auto label_hour = Label::createWithSystemFont(l_hour10, "Thonburi", 24);
		label_hour->setColor(Color3B(0, 0, 0));
		label_hour->setPosition(400, 20);
		
		auto label_minute = Label::createWithSystemFont(l_middle, "Thonburi", 24);
		label_minute->setColor(Color3B(0, 0, 0));
		label_minute->setPosition(440, 20);
		
		menuitem->addChild(label_hour);
		menuitem->addChild(label_minute);
	}
}


void MissionScene::MissionButtonCallback(Ref *sender, ui::Widget::TouchEventType type)
{
	auto item = (ui::Button*)sender;
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:

		break;

	case ui::Widget::TouchEventType::MOVED:
		break;

	case ui::Widget::TouchEventType::ENDED:
		this->removeChildByName("LAYER_MENU", false);
		GuildMemberManager::getInstance()->changeMode(GameMode::DETAIL_MISSION_MODE);
		MissionManager::getInstance()->setDetailNum(item->getTag());
		Director::getInstance()->replaceScene(MissionDetailScene::createScene());
		break;

	case ui::Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}

void MissionScene::gameCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;

	if ("MAIN_FUNCTION" == item->getName())
	{
		GuildMemberManager::getInstance()->changeMode(GameMode::MAIN_MODE);
		Director::getInstance()->replaceScene(MainScene::createScene());
	}

}
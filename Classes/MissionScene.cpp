#include "MissionScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "Structs.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "DetailScene.h"
#include "MissionManager.h"
#include "MenuManager.h"

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
	MissionScroll->setInnerContainerSize(Size(480, MissionManager::getInstance()->getMissionSize()
		* 40));
	this->addChild(MissionScroll, 0, "MISSION_SCROLLVIEW");

	auto RewardLayer = Layer::create();
	this->addChild(RewardLayer, 0, "LAYER_REWARD");


}

void MissionScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());
	/*auto item_0 = MenuItemImage::create("res/MainMenuButton.png", "res/MainMenuButton.png",
		CC_CALLBACK_1(MissionScene::gameCallback, this));
	auto item_1 = MenuItemImage::create("res/MissionMenuButton.png", "res/MissionMenuButton.png",
		CC_CALLBACK_1(MissionScene::gameCallback, this));
	auto item_2 = MenuItemImage::create("res/StructMenuButton.png", "res/StructMenuButton.png",
		CC_CALLBACK_1(MissionScene::gameCallback, this));
	auto item_3 = MenuItemImage::create("res/MemberMenuButton.png", "res/MemberMenuButton.png",
		CC_CALLBACK_1(MissionScene::gameCallback, this));
	auto item_4 = MenuItemImage::create("res/Resource.png", "res/Resource.png",
		CC_CALLBACK_1(MissionScene::gameCallback, this));

	item_0->setName("MAIN_FUNCTION");
	item_2->setName("STRUCT_FUNCTION");
	item_3->setName("MEMBER_FUNCTION");


	

	auto graybar = Sprite::create("res/GrayBar.png");
	graybar->setAnchorPoint(Point(0, 0));
	graybar->setPositionY(280.0f);
	this->getChildByName("LAYER_MENU")->addChild(graybar, 0);

	auto menu = Menu::create(item_0, item_1, item_2, item_3, item_4, NULL);
	menu->alignItemsHorizontallyWithPadding(5);
	menu->setPosition(Point(240, 300));

	this->getChildByName("LAYER_MENU")->addChild(menu,1);
	*/
}

void MissionScene::initButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int MemberNum = 10;
	int MissionNum = MissionManager::getInstance()->getMissionSize();
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


	for (int i = 0; i < MissionNum; i++)
	{
		Mission mission = MissionManager::getInstance()->getMission(i);

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

		char LevelLabel[5] = "Lv ";
		char Level[5] = { 0 };
		itoa(mission.level, Level, 10);
		strcat(LevelLabel, Level);
		auto label = Label::createWithSystemFont(LevelLabel, "Thonburi", 24);
		label->setColor(Color3B(0, 0, 0));
		label->setPosition(40,20);
		menuitem->addChild(label);

		auto missionName = Label::createWithSystemFont(mission.name, "Thonburi", 24);
		missionName->setColor(Color3B(0, 0, 0));
		missionName->setPosition(150, 20);
		menuitem->addChild(missionName);
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
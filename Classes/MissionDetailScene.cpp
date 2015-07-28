#include "MissionDetailScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "Structs.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "MemberScene.h"
#include "MissionManager.h"
#include "MenuManager.h"
#include "GuildMemberManager.h"
#include "MissionScene.h"

Scene* MissionDetailScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MissionDetailScene::create();
	scene->addChild(layer);

	return scene;
}

bool MissionDetailScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	this->initLayer();
	this->initMenu();
	this->initDetail();
	this->scheduleUpdate();
	MenuManager::getInstance()->setPreGameMode(GameMode::DETAIL_MISSION_MODE);
	return true;
}

void MissionDetailScene::initLayer()
{
	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer, 0, "LAYER_MENU");


	ui::ScrollView *MemberScroll = ui::ScrollView::create();
	MemberScroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	MemberScroll->setAnchorPoint(Point(0, 0));
	MemberScroll->setContentSize(Size(160, 280));
	MemberScroll->setInnerContainerSize(Size(160, GuildMemberManager::getInstance()->getMemberSize()
		* 40));
	MemberScroll->addChild(GuildMemberManager::getInstance()->getMemberLayer(), 1);
	this->addChild(MemberScroll, 0, "MEMBER_SCROLLVIEW");



	auto MissionLayer = Layer::create();
	this->addChild(MissionLayer, 0, "LAYER_MISSION");
	auto MissionSprite = Sprite::create("res/D_Mission.png");
	MissionSprite->setAnchorPoint(Point(0, 0));
	MissionSprite->setPositionX(160);
	MissionLayer->addChild(MissionSprite);

	auto ok = ui::Button::create("res/OK.png");
	ok->addTouchEventListener(CC_CALLBACK_2(MissionDetailScene::OkCallback, this));
	ok->setAnchorPoint(Point(0, 0));
	MissionLayer->addChild(ok, 1);
	ok->setPosition(Point(285, 50));
}

void MissionDetailScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());
}

void MissionDetailScene::initDetail()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int MemberNum = GuildMemberManager::getInstance()->getMemberSize();
	int revision = 0;
	for (int i = 0; i < MemberNum; i++)
	{
		auto menuitem = ui::Button::create("res/MissionMemberButton.png");
		menuitem->addTouchEventListener(CC_CALLBACK_2(MissionDetailScene::MemberButtonCallback, this));
		menuitem->setAnchorPoint(Point(0, 0));
		menuitem->setTag(MemberButtonList.size());
		menuitem->setName("DETAIL_FUNCTION");
		this->getChildByName("MEMBER_SCROLLVIEW")->addChild(menuitem);
		if (8 > MemberNum)
		{
			revision = 7 - MemberNum;
		}
		menuitem->setPositionY(MemberNum
			* 40 - 40 * i + revision * 40 - 40);
		CCLOG("y: %f", menuitem->getPositionY());
		MemberButtonList.push_back(menuitem);
	}
}

void MissionDetailScene::update(float delta)
{
}

void MissionDetailScene::MemberButtonCallback(Ref *sender, ui::Widget::TouchEventType type)
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

void MissionDetailScene::gameCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;
}

void MissionDetailScene::OkCallback(Ref *sender, ui::Widget::TouchEventType type)
{
	auto item = (ui::Button*)sender;
	int num = item->getTag();

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:

		break;

	case ui::Widget::TouchEventType::MOVED:
		break;

	case ui::Widget::TouchEventType::ENDED:
		MissionManager::getInstance()->moveToPROGRESS(num);
		MenuManager::getInstance()->setPreGameMode(GameMode::DETAIL_MISSION_MODE);
		MenuManager::getInstance()->sceneClean();
		MenuManager::getInstance()->setPreGameMode(GameMode::MISSION_MODE);
		GuildMemberManager::getInstance()->changeMode(GameMode::MISSION_MODE);
		Director::getInstance()->replaceScene(MissionScene::createScene());

		break;

	case ui::Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}
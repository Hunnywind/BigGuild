#include "CompleteMissionScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "Structs.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "DetailScene.h"
#include "MissionManager.h"
#include "MenuManager.h"
#include "MissionDetailScene.h"
#include "Member.h"

Scene* CompleteMissionScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CompleteMissionScene::create();
	scene->addChild(layer);

	return scene;
}

bool CompleteMissionScene::init()
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

void CompleteMissionScene::initLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer, 0, "LAYER_MENU");

	ui::ScrollView *MissionScroll = ui::ScrollView::create();
	MissionScroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	MissionScroll->setAnchorPoint(Point(0, 0));
	MissionScroll->setContentSize(Size(480, 280));
	MissionScroll->setBounceEnabled(true);
	MissionScroll->setInnerContainerSize(Size(480, MissionManager::getInstance()->getMissionSize(MissionCondition::STAN_BY)
		* 40));
	this->addChild(MissionScroll, 0, "MISSION_SCROLLVIEW");

}

void CompleteMissionScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());
}

void CompleteMissionScene::initButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int MemberNum = 10;
	int MissionNum = MissionManager::getInstance()->getMissionSize(MissionCondition::COMPLETION);
	int revision = 0;

	for (int i = 0; i < MissionNum; i++)
	{
		Mission mission = MissionManager::getInstance()->getMission(MissionCondition::COMPLETION,i);

		auto menuitem = ui::Button::create("res/MissionButton.png");
		menuitem->addTouchEventListener(CC_CALLBACK_2(CompleteMissionScene::MissionButtonCallback, this));
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
		
	}
}


void CompleteMissionScene::MissionButtonCallback(Ref *sender, ui::Widget::TouchEventType type)
{
	auto item = (ui::Button*)sender;
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:

		break;

	case ui::Widget::TouchEventType::MOVED:
		break;

	case ui::Widget::TouchEventType::ENDED:
		this->MemberToSTANBY(item->getTag());
		MissionManager::getInstance()->removeMission(MissionCondition::COMPLETION,item->getTag());
		/*
		this->removeChildByName("LAYER_MENU", false);
		GuildMemberManager::getInstance()->changeMode(GameMode::DETAIL_MISSION_MODE);
		MissionManager::getInstance()->setDetailNum(item->getTag());
		Director::getInstance()->replaceScene(MissionDetailScene::createScene());
		*/
		break;

	case ui::Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}

void CompleteMissionScene::gameCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;

	if ("MAIN_FUNCTION" == item->getName())
	{
		GuildMemberManager::getInstance()->changeMode(GameMode::MAIN_MODE);
		Director::getInstance()->replaceScene(MainScene::createScene());
	}

}

void CompleteMissionScene::MemberToSTANBY(int num)
{
	Mission mission = MissionManager::getInstance()->getMission(MissionCondition::COMPLETION, num);
	std::list<Member*>::iterator finditer;
	auto FindMember = Member::create();
	std::list<Member*> findlist = GuildMemberManager::getInstance()->getMemberList();

	int size = mission.MemberID.size();
	int id = 0;
	

	for (int i = 0; i < size; i++)
	{
		id = mission.MemberID.back();
		mission.MemberID.pop_back();
		FindMember->setID(id);

		auto find_mission = [&FindMember](Member* member)
		{
			return FindMember->getID() == member->getID();
		};
		finditer = find_if(findlist.begin(), findlist.end(), find_mission);
		
		(*finditer)->setMission(MissionCondition::STAN_BY);
	}

}

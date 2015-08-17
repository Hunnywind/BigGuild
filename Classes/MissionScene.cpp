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

MissionScene::MissionScene()
	: isWAIT(true)
{
}

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
	this->changeTap();
	this->initMenu();
	this->initButton();
	return true;
}

void MissionScene::initLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer, 0, "LAYER_MENU");
	
	auto MissionShapeLayer = Layer::create();
	this->addChild(MissionShapeLayer, 0, "LAYER_SHAPE");

	ui::ScrollView *MissionScroll = ui::ScrollView::create();
	MissionScroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	MissionScroll->setAnchorPoint(Point(0, 0));
	MissionScroll->setContentSize(Size(550, 830 + 48));
	MissionScroll->setPosition(Point(Director::getInstance()->getWinSize().width * 0.5
		- 550 * 0.5 + 48
		, MenuManager::getInstance()->getMenuLayer()
		->getChildByName("BAR")->getContentSize().height
		+ MenuManager::getInstance()->getMenuLayer()
		->getChildByName("BAR")->getPositionY()
		+ 165 - 48
		));
	MissionScroll->setInnerContainerSize
		(Size(550, MissionManager::getInstance()->getMissionSize(MissionCondition::STAN_BY)
		* 160 + MissionManager::getInstance()->getMissionSize(MissionCondition::STAN_BY)
		* 160
		+ 48));
	this->addChild(MissionScroll, 1, "MISSION_SCROLLVIEW");

}

void MissionScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());
}

void MissionScene::initButton()
{

	this->getChildByName("MISSION_SCROLLVIEW")
		->removeAllChildrenWithCleanup(true);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int MemberNum = 10;
	int MissionNum = MissionManager::getInstance()->getMissionSize(MissionCondition::STAN_BY);
	int ProgressNum = MissionManager::getInstance()->getMissionSize(MissionCondition::PROGRESS);
	int CompleteNum = MissionManager::getInstance()->getMissionSize(MissionCondition::COMPLETION);
	int revision = 0;

	int hour10 = 0;
	int hour = 0;
	int minute10 = 0;
	int minute = 0;
	int sec = 0;

	if (isWAIT)
	{
		// scroll size set
		dynamic_cast<cocos2d::ui::ScrollView*>(this->getChildByName("MISSION_SCROLLVIEW"))
			->setInnerContainerSize
			(Size(550,
			MissionManager::getInstance()->getMissionSize(MissionCondition::STAN_BY)
			* 160
			+ 48));

		for (int i = 0; i < MissionNum; i++)
		{
			Mission mission = MissionManager::getInstance()->getMission(MissionCondition::STAN_BY, i);

			auto menuitem = ui::Button::create("UI/Mission/mission_base.png");
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
				* 160 - 160 * i - 160 + revision * 160 + 48);
			MissionButtonList.push_back(menuitem);


			auto reward = Sprite::create("UI/Mission/reward.png");
			reward->setAnchorPoint(Point(0, 0));
			reward->setPosition(menuitem->getSize().width - reward->getContentSize().width
				- 20, 0);
			menuitem->addChild(reward, 1);


			auto foes = //Sprite::create("UI/Mission/058.png");
				Sprite::createWithSpriteFrameName("Pokemon_58.png");
			foes->setAnchorPoint(Point(0, 0));
			foes->setPosition(-20, 6);
			foes->setScale(0.8);
			menuitem->addChild(foes, 1);
			//auto missionName = Label::createWithSystemFont(mission.name, "Thonburi", 24, Size::ZERO,
			//	TextHAlignment::LEFT);
			//missionName->setColor(Color3B(0, 0, 0));
			//missionName->setPosition(110, 20);
			//menuitem->addChild(missionName);
			//
			auto stimer = Sprite::create("res/ic_time.png");
			stimer->setAnchorPoint(Point(0, 0));
			menuitem->addChild(stimer);
			stimer->setPosition(Point(250, 5));

			// time setting
			int sec = mission.time;
			int hour;
			int minute;

			hour = (sec / 3600);
			sec = (sec % 3600);

			minute = (sec / 60);
			sec = (sec % 60);

			char time[20];
			sprintf(time, "%02d : %02d", hour, minute);

			Label *label_time = Label::createWithSystemFont(time, "Thonburi", 24);
			label_time->setColor(Color3B(0, 0, 0));
			label_time->setPosition(330.0f, 20.0f);

			menuitem->addChild(label_time);
		}
	}
	else // progress, completion
	{
		// scroll size set
		dynamic_cast<cocos2d::ui::ScrollView*>(this->getChildByName("MISSION_SCROLLVIEW"))
			->setInnerContainerSize
			(Size(550,
			MissionManager::getInstance()->getMissionSize(MissionCondition::STAN_BY)
			* 160 + MissionManager::getInstance()->getMissionSize(MissionCondition::COMPLETION)
			* 160 + MissionManager::getInstance()->getMissionSize(MissionCondition::PROGRESS)
			* 160
			+ 48));


		for (int i = 0; i < CompleteNum; i++)
		{
			Mission mission = MissionManager::getInstance()->getMission(MissionCondition::COMPLETION, i);

			auto menuitem = ui::Button::create("UI/Mission/mission_base.png");
			menuitem->addTouchEventListener(CC_CALLBACK_2(MissionScene::MissionButtonCallback, this));
			menuitem->setAnchorPoint(Point(0, 0));
			menuitem->setTag(MissionButtonList.size());
			menuitem->setName("COMPLETE_FUNCTION");
			this->getChildByName("MISSION_SCROLLVIEW")->addChild(menuitem);

			if (8 > CompleteNum + ProgressNum)
			{
				revision = 7 - CompleteNum - ProgressNum;
			}

			menuitem->setPositionY(MissionNum
				* 160 - 160 * i - 160 + revision * 160 + 48);
			MissionButtonList.push_back(menuitem);


			auto reward = Sprite::create("UI/Mission/reward.png");
			reward->setAnchorPoint(Point(0, 0));
			reward->setPosition(menuitem->getSize().width - reward->getContentSize().width
				- 20, 0);
			menuitem->addChild(reward, 1);


			auto foes = //Sprite::create("UI/Mission/058.png");
				Sprite::createWithSpriteFrameName("Pokemon_58.png");
			foes->setAnchorPoint(Point(0, 0));
			foes->setPosition(-20, 6);
			foes->setScale(0.8);
			menuitem->addChild(foes, 1);
			//auto missionName = Label::createWithSystemFont(mission.name, "Thonburi", 24, Size::ZERO,
			//	TextHAlignment::LEFT);
			//missionName->setColor(Color3B(0, 0, 0));
			//missionName->setPosition(110, 20);
			//menuitem->addChild(missionName);
			//
			auto stimer = Sprite::create("res/ic_time.png");
			stimer->setAnchorPoint(Point(0, 0));
			menuitem->addChild(stimer);
			stimer->setPosition(Point(250, 5));

			// time setting
			int sec = mission.time;
			int hour;
			int minute;

			hour = (sec / 3600);
			sec = (sec % 3600);

			minute = (sec / 60);
			sec = (sec % 60);

			char time[20];
			sprintf(time, "%02d : %02d", hour, minute);

			Label *label_time = Label::createWithSystemFont(time, "Thonburi", 24);
			label_time->setColor(Color3B(0, 0, 0));
			label_time->setPosition(330.0f, 20.0f);

			menuitem->addChild(label_time);
		}

		// Progress Mission setting
		for (int i = 0; i < ProgressNum; i++)
		{
			Mission mission = MissionManager::getInstance()->getMission(MissionCondition::COMPLETION, i);

			auto menuitem = ui::Button::create("UI/Mission/mission_base.png");
			menuitem->addTouchEventListener(CC_CALLBACK_2(MissionScene::MissionButtonCallback, this));
			menuitem->setAnchorPoint(Point(0, 0));
			menuitem->setTag(MissionButtonList.size());
			menuitem->setName("COMPLETE_FUNCTION");
			this->getChildByName("MISSION_SCROLLVIEW")->addChild(menuitem);

			menuitem->setPositionY(ProgressNum
				* 160 - 160 * i - 160 - CompleteNum * 160
				+ revision * 160 + 48);
			MissionButtonList.push_back(menuitem);


			auto reward = Sprite::create("UI/Mission/reward.png");
			reward->setAnchorPoint(Point(0, 0));
			reward->setPosition(menuitem->getSize().width - reward->getContentSize().width
				- 20, 0);
			menuitem->addChild(reward, 1);


			auto foes = //Sprite::create("UI/Mission/058.png");
				Sprite::createWithSpriteFrameName("Pokemon_58.png");
			foes->setAnchorPoint(Point(0, 0));
			foes->setPosition(-20, 6);
			foes->setScale(0.8);
			menuitem->addChild(foes, 1);
			//auto missionName = Label::createWithSystemFont(mission.name, "Thonburi", 24, Size::ZERO,
			//	TextHAlignment::LEFT);
			//missionName->setColor(Color3B(0, 0, 0));
			//missionName->setPosition(110, 20);
			//menuitem->addChild(missionName);
			//
			auto stimer = Sprite::create("res/ic_time.png");
			stimer->setAnchorPoint(Point(0, 0));
			menuitem->addChild(stimer);
			stimer->setPosition(Point(250, 5));

			// time setting
			int sec = mission.time;
			int hour;
			int minute;

			hour = (sec / 3600);
			sec = (sec % 3600);

			minute = (sec / 60);
			sec = (sec % 60);

			char time[20];
			sprintf(time, "%02d : %02d", hour, minute);

			Label *label_time = Label::createWithSystemFont(time, "Thonburi", 24);
			label_time->setColor(Color3B(0, 0, 0));
			label_time->setPosition(330.0f, 20.0f);

			menuitem->addChild(label_time);
		}
	}
}


void MissionScene::MissionButtonCallback(Ref *sender, ui::Widget::TouchEventType type)
{
	auto item = (ui::Button*)sender;
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		//this->removeChildByName("LAYER_MENU", false);
		//GuildMemberManager::getInstance()->changeMode(GameMode::DETAIL_MISSION_MODE);
		//MissionManager::getInstance()->setDetailNum(item->getTag());
		//Director::getInstance()->replaceScene(MissionDetailScene::createScene());
		break;
	}
}

void MissionScene::BasicCallback(Ref *sender, ui::Widget::TouchEventType type)
{
	auto item = (ui::Button*)sender;
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		if ("CHANGE_TAP" == item->getName())
		{
			if (isWAIT) isWAIT = false;
			else isWAIT = true;
			this->changeTap();
			this->initButton();
		}
		//this->removeChildByName("LAYER_MENU", false);
		//GuildMemberManager::getInstance()->changeMode(GameMode::DETAIL_MISSION_MODE);
		//MissionManager::getInstance()->setDetailNum(item->getTag());
		//Director::getInstance()->replaceScene(MissionDetailScene::createScene());
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

void MissionScene::changeTap()
{
	this->getChildByName("LAYER_SHAPE")->removeAllChildrenWithCleanup(true);

	if (isWAIT)
	{
		auto wait = Sprite::create("UI/Mission/base1.png");
		wait->setAnchorPoint(Point(0, 0));
		wait->setPositionX(Director::getInstance()->getWinSize().width * 0.5
			- wait->getContentSize().width * 0.5);
		wait->setPositionY(MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getContentSize().height
			+ MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getPositionY());
		this->getChildByName("LAYER_SHAPE")->addChild(wait);

		auto button = ui::Button::create("UI/empty1.png");
		button->setAnchorPoint(Point(0, 0));
		button->setName("CHANGE_TAP");
		button->setPositionX(170);
		button->setPositionY(MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getContentSize().height
			+ MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getPositionY());
		this->getChildByName("LAYER_SHAPE")->addChild(button);
		button->addTouchEventListener(CC_CALLBACK_2(MissionScene::BasicCallback, this));
	}
	else
	{
		auto wait = Sprite::create("UI/Mission/base2.png");
		wait->setAnchorPoint(Point(0, 0));
		wait->setPositionX(Director::getInstance()->getWinSize().width * 0.5
			- wait->getContentSize().width * 0.5);
		wait->setPositionY(MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getContentSize().height
			+ MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getPositionY());
		this->getChildByName("LAYER_SHAPE")->addChild(wait);

		auto button = ui::Button::create("UI/empty1.png");
		button->setAnchorPoint(Point(0, 0));
		button->setName("CHANGE_TAP");
		button->setPositionX(170);
		button->setPositionY(MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getContentSize().height
			+ MenuManager::getInstance()->getMenuLayer()
			->getChildByName("BAR")->getPositionY());
		this->getChildByName("LAYER_SHAPE")->addChild(button);
		button->addTouchEventListener(CC_CALLBACK_2(MissionScene::BasicCallback, this));
	}
}
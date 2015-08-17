#include "MenuManager.h"
#include "Member.h"
#include "Enum.h"
#include "Structs.h"
#include "ui/CocosGUI.h"

#include "MapManager.h"
#include "GuildMemberManager.h"
#include "MainScene.h"
#include "MissionScene.h"
#include "MemberScene.h"
#include "MissionManager.h"
#include "CompleteMissionScene.h"

MenuManager::MenuManager()
	: Menuset(NULL), Mode(false)
{
	this->init();
	preGameMode = GameMode::MAIN_MODE;
}
MenuManager* MenuManager::getInstance()
{
	static MenuManager* instance = NULL;

	if (NULL == instance)
		instance = new MenuManager();

	return instance;
}
bool MenuManager::init()
{
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("UI/Menu.plist");

	Menuset = Layer::create();
	Menuset->retain();
	Menuset->setAnchorPoint(Point(0, 0));

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Init Switch
	auto switchClose = cocos2d::ui::Button::create("close.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	switchClose->setAnchorPoint(Point(0.5f, 0.5f));
	switchClose->setName("SWITCH_CLOSE");
	switchClose->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	Menuset->addChild(switchClose, 1);
	switchClose->setPositionX(visibleSize.width - (switchClose->getSize().width / 2.0f));
	switchClose->setPositionY(switchClose->getSize().height / 2.0f);

	auto switchOpen = cocos2d::ui::Button::create("open1.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	switchOpen->setAnchorPoint(Point(0.5f, 0.5f));
	switchOpen->setName("SWITCH_OPEN");
	switchOpen->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	Menuset->addChild(switchOpen, 1);
	switchOpen->setPositionX(visibleSize.width - (switchOpen->getSize().width / 2.0f));
	switchOpen->setPositionY(switchOpen->getSize().height / 2.0f);
	switchOpen->setVisible(false);
	switchOpen->setEnabled(false);

	// Init ButtonBar
	auto buttonbar = Sprite::createWithSpriteFrameName("open3.png");
	buttonbar->setAnchorPoint(Point(1.0f, 0.0f));
	Menuset->addChild(buttonbar, 0, "BAR");
	buttonbar->setPosition(switchOpen->getPositionX(), (switchOpen->getSize().height / 2.0f) - (buttonbar->getContentSize().height / 2.0f));
	buttonbar->setScale(0.0f, 1.0f);

	// Init Button
	Size buttonBarSize = buttonbar->getContentSize();
	Vec2 buttonBarPosition = buttonbar->getPosition();

	auto buttonMission = cocos2d::ui::Button::create("1_mission.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	buttonMission->setAnchorPoint(Point(0, 0));
	buttonMission->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	buttonbar->addChild(buttonMission, 1, "MISSION_FUNCTION");
	buttonMission->setPosition(Vec2(buttonBarSize.width * 0.1f, buttonMission->getSize().height * 0.1f));

	auto buttonTown = cocos2d::ui::Button::create("2_town.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	buttonTown->setAnchorPoint(Point(0, 0));
	buttonTown->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	buttonbar->addChild(buttonTown, 1, "MAIN_FUNCTION");
	buttonTown->setPosition(Vec2(buttonBarSize.width * 0.25f, buttonMission->getSize().height * 0.06f));

	auto buttonTrainer = cocos2d::ui::Button::create("3_trainer.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	buttonTrainer->setAnchorPoint(Point(0, 0));
	buttonTrainer->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	buttonbar->addChild(buttonTrainer, 1, "TRAINER_FUNCTION");
	buttonTrainer->setPosition(Vec2(buttonBarSize.width * 0.4f, buttonMission->getSize().height * 0.08f));

	auto buttonMember = cocos2d::ui::Button::create("4_member.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	buttonMember->setAnchorPoint(Point(0, 0));
	buttonMember->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	buttonbar->addChild(buttonMember, 1, "MEMBER_FUNCTION");
	buttonMember->setPosition(Vec2(buttonBarSize.width * 0.56f, buttonMission->getSize().height * 0.05f));

	auto buttonSystem = cocos2d::ui::Button::create("5_system.png", "", "", cocos2d::ui::Widget::TextureResType::PLIST);
	buttonSystem->setAnchorPoint(Point(0, 0));
	buttonSystem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	buttonbar->addChild(buttonSystem, 1, "SYSTEM_FUNCTION");
	buttonSystem->setPosition(Vec2(buttonBarSize.width * 0.71f, buttonMission->getSize().height * 0.06f));

	buttonbar->setVisible(false);
	buttonMission->setEnabled(false);
	buttonTown->setEnabled(false);
	buttonTrainer->setEnabled(false);
	buttonMember->setEnabled(false);
	buttonSystem->setEnabled(false);

	//button1->setEnabled(false);
	//button2->setEnabled(false);
	//button3->setEnabled(false);
	//button4->setEnabled(false);
	//button5->setEnabled(false);
	
	//auto graybar = Sprite::create("res/graybar.png");
	//graybar->setAnchorPoint(Point(0, 0));

	//auto mainitem = cocos2d::ui::Button::create("res/MainMenuButton.png");
	//mainitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	//mainitem->setAnchorPoint(Point(0, 0));

	//auto missionitem = ui::Button::create("res/MissionMenuButton.png");
	//missionitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	//missionitem->setAnchorPoint(Point(0, 0));

	//auto structitem = ui::Button::create("res/StructMenuButton.png");
	//structitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	//structitem->setAnchorPoint(Point(0, 0));
	//structitem->setName("STRUCT_FUNCTION");

	//auto memberitem = ui::Button::create("res/MemberMenuButton.png");
	//memberitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	//memberitem->setAnchorPoint(Point(0, 0));

	//Menuset->addChild(graybar, 0);
	//Menuset->addChild(mainitem, 1, "MAIN_FUNCTION");
	//Menuset->addChild(missionitem, 1, "MISSION_FUNCTION");
	//Menuset->addChild(structitem, 1, "STRUCT_FUNCTION");
	//Menuset->addChild(memberitem, 1, "MEMBER_FUNCTION");

	//mainitem->setPosition(Point(5,6));
	//missionitem->setPosition(Point(100,6));
	//structitem->setPosition(Point(195,6));
	//memberitem->setPosition(Point(290,6));

	return true;
}

void MenuManager::buttonCallback(Ref *pSender, ui::Widget::TouchEventType type)
{
	auto item = (ui::Button*)pSender;

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:

		break;

	case ui::Widget::TouchEventType::MOVED:
		break;

	case ui::Widget::TouchEventType::ENDED:
		if (GameMode::MAIN_MODE != preGameMode
			&& "MAIN_FUNCTION" == item->getName())
		{
			this->sceneClean();
			GuildMemberManager::getInstance()->changeMode(GameMode::MAIN_MODE);
			Director::getInstance()->replaceScene(MainScene::createScene());
			preGameMode = GameMode::MAIN_MODE;
		}
		if (GameMode::MEMBER_MODE != preGameMode
			&& "MEMBER_FUNCTION" == item->getName())
		{
			//this->sceneClean();
			//GuildMemberManager::getInstance()->changeMode(GameMode::MEMBER_MODE);
			//Director::getInstance()->replaceScene(MemberScene::createScene());
			//preGameMode = GameMode::MEMBER_MODE;
		}
		if (GameMode::MISSION_MODE != preGameMode
			&& "MISSION_FUNCTION" == item->getName())
		{
			this->sceneClean();
			GuildMemberManager::getInstance()->changeMode(GameMode::MISSION_MODE);
			preGameMode = GameMode::MISSION_MODE;
			if (MissionManager::getInstance()->getMissionSize(MissionCondition::COMPLETION)
				== 0)
			{
				Director::getInstance()->replaceScene(MissionScene::createScene());
			}
			else
			{
				Director::getInstance()->replaceScene(CompleteMissionScene::createScene());
			}
			
		}
		if (item->getName() == "SWITCH_CLOSE" || item->getName() == "SWITCH_OPEN")
		{
			Mode = !Mode;

			this->changeMode();
		}
		break;

	case ui::Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}

void MenuManager::sceneClean()
{
	switch (preGameMode)
	{
	case GameMode::MAIN_MODE:
	{
		GuildMemberManager::getInstance()->rememberPosition();
		GuildMemberManager::getInstance()->getMemberLayer()->removeFromParentAndCleanup(false);
		MapManager::getInstance()->getTilemap()->removeFromParentAndCleanup(false);
		MissionManager::getInstance()->removeFromParentAndCleanup(false);
		Menuset->removeFromParentAndCleanup(false);
		break;
	}
	case GameMode::MEMBER_MODE:
	{
		GuildMemberManager::getInstance()->getMemberLayer()->removeFromParentAndCleanup(false);
		Menuset->removeFromParentAndCleanup(false);
		break;
	}
	case GameMode::MISSION_MODE:
	{
		GuildMemberManager::getInstance()->getMemberLayer()->removeFromParentAndCleanup(false);
		Menuset->removeFromParentAndCleanup(false);
		break;
	}
	case GameMode::DETAIL_MEMBER_MODE:
	{
		GuildMemberManager::getInstance()->getMemberLayer()->removeFromParentAndCleanup(false);
		Menuset->removeFromParentAndCleanup(false);
		break;
	}
	case GameMode::DETAIL_MISSION_MODE:
	{
		GuildMemberManager::getInstance()->getMemberLayer()->removeFromParentAndCleanup(false);
		Menuset->removeFromParentAndCleanup(false);
		break;
	}
	}
}

void MenuManager::changeMode()
{
	if (!Mode)
	{
		// Switch
		auto switchClose = (cocos2d::ui::Button*)Menuset->getChildByName("SWITCH_CLOSE");
		auto switchOpen = (cocos2d::ui::Button*)Menuset->getChildByName("SWITCH_OPEN");

		switchOpen->setEnabled(false);

		// Button
		auto buttonbar = (Sprite*)Menuset->getChildByName("BAR");
		auto buttonMission = (cocos2d::ui::Button*)buttonbar->getChildByName("MISSION_FUNCTION");
		auto buttonTown = (cocos2d::ui::Button*)buttonbar->getChildByName("MAIN_FUNCTION");
		auto buttonTrainer = (cocos2d::ui::Button*)buttonbar->getChildByName("TRAINER_FUNCTION");
		auto buttonMember = (cocos2d::ui::Button*)buttonbar->getChildByName("MEMBER_FUNCTION");
		auto buttonSystem = (cocos2d::ui::Button*)buttonbar->getChildByName("SYSTEM_FUNCTION");

		buttonMission->setEnabled(false);
		buttonTown->setEnabled(false);
		buttonTrainer->setEnabled(false);
		buttonMember->setEnabled(false);
		buttonSystem->setEnabled(false);

		// Action
		auto actionEnd = [&]()
		{
			switchClose->setVisible(true);
			switchClose->setEnabled(true);
			switchOpen->setVisible(false);

			buttonbar->setVisible(false);
		};
		CallFunc *actionCallFunc = CallFunc::create(actionEnd);
		RotateTo *actionRotate = RotateTo::create(0.5f, 60.0f);
		ScaleTo *actionScale = ScaleTo::create(0.5f, 0.0f, 1.0f);

		switchOpen->runAction(Sequence::create(EaseBounceOut::create(actionRotate), actionCallFunc, nullptr));
		buttonbar->runAction(EaseOut::create(actionScale, 10.0f));
	}
	else
	{
		// Switch
		auto switchClose = (cocos2d::ui::Button*)Menuset->getChildByName("SWITCH_CLOSE");
		auto switchOpen = (cocos2d::ui::Button*)Menuset->getChildByName("SWITCH_OPEN");

		switchClose->setVisible(false);
		switchClose->setEnabled(false);
		switchOpen->setVisible(true);

		switchOpen->setRotation(60.0f);

		// Button
		auto buttonbar = (Sprite*)Menuset->getChildByName("BAR");
		auto buttonMission = (cocos2d::ui::Button*)buttonbar->getChildByName("MISSION_FUNCTION");
		auto buttonTown = (cocos2d::ui::Button*)buttonbar->getChildByName("MAIN_FUNCTION");
		auto buttonTrainer = (cocos2d::ui::Button*)buttonbar->getChildByName("TRAINER_FUNCTION");
		auto buttonMember = (cocos2d::ui::Button*)buttonbar->getChildByName("MEMBER_FUNCTION");
		auto buttonSystem = (cocos2d::ui::Button*)buttonbar->getChildByName("SYSTEM_FUNCTION");

		buttonbar->setVisible(true);

		// Action
		auto actionEnd = [&]()
		{
			switchOpen->setEnabled(true);

			buttonMission->setEnabled(true);
			buttonTown->setEnabled(true);
			buttonTrainer->setEnabled(true);
			buttonMember->setEnabled(true);
			buttonSystem->setEnabled(true);
		};
		CallFunc *actionCallFunc = CallFunc::create(actionEnd);
		RotateTo *actionRotate = RotateTo::create(0.5f, 0.0f);
		ScaleTo *actionScale = ScaleTo::create(0.5f, 1.0f, 1.0f);

		switchOpen->runAction(Sequence::create(EaseBounceOut::create(actionRotate), actionCallFunc, nullptr));
		buttonbar->runAction(EaseOut::create(actionScale, 10.0f));
	}
}
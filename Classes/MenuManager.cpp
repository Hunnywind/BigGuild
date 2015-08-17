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

	this->changeMode();

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
 		if ("SWITCH" == item->getName())
		{
			if (Mode) Mode = false;
			else Mode = true;

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
	Menuset->removeAllChildrenWithCleanup(true);
	
	if (!Mode)
	{
		auto Switch = cocos2d::ui::Button::create("close.png", "", "",
			cocos2d::ui::Widget::TextureResType::PLIST);
		Switch->setAnchorPoint(Point(0, 0));
		Switch->setTouchEnabled(true);
		Switch->setName("SWITCH");
		Switch->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
		Menuset->addChild(Switch);
		Switch->setPositionX(Director::getInstance()->getWinSize().width - Switch->getSize().width);
	}
	else
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto Switch = cocos2d::ui::Button::create("open1.png", "", "",
			cocos2d::ui::Widget::TextureResType::PLIST);
		Switch->setAnchorPoint(Point(0.5f, 0.5f));
		Switch->setName("SWITCH");
		Switch->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
		Menuset->addChild(Switch, 1);
		Switch->setPositionX(visibleSize.width - (Switch->getSize().width / 2.0f));
		Switch->setPositionY(Switch->getSize().height / 2.0f);
		Switch->setRotation(60.0f);

		auto buttonbar = Sprite::createWithSpriteFrameName("open3.png");
		buttonbar->setAnchorPoint(Point(1.0f, 0.0f));
		Menuset->addChild(buttonbar, 0, "BAR");
		buttonbar->setPosition(Switch->getPositionX(), (Switch->getSize().height / 2.0f) - (buttonbar->getContentSize().height / 2.0f));
		buttonbar->setScale(0.0f, 1.0f);

		// Button
		Size buttonBarSize = buttonbar->getContentSize();
		Vec2 buttonBarPosition = buttonbar->getPosition();

		auto button1 = cocos2d::ui::Button::create("1_mission.png", "", "",
			cocos2d::ui::Widget::TextureResType::PLIST);
		button1->setAnchorPoint(Point(0, 0));
		button1->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
		buttonbar->addChild(button1, 1, "MISSION_FUNCTION");
		button1->setPosition(Vec2(buttonBarSize.width * 0.1f, button1->getSize().height * 0.1f));

		auto button2 = cocos2d::ui::Button::create("2_town.png", "", "",
			cocos2d::ui::Widget::TextureResType::PLIST);
		button2->setAnchorPoint(Point(0, 0));
		button2->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
		buttonbar->addChild(button2, 1, "MAIN_FUNCTION");
		button2->setPosition(Vec2(buttonBarSize.width * 0.25f, button1->getSize().height * 0.06f));

		auto button3 = cocos2d::ui::Button::create("3_trainer.png", "", "",
			cocos2d::ui::Widget::TextureResType::PLIST);
		button3->setAnchorPoint(Point(0, 0));
		button3->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
		buttonbar->addChild(button3, 1, "TRAINER_FUNCTION");
		button3->setPosition(Vec2(buttonBarSize.width * 0.4f, button1->getSize().height * 0.08f));

		auto button4 = cocos2d::ui::Button::create("4_member.png", "", "",
			cocos2d::ui::Widget::TextureResType::PLIST);
		button4->setAnchorPoint(Point(0, 0));
		button4->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
		buttonbar->addChild(button4, 1, "MEMBER_FUNCTION");
		button4->setPosition(Vec2(buttonBarSize.width * 0.56f, button1->getSize().height * 0.05f));

		auto button5 = cocos2d::ui::Button::create("5_system.png", "", "",
			cocos2d::ui::Widget::TextureResType::PLIST);
		button5->setAnchorPoint(Point(0, 0));
		button5->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
		buttonbar->addChild(button5, 1, "SYSTEM_FUNCTION");
		button5->setPosition(Vec2(buttonBarSize.width * 0.71f, button1->getSize().height * 0.06f));

		// Action
		RotateTo *actionRotate = RotateTo::create(0.5f, 0.0f);
		Switch->runAction(EaseBounceOut::create(actionRotate));

		ScaleTo *actionScale = ScaleTo::create(0.5f, 1.0f);
		buttonbar->runAction(EaseOut::create(actionScale, 10.0f));
	}
}

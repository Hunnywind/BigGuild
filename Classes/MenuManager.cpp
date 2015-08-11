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
	Menuset = Layer::create();
	Menuset->retain();
	Menuset->setAnchorPoint(Point(0, 0));
	Menuset->setPosition(Point(0, 280));

	auto graybar = Sprite::create("res/graybar.png");
	graybar->setAnchorPoint(Point(0, 0));

	auto mainitem = ui::Button::create("res/MainMenuButton.png");
	mainitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	mainitem->setAnchorPoint(Point(0, 0));

	auto missionitem = ui::Button::create("res/MissionMenuButton.png");
	missionitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	missionitem->setAnchorPoint(Point(0, 0));

	auto structitem = ui::Button::create("res/StructMenuButton.png");
	structitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	structitem->setAnchorPoint(Point(0, 0));
	structitem->setName("STRUCT_FUNCTION");

	auto memberitem = ui::Button::create("res/MemberMenuButton.png");
	memberitem->addTouchEventListener(CC_CALLBACK_2(MenuManager::buttonCallback, this));
	memberitem->setAnchorPoint(Point(0, 0));

	Menuset->addChild(graybar, 0);
	Menuset->addChild(mainitem, 1, "MAIN_FUNCTION");
	Menuset->addChild(missionitem, 1, "MISSION_FUNCTION");
	Menuset->addChild(structitem, 1, "STRUCT_FUNCTION");
	Menuset->addChild(memberitem, 1, "MEMBER_FUNCTION");

	mainitem->setPosition(Point(5,6));
	missionitem->setPosition(Point(100,6));
	structitem->setPosition(Point(195,6));
	memberitem->setPosition(Point(290,6));

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
			this->sceneClean();
			GuildMemberManager::getInstance()->changeMode(GameMode::MEMBER_MODE);
			Director::getInstance()->replaceScene(MemberScene::createScene());
			preGameMode = GameMode::MEMBER_MODE;
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
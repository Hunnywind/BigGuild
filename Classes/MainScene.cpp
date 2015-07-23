#include "MainScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "MemberScene.h"
#include "MissionScene.h"
#include "MenuManager.h"

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
	this->initLayer();
	this->initMenu();
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

}

void MainScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());
	//auto item_0 = MenuItemFont::create("Mission", CC_CALLBACK_1(MainScene::gameCallback, this));
	//auto item_1 = MenuItemFont::create("Building", CC_CALLBACK_1(MainScene::gameCallback, this));
	//auto item_2 = MenuItemFont::create("Member", CC_CALLBACK_1(MainScene::gameCallback, this));
	//item_0->setName("MISSION_FUNCTION");
	//item_1->setName("STRUCT_FUNCTION");
	//item_2->setName("MEMBER_FUNCTION");

	//auto menu = Menu::create(item_0, item_1, item_2, NULL);
	//menu->alignItemsVerticallyWithPadding(20);
	//menu->setPosition(Point(400, 240));

	//this->getChildByName("LAYER_MENU")->addChild(menu);
}

void MainScene::gameCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;

	this->getChildByName("LAYER_MEMBER")->removeChild(GuildMemberManager::getInstance()->getMemberLayer(), false);
	this->getChildByName("LAYER_MAP")->removeChild(MapManager::getInstance()->getTilemap(), false);
	
	if ("MISSION_FUNCTION" == item->getName())
	{
		GuildMemberManager::getInstance()->rememberPosition();
		GuildMemberManager::getInstance()->changeMode(GameMode::MISSION_MODE);
		Director::getInstance()->replaceScene(MissionScene::createScene());
	}
	if ("MEMBER_FUNCTION" == item->getName())
	{
		GuildMemberManager::getInstance()->rememberPosition();
		GuildMemberManager::getInstance()->changeMode(GameMode::MEMBER_MODE);
		Director::getInstance()->replaceScene(MemberScene::createScene());
	}
}
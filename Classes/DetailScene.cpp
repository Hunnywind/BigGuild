#include "DetailScene.h"
#include "GuildMemberManager.h"
#include "Structs.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "MemberScene.h"
#include "MenuManager.h"

Scene* DetailScene::createScene()
{
	auto scene = Scene::create();

	auto layer = DetailScene::create();
	scene->addChild(layer);

	return scene;
}

bool DetailScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	this->initLayer();
	this->initMenu();
	this->initDetail();
	this->scheduleUpdate();
	MenuManager::getInstance()->setPreGameMode(GameMode::DETAIL_MEMBER_MODE);
	return true;
}

void DetailScene::initLayer()
{
	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer, 0, "LAYER_MENU");

	auto MemberLayer = Layer::create();
	MemberLayer->addChild(GuildMemberManager::getInstance()->getMemberLayer(),1);
	this->addChild(MemberLayer, 0, "LAYER_MEMBER");

	auto DetailLayer = Layer::create();
	MemberLayer->addChild(DetailLayer, 0, "LAYER_DETAIL");
}

void DetailScene::initMenu()
{
	auto item_0 = MenuItemFont::create("Main", CC_CALLBACK_1(DetailScene::gameCallback, this));
	auto item_1 = MenuItemFont::create("All", CC_CALLBACK_1(DetailScene::gameCallback, this));
	auto item_2 = MenuItemFont::create("Back", CC_CALLBACK_1(DetailScene::gameCallback, this));
	auto item_3 = MenuItemFont::create("Next", CC_CALLBACK_1(DetailScene::gameCallback, this));
	item_0->setName("MAIN_FUNCTION");
	item_1->setName("ALL_FUNCTION");
	item_2->setName("BACK_FUNCTION");
	item_3->setName("NEXT_FUNCTION");
	auto menu = Menu::create(item_0, item_1, item_2, item_3, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Point(440, 220));

	this->getChildByName("LAYER_MENU")->addChild(menu,0,"MENU");
}

void DetailScene::initDetail()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	BasicInfo Stat = GuildMemberManager::getInstance()->getBasicInfo(
		GuildMemberManager::getInstance()->getDetailNum());
	Ability Abil = GuildMemberManager::getInstance()->getAbilityInfo(
		GuildMemberManager::getInstance()->getDetailNum());


	auto DetailBackGround = Sprite::create("res/DetailMemberButton.png");
	DetailBackGround->setAnchorPoint(Point(0, 0));
	this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
		->addChild(DetailBackGround, 0);


	char LevelLabel[5] = "Lv";
	char Level[5] = { 0 };
	itoa(Stat.level, Level, 10);
	strcat(LevelLabel, Level);
	auto label = Label::createWithSystemFont(LevelLabel, "Thonburi", 24);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(visibleSize.width / 14, visibleSize.height / 1.3 + 2);
	this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
		->addChild(label, 1);

	auto name = Label::create(Stat.name, "Thonburi", 32);
	name->setColor(Color3B(0, 0, 0));
	name->setAnchorPoint(Point(0, 0));
	name->setPosition(visibleSize.width / 3, visibleSize.height / 1.2);
	this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
		->addChild(name, 1);

	auto expbar = Sprite::create("res/exp1.png");
	expbar->setAnchorPoint(Point(0, 0));
	expbar->setPosition(Point(visibleSize.width / 8, visibleSize.height / 1.3 - 8));
	this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
		->addChild(expbar, 1);

	auto type1 = Sprite::createWithSpriteFrameName(GuildMemberManager::getInstance()
		->getTypeFilename(Stat.type1));
	type1->setScale(1.4f, 1.4f);
	type1->setAnchorPoint(Point(0, 0));
	type1->setPosition(Point(visibleSize.width / 7, visibleSize.height / 1.2));
	this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
		->addChild(type1, 1);
		
	if (TypeList::TYPE_DEFAULT == Stat.type2)
		return;

	auto type2 = Sprite::createWithSpriteFrameName(GuildMemberManager::getInstance()
		->getTypeFilename(Stat.type2));
	type2->setScale(1.4f, 1.4f);
	type2->setAnchorPoint(Point(0, 0));
	type1->setPosition(Point(visibleSize.width / 7, visibleSize.height / 1.2 + 13));
	type2->setPosition(Point(visibleSize.width / 7, visibleSize.height / 1.2 - 13));
	this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
		->addChild(type2, 1);
}

void DetailScene::update(float delta)
{
	int present = GuildMemberManager::getInstance()->getDetailNum();
	if (0 == present)
	{
		this->getChildByName("LAYER_MENU")->getChildByName("MENU")->
			getChildByName("BACK_FUNCTION")->setOpacity(60);
	}
	else
	{
		this->getChildByName("LAYER_MENU")->getChildByName("MENU")->
			getChildByName("BACK_FUNCTION")->setOpacity(255);
	}
	if (GuildMemberManager::getInstance()->getMemberSize() == present + 1)
	{
		this->getChildByName("LAYER_MENU")->getChildByName("MENU")->
			getChildByName("NEXT_FUNCTION")->setOpacity(60);
	}
	else
	{
		this->getChildByName("LAYER_MENU")->getChildByName("MENU")->
			getChildByName("NEXT_FUNCTION")->setOpacity(255);
	}
}

void DetailScene::gameCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;
	int present = GuildMemberManager::getInstance()->getDetailNum();

	if (item->getOpacity() == 60)
		return;
	if ("NEXT_FUNCTION" == item->getName())
	{
		this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
			->removeAllChildrenWithCleanup(true);
		GuildMemberManager::getInstance()->changeMode(GameMode::DETAIL_MEMBER_MODE);
		GuildMemberManager::getInstance()->detailMember(present + 1);
		this->initDetail();
	}
	if ("BACK_FUNCTION" == item->getName())
	{
		this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
			->removeAllChildrenWithCleanup(true);
		GuildMemberManager::getInstance()->changeMode(GameMode::DETAIL_MEMBER_MODE);
		GuildMemberManager::getInstance()->detailMember(present - 1);
		this->initDetail();
	}
	if ("MAIN_FUNCTION" == item->getName())
	{
		this->getChildByName("LAYER_MEMBER")->removeChild
			(GuildMemberManager::getInstance()->getMemberLayer(), false);
		GuildMemberManager::getInstance()->changeMode(GameMode::MAIN_MODE);
		Director::getInstance()->replaceScene(MainScene::createScene());
	}
	if ("ALL_FUNCTION" == item->getName())
	{
		this->getChildByName("LAYER_MEMBER")->removeChild
			(GuildMemberManager::getInstance()->getMemberLayer(), false);
		GuildMemberManager::getInstance()->changeMode(GameMode::MEMBER_MODE);
		Director::getInstance()->replaceScene(MemberScene::createScene());

	}
}
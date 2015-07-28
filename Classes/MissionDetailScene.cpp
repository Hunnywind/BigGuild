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
	ok->addTouchEventListener(CC_CALLBACK_2(MissionDetailScene::MemberButtonCallback, this));
	ok->setAnchorPoint(Point(0, 0));
	MissionLayer->addChild(ok, 1);
	ok->setPosition(Point(160, 50));
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

		//auto label = Label::createWithSystemFont("Lv", "Thonburi", 24);

		//label->setColor(Color3B(0, 0, 0));
		//label->setPosition(64.0f, 16.0f);
		//menuitem->addChild(label, 1);

		//BasicInfo Info = GuildMemberManager::getInstance()->getBasicInfo(i);

		//char cLevel[5] = { 0 };
		//itoa(Info.level, cLevel, 10);
		//auto level = Label::create(cLevel, "Thonburi", 24);
		//level->setColor(Color3B(0, 0, 0));
		//level->setPosition(90.0f, 16.0f);
		//menuitem->addChild(level, 1);

		//auto name = Label::create(Info.name, "Thonburi", 24);
		//name->setColor(Color3B(0, 0, 0));
		//name->setPosition(180.0f, 16.0f);
		//menuitem->addChild(name, 1);

		//auto type1 = Sprite::createWithSpriteFrameName(
		//	GuildMemberManager::getInstance()->getTypeFilename(Info.type1));
		//type1->setScale(1.4f, 1.4f);
		//type1->setPosition(280.0f, 18.0f);
		//menuitem->addChild(type1, 1);

		//if (TypeList::TYPE_DEFAULT == Info.type2)
		//	continue;

		//auto type2 = Sprite::createWithSpriteFrameName(
		//	GuildMemberManager::getInstance()->getTypeFilename(Info.type2));
		//type2->setScale(1.4f, 1.4f);
		//type2->setPosition(360.0f, 18.0f);
		//menuitem->addChild(type2, 1);
	}
	//BasicInfo Stat = GuildMemberManager::getInstance()->getBasicInfo(
	//	GuildMemberManager::getInstance()->getDetailNum());
	//Ability Abil = GuildMemberManager::getInstance()->getAbilityInfo(
	//	GuildMemberManager::getInstance()->getDetailNum());


	//auto DetailBackGround = Sprite::create("res/DetailMemberButton.png");
	//DetailBackGround->setAnchorPoint(Point(0, 0));
	//this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
	//	->addChild(DetailBackGround, 0);


	//char LevelLabel[5] = "Lv";
	//char Level[5] = { 0 };
	//itoa(Stat.level, Level, 10);
	//strcat(LevelLabel, Level);
	//auto label = Label::createWithSystemFont(LevelLabel, "Thonburi", 24);
	//label->setColor(Color3B(0, 0, 0));
	//label->setPosition(visibleSize.width / 14, visibleSize.height / 1.3 + 2);
	//this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
	//	->addChild(label, 1);

	//auto name = Label::create(Stat.name, "Thonburi", 32);
	//name->setColor(Color3B(0, 0, 0));
	//name->setAnchorPoint(Point(0, 0));
	//name->setPosition(visibleSize.width / 3, visibleSize.height / 1.2);
	//this->getChildByName("LAYER_MEMBER")->getChildByName("LAYER_DETAIL")
	//	->addChild(name, 1);

	
	

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
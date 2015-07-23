#include "MemberScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "Structs.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "DetailScene.h"
#include "MenuManager.h"

Scene* MemberScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MemberScene::create();
	scene->addChild(layer);

	return scene;
}

bool MemberScene::init()
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

void MemberScene::initLayer()
{
	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer, 0, "LAYER_MENU");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	ui::ScrollView *scroll = ui::ScrollView::create();
	//scroll->setAnchorPoint(Point(0, 0));
	CCLOG("x:%f, y:%f", scroll->getAnchorPoint().x, scroll->getAnchorPoint().y);
	scroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	scroll->setContentSize(Size(400, 280));
	scroll->setInnerContainerSize(Size(400, GuildMemberManager::getInstance()->getMemberSize()
		* 40));
	CCLOG("x:%f, y:%f", scroll->getPositionX(), scroll->getPositionY());
	scroll->addChild(GuildMemberManager::getInstance()->getMemberLayer(),1);
	this->addChild(scroll,0,"SCROLLVIEW");
}

void MemberScene::initMenu()
{
	this->getChildByName("LAYER_MENU")->addChild(MenuManager::getInstance()->getMenuLayer());
	//auto item_0 = MenuItemFont::create("Main", CC_CALLBACK_1(MemberScene::gameCallback, this));
	//item_0->setName("MAIN_FUNCTION");

	//auto menu = Menu::create(item_0, NULL);
	//menu->alignItemsVerticallyWithPadding(20);
	//menu->setPosition(Point(440, 300));

	//

	//this->getChildByName("LAYER_MENU")->addChild(menu);
}

void MemberScene::initButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int MemberNum = GuildMemberManager::getInstance()->getMemberSize();
	int revision = 0;
	for (int i = 0; i < MemberNum; i++)
	{
		auto menuitem = ui::Button::create("res/MemberButton.png");
		menuitem->addTouchEventListener(CC_CALLBACK_2(MemberScene::buttonCallback, this));
		menuitem->setAnchorPoint(Point(0, 0));
		menuitem->setTag(ButtonList.size());
		menuitem->setName("DETAIL_FUNCTION");
		this->getChildByName("SCROLLVIEW")->addChild(menuitem);
		if (8 > MemberNum)
		{
			revision = 7 - MemberNum;
		}
		menuitem->setPositionY(MemberNum
			* 40 - 40 * i + revision * 40 - 40);
		CCLOG("y: %f", menuitem->getPositionY());
		ButtonList.push_back(menuitem);

		auto label = Label::createWithSystemFont("Lv", "Thonburi", 24);
		
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
}

void MemberScene::buttonCallback(Ref *sender, ui::Widget::TouchEventType type)
{
	auto item = (ui::Button*)sender;

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:

		break;

	case ui::Widget::TouchEventType::MOVED:
		break;

	case ui::Widget::TouchEventType::ENDED:
		this->getChildByName("SCROLLVIEW")
			->removeChild(GuildMemberManager::getInstance()->getMemberLayer(), false);
		GuildMemberManager::getInstance()->changeMode(GameMode::DETAIL_MODE);
		GuildMemberManager::getInstance()->detailMember(item->getTag());
		Director::getInstance()->replaceScene(DetailScene::createScene());
		break;

	case ui::Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}

void MemberScene::gameCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;

	this->getChildByName("SCROLLVIEW")
		->removeChild(GuildMemberManager::getInstance()->getMemberLayer(), false);

	if ("MAIN_FUNCTION" == item->getName())
	{
		GuildMemberManager::getInstance()->changeMode(GameMode::MAIN_MODE);
		Director::getInstance()->replaceScene(MainScene::createScene());
	}

}
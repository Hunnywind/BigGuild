#include "GameScene.h"
#include "GuildMemberManager.h"
#include "MapManager.h"
#include "Enum.h"

#include "ui/CocosGUI.h"


Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();
	MapManager::getInstance()->init();
	this->addChild(MapManager::getInstance()->getTilemap(), 0, "TILEMAP");
	this->initLayers();
	this->initMenu();
	return true;
}

void GameScene::initLayers()
{
	auto NormalLayer = Layer::create();
	NormalLayer->setVisible(true);
	this->addChild(NormalLayer,0,"1.LAYER_NORMAL");

	auto MemberLayer = Layer::create();
	MemberLayer->setVisible(false);
	this->addChild(MemberLayer, 0, "1.LAYER_MEMBER");

	auto NoneScrollLayer = Layer::create();
	NoneScrollLayer->setVisible(false);
	MemberLayer->addChild(NoneScrollLayer, 0, "2.LAYER_MEMBER_NONESCROLL");

	ui::ScrollView *scroll = ui::ScrollView::create();
	scroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	scroll->setContentSize(Size(450, 800));
	scroll->setInnerContainerSize(Size(450, 1400));
	MemberLayer->addChild(scroll, 0, "2.MEMBER_SCROLL");

	auto ScrollButtonMenu = Menu::create();
	ScrollButtonMenu->setPositionY(550.0f);
	scroll->addChild(ScrollButtonMenu, 0, "3.MEMBER_SCROLL_BUTTON");

	GuildMemberManager::getInstance()->init();
	NormalLayer->addChild(GuildMemberManager::getInstance()->initMemberLayer());

	auto DetailBackGround = Sprite::create("res/DetailMemberButton.png");
	DetailBackGround->setPosition(Point(400.0 / 2.0, 320.0 / 2.0));
	NoneScrollLayer->addChild(DetailBackGround,0,"DETAIL_BOX");

	
	// test
	this->addMember(0);
	this->addMember(0);
	this->addMember(0);
	this->addMember(0);
	this->addMember(0);
}

void GameScene::initMenu()
{
	auto MenuLayer = Layer::create();
	this->addChild(MenuLayer,0,"1.LAYER_MENU");

	auto item_0 = MenuItemFont::create("Mission", CC_CALLBACK_1(GameScene::gameCallback, this));
	auto item_1 = MenuItemFont::create("Building", CC_CALLBACK_1(GameScene::gameCallback, this));
	auto item_2 = MenuItemFont::create("Member", CC_CALLBACK_1(GameScene::gameCallback, this));
	item_1->setName("STRUCT_FUNCTION");
	item_2->setName("MEMBER_FUNCTION");
	auto menu = Menu::create(item_0, item_1, item_2, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Point(400, 240));

	MenuLayer->addChild(menu, 0, "2.MENU_NORMAL");


	auto nitem_0 = MenuItemFont::create("Main", CC_CALLBACK_1(GameScene::gameCallback, this));
	auto nitem_1 = MenuItemFont::create("Sort", CC_CALLBACK_1(GameScene::gameCallback, this));
	nitem_0->setName("RETURN_FUNCTION");
	nitem_1->setName("RETURN_FUNCTION");
	auto nmenu = Menu::create(nitem_0, nitem_1,NULL);
	nmenu->setTag(VisibleList::MEMBER_BUTTON);
	nmenu->setVisible(false);
	nmenu->alignItemsVerticallyWithPadding(20);
	nmenu->setPosition(Point(440, 260));

	MenuLayer->addChild(nmenu, 0, "2.MENU_MEMBER");
}

void GameScene::gameCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;
	int support_y = 0;
	std::list<MenuItemImage*>::iterator iter = ButtonList.begin();

	//std::string function = item->getName();

	if ("MEMBER_FUNCTION" == item->getName())
	{
		// visible
		this->getChildByName("TILEMAP")->setVisible(false);
		this->getChildByName("1.LAYER_MENU")->getChildByName("2.MENU_NORMAL")
			->setVisible(false);
		this->getChildByName("1.LAYER_MENU")->getChildByName("2.MENU_MEMBER")
			->setVisible(true);
		this->getChildByName("1.LAYER_NORMAL")->setVisible(false);
		this->getChildByName("1.LAYER_MEMBER")->setVisible(true);

		// change member layer
		this->getChildByName("1.LAYER_NORMAL")->removeChild(GuildMemberManager::getInstance()
			->getMemberLayer(), false);
		this->getChildByName("1.LAYER_MEMBER")->getChildByName("2.MEMBER_SCROLL")
			->addChild(GuildMemberManager::getInstance()->getMemberLayer());
		


		for (iter = ButtonList.begin(); iter != ButtonList.end(); iter++)
		{
			auto fadeinAction = FadeIn::create(1.0f);
			(*iter)->setPositionY(345.0f - support_y * 42);
			(*iter)->setPositionX(-40.0f);
			(*iter)->setOpacity(0);
			(*iter)->runAction(fadeinAction);
			support_y++;
		}

		GuildMemberManager::getInstance()->changeMode(GameMode::MEMBER_MODE);
	}

	if ("RETURN_FUNCTION" == item->getName())
	{
		// visible
		this->getChildByName("TILEMAP")->setVisible(true);
		this->getChildByName("1.LAYER_MENU")->getChildByName("2.MENU_NORMAL")
			->setVisible(true);
		this->getChildByName("1.LAYER_MENU")->getChildByName("2.MENU_MEMBER")
			->setVisible(false);
		this->getChildByName("1.LAYER_NORMAL")->setVisible(true);
		this->getChildByName("1.LAYER_MEMBER")->setVisible(false);


		// change member layer
		this->getChildByName("1.LAYER_MEMBER")->getChildByName("2.MEMBER_SCROLL")
			->removeChild(GuildMemberManager::getInstance()
			->getMemberLayer(), false);
		this->getChildByName("1.LAYER_NORMAL")->addChild(GuildMemberManager::getInstance()
			->getMemberLayer());
		dynamic_cast<cocos2d::ui::ScrollView*>(this->getChildByName("1.LAYER_MEMBER")
			->getChildByName("2.MEMBER_SCROLL"))
			->scrollToPercentVertical(0, 1, false);
		GuildMemberManager::getInstance()->changeMode(GameMode::NORMAL_MODE);
	}
	
	if ("DETAIL_FUNCTION" == item->getName())
	{
		
		// visible
		this->getChildByName("1.LAYER_MEMBER")->getChildByName("2.MEMBER_SCROLL")
			->setVisible(false);
		this->getChildByName("1.LAYER_MEMBER")->getChildByName("2.LAYER_MEMBER_NONESCROLL")
			->setVisible(true);
		this->getChildByName("1.LAYER_MENU")->getChildByName("2.MENU_MEMBER")
			->setVisible(false);
		// change member layer
		this->getChildByName("1.LAYER_MEMBER")->getChildByName("2.MEMBER_SCROLL")
			->removeChild(GuildMemberManager::getInstance()
			->getMemberLayer(), false);
		this->getChildByName("1.LAYER_MEMBER")->getChildByName("2.LAYER_MEMBER_NONESCROLL")
			->addChild(GuildMemberManager::getInstance()
			->getMemberLayer());

		GuildMemberManager::getInstance()->changeMode(GameMode::DETAILMEMBER_MODE);
		GuildMemberManager::getInstance()->detailMember(item->getTag());

	}
}

void GameScene::addMember(int const dex)
{
	auto menuitem = MenuItemImage::create("res/MemberButton.png", "res/MemberButton.png",
		CC_CALLBACK_1(GameScene::gameCallback, this));
	menuitem->setTag(ButtonList.size());
	menuitem->setName("DETAIL_FUNCTION");

	this->getChildByName("1.LAYER_MEMBER")
		->getChildByName("2.MEMBER_SCROLL")
		->getChildByName("3.MEMBER_SCROLL_BUTTON")
		->addChild(menuitem);
	ButtonList.push_back(menuitem);

	GuildMemberManager::getInstance()->addMember(dex);
}
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
#include "MissionScene.h"
#include "Member.h"

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

	MemberGrades = 0;

	this->initLayer();
	this->initMenu();
	this->initDetail();
	this->setGrades();
	this->scheduleUpdate();
	MenuManager::getInstance()->setPreGameMode(GameMode::DETAIL_MISSION_MODE);
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
	ok->addTouchEventListener(CC_CALLBACK_2(MissionDetailScene::OkCallback, this));
	ok->setAnchorPoint(Point(0, 0));
	MissionLayer->addChild(ok, 1, "OK_BUTTON");
	ok->setPosition(Point(285, 50));

	auto GradeLayer = Layer::create();
	MissionLayer->addChild(GradeLayer, 0, "LAYER_GRADE");

	auto StanByMemberLayer = Layer::create();
	MissionLayer->addChild(StanByMemberLayer, 0, "LAYER_STANBY");
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
		menuitem->setName("WAIT");
		this->getChildByName("MEMBER_SCROLLVIEW")->addChild(menuitem);
		if (8 > MemberNum)
		{
			revision = 7 - MemberNum;
		}
		menuitem->setPositionY(MemberNum
			* 40 - 40 * i + revision * 40 - 40);
		CCLOG("y: %f", menuitem->getPositionY());
		MemberButtonList.push_back(menuitem);
	}
}

void MissionDetailScene::setGrades()
{
	this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_GRADE")
		->removeAllChildren();
	Mission preMission = MissionManager::getInstance()->getPreSTANBY();

	for (int i = 0; i < preMission.gradeMax; i++)
	{
		auto sprite = Sprite::create("res/ic_favorite.png");
		sprite->setAnchorPoint(Point(0, 0));
		sprite->setPosition(Point(170 + 32 * i, 220));
		this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_GRADE")
			->addChild(sprite, 1);
	}
	for (int i = 0; i < preMission.gradeMin; i++)
	{
		auto sprite = Sprite::create("res/ic_favorite.png");
		sprite->setAnchorPoint(Point(0, 0));
		sprite->setPosition(Point(170 + 32 * i, 140));
		this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_GRADE")
			->addChild(sprite, 1);
	}
	for (int i = 0; i < MemberGrades; i++)
	{
		auto sprite = Sprite::create("res/ic_favorite.png");
		sprite->setAnchorPoint(Point(0, 0));
		sprite->setPosition(Point(170 + 32 * i, 180));
		this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_GRADE")
			->addChild(sprite, 1);
	}
}

void MissionDetailScene::update(float delta)
{
	Mission preMission = MissionManager::getInstance()->getPreSTANBY();
	if (preMission.gradeMin <= MemberGrades && preMission.gradeMax >= MemberGrades)
	{
		this->getChildByName("LAYER_MISSION")
			->getChildByName("OK_BUTTON")->setOpacity(255);
	}
	else
	{
		this->getChildByName("LAYER_MISSION")
			->getChildByName("OK_BUTTON")->setOpacity(60);
	}
	
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
		if (MissionCondition::STAN_BY !=
			GuildMemberManager::getInstance()->getMemberM_Condition(item->getTag()))
			return;
		if ("WAIT" == item->getName())
		{
			this->addMemberToMission(item->getTag());
			item->setColor(Color3B(0, 255, 0));
			item->setName("STANBY");
		}
		else
		{
			this->subMemberToMission(item->getTag());
			item->setColor(Color3B(255, 255, 255));
			item->setName("WAIT");
		}
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
	int num = item->getTag();

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:

		break;

	case ui::Widget::TouchEventType::MOVED:
		break;

	case ui::Widget::TouchEventType::ENDED:
		if (this->getChildByName("LAYER_MISSION")
			->getChildByName("OK_BUTTON")->getOpacity() == 255)
		{
			this->participateInMission();
			MissionManager::getInstance()->moveToPROGRESS();
			MenuManager::getInstance()->setPreGameMode(GameMode::DETAIL_MISSION_MODE);
			MenuManager::getInstance()->sceneClean();
			MenuManager::getInstance()->setPreGameMode(GameMode::MISSION_MODE);
			GuildMemberManager::getInstance()->changeMode(GameMode::MISSION_MODE);
			Director::getInstance()->replaceScene(MissionScene::createScene());
		}
		break;

	case ui::Widget::TouchEventType::CANCELED:
		break;

	default:
		break;
	}
}

void MissionDetailScene::addMemberToMission(int num)
{
	MemberGrades += GuildMemberManager::getInstance()->getBasicInfo(num)
		.grade;

	int _dex = GuildMemberManager::getInstance()->getBasicInfo(num).dex;

	auto StanByMember = Member::create();
	char filename[20] = "Pokemon_";
	char _num[20];
	char extension[20] = ".png";
	sprintf(_num, "%d", _dex);
	strcat(_num, extension);
	strcat(filename, _num);
	std::string finalname = filename;
	StanByMember->changeMode(GameMode::DETAIL_MISSION_MODE);
	StanByMember->initSprite(finalname);

	StanByMember->setTag(num);
	StanByMember->setID(GuildMemberManager::getInstance()->getID(num));
	this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_STANBY")
		->addChild(StanByMember);


	this->sortSTANBY();
	this->setGrades();
}

void MissionDetailScene::subMemberToMission(int num)
{
	MemberGrades -= GuildMemberManager::getInstance()->getBasicInfo(num)
		.grade;
	this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_STANBY")
		->removeChildByTag(num);
	this->sortSTANBY();
	this->setGrades();
}

void MissionDetailScene::sortSTANBY()
{
	std::vector<Node*>::iterator iter =
		this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_STANBY")
		->getChildren().begin();

	
	int i = 0;

	for (iter; iter != this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_STANBY")
		->getChildren().end(); iter++)
	{
		
		(*iter)->setPosition(180 + 30 * i, 140);
		i++;
	}

}

void MissionDetailScene::participateInMission()
{

	std::vector<Node*>::iterator iter =
		this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_STANBY")
		->getChildren().begin();

	for (iter; iter != this->getChildByName("LAYER_MISSION")->getChildByName("LAYER_STANBY")
		->getChildren().end(); iter++)
	{
		MissionManager::getInstance()->addMemberToMission(dynamic_cast<Member*>(*iter)->getID());
		GuildMemberManager::getInstance()->setMemberMission((*iter)->getTag());
	}
}
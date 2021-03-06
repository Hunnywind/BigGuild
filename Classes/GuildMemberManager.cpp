#include "GuildMemberManager.h"
#include "Member.h"
#include "Enum.h"
#include "Structs.h"
#include "ui/CocosGUI.h"

bool Compare(Member* elem1, Member* elem2)
{
	if (elem1->getStat().level > elem2->getStat().level)
		return true;

	return false;
}
bool CompareMission(Member* elem1, Member* elem2)
{
	if (elem1->getM_Condition() > elem2->getM_Condition())
		return true;

	return false;
}
GuildMemberManager::GuildMemberManager()
{
	this->init();
}
GuildMemberManager* GuildMemberManager::getInstance()
{
	static GuildMemberManager* instance = NULL;

	if (NULL == instance)
		instance = new GuildMemberManager();

	return instance;
}
bool GuildMemberManager::init()
{
	pool.initialize(5000);

	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Pokemon/151_4x.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("res/Type.plist");
	this->initMemberLayer();

	this->addMember(RandomHelper::random_int(1,151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	this->addMember(RandomHelper::random_int(1, 151));
	return true;
}

void GuildMemberManager::initMemberLayer()
{
	MemberLayer = Layer::create();
	MemberLayer->retain();
}

void GuildMemberManager::addMember(int dex)
{
	// json
	char filename[20] = "Pokemon_";
	char num[20];
	char extension[20] = ".png";
	sprintf(num, "%d", dex);
	strcat(num, extension);
	strcat(filename,num);
	std::string finalname = filename;
	auto Unit = Member::create();
	Unit->initSprite(finalname);
	Unit->setID(*(pool.newData()));
	Unit->setDex(dex);

	MemberLayer->addChild(Unit);
	MemberList.push_back(Unit);
	
}

BasicInfo GuildMemberManager::getBasicInfo(int num)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	for (int i = 0; i < num; i++)
		iter++;

	return (*iter)->getStat();
}
Ability GuildMemberManager::getAbilityInfo(int num)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	for (int i = 0; i < num; i++)
		iter++;

	return (*iter)->getAbil();
}
int GuildMemberManager::getID(int num)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	for (int i = 0; i < num; i++)
		iter++;

	return (*iter)->getID();
}
std::string GuildMemberManager::getTypeFilename(TypeList Type)
{
	if (TypeList::TYPE_DEFAULT == Type)
		CCLOG("This Type is DEFAULT");

	char filename[20] = "type";
	char nation[20] = "E";
	char num[20];
	int typenum = Type;
	sprintf(num, "%d", typenum);
	char extension[20] = ".png";

	strcat(num, extension);
	strcat(filename, nation);
	strcat(filename, num);

	std::string returnValue = filename;
	return returnValue;
}
void GuildMemberManager::changeMode(GameMode mode)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int support_y = 0;
	int revision = 0;
	switch (mode)
	{
	case GameMode::MAIN_MODE:
	{
		for (auto i : MemberList)
		{
			i->stopAllActions();
			i->changeMode(mode);
		}
		break;
	}
	case GameMode::MEMBER_MODE:
	{
		MemberList.sort(CompareMission);
		for (auto i : MemberList)
		{
			i->changeMode(mode);
			if (8 > MemberList.size())
			{
				revision = 7 - MemberList.size();
			}
			i->getCharacter()->setAnchorPoint(Point(0, 0));
			Point Location = { -4.0f, MemberList.size() * 40 - 2
				- 40 * support_y + revision * 40 - 40.0f};
			i->getCharacter()->setPosition(Location);
			i->getCharacter()->setScale(1.5f);
			support_y++;
		}
		
		break;
	}
	case GameMode::DETAIL_MEMBER_MODE:
	{
		for (auto i : MemberList)
		{
			i->getCharacter()->setVisible(false);
			i->stopAllActions();
		}
		break;
	}
	case GameMode::MISSION_MODE:
	{
		MemberList.sort(CompareMission);
		break;
	}
	case GameMode::DETAIL_MISSION_MODE:
	{
		for (auto i : MemberList)
		{
			i->changeMode(mode);
			if (8 > MemberList.size())
			{
				revision = 7 - MemberList.size();
			}
			i->getCharacter()->setAnchorPoint(Point(0, 0));
			Point Location = { -4.0f, MemberList.size() * 40 - 2
				- 40 * support_y + revision * 40 - 40.0f };
			i->getCharacter()->setPosition(Location);
			i->getCharacter()->setScale(1.5f);
			support_y++;
		}
		break;
	}
	}
}

void GuildMemberManager::rememberPosition()
{
	for (auto i : MemberList)
	{
		i->rememberPostion();
	}
}
void GuildMemberManager::detailMember(int num)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	(*iter)->getCharacter()->setVisible(true);
	(*iter)->changeMode(GameMode::DETAIL_MEMBER_MODE);
	DetailNum = num;
}

void GuildMemberManager::setMemberMission(int num)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	(*iter)->setMission(MissionCondition::PROGRESS);
}

MissionCondition GuildMemberManager::getMemberM_Condition(int num)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	return (*iter)->getM_Condition();
}
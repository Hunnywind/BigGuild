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
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("res/pokemon.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("res/type.plist");
	this->initMemberLayer();

	this->addMember(0);
	this->addMember(0);
	this->addMember(0);
	this->addMember(0);
	this->addMember(0);

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
	std::string filename = "Pokemon_37.gif";
	auto Unit = Member::create();
	Unit->initSprite(filename);

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
std::string GuildMemberManager::getTypeFilename(TypeList Type)
{
	if (TypeList::TYPE_DEFAULT == Type)
		CCLOG("This Type is DEFAULT");

	char filename[20] = "type";
	char nation[20] = "E";
	char num[20];
	itoa(Type, num, 10);
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
		for (iter = MemberList.begin(); iter != MemberList.end(); iter++)
		{
			(*iter)->stopAllActions();
			(*iter)->changeMode(mode);
		}
		break;
	}
	case GameMode::MEMBER_MODE:
	{
		MemberList.sort(Compare);
		for (iter = MemberList.begin(); iter != MemberList.end(); iter++)
		{
			(*iter)->changeMode(mode);
			(*iter)->getCharacter()->setPositionY(MemberList.size() * 40
			- (*iter)->getPositionY());
			if (8 > MemberList.size())
			{
				revision = 8 - MemberList.size();
			}
			Point Location = { 25.0f, MemberList.size() * 40  - 12.0f
				- 40 * support_y + revision * 40};
			/*auto moveAction = MoveTo::create(1.0f, ActionPoint);
			auto scaleAction = ScaleTo::create(1.0f, 2.0f);
			auto spawnAction = Spawn::create(moveAction, scaleAction, NULL);
			(*iter)->getCharacter()->runAction(spawnAction);*/
			(*iter)->getCharacter()->setPosition(Location);
			(*iter)->getCharacter()->setScale(2.0f);
			support_y++;
		}
		
		break;
	}
	case GameMode::DETAIL_MODE:
	{
		for (iter = MemberList.begin(); iter != MemberList.end(); iter++)
		{
			(*iter)->getCharacter()->setVisible(false);
			(*iter)->stopAllActions();
			//(*iter)->setPositionY((*iter)->getPositionY() - 600);
		}
		break;
	}
	}
}

void GuildMemberManager::rememberPosition()
{
	std::list<Member*>::iterator iter = MemberList.begin();

	for (iter = MemberList.begin(); iter != MemberList.end(); iter++)
	{
		(*iter)->rememberPostion();
		
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
	(*iter)->changeMode(GameMode::DETAIL_MODE);
	DetailNum = num;
}
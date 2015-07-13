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

	
	return true;
}
Layer* GuildMemberManager::initMemberLayer()
{
	MemberLayer = Layer::create();
	MemberLayer->retain();
	return MemberLayer;
}
void GuildMemberManager::addMember(int dex)
{
	// json
	std::string filename = "Pokemon_37.gif";
	auto Unit = Member::create();
	Unit->setSpriteFrame(filename);
	MemberLayer->addChild(Unit);


	MemberList.push_back(Unit);
	
}

void GuildMemberManager::changeMode(int mode)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	
	int support_y = 0;

	switch (mode)
	{
	case GameMode::NORMAL_MODE:
	{
		//this->getChildByTag(VisibleList::MEMBER_BUTTON)->setVisible(false);
		for (iter = MemberList.begin(); iter != MemberList.end(); iter++)
		{
			//this->getChildByTag(VisibleList::MEMBER_BUTTON)->setVisible(false);
			(*iter)->setPositionY((*iter)->getPositionY() - 600);
			(*iter)->stopAllActions();
			(*iter)->changeMode(mode);
		}
		break;
	}
	case GameMode::MEMBER_MODE:
	{
		MemberList.sort(Compare);
		//this->getChildByTag(VisibleList::MEMBER_BUTTON)->setVisible(true);
		for (iter = MemberList.begin(); iter != MemberList.end(); iter++)
		{
			//this->getChildByTag(VisibleList::MEMBER_BUTTON)->setVisible(true);
			(*iter)->changeMode(mode);
			(*iter)->setPositionY((*iter)->getPosition().y + 600);
			Point ActionPoint = { 25.0f, 900.0f - support_y * 42 };
			auto moveAction = MoveTo::create(1.0f, ActionPoint);
			auto scaleAction = ScaleTo::create(1.0f, 2.0f);
			auto spawnAction = Spawn::create(moveAction, scaleAction, NULL);
			(*iter)->runAction(spawnAction);
			support_y++;
		}
		
		break;
	}
	case GameMode::DETAILMEMBER_MODE:
	{
		for (iter = MemberList.begin(); iter != MemberList.end(); iter++)
		{
			(*iter)->setVisible(false);
			(*iter)->stopAllActions();
			(*iter)->setPositionY((*iter)->getPositionY() - 600);
		}
		break;
	}
	}
}

void GuildMemberManager::detailMember(int num)
{
	std::list<Member*>::iterator iter = MemberList.begin();
	for (int i = 0; i < num; i++)
	{
		iter++;
	}
	(*iter)->setVisible(true);
	(*iter)->changeMode(GameMode::DETAILMEMBER_MODE);
}
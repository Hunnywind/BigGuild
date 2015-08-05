#pragma once

#include "cocos2d.h"
#include <list>
#include "Enum.h"
#include "Structs.h"
#include "Pooling.h"
#include "ID.h"

USING_NS_CC;
class Member;


class GuildMemberManager
{
public:
	~GuildMemberManager(){}
	static GuildMemberManager* getInstance();
	BasicInfo getBasicInfo(int num);
	Ability getAbilityInfo(int num);
	void initMemberLayer();
	Layer* getMemberLayer() { return MemberLayer; }
	std::string getTypeFilename(TypeList Type);
	bool init();
	void addMember(int dex);
	void changeMode(GameMode mode);
	int getMemberSize() { return MemberList.size(); }
	void detailMember(int num);
	int getDetailNum() { return DetailNum; }
	int getID(int num);
	void rememberPosition();
	void setMemberMission(int num);
private:
	GuildMemberManager();

	Layer* MemberLayer;
	std::list<Member*> MemberList;

	int DetailNum;

	CPool<ID> pool;
};

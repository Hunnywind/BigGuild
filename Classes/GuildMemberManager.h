#pragma once

#include "cocos2d.h"
#include <list>
USING_NS_CC;
class Member;


class GuildMemberManager
{
public:
	~GuildMemberManager(){}
	static GuildMemberManager* getInstance();

	Layer* initMemberLayer();
	Layer* getMemberLayer() { return MemberLayer; }
	virtual bool init();
	void addMember(int dex);
	void changeMode(int mode);
	void detailMember(int num);
private:
	GuildMemberManager(){}

	Layer* MemberLayer;
	std::list<Member*> MemberList;
};

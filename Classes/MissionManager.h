#pragma once

#include "cocos2d.h"
#include <list>
#include "Enum.h"
#include "Structs.h"

USING_NS_CC;
class Member;


class MissionManager : public Node
{
public:
	~MissionManager(){}
	static MissionManager* getInstance();
	bool init();
	virtual void update(float delta);

	void addMission(int dex);
	Mission getMission(int num);
	int getMissionSize() { return MissionList.size(); }
private:
	MissionManager();
	std::list<Mission> MissionList;

};

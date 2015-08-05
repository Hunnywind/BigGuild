#pragma once

#include "cocos2d.h"
#include <list>
#include "Enum.h"
#include "Structs.h"
#include "Pooling.h"
#include "ID.h";
USING_NS_CC;
using namespace Homura;


class MissionManager : public Node
{
public:
	~MissionManager(){}
	static MissionManager* getInstance();
	bool init();
	virtual void update(float delta);

	void addSTANBY(int dex);

	Mission getMission(MissionCondition con, int num);
	Mission getPreSTANBY();
	
	void moveToPROGRESS();

	int getMissionSize(MissionCondition con);

	void setDetailNum(int num) { DetailNum = num; }
	void addMemberToMission(int id);
private:
	MissionManager();
	std::list<Mission> STANBY_List;
	std::list<Mission> PROGRESS_List;
	std::list<Mission> COMPLETE_List;

	int DetailNum;

	CPool<ID> pool;

	// is Sort Progress Mission
	bool isSort;
};

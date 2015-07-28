#pragma once

#include "cocos2d.h"
#include <list>
#include "Enum.h"
#include "Structs.h"

USING_NS_CC;



class MissionManager : public Node
{
public:
	~MissionManager(){}
	static MissionManager* getInstance();
	bool init();
	virtual void update(float delta);

	void addSTANBY(int dex);

	Mission getSTANBY(int num);
	Mission getPreSTANBY();

	void moveToPROGRESS(int num);

	int getSTANBYSize() { return STANBY_List.size(); }

	void setDetailNum(int num) { DetailNum = num; }
private:
	MissionManager();
	std::list<Mission> STANBY_List;
	std::list<Mission> PROGRESS_List;
	std::list<Mission> COMPLETE_List;

	int DetailNum;
};

#pragma once

#include "cocos2d.h"
#include "Enum.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"
#include <list>
USING_NS_CC;


class CompleteMissionScene : public Layer
{
public:

	static Scene* createScene();
	CREATE_FUNC(CompleteMissionScene);

	virtual bool init();
	void initLayer();
	void initMenu();
	void initButton();
	void MissionButtonCallback(Ref *pSender, ui::Widget::TouchEventType type);
	void gameCallback(Ref *sender);

	void MemberToSTANBY(int num);
private:
	std::list<ui::Button*> MissionButtonList;
	int ButtonScrollSize;
};



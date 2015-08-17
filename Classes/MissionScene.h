#ifndef __MISSION_SCENE_H__
#define __MISSION_SCENE_H__

#include "cocos2d.h"
#include "Enum.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"
#include <list>
USING_NS_CC;


class MissionScene : public Layer
{
public:
	MissionScene();
	static Scene* createScene();
	CREATE_FUNC(MissionScene);

	virtual bool init();
	void initLayer();
	void initMenu();
	void initButton();
	void MissionButtonCallback(Ref *pSender, ui::Widget::TouchEventType type);
	void BasicCallback(Ref *pSender, ui::Widget::TouchEventType type);
	void gameCallback(Ref *sender);

	void changeTap();
private:
	std::list<ui::Button*> MissionButtonList;

	int ButtonScrollSize;
	bool isWAIT;
};

#endif
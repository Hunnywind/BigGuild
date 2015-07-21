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

	static Scene* createScene();
	CREATE_FUNC(MissionScene);

	virtual bool init();
	void initLayer();
	void initMenu();
	void initButton();
	void MissionButtonCallback(Ref *pSender, ui::Widget::TouchEventType type);
	void gameCallback(Ref *sender);
private:
	std::list<ui::Button*> MissionButtonList;


	int ButtonScrollSize;
};



#endif
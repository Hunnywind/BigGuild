#ifndef __MISSION_DETAIL_SCENE_H__
#define __MISSION_DETAIL_SCENE_H__

#include "cocos2d.h"
#include "Enum.h"
#include <list>
#include "ui/UIWidget.h"
#include "ui/UIButton.h"
USING_NS_CC;

class MissionDetailScene : public Layer
{
public:

	static Scene* createScene();
	CREATE_FUNC(MissionDetailScene);

	virtual bool init();
	virtual void update(float delta);

	void initLayer();
	void initMenu();
	void initDetail();

	void gameCallback(Ref *sender);
	void MemberButtonCallback(Ref *sender, ui::Widget::TouchEventType type);
	void OkCallback(Ref *sender, ui::Widget::TouchEventType type);
private:
	std::list<ui::Button*> MemberButtonList;
};



#endif
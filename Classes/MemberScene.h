#ifndef __Member_SCENE_H__
#define __Member_SCENE_H__

#include "cocos2d.h"
#include "Enum.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"
#include <list>
USING_NS_CC;


class MemberScene : public Layer
{
public:

	static Scene* createScene();
	CREATE_FUNC(MemberScene);

	virtual bool init();
	void initLayer();
	void initMenu();
	void initButton();
	void buttonCallback(Ref *pSender, ui::Widget::TouchEventType type);
	void gameCallback(Ref *sender);
private:
	std::list<ui::Button*> ButtonList;

	int ButtonScrollSize;
};



#endif
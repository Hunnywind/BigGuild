#pragma once

#include "cocos2d.h"
#include <list>
#include "Enum.h"
#include "Structs.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"

USING_NS_CC;
class Member;


class MenuManager
{
public:
	~MenuManager(){}
	static MenuManager* getInstance();
	bool init();
	Layer* getMenuLayer() { return Menuset; }
	void buttonCallback(Ref *pSender, ui::Widget::TouchEventType type);
	void sceneClean();
private:
	MenuManager();
	Layer* Menuset;
	GameMode preGameMode;
};

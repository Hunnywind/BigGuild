#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public LayerColor
{
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(MenuScene);

	void changeScene(Ref *sender);
};



#endif
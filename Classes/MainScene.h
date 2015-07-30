#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainScene : public Layer
{
public:

	static Scene* createScene();
	CREATE_FUNC(MainScene);

	virtual bool init();
	virtual void update(float delta);

	void initLayer();
	void initMenu();
	void initMission();

	void gameCallback(Ref *sender);
};



#endif
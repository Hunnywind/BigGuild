#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include <list>
USING_NS_CC;
USING_NS_CC_EXT;

class GuildMemberManager;

class GameScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);
	void initLayers();
	void initMenu();
	void gameCallback(Ref *sender);

	void addMember(int const dex);
private:
	std::list<MenuItemImage*> ButtonList;
};


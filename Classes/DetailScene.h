#ifndef __DETAIL_SCENE_H__
#define __DETAIL_SCENE_H__

#include "cocos2d.h"
#include "Enum.h"
#include <list>
USING_NS_CC;

class DetailScene : public Layer
{
public:

	static Scene* createScene();
	CREATE_FUNC(DetailScene);

	virtual bool init();
	virtual void update(float delta);

	void initLayer();
	void initMenu();
	void initDetail();
	void gameCallback(Ref *sender);
private:
	std::list<MenuItemImage*> ButtonList;
	int ButtonScrollSize;
};



#endif
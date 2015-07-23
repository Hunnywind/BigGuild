#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MapManager
{
public:
	~MapManager(){}

	static MapManager* getInstance();
	void init();
	void clear();
	Rect getBox(int i) { return boxCollision[i]; }
	TMXTiledMap* getTilemap() { return tilemap; }
private:
	MapManager();
	TMXTiledMap* tilemap;
	Rect boxCollision[10];
};

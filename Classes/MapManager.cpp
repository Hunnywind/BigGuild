#include "MapManager.h"

MapManager::MapManager()
{
	this->init();
}
MapManager* MapManager::getInstance()
{
	static MapManager* instance = NULL;

	if (NULL == instance)
		instance = new MapManager();

	return instance;
}
void MapManager::init()
{
	tilemap = NULL;
	tilemap = TMXTiledMap::create("res/Map.tmx");
	tilemap->retain();

	auto group = tilemap->getObjectGroup("CollisionBox");
	auto& objects = group->getObjects();

	Value objectsVal = Value(objects);

	int i = 0;
	for (auto& obj : objects)
	{
		ValueMap& dict = obj.asValueMap();

		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();

		boxCollision[i] = { x, y, width, height };
		i++;
	}
}

void MapManager::clear()
{
}

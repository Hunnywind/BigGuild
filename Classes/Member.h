#pragma once

#include "cocos2d.h"
#include "Structs.h"
#include <string>

USING_NS_CC;

class Member : public Sprite
{
public:
	Member();
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(Member);
	
	void initType(int type1, int type2);


	void collisionCheck();
	void actionMake(float delta);

	void changeMode(int mode);

	Properties getStat() { return Stat; }
	Point getPosition() { return Position; }
	Point tileCoordForPosition(Point position);
private:
	int Mode;
	Rect BoxCollision;
	Point Position;
	Point RanPosition;
	// A Member Properties
	Properties Stat;
};


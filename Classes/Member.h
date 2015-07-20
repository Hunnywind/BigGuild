#pragma once

#include "cocos2d.h"
#include "Structs.h"
#include "Enum.h"
#include <string>

USING_NS_CC;

class Member : public Node
{
public:
	Member();
	CREATE_FUNC(Member);

	virtual bool init();
	virtual void update(float delta);
	void initSprite(std::string filename);
	void collisionCheck();
	void actionMake(float delta);
	

	void modeClear();
	void changeMode(GameMode mode);
	Sprite* getCharacter() { return Character; }
	BasicInfo getStat() { return Stat; }
	Ability getAbil() { return Abil; }
	Point getPosition() { return Position; }
	BasicInfo getBasicInfo() { return Stat; }

	void rememberPostion();
private:
	Sprite* Character;
	GameMode Mode;
	Rect BoxCollision;
	Point Position;
	Point RanPosition;

	// A Member Properties
	BasicInfo Stat;
	Ability Abil;
};


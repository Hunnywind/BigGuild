#include "Member.h"
#include "MapManager.h"


#include "GuildMemberManager.h"

Member::Member()
	: Position(0.0f, 0.0f), Mode(GameMode::MAIN_MODE)
	, RanPosition(0.0f, 0.0f), BoxCollision(0, 0, 0, 0)
{

}

bool Member::init()
{
	this->scheduleUpdate();
	this->schedule(schedule_selector(Member::actionMake), 0.1f);
	this->setGlobalZOrder(1);
	MissionProperty = MissionCondition::STAN_BY;

	// test
	Stat.level = RandomHelper::random_int(1, 20);
	Stat.type1 = TypeList::TYPE_ELECTRIC;
	//Stat.type2 = TypeList::TYPE_DARK;
	return true;
}

void Member::initSprite(std::string filename)
{
	Character = Sprite::createWithSpriteFrameName(filename);
	if (NULL != Character)
	{
		auto group = MapManager::getInstance()->getTilemap()->getObjectGroup("Spawn");
		auto spawnPoint = group->getObject("SpawnPoint");
		Value objectsVal = Value(spawnPoint);
		ValueMap obj = objectsVal.asValueMap();
		//Position.x = RandomHelper::random_int(obj["x"].asInt(), obj["x"].asInt() + obj["width"].asInt());
		//Position.y = RandomHelper::random_int(obj["y"].asInt(), obj["y"].asInt() + obj["height"].asInt());
		Position.x = RandomHelper::random_int(10, 750);
		Position.y = RandomHelper::random_int(180, 1270);
		if (GameMode::DETAIL_MISSION_MODE == Mode)
		{
			Position.x = 0;
			Position.y = 0;
		}
		
	
		Character->setAnchorPoint(Point(0.5f, 0.5f));
		Character->setPosition(Position);
		this->addChild(Character);
	}
	else
		CCLOG("Sprite Create Error");
}

void Member::actionMake(float delta)
{
	if (NULL != Character->getActionManager()->getActionByTag(MoveList::ACTION_RETURN, this))
		return;

	switch (Mode)
	{
	case GameMode::MAIN_MODE:
	{
		auto rAction = MoveBy::create(0.1f, RanPosition);

		auto sAction = Sequence::create(rAction, NULL);
		sAction->setTag(MoveList::ACTION_NORMAL);
		Character->stopAllActions();
		Character->runAction(sAction);
		break;
	}
	}
}

void Member::update(float delta)
{
	RanPosition = { RandomHelper::random_real(-1.0f, 1.0f), RandomHelper::random_real(-1.0f, 1.0f) };
	// tilemap over check
	//if (10 > Character->getPositionX() && RanPosition.x < 0)
	//{
	//	RanPosition.x *= -1;
	//}
	//if (40 > Character->getPositionY() && RanPosition.y < 0)
	//{
	//	RanPosition.y *= -1;
	//}
	//if (260 < Character->getPositionX() && RanPosition.x > 0)
	//{
	//	RanPosition.x *= -1;
	//}
	//if (260 < Character->getPositionY() && RanPosition.y > 0)
	//{
	//	RanPosition.y *= -1;
	//}

	//this->collisionCheck();

	if (MissionCondition::PROGRESS == MissionProperty)
	{
		Character->setOpacity(60);
	}
	else
	{
		Character->setOpacity(255);
	}
}

void Member::collisionCheck()
{
	BoxCollision = Character->getBoundingBox();

	Rect CheckBoxX = { BoxCollision.getMidX() + RanPosition.x * Character->getContentSize().width / 2,
		BoxCollision.getMidY(),
		BoxCollision.size.width, BoxCollision.size.height };

	Rect CheckBoxY = { BoxCollision.getMidX(),
		BoxCollision.getMidY() + RanPosition.y * Character->getContentSize().height / 2,
		BoxCollision.size.width, BoxCollision.size.height };

	if (GameMode::MAIN_MODE == Mode && NULL == Character->getActionManager()->getActionByTag(MoveList::ACTION_RETURN, this))
	{
		for (int i = 0; i < 6; i++)
		{
			if (CheckBoxX.intersectsRect(MapManager::getInstance()->getBox(i)))
			{
				RanPosition.x *= -1;
			}
			if (CheckBoxY.intersectsRect(MapManager::getInstance()->getBox(i)))
			{
				RanPosition.y *= -1;
			}
		}
	}
}

void Member::changeMode(GameMode mode)
{
	Mode = mode;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	switch (mode)
	{
	case GameMode::MEMBER_MODE:
	{
		Character->setVisible(true);
		Character->stopAllActions();
		break;
	}
	case GameMode::MAIN_MODE:
	{
		Character->stopAllActions();
		Character->setPosition(Position);
		Character->setScale(1.0f);
		Character->setVisible(true);
		break;
	}
	case GameMode::DETAIL_MEMBER_MODE:
	{
		Character->setPosition(Point(visibleSize.width / 13 , visibleSize.height / 1.1));
		break;
	}
	case GameMode::DETAIL_MISSION_MODE:
	{
		break;
	}
	}
}

void Member::rememberPostion()
{
	Position.x = Character->getPositionX();
	Position.y = Character->getPositionY();
}
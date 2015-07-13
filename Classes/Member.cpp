#include "Member.h"
#include "MapManager.h"
#include "Enum.h"

#include "GuildMemberManager.h"

Member::Member()
	: Position(0.0f, 0.0f), Mode(GameMode::NORMAL_MODE)
	, RanPosition(0.0f, 0.0f), BoxCollision(0, 0, 0, 0)
{

}

bool Member::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	Stat.name = "MISSINGNO";
	auto group = MapManager::getInstance()->getTilemap()->getObjectGroup("Spawn");
	auto spawnPoint = group->getObject("SpawnPoint");
	Value objectsVal = Value(spawnPoint);
	ValueMap obj = objectsVal.asValueMap();
	Position.x = RandomHelper::random_int(obj["x"].asInt(), obj["x"].asInt() + obj["width"].asInt());
	Position.y = RandomHelper::random_int(obj["y"].asInt(), obj["y"].asInt() + obj["height"].asInt());

	this->setAnchorPoint(Point(0.5f, 0.5f));
	this->setPosition(Position);

	auto Menulayer = Layer::create();
	Menulayer->setTag(GameMode::MEMBER_MODE);
	Menulayer->setVisible(false);
	Menulayer->setAnchorPoint(Point(0.5, 0.5));
	Menulayer->setName("LAYER_STAT");
	this->addChild(Menulayer);

	this->setGlobalZOrder(1);
	
	auto label = Label::createWithSystemFont("Lv", "Thonburi", 11);
	label->setColor(Color3B::BLACK);
	label->setPosition(36.0f, 10.0f);
	label->setName("LV");
	Menulayer->addChild(label);

	Stat.level = RandomHelper::random_int(1, 20);
	std::string level = std::to_string(Stat.level);
	auto flevel = Label::createWithSystemFont(level, "Thonburi", 11);
	flevel->setName("LEVEL");
	flevel->setColor(Color3B::BLACK);
	flevel->setPosition(48.0f, 10.0f);
	Menulayer->addChild(flevel);

	auto fname = Label::createWithSystemFont(Stat.name, "Thonburi", 11);
	fname->setColor(Color3B::BLACK);
	fname->setPosition(92.0f, 10.0f);
	fname->setName("NAME");
	Menulayer->addChild(fname);

	this->scheduleUpdate();
	this->schedule(schedule_selector(Member::actionMake), 0.1f);

	initType(0,0);

	return true;
}

void Member::initType(int type1 = 0, int type2 = 0)
{
	std::string filename1;
	std::string filename2;

	switch (Stat.type1)
	{
	case TypeList::TYPE_DEFAULT:
		filename1 = "typeK13.png";
		break;
	}
	switch (Stat.type2)
	{
	case TypeList::TYPE_DEFAULT:
		filename2 = "typeK13.png";
		break;
	}
	auto sType1 = Sprite::createWithSpriteFrameName(filename1);
	sType1->setPosition(146.0f, 12.0f);
	sType1->setScale(0.7f);
	this->getChildByName("LAYER_STAT")->addChild(sType1, 1, "TYPE1");
	
	if (TYPE_DEFAULT != Stat.type2)
	{
		auto sType2 = Sprite::createWithSpriteFrameName(filename2);
		sType2->setPosition(186.0f, 12.0f);
		sType2->setScale(0.7f);
		this->getChildByName("LAYER_STAT")->addChild(sType2, 1, "TYPE2");
	}
}

void Member::actionMake(float delta)
{
	if (NULL != this->getActionManager()->getActionByTag(MoveList::ACTION_RETURN, this))
		return;

	switch (Mode)
	{
	case GameMode::NORMAL_MODE:
	{
		auto rAction = MoveBy::create(0.1f, RanPosition);

		auto sAction = Sequence::create(rAction, NULL);
		sAction->setTag(MoveList::ACTION_NORMAL);
		this->stopAllActions();
		this->runAction(sAction);
		break;
	}
	}
}

void Member::update(float delta)
{
	RanPosition = { RandomHelper::random_real(-1.0f, 1.0f), RandomHelper::random_real(-1.0f, 1.0f) };
	// tilemap over check
	if (10 > this->getPositionX() && RanPosition.x < 0)
	{
		RanPosition.x *= -1;
	}
	if (40 > this->getPositionY() && RanPosition.y < 0)
	{
		RanPosition.y *= -1;
	}
	if (260 < this->getPositionX() && RanPosition.x > 0)
	{
		RanPosition.x *= -1;
	}
	if (260 < this->getPositionY() && RanPosition.y > 0)
	{
		RanPosition.y *= -1;
	}

	collisionCheck();

}
void Member::collisionCheck()
{
	BoxCollision = this->getBoundingBox();

	Rect CheckBoxX = { BoxCollision.getMidX() + RanPosition.x * this->getContentSize().width / 2,
		BoxCollision.getMidY(),
		BoxCollision.size.width, BoxCollision.size.height };

	Rect CheckBoxY = { BoxCollision.getMidX(),
		BoxCollision.getMidY() + RanPosition.y * this->getContentSize().height / 2,
		BoxCollision.size.width, BoxCollision.size.height };

	if (GameMode::NORMAL_MODE == Mode && NULL == this->getActionManager()->getActionByTag(MoveList::ACTION_RETURN, this))
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
void Member::changeMode(int mode)
{
	Mode = mode;
	switch (mode)
	{
	case GameMode::MEMBER_MODE:
	{
		if (NULL == this->getActionManager()->getActionByTag(MoveList::ACTION_RETURN, this))
		{
			Position.x = this->getPositionX();
			Position.y = this->getPositionY();
		}
		this->stopAllActions();
		this->getChildByTag(GameMode::MEMBER_MODE)->setVisible(true);
		break;
	}
	case GameMode::NORMAL_MODE:
	{
		this->stopAllActions();
		auto returnAction = MoveTo::create(1.0f, Position);
		auto scaleAction = ScaleTo::create(1.0f, 1.0f);
		auto spawnAction = Spawn::create(returnAction, scaleAction, NULL);
		spawnAction->setTag(MoveList::ACTION_RETURN);
		this->runAction(spawnAction);
		this->getChildByTag(GameMode::MEMBER_MODE)->setVisible(false);
	}
	case GameMode::DETAILMEMBER_MODE:
	{
		this->setPosition(40, 294);
		

		if (TypeList::TYPE_DEFAULT == Stat.type2)
		{
			this->getChildByName("LAYER_STAT")->getChildByName("TYPE1")
				->setPosition(60.0f, 10.0f);
		}
		else
		{
			this->getChildByName("LAYER_STAT")->getChildByName("TYPE1")
				->setPosition(60.0f, 20.0f);
			this->getChildByName("LAYER_STAT")->getChildByName("TYPE2")
				->setPosition(60.0f, 5.0f);
		}

		
		this->getChildByName("LAYER_STAT")->getChildByName("LV")
			->setPosition(10.0f, -6.0f);
		this->getChildByName("LAYER_STAT")->getChildByName("LEVEL")
			->setPosition(24.0f, -6.0f);
		this->getChildByName("LAYER_STAT")->getChildByName("NAME")
			->setPosition(120.0f, 10.0f);

	}
	}
}

Point Member::tileCoordForPosition(Point position)
{
	int x = position.x / MapManager::getInstance()->getTilemap()->getTileSize().width;
	int y = ((MapManager::getInstance()->getTilemap()->getMapSize().height
		* MapManager::getInstance()->getTilemap()->getTileSize().height) - position.y)
		/ MapManager::getInstance()->getTilemap()->getTileSize().height;
	return Point(x, y);
}

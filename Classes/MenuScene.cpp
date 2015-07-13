#include "MenuScene.h"
#include "GameScene.h"

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 255, 255)))
	{
		return false;
	}

	auto item = MenuItemFont::create("Game Start", CC_CALLBACK_1(MenuScene::changeScene, this));

	auto menu = Menu::create(item, NULL);
	menu->alignItemsHorizontally();
	this->addChild(menu);

	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void MenuScene::changeScene(Ref *sender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}
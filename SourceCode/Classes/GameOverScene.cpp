#include "GameOverScene.h"
#include "GameScene.h"

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
	if (!LayerColor::initWithColor(Color4B::RED))
	{
		return false;
	}

	Size size = Director::getInstance()->getWinSize();

	//ÓÎÏ·½áÊølabel
	auto label = Label::create("Game Over", "Arial", 40);
	label->setPosition(size / 2);
	label->setColor(Color3B::WHITE);
	this->addChild(label);

	//°´Å¥
	auto menuItemReStart = MenuItemFont::create("Restart", CC_CALLBACK_1(GameOverScene::menuRestartCallBack, this));
	menuItemReStart->setColor(Color3B::WHITE);

	auto menuItemQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(GameOverScene::menuCloseCallBack, this));
	menuItemQuit->setColor(Color3B::WHITE);

	auto menu = Menu::create(menuItemReStart, menuItemQuit, NULL);
	menu->setPosition(Point::ZERO);
	menuItemReStart->setPosition(size.width / 5, size.height / 8);
	menuItemQuit->setPosition(size.width * 7 / 8, size.height / 8);
	this->addChild(menu);

	return true;
}

void GameOverScene::menuRestartCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOverScene::menuCloseCallBack(Ref* obj)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
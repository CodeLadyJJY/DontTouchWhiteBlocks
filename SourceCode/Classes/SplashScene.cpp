#include "SplashScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene * SplashScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

bool SplashScene::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	TTFConfig config("fonts/Marker Felt.ttf", 30);

	//游戏名称
	auto GameName = Label::createWithTTF(config, "Don't Touch White Blocks");
	GameName->setColor(Color3B::WHITE);
	GameName->setPosition(Point(size.width / 2, size.height * 3 / 4));
	this->addChild(GameName);

	//作者
	auto author = Label::createWithTTF(config, "Game By CodeLadyJJY");
	author->setColor(Color3B::WHITE);
	author->setScale(0.5);
	author->setPosition(Point(size.width / 2, size.height * 5 / 8));
	this->addChild(author);

	//按钮
	auto menuItemStart = MenuItemFont::create("Start", CC_CALLBACK_1(SplashScene::menuCallBack, this));
	menuItemStart->setColor(Color3B::WHITE);

	auto menu = Menu::create(menuItemStart, NULL);
	menu->setPosition(Point::ZERO);
	menuItemStart->setPosition(Point(size.width/2, size.height / 4));
	this->addChild(menu);

	return true;
}

void SplashScene::menuCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
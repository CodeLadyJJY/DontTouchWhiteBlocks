#include "GameScene.h"
#include "Block.h"
#include "GameOverScene.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	//以时间为随机种子
	srand(time(NULL));

	//初始化
    winSize = Director::getInstance()->getWinSize();
	rowCount = 0;
	isShowEnd = false;
	isRunning = false;

	//添加游戏层
	gameLayer = Node::create();
	this->addChild(gameLayer);

	//时间标签
	timeLabel = Label::createWithSystemFont("0.000", "Consolas", 20);
	timeLabel->setColor(Color3B::GRAY);
	timeLabel->setAnchorPoint(Point::ZERO);
	timeLabel->setPosition(winSize.width * 3 / 4, winSize.height * 11 / 12);
	this->addChild(timeLabel);

	//开启游戏
	this->startGame();

	//触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *t, Event *e)
	{
		auto bs = Block::getBlocks();
		for (auto it = bs->begin(); it != bs->end(); it++)
		{
			//检测行号为1的块
			if ((*it)->getRow() == 1 && (*it)->getBoundingBox().containsPoint(t->getLocation()))
			{
				//黑块
				if ((*it)->getColor() == Color3B::BLACK)
				{
					if (!isRunning)					//处于非运行状态，则开启
						this->startTimer();
					(*it)->setColor(Color3B::GRAY);	//并且点击后，颜色变为灰色
					this->moveDown();				//并下移
				}
				//绿块
				else if ((*it)->getColor() == Color3B::GREEN)
				{
					this->moveDown();	//下移
					if (isRunning)		//处于运行状态，则终止计时器
						this->endTimer();

					auto menuItemReStart = MenuItemFont::create("Restart", CC_CALLBACK_1(GameScene::menuRestartCallBack, this));
					menuItemReStart->setColor(Color3B::WHITE);

					auto menuItemQuit = MenuItemFont::create("Quit", CC_CALLBACK_1(GameScene::menuCloseCallBack, this));
					menuItemQuit->setColor(Color3B::WHITE);

					auto menu = Menu::create(menuItemReStart, menuItemQuit, NULL);
					menu->setPosition(Point::ZERO);
					menuItemReStart->setPosition(winSize.width / 5, winSize.height / 8);
					menuItemQuit->setPosition(winSize.width * 7 / 8, winSize.height / 8);
					this->addChild(menu);
				}
				//白块，结束游戏
				else
				{
					//清理方块
					auto bs = Block::getBlocks();
					bs->clear();
					//场景跳转
					auto scene = GameOverScene::createScene();
					Director::getInstance()->replaceScene(scene);
				}

				break;
			}
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void GameScene::addStartLine()
{
	auto b = Block::createBlocks(Size(winSize.width, winSize.height / 4), Color3B::YELLOW, "", 0, Color3B::WHITE);
	b->setRow(0);
	gameLayer->addChild(b);
}

void GameScene::addEndLine()
{
	auto b = Block::createBlocks(winSize, Color3B::GREEN, "Congratulations", 30, Color3B::WHITE);
	b->setPosition(0, winSize.height);
	b->setRow(4);
	gameLayer->addChild(b);
}

void GameScene::addNormalLine(int row)
{
	Block *b;

	//黑块为(0~3)随机一个列号
	int black_col = rand() % 4;

	//每行有4个黑白块
	for (int i = 0; i < 4; ++i)
	{
		if(row == 1)
			b = Block::createBlocks(Size(winSize.width / 4 - 1, winSize.height / 4 - 1), i == black_col ? Color3B::BLACK : Color3B::WHITE, i == black_col ? "Start" : "", 20, Color3B::GRAY);
		else
			b = Block::createBlocks(Size(winSize.width / 4 - 1, winSize.height / 4 - 1), i == black_col ? Color3B::BLACK : Color3B::WHITE, "", 0, Color3B::WHITE);
		b->setPosition(i * winSize.width / 4, row * winSize.height / 4);
		b->setRow(row);
		gameLayer->addChild(b);
	}

	//总行数加一
	rowCount++;
}

void GameScene::startGame()
{
	this->addStartLine();
	this->addNormalLine(1);
	this->addNormalLine(2);
	this->addNormalLine(3);
}

void GameScene::moveDown()
{
	//总行数小于30，则继续添加黑白行
	if(rowCount <= 30)
		this->addNormalLine(4);//每次新添加的行号都为4
	//总行数大于30，则添加结束行，并且设置isShowEnd为true，因为只能显示一次结束行
	else if(!isShowEnd)
	{
		this->addEndLine();
		isShowEnd = true;
	}

	//整体下移
	auto bs = Block::getBlocks();
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		(*it)->moveDown();
	}
}

void GameScene::update(float t)
{
	//时间更新
	long offset = clock() - startTime;

	timeLabel->setString(StringUtils::format("%g", (double)offset / 1000));
}

void GameScene::startTimer()
{
	if (!isRunning)
	{
		isRunning = true;
		this->scheduleUpdate();
		startTime = clock();
	}
}

void GameScene::endTimer()
{
	if (isRunning)
	{
		isRunning = false;
		this->unscheduleUpdate();
	}
}

void GameScene::menuRestartCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameScene::menuCloseCallBack(Ref* obj)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
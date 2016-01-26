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
    
	//��ʱ��Ϊ�������
	srand(time(NULL));

	//��ʼ��
    winSize = Director::getInstance()->getWinSize();
	rowCount = 0;
	isShowEnd = false;
	isRunning = false;

	//�����Ϸ��
	gameLayer = Node::create();
	this->addChild(gameLayer);

	//ʱ���ǩ
	timeLabel = Label::createWithSystemFont("0.000", "Consolas", 20);
	timeLabel->setColor(Color3B::GRAY);
	timeLabel->setAnchorPoint(Point::ZERO);
	timeLabel->setPosition(winSize.width * 3 / 4, winSize.height * 11 / 12);
	this->addChild(timeLabel);

	//������Ϸ
	this->startGame();

	//��������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *t, Event *e)
	{
		auto bs = Block::getBlocks();
		for (auto it = bs->begin(); it != bs->end(); it++)
		{
			//����к�Ϊ1�Ŀ�
			if ((*it)->getRow() == 1 && (*it)->getBoundingBox().containsPoint(t->getLocation()))
			{
				//�ڿ�
				if ((*it)->getColor() == Color3B::BLACK)
				{
					if (!isRunning)					//���ڷ�����״̬������
						this->startTimer();
					(*it)->setColor(Color3B::GRAY);	//���ҵ������ɫ��Ϊ��ɫ
					this->moveDown();				//������
				}
				//�̿�
				else if ((*it)->getColor() == Color3B::GREEN)
				{
					this->moveDown();	//����
					if (isRunning)		//��������״̬������ֹ��ʱ��
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
				//�׿飬������Ϸ
				else
				{
					//������
					auto bs = Block::getBlocks();
					bs->clear();
					//������ת
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

	//�ڿ�Ϊ(0~3)���һ���к�
	int black_col = rand() % 4;

	//ÿ����4���ڰ׿�
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

	//��������һ
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
	//������С��30���������Ӻڰ���
	if(rowCount <= 30)
		this->addNormalLine(4);//ÿ������ӵ��кŶ�Ϊ4
	//����������30������ӽ����У���������isShowEndΪtrue����Ϊֻ����ʾһ�ν�����
	else if(!isShowEnd)
	{
		this->addEndLine();
		isShowEnd = true;
	}

	//��������
	auto bs = Block::getBlocks();
	for (auto it = bs->begin(); it != bs->end(); it++)
	{
		(*it)->moveDown();
	}
}

void GameScene::update(float t)
{
	//ʱ�����
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
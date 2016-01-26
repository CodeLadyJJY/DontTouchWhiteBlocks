#include "Block.h"

Vector<Block*> *Block::blocks = new Vector<Block*>();	//静态变量初始化

Vector<Block*> * Block::getBlocks()
{
	return Block::blocks;
}

Block* Block::createBlocks(Size block_size, Color3B block_color, string label, float label_size, Color3B label_color)
{
	Block* pRet = new Block();
	if (pRet && pRet->init(block_size, block_color, label, label_size, label_color))
	{
		pRet->autorelease();
		blocks->pushBack(pRet);
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Block::init(Size block_size, Color3B block_color, string label, float label_size, Color3B label_color)
{
	if (!Sprite::init())
		return false;

	//块
	this->setContentSize(block_size);
	this->setAnchorPoint(Point::ZERO);
	this->setTextureRect(Rect(0, 0, block_size.width, block_size.height));
	this->setColor(block_color);

	//块中的文字
	auto l = Label::createWithSystemFont(label, "Consolas", label_size);
	l->setPosition(block_size / 2);
	l->setColor(label_color);
	this->addChild(l);

	return true;
}

int Block::getRow()
{
	return row;
}

void Block::setRow(int row)
{
	this->row = row;
}

void Block::removeBlock()
{
	this->removeFromParent();
	blocks->eraseObject(this);
}

void Block::moveDown()
{
	row--;	//行号减一
	Size winSize = Director::getInstance()->getWinSize();
	runAction(Sequence::create(MoveBy::create(0.1f, Point(0, - winSize.height / 4)), 
		CallFunc::create([&]()
		{
			if (row < 0)	//行号小于0，移除块
			{
				this->removeBlock();
			}
		}), NULL));
}

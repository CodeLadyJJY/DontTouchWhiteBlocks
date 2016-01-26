#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class Block : public Sprite
{
public:
	static Block* createBlocks(Size block_size, Color3B block_color, string label, float label_size, Color3B label_color);
	virtual bool init(Size block_size, Color3B block_color, string label, float label_size, Color3B label_color);

	int getRow();						//获取行号
	void setRow(int row);				//设置行号
	static Vector<Block*> * getBlocks();//获取块向量
	void removeBlock();					//移除块
	void moveDown();					//块整体向下移动

private:
	int row;							//块的行号
	static Vector<Block*> *blocks;		//块向量
};

#endif

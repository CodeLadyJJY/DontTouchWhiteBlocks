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

	int getRow();						//��ȡ�к�
	void setRow(int row);				//�����к�
	static Vector<Block*> * getBlocks();//��ȡ������
	void removeBlock();					//�Ƴ���
	void moveDown();					//�����������ƶ�

private:
	int row;							//����к�
	static Vector<Block*> *blocks;		//������
};

#endif

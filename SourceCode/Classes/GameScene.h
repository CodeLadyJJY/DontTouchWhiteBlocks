#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
    static Scene* createScene();
	virtual bool init();
    CREATE_FUNC(GameScene);

	void moveDown();					//������
	virtual void update(float t);		//ʱ��ˢ��
	void startTimer();					//������ʱ��
	void endTimer();					//��ֹ��ʱ��
	void menuRestartCallBack(Ref* obj);	//���¿�ʼ
	void menuCloseCallBack(Ref* obj);	//�˳�

private:
	Size winSize;					//��Ϸ���ڴ�С
	Node *gameLayer;				//��Ϸ��
	Label *timeLabel;				//ʱ��Label
	int rowCount;					//������
	bool isShowEnd;					//�Ƿ���ʾ������
	bool isRunning;					//��Ϸ�Ƿ���������
	long startTime;					//��ʼʱ��

	void addStartLine();			//��ӿ�ʼ��
	void addEndLine();				//��ӽ�����
	void addNormalLine(int row);	//��������ڰ��У�rowΪ����к�
	void startGame();				//��ʼ��Ϸ
};

#endif

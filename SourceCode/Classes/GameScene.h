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

	void moveDown();					//块下移
	virtual void update(float t);		//时间刷新
	void startTimer();					//开启计时器
	void endTimer();					//终止计时器
	void menuRestartCallBack(Ref* obj);	//重新开始
	void menuCloseCallBack(Ref* obj);	//退出

private:
	Size winSize;					//游戏窗口大小
	Node *gameLayer;				//游戏层
	Label *timeLabel;				//时间Label
	int rowCount;					//总行数
	bool isShowEnd;					//是否显示结束行
	bool isRunning;					//游戏是否正在运行
	long startTime;					//开始时间

	void addStartLine();			//添加开始行
	void addEndLine();				//添加结束行
	void addNormalLine(int row);	//添加正常黑白行，row为块的行号
	void startGame();				//开始游戏
};

#endif

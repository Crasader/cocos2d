#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d::extension;

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void startGame();

	void autoStartGame(float dt);

	void getMusicState(cocos2d::Ref* pSender);

	void showHelpView();//��ʾ��������

	void buttonTouchEvent(Ref* pSender,Widget::TouchEventType type);

	void showQuit();

	void confirmQuit();

	void cancelQuit();

	void showMoreGame();

	void updateScene(float dt);

    CREATE_FUNC(StartScene);

private:
	ui::Button* helpButton;
	//Layer* quitDialog;//�˳�ȷ�Ͻ���
	Menu* moreGame;
	bool flag;
};

#endif

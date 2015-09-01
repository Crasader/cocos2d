#ifndef __GAME_GUI_LAYER_H__
#define __GAME_GUI_LAYER_H__
#include "cocos2d.h"
#include "GameSlioder.h" 

USING_NS_CC;

class GameGuiLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameGuiLayer);
	void updateShowScore();
	void updateShowTime();
private :
	void pauseGame();
	void initTime();
	void update(float dt);
	void gotoResult();
	float passTime;
	float totalTime;
	float countTime;
	void updateTime(float dt);
	LabelAtlas* playerScore;//��ҷ�����ʾ
	LabelAtlas* palyTime;//ʱ����ʾ
	GameSlioder* gameSlioder;
	bool gotoResultLayer;
};
#endif
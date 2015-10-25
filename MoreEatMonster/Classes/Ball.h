#pragma once

#include "cocos2d.h"
#include "GameData.h"

class Ball :public cocos2d::Sprite {
public:
	enum  BallState
	{
		Top = 0,		// ����������
		Buttom,		    // ����������
		Left,		   // ����������
		Right		  //  ����������
	};
public:
	virtual bool init();
	CREATE_FUNC(Ball);
	static Ball * create(const std::string & fileName);

	void update(float dt);
	int getBallState();
	void addBall();
	void setNextPosition();
	void setBallSpeed(int speed);
public:
	bool checkWidthBorder(float x);
	bool checkHeightBorder(float y);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Vec2 ballPosition;
	int ballState;
	int ballSpeed;

};

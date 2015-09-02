#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "FishManage.h"
#include "BulletManage.h"
#include "Turret.h"

USING_NS_CC;

class GameLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	void createTurret(int type);//����������������
	void addTouchEvent();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	//�����ӵ�
	void createFish(float dt);//������
	void shoot(float degree);//�����ӵ�
	float getTurretRotation(Point pos1,Point pos2);//��ȡ������Ҫ��ת�ĽǶ�
	void rotateTurret(float degree);//��ת����
	void update(float dt);
	Turret* myTurret;
};
#endif
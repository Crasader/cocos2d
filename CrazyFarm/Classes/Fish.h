#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"
#include "CircleBy.h"

using namespace cocos2d;

#define FISHTYPE_1 0
#define FISHTYPE_2 1
#define FISHTYPE_3 2
#define FISHTYPE_4 3
#define FISHTYPE_5 4
#define FISHTYPE_6 5
#define FISHTYPE_7 6
#define FISHTYPE_8 7

using namespace std;

class Fish :public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Fish);
	void initFish(int fishType);
	void move(int moveType);
private:
	int speed;//����ƶ��ٶ�
	int fishType;//�������
	int experience;//��ľ���ֵ
	int fishGold;//��Ľ�Ǯ
	float  rotation;//��ת�ĽǶ�
	string resoureName;//��Դ����
	string getSrcByType(int type);
	int getFishGoldByType(int type);
	int getFishExperienceByType(int type);
	float getFishSpeedByType(int type);
	void initFishAnim(string name, int startIndex);
	void moveFishStraight(float dt);//ֱ���ƶ�
	void moveFishCircle(float dt);//Բ���˶�
	void moveFishRandom(float dt);//����˶�
	Point getNextPostion(Point pos,float speed,float degree);
	bool checkOutBorder();
};

#endif
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

USING_NS_CC;

class Monster : public cocos2d::Node
{
public:
	Monster();
	~Monster();
	static Monster* create(int ID);
    bool init(int ID);
 
    /* ���뵽��ǰ���� */
    void joinToMap(Node* parent);

	/*��ȡ��ǰ�������ŵ��ڼ�֡*/
	int getCurrentFrame();

	void logic(float dt);
 
    CC_SYNTHESIZE(int, m_ID, ID);
    CC_SYNTHESIZE(int, m_iPosX, iPosX);
    CC_SYNTHESIZE(int, m_iPosY, iPosY);
    CC_SYNTHESIZE(Value, m_sModelPath, sModelPath);
private:
	float animTime;
	bool startAnim;
};

#endif 

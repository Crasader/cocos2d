#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#pragma once
#include "cocos2d.h"
#include "Player.h"//��ɫ�ļ���
#include "Def.h"
#include <vector>
#include "InfoLayer.h"

using namespace cocos2d;
using namespace std;
USING_NS_CC;
class GameLayer : public Layer
{
public:
 bool init();
 CREATE_FUNC(GameLayer);
 bool onTouchBegan(Touch *touch, Event *unused_event);
 Player* player;
 InfoLayer* gameInfo;
 Sprite *wall;
 CCTMXTiledMap *tileMap;//�����ͼ������
 CCTMXLayer *tileLay;//����
 CCTMXObjectGroup *tileObject;//����
 void timeCallBcak(float f);//��ͼ�����ƶ�
 void bobCallBcak(float f);//��ײ���
 void playerCallBcak(float f);//�ұ����ϰ������ƶ�
 void distanceCallBack(float f);
 SpriteBatchNode *m_batchNode;//����ש�黺���
 SpriteBatchNode *m_goldBatchNode;//��һ����
 SpriteBatchNode *m_wallBatchNode;//ǽ�ڻ����
 vector< Sprite* > m_Vector;//��ŵ�������
 vector< Sprite* > m_goldVector;//��Ž������
 vector< Sprite* > m_wallVector;//���ǽ������
 bool IscollWithUp();
 bool IscollWithDown();
 bool IscollWithRight();
 bool IscollWithLeft();
 bool IscollWithGold();
 bool IsDie();
 void DownLogic();
 void UpLogic();
 void RightLogic();
 void LeftLogic();
 void toResultScene(float dt);
};
#endif

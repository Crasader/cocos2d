#ifndef _SCROLLTEXT_H_
#define _SCROLLTEXT_H_
#include "cocos2d.h"

USING_NS_CC;
class ScrollText: public cocos2d::Node {
public:
	/**
	 @pragma  pMask ��Ҫ�������ֵľ���
	 @pragma  pMoveChild ��Ҫ�ƶ���Node
	 @pragma  otherChid ������Ҫ��ʾ��Node
	 */
	static ScrollText* create(cocos2d::Sprite* pMask, cocos2d::Label* pMoveChild,
			cocos2d::Label* otherChild, ...);
	/**
	 @pragma  isScroll �����Ƿ���Ҫ�Զ�����
	 @pragma  byWidth �����Ƿ���Ҫ���ݳ���������
	 PS��������ճ��������ã��򳤶�С�����ֳ��ȵĽ��������
	 */
	void setAutoScroll(bool isScroll, bool byWidth = false);
	CREATE_FUNC(ScrollText);
    CC_CONSTRUCTOR_ACCESS:
	ScrollText();
	virtual ~ScrollText();
	virtual bool init();
	virtual bool initWithDatas(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild);
	bool initClipper(cocos2d::Sprite* pMask, cocos2d::Label* pMoveChild);
	void update(float delta);
	void setpMaskString(std::string string);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	long getCurrentTime();

private:
	cocos2d::Label* _mLable;
	cocos2d::Sprite* pMask;
	cocos2d::Vector<Node*> _mNodes;
	bool _autoScroll;
	std::string marInfo;
	bool ishowDialog;
};
#endif

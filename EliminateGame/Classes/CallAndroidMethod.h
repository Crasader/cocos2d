#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	void Java_org_cocos2dx_cpp_PayService_callback();
	static CallAndroidMethod* getInstance();
	//TODO��ӷ���
	void eventToPay(int eventPoint);//����֧�����¼�
private:
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif

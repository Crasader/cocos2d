#ifndef _TASK_INFO_H_
#define _TASK_INFO_H_
#include <string>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class TaskInfo: public Node{
public:
	int id;//����ID
	std::string name;//��������
	std::string imageName;//����ͼƬ������
	vector<std::string> thingsId;//��������������ƷID
	int needNumber;//��Ҫ����Ʒ����
	int findNumber;
};
#endif
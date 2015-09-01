#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"
#include "TaskInfo.h"
#include "Materials.h"

using namespace cocos2d;

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	Vector<Materials*> myMaterials;//���������Ʒ
	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();
	Vector<TaskInfo*> getCurrentTask();
	void addTask(TaskInfo* task);
	void deleteTask(TaskInfo* task);
	int getRecord();
	int getLevel();
	void setLevel(int level);
	void cleanDatas();
	void setScore(int score);
	int  getScore();
	void setFindTimes(int score);
	int  getFindTimes();
	int  getReviveNum();//�������
	void  setReviveNum(int num);
	int  getLoginTimes();
	void setLoginTimes();
	int  getLastClikTime();
	void setLastClikTime(int clickTime);
	long getCurrentTime();
	int  getFinishTaskNum();
	void setFinishTaskNum();
	int  getCreatTaskNum();
	void setCreatTaskNum();
	int getPropFindNum();
	void setPropFindNum(int num);
	int getPropTimeNum();
	void setPropTimeNum(int num);
private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	Vector<TaskInfo*> tasks;
	int score;//��ǰ��Ϸ����
	int findTimes;
	int level;//�ؿ�
	int lastClikTime;
	int finishTaskNum;
	int createTaskNum;
};

#endif

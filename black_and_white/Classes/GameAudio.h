#ifndef GameAudio_H
#define GameAudio_H
#include "cocos2d.h"
#include "json\reader.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"
using  namespace cocos2d;
class GameAudio{
public:
	GameAudio();
	static GameAudio * getInstance();
	void  init();
	void prepare();
	void playsounds();
	void playerror();
public:
	static GameAudio*_instance;
	int music_index;//��¼����ǰ�����ĵڼ�������
	int currentMusic_Type;//0,1,2,3,4,5,6��Ӧ���ȣ�269��57��152��295��86��135��114 
};
#endif
#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

//������Ч��·��
#define BACKGORUND_MUSIC "music/bg_music.mp3"//��������
#define CLICK "music/click.ogg"//�����Ч


class Audio{
public:
	static Audio* getInstance();
	//���ű�����
	void playBGM(char* soundName);
	//������Ч
	void playSound(char* soundName);
	void prepare();
private:
	static Audio* m_instance;
};
#endif
#pragma  once
//������˶�״̬
const int STATE_PLAYER_RUN = 0;
const int STATE_PLAYER_JUMP = 1;
const int STATE_PLAYER_DOWN = 2;
const int STATE_PLAYER_STOP = 3;
const int STATE_PLAYER_DIE = 4;
//�����ٶȺͼ��ٶ�
const double DEFLAUT_SPEEDY = 4;
const double DEFLAUT_ACCE = 0.1;
//��ͼ���ƴ�С���ٶȣ�
const int MOVING_GAP = 8;
//���ﶯ������tag
const int TAG_RUN = 1;
const int TAG_JUMP = 2;
const int TAG_DOWN = 3;
//��������
const int PROP_NONE = 0;
const int PROP_SUPER = 1;
const int PROP_MAGNETIC = 2;
const int PROP_POTENTIAL = 3;

#define MUSIC_GOLD "gold.mp3"
#define MUSIC_TOUCH "touch.wav"
#define MUSIC_BACKGROUND "background.mp3"
#define MUSIC_JUMP "jump.mp3"

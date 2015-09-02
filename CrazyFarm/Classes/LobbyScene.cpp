#include "LobbyScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "Chinese.h"

Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();

	scene->addChild(layer);

	return scene;
}

bool LobbyScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    //add all fish plsit
	loadResource();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("lobby_bg.jpg");
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(lobby_bg,-1);
	//add statr menu to layer

	MenuItemImage* start_btn = MenuItemImage::create("start_game_normal.png","start_game_pressed.png",CC_CALLBACK_0(LobbyScene::startGame,this));
	Menu* start_game = Menu::create(start_btn,NULL);
	start_game->setPosition(visibleSize.width/2,visibleSize.height/4);
	this->addChild(start_game);

    //�����ʾ�ı�����
	Sprite* playerGold = Sprite::create("fish_gold.png");
	playerGold->setPosition(ccp(visibleSize.width-150,visibleSize.height-50));
	this->addChild(playerGold);
	//���������ʾ
	LabelAtlas* playerGoldNum = LabelAtlas::create("200", "player_gold_num.png", 14, 19, '0');
	playerGoldNum->setPosition(ccp(visibleSize.width - 120, visibleSize.height - 60));
	this->addChild(playerGoldNum);

	//��ҳ�ֵ��ť
	MenuItemImage* recharge_image = MenuItemImage::create("fish_gold.png", "fish_gold.png", CC_CALLBACK_0(LobbyScene::rechargeGold, this));
	Menu* recharge = Menu::create(recharge_image,NULL);
	recharge->setPosition(ccp(visibleSize.width -50, visibleSize.height - 50));
	this->addChild(recharge);

	//���ð�ť
	MenuItemImage* settting_img = MenuItemImage::create("btn_setting.png", "btn_setting.png", CC_CALLBACK_0(LobbyScene::showSettingLayer, this));
	Menu* settting = Menu::create(settting_img, NULL);
	settting->setPosition(ccp(50,100));
	this->addChild(settting);

	//�����ͼ
	auto bgk = Sprite::createWithSpriteFrameName("input_bg.png");
	bgk->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	addChild(bgk);

	// �����ϵ�����
	auto bgv = Sprite::createWithSpriteFrameName("bt_paste.png");
	bgv->setPosition(Vec2(visibleSize.width / 2-150, visibleSize.height / 2 + 150));
	addChild(bgv);


	//���� Ӯȡ����
	auto post = Label::create();
	post->setSystemFontSize(24);
	post->setString(ChineseWord("post"));
	post->setPosition(Vec2(visibleSize.width/2+50,visibleSize.height/2+150));
	addChild(post);


	//���ϵͳ���ؼ�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO չʾ�˳�����
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void LobbyScene::startGame(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,LevelScene::create()));
}

void LobbyScene::rechargeGold(){
	//TODO �����Ʒѵ�
}

void LobbyScene::showSettingLayer(){
	//TODO �������ý���
}


void LobbyScene::loadResource(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_5.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_8.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_10.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_11.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_14.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish_frame_16.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("batch_frame_bullet.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gun_frame.plist");
	//add 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gift_frame.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_scene_frame.plist");
}
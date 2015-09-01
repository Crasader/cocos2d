#include "GameView.h"
#include "GameData.h"
#include "GameState.h"
#include "TaskMenu.h"
#include "TaskInfoUtil.h"
#include "BottomMenu.h"
#include "CallAndroidMethod.h"
#include "GuideInfoUtil.h"
#include "PositionInfoUtil.h"
#include "GameParticle.h"
#include "Audio.h"

#define THING_SIZE (80)
#define OFFSET_X (23)
#define OFFSET_Y (10)
#define THING_NUM_X (20)
#define THING_NUM_Y (4)

bool GameView::init() {
	if (!Layer::init()) {
		return false;
	}
	firstClick = true;
	isGuideTime = false;
	slide = nullptr;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	///��������
	if (GAMEDATA::getInstance()->getLoginTimes() == 1){
		createGuideMaterials();
	}
	else{
		createMaterials();//����������״̬�����������Ʒ
	}
	scheduleUpdate();
	//���ٲ��ҵı��
	quickFindResult = Sprite::create("findresult.png");
	quickFindResult->setScale(0.8);
	quickFindResult->setAnchorPoint(Point(0.5, 0.5));
	quickFindResult->setVisible(false);
	this->addChild(quickFindResult);
	//���õ���¼�����
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameView::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameView::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameView::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

void GameView::update(float dt){
	if (GAMESTATE::getInstance()->isUsePropFind()){
		GAMESTATE::getInstance()->setUsePropFind(false);
		BottomMenu::getInstance()->updatePropNum();
		schedule(schedule_selector(GameView::quickfind), 0.1f, 0, 0);
	}
	if (GAMESTATE::getInstance()->isUsePropTime()){
		GAMESTATE::getInstance()->setUsePropTime(false);
		showPropTimeAnim();
		BottomMenu::getInstance()->updatePropNum();

	}
	if (GAMESTATE::getInstance()->getIsGuide()){
		showPlayerGuide();
		isGuideTime = true;
		GAMESTATE::getInstance()->setIsGuide(false);
	}
}

void GameView::quickfind(float dt){
	//���һ���,������Ҫ�������ٵ���Ʒ,������˳������
	//���ҵ�ʱ��ͽ�ԭ���뵱ǰҳ�������Ʒ���ȱ��ҵ�
	GAMEDATA* data = GAMEDATA::getInstance();
	Vector<TaskInfo*> taskList = data->getCurrentTask();//��ȡ�����б�
	//��ȡ��Ҫ�������ٵ�����
	if (taskList.empty() || taskList.size() > 3){
		return;
	}
	//CCLOG("task list size = %d",taskList.size());
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("task list size = %d", taskList.size());
#endif
	TaskInfo* mix = taskList.at(0);
	Vector<TaskInfo*>::iterator beg = taskList.begin();
	Vector<TaskInfo*>::iterator end = taskList.end();
	for (Vector<TaskInfo*>::const_iterator it = beg; it != end; ++it){
		TaskInfo* info = *it;
		if ((info->needNumber - info->findNumber) < (mix->needNumber - mix->findNumber)){
			mix = info;
		}
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//������Ʒ��������������Ʒ����һ��
	Vector<Materials*> result;
	//��ȡ������Ҫ����ƷID
	for (std::string id : mix->thingsId){
		for (Materials* mat : data->myMaterials){
			if (mat->getMaterialsName().compare(id) == 0){
				result.pushBack(mat);
			}
		}
	}
	//CCLOG("quick find result1 = %d",result.size());
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("quick find result1 = %d", result.size());
#endif
	if (result.empty()){
		//�޵���Ƥ���У�Ϊ����������ɵĲ���ѧ����������Ʒ�Ѿ����������������ˣ������´���
		//step1:��ȡ��Ļ֮�������һ����Ʒ
		Vector<Materials*> changeList;
		auto cur_x = abs(this->getPosition().x);
		for (Materials* mat : data->myMaterials){
			if (mat->getDisPosition()->x<cur_x || mat->getDisPosition()->x>(cur_x + visibleSize.width)){
				changeList.pushBack(mat);
			}
		}
		//CCLOG("change the target to solve this promble1 = %d",changeList.size());
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		CCLog("change the target to solve this promble1 = %d", changeList.size());
#endif
		//Step2 �������Ʒת��ΪĿ����Ʒ
		int index = changeList.size() - 1;
		Materials* changeTarget = changeList.at(random(1, index));
		changeTarget->removeAllChildren();
		changeTarget->changeMaterials(mix->thingsId.at(0));
		result.pushBack(changeTarget);
		//CCLOG("change the target to solve this promble2");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		CCLog("change the target to solve this promble2");
#endif
	}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("quick find result2 = %d", result.size());
#endif
	//CCLOG("quick find result2 = %d",result.size());
	Materials* mixMat = result.at(0);
	if (result.size() > 1){
		for (Materials* me : result){
			//��ȡ����ǰ��Ļ�����������Ʒ
			int pos_x = abs(this->getPosition().x) + visibleSize.width / 2;//��ǰ��Ļ���ĵĺ�����
			if (mixMat->getDisPosition()->x - pos_x > me->getDisPosition()->x - pos_x){
				mixMat = me;
			}
		}
	}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("show quick find flag");
	CCLog("result X = %f",mixMat->getDisPosition()->x);
	CCLog("result Y = %f", mixMat->getDisPosition()->y);
#endif
	//CCLOG("show quick find flag");
	//CCLOG("result X = %f",mixMat->getDisPosition()->x);
	//CCLOG("result Y = %f",mixMat->getDisPosition()->y);
	//�ҵ�����Ʒ��ӱ��
	quickFindResult->setPosition(ccp(mixMat->getDisPosition()->x, mixMat->getDisPosition()->y));
	quickFindResult->setVisible(true);
	//����ʹ�ҵ�����Ʒ������Ļ�м���Ҫ��ƫ����
	Point matPos = Point(mixMat->getDisPosition()->x, mixMat->getDisPosition()->y);
	float distance = matPos.x - (abs(this->getPosition().x) + visibleSize.width / 2);
	//CCLOG("need move distance = %f",distance);
	Point prePos = this->getPosition();
	Point curPos = Point(prePos.x - distance, prePos.y);
	if (curPos.x > 0){
		this->setPosition(0, 0);
		return;
	}
	else if (curPos.x < -1200){
		this->setPosition(-1200, 0);//������Ļ�Ŀ��
		return;
	}
	//CCLOG("gameview curPos = %f",curPos.x);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("gameview curPos = %f", curPos.x);
#endif
	this->setPosition(curPos);
	Audio::getInstance()->playSound(QUICKFIND);
	}


void GameView::createMaterials(){
	map<int, Point*> pos_map = PositionInfoUtil::getInstance()->getPositionList();
	map<int, Point*>::iterator it;
	for (it = pos_map.begin(); it != pos_map.end(); ++it){
		singleMaterial(it->first);
	}
}

void GameView::createGuideMaterials(){
	ValueVector idList = GuideInfoUtil::getInstance()->getGuideInfo()->idList;
	map<int, Point*> pos_map = PositionInfoUtil::getInstance()->getPositionList();
	map<int, Point*>::iterator it;
	for (it = pos_map.begin(); it != pos_map.end(); ++it){
		Materials* m = Materials::create();
		m->setMaterialsID(idList.at(it->first).asInt(), it->second);
		m->setAnchorPoint(Point::ANCHOR_MIDDLE);
		m->setTag(it->first);
		this->addChild(m);
		GAMEDATA::getInstance()->myMaterials.pushBack(m);
	}
}

void GameView::singleMaterial(int index){
	Materials* m = Materials::create();
	Point* pos = PositionInfoUtil::getInstance()->getPositionById(index);
	int range = random(100, 17500);
	if (GAMESTATE::getInstance()->getIsGuide()){
		range = 3000;
	}
	m->setMaterialsID(range / 100, pos);
	m->setAnchorPoint(Point::ANCHOR_MIDDLE);
	m->setTag(index);
	this->addChild(m);
	GAMEDATA::getInstance()->myMaterials.pushBack(m);
}


bool GameView::onTouchBegan(Touch *touch, Event  *event)
{

	if (GAMESTATE::getInstance()->getGamePause()){
		acceptTouch = false;//������ܵ��ʱ��
	}
	else{
		acceptTouch = true;
	}
	touchDownPoint = touch->getLocation();
	touchCurPoint = touchDownPoint;
	return true;
}

void GameView::onTouchMoved(Touch *touch, Event  *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + touchPoint.x - touchCurPoint.x;
	Point posPoint = Point(currX, getPositionY());
	auto dis = fabsf(touchPoint.x - touchCurPoint.x);
	if (currX > 0){
		this->setPosition(dis / 3, 0);
		return;
	}
	else if (currX < -1200){
		this->setPosition(-1200 - dis / 3, 0);
		return;
	}
	this->setPosition(posPoint);
	touchCurPoint = touchPoint;
	if (slide!= nullptr && slide->isVisible() && isGuideTime){
		slide->setPosition(275 + abs(this->getPosition().x), 340);
	}
	
}

void GameView::onTouchEnded(Touch *touch, Event  *event)
{
	auto pos = getPosition().x;
	if (pos>0){
		this->setPosition(0, 0);
		return;
	}
	else if (pos < -1200){
		this->setPosition(-1200, 0);
		return;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	touchUpPoint = touch->getLocation();
	auto dis = touchUpPoint.getDistance(touchDownPoint);
	Materials* deleteMaterial = nullptr;
	if (dis < THING_SIZE / 3){
		auto vec = GAMEDATA::getInstance()->getCurrentTask();
		GAMEDATA::getInstance()->setLastClikTime(GAMEDATA::getInstance()->getCurrentTime());
		//���������ж�
		Vector<Materials*> maters = GAMEDATA::getInstance()->myMaterials;//��ȡ˵�е���Ʒ
		bool find = false;
		TaskInfo* canUpdateTask = nullptr;//��Ҫ���µ�����
		for (Materials* mater : maters){
			if (mater->onTouchBegan(touch, event, this->getPosition())){
				quickFindResult->setVisible(false);//���������Ʒ���رտ��ٲ��ҵ���ʾ
				//ʱ������Ԫ�ش���
				if (mater->isSpecial()){
					deleteMaterial = mater;
					find = true;
					break;
				}
				//һ��Ԫ�صĴ���
				for (TaskInfo* ta : vec){
					for (std::string v : ta->thingsId){
						if (v.compare(mater->getMaterialsName()) == 0){
							deleteMaterial = mater;
							canUpdateTask = ta;
							find = true;
							break;
						}
					}
				}
				if (acceptTouch&&!find){
					Audio::getInstance()->playSound(SELECTERROR);
					acceptTouch = false;
					addTimeAnim(-3, Point(mater->getDisPosition()->x, mater->getDisPosition()->y));//ʱ��۳�����
					Sprite* wrongSprite = Sprite::create("fail.png");
					wrongSprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
					wrongSprite->setScale(0.6);
					wrongSprite->setPosition(mater->getDisPosition()->x, mater->getDisPosition()->y);
					mater->addChild(wrongSprite);
					auto delay = DelayTime::create(0.2f);
					CallFunc* createC = CallFunc::create([=]() {
						wrongSprite->removeFromParentAndCleanup(true);
						acceptTouch = true;
					});
					Sequence* action = Sequence::create(delay, createC, NULL);
					wrongSprite->runAction(action);
				}
				break;
			}
		}

	
		//ÿһ�ε��ֻ���Ƴ�һ����Ʒ
		if (acceptTouch &&nullptr != deleteMaterial){
			if (deleteMaterial->isSpecial()){
				Audio::getInstance()->playSound(SELECTTIME);
			}
			else{
				Audio::getInstance()->playSound(SELECTCORRECT);
			}
			acceptTouch = false;
			//���һ���������һ��
			GAMEDATA::getInstance()->setScore(GAMEDATA::getInstance()->getScore() + 1);
			BottomMenu::getInstance()->updateScore();
			//�����ҵ�����Ʒ����ʱ��
			int ti = addTime(deleteMaterial->isSpecial());
			addTimeAnim(ti, Point(deleteMaterial->getDisPosition()->x, deleteMaterial->getDisPosition()->y));
			//��ȡ������Ʒ��λ�ñ��
			newIndex = deleteMaterial->getTag();
			//�Ƴ��ɵ���Ʒ
			GAMEDATA::getInstance()->myMaterials.eraseObject(deleteMaterial);
			deleteMaterial->removeAllChildrenWithCleanup(true);
			deleteMaterial->removeFromParentAndCleanup(true);//�Ƴ���Ʒ
			//����µ���Ʒ
			auto delay = DelayTime::create(0.1);
			CallFunc* createC = CallFunc::create([=]() {
				singleMaterial(newIndex);
				acceptTouch = true;
				if (nullptr != canUpdateTask){
					//��������
					TaskMenu::getInstance()->refreshTask(canUpdateTask);
				}
			});
			Sequence* action = Sequence::create(delay, createC, NULL);
			runAction(action);
		}

		if (find && isGuideTime){
			if (firstClick){
				pStencil->clear();
				pStencil->drawSolidCircle(ccp(1660, 350), 50, 0, 180, ccc4f(1, 0, 0, 1));
				circle->setPosition(1660, 350);
				slide->setVisible(true);
				slide->setPosition(375, 340);
				firstClick = false;
			}
			else{
				pClip->setVisible(false);
				pStencil->setVisible(false);
				pClip->removeFromParent();
				isGuideTime = false;
			}

		}
	}
}

int GameView::addTime(bool isSpecial){
	int time = 0;
	if (isSpecial){
		int rand = random(1, 100);
		if (rand <= 20){
			time = 1;
		}
		else if (rand > 20 && rand <= 70){
			time = 2;
		}
		else if (rand > 70 && rand <= 85){
			time = 3;
		}
		else if (rand > 85 && rand <= 95){
			time = 4;
		}
		else {
			time = 5;
		}
	}
	else{
		time = 1;
	}
	return time;
}

int GameView::getIndexByPosition(Point pos){
	int x = (pos.x - OFFSET_X) / (OFFSET_X + THING_SIZE);
	int y = (pos.y - 64) / (OFFSET_Y + THING_SIZE);
	return x*THING_NUM_Y + y;
}

Point GameView::getPositionByIndex(int index){
	int x = index / THING_NUM_Y;
	int y = index - x*THING_NUM_Y;
	return Point(OFFSET_X*(x + 1) + THING_SIZE*x, 64 + OFFSET_Y*y + THING_SIZE*y);
}

void GameView::addTimeAnim(int time, Point pos){
	Sprite* animSprite = Sprite::create();
	animSprite->setPosition(pos);
	this->addChild(animSprite);

	Sprite* symbol;
	if (time > 0){
		symbol = Sprite::create("time_plus.png");
	}
	else{
		symbol = Sprite::create("time_minus.png");
	}
	symbol->setAnchorPoint(Point(0, 0));
	symbol->setPosition(0, 0);
	animSprite->addChild(symbol);

	LabelAtlas* time_num = LabelAtlas::create(cocos2d::String::createWithFormat("%d", abs(time))->_string, "time_number.png", 15, 30, '0');
	time_num->setAnchorPoint(Point(0, 0));
	time_num->setPosition(32, 0);
	animSprite->addChild(time_num);

	Sprite* second = Sprite::create("second.png");
	second->setAnchorPoint(Point(0, 0));
	second->setPosition(48, 0);
	animSprite->addChild(second);

	auto move = MoveTo::create(0.5, Point(pos.x, pos.y + 100));
	CallFunc* removeC = CallFunc::create([=](){
		BottomMenu::getInstance()->plusGameTime(time);
		animSprite->removeFromParent();
	});
	auto sequence = Sequence::create(move, removeC, NULL);
	animSprite->runAction(sequence);
}

//��������
void GameView::showPlayerGuide(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	bg = LayerColor::create(ccc4(0, 0, 0, 125));
	bg->setContentSize(CCSizeMake(2000, visibleSize.height));
	pClip = CCClippingNode::create();
	pClip->setInverted(true);
	pClip->addChild(bg);
	this->addChild(pClip, 5);
	pStencil = CCDrawNode::create();
	pStencil->drawSolidCircle(ccp(375, 240), 50, 0, 180, ccc4f(1, 0, 0, 1));
	pClip->setStencil(pStencil);
	circle = Sprite::create("guide_circle.png");
	circle->setPosition(375, 240);
	bg->addChild(circle);
	slide = Sprite::create("guide_slide.png");
	slide->setVisible(false);
	bg->addChild(slide);
	//EventListenerTouchOneByOne* touchEvent = EventListenerTouchOneByOne::create();
	//touchEvent->onTouchBegan = [=](Touch* touch,Event* ev){
	//	Rect rect = Rect(340,205,410,280);
	//	if(rect.containsPoint(touch->getLocation())){
	//		pStencil->clear();
	//		pStencil->drawSolidCircle(ccp(1660,350), 50, 0,180,ccc4f(1,0,0,1));
	//		circle->setPosition(1660,350);
	//		slide->setVisible(true);
	//		slide->setPosition(375,340);
	//	}
	//	slide->setPosition(300+abs(this->getPosition().x),340);
	//	Rect rect2 = Rect(1610,300,1710,400);
	//	if(rect2.containsPoint(Point(touch->getLocation().x+abs(this->getPosition().x),touch->getLocation().y))){
	//		pClip->removeFromParent();
	//		_eventDispatcher->removeEventListener(touchEvent);
	//	}
	//	return false;
	//};
	//touchEvent->onTouchMoved = [=](Touch* touch,Event* ev){
	//	slide->setPosition(375+this->getPosition().x,340);
	//};
	//touchEvent->onTouchEnded = [=](Touch* touch,Event* ev){
	//	slide->setPosition(375+this->getPosition().x,340);
	//	if(abs(this->getPosition().x)>1200){
	//		this->setPosition(-1200,0);//������Ļ�Ŀ��
	//	}
	//};
	//_eventDispatcher->addEventListenerWithFixedPriority(touchEvent, -128);
}


void GameView::showPropTimeAnim(){
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* animSprite = Sprite::create();
	animSprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
	animSprite->setPosition(visibleSize.width / 2 - 60 + abs(this->getPosition().x), visibleSize.height / 2);
	this->addChild(animSprite);

	Sprite* symbol = Sprite::create("time_plus.png");
	symbol->setAnchorPoint(Point::ANCHOR_MIDDLE);
	symbol->setPosition(16, 0);
	animSprite->addChild(symbol);

	LabelAtlas* time_num = LabelAtlas::create(cocos2d::String::createWithFormat("%d", PROPPLUSTIME)->_string, "time_number.png", 15, 30, '0');
	time_num->setAnchorPoint(Point::ANCHOR_MIDDLE);
	time_num->setPosition(42, 0);
	animSprite->addChild(time_num);

	Sprite* second = Sprite::create("second.png");
	second->setAnchorPoint(Point::ANCHOR_MIDDLE);
	second->setPosition(72, 0);
	animSprite->addChild(second);

	auto scale = ScaleTo::create(0.5f, 2.0f);
	CallFunc* removeC = CallFunc::create([=](){
		showGameParticleEffect(1, Point(visibleSize.width / 2, visibleSize.height / 2), this);
		BottomMenu::getInstance()->plusGameTime(PROPPLUSTIME);
		animSprite->removeFromParent();

	});
	auto sequence = Sequence::create(scale, removeC, NULL);
	animSprite->runAction(sequence);
}
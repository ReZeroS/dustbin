#include "StartScene.h"
#include "GameDefine.h"
#include "GameScene.h"


Scene* StartScene::createScene(){
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init(){
	if (!Layer::init()){
		return false;
	}

	//back_ground.jpg
	auto sprite = Sprite::create("back_ground.jpg");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT/2));

	this->addChild(sprite);


	int iFrameNum = 375;
	SpriteFrame* frame = NULL;
	
	Vector <SpriteFrame*> frameVec;
	for (int i = 1; i <= iFrameNum; i++){
		frame = SpriteFrame::create(StringUtils::format("part/link_start (%d).png", i), Rect(0, 0, GAME_SCREEN_HEIGHT, GAME_SCREEN_WIDTH));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setDelayPerUnit(0.045f);

	action = Animate::create(animation);
	action->retain();

	auto startItem = MenuItemImage::create("start_btn0.png", "start_btn1.png", 
		CC_CALLBACK_1(StartScene::menuStartCallBack, this));
	startItem->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT/4));
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);
	return true;

}


void StartScene::menuStartCallBack(Ref* pSender){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("linkstr.ogg", true);
	//replace scene
	auto callbackFunc = [&](){
		action->release();
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);//TransitionCrossFade TransitionMoveInT::create(2.0f, scene)
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	//antimation
	Sprite* runSp = Sprite::create("part/link_start (1).png");
	runSp->setRotation(-90.0f);
	runSp->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(runSp);
	
	auto actions = Sequence::create(action, callFunc, NULL);
	
	
	runSp->runAction(actions);

}


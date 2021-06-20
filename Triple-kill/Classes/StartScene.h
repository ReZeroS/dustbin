#ifndef _START_SCENE_H_
#define _START_SCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class StartScene :public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	//virtual void onExit();

	CREATE_FUNC(StartScene);
	void menuStartCallBack(Ref* pSender);


private:
	Animate* action;
};


#endif
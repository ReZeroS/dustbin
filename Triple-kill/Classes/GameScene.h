#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "GameDefine.h"
#include "SpriteShape.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameScene :public cocos2d::Layer{
public:
	//base function
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	
public:
	void initMap();//init map
	void createSprite(int row, int col);
public:
	Point PositionOfItem(int row, int col);
public:
	void update(float dt);
	void checkaAndRemoveSprite();
private:
	SpriteShape* map[ROWS][COLS];
public:
	void getRowChain(SpriteShape* spr, std::list<SpriteShape*>&chainList);
	void getColChain(SpriteShape* spr, std::list<SpriteShape*>&chainList);

	void markRemove(SpriteShape* spr);
	void removeSprite(SpriteShape* spr);
	void explodeSprite(SpriteShape* spr);
private:
	bool isFillSprite;
	bool isAction;
	bool isTouchEnd;
public:
	void actionEndCallback(Node* node);
	void fillSprite();
	bool onTouchBegan(Touch* touch, Event* unused);
	SpriteShape* spriteOfPoint(Point* location);
	void onTouchMoved(Touch* touch, Event* unused);
	void swapSprite();
private:
	SpriteShape* staSprite;
	SpriteShape* endSprite;

private:
	int m_score;
	int m_time;
public:
	void myClock(float dt);
	void gameOver(Node* node);
};


#endif
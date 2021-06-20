#include "GameScene.h"
#include "GameDefine.h"
#include "StartScene.h"

Scene* GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init(){
	if (!Layer::init()){
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist");

	auto sprite = Sprite::create("game_ground.jpg");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT/2));
	this->addChild(sprite);

	initMap();
	this->scheduleUpdate();

	m_score = 0;
	m_time = 198;

	TTFConfig config("fonts/haibaoti.ttf", 30);
	auto labelScore = Label::createWithTTF(config, StringUtils::format("Score:%d", m_score));
	labelScore->setPosition(Point(720, 320));
	labelScore->setTag(10);
	this->addChild(labelScore);


	auto labelTime = Label::createWithTTF(config, StringUtils::format("Time:%d", m_time));
	labelTime->setPosition(Point(720, 360));
	labelTime->setTag(11);
	this->addChild(labelTime);
	this->schedule(schedule_selector(GameScene::myClock), 1.0f);

	//key monitor register
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music_bg.ogg", true);
	return true;

}

void GameScene::initMap(){
		for (int r = 0; r < ROWS; ++r){
			for (int c = 0; c < COLS; ++c){
				createSprite(r, c);
			}
		}
}

void GameScene::createSprite(int row, int col){

	SpriteShape* spr = SpriteShape::create(row, col);
	Point endPosition = PositionOfItem(row, col);
	Point startPosition = Point(endPosition.x, endPosition.y+GAME_SCREEN_HEIGHT/2);
	spr->setPosition(startPosition);
	float speed = startPosition.y / (1.5*GAME_SCREEN_HEIGHT);
	spr->runAction(MoveTo::create(speed, endPosition));
	this->addChild(spr);
	spr->setRow(row);
	spr->setCol(col);
	map[row][col] = spr;

}

Point GameScene::PositionOfItem(int row, int col){
	float x = (col + 1) * SPRITE_WIDTH + BODER_HEIGHT+120;
	float y = (row + 1) * SPRITE_WIDTH + BODER_HEIGHT;

	return Point(x, y);
}

void GameScene::update(float dt){
	if (isAction){
		isAction = false;
		for (int r = 0; r < ROWS; r++){
			for (int c = 0; c < COLS; c++){
				SpriteShape* spr = map[r][c];
				///如果正在运动
				if (spr && spr->getNumberOfRunningActions() > 0){
					isAction = true;
					isTouchEnd = false;
				}
			}
		}
	}
	else{
		isTouchEnd = true;
		if (isFillSprite){
			fillSprite();
			isFillSprite = false;
		}
		else{
			checkaAndRemoveSprite();
		}
	}
	Label* labelScore = (Label*) this->getChildByTag(10);
	labelScore->setString(StringUtils::format("Score:%d", m_score));
}

void GameScene::checkaAndRemoveSprite(){
	SpriteShape* spr;
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			spr = map[r][c];
			if (!spr){
				continue;
			}
			if (spr->getIsNeedRemove()){
				continue;
			}
			//先遍历上下相邻糖果，放在list
			std::list<SpriteShape*> colChainList;
			getColChain(spr, colChainList);

			//先遍历左右相邻糖果，放在list
			std::list<SpriteShape*> rowChainList;
			getRowChain(spr, rowChainList);

			std::list<SpriteShape*> &longerList = colChainList.size()>rowChainList.size() ? colChainList : rowChainList;
			if (longerList.size() < 3){
				continue;
			}

			for (auto itList = longerList.begin(); itList != longerList.end(); ++itList){
				spr = (SpriteShape*)*itList;
				if (!spr){
					continue;
				}
				markRemove(spr);
			}
		}
	}

	removeSprite(spr);
}

void GameScene::getColChain(SpriteShape* spr, std::list<SpriteShape*>&chainList)
{
	chainList.push_back(spr);
	//向上查找
	int neighborRow = spr->getRow() - 1;
	while (neighborRow >= 0){
		SpriteShape* neighborSprite = map[neighborRow][spr->getCol()];

		if (neighborSprite && neighborSprite->getImgIndex() == spr->getImgIndex() && !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborRow--;
		}
		else {
			break;
		}
	}

	//向下查找
	neighborRow = spr->getRow() + 1;
	while (neighborRow < ROWS){
		SpriteShape* neighborSprite = map[neighborRow][spr->getCol()];

		if (neighborSprite && neighborSprite->getImgIndex() == spr->getImgIndex() && !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborRow++;
		}
		else {
			break;
		}
	}

}

void GameScene::getRowChain(SpriteShape* spr, std::list<SpriteShape*>&chainList){
	chainList.push_back(spr);
	//向左查找
	int neighborCol = spr->getCol() - 1;
	while (neighborCol >= 0){
		SpriteShape* neighborSprite = map[spr->getRow()][neighborCol];

		if (neighborSprite && neighborSprite->getImgIndex() == spr->getImgIndex() && !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborCol--;
		}
		else {
			break;
		}
	}

	//向右查找
	neighborCol = spr->getCol() + 1;
	while (neighborCol < COLS){
		SpriteShape* neighborSprite = map[spr->getRow()][neighborCol];

		if (neighborSprite && neighborSprite->getImgIndex() == spr->getImgIndex() && !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborCol++;
		}
		else {
			break;
		}
	}
}

void GameScene::markRemove(SpriteShape* spr){
	if (spr->getIsNeedRemove()){
		return;
	}
	spr->setIsNeedRemove(true);
}

void GameScene::removeSprite(SpriteShape* spr){
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			spr = map[r][c];
			if (!spr){
				continue;
			}
			if (spr->getIsNeedRemove()){
				isFillSprite = true;
				explodeSprite(spr);

			}
		}
	}
}

void GameScene::explodeSprite(SpriteShape* spr){
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music_explode.wav", false);
	isAction = true;
	isTouchEnd = false;
	spr->runAction(Sequence::create
		(ScaleTo::create(0.2f, 0.1),
		CallFuncN::create(CC_CALLBACK_1(GameScene::actionEndCallback, this)),
		NULL));

}

void GameScene::actionEndCallback(Node* node){
	SpriteShape* spr = (SpriteShape*)node;
	spr->removeFromParent();
	map[spr->getRow()][spr->getCol()] = NULL;
	m_score += 30;
}

void GameScene::fillSprite(){
	int colRemoveNum[10];
	SpriteShape* spr = NULL;
	for (int c = 0; c < COLS; c++){
		int removeSpriteOfCol = 0;
		//从底向上遍历
		for (int r = 0; r < ROWS; r++){
			spr = map[r][c];
			if (spr == NULL){
				removeSpriteOfCol++;
			}
			else{//下面有空的
				if (removeSpriteOfCol > 0){
					int newRow = r - removeSpriteOfCol;
					map[newRow][c] = spr;
					map[r][c] = NULL;
					Point startPosition = spr->getPosition();
					Point endPosition = PositionOfItem(newRow, c);
					float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT * 3;
					spr->stopAllActions();
					spr->runAction(CCMoveTo::create(speed, endPosition));

					spr->setRow(newRow);
				}
			}
		}
		colRemoveNum[c] = removeSpriteOfCol;
	}
	for (int c = 0; c < COLS; c++){
		for (int r = ROWS - colRemoveNum[c]; r < ROWS; r++)
		{
			createSprite(r, c);
		}
	}
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused){
	staSprite = NULL;
	endSprite = NULL;
	if (isTouchEnd)
	{
		auto location = touch->getLocation();
		staSprite = spriteOfPoint(&location);
	}
	return isTouchEnd;
}

SpriteShape* GameScene::spriteOfPoint(Point* location){
	SpriteShape* spr = NULL;
	Rect rect = Rect(0, 0, 0, 0);
	Size sz;
	sz.height = SPRITE_WIDTH;
	sz.width = SPRITE_WIDTH;
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			spr = map[r][c];
			if (spr){
				rect.origin.x = spr->getPositionX() - (SPRITE_WIDTH / 2);
				rect.origin.y = spr->getPositionY() - (SPRITE_WIDTH / 2);

				rect.size = sz;
				if (rect.containsPoint(*location)){
					return spr;
				}
			}
		}
	}

}

void GameScene::onTouchMoved(Touch* touch, Event* unused){
	if (!staSprite || !isTouchEnd){
		return;
	}
	int row = staSprite->getRow();
	int col = staSprite->getCol();

	auto location = touch->getLocation();
	auto halfSpriteWidth = SPRITE_WIDTH / 2;
	auto halfSpriteHeight = SPRITE_WIDTH / 2;

	auto upRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
		staSprite->getPositionY() + halfSpriteHeight + BODER_HEIGHT,
		SPRITE_WIDTH, SPRITE_WIDTH);
	//判断向上是否移动到上方的糖果中
	if (upRect.containsPoint(location)){
		++row;
		if (row < ROWS){
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}
	auto downRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
		staSprite->getPositionY() - halfSpriteHeight * 3 - BODER_HEIGHT,
		SPRITE_WIDTH, SPRITE_WIDTH);

	//判断向下是否移动到下方的糖果中
	if (downRect.containsPoint(location)){
		--row;
		if (row >= 0){
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}
	auto leftRect = Rect(staSprite->getPositionX() - halfSpriteWidth * 3 - BODER_HEIGHT,
		staSprite->getPositionY() - halfSpriteHeight,
		SPRITE_WIDTH, SPRITE_WIDTH);
	//判断向左是否移动到左方的糖果中
	if (leftRect.containsPoint(location)){
		--col;
		if (col >= 0){
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}
	auto rightRect = Rect(staSprite->getPositionX() + halfSpriteWidth + BODER_HEIGHT,
		staSprite->getPositionY() - halfSpriteHeight,
		SPRITE_WIDTH, SPRITE_WIDTH);
	//判断向右是否移动到右方的糖果中
	if (rightRect.containsPoint(location)){
		++col;
		if (col < COLS){
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}

}

void GameScene::swapSprite(){
	isAction = true;
	isTouchEnd = false;

	if (!staSprite || !endSprite){
		return;
	}
	Point posOfSrc = staSprite->getPosition();
	Point posOfDest = endSprite->getPosition();

	float time = 0.2;

	map[staSprite->getRow()][staSprite->getCol()] = endSprite;
	map[endSprite->getRow()][endSprite->getCol()] = staSprite;

	int tempRow = staSprite->getRow();
	int tempCol = staSprite->getCol();
	staSprite->setRow(endSprite->getRow());
	staSprite->setCol(endSprite->getCol());
	endSprite->setRow(tempRow);
	endSprite->setCol(tempCol);

	//判断移动后是否有糖果可以消除
	std::list<SpriteShape*> colChainListOfFirst;
	getColChain(staSprite, colChainListOfFirst);

	std::list<SpriteShape*> rowChainListOfFirst;
	getRowChain(staSprite, rowChainListOfFirst);

	std::list<SpriteShape*> colChainListOfSecond;
	getColChain(staSprite, colChainListOfSecond);

	std::list<SpriteShape*> rowChainListOfSecond;
	getRowChain(staSprite, rowChainListOfSecond);

	if (colChainListOfFirst.size() >= 3
		|| rowChainListOfFirst.size() >= 3
		|| colChainListOfSecond.size() >= 3
		|| rowChainListOfSecond.size() >= 3)
	{
		staSprite->runAction(MoveTo::create(time, posOfDest));
		endSprite->runAction(MoveTo::create(time, posOfSrc));
		return;
	}
	//不可移除， 移动后移回
	map[staSprite->getRow()][staSprite->getCol()] = endSprite;
	map[endSprite->getRow()][endSprite->getCol()] = staSprite;

	tempRow = staSprite->getRow();
	tempCol = staSprite->getCol();
	staSprite->setRow(endSprite->getRow());
	staSprite->setCol(endSprite->getCol());
	endSprite->setRow(tempRow);
	endSprite->setCol(tempCol);

	staSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfDest),
		MoveTo::create(time, posOfSrc)
		, NULL));

	endSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfSrc),
		MoveTo::create(time, posOfDest)
		, NULL));
}

void GameScene::myClock(float dt){
	m_time--;
	if (m_time >= 0){
		Label* labelTime = (Label*) this->getChildByTag(11);
		labelTime->setString(StringUtils::format("Time:%d", m_time));

	}
	if (m_time == 0){
		auto gmov = Sprite::create("pic_gameover.png");
		gmov->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
		this->addChild(gmov);

		gmov->runAction(Sequence::create
			(MoveTo::create(2.0f, Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2)),
			CallFuncN::create(CC_CALLBACK_1(GameScene::gameOver, this)),
			NULL));

	}
}

void GameScene::gameOver(Node* node){
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("music_bg.ogg");
	auto scene = StartScene::createScene();
	CCDirector::sharedDirector()->replaceScene(scene);
}
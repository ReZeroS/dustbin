#include "SpriteShape.h"
#include "GameDefine.h"

USING_NS_CC;

SpriteShape::SpriteShape()
	:m_isNeedRemove(false) {
}

SpriteShape* SpriteShape::create(int row, int col){
	SpriteShape* spr = new SpriteShape();
	spr->m_row = row;
	spr->m_col = col;
	spr->m_imgIndex = rand() % TOTAL_SPRITE;
	spr->initWithSpriteFrameName(spriteNormal[spr->m_imgIndex]);
	spr->autorelease();

	return spr;
}
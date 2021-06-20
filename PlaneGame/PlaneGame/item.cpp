#include "StdAfx.h"
#include "item.h"
#include "resource.h"

CImageList CItem::m_Images;

CItem::CItem(void) 
{
	m_ptPos.x = rand() % (GAME_WIDTH - ITEM_HEIGHT) + 1;

	//随机确定图像索引
	m_nImgIndex = rand() % 6;
	
	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = -ITEM_HEIGHT;
	
	m_V = rand() % 6 + 2;

	m_nWait = 0;
}

CItem::~CItem(void)
{
}
BOOL CItem::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + ITEM_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CItem::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP9, RGB(255, 255, 255), 30, 30, 6);
}
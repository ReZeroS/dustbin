#include "StdAfx.h"
#include "Boss.h"
#include "resource.h"

CImageList CBoss::m_Images;

CBoss::CBoss(int type)
{
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS_HEIGHT) + 1;

	//随机确定图像索引
	if (type > 3)
		type = rand() % 3 + 1;
	m_nImgIndex = type - 1;
	
	hp =  type * 100;
	//根据图像索引确定方向
	m_nMotion = 1;
	m_nMotion2 = 1;
	m_ptPos.y = -BOSS_HEIGHT;
	m_V = rand() % 12 + 10 * barrier;

	m_nWait = 0;
}

CBoss::~CBoss(void)
{
}
BOOL CBoss::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>60)
		m_nWait = 0;

	if (!bPause)
	{
		if (m_nImgIndex == 1 && m_ptPos.y > 10)
			m_ptPos.y = m_ptPos.y;
		else
			m_ptPos.y = m_ptPos.y + m_nMotion * 2;
		
		m_ptPos.x = m_ptPos.x + m_nMotion2 * 2;
	}

	if (m_ptPos.y > GAME_HEIGHT - BOSS_HEIGHT - 100)
		m_nMotion = -1;
	if (m_ptPos.y < -BOSS_HEIGHT)
		m_nMotion = 1;
	if (m_ptPos.x > GAME_WIDTH - BOSS_HEIGHT)
		m_nMotion2 = -1;
	if (m_ptPos.x < -BOSS_HEIGHT)
		m_nMotion2 = 1;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);



	return TRUE;
}

BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP14, RGB(0, 0, 255), 270, 272, 1);
}

BOOL CBoss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
#include "StdAfx.h"
#include "Cri.h"
#include "resource.h"

CImageList CCri::m_Images;

CCri::CCri(int type)
{
	m_ptPos.x = rand() % (GAME_WIDTH - CRI_HEIGHT) + 1;
	m_ptPos.y = GAME_HEIGHT/2;
	//随机确定图像索引
	m_nImgIndex = 0;

	hp = type * 10;
	//根据图像索引确定方向
	m_nMotion = 1;
	m_nMotion2 = 1;
	m_ptPos.y = -CRI_HEIGHT;
	//if (m_nImgIndex%2!=0)//如果是图像索引是偶数
	//{
	//	m_nMotion=-1;
	//	m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	//}
	//随机确定速度
	m_V = 70;

	m_nWait = 0;
}

CCri::~CCri(void)
{
}
BOOL CCri::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>60)
		m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 10;
		m_ptPos.x = m_ptPos.x + m_nMotion2 * 10;
	}

	if (m_ptPos.y > GAME_HEIGHT - CRI_HEIGHT - 100)
		m_nMotion = -1;
	if (m_ptPos.y < -CRI_HEIGHT)
		m_nMotion = 1;
	if (m_ptPos.x > GAME_WIDTH - CRI_HEIGHT)
		m_nMotion2 = -1;
	if (m_ptPos.x < -CRI_HEIGHT)
		m_nMotion2 = 1;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);



	return TRUE;
}

BOOL CCri::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP18, RGB(0, 0, 0), 100, 100, 1);
}

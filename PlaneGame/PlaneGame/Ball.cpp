#include "StdAfx.h"
#include "Ball.h"
#include "resource.h"

CImageList CBall::m_Images;
CImageList CBall::m_Images1;
CBall::CBall(int x,int y,int z,int nMontion, int zt, int speeds, int zt2):CGameObject(x,y),m_nMotion(nMontion)
{
	m_nImgIndex = zt2;
	type = zt;
	ballz = z;
	m_V = speeds;
	if (type == 1)
		BALL_HEIGHT = 30;
	else BALL_HEIGHT = 8;
}

CBall::~CBall(void)
{
}
BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		if (type == 0)
		{
			m_ptPos.x = m_ptPos.x + ballz * m_V;
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		}
		else
		{
		/*	m_ptPos.x = m_ptPos.x + ballz * m_V;
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;*/
			
			m_ptPos.y = m_ptPos.y + 7;
		}
	}

	if(m_ptPos.y > GAME_HEIGHT+BALL_HEIGHT )
		return FALSE;
	if(m_ptPos.y < -BALL_HEIGHT)
		return FALSE;
	if (m_ptPos.x > GAME_WIDTH + BALL_HEIGHT)
		return FALSE;
	if (m_ptPos.x < -BALL_HEIGHT)
		return FALSE;
	if (type == 0)
	m_Images.Draw(pDC,m_nImgIndex,m_ptPos,ILD_TRANSPARENT);
	else m_Images1.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CBall::LoadImage()
{
	CGameObject::LoadImage(m_Images, IDB_BITMAP5, RGB(0, 0, 0), 8, 8, 1);
	CGameObject::LoadImage(m_Images1, IDB_BITMAP15, RGB(255, 255, 255), 30, 30, 1);
	return true;
}
#include "StdAfx.h"
#include "Laser.h"
#include "resource.h"

CImageList CLaser::m_Images;
CLaser::CLaser(int x, int y) :CGameObject(x, y)
{
	m_nImgIndex = 0;
}

CLaser::~CLaser(void)
{
}
BOOL CLaser::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + 8;		
	}

	if (m_ptPos.y > GAME_HEIGHT)
		return FALSE;
	
		m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL CLaser::LoadImage()
{
	CGameObject::LoadImage(m_Images, IDB_BITMAP19, RGB(0,0, 0), 20, 600, 1);
	return true;
}
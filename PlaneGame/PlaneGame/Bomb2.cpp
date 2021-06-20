#include "StdAfx.h"
#include "Bomb2.h"
#include "resource.h"

CImageList CBomb2::m_Images;

CBomb2::CBomb2(int x, int y,int z,int types, int speed) :CGameObject(x, y)
{
	bombz = z;
	m_nImgIndex = types;
	m_V = speed;
}

CBomb2::~CBomb2(void)
{
}
BOOL CBomb2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP16, RGB(0, 0, 255), 10, 20, 4);
}
BOOL CBomb2::Draw(CDC* pDC, BOOL bPause)
{
	
	
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y - m_V * 2;
		m_ptPos.x = m_ptPos.x + bombz;
	}

	if (m_ptPos.y < -BOMB2_HEIGHT)
		return FALSE;
	if (typeb == 3)
	{
		if (m_ptPos.x < 0)
			bombz = 20;
		else if (m_ptPos.x > 600)
			bombz = -20;
	}

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
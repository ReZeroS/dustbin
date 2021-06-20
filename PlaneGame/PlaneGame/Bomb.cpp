#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"

CImageList CBomb::m_Images;

CBomb::CBomb(int x, int y, int speed, int ex_, int ey_) :CGameObject(x, y)
{
	m_nImgIndex = 0;
	m_V = speed;
	ex = ex_;
	ey = ey_;
}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP16, RGB(0, 0,255), 10, 20, 4);
}
BOOL CBomb::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		if (m_ptPos.y < 0 || m_ptPos.x <0 || m_ptPos.x > GAME_WIDTH)
			return false;
		m_ptPos.y = m_ptPos.y - 10;

		if (m_ptPos.x > ex)
			m_ptPos.x = m_ptPos.x - 10;
		if (m_ptPos.x < ex)
			m_ptPos.x = m_ptPos.x + 10;
	}

	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;




	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
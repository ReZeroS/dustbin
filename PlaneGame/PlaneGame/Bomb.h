#pragma once
#include "gameobject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x, int y, int speed, int ex_, int ey_);
	~CBomb(void);
	BOOL Draw(CDC* pDC, BOOL bPause);
	int m_nImgIndex;
	int m_V;
	static BOOL LoadImage();
	int ex, ey;
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 10;
	static CImageList m_Images;


};

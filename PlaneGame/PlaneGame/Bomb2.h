#pragma once
#include "gameobject.h"

class CBomb2 :
	public CGameObject
{
public:
	CBomb2(int x, int y, int z, int types, int speed);
	~CBomb2(void);
	int bombz;
	BOOL Draw(CDC* pDC, BOOL bPause);
	int m_nImgIndex;
	int m_V;
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB2_HEIGHT));
	}
private:
	static const int BOMB2_HEIGHT = 10;
	static CImageList m_Images;
	

};

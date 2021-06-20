#pragma once
#include "GameObject.h"

class CLaser :public CGameObject
{
public:
	CLaser(int x, int y);
	~CLaser(void);

	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + LASER_HEIGHT, m_ptPos.y + LASER_HEIGHT));
	}
private:
	static CImageList m_Images;
	static const int LASER_HEIGHT = 600;
	int m_nImgIndex;

};

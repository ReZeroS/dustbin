#pragma once
#include "GameObject.h"

class CCri :public CGameObject
{
public:
	CCri(int type);
	~CCri(void);
	int m_nImgIndex;
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	int GetMontion() const
	{
		return m_nMotion;
	}
	int hp;
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + CRI_HEIGHT, m_ptPos.y + CRI_HEIGHT));
	}

private:

	static const int CRI_HEIGHT = 100;
	static CImageList m_Images;
	int    m_nMotion;
	int	   m_nMotion2;
	int m_V;
	int m_nWait;
};

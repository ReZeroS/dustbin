#pragma once
#include "GameObject.h"

class CBoss :public CGameObject
{
public:
	CBoss(int type);
	~CBoss(void);
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
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_HEIGHT, m_ptPos.y + BOSS_HEIGHT));
	}

	BOOL Fired();
private:

	static const int BOSS_HEIGHT = 270;
	static CImageList m_Images;
	int    m_nMotion;
	int	   m_nMotion2;
	int m_V;
	int m_nWait;
};

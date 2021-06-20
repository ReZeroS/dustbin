#pragma once
#include "GameObject.h"

class CItem :public CGameObject
{
public:
	CItem(void);
	~CItem(void);
	int m_nImgIndex;
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + ITEM_HEIGHT, m_ptPos.y + ITEM_HEIGHT));
	}
private:
	
	static const int ITEM_HEIGHT = 30;
	static CImageList m_Images;
	int    m_nMotion;
	int m_V;
	int m_nWait;
};

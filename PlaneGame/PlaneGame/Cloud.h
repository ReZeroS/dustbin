#pragma once
#include "GameObject.h"

class CCloud :public CGameObject
{
public:
	CCloud(void);
	~CCloud(void);
	int m_nImgIndex;
	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 200, m_ptPos.y + 100));
	}
private:

	static const int CLOUD_HEIGHT = 100;
	static CImageList m_Images;
	int    m_nMotion;
	int m_V;
	int m_nWait;
};

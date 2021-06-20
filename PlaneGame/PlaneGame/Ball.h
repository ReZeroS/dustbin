#pragma once
#include "GameObject.h"

class CBall :public CGameObject
{
public:
	CBall(int x,int y,int z,int nMontion, int zt, int speeds, int zt2);
	~CBall(void);
	int BALL_HEIGHT;
	BOOL Draw(CDC* pDC,BOOL bPause);
	int m_V;
	int ballz;
	static BOOL LoadImage();

	CRect GetRect()
	{
		if (type == 0)
			BALL_HEIGHT = 8;
		else BALL_HEIGHT = 30;
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}
private:


	static CImageList m_Images;
	static CImageList m_Images1;
	int    m_nMotion;
	int m_nImgIndex;
	int type;
};

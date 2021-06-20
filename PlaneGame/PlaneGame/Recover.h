#pragma once
#include "gameobject.h"

class CRecover :public CGameObject
{
public:
	CRecover(int x, int y);
	~CRecover(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + RECOVER_WIDTH, m_ptPos.y + RECOVER_WIDTH));
	}
private:
	//炸弹的图片列表
	static CImageList m_Images;
	//图像索引的步进计数
	int   m_nProcess;
public:
	static const int  RECOVER_WIDTH = 66;

};

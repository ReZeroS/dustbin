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
	//ը����ͼƬ�б�
	static CImageList m_Images;
	//ͼ�������Ĳ�������
	int   m_nProcess;
public:
	static const int  RECOVER_WIDTH = 66;

};

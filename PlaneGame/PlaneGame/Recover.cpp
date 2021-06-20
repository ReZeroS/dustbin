#include "StdAfx.h"
#include "Recover.h"
#include "resource.h"

CImageList CRecover::m_Images;

CRecover::CRecover(int x, int y) :CGameObject(x, y), m_nProcess(0)
{
}

CRecover::~CRecover(void)
{
}
BOOL CRecover::Draw(CDC* pDC, BOOL bPause)
{
	//只有15张图片
	if (m_nProcess == 15)
	{
		m_nProcess = 0;
		return FALSE;
	}

	//用新位置绘制图像
	m_Images.Draw(pDC, m_nProcess, m_ptPos, ILD_TRANSPARENT);
	m_nProcess++;
	return TRUE;
}

BOOL CRecover::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP7, RGB(0, 0, 0), 66, 66, 8);
}
#include "StdAfx.h"
#include "Cloud.h"
#include "resource.h"

CImageList CCloud::m_Images;

CCloud::CCloud(void)
{
	m_ptPos.x = rand() % (GAME_WIDTH - CLOUD_HEIGHT) + 1;

	//���ȷ��ͼ������
	m_nImgIndex = rand() % 2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -CLOUD_HEIGHT;

	m_V = rand() % 4 + barrier * 4 + 3;

	m_nWait = 0;
}

CCloud::~CCloud(void)
{
}
BOOL CCloud::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + CLOUD_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CCloud::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP17, RGB(0, 0, 0), 200, 100, 2);
}
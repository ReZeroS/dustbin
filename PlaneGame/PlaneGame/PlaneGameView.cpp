// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "resource.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bomb.h"
#include "Bomb2.h"
#include "Ball.h"
#include "Item.h"
#include "Cloud.h"
#include "Laser.h"
#include "Cri.h"
#include "Explosion.h"
#include "Recover.h"
#include <atlimage.h>
#include "background.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
//	ON_WM_KEYDOWN()
//ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
	/*mciSendString(L"stop bgMusic ", NULL, 0, NULL);*/
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	


	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	if (AfxMessageBox(L"阅读游戏说明？", MB_YESNO) == 6){
		AfxMessageBox(L"       C键释放大招\n游戏中G键开启God模式\n游戏中H键关闭God模式");
		AfxMessageBox(L"机体左侧为剩余生命数量\n机体右侧为剩余大招数量 ");
		AfxMessageBox(L"Let's Go ！");
	}
	InitGame();
	
	

}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBoss::LoadImage();
	CBomb::LoadImage();
	CBomb2::LoadImage();
	CBall::LoadImage();
	CItem::LoadImage();
	CCri::LoadImage();
	CLaser::LoadImage();
	CCloud::LoadImage();
	CExplosion::LoadImage();
	CRecover::LoadImage();




	//产生主角(战机)
	m_pMe = new CMyPlane;

	//启动游戏
	mciSendString(L"open Audio\\bac.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);
	SetTimer(1,30,NULL);
	
	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	
	//绘制滚动背景图
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pMemDC);
	if (!pDoc && lifep)
		return;
	 if (barrier > 2 && lifep)
		pDoc->bg.draw3(pMemDC);
	else if (barrier == 2 && lifep)
		pDoc->bg.draw2(pMemDC);
	else if (barrier == 1 && lifep)
		pDoc->bg.draw(pMemDC);
	else if (!lifep)
		pDoc->bg.draw4(pMemDC);

	//绘制BOSS血条

	for (POSITION ePos = m_ObjList[enBoss].GetHeadPosition(); ePos != NULL;)
	{
		CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos);
		CPoint  ePt = pBoss->GetPoint();
		
		pMemDC->FillSolidRect(ePt.x - 50, ePt.y + 260 ,360, 12, RGB(255, 255, 255));
		pMemDC->FillSolidRect(ePt.x - 50, ePt.y + 260 ,pBoss->hp / (150.0 * ((pBoss->m_nImgIndex) + 1)) * 360, 12, RGB(0, 0, 255));
		
	}
	



	//绘制我方当前HP
	if (m_pMe != NULL)
	{
		CPoint ptnow = m_pMe->GetPoint();
		if (lifep > 1)
		{
			pMemDC->FillSolidRect(ptnow.x, ptnow.y + 60, lifee * 15, 12, RGB(0, 255, 0));
			pMemDC->FillSolidRect(ptnow.x + lifee * 15, ptnow.y + 60, (5 - lifee) * 15, 12, RGB(255, 0, 0));
		}
		else
		{
			pMemDC->FillSolidRect(ptnow.x, ptnow.y + 60, lifee * 15, 12, RGB(255, 0, 0));
			pMemDC->FillSolidRect(ptnow.x + lifee * 15, ptnow.y + 60, (5 - lifee) * 15, 12, RGB(255, 255, 255));
		}

	}
	//绘制分数
	CString strscore;
	strscore.Format(_T("(C键)Release The Cri"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(590, 0, strscore);
	//绘制GOD
	CString strgod;
	if (godblue)
	strgod.Format(_T("(H键)Show You Power"), godblue);
	else 
	strgod.Format(_T("(G键)God Bless You"), godblue);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 99, 0));
	pMemDC->TextOut(590, 40, strgod);
	//绘制barrier
	CString strb;
	if (barrier > 3)
		strb.Format(_T("无尽模式"));
	else 
	strb.Format(_T("Current Barrier: %d"), barrier);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(255, 99, 0));
	pMemDC->TextOut(590, 80, strb);
	//绘制命数
	if (m_pMe != NULL)
	{
	CPoint ptnow = m_pMe->GetPoint();
		for (int i = 0; i < lifep; ++i)
			pMemDC->FillSolidRect(ptnow.x - 16, ptnow.y + 20 * i,  12, 12, RGB(255, 102, 0));
	}
	//绘制jackspa
	if (m_pMe != NULL)
	{
	CPoint ptnow = m_pMe->GetPoint();
		for (int i = 0; i < jackspa; ++i)
			pMemDC->FillSolidRect(ptnow.x + 78, ptnow.y + 20 * i, 12, 12, RGB(0, 102, 255)); 
	}
	
	


	//绘制我方战机
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	}
	//绘制Gameover
	if (m_pMe == NULL)
	{
		for (int i = 0; i < 11; i++)
			m_ObjList[i].RemoveAll();
		if (GetKey('R') == 1)
		{
			
			KillTimer(1);
			m_pMe = new CMyPlane;
			lifep = 3;
			lifee = 5;
			total = 0;
			typeb = 0;
			jackspa = 3;
			barrier = 1;
			flag = 0;
			flag2 = 0;
			totalflag = 1;
			SetTimer(1, 30, NULL);


		}
		if (GetKey('E') == 1)
			exit(1);
		
	}
	//检测确认键
	if (GetKey('G') == 1)
		godblue = 1;
	else if (GetKey('H') == 1)
		godblue = 0;

	//绘制 导弹、爆炸、敌机、子弹、道具、回复、BOSS、大招
	for(int i=0;i<11;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = (6 - barrier) * 5;
	static int mCreator = rand() % 300 + 10;
	

	//随机产生敌机
	if (nCreator <= 0)
	{
		nCreator = (6 - barrier) * 5;
		m_ObjList[enEnemy].AddTail(new CEnemy(barrier));
	}
	nCreator--;
	//随机产生云层
	if (mCreator <= 0 && barrier > 2  && flag2 == 1)
	{
		mCreator = rand() % 300 + 10;
		m_ObjList[enCloud].AddTail(new CCloud);
	}
	mCreator--;

	//分数决定产生道具
	if (total % 8 == 0 && total != 0 && flag)	
	{ 
		flag = 0;
		m_ObjList[enItem].AddTail(new CItem);
	}
	//分数决定产生BOSS
	if (total  > 56 && total < 70 && barrier == 1 && total != 0 && flag2 == 0)
	{
		flag2 = 1;
		totalflag = 0;
		m_ObjList[enBoss].AddTail(new CBoss(1));
	}
	if (total > 112 && total < 160 && barrier  == 2 && total != 0 && flag2 == 0)
	{
		flag2 = 1;
		totalflag = 0;
		m_ObjList[enBoss].AddTail(new CBoss(2));
	}
	if (total > 224 && total < 300 && barrier == 3 && total != 0 && flag2 == 0)
	{
		flag2 = 1;
		totalflag = 0;
		m_ObjList[enBoss].AddTail(new CBoss(3));
	}


	if (m_pMe == NULL)
	{
		
		return;
	}
	
	//检测四个方向键，移动战机
	for (int i = 0; i < 4; i++)
	{
		int nMeMotion = 0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(1);

		nMeMotion = GetKey(VK_DOWN);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(-1);
	}
	//大招
	if (GetKey('C') == 1 && jackspa)//按下C键
	{
		Sleep(80);
		jackspa--;
		PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_ASYNC | SND_RESOURCE);
		m_ObjList[enCri].AddTail(new CCri(barrier));
	}
	

	//产生战机导弹
	if (GetKey(VK_SPACE) == 1)//按下了空格键
	{
		
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if (typeb == 0)
			{
				m_ObjList[enBomb2].AddTail(new CBomb2(pt.x + 20, pt.y + 10, 0, 1, 9));
				m_ObjList[enBomb2].AddTail(new CBomb2(pt.x + 40, pt.y + 10, 0, 1, 9));
			}
			else if (typeb == 1)
			{
				for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
				{
					CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
					CPoint  ePt = pEnemy->GetPoint();

					m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10, 9, ePt.x, ePt.y));
				}
			}
			else if (typeb == 2)
			{
				m_ObjList[enBomb2].AddTail(new CBomb2(pt.x + 20, pt.y + 10, -2, 2, 7));
				m_ObjList[enBomb2].AddTail(new CBomb2(pt.x + 30, pt.y + 10, 0, 2, 7));
				m_ObjList[enBomb2].AddTail(new CBomb2(pt.x + 40, pt.y + 10, 2, 2, 7));
			}
			else if (typeb == 3)
			{
				m_ObjList[enBomb2].AddTail(new CBomb2(pt.x + 20, pt.y + 10, -2, 2, 6));
				m_ObjList[enBomb2].AddTail(new CBomb2(pt.x + 40, pt.y + 10, 2, 2, 6));
				for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
				{
					CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
					CPoint  ePt = pEnemy->GetPoint();

					m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10, 9, ePt.x, ePt.y));
				}
				
				
			}
		
		}
	}


	//敌机发射子弹
	if (m_pMe != NULL)
	{
		CPoint PlanePt = m_pMe->GetPoint();
		for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
			if (!pEnemy->Fired())
				continue;
			CPoint  ePt = pEnemy->GetPoint();

			BOOL by = FALSE;

			//敌机在战机前面
			if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
				by = TRUE;

			if (by && ePt.x >= PlanePt.x && ePt.x < PlanePt.x + CMyPlane::PLANE_WIDTH)
			{
				if (pEnemy->m_nImgIndex == 0)
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, 0, pEnemy->GetMontion(), 0, 5, 0));
		
			if (pEnemy->m_nImgIndex == 2)
				{
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, -3, pEnemy->GetMontion(), 0, 5, 2));
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, 0, pEnemy->GetMontion(), 0, 5, 0));
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, 3, pEnemy->GetMontion(), 0, 5, 2));
				}
			}
			if (by && ePt.x <= PlanePt.x || ePt.x >= PlanePt.x + CMyPlane::PLANE_WIDTH)
			{
				if (pEnemy->m_nImgIndex == 1)
				{
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, -1, pEnemy->GetMontion(), 0, 5, 1));
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, 1, pEnemy->GetMontion(), 0, 5, 1));
				}
			}
		}
	}


	//BOSS发射子弹
	if (m_pMe != NULL){
		CPoint PlanePt = m_pMe->GetPoint();
		for (POSITION ePos = m_ObjList[enBoss].GetHeadPosition(); ePos != NULL;)
		{
			CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos);
			if (!pBoss->Fired())
				continue;
			CPoint  ePt = pBoss->GetPoint();
			
			BOOL by = TRUE;

			//Boss在战机前面
			if (ePt.y < PlanePt.y)
				by = TRUE;
			
			
				

			if ((pBoss->m_nImgIndex == 0 && by) && (ePt.x <  PlanePt.x && ePt.x + 270 >  PlanePt.x))
			{
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 0, ePt.y + 150, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 40, ePt.y + 120, 1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 80, ePt.y + 120, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 120, ePt.y + 150, 1, pBoss->GetMontion(), 0, 5, 1));

				m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, 0, pBoss->GetMontion(), 0, 3, 0));
				
				m_ObjList[enBall].AddTail(new CBall(ePt.x - 10, ePt.y, 0, 2, 1, 3, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x      , ePt.y, 0, 2, 1, 3, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 30 , ePt.y + 150, 0, 2, 1, 3, 0));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 90 , ePt.y + 150, 0, 2, 1, 3, 0));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 120, ePt.y, 0, 2, 1, 3, 2));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 150, ePt.y, 0, 2, 1, 3, 2));
			
			}
			else if (pBoss->m_nImgIndex == 1)
			{
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 0, ePt.y + 150, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 20, ePt.y + 150, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 40, ePt.y + 120, 1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 60, ePt.y + 150, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 80, ePt.y + 120, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 100, ePt.y + 150, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 120, ePt.y + 150, 1, pBoss->GetMontion(), 0, 5, 1));

				m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, 0, pBoss->GetMontion(), 0, 3, 0));
				
				if (ePt.x > 100 && ePt.x < 600)
				{
					m_ObjList[enLaser].AddTail(new CLaser(ePt.x + 200, ePt.y + 270));
					PlaySound((LPCTSTR)IDR_WAVE7, NULL, SND_ASYNC | SND_RESOURCE);
				}
				m_ObjList[enBall].AddTail(new CBall(ePt.x	, ePt.y , 0, 2, 1, 3, 3));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 30, ePt.y + 150, 0, 2, 1, 3, 4));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 50, ePt.y + 150, 0, 2, 1, 3, 4));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 90, ePt.y + 150, 0, 2, 1, 3, 4));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 110, ePt.y + 150, 0, 2, 1, 3, 4));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 120, ePt.y, 0, 2, 1, 3, 5));


			}
			else if (pBoss->m_nImgIndex == 2)
			{
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 0, ePt.y + 150, -1, pBoss->GetMontion(), 0, 5, 1));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 40, ePt.y + 120, 1, pBoss->GetMontion(), 0, 5, 1));
				
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 120, ePt.y + 150, 1, pBoss->GetMontion(), 0, 5, 1));

				m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, 0, pBoss->GetMontion(), 0, 3, 0));

				if (ePt.x < 300 || ePt.x > 400)
				{
					PlaySound((LPCTSTR)IDR_WAVE7, NULL, SND_ASYNC | SND_RESOURCE);
					m_ObjList[enLaser].AddTail(new CLaser(ePt.x + 160, ePt.y + 270));
					m_ObjList[enLaser].AddTail(new CLaser(ePt.x + 240, ePt.y + 270));
				}
				m_ObjList[enBall].AddTail(new CBall(ePt.x, ePt.y , 0, 2, 1, 3, 6));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 30, ePt.y + 150, 0, 2, 1, 3, 7));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 90, ePt.y + 150,0, 2, 1, 3, 7));
				m_ObjList[enBall].AddTail(new CBall(ePt.x + 120, ePt.y , 0, 2, 1, 3, 8));

			}

		}
	}


	//道具666
	if (m_pMe != NULL){
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enItem].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CItem* pItem = (CItem*)m_ObjList[enItem].GetNext(bPos1);
			CRect bRect = pItem->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加回复效果
				m_ObjList[enRecover].AddTail(
					new CRecover(mRect.left, mRect.top)
					);
				PlaySound((LPCTSTR)IDR_WAVE3, NULL, SND_ASYNC | SND_RESOURCE);
				//根据道具确定效果
				int itempq = pItem->m_nImgIndex;
				if (itempq == 5)
					itempq = rand() % 5;
				else if (itempq == 1)  typeb = 1;
				else if (itempq == 2) typeb = 2;
				else if (itempq == 3) typeb = 3;
				else if (itempq == 4)
				{
					jackspa++;
					if (jackspa > 4)
						jackspa = 4;
				}
				else if (itempq == 0)
				{
					if (lifee != 5)
					lifee++;

					if (lifee == 5)
					{
						lifep ++;
						if (lifep > 4)
							lifep = 4;
						lifee = 1;
					}
				}
				//删除道具
				m_ObjList[enItem].RemoveAt(bPos2);
				delete pItem;
				pItem = NULL;
				break;				
			}
		}
	}
	//第三关陨石碰到掉血
	if (m_pMe != NULL && barrier > 2){
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enCloud].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CCloud* pCloud = (CCloud*)m_ObjList[enCloud].GetNext(bPos1);
			CRect bRect = pCloud->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
			

				m_ObjList[enCloud].RemoveAt(bPos2);
				delete pCloud;
				pCloud = NULL;
				if (!godblue)
					lifee--;
				if (lifee == 0)
				{
					lifep--;
					typeb = 0;
					lifee = 5;
				}
				if (totalflag)
				total++;
				flag = 1;
				////删除战机
				if (lifep == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
				break;
			}
		}
	}
	//激光碰到掉血
	if (m_pMe != NULL){
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enLaser].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CLaser* pLaser = (CLaser*)m_ObjList[enLaser].GetNext(bPos1);
			CRect bRect = pLaser->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
				
				

				m_ObjList[enLaser].RemoveAt(bPos2);
				delete pLaser;
				pLaser = NULL;
				if (!godblue)
					lifee--;
				if (lifee == 0)
				{
					lifep--;
					typeb = 0;
					lifee = 5;
				}
				if (totalflag)
				total++;
				flag = 1;
				////删除战机
				if (lifep == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
				break;
			}
		}
	}
	
	//敌机子弹炸掉战机
	if (m_pMe != NULL){
	POSITION Pos1 = NULL, Pos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (Pos1 = m_ObjList[enBall].GetHeadPosition(); (Pos2 = Pos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(Pos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
				);
			//PlaySound((LPCTSTR)IDR_WAVE6, NULL, SND_ASYNC | SND_RESOURCE);
			//删除子弹
			m_ObjList[enBall].RemoveAt(Pos2);
			delete pBall;
			pBall = NULL;
			if (!godblue) lifee--;
				if (lifee == 0)
				{
					lifep--;
					typeb = 0;
					lifee = 5;
				}
				////删除战机
				if (lifep == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
			
		}
	}
	}
	//敌机碰到战机双死亡
	if (m_pMe != NULL){
	POSITION kPos1 = NULL, kPos2 = NULL;
	CRect yRect = m_pMe->GetRect();
	for (kPos1 = m_ObjList[enEnemy].GetHeadPosition(); (kPos2 = kPos1) != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(kPos1);
		CRect bRect = pEnemy->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, yRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(yRect.left, yRect.top)
				);
			//PlaySound((LPCTSTR)IDR_WAVE6, NULL, SND_ASYNC | SND_RESOURCE);
			//删除敌机
			m_ObjList[enEnemy].RemoveAt(kPos2);
			delete pEnemy;
			pEnemy = NULL;
			if (!godblue)
			lifee--;
			if (lifee == 0)
			{
				lifep --;
				typeb = 0;
				lifee = 5;
			}
			if (totalflag)
			total++;
			flag = 1;
			////删除战机
			if (lifep == 0)
			{
				delete m_pMe;
				m_pMe = NULL;
				
				break;
			}
			break;
		}
	}
	}
	//大招炸掉敌机
	if (m_pMe != NULL)
	{
		POSITION qPos1 = NULL, qPos2 = NULL;
		for (qPos1 = m_ObjList[enCri].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
		{
			CCri* pCri = (CCri*)m_ObjList[enCri].GetNext(qPos1);
			CRect bRect = pCri->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					
					
					if (!((pCri->hp)--))
					{
						m_ObjList[enCri].RemoveAt(qPos2);
						delete pCri;
						pCri = NULL;
					}
					//删除敌机
					m_ObjList[enEnemy].RemoveAt(ePos2);
					

					delete pEnemy;
					pEnemy = NULL;
					flag = 1;
					break;

				}
			}
		}
	}
	
	
	//导弹2炸掉敌机
	if (m_pMe != NULL)
	{
		POSITION qPos1 = NULL, qPos2 = NULL;
		for (qPos1 = m_ObjList[enBomb2].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
		{
			CBomb2* pBomb2 = (CBomb2*)m_ObjList[enBomb2].GetNext(qPos1);
			CRect bRect = pBomb2->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					
			
					//删除导弹
					m_ObjList[enBomb2].RemoveAt(qPos2);
					delete pBomb2;
					pBomb2 = NULL;

					//删除敌机
					m_ObjList[enEnemy].RemoveAt(ePos2);
					if (totalflag)
					total++;//加分

					delete pEnemy;
					pEnemy = NULL;
					flag = 1;
					break;

				}
			}
		}
	}
	//导弹2炸掉子弹
	if (m_pMe != NULL)
	{
		POSITION qPos1 = NULL, qPos2 = NULL;
		for (qPos1 = m_ObjList[enBomb2].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
		{
			CBomb2* pBomb2 = (CBomb2*)m_ObjList[enBomb2].GetNext(qPos1);
			CRect bRect = pBomb2->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBall].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(ePos1);
				CRect mRect = pBall->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
						);
					
					//PlaySound((LPCTSTR)IDR_WAVE6, NULL, SND_ASYNC | SND_RESOURCE);
					//删除导弹
					m_ObjList[enBomb2].RemoveAt(qPos2);
					delete pBomb2;
					pBomb2 = NULL;

					//删除敌机
					m_ObjList[enBall].RemoveAt(ePos2);
					

					delete pBall;
					pBall = NULL;
					flag = 1;
					break;

				}
			}
		}
	}


	//导弹1炸掉敌机
	if (m_pMe != NULL)
	{
		POSITION qPos1 = NULL, qPos2 = NULL;
		for (qPos1 = m_ObjList[enBomb].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(qPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
						);
					
					//PlaySound((LPCTSTR)IDR_WAVE6, NULL, SND_ASYNC | SND_RESOURCE);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(qPos2);
					delete pBomb;
					pBomb = NULL;

					//删除敌机
					m_ObjList[enEnemy].RemoveAt(ePos2);
					if(totalflag)total++;//加分

					delete pEnemy;
					pEnemy = NULL;
					flag = 1;
					break;

				}
			}
		}
	}
	//导弹1炸掉子弹
	if (m_pMe != NULL)
	{
		POSITION qPos1 = NULL, qPos2 = NULL;
		for (qPos1 = m_ObjList[enBomb].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(qPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBall].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(ePos1);
				CRect mRect = pBall->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
						);
					
					//PlaySound((LPCTSTR)IDR_WAVE6, NULL, SND_ASYNC | SND_RESOURCE);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(qPos2);
					delete pBomb;
					pBomb = NULL;

					//删除敌机
					m_ObjList[enBall].RemoveAt(ePos2);
			

					delete pBall;
					pBall = NULL;
					flag = 1;
					break;

				}
			}
		}
	}
	///--------------------特马勒戈壁------------------------
	///--------------------特马勒戈壁------------------------
	//Boss碰到战机双掉血
	if (m_pMe != NULL){
		POSITION kPos1 = NULL, kPos2 = NULL;
		CRect yRect = m_pMe->GetRect();
		for (kPos1 = m_ObjList[enBoss].GetHeadPosition(); (kPos2 = kPos1) != NULL;)
		{
			CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(kPos1);
			CRect bRect = pBoss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, yRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(yRect.left + 60, yRect.top + 60)
					);
				//PlaySound((LPCTSTR)IDR_WAVE6, NULL, SND_ASYNC | SND_RESOURCE);
				//Boss掉血
				
				if (--(pBoss->hp) == 0)
				{
					m_ObjList[enBoss].RemoveAt(kPos2);
					barrier = pBoss->m_nImgIndex + 2;
					delete pBoss;
					total++;
					pBoss = NULL;
					flag2 = 0;
					totalflag = 1;
				}
				if (!godblue)
				lifee--;
				if (lifee == 0)
				{
					lifep--;
					typeb = 0;
					lifee = 5;
				}
				
				flag = 1;
				////删除战机
				if (lifep == 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					
					break;
				}
				break;
			}
		}
	}
	//战机导弹炸掉敌机
	if (m_pMe != NULL){
		POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb2].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb2* pBomb = (CBomb2*)m_ObjList[enBomb2].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
						);
					
					
					//删除导弹
					m_ObjList[enBomb2].RemoveAt(mPos2);
					delete pBomb;
					pBomb = NULL;

					//删除敌机
					m_ObjList[enEnemy].RemoveAt(ePos2);
					if(totalflag)total++;//加分

					delete pEnemy;
					pEnemy = NULL;
					flag = 1;
					break;

				}
			}
		}
	}
	//战机导弹炸掉BOSS
	if (m_pMe != NULL)
	{
		POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos1);
				CRect mRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					
		
					//删除导弹
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					pBomb = NULL;

					//Boss掉血

					if (--(pBoss->hp) == 0)
					{
						m_ObjList[enBoss].RemoveAt(ePos2);
						barrier = (pBoss->m_nImgIndex + 2);
						delete pBoss;
						pBoss = NULL;
						total++;//加分
						flag2 = 0;
						totalflag = 1;
					}
					//delete pBoss;
					flag = 1;
					break;

				}
			}
		}
	}
	//导弹2炸掉BOSS
	if (m_pMe != NULL){
	POSITION qPos1 = NULL, qPos2 = NULL;
	for (qPos1 = m_ObjList[enBomb2].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
	{
		CBomb2* pBomb2 = (CBomb2*)m_ObjList[enBomb2].GetNext(qPos1);
		CRect bRect = pBomb2->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enBoss].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos1);
			CRect mRect = pBoss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);
				
				//删除导弹
				m_ObjList[enBomb2].RemoveAt(qPos2);
				delete pBomb2;
				pBomb2 = NULL;
				//删除boss

				if (--(pBoss->hp) == 0)
				{
					m_ObjList[enBoss].RemoveAt(ePos2);
					barrier = pBoss->m_nImgIndex + 2;
					delete pBoss;
					pBoss = NULL;
					total++;//加分
					flag2 = 0;
					totalflag = 1;
				}
				flag = 1;
				break;

			}
		}
	}
	}
	//Cri击中boss
	if (m_pMe != NULL){
		POSITION qPos1 = NULL, qPos2 = NULL;
		for (qPos1 = m_ObjList[enCri].GetHeadPosition(); (qPos2 = qPos1) != NULL;)
		{
			CCri* pCri = (CCri*)m_ObjList[enCri].GetNext(qPos1);
			CRect bRect = pCri->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos1);
				CRect mRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left , mRect.top)
						);

					//删除导弹
					m_ObjList[enCri].RemoveAt(qPos2);
					delete pCri;
					pCri = NULL;
					//删除boss

					if (--(pBoss->hp) == 0)
					{
						m_ObjList[enBoss].RemoveAt(ePos2);
						barrier = pBoss->m_nImgIndex + 2;
						delete pBoss;
						pBoss = NULL;
						totalflag = 1;
						flag2 = 0;
					}
					flag = 1;
					break;

				}
			}
		}
	}
	///--------------------特马勒戈壁------------------------

}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//刷新游戏帧画面: 在内存DC上绘图

		UpdateFrame(m_pMemDC);
		AI();
		
	CView::OnTimer(nIDEvent);
}



void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	PlaySound(NULL, NULL, SND_ASYNC);
	mciSendString(L"close bgm", NULL, 0, NULL);
	this->StopGame();
	// TODO: 在此处添加消息处理程序代码
}





#include "stdafx.h"
#include "background.h"
#include "resource.h"


background::background()
	: bgloop(0)
{
}


background::~background()
{
}


void background::draw(CDC * pdc)
{
	bgloop++;
	if (bgloop >= 888)
		bgloop = 0;

	CBitmap mbg;
	mbg.LoadBitmapW(IDB_BITMAP8);

	CDC mdc;
	mdc.CreateCompatibleDC(pdc);
	mdc.SelectObject(mbg);
	pdc->BitBlt(0, bgloop, 768,888 - bgloop, &mdc, 0, 0, SRCCOPY);
	pdc->BitBlt(0, 0, 768, bgloop, &mdc, 0, 888 - bgloop, SRCCOPY);


}
void background::draw2(CDC * pdc)
{
	bgloop++;
	if (bgloop >= 888)
		bgloop = 0;

	CBitmap mbg;
	mbg.LoadBitmapW(IDB_BITMAP12);

	CDC mdc;
	mdc.CreateCompatibleDC(pdc);
	mdc.SelectObject(mbg);
	pdc->BitBlt(0, bgloop, 768, 888 - bgloop, &mdc, 0, 0, SRCCOPY);
	pdc->BitBlt(0, 0, 768, bgloop, &mdc, 0, 888 - bgloop, SRCCOPY);


}
void background::draw3(CDC * pdc)
{
	bgloop++;
	if (bgloop >= 888)
		bgloop = 0;

	CBitmap mbg;
	mbg.LoadBitmapW(IDB_BITMAP13);

	CDC mdc;
	mdc.CreateCompatibleDC(pdc);
	mdc.SelectObject(mbg);
	pdc->BitBlt(0, bgloop, 768, 888 - bgloop, &mdc, 0, 0, SRCCOPY);
	pdc->BitBlt(0, 0, 768, bgloop, &mdc, 0, 888 - bgloop, SRCCOPY);


}

void background::draw4(CDC * pdc)
{
	

	CBitmap mbg;
	mbg.LoadBitmapW(IDB_BITMAP4);

	CDC mdc;
	mdc.CreateCompatibleDC(pdc);
	mdc.SelectObject(mbg);
	pdc->BitBlt(0, 0, 768, 888 , &mdc, 0, 0, SRCCOPY);


}

void background::draw5(CDC * pdc)
{


	CBitmap mbg;
	mbg.LoadBitmapW(IDB_BITMAP6);

	CDC mdc;
	mdc.CreateCompatibleDC(pdc);
	mdc.SelectObject(mbg);
	pdc->BitBlt(0, 0, 768, 888, &mdc, 0, 0, SRCCOPY);


}

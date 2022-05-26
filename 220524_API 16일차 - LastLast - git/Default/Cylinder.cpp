#include "stdafx.h"
#include "Cylinder.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CCylinder::CCylinder()
{
}

CCylinder::~CCylinder()
{
	Release();
}

void CCylinder::Initialize()
{
	m_tInfo.fCX = 224.f;
	m_tInfo.fCY = 393.f;

	m_pFrameKey = L"Cylinder1";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CCylinder::Update()
{
	Update_Rect();
	Update_InfoCollision();

	return OBJ_NOEVENT;
}

void CCylinder::Late_Update()
{
}

void CCylinder::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
	//	int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
	//	int(m_tRect.top + iScrollY),
	//	int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
	//	int(m_tInfo.fCY),
	//	hMemDC,							// 비트맵을 가지고 있는 DC
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
	//	m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
	//	(int)m_tInfo.fCY,
	//	RGB(255, 255, 255));			// 제거하고자 하는 색상
	//
		//Rectangle(hDC, (int)m_tInfoCollision.fX - m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY - m_tInfoCollision.fCY * 0.5 + iScrollY, (int)m_tInfoCollision.fX + m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY + m_tInfoCollision.fCY * 0.5 + iScrollY);
		//Rectangle(hDC, (int)m_tInfo.fX - m_tInfo.fCX * 0.5 + iScrollX, (int)m_tInfo.fY - m_tInfo.fCY * 0.5 + iScrollY, (int)m_tInfo.fX + m_tInfo.fCX * 0.5 + iScrollX, (int)m_tInfo.fY + m_tInfo.fCY * 0.5 + iScrollY);

}

void CCylinder::Release()
{
}

void CCylinder::Motion_Change()
{
}

void CCylinder::Update_InfoCollision()
{
	m_tInfoCollision.fX = m_tInfo.fX;
	m_tInfoCollision.fY = m_tInfo.fY;
	m_tInfoCollision.fCX = m_tInfo.fCX * 0.7f;
	m_tInfoCollision.fCY = m_tInfo.fCY;
}


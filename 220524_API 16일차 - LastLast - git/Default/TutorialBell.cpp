#include "stdafx.h"
#include "TutorialBell.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTutorialBell::CTutorialBell()
{
}


CTutorialBell::~CTutorialBell()
{
	Release();
}

void CTutorialBell::Initialize()
{
	m_tInfo.fCX = 72.f;
	m_tInfo.fCY = 62.f;
	m_iHp = 1;

	m_pFrameKey = L"Tutorial_Bell";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CTutorialBell::Update()
{
	m_tInfo.fX = 2271.f;
	m_tInfo.fY = 133.f;
	
	if (m_bDead || !m_iHp)
	{
		m_tFrame.iFrameStart = 1;
		//m_bDead = false;
	}

	Update_Rect();
	Update_RectCollision(0.f, 0.f, 0.f, 0.f);
	return OBJ_NOEVENT;
}

void CTutorialBell::Late_Update()
{
	//if (!m_bDead)
	//	Move_Frame();
}

void CTutorialBell::Render(HDC hDC)
{	
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		0,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	//Rectangle(hDC, (int)m_tRectCollision.left + iScrollX, (int)m_tRectCollision.top + iScrollY, (int)m_tRectCollision.right+ iScrollX, (int)m_tRectCollision.bottom + iScrollY);
}

void CTutorialBell::Release()
{
}

void CTutorialBell::Motion_Change()
{
}

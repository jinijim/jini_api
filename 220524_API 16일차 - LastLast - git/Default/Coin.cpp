#include "stdafx.h"
#include "Coin.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CCoin::CCoin()
{
	m_Tag = TAG_ITEM;
}


CCoin::~CCoin()
{
	Release();
}

void CCoin::Initialize()
{
	m_tInfo.fCX = 72.06f;
	m_tInfo.fCY = 89.f;

	m_eCurState = IDLE;
	m_pFrameKey = L"Coin";

	m_iHp = 1;
}

int CCoin::Update()
{
	if (m_bDead || !m_iHp)
	{
		m_bDead = true;
		m_eCurState = DEAD;

		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		if (GetTickCount() - m_dwDeadMotionTime > 2000)
			return OBJ_DEAD;
	}

	Update_Rect();
	Update_RectCollision(20.f, 20.f, 20.f, 20.f);

	return OBJ_NOEVENT;
}

void CCoin::Late_Update()
{
	Motion_Change();

	if (m_eCurState == IDLE)
		Move_Frame();
	else
		Move_Frame_MultiLine(3, 9);
}

void CCoin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	//Rectangle(hDC, (int)m_tRectCollision.left, (int)m_tRectCollision.top, (int)m_tRectCollision.right, (int)m_tRectCollision.bottom);
}

void CCoin::Release()
{
}

void CCoin::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_pFrameKey = L"Coin_Death";

			m_tInfo.fCX = 328.6f;
			m_tInfo.fCY = 285.f;

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

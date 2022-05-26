#include "stdafx.h"
#include "Flag.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CFlag::CFlag()
{
}


CFlag::~CFlag()
{
	Release();
}

void CFlag::Initialize()
{
	m_tInfo.fCX = 89.5f;
	m_tInfo.fCY = 136.5f;

	m_pFrameKey = L"Flag";
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount(); 

	m_reStart = true;
}

void CFlag::Update()
{
	Update_Rect();
}

void CFlag::Late_Update()
{
	Motion_Change();

	if (m_reStart)
		Move_Frame();
	else
		Move_Frame_Middle(14);
}

void CFlag::Render(HDC hDC)
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
}

void CFlag::Release()
{
}

void CFlag::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LIVE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 27;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CFlag::Move_Frame_Middle(int _i)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = _i;
	}
}

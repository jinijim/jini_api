#include "stdafx.h"
#include "EffectMonsterDead.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CEffectMonsterDead::CEffectMonsterDead()
{
}

CEffectMonsterDead::~CEffectMonsterDead()
{
	Release();
}

void CEffectMonsterDead::Initialize()
{
	m_tInfo.fCX = 561.66f;
	m_tInfo.fCY = 556.f;
	m_bDead = true;
	//m_dwDeadTime = long(0);
	m_pFrameKey = L"Effect_Bang";
	//m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 80;
	m_tFrame.dwTime = GetTickCount();
}

int CEffectMonsterDead::Update()
{
	if (m_dwDeadMotionTime == 0)
		m_dwDeadMotionTime = GetTickCount();


	if (m_iOption == 10)
	{
		if (GetTickCount() - m_dwDeadMotionTime > 800)
			return OBJ_DEAD;
	}
	else
	{
		if (GetTickCount() - m_dwDeadMotionTime > 2000)
			return OBJ_DEAD;
	}
	
	// Option에 따라 Effect 생성이후 효과
	if (m_iOption == 1)
	{
		m_tInfo.fY += 3.f;
	}


	Update_Rect();
	return OBJ_NOEVENT;
}

void CEffectMonsterDead::Late_Update()
{
	Move_Frame();
}

void CEffectMonsterDead::Render(HDC hDC)
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
		0,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
}

void CEffectMonsterDead::Release()
{
}

void CEffectMonsterDead::Motion_Change()
{
}

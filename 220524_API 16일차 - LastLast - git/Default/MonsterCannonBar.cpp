#include "stdafx.h"
#include "MonsterCannonBar.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CMonsterCannonBar::CMonsterCannonBar()
{
	m_Tag = TAG_MONSTER;
}


CMonsterCannonBar::~CMonsterCannonBar()
{
	Release();
}

void CMonsterCannonBar::Initialize()
{
	m_tInfo.fCX = 59.f;
	m_tInfo.fCY = 600.f;

	m_fSpeed = 4.f;

	m_iHp = 10;
	m_iAttack = 1;

	m_pFrameKey = L"Run_Cannon_Bar";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	//m_dwPhaseTime = GetTickCount();
	//m_dwAttackTime = 0;
}

int CMonsterCannonBar::Update()
{
	if (m_bDead || !m_iHp)
	{
		m_bDead = true;
		m_eCurState = DEAD;

		m_tInfo.fY -= m_fSpeed;

		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		if (GetTickCount() - m_dwDeadMotionTime > 3000)
			return OBJ_DEAD;
	}

	Update_Rect();
	Update_RectCollision(0.f, 0.f, 0.f, 0.f);

	return OBJ_NOEVENT;
}

void CMonsterCannonBar::Late_Update()
{
	//Motion_Change();
	//Move_Frame();
}

void CMonsterCannonBar::Render(HDC hDC)
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

void CMonsterCannonBar::Release()
{
}

void CMonsterCannonBar::Motion_Change()
{//
}

void CMonsterCannonBar::Set_Phase()
{
}

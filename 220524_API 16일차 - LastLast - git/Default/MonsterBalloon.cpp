#include "stdafx.h"
#include "MonsterBalloon.h"
#include "ObjMgr.h"

CMonsterBalloon::CMonsterBalloon()
{
	m_Tag = TAG_BOSS;
}

CMonsterBalloon::~CMonsterBalloon()
{
	Release();
}

void CMonsterBalloon::Initialize()
{
	m_fBirthX = m_tInfo.fX;
	m_bDown = false;

	m_tInfo.fCX = 134.f;
	m_tInfo.fCY = 195.f;
	m_fSpeed = 4.f;
	m_iHp = 5;
	m_iAttack = 1;

	m_pFrameKey = L"Run_Balloon";
	m_eCurState = IDLE;

	if(m_iOption == 1)
		CObjMgr::Get_Instance()->Add_ObjectParry(this);

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
}

int CMonsterBalloon::Update()
{
	if (m_bDead || !m_iHp)
	{
		m_bDead = true;
		m_eCurState = DEAD;

			return OBJ_DEAD;
	}

	if (m_pPlayer->Get_Info().fX > m_fBirthX  - 600.f)
		m_bDown = true;

	if (m_bDown)
	{
		m_tInfo.fX -= 3.f;
		m_tInfo.fY += 3.f;
	}
	
	Update_Rect();
	Update_RectCollision(10.f, 10.f, 50.f, 100.f);

	return OBJ_NOEVENT;
}

void CMonsterBalloon::Late_Update()
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_pPlayer->Get_Info().fX > m_fBirthX + 400.f)
	{
		if (WINCX + 300 - iScrollX <= m_tRect.left || 0 - 300 + iScrollX >= m_tRect.right ||
			WINCY + 300 + iScrollY <= m_tRect.top || 0 - 300 - iScrollY >= m_tRect.bottom)
			m_bDead = true;
	}
	
	Motion_Change();
	Move_Frame();
}

void CMonsterBalloon::Render(HDC hDC)
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
	//Rectangle(hDC, (int)m_tRectCollision.left + iScrollX, (int)m_tRectCollision.top + iScrollY, (int)m_tRectCollision.right + iScrollX, (int)m_tRectCollision.bottom + iScrollY);
}

void CMonsterBalloon::Release()
{
}

void CMonsterBalloon::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			if (m_iOption == 1)
				m_tFrame.iMotion = 0;
			else
				m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMonsterBalloon::Set_Phase()
{
}

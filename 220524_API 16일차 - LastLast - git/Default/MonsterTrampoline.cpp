#include "stdafx.h"
#include "MonsterTrampoline.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
//#include "AbstractFactory.h"


CMonsterTrampoline::CMonsterTrampoline()
{
	m_Tag = TAG_TRAMPOLIN;
}


CMonsterTrampoline::~CMonsterTrampoline()
{
	Release();
}

void CMonsterTrampoline::Initialize()
{
	m_tInfo.fCX = 216.f;
	m_tInfo.fCY = 214.5f;
	m_fSpeed = 2.f;
	m_iHp = 200;
	m_iAttack = 0;
	m_fXBirth = m_tInfo.fX;

	m_pFrameKey = L"Run_Trampoline";
	m_eCurState = IDLE;

	m_bJump = false;
	m_dwMotionTime = long(0);
	m_bJumpSound = false;

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	CObjMgr::Get_Instance()->Add_ObjectParry(this);
}

int CMonsterTrampoline::Update()
{
	//if (m_bDead || !m_iHp)
	//{
	//	m_bDead = true;
	//	m_eCurState = IDLE;

	//	if (m_dwDeadMotionTime == 0)
	//		m_dwDeadMotionTime = GetTickCount();

	//	if (GetTickCount() - m_dwDeadMotionTime > 2000)
	//		return OBJ_DEAD;
	//}
	//else
	//{
	
	Move();
	
	//}

	Update_Rect();
	//Update_RectCollision(50.f, 50.f, 50.f, 50.f);
	Update_InfoCollision();

	return OBJ_NOEVENT;
}

void CMonsterTrampoline::Late_Update()
{
	if (m_bJump)
	{
		m_eCurState = JUMP;
		
		if (!m_bJumpSound)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_level_platform_trampoline_bounce.wav", SOUND_EFFECT, g_fSound_EFFECT);
			m_bJumpSound = true;
		}

		if (m_dwMotionTime == long(0))
			m_dwMotionTime = GetTickCount();

		if (1000 < GetTickCount() - m_dwMotionTime)
		{
			m_eCurState = IDLE;
			m_bJump = false;
			m_bJumpSound = false;
			m_dwMotionTime = GetTickCount();
		}
	}

	Motion_Change();
	Move_Frame();

	m_bDead = false;
	/*m_fXBefore = m_tInfo.fX;*/
}

void CMonsterTrampoline::Render(HDC hDC)
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

	//Rectangle(hDC, (int)m_tRectCollision.left + iScrollX, (int)m_tRectCollision.top, (int)m_tRectCollision.right + iScrollX, (int)m_tRectCollision.bottom);
	//Rectangle(hDC, (int)m_tInfoCollision.fX - m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY - m_tInfoCollision.fCY * 0.5 + iScrollY, (int)m_tInfoCollision.fX + m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY + m_tInfoCollision.fCY * 0.5 + iScrollY);
}

void CMonsterTrampoline::Release()
{
}

void CMonsterTrampoline::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}

void CMonsterTrampoline::Update_InfoCollision()
{
	m_tInfoCollision.fX = m_tInfo.fX;
	m_tInfoCollision.fY = m_tInfo.fY - 50.f;
	m_tInfoCollision.fCX = m_tInfo.fCX * 0.3f;
	m_tInfoCollision.fCY = m_tInfo.fCY * 0.5f;
}

void CMonsterTrampoline::Move()
{
	if (m_pPlayer->Get_Info().fX > 1200.f && m_pPlayer->Get_Info().fX < 3200.f)
	{
		if (m_pPlayer->Get_Info().fX  < m_tInfo.fX)
			m_tInfo.fX -= m_fSpeed;
		else if (m_pPlayer->Get_Info().fX  > m_tInfo.fX)
			m_tInfo.fX += m_fSpeed;
	}
	else
	{
		if (m_tInfo.fX < m_fXBirth)
			m_tInfo.fX += m_fSpeed;
		else if (m_tInfo.fX > m_fXBirth)
			m_tInfo.fX -= m_fSpeed;
	}
	//else
	//	m_tInfo.fX = m_fXBefore;
}

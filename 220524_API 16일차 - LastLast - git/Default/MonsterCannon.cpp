#include "stdafx.h"
#include "MonsterCannon.h"
#include "MonsterCannonBall.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"

CMonsterCannon::CMonsterCannon()
{
	m_Tag = TAG_MONSTER;
}


CMonsterCannon::~CMonsterCannon()
{
	Release();
}

void CMonsterCannon::Initialize()
{
	m_tInfo.fCX = 147.f;
	m_tInfo.fCY = 96.f;
	m_fSpeed = 4.f;
	m_iHp = 30;
	m_iAttack = 1;

	m_pFrameKey = L"Run_Cannon_Head";
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_dwPhaseTime = long(0);
	m_dwAttackTime = long(0);

	//m_dwPhaseTime = GetTickCount();
	//m_dwAttackTime = 0;

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
}

int CMonsterCannon::Update()
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
	else
	{
		if (m_pPlayer->Get_Info().fX > 4600.f && m_dwPhaseTime == long(0))
			m_dwPhaseTime = GetTickCount();

		if(m_dwPhaseTime != long(0))
			Attack();
	}

	Update_Rect();
	Update_RectCollision(0.f, 0.f, 0.f, 0.f);

	return OBJ_NOEVENT;
}

void CMonsterCannon::Late_Update()
{
	Motion_Change();
	Move_Frame();
}

void CMonsterCannon::Render(HDC hDC)
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

void CMonsterCannon::Release()
{
}

void CMonsterCannon::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMonsterCannon::Attack()
{
	int _index = 0;

	if (m_iOption == 1)
		_index = 1500;
	else if (m_iOption == 2)
		_index = 1000;
	else
		_index = 2200;
	
	if (_index < GetTickCount() - m_dwPhaseTime /*&& _index + 6000 > GetTickCount() - m_dwPhaseTime*/)
	{

		if (m_dwAttackTime == 0)
		{
			m_dwAttackTime = GetTickCount();
		}

		if (_index * 3 < GetTickCount() - m_dwAttackTime)
		{
			if (m_pPlayer->Get_Info().fX > 6500.f)
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_level_platform_cannon_shoot_04.wav", SOUND_MONSTER, g_fSound_MONSTER);
			}
			m_eCurState = ATTACK;
			m_dwAttackTime = GetTickCount();
			m_dwMotionTime = GetTickCount();
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterCannonBall>::Create(m_tInfo.fX - 50, m_tInfo.fY, rand() % 3 + 1));
		}

		if (500 < GetTickCount() - m_dwMotionTime)
		{
			m_eCurState = IDLE;
			m_dwMotionTime = GetTickCount();
		}
	}	
}

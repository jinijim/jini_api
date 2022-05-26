#include "stdafx.h"
#include "MonsterMachine.h"
#include "MonsterMachineBullet.h"
#include "EffectMonsterDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"



CMonsterMachine::CMonsterMachine()
{
	m_Tag = TAG_BOSS;
}


CMonsterMachine::~CMonsterMachine()
{
	Release();
}

void CMonsterMachine::Initialize()
{
	m_tInfo.fCX = 475.f;
	m_tInfo.fCY = 430.f;
	m_fSpeed = 4.f;
	m_iHp = 20;
	m_iAttack = 1;
	
	//m_bAttack = false;

	m_pFrameKey = L"Run_Machine";
	m_eCurState = IDLE;

	m_dwPhaseTime = long(0);
	m_dwAttackTime = long(0);
	m_dwAttackSoundTime = long(0);
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
}

int CMonsterMachine::Update()
{
	if (m_bDead || !m_iHp)
	{
		if (!m_bDead)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectMonsterDead>::Create(m_tInfo.fX, m_tInfo.fY, 0));
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_platforming_arcade_death_02.wav", SOUND_EFFECT, g_fSound_EFFECT);
		}

		m_bDead = true;
		m_eCurState = DEAD;

		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		if (GetTickCount() - m_dwDeadMotionTime > 2000)
			return OBJ_DEAD;
	}
	else
	{
		if (m_pPlayer->Get_Info().fX > 9500.f && m_dwPhaseTime == long(0))
			m_dwPhaseTime = GetTickCount();
		
		Set_Phase();
	}

	////최적화 관련
	////if (m_pPlayer->Get_Info().fX > 10200.f)
	////{
	//m_bAttack = true;
	////m_dwAttackTime = GetTickCount();
	////}

	//if (m_bAttack)
	//{
	//	if (GetTickCount() - m_dwAttackTime > 1000)
	//	{
	//		//불릿 발사
	//		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterMachineBullet>::Create(m_tInfo.fX, rand() % 570 - 400, rand() % 3 + 1));
	//		m_dwAttackTime = GetTickCount();
	//	}
	//}

	Update_Rect();
	Update_RectCollision(120.f, 0.f, 120.f, 0.f);

	return OBJ_NOEVENT;
}

void CMonsterMachine::Late_Update()
{
	Motion_Change();
	Move_Frame();
}

void CMonsterMachine::Render(HDC hDC)
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

}

void CMonsterMachine::Release()
{
}

void CMonsterMachine::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMonsterMachine::Set_Phase()
{
	// 공격
	if (2000 < GetTickCount() - m_dwPhaseTime && 9000 > GetTickCount() - m_dwPhaseTime)
	{

		if (m_dwAttackTime == 0)
		{
			m_dwAttackTime = GetTickCount();
			m_dwAttackSoundTime = GetTickCount();
			//CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_MACHINE, 0.8f);
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_platform_plank_platform_drop_01.wav", SOUND_MACHINE, g_fSound_MONSTER);

		}

		m_eCurState = ATTACK;

		if (1300 < GetTickCount() - m_dwAttackSoundTime)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_platform_plank_platform_drop_01.wav", SOUND_MACHINE, g_fSound_MONSTER);
			m_dwAttackSoundTime = GetTickCount();
		}

		if (700 < GetTickCount() - m_dwAttackTime)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterMachineBullet>::Create(m_pPlayer->Get_Info().fX, 10));
			m_dwAttackTime = GetTickCount();
		}
	}
	 //휴식
	else if (9000 < GetTickCount() - m_dwPhaseTime && 12000 > GetTickCount() - m_dwPhaseTime)
	{
		m_dwAttackTime = 0;
		m_eCurState = IDLE;
		m_dwPhaseTime = GetTickCount();
	}
}
#include "stdafx.h"
#include "MonsterOnion.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "MonsterOnionBullet.h"
#include "MonsterOnionParry.h"
#include "EffectMonsterDead.h"

CMonsterOnion::CMonsterOnion()
{
	m_Tag = TAG_BOSS;
}


CMonsterOnion::~CMonsterOnion()
{
	Release();
}

void CMonsterOnion::Initialize()
{
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 444.f;
	m_fSpeed = 5.f;
	m_iHp = 50;
	m_iAttack = 1;

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_bSoundCrying = false;

	m_pFrameKey = L"Boss_Onion";
	m_eCurState = BIRTH;

	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 17;
	//m_tFrame.iMotion = 0;
	//m_tFrame.dwSpeed = 100;
	//m_tFrame.dwTime = GetTickCount();

	m_dwPhaseTime = GetTickCount();
	m_dwAttackTime = long(0);
}

int CMonsterOnion::Update()
{
	if (m_bDead || !m_iHp)
	{
		if (!m_bDead)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectMonsterDead>::Create(m_tInfo.fX, m_tInfo.fY, 1));
			//CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Onion_Die.wav", SOUND_MONSTER, g_fSound_MONSTER);
		}

		m_bDead = true;
		m_eCurState = DEAD;


		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		if (GetTickCount() - m_dwDeadMotionTime > 2500)
			return OBJ_DEAD;
	}
	else
	{
		Set_Phase();
	}
	Update_Rect();
	Update_RectCollision(100.f, 220.f, 100.f, 30.f);		// 충돌 렉트 별도 설정

	return OBJ_NOEVENT;
}

void CMonsterOnion::Late_Update()
{
	Motion_Change();
	Move_Frame();
}

void CMonsterOnion::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
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

void CMonsterOnion::Release()
{
}

void CMonsterOnion::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BIRTH:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 130;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMonsterOnion::Set_Phase()
{
	srand(time(NULL));
	int rd = rand() % 10;

	// 1페이즈
	if (2000 < GetTickCount() - m_dwPhaseTime && 8500 > GetTickCount() - m_dwPhaseTime)
	{
		if (m_dwAttackTime == 0)
			m_dwAttackTime = GetTickCount();

		if (!m_bSoundCrying)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Onion_Crying.wav", SOUND_MONSTER, g_fSound_MONSTER);
			m_bSoundCrying = true;
		}
		m_eCurState = ATTACK;
		if (1000 < GetTickCount() - m_dwAttackTime)
		{
			if (6 > rd)
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterOnionBullet>::Create(m_pPlayer->Get_Info().fX, 10));
			else
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterOnionParry>::Create(m_pPlayer->Get_Info().fX, 10));

			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Onion_Teardrop_01.wav", SOUND_EFFECT, g_fSound_EFFECT);
			m_dwAttackTime = GetTickCount();
		}
	}
	// 휴식
	else if (8500 < GetTickCount() - m_dwPhaseTime && 10000 > GetTickCount() - m_dwPhaseTime)
	{
		m_dwAttackTime = 0;
		m_eCurState = IDLE;
		m_bSoundCrying = false;
		CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
	}
	// 2페이즈
	else if (10000 < GetTickCount() - m_dwPhaseTime && 14500 > GetTickCount() - m_dwPhaseTime)
	{
		if (m_dwAttackTime == 0)
			m_dwAttackTime = GetTickCount();

		if (!m_bSoundCrying)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Onion_Crying.wav", SOUND_MONSTER, g_fSound_MONSTER);
			m_bSoundCrying = true;
		}

		m_eCurState = ATTACK;
		m_tFrame.dwSpeed = 60;
		if (800 < GetTickCount() - m_dwAttackTime)
		{
			if (6 > rd)
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterOnionBullet>::Create(m_pPlayer->Get_Info().fX, 10));
			else
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterOnionParry>::Create(m_pPlayer->Get_Info().fX, 10));

			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Onion_Teardrop_01.wav", SOUND_EFFECT, g_fSound_EFFECT);
			m_dwAttackTime = GetTickCount();
		}
	}
	// 끝
	else if (14500 < GetTickCount() - m_dwPhaseTime)
	{
		m_dwAttackTime = 0;
		m_eCurState = IDLE;
		m_dwPhaseTime = GetTickCount();
		m_bSoundCrying = false;
		CSoundMgr::Get_Instance()->StopSound(SOUND_MONSTER);
	}
}

#include "stdafx.h"
#include "MonsterPotato.h"
#include "MonsterPotatoBullet.h"
#include "MonsterPotatoParry.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "EffectMonsterDead.h"

CMonsterPotato::CMonsterPotato()
{
	m_Tag = TAG_BOSS;
}


CMonsterPotato::~CMonsterPotato()
{
	Release();
}

void CMonsterPotato::Initialize()
{
	m_tInfo.fCX = 450.f;
	m_tInfo.fCY = 440.f;
	m_fSpeed = 5.f;
	m_iHp = 50;
	m_iAttack = 1;

	m_pFrameKey = L"Boss_Potato";
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 19;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	
	m_dwPhaseTime = GetTickCount();
	m_dwAttackTime = 0;
}

int CMonsterPotato::Update()
{
	if (m_bDead || !m_iHp)
	{
		if (!m_bDead)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectMonsterDead>::Create(m_tInfo.fX, m_tInfo.fY, 1));
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_dice_chips_vox_death.wav", SOUND_MONSTER, g_fSound_MONSTER);
		}

		m_bDead = true;
		m_eCurState = DEAD;
		m_tInfo.fY += 3.f;
		
		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		if (GetTickCount() - m_dwDeadMotionTime > 3000)
			return OBJ_DEAD;
	}
	else
	{
		Set_Phase();
	}

	Update_Rect();
	Update_RectCollision(130.f, 110.f, 100.f, 30.f);		// 충돌 렉트 별도 설정

	return OBJ_NOEVENT;
}

void CMonsterPotato::Late_Update()
{
	Motion_Change();
	Move_Frame();
}

void CMonsterPotato::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left /*+ iScrollX*/),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top /*+ iScrollY*/),
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

void CMonsterPotato::Release()
{
	//CObjMgr::Get_Instance()->Destroy_Instance();
	//CSoundMgr::Get_Instance()->StopAll();
}

void CMonsterPotato::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 19;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 16;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CMonsterPotato::Set_Phase()
{
	srand(time(NULL));
	int rd = rand() % 10;

	// 1페이즈
	if (3000 < GetTickCount() - m_dwPhaseTime && 8000 > GetTickCount() - m_dwPhaseTime)
	{
		if (m_dwAttackTime == 0)
			m_dwAttackTime = GetTickCount();
		m_eCurState = ATTACK;

		if (1500 < GetTickCount() - m_dwAttackTime)
		{
			if (6 > rd)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterPotatoBullet>::Create(m_tInfo.fX - 150, m_tInfo.fY + 130));
			}
			else
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterPotatoParry>::Create(m_tInfo.fX - 150, m_tInfo.fY + 130));
			}

			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Potato_Spit_01.wav", SOUND_MONSTER, g_fSound_MONSTER);
			m_dwAttackTime = GetTickCount();
		}
	}
	// 휴식
	else if (8000 < GetTickCount() - m_dwPhaseTime && 10000 > GetTickCount() - m_dwPhaseTime)
	{
		m_dwAttackTime = long(0);
		m_eCurState = IDLE;
	}
	// 2페이즈
	else if (10000 < GetTickCount() - m_dwPhaseTime && 14500 > GetTickCount() - m_dwPhaseTime)
	{
		if (m_dwAttackTime == 0)
			m_dwAttackTime = GetTickCount();
		m_eCurState = ATTACK;
		m_tFrame.dwSpeed = 60;
		if (1000 < GetTickCount() - m_dwAttackTime)
		{
			if (6 > rd)
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterPotatoBullet>::Create(m_tInfo.fX - 150, m_tInfo.fY + 130));
			else
				CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterPotatoParry>::Create(m_tInfo.fX - 150, m_tInfo.fY + 130));

			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Potato_Spit_01.wav", SOUND_MONSTER, g_fSound_MONSTER);
			m_dwAttackTime = GetTickCount();
		}
	}
	// 끝
	else if (14500 < GetTickCount() - m_dwPhaseTime)
	{
		m_dwAttackTime = long(0);
		m_eCurState = IDLE;
		m_dwPhaseTime = GetTickCount();
	}
}

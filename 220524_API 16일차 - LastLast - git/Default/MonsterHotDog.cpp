#include "stdafx.h"
#include "MonsterHotDog.h"
#include "MonsterHotDogBullet.h"
#include "EffectMonsterDead.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMonsterHotDog::CMonsterHotDog()
{
	m_Tag = TAG_BOSS;
}


CMonsterHotDog::~CMonsterHotDog()
{
	Release();
}

void CMonsterHotDog::Initialize()
{
	m_fBirthX = m_tInfo.fX;

	m_tInfo.fCX = 325.6f;
	m_tInfo.fCY = 350.f;

	m_fSpeed = 4.f;

	m_iHp = 30;
	m_iAttack = 1;

	m_bAttack = false;

	m_pFrameKey = L"Run_Boss";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_dwAttackTime = long(0);

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
}

int CMonsterHotDog::Update()
{
	if (m_bDead || !m_iHp)
	{
		if (!m_bDead)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectMonsterDead>::Create(m_tInfo.fX, m_tInfo.fY, 0));
			CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_level_platform_hotdog_death.wav", SOUND_MONSTER, g_fSound_MONSTER);
		}
			
		m_bDead = true;
		m_eCurState = DEAD;
		m_pFrameKey = L"Run_Boss_Death";
		m_tInfo.fCX = 357.2f;
		m_tInfo.fCY = 400.f;

		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		if (GetTickCount() - m_dwDeadMotionTime > 2000)
			return OBJ_DEAD;
	}
	
	//최적화 관련
	if (m_pPlayer->Get_Info().fX > 10200.f)
	{
		m_bAttack = true;
		if(!m_dwAttackTime)
			m_dwAttackTime = GetTickCount();
	}
		
	if (m_bAttack)
	{
		if (GetTickCount() - m_dwAttackTime > 1500)
		{
			//불릿 발사
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterHotDogBullet>::Create(m_tInfo.fX, rand() % 570 - 400, rand() % 3 + 1));
			CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_level_platform_hotdog_projectile_shoot_04.wav", SOUND_MONSTER, g_fSound_MONSTER);

			m_dwAttackTime = GetTickCount();
		}
	}

	//CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_level_platform_hotdog_dance_01.wav", SOUND_MONSTER, g_fSound_MONSTER);

	Update_Rect();
	Update_RectCollision(50.f, 50.f, 50.f, 50.f);

	return OBJ_NOEVENT;
}

void CMonsterHotDog::Late_Update()
{
	Motion_Change();
	Move_Frame();
}

void CMonsterHotDog::Render(HDC hDC)
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

void CMonsterHotDog::Release()
{
}

void CMonsterHotDog::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CMonsterHotDog::Set_Phase()
{
}

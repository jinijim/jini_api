#include "stdafx.h"
#include "MonsterCrown.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"
#include "EffectMonsterDead.h"


CMonsterCrown::CMonsterCrown()
{
	m_Tag = TAG_MONSTER;
}


CMonsterCrown::~CMonsterCrown()
{
	Release();
}

void CMonsterCrown::Initialize()
{
	m_fBirthX = m_tInfo.fX;

	m_tInfo.fCX = 153.6f;
	m_tInfo.fCY = 250.f;
	
	m_fSpeed = 4.f;
	if (m_iOption == 2) // 빨간애면 방향 다르게
		m_fSpeed *= -1;
	m_iHp = 10;
	m_iAttack = 1;

	if(m_iOption == 1)
		m_pFrameKey = L"Run_Crown_Blue";
	else
		m_pFrameKey = L"Run_Crown_Red";

	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CMonsterCrown::Update()
{
	if (m_bDead || !m_iHp)
	{
		if (!m_bDead)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectMonsterDead>::Create(m_tInfo.fX, m_tInfo.fY, 10));
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_train_lollipop_cannon_ghost_death_02.wav", SOUND_MONSTER, g_fSound_MONSTER);
		}
		
		m_bDead = true;
		m_eCurState = DEAD;

		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		if (GetTickCount() - m_dwDeadMotionTime > 3000)
			return OBJ_DEAD;
	}

	// 몬스터 좌우 이동
	m_tInfo.fX += m_fSpeed;

	if (m_iOption == 1 && (m_tInfo.fX < m_fBirthX - 70  || m_tInfo.fX > m_fBirthX + 270))
	{
		m_fSpeed *= -1;
	}
	if (m_iOption == 2 && (m_tInfo.fX < m_fBirthX - 280 || m_tInfo.fX > m_fBirthX + 20))
	{
		m_fSpeed *= -1;
	}
		
	Update_Rect();
	Update_RectCollision(20.f, 20.f, 20.f, 20.f);

	return OBJ_NOEVENT;
}

void CMonsterCrown::Late_Update()
{
	Motion_Change();
	Move_Frame();
}

void CMonsterCrown::Render(HDC hDC)
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

	Rectangle(hDC, (int)m_tRectCollision.left, (int)m_tRectCollision.top, (int)m_tRectCollision.right, (int)m_tRectCollision.bottom);
}

void CMonsterCrown::Release()
{
}

void CMonsterCrown::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

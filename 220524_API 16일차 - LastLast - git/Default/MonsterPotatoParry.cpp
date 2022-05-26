#include "stdafx.h"
#include "MonsterPotatoParry.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CMonsterPotatoParry::CMonsterPotatoParry()
{
	m_Tag = TAG_MONSTER;
}


CMonsterPotatoParry::~CMonsterPotatoParry()
{
	Release();
}

void CMonsterPotatoParry::Initialize(void)
{
	m_tInfo.fCX = 133.f;
	m_tInfo.fCY = 142.f;

	m_fSpeed = 5.f;

	m_iHp = 2;
	m_iAttack = 1;

	m_bParry = true;


	m_pFrameKey = L"Boss_Potato_Parry";
	m_eCurState = IDLE;

	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 3;
	//m_tFrame.iMotion = 0;
	//m_tFrame.dwSpeed = 100;
	//m_tFrame.dwTime = GetTickCount();

	////패링 리스트에 별도 추가
	CObjMgr::Get_Instance()->Add_ObjectParry(this);
}

int CMonsterPotatoParry::Update(void)
{
	if (m_bDead || !m_iHp)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Potato_Worm_Explode_01.wav", SOUND_MONSTER, g_fSound_MONSTER);
		return OBJ_DEAD;
	}

	m_tInfo.fX -= m_fSpeed;
	Update_Rect();
	Update_RectCollision(20.f, 50.f, 30.f, 30.f);

	return OBJ_NOEVENT;
}

void CMonsterPotatoParry::Late_Update(void)
{
	if (0 >= m_tRect.right || WINCX <= m_tRect.left ||
		0 >= m_tRect.bottom || WINCY <= m_tRect.top)
		m_bDead = true;

	Motion_Change();
	Move_Frame();
}

void CMonsterPotatoParry::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),				// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	//Rectangle(hDC, (int)m_tInfo.fX - m_tInfo.fCX * 0.5 , (int)m_tInfo.fY - m_tInfo.fCY * 0.5, (int)m_tInfo.fX + m_tInfo.fCX * 0.5 , (int)m_tInfo.fY + m_tInfo.fCY * 0.5);
	//Rectangle(hDC, (int)m_tRect.left, (int)m_tRect.top, (int)m_tRect.right, (int)m_tRect.bottom);
}

void CMonsterPotatoParry::Release(void)
{
}

void CMonsterPotatoParry::Motion_Change(void)
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
		}
		m_ePreState = m_eCurState;
	}
}
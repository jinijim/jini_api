#include "stdafx.h"
#include "MonsterMachineBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CMonsterMachineBullet::CMonsterMachineBullet()
{
	m_Tag = TAG_MONSTER;
}


CMonsterMachineBullet::~CMonsterMachineBullet()
{
	Release();
}

void CMonsterMachineBullet::Initialize(void)
{
	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 88.f;

	m_fSpeed = 5.f;

	m_iHp = 2;
	m_iAttack = 1;

	m_pFrameKey = L"Run_Machine_Bullet";
	//m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 80;
	m_tFrame.dwTime = GetTickCount();
}

int CMonsterMachineBullet::Update(void)
{
	if (m_bDead || !m_iHp)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;

	Update_Rect();
	Update_RectCollision(15.f, 15.f, 15.f, 15.f);

	return OBJ_NOEVENT;
}

void CMonsterMachineBullet::Late_Update(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (0 + iScrollX >= m_tRect.right || WINCX - iScrollX <= m_tRect.left ||
		0 - iScrollY >= m_tRect.bottom || WINCY + iScrollY <= m_tRect.top)
		m_bDead = true;

	//Motion_Change();
	Move_Frame();
}

void CMonsterMachineBullet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
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

void CMonsterMachineBullet::Release(void)
{
}

void CMonsterMachineBullet::Motion_Change(void)
{
}

#include "stdafx.h"
#include "UI_Weapon.h"

#include "ObjMgr.h"
#include "BmpMgr.h"
#include "Player.h"


CUI_Weapon::CUI_Weapon()
{
}


CUI_Weapon::~CUI_Weapon()
{
	Release();
}

void CUI_Weapon::Initialize()
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_pFrameKey = L"UI_Weapon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iMotion = 0;

	m_dwMoveTime = long(0);
	m_bMove = false;
}

int CUI_Weapon::Update()
{
	if (!(m_pPlayer->Get_Dead()))
	{
		m_iPlayerGunBefore = m_iPlayerGun;
		m_iPlayerGun = dynamic_cast<CPlayer*>(m_pPlayer)->Get_iGun();
		m_tFrame.iFrameStart = m_iPlayerGun;
		m_tFrame.iFrameEnd = m_iPlayerGun;

		if (m_iOption == 3)
		{
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 2;
		}

		if (m_iPlayerGunBefore != m_iPlayerGun)
		{
			m_bMove = true;
			m_dwMoveTime = GetTickCount();
			m_tInfo.fY = 600;
		}

		if (m_bMove)
			Move();
	}
	return OBJ_NOEVENT;
}

void CUI_Weapon::Late_Update()
{
}

void CUI_Weapon::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tInfo.fX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tInfo.fY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
										/*RGB(255, 255, 255));*/
}

void CUI_Weapon::Release()
{
}

void CUI_Weapon::Move()
{
	if (GetTickCount() - m_dwMoveTime > 2000)
	{
		m_bMove = false;
		m_dwMoveTime = GetTickCount();
	}

	if (m_tInfo.fY > 500)
		m_tInfo.fY -= 8.f;
}
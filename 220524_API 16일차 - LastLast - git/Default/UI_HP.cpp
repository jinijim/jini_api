#include "stdafx.h"
#include "UI_HP.h"

#include "ObjMgr.h"
#include "BmpMgr.h"


CUI_HP::CUI_HP()
{
}


CUI_HP::~CUI_HP()
{
	Release();
}

void CUI_HP::Initialize()
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 28.f;
	m_fSpeed = 3.f;
	m_bMove = false;
	m_MoveIndex = 0;
	m_fBirthX = m_tInfo.fX;

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_iPlayerHpBefore = m_pPlayer->Get_Hp();
	m_iPlayerHp = m_pPlayer->Get_Hp();

	m_tFrame.iMotion = 0;
	m_pFrameKey = L"UI_Hp";

	/*m_tFrame.dwSpeed = 80;
	m_tFrame.dwTime = GetTickCount();*/

}

int CUI_HP::Update()
{
	m_iPlayerHpBefore = m_iPlayerHp;
	m_iPlayerHp = m_pPlayer->Get_Hp();

	if (m_iPlayerHpBefore != m_iPlayerHp)
	{
		m_bMove = true;
		m_dwMoveTime = GetTickCount();
		m_dwMoveCoolTime = GetTickCount();
		m_tFrame.iMotion = 1;
	}
	
	if (m_bMove)
		Move();

	m_tFrame.iFrameStart = m_iPlayerHp;
	m_tFrame.iFrameEnd = m_iPlayerHp;

	return OBJ_NOEVENT;
}

void CUI_HP::Late_Update()
{
}

void CUI_HP::Render(HDC hDC)
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

void CUI_HP::Release()
{
}

void CUI_HP::Move()
{
	if (m_tInfo.fX >= m_fBirthX + 3.f)
		m_fSpeed *= -1;

	if (m_tInfo.fX <= m_fBirthX - 3.f)
		m_fSpeed *= -1;

	if (GetTickCount() - m_dwMoveCoolTime > 35)
	{
		m_tInfo.fX += m_fSpeed;
		//if(m_MoveIndex == 0)
		//	m_tInfo.fX = m_fBirthX + 5.f;
		m_dwMoveCoolTime = GetTickCount();
	}

	if (GetTickCount() - m_dwMoveTime > 1500)
	{
		m_bMove = false;
		m_dwMoveTime = GetTickCount();
		m_tFrame.iMotion = 0;
		m_tInfo.fX = m_fBirthX;
	}
}

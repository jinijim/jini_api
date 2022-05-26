#include "stdafx.h"
#include "Item.h"
#include "BmpMgr.h"


CItem::CItem()
{
}


CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	m_pFrameKey = L"Shop_Item";
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 150.f;
	m_fSpeed = 3.f;

	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 1;

	m_iState = 1;
	m_tFrame.iMotion = m_iOption;	// 장난감총, 곡사포, HP

	m_fBirthY = m_tInfo.fY;
	m_dwMoveCoolTime = long(0);
	m_dwMoveTime = long(0);
	m_bMove = false;
}

int CItem::Update()
{
	Update_Rect();
	m_tFrame.iFrameStart = m_iState;

	if (m_bMove)
	{
		if (!m_dwMoveTime)
		{
			m_dwMoveTime = GetTickCount();
			m_dwMoveCoolTime = GetTickCount();
		}
		Move();
	}

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
}

void CItem::Render(HDC hDC)
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

}

void CItem::Release()
{
}

void CItem::Motion_Change()
{
}

void CItem::Move()
{
	if (m_tInfo.fY >= m_fBirthY + 3.f)
		m_fSpeed *= -1;

	if (m_tInfo.fY <= m_fBirthY - 3.f)
		m_fSpeed *= -1;

	if (GetTickCount() - m_dwMoveCoolTime > 35)
	{
		m_tInfo.fY += m_fSpeed;
		//if(m_MoveIndex == 0)
		//	m_tInfo.fX = m_fBirthX + 5.f;
		m_dwMoveCoolTime = GetTickCount();
	}

	if (GetTickCount() - m_dwMoveTime > 600)
	{
		m_bMove = false;
		m_dwMoveTime = long(0);
		m_tInfo.fY = m_fBirthY;
	}
}

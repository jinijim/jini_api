#include "stdafx.h"
#include "Shop_Piggy.h"

#include "BmpMgr.h"


CShop_Piggy::CShop_Piggy()
{
}

CShop_Piggy::~CShop_Piggy()
{
	Release();
}

void CShop_Piggy::Initialize()
{
	m_tInfo.fCX = 349.66f;
	m_tInfo.fCY = 312.f;

	m_pFrameKey = L"Shop_Piggy_IDLE";
	m_eCurState = IDLE;

}

int CShop_Piggy::Update()
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CShop_Piggy::Late_Update()
{
	Motion_Change();

	if (m_eCurState == IDLE)
		Move_Frame();
	else
		Move_Frame_MultiLine(8, 4);
}

void CShop_Piggy::Render(HDC hDC)
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
		RGB(255, 255, 255));
}

void CShop_Piggy::Release()
{
}

void CShop_Piggy::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BYE:
			m_tInfo.fCX = 400.f;
			m_tInfo.fCY = 345.f;
			m_pFrameKey = L"Shop_Piggy_GOODBYE";
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 70;
			m_tFrame.dwTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}
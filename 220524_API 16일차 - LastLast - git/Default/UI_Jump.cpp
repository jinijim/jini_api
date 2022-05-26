#include "stdafx.h"
#include "UI_Jump.h"

#include "BmpMgr.h"

CUI_Jump::CUI_Jump()
{
}


CUI_Jump::~CUI_Jump()
{
	Release();
}

void CUI_Jump::Initialize()
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	m_pFrameKey = L"UI_Weapon";
	m_tFrame.iFrameStart = 2;
	m_tFrame.iMotion = 0;

	m_dwMoveTime = long(0);
	m_bMove = true;
}

int CUI_Jump::Update()
{
	if (m_bMove)
	{
		if (m_tInfo.fY > 440)
			m_tInfo.fY -= 8.f;
		else
			m_bMove = false;
	}

	return OBJ_NOEVENT;
}

void CUI_Jump::Late_Update()
{
}

void CUI_Jump::Render(HDC hDC)
{
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
		RGB(255, 255, 255));
}

void CUI_Jump::Release()
{
}

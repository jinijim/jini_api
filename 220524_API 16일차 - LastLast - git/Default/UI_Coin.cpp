#include "stdafx.h"
#include "UI_Coin.h"

#include "BmpMgr.h"

CUI_Coin::CUI_Coin()
{
}


CUI_Coin::~CUI_Coin()
{
	Release();
}

void CUI_Coin::Initialize()
{
	m_tInfo.fCX = 39.f;
	m_tInfo.fCY = 55.f;

	//m_tFrame.iFrameStart = g_iCoin;
	//m_tFrame.iFrameEnd = g_iCoin;

	m_tFrame.iMotion = 0;
	/*m_tFrame.dwSpeed = 80;
	m_tFrame.dwTime = GetTickCount();*/

	m_pFrameKey = L"Coin_Get";
}

int CUI_Coin::Update()
{
	m_tFrame.iFrameStart = g_iCoin;
	//m_tFrame.iFrameEnd = g_iCoin;

	return OBJ_NOEVENT;
}

void CUI_Coin::Late_Update()
{
}

void CUI_Coin::Render(HDC hDC)
{
	if (g_iCoin)
	{
		// 동전모양
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tInfo.fX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tInfo.fY),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			0 * (int)m_tInfo.fCX,					// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));

		// 숫자
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tInfo.fX + m_tInfo.fCX),	// 2,3 인자 :  복사받을 위치 X, Y
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
}

void CUI_Coin::Release()
{
}

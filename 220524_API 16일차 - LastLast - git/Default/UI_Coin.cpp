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
		// �������
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tInfo.fX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tInfo.fY),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0 * (int)m_tInfo.fCX,					// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));

		// ����
		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tInfo.fX + m_tInfo.fCX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tInfo.fY),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
}

void CUI_Coin::Release()
{
}

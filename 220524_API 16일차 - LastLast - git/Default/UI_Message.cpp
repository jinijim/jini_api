#include "stdafx.h"
#include "UI_Message.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CUI_Message::CUI_Message()
{
}

CUI_Message::~CUI_Message()
{
	Release();
}

void CUI_Message::Initialize()
{
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 450.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	switch (m_iOption)
	{
	case 1 :
		m_pFrameKey = L"UI_Bravo";
		m_iX = 2;
		m_iY = 7;
		break;
	case 2:
		m_pFrameKey = L"UI_Run";
		m_iX = 2;
		m_iY = 6;
		break;
	case 3:
		m_pFrameKey = L"UI_YouDied";
		m_iX = 2;
		m_iY = 7;
		m_tInfo.fCX = 1079.f;
		m_tInfo.fCY = 235.142f;
		m_tFrame.dwSpeed = 400;
		break;
	case 4:
		m_pFrameKey = L"UI_Ready";
		m_iX = 4;
		m_iY = 10;
		m_tInfo.fCX = 800.f;
		m_tInfo.fCY = 600.f;
		break;
	case 5:
		m_pFrameKey = L"UI_DoubleJump";
		m_iX = 1;
		m_iY = 5;
		m_tInfo.fCX = 800.f;
		m_tInfo.fCY = 600.f;
		m_tFrame.dwSpeed = 200;

		break;
	}
}

int CUI_Message::Update()
{
	if (m_tFrame.iMotion >= m_iY)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CUI_Message::Late_Update()
{
	Move_Frame_MultiLine(m_iX, m_iY);
}

void CUI_Message::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_iOption == 4) // Stage
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left /*+ iScrollX*/),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + 3 /*+ iScrollY*/),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(141, 141, 141));			// �����ϰ��� �ϴ� ����
	}
	else if (m_iOption == 5) // Run_ DoubleJump
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left /*+ iScrollX*/),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + 50 /*+ iScrollY*/),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(141, 141, 141));			// �����ϰ��� �ϴ� ����
	}
	else
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left /*+ iScrollX*/),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top + 100/*+ iScrollY*/),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(141, 141, 141));
	}
}

void CUI_Message::Release()
{
}

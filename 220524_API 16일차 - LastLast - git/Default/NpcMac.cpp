#include "stdafx.h"
#include "NpcMac.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "CoinBig.h"

CNpcMac::CNpcMac()
{
}


CNpcMac::~CNpcMac()
{
	Release();
}

void CNpcMac::Initialize()
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 140.f;

	m_tInfo.fX = 810.f;
	m_tInfo.fY = 450.f;

	m_pFrameKey = L"Npc_Mac";
	m_eCurState = IDLE;
	m_iTalkNo = -1;
	m_bCoinGet = false;

	m_pCoin = nullptr;
}

void CNpcMac::Update()
{
	Update_Rect();
	
	if (!m_bCoinGet && m_iTalkNo >= 3)
	{
		m_pCoin = new CCoinBig(250, 300);
		m_pCoin->Initialize();
		m_pCoin->Update();
		m_bCoinGet = true;
	}
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	//{
	//	++m_iTalkNo;
	//}
}

void CNpcMac::Late_Update()
{
	if(m_pCoin)
		m_pCoin->Late_Update();
	Motion_Change();
	Move_Frame();
}

void CNpcMac::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����

	if (m_iTalkNo < 3)
		Render_Talk(hDC);
	else if (m_pCoin)
		m_pCoin->Render(hDC);
	//switch (m_iTalkNo)
	//{
	//case 0:
	//	break;
	//case 1:
	//	break;
	//case 2:
	//	break;
	//case 4:
	//	break;
	//}

	//cout << m_iTalkNo << endl;

}

void CNpcMac::Release()
{
	if (m_pCoin)
		Safe_Delete<CWorldObj*>(m_pCoin);
}

void CNpcMac::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;

		case LIVE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 90;
			m_tFrame.dwTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}

void CNpcMac::Render_Talk(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Npc_Mac_Talk");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tInfo.fX - 150.f + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tInfo.fY - 100.f + iScrollY),
		int(346),				// 4,5 ���� : ������� ����, ���� ����
		int(69),
		hMemDC2,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_iTalkNo * 69,
		int(346),				// ������ ��Ʈ���� ����, ���� ����
		int(69),
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
}

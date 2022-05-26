#include "stdafx.h"
#include "ObjRun_NonCollision.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CObjRun_NonCollision::CObjRun_NonCollision()
{
}


CObjRun_NonCollision::~CObjRun_NonCollision()
{
	Release();
}

void CObjRun_NonCollision::Initialize()
{
	m_bCollision = false;

	switch (m_iOption)
	{
	case 1: //
		m_pFrameKey = L"RunNonCol_1";
		m_tInfo.fCX = 730.f;
		m_tInfo.fCY = 372.f;
		break;
	case 2: //
		m_pFrameKey = L"RunNonCol_2_Ticket";
		m_tInfo.fCX = 258.f;
		m_tInfo.fCY = 348.f;
		break;
	case 3:
		m_pFrameKey = L"RunNonCol_3_balloon";
		m_tInfo.fCX = 186.f;
		m_tInfo.fCY = 387.f;
		break;
	case 4: //
		m_pFrameKey = L"RunNonCol_4_Booth";
		m_tInfo.fCX = 405.f;
		m_tInfo.fCY = 495.f;
		break;
	case 5:
		m_pFrameKey = L"RunNonCol_5_Booth2";
		m_tInfo.fCX = 487.f;
		m_tInfo.fCY = 496.f;
	case 6://
		m_pFrameKey = L"RunNonCol_6_cm1";
		m_tInfo.fCX = 700.f;
		m_tInfo.fCY = 399.f;
		break;
	case 7://
		m_pFrameKey = L"RunNonCol_7_cm2";
		m_tInfo.fCX = 800.f;
		m_tInfo.fCY = 464.f;
		break;
	case 8:
		m_pFrameKey = L"RunNonCol_8_Opening";
		m_tInfo.fCX = 133.f;
		m_tInfo.fCY = 152.f;
		break;
	case 9://
		m_pFrameKey = L"RunNonCol_9_Opening2";
		m_tInfo.fCX = 167.f;
		m_tInfo.fCY = 177.f;
		break;
	case 10://
		m_pFrameKey = L"RunNonCol_10_Pannel";
		m_tInfo.fCX = 320.f;
		m_tInfo.fCY = 336.f;
		break;
	case 11:
		m_pFrameKey = L"RunNonCol_11_Shop";
		m_tInfo.fCX = 359.f;
		m_tInfo.fCY = 340.f;
		break;
	case 12:
		m_pFrameKey = L"RunNonCol_12_Shop2";
		m_tInfo.fCX = 133.f;
		m_tInfo.fCY = 152.f;
		break;
	case 13:
		m_pFrameKey = L"RunNonCol_13_Shop3";
		m_tInfo.fCX = 344.f;
		m_tInfo.fCY = 346.f;
		break;
	case 14:
		m_pFrameKey = L"RunNonCol_14_Shop4";
		m_tInfo.fCX = 133.f;
		m_tInfo.fCY = 152.f;
		break;
	case 15:
		m_pFrameKey = L"RunNonCol_15_Shop5";
		m_tInfo.fCX = 133.f;
		m_tInfo.fCY = 152.f;
		break;
	case 16: //
		m_pFrameKey = L"RunNonCol_16_Shop6";
		m_tInfo.fCX = 223.f;
		m_tInfo.fCY = 246.f;
		break;
	case 17:
		m_pFrameKey = L"RunNonCol_17_Shop7";
		m_tInfo.fCX = 133.f;
		m_tInfo.fCY = 152.f;
		break;
	case 18://
		m_pFrameKey = L"RunNonCol_18_Shop8";
		m_tInfo.fCX = 320.f;
		m_tInfo.fCY = 328.f;
		break;
	case 19://
		m_pFrameKey = L"RunNonCol_19_Shop9";
		m_tInfo.fCX = 300.f;
		m_tInfo.fCY = 450.f;
		break;
	}

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CObjRun_NonCollision::Update()
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CObjRun_NonCollision::Late_Update()
{
}

void CObjRun_NonCollision::Render(HDC hDC)
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
}

void CObjRun_NonCollision::Release()
{
}

void CObjRun_NonCollision::Motion_Change()
{
	// None
}

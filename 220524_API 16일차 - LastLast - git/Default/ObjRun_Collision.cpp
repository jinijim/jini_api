#include "stdafx.h"
#include "ObjRun_Collision.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CObjRun_Collision::CObjRun_Collision()
{
}


CObjRun_Collision::~CObjRun_Collision()
{
	Release();
}

void CObjRun_Collision::Initialize()
{
	m_bCollision = true;

	switch (m_iOption)
	{
	case 1:
		m_pFrameKey = L"Phase1";
		m_tInfo.fCX = 101.f;
		m_tInfo.fCY = 600.f;
		break;
	case 2:
		m_pFrameKey = L"Box";
		m_tInfo.fCX = 170.f;
		m_tInfo.fCY = 210.f;
		break;
	case 3:
		m_pFrameKey = L"Box2";
		m_tInfo.fCX = 146.f;
		m_tInfo.fCY = 210.f;
		break;
	case 4:
		m_pFrameKey = L"Box3";
		m_tInfo.fCX = 141.f;
		m_tInfo.fCY = 210.f;
		break;
	case 5://
		m_pFrameKey = L"PinkBell";
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 72.f;
		m_fSpeed = 3.f;
		////패링 리스트에 별도 추가
		CObjMgr::Get_Instance()->Add_ObjectParry(this);
		break;
	case 6:
		m_pFrameKey = L"PinkBellBox";
		m_tInfo.fCX = 284.f;
		m_tInfo.fCY = 400.f;
		break;
	case 7://
		m_pFrameKey = L"Tamberine";
		m_tInfo.fCX = 237.f;
		m_tInfo.fCY = 130.f;
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	}

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CObjRun_Collision::Update()
{
	if (m_iOption == 5)
	{
		m_tInfo.fY += m_fSpeed;
		
		if (m_tInfo.fY < 200.f || m_tInfo.fY > 420.f)
			m_fSpeed *= -1;
	}

	Update_Rect();
	//Update_RectCollision(0.f, 0.f, 0.f, 0.f);
	Update_InfoCollision();

	return OBJ_NOEVENT;
}

void CObjRun_Collision::Late_Update()
{
	m_bDead = false;
}

void CObjRun_Collision::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	//Rectangle(hDC, (int)m_tInfoCollision.fX - m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY - m_tInfoCollision.fCY * 0.5 + iScrollY, (int)m_tInfoCollision.fX + m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY + m_tInfoCollision.fCY * 0.5 + iScrollY);
}

void CObjRun_Collision::Release()
{
}

void CObjRun_Collision::Motion_Change()
{
}

void CObjRun_Collision::Update_InfoCollision()
{
	switch (m_iOption)
	{
	case 1: // 공연장 1 장애물
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY + 150.f;
		m_tInfoCollision.fCX = m_tInfo.fCX - 70.f;
		m_tInfoCollision.fCY = m_tInfo.fCY - 300.f;
		break;
	case 2: // 박스 1~3
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX - 50.f;
		m_tInfoCollision.fCY = m_tInfo.fCY - 20.f;
		break;
	case 3:
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX - 30.f;
		m_tInfoCollision.fCY = m_tInfo.fCY - 30.f;
		break;
	case 4:
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX - 10.f;
		m_tInfoCollision.fCY = m_tInfo.fCY - 30.f;
		break;
	case 5: // PinkBell
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX;
		m_tInfoCollision.fCY = m_tInfo.fCY;
		break;
	case 6: // PinkBox
		m_tInfoCollision.fX = m_tInfo.fX + 70.f;
		m_tInfoCollision.fY = m_tInfo.fY + 50.f;
		m_tInfoCollision.fCX = m_tInfo.fCX - 200.f;
		m_tInfoCollision.fCY = m_tInfo.fCY;
		break;
	case 7:
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX;
		m_tInfoCollision.fCY = m_tInfo.fCY;
		break;
	case 8:
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX;
		m_tInfoCollision.fCY = m_tInfo.fCY;
		break;
	case 9:
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX;
		m_tInfoCollision.fCY = m_tInfo.fCY;
		break;
	case 10:
		m_tInfoCollision.fX = m_tInfo.fX;
		m_tInfoCollision.fY = m_tInfo.fY;
		m_tInfoCollision.fCX = m_tInfo.fCX;
		m_tInfoCollision.fCY = m_tInfo.fCY;
		break;
	}
}
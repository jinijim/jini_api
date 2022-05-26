#include "stdafx.h"
#include "ObjRun_Alphabet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CObjRun_Alphabet::CObjRun_Alphabet()
{
}

CObjRun_Alphabet::~CObjRun_Alphabet()
{
	Release();
}

void CObjRun_Alphabet::Initialize()
{
	m_bCollision = false;
	m_pFrameKey = L"Ground_Run_Alphabet";
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 308.f;
	m_fSpeed = 2.f;

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = m_iOption - 1;
}

int CObjRun_Alphabet::Update()
{
	m_tInfo.fY += m_fSpeed;

	if (m_tInfo.fY < -400.f || m_tInfo.fY > 0.f)
		m_fSpeed *= -1;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CObjRun_Alphabet::Late_Update()
{
}

void CObjRun_Alphabet::Render(HDC hDC)
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
}

void CObjRun_Alphabet::Release()
{
}

void CObjRun_Alphabet::Motion_Change()
{
	// None
}

#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"



CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	if (m_fAngle == 90.f)
	{
		m_pFrameKey = L"Gun_loop_Up";
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 160.f;
	}
	else
	{
		m_pFrameKey = L"Gun_loop";
		m_tInfo.fCX = 160.f;
		m_tInfo.fCY = 50.f;
	}

	m_fSpeed = 20.f;

	m_iHp = 1;
	m_iAttack = 1;
	m_dwDeadMotionTime = long(0);
	m_bDeathOut = false;
}

int CBullet::Update(void)
{
	if (m_bDead || !m_iHp)
	{
		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();

		m_bDead = true;
		m_eCurState = DEAD;
		m_pFrameKey = L"Gun_Death";

		m_tInfo.fCX = 260.f;
		m_tInfo.fCY = 278.f;

		if (GetTickCount() - m_dwDeadMotionTime > 500)
			return OBJ_DEAD;

		return OBJ_NOEVENT;
	}
	
	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	
	Update_Rect();

	if(m_fAngle != 90.f)
		Update_RectCollision(40.f, 20.f, 40.f, 20.f);		// 충돌 렉트 별도 설정
	else
		Update_RectCollision(10.f, 40.f, 10.f, 40.f);		// 충돌 렉트 별도 설정

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// 화면밖에 나가면 총알 죽이기
	if (WINCX + 300 - iScrollX <= m_tRect.left || 0 - 300 + iScrollX >= m_tRect.right ||
		WINCY + 300 + iScrollY <= m_tRect.top || 0 - 300 - iScrollY  >= m_tRect.bottom)
		m_bDead = true;


	Motion_Change();
	Move_Frame();
}

void CBullet::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	if (!m_bDead)
	{
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
	else if (m_bDead && m_fAngle == 0.f)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top - 120.f + iScrollY),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// 제거하고자 하는 색상
	}
	else if (m_bDead && m_fAngle == 180.f)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left - 80.f + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top - 120.f + iScrollY),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// 제거하고자 하는 색상
	}
	

	//Rectangle(hDC, (int)m_tRectCollision.left, (int)m_tRectCollision.top, (int)m_tRectCollision.right, (int)m_tRectCollision.bottom);

}

void CBullet::Release(void)
{
	
}

void CBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

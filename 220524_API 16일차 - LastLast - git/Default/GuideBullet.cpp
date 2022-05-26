#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
	Release();
}


void CGuideBullet::Initialize(void)
{
	m_tInfo.fCX = 51.f;
	m_tInfo.fCY = 54.f;
	m_fSpeed = 7.f;
	m_iHp = 1;
	m_iAttack = 1;

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_AngleTime = GetTickCount();
	m_AngleTime2 = GetTickCount();

	m_fAngleOriginal = 0.f;

	m_bAngleFirst = true;

	m_DeathTime = GetTickCount();

	m_pFrameKey = L"Star_loop";

	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 7;
	//m_tFrame.iMotion = 0;
	//m_tFrame.dwSpeed = 50;
	//m_tFrame.dwTime = GetTickCount();

}

int CGuideBullet::Update(void)
{

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, TAG_BOSS, this);
	//m_pPlayerFrameKey = m_pPlayer->Get_FrameKey();

	if (m_bDead || !m_iHp || m_pTarget == nullptr)
		return OBJ_DEAD;

	if (m_pTarget && !m_fAngleOriginal)
	{
		m_pTargetOriginal = m_pTarget;

		m_fTempX = m_pTarget->Get_Info().fX;
		m_fTempY = m_pTarget->Get_Info().fY;

		float		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
		float		fRadian = acosf(fWidth / fDiagonal);

		m_fAngleOriginal = fRadian * 180.f / PI;

		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			m_fAngleOriginal *= -1.f;
	}

	//오른쪽 볼때
	if (L"Player_RIGHT" == m_pPlayerFrameKey || L"Player_DASH_RIGHT" == m_pPlayerFrameKey)
	{
		// 90이면
		if (m_fAngleOriginal == 90.f)
		{
			m_fAngle = 90.f;
			//점점커지기
			if (GetTickCount() - m_AngleTime > 1000)
			{
				//m_fAngle = m_fAngleOriginal;
				AngleSetting();
				m_fAngle = m_fAngleOriginal * 1.3f;
			}
		}
		// 90보다 크면
		else if (m_fAngleOriginal > 90.f)
		{
			if (m_fAngleOriginal < 130.f)
				m_fAngle = m_fAngleOriginal * 2.5f;
			else if (m_fAngleOriginal < 155.f)
				m_fAngle = m_fAngleOriginal * 3.5f;
			else
				m_fAngle = m_fAngleOriginal * 7.f;

			//점점 커지기
			if (GetTickCount() - m_AngleTime > 350)
			{
				if (GetTickCount() - m_AngleTime2 > 200)
				{
					AngleSetting();
					m_fAngle = m_fAngleOriginal * 1.1f;
					m_AngleTime2 = GetTickCount();
				}
			}
		}
		else
		{
			m_fAngle = m_fAngleOriginal;
		}
	}
	//왼쪽 볼때
	else if (L"Player_LEFT" == m_pPlayerFrameKey || L"Player_DASH_LEFT" == m_pPlayerFrameKey)
	{
		// 90이면
		if (m_fAngleOriginal == 90.f)
		{
			m_fAngle = 90.f;
			//점점 작아지기
			if (GetTickCount() - m_AngleTime > 1000)
			{
				AngleSetting();
				m_fAngle = m_fAngleOriginal * 0.7f;
			}
		}
		// 90보다 작으면
		else if (m_fAngleOriginal < 90.f)
		{
			if (m_fAngleOriginal > 50.f)
				m_fAngle = m_fAngleOriginal * 3.5f;
			else if (m_fAngleOriginal > 25.f)
				m_fAngle = m_fAngleOriginal * 5.5f;
			else
				m_fAngle = m_fAngleOriginal * 9.f;

			cout << m_fAngleOriginal << "\t" << m_fAngle << endl;
			//점점 작아지기
			if (GetTickCount() - m_AngleTime > 350)
			{
				if (GetTickCount() - m_AngleTime2 > 200)
				{
					AngleSetting();
					m_fAngle = m_fAngleOriginal * 0.9f;
					m_AngleTime2 = GetTickCount();
				}
			}
		}
		else
		{
			m_fAngle = m_fAngleOriginal;
		}
	}

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);

	Update_Rect();
	Update_RectCollision(0.f, 0.f, 0.f, 0.f);

	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update(void)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//// 화면밖에 나가면 총알 죽이기
	//if (WINCX + 200 - iScrollX <= m_tRect.left || 0 - 200 + iScrollX >= m_tRect.right ||
	//	WINCY + 200 + iScrollY <= m_tRect.top || 0 - 200 - iScrollY >= m_tRect.bottom)
	//	m_bDead = true;

	if (GetTickCount() - m_DeathTime > 5000)
		m_bDead = true;

	Motion_Change();
	Move_Frame();
}

void CGuideBullet::Render(HDC hDC)
{
	//int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	//int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left/* + iScrollX*/),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top/* + iScrollY*/),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상


	//Rectangle(hDC, (int)m_tRectCollision.left, (int)m_tRectCollision.top, (int)m_tRectCollision.right, (int)m_tRectCollision.bottom);
}

void CGuideBullet::Release(void)
{

}

void CGuideBullet::Motion_Change(void)
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

			//case DEAD:
			//	m_tFrame.iFrameStart = 0;
			//	m_tFrame.iFrameEnd = 5;
			//	m_tFrame.iMotion = 0;
			//	m_tFrame.dwSpeed = 100;
			//	m_tFrame.dwTime = GetTickCount();
			//	break;
		}

		m_ePreState = m_eCurState;
	}
}

void CGuideBullet::AngleSetting(void)
{
	if (m_pTarget)
	{
		m_pTargetOriginal = m_pTarget;

		float		fWidth = m_fTempX - m_tInfo.fX;
		float		fHeight = m_fTempY - m_tInfo.fY;

		float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
		float		fRadian = acosf(fWidth / fDiagonal);

		m_fAngleOriginal = fRadian * 180.f / PI;

		if (m_tInfo.fY < m_pTarget->Get_Info().fY)
			m_fAngleOriginal *= -1.f;
	}
}

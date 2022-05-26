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
		Update_RectCollision(40.f, 20.f, 40.f, 20.f);		// �浹 ��Ʈ ���� ����
	else
		Update_RectCollision(10.f, 40.f, 10.f, 40.f);		// �浹 ��Ʈ ���� ����

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// ȭ��ۿ� ������ �Ѿ� ���̱�
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
	else if (m_bDead && m_fAngle == 0.f)
	{
		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top - 120.f + iScrollY),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
	}
	else if (m_bDead && m_fAngle == 180.f)
	{
		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left - 80.f + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top - 120.f + iScrollY),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
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

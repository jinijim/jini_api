#include "stdafx.h"
#include "MonsterOnionBullet.h"
#include "BmpMgr.h"


CMonsterOnionBullet::CMonsterOnionBullet()
{
	m_Tag = TAG_MONSTER;
}


CMonsterOnionBullet::~CMonsterOnionBullet()
{
	Release();
}

void CMonsterOnionBullet::Initialize(void)
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 80.f;

	m_fSpeed = 5.f;

	m_iHp = 2;
	m_iAttack = 1;

	m_bHit = false;
	m_bSuper = false;


	m_pFrameKey = L"Boss_Onion_Bullet";
	m_eCurState = IDLE;

	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 2;
	//m_tFrame.iMotion = 0;
	//m_tFrame.dwSpeed = 100;
	//m_tFrame.dwTime = GetTickCount();
}

int CMonsterOnionBullet::Update(void)
{
	if (m_bDead || !m_iHp)
		return OBJ_DEAD;
/*
	m_bHit = false;
	m_bSuper = false;*/

	m_tInfo.fY += m_fSpeed;
	Update_Rect();
	Update_RectCollision(15.f, 15.f, 15.f, 15.f);

	return OBJ_NOEVENT;
}

void CMonsterOnionBullet::Late_Update(void)
{
	if (0 >= m_tRect.right || WINCX <= m_tRect.left ||
		0 >= m_tRect.bottom || WINCY <= m_tRect.top)
		m_bDead = true;

	Motion_Change();
	Move_Frame();
}

void CMonsterOnionBullet::Render(HDC hDC)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),				// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����

	//Rectangle(hDC, (int)m_tRectCollision.left, (int)m_tRectCollision.top, (int)m_tRectCollision.right, (int)m_tRectCollision.bottom);
}

void CMonsterOnionBullet::Release(void)
{
}

void CMonsterOnionBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

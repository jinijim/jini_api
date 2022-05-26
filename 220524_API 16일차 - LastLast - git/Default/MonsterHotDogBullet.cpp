#include "stdafx.h"
#include "MonsterHotDogBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CMonsterHotDogBullet::CMonsterHotDogBullet()
{
	m_Tag = TAG_MONSTER;
}

CMonsterHotDogBullet::~CMonsterHotDogBullet()
{
	Release();
}

void CMonsterHotDogBullet::Initialize()
{
	//m_tInfo.fCX = 126.f;
	m_tInfo.fCY = 35.f;

	m_fSpeed = 5.f;

	m_iHp = 2;
	m_iAttack = 1;
/*
	m_bCollision = true;*/

	switch (m_iOption)
	{
	case 1:
		m_pFrameKey = L"Run_Boss_Bullet";
		m_tInfo.fCX = 126.f;
		break;
	case 2:
		m_pFrameKey = L"Run_Boss_Bullet2";
		m_tInfo.fCX = 91.f;
		break;
	case 3:
		m_pFrameKey = L"Run_Boss_Bullet3";
		m_tInfo.fCX = 95.8f;
		break;
	}
	m_eCurState = IDLE;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CMonsterHotDogBullet::Update()
{
	if (m_bDead || !m_iHp)
		return OBJ_DEAD;

	m_tInfo.fX -= m_fSpeed;
	Update_Rect();
	Update_RectCollision(0.f, 0.f, 0.f, 0.f);

	return OBJ_NOEVENT;
}

void CMonsterHotDogBullet::Late_Update()
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (10400.f >= m_tRect.right)
		m_bDead = true;

	Motion_Change();
	Move_Frame();
}

void CMonsterHotDogBullet::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),				// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
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

void CMonsterHotDogBullet::Release()
{
}

void CMonsterHotDogBullet::Motion_Change()
{
}

#include "stdafx.h"
#include "EffectMonsterDead.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CEffectMonsterDead::CEffectMonsterDead()
{
}

CEffectMonsterDead::~CEffectMonsterDead()
{
	Release();
}

void CEffectMonsterDead::Initialize()
{
	m_tInfo.fCX = 561.66f;
	m_tInfo.fCY = 556.f;
	m_bDead = true;
	//m_dwDeadTime = long(0);
	m_pFrameKey = L"Effect_Bang";
	//m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 80;
	m_tFrame.dwTime = GetTickCount();
}

int CEffectMonsterDead::Update()
{
	if (m_dwDeadMotionTime == 0)
		m_dwDeadMotionTime = GetTickCount();


	if (m_iOption == 10)
	{
		if (GetTickCount() - m_dwDeadMotionTime > 800)
			return OBJ_DEAD;
	}
	else
	{
		if (GetTickCount() - m_dwDeadMotionTime > 2000)
			return OBJ_DEAD;
	}
	
	// Option�� ���� Effect �������� ȿ��
	if (m_iOption == 1)
	{
		m_tInfo.fY += 3.f;
	}


	Update_Rect();
	return OBJ_NOEVENT;
}

void CEffectMonsterDead::Late_Update()
{
	Move_Frame();
}

void CEffectMonsterDead::Render(HDC hDC)
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
		0,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
}

void CEffectMonsterDead::Release()
{
}

void CEffectMonsterDead::Motion_Change()
{
}

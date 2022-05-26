#include "stdafx.h"
#include "EffectPlayerDust.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CEffectPlayerDust::CEffectPlayerDust()
{
}


CEffectPlayerDust::~CEffectPlayerDust()
{
	Release();
}

void CEffectPlayerDust::Initialize()
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() != SC_WORLD)
	{
		m_tInfo.fCX = 145.f;
		m_tInfo.fCY = 145.f;
		m_pFrameKey = L"Effect_Dust";
	}
	else
	{
		m_tInfo.fCX = 72.5f;
		m_tInfo.fCY = 72.5f;
		m_pFrameKey = L"Effect_Dust_Small";
	}
	m_bDead = true;
	m_fSpeed = 7.f;

	//m_dwDeadTime = long(0);
	
	m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 18;
	m_tFrame.iMotion = m_iOption;
	m_tFrame.dwSpeed = 40;
	m_tFrame.dwTime = GetTickCount();
}

int CEffectPlayerDust::Update()
{
	if (m_dwDeadMotionTime == 0)
		m_dwDeadMotionTime = GetTickCount();

	if (GetTickCount() - m_dwDeadMotionTime > 800)
		return OBJ_DEAD;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CEffectPlayerDust::Late_Update()
{
	Move_Frame();
}

void CEffectPlayerDust::Render(HDC hDC)
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
void CEffectPlayerDust::Release()
{
}

void CEffectPlayerDust::Motion_Change()
{
}

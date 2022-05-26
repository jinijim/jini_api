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
void CEffectPlayerDust::Release()
{
}

void CEffectPlayerDust::Motion_Change()
{
}

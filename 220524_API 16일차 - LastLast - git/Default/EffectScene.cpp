#include "stdafx.h"
#include "EffectScene.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CEffectScene::CEffectScene()
{
}

CEffectScene::~CEffectScene()
{
	Release();
}

void CEffectScene::Initialize()
{
	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 600.f;
	m_bDead = true;
	m_pFrameKey = L"Effect_SceneChange";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 17;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CEffectScene::Update()
{
	if (m_dwDeadMotionTime == 0)
		m_dwDeadMotionTime = GetTickCount();

	if (GetTickCount() - m_dwDeadMotionTime > 2000)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CEffectScene::Late_Update()
{
	Move_Frame_MultiLine(2,6);
}

void CEffectScene::Render(HDC hDC)
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
		0,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
}

void CEffectScene::Release()
{
}

void CEffectScene::Motion_Change()
{
}

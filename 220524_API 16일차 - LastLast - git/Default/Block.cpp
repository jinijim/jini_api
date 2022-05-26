#include "stdafx.h"
#include "Block.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBlock::CBlock()
{
}

CBlock::~CBlock()
{
	Release();
}

void CBlock::Initialize()
{
	m_tInfo.fCX = 224.f;
	m_tInfo.fCY = 192.f;

	m_bCollision = false;
	m_pFrameKey = L"Block1";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CBlock::Update()
{
	Update_Rect();
	//Update_RectCollision(20.f, 40.f, 20.f, 20.f);

	return OBJ_NOEVENT;
}

void CBlock::Late_Update()
{
}

void CBlock::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 							// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),							// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,										// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,							// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));						// 제거하고자 하는 색상

	if (m_bCollision)
		Rectangle(hDC, (int)m_tInfoCollision.fX - m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY - m_tInfoCollision.fCY * 0.5 + iScrollY, (int)m_tInfoCollision.fX + m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY + m_tInfoCollision.fCY * 0.5 + iScrollY);
}

void CBlock::Release()
{
}

void CBlock::Motion_Change()
{
}

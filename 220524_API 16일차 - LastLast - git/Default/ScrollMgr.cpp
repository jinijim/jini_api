#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - TILECX * TILEXSCROLL > m_fScrollX)
		m_fScrollX = WINCX - TILECX * TILEXSCROLL;

	if (WINCY - TILECY * TILEYSCROLL > m_fScrollY)
		m_fScrollY = WINCY - TILECY * TILEYSCROLL;
}

void CScrollMgr::Scroll_LockY()
{
	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - TILECY * TILEYSCROLL > m_fScrollY)
		m_fScrollY = WINCY - TILECY * TILEYSCROLL;
}

void CScrollMgr::Scroll_LockX()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (WINCX - TILECX * TILEXSCROLL > m_fScrollX)
		m_fScrollX = WINCX - TILECX * TILEXSCROLL;
}

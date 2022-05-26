#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"


CLine::CLine()
	: m_tInfo()
{
	
}


CLine::CLine(LINEPOINT& tLeft, LINEPOINT& tRight)
	: m_tInfo(tLeft, tRight)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo.tLPoint.fX + iScrollX, (int)m_tInfo.tLPoint.fY + iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRPoint.fX + iScrollX, (int)m_tInfo.tRPoint.fY + iScrollY);
}

void CLine::Set_InfoMoveY(float _MinY, float _MaxY)
{
	m_tInfo.tLPoint.fY += m_fSpeed;
	m_tInfo.tRPoint.fY += m_fSpeed;

	if (m_tInfo.tLPoint.fY < _MinY || m_tInfo.tLPoint.fY > _MaxY)
	{
		m_fSpeed *= -1;
	}
}

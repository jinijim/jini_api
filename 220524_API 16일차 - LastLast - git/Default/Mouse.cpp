#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CMouse::Update()
{

	POINT	pt{};

	GetCursorPos(&pt);	// ���� ���콺�� ��ġ ��ǥ�� ������ �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ü ��ũ���������� ������ Ŭ���̾�Ʈ(â) ��ǥ�� ��ȯ

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	
	Update_Rect();
	ShowCursor(true);		// ���콺 Ŀ���� ������� �ʰڴ�.

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	

}

void CMouse::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CMouse::Release()
{
	
}

void CMouse::Motion_Change()
{
}

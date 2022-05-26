#include "stdafx.h"
#include "UIInventory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"


CUIInventory::CUIInventory()
{
}


CUIInventory::~CUIInventory()
{
	Release();
}

void CUIInventory::Initialize()
{
	m_tInfo.fX = 10.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 530.f;
	m_tInfo.fCY = 600.f;

	//m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_iDepth = 0;
	m_iChoose = 1;
	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 0;
	m_pFrameKey = L"UI_Inventory";
}

int CUIInventory::Update()
{
	if (m_iDepth == -1)
		return OBJ_DEAD;


	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		m_iDepth += 1;
		if (m_iDepth > 1)
			m_iDepth = 1;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		m_iDepth -= 1;
		if (m_iDepth == -1)
			m_iDepth = -1;
		m_iChoose = 1;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
	{
		m_iChoose += 1;
		if (m_iChoose > 1)
			m_iChoose = 1;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
	{
		m_iChoose -= 1;
		if (m_iChoose < 0)
			m_iChoose = 0;
	}

	return OBJ_NOEVENT;
}

void CUIInventory::Late_Update()
{
}

void CUIInventory::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(100),				// 2,3 ���� :  ������� ��ġ X, Y
		int(0),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_iChoose * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_iDepth * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CUIInventory::Release()
{
}

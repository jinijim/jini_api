#include "stdafx.h"
#include "UI_Jump.h"

#include "BmpMgr.h"

CUI_Jump::CUI_Jump()
{
}


CUI_Jump::~CUI_Jump()
{
	Release();
}

void CUI_Jump::Initialize()
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	m_pFrameKey = L"UI_Weapon";
	m_tFrame.iFrameStart = 2;
	m_tFrame.iMotion = 0;

	m_dwMoveTime = long(0);
	m_bMove = true;
}

int CUI_Jump::Update()
{
	if (m_bMove)
	{
		if (m_tInfo.fY > 440)
			m_tInfo.fY -= 8.f;
		else
			m_bMove = false;
	}

	return OBJ_NOEVENT;
}

void CUI_Jump::Late_Update()
{
}

void CUI_Jump::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tInfo.fX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tInfo.fY),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

void CUI_Jump::Release()
{
}

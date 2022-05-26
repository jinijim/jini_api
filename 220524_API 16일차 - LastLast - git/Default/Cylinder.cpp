#include "stdafx.h"
#include "Cylinder.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CCylinder::CCylinder()
{
}

CCylinder::~CCylinder()
{
	Release();
}

void CCylinder::Initialize()
{
	m_tInfo.fCX = 224.f;
	m_tInfo.fCY = 393.f;

	m_pFrameKey = L"Cylinder1";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CCylinder::Update()
{
	Update_Rect();
	Update_InfoCollision();

	return OBJ_NOEVENT;
}

void CCylinder::Late_Update()
{
}

void CCylinder::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
	//	int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
	//	int(m_tRect.top + iScrollY),
	//	int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
	//	int(m_tInfo.fCY),
	//	hMemDC,							// ��Ʈ���� ������ �ִ� DC
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
	//	m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
	//	(int)m_tInfo.fCY,
	//	RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
	//
		//Rectangle(hDC, (int)m_tInfoCollision.fX - m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY - m_tInfoCollision.fCY * 0.5 + iScrollY, (int)m_tInfoCollision.fX + m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY + m_tInfoCollision.fCY * 0.5 + iScrollY);
		//Rectangle(hDC, (int)m_tInfo.fX - m_tInfo.fCX * 0.5 + iScrollX, (int)m_tInfo.fY - m_tInfo.fCY * 0.5 + iScrollY, (int)m_tInfo.fX + m_tInfo.fCX * 0.5 + iScrollX, (int)m_tInfo.fY + m_tInfo.fCY * 0.5 + iScrollY);

}

void CCylinder::Release()
{
}

void CCylinder::Motion_Change()
{
}

void CCylinder::Update_InfoCollision()
{
	m_tInfoCollision.fX = m_tInfo.fX;
	m_tInfoCollision.fY = m_tInfo.fY;
	m_tInfoCollision.fCX = m_tInfo.fCX * 0.7f;
	m_tInfoCollision.fCY = m_tInfo.fCY;
}


#include "stdafx.h"
#include "ObjRun_Alphabet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CObjRun_Alphabet::CObjRun_Alphabet()
{
}

CObjRun_Alphabet::~CObjRun_Alphabet()
{
	Release();
}

void CObjRun_Alphabet::Initialize()
{
	m_bCollision = false;
	m_pFrameKey = L"Ground_Run_Alphabet";
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 308.f;
	m_fSpeed = 2.f;

	m_tFrame.iMotion = 0;
	m_tFrame.iFrameStart = m_iOption - 1;
}

int CObjRun_Alphabet::Update()
{
	m_tInfo.fY += m_fSpeed;

	if (m_tInfo.fY < -400.f || m_tInfo.fY > 0.f)
		m_fSpeed *= -1;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CObjRun_Alphabet::Late_Update()
{
}

void CObjRun_Alphabet::Render(HDC hDC)
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

void CObjRun_Alphabet::Release()
{
}

void CObjRun_Alphabet::Motion_Change()
{
	// None
}

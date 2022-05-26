#include "stdafx.h"
#include "ClearCuphead.h"
#include "BmpMgr.h"


CClearCuphead::CClearCuphead()
{
}


CClearCuphead::~CClearCuphead()
{
	Release();
}

void CClearCuphead::Initialize()
{
	m_tInfo.fCX = 240.f;
	m_tInfo.fCY = 343.f;
	m_pFrameKey = L"Clear_Cuphead";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 80;
	m_tFrame.dwTime = GetTickCount();
}

int CClearCuphead::Update()
{
	if(m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CClearCuphead::Late_Update()
{
	Move_Frame();
}

void CClearCuphead::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
}

void CClearCuphead::Release()
{
}

void CClearCuphead::Motion_Change()
{
}

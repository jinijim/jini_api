#include "stdafx.h"
#include "CoinBig.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CCoinBig::CCoinBig(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}


CCoinBig::~CCoinBig()
{
	Release();
}

void CCoinBig::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 204.f;

	m_pFrameKey = L"Coin_Big";
	m_eCurState = IDLE;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 12;
	m_tFrame.dwSpeed = 50.f;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();

	m_dwRenderTime = GetTickCount();
	
	g_iCoin += 3;
	CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_coin_pickup_03.wav", SOUND_EFFECT, g_fSound_EFFECT);
}

void CCoinBig::Update()
{
	Update_Rect();
}

void CCoinBig::Late_Update()
{
	Move_Frame();
}

void CCoinBig::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (GetTickCount() - m_dwRenderTime < 3000)
	{
		HDC		hMemDC_BG = CBmpMgr::Get_Instance()->Find_Image(L"Npc_Coin_Get");
		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(0),					// 2,3 ���� :  ������� ��ġ X, Y
			int(0),
			int(800),					// 4,5 ���� : ������� ����, ���� ����
			int(600),
			hMemDC_BG,								// ��Ʈ���� ������ �ִ� DC
			0,						// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)800,					// ������ ��Ʈ���� ����, ���� ����
			(int)600,
			RGB(255, 255, 255));				// �����ϰ��� �ϴ� ����


		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),					// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),					// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,								// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,						// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,					// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));				// �����ϰ��� �ϴ� ����

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + 150),					// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),					// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,								// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,						// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,					// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left + 300),					// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),					// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,								// ��Ʈ���� ������ �ִ� DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,						// ��Ʈ�� ��� ���� ��ǥ, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,					// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
}

void CCoinBig::Release()
{
}

void CCoinBig::Motion_Change()
{
}

#include "stdafx.h"
#include "Loading.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CLoading::CLoading()
{
}

CLoading::~CLoading()
{
	Release();
}

void CLoading::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Loading_MUS_Intro_DontDealWithDevil_Vocal.wav", g_fSound_BG);
	m_dwExitTime = GetTickCount();

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 36;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = GetTickCount();
}

void CLoading::Update()
{
	if(GetTickCount() - m_dwExitTime > 10000)
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);

	if(GetAsyncKeyState(VK_RETURN))
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);
}

void CLoading::Late_Update()
{
	Move_Frame_MultiLine(3, 8);
}

void CLoading::Render(HDC hDC)
{
	// ���
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Loading_BG");
	BitBlt(hDC, 0, 0, 800, 600, hGroundMemDC, 0, 0, SRCCOPY);

	// �����
	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Loading_Cuphead");
	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(0),						// 2,3 ���� :  ������� ��ġ X, Y
		int(153),
		int(800),							// 4,5 ���� : ������� ����, ���� ����
		int(449),
		hGroundMemDC,						// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * 800,									// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * 449,
		800,								// ������ ��Ʈ���� ����, ���� ����
		449,
		RGB(255, 255, 255));				// �����ϰ��� �ϴ� ����
}

void CLoading::Release()
{
	CSoundMgr::Get_Instance()->StopAll();
}

void CLoading::Move_Frame_MultiLine(int _iX, int _iY)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > _iX)
		{
			++m_tFrame.iMotion;
			m_tFrame.iFrameStart = 0;
		}

		if (m_tFrame.iMotion > _iY)
			m_tFrame.iMotion = 0;
	}
}
#include "stdafx.h"
#include "ScoreBoard.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ClearCuphead.h"


CScoreBoard::CScoreBoard()
{
}

CScoreBoard::~CScoreBoard()
{
	Release();
}

void CScoreBoard::Initialize()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 90;
	m_tFrame.dwTime = GetTickCount();
	m_dwExitTime = GetTickCount();
	
	CSoundMgr::Get_Instance()->PlayBGM(L"MUS_VictoryScreen.wav", g_fSound_BG);

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CClearCuphead>::Create(210, 350));
}

void CScoreBoard::Update()
{
	if (GetTickCount() - m_dwExitTime > 5000)
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);

	CObjMgr::Get_Instance()->Update();
}

void CScoreBoard::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	Move_Frame_MultiLine(2, 2);
}

void CScoreBoard::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Clear_BG");
	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(0),				// 2,3 ���� :  ������� ��ġ X, Y
		int(0),
		int(800),				// 4,5 ���� : ������� ����, ���� ����
		int(600),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * 800,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * 600,
		(int)800,				// ������ ��Ʈ���� ����, ���� ����
		(int)600,
		RGB(255, 255, 255));


	HDC hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Clear_Stage");
	
	if(g_iClearIndex == 2)
		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"Clear_Run");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(0),				// 2,3 ���� :  ������� ��ġ X, Y
		int(0),
		int(800),				// 4,5 ���� : ������� ����, ���� ����
		int(600),
		hMemDC2,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		(int)800,				// ������ ��Ʈ���� ����, ���� ����
		(int)600,
		RGB(255, 255, 255));

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScoreBoard::Release()
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopAll();
}

void CScoreBoard::Move_Frame_MultiLine(int _iX, int _iY)
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

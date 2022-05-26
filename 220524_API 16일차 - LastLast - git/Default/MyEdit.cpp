#include "stdafx.h"
#include "MyEdit.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"


CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/BackGround/BackGround_World.bmp", L"Ground");
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile();
	m_fSpeed = 10.f;
	m_Tag = TILE_END;
}

void CMyEdit::Update()
{
	CTileMgr::Get_Instance()->Update();
	Key_Input();
}

void CMyEdit::Late_Update()
{
	CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
	BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundMemDC, 0, 0, SRCCOPY);

	CTileMgr::Get_Instance()->Render(hDC);
	
	// 안내문 출력
	static TCHAR	m_szIndex[128];
	swprintf_s(m_szIndex, L" 1.Stage 2.Tutorial 3.Shop 4.Run 5.End 6.Npc / 현재 선택됨 : %d", m_Tag + 1);
	TextOut(hDC, 10, 10, m_szIndex, lstrlen(m_szIndex));
}

void CMyEdit::Release()
{
	CTileMgr::Get_Instance()->Destroy_Instance();
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		
		CTileMgr::Get_Instance()->Picking_Tile(1, pt, 0, 0, m_Tag); // mode 1 : Tag 변경
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		POINT		pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(0, pt, 0, 0, TILE_END); // mode 0 : 충돌전환
	}

	// World 돌아가기
	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		CTileMgr::Get_Instance()->Save_Tile();

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
		CTileMgr::Get_Instance()->Load_Tile();

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
		m_Tag = TILE_STAGE;

	if (CKeyMgr::Get_Instance()->Key_Down('2'))
		m_Tag = TILE_TUTORIAL;

	if (CKeyMgr::Get_Instance()->Key_Down('3'))
		m_Tag = TILE_SHOP;

	if (CKeyMgr::Get_Instance()->Key_Down('4'))
		m_Tag = TILE_RUN;

	if (CKeyMgr::Get_Instance()->Key_Down('5'))
		m_Tag = TILE_END;

	if (CKeyMgr::Get_Instance()->Key_Down('6'))
		m_Tag = TILE_NPC;
}

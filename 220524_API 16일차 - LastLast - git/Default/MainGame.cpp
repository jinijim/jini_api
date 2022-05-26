#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "MonsterPotato.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ScoreBoard.h"

float	g_fSound_BG = 1.0f;
float	g_fSound_PLAYER = 1.0f;
float	g_fSound_EFFECT = 1.0f;
float	g_fSound_MONSTER = 1.0f;

int		g_iClearIndex = 0;
bool	g_iItemSale1 = false;
bool	g_iItemSale2 = false;
bool	g_iItemSale3 = false;

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()) /*m_dwStartTime(long(0)), m_bGameStart(false)*/
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	//Insert_Bmp 모아놓기
	BmpSetting();
		
	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOADING);


//#ifdef _DEBUG
//
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//
//#endif // _DEBUG
}

void CMainGame::Update()
{
	//if (!m_bGameStart)
	//{
	//	if (!m_dwStartTime)
	//		m_dwStartTime = GetTickCount();

	//	if (GetTickCount() - m_dwStartTime > 1000)
	//	{
	//		CSceneMgr::Get_Instance()->Scene_Change(SC_LOADING);
	//		m_dwStartTime = GetTickCount();
	//		m_bGameStart = true;
	//	}

	//}


	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hMemDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"CupHead");
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::BmpSetting()
{
	// MainGame
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/BackGround/BackGround_1.bmp", L"Back");

	// Player
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Player/Player_LEFT(Shadow).bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Player/Player_RIGHT(Shadow).bmp", L"Player_RIGHT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Player/Player_Dash_Left.bmp", L"Player_DASH_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Player/Player_Dash_Right.bmp", L"Player_DASH_RIGHT");

	// Player_Bullet
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Bullet/Gun_Spawn.bmp", L"Gun_Spawn");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Bullet/Gun_loop2.bmp", L"Gun_loop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Bullet/Gun_loop_Up.bmp", L"Gun_loop_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Bullet/Gun_Death2.bmp", L"Gun_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Bullet/Star_loop.bmp", L"Star_loop");

	// World
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/BackGround/BackGround_World.bmp", L"WorldMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/Flag/Flag_Big.bmp", L"Flag");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/Npc/NPC.bmp", L"Npc_Mac");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/Npc/NPC_Talk.bmp", L"Npc_Mac_Talk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/Npc/Coin_Get.bmp", L"Npc_Coin_Get");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/BackGround/Tree2.bmp", L"World_Tree1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/BackGround/Tree3.bmp", L"World_Tree3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/BackGround/Tree4.bmp", L"World_Tree4");

	// World_Player
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/Player/Player_.bmp", L"Player");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/World/Player/Stretch.bmp", L"Stretch");

	// Edit
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile/Tile_Collision32.bmp", L"Tile_Collision");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile/Tile_Collision32-Stage.bmp", L"Tile_Stage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile/Tile_Collision32-Tutorial.bmp", L"Tile_Tutorial");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile/Tile_Collision32-Shop.bmp", L"Tile_Shop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile/Tile_Collision32-Run.bmp", L"Tile_Run");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile/Tile_Collision32-NPC.bmp", L"Tile_NPC");

	// Stage
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/BackGround/BackGround_1.bmp", L"Ground_Stage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/BackGround/BackGround_2.bmp", L"Ground_Stage2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Boss_Potato.bmp", L"Boss_Potato");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Boss_Potato_Bullet.bmp", L"Boss_Potato_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Boss_Potato_Parry.bmp", L"Boss_Potato_Parry");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Boss_Onion.bmp", L"Boss_Onion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Boss_Onion_Tears.bmp", L"Boss_Onion_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Monster/Boss_Onion_Parry.bmp", L"Boss_Onion_Parry");

	// Tutorial
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/BackGround/BackGround_0.bmp", L"Ground_Tutorial");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/BackGround/BackGround_Tu.bmp", L"Ground_Tutorial_");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/BackGround/BackGround_2.bmp", L"Ground_Tutorial2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Block/tutorial_cube.bmp", L"Block1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Block/tutorial_cylinder_1.bmp", L"Cylinder1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Arrows/tutorial_arrow_parry_bounce.bmp", L"Arrow1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Parry/tutorial_pink_sphere_1.bmp", L"Tutorial_Parry");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Parry/tutorial_target_0003.bmp", L"Tutorial_Bell");

	//Run
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/BackGround/BackGround.bmp", L"Ground_Run");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/BackGround/BackGround2_ObjectOn.bmp", L"Ground_Run2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/BackGround/BackGround3.bmp", L"Ground_Run3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/BackGround/BackGround3_Front.bmp", L"Ground_Run3_front");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/BackGround/BackGround_Final.bmp", L"Ground_Run4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/BackGround/BackGround_Final_front.bmp", L"Ground_Run4_front");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/BackGround/BackGround_Final_back.bmp", L"Ground_Run4_back");

	//Run_Collision
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjCollision/Phase1.bmp", L"Phase1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjCollision/Box.bmp", L"Box");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjCollision/Box2.bmp", L"Box2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjCollision/Box3.bmp", L"Box3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjCollision/PinkBell.bmp", L"PinkBell");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjCollision/PinkBellBox.bmp", L"PinkBellBox"); 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjCollision/Tamberine.bmp", L"Tamberine"); 

	//Run_NonCollision
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/Alphabet.bmp", L"Ground_Run_Alphabet");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/1.bmp", L"RunNonCol_1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/2.bmp", L"RunNonCol_2_Ticket");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/3_balloon.bmp", L"RunNonCol_3_balloon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/4_Booth.bmp", L"RunNonCol_4_Booth");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/5_Booth2.bmp", L"RunNonCol_5_Booth2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/6_cm1.bmp", L"RunNonCol_6_cm1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/7_cm2.bmp", L"RunNonCol_7_cm2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/8_Opening.bmp", L"RunNonCol_8_Opening");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/9_Opening2.bmp", L"RunNonCol_9_Opening2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/10_Pannel.bmp", L"RunNonCol_10_Pannel");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/11_Shop.bmp", L"RunNonCol_11_Shop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/12_Shop2.bmp", L"RunNonCol_12_Shop2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/13_Shop3.bmp", L"RunNonCol_13_Shop3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/14_Shop4.bmp", L"RunNonCol_14_Shop4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/15_Shop5.bmp", L"RunNonCol_15_Shop5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/16_Shop6.bmp", L"RunNonCol_16_Shop6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/17_Shop7.bmp", L"RunNonCol_17_Shop7");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/18_Shop8.bmp", L"RunNonCol_18_Shop8");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/ObjNonCollision/19_Shop9.bmp", L"RunNonCol_19_Shop9");

	//Run_Monster
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Boss/Boss.bmp", L"Run_Boss");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Boss/Boss_Death.bmp", L"Run_Boss_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Boss/Boss_Bullet.bmp", L"Run_Boss_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Boss/Boss_Bullet2.bmp", L"Run_Boss_Bullet2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Boss/Boss_Bullet3.bmp", L"Run_Boss_Bullet3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Trampoline.bmp", L"Run_Trampoline");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Crown_blue.bmp", L"Run_Crown_Blue");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Crown_Red.bmp", L"Run_Crown_Red");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Cannon_Bar.bmp", L"Run_Cannon_Bar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Cannon_Head2.bmp", L"Run_Cannon_Head");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Cannon_Ball.bmp", L"Run_Cannon_Ball");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Balloon.bmp", L"Run_Balloon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Balloon_Bullet.bmp", L"Run_Balloon_Bullet");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Machine.bmp", L"Run_Machine");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Run/Monster/Machine_Bullet.bmp", L"Run_Machine_Bullet");

	//UI
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Bravo.bmp", L"UI_Bravo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Run.bmp", L"UI_Run");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Hp.bmp", L"UI_Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Weapon.bmp", L"UI_Weapon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inventory.bmp", L"UI_Inventory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/YOUDIED.bmp", L"UI_YouDied");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Clear/BG2.bmp", L"Clear_BG");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Clear/Clear_Stage_Contents.bmp", L"Clear_Stage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Clear/Clear_Run_Contents.bmp", L"Clear_Run");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Clear/Clear_Cuphead.bmp", L"Clear_Cuphead");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Clear/Start_Shop.bmp", L"Start_Shop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Clear/Start_Run.bmp", L"Start_Run");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Merge.bmp", L"UI_Ready");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/DJ800_Merge3.bmp", L"UI_DoubleJump");


	//Coin
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/Run_Coin.bmp", L"Coin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/Run_Coin_Death.bmp", L"Coin_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/Coin_Get.bmp", L"Coin_Get");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/World_Coin_Big.bmp", L"Coin_Big");

	//Effect
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Bang.bmp", L"Effect_Bang");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Dust.bmp", L"Effect_Dust");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Dust_Small.bmp", L"Effect_Dust_Small");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/SceneChange.bmp", L"Effect_SceneChange");

	//Shop
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/BG_Full.bmp", L"Shop_BG_Full");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/BG_Front.bmp", L"Shop_BG_Front");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/Item.bmp", L"Shop_Item");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/Item_Info.bmp", L"Shop_Item_Info");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/Piggy_IDLE.bmp", L"Shop_Piggy_IDLE");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Shop/Piggy_GOODBYE.bmp", L"Shop_Piggy_GOODBYE");

	//Load 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Loading/title_screen_background.bmp", L"Loading_BG");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Loading/cuphead_title_screen.bmp", L"Loading_Cuphead");


}
//
////랜덤 처리
//random_device random; // 변수명 각각 다르게 써야함
//mt19937 rd(random());// 변수명 각각 다르게 써야함
//uniform_int_distribution<int> range(1, 4)// 범위 // 변수명 각각 다르게 써야함
////변수명 = (형변환)range(rd);
//

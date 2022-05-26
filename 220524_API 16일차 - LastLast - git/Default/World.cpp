#include "stdafx.h"
#include "World.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "PlayerWorld.h"
#include "TileMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Flag.h"
#include "WorldObj.h"
#include "SoundMgr.h"
#include "UIMgr.h"
#include "AbstractFactoryUI.h"
#include "UI_Coin.h"
#include "UIInventory.h"
#include "NpcMac.h"
#include "ObjMgr.h"
#include "UIInventory.h"
#include "EffectScene.h"

float g_fWorldPlayerX;
float g_fWorldPlayerY;
int	  g_iCoin = 4;
bool  g_bNpcCoinGet;
int	  g_iHp = 5;
//bool  g_bGunGet = false;
//bool  g_bGuideGunGet = false;

CWorld::CWorld()
{
	m_pPlayerWorld = nullptr;
	m_pPlayerTile = nullptr;
	m_pFlag = nullptr;
}

CWorld::~CWorld()
{
	Release();
}

void CWorld::Initialize()
{
	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Tile();
	CSoundMgr::Get_Instance()->PlayBGM(L"World_MUS_InkwellIsleOne.wav", g_fSound_BG);
	//CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_BGM, 0.3f);
	//CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_PLAYER, 1.0f);

	if (0 == g_fWorldPlayerX)
	{
		m_pPlayerWorld = CAbstractFactory<CPlayerWorld>::Create(402.f, 414.f);
	}
	else
		m_pPlayerWorld = CAbstractFactory<CPlayerWorld>::Create(g_fWorldPlayerX, g_fWorldPlayerY);
	m_vecTile = CTileMgr::Get_Instance()->Get_vecTile();
	
	m_pInventory = nullptr;

	m_pFlag = new CFlag;
	m_pFlag->Initialize();

	m_pNpcMac = new CNpcMac;
	m_pNpcMac->Initialize();

	m_bNpcOrPlayer = false;
	m_dwNpcOrPlayerRender = long(0);

	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Coin>::Create(10, 10));

	//CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectScene>::Create(400,300));

}

void CWorld::Update()
{
	m_pPlayerWorld->Update();
	m_pFlag->Update();
	m_pNpcMac->Update();

	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	if(m_pInventory)
		m_pInventory->Update();

	float _fX = dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Get_InfoCollision().fX;
	float _fY = dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Get_InfoCollision().fY;

	// 플레이어가 서있는 타일 위치를 받아옴 - 상호작용 용도
	m_pPlayerTile = CTileMgr::Get_Instance()->Check_Tile(_fX, _fY);
	
	Interactive_Object();
	Key_Input();
}

void CWorld::Late_Update()
{
	m_pPlayerWorld->Late_Update();
	m_pFlag->Late_Update();
	m_pNpcMac->Late_Update();
	
	if(m_pInventory)
		m_pInventory->Late_Update();

	CObjMgr::Get_Instance()->Late_Update();
	CTileMgr::Get_Instance()->Late_Update();
	CCollisionMgr::Collision_RectExVec(m_vecTile, m_pPlayerWorld);
	CUIMgr::Get_Instance()->Late_Update();


	//_DEBUG //이코드 실행 시, Stage에서 World 돌아오는게 안됨.
	//cout << "플레이어 타일 : " << dynamic_cast<CTile*>(m_pPlayerTile)->Get_Index() << "\t 태그 : "<< (int)dynamic_cast<CTile*>(m_pPlayerTile)->Get_TileTag() << endl;
	//cout << dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Get_Info().fX << "\t" << dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Get_Info().fY << endl;
}

void CWorld::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"WorldMap");
	BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	m_pFlag->Render(hDC);
	

	if (!g_bNpcCoinGet)
	{
		m_pNpcMac->Render(hDC);
		m_pPlayerWorld->Render(hDC);

		HDC		hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree1");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(145 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
			int(315 + iScrollY),
			int(318),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(330),
			hGroundMemDC2,						// 비트맵을 가지고 있는 DC
			0,									// 비트맵 출력 시작 좌표, X,Y
			0,
			318,								// 복사할 비트맵의 가로, 세로 길이
			330,
			RGB(255, 255, 255));

		//hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree3");
		//GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		//	int(795 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
		//	int(350 + iScrollY),
		//	int(162),							// 4,5 인자 : 복사받을 가로, 세로 길이
		//	int(176),
		//	hGroundMemDC2,						// 비트맵을 가지고 있는 DC
		//	0,									// 비트맵 출력 시작 좌표, X,Y
		//	0,
		//	162,								// 복사할 비트맵의 가로, 세로 길이
		//	176,
		//	RGB(255, 255, 255));

		hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree4");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(421 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
			int(412 + iScrollY),
			int(157),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(103),
			hGroundMemDC2,						// 비트맵을 가지고 있는 DC
			0,									// 비트맵 출력 시작 좌표, X,Y
			0,
			157,								// 복사할 비트맵의 가로, 세로 길이
			103,
			RGB(255, 255, 255));

	}
	else if (m_dwNpcOrPlayerRender && GetTickCount() - m_dwNpcOrPlayerRender > 3000)
	{
		m_pNpcMac->Render(hDC);
		m_pPlayerWorld->Render(hDC);
		HDC		hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree1");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(145 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
			int(315 + iScrollY),
			int(318),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(330),
			hGroundMemDC2,						// 비트맵을 가지고 있는 DC
			0,									// 비트맵 출력 시작 좌표, X,Y
			0,
			318,								// 복사할 비트맵의 가로, 세로 길이
			330,
			RGB(255, 255, 255));

		//hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree3");
		//GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		//	int(795 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
		//	int(350 + iScrollY),
		//	int(162),							// 4,5 인자 : 복사받을 가로, 세로 길이
		//	int(176),
		//	hGroundMemDC2,						// 비트맵을 가지고 있는 DC
		//	0,									// 비트맵 출력 시작 좌표, X,Y
		//	0,
		//	162,								// 복사할 비트맵의 가로, 세로 길이
		//	176,
		//	RGB(255, 255, 255));

		hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree4");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(421 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
			int(412 + iScrollY),
			int(157),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(103),
			hGroundMemDC2,						// 비트맵을 가지고 있는 DC
			0,									// 비트맵 출력 시작 좌표, X,Y
			0,
			157,								// 복사할 비트맵의 가로, 세로 길이
			103,
			RGB(255, 255, 255));
	}
	else if (g_bNpcCoinGet)
	{

		HDC		hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree1");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(145 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
			int(315 + iScrollY),
			int(318),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(330),
			hGroundMemDC2,						// 비트맵을 가지고 있는 DC
			0,									// 비트맵 출력 시작 좌표, X,Y
			0,
			318,								// 복사할 비트맵의 가로, 세로 길이
			330,
			RGB(255, 255, 255));

		//hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree3");
		//GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		//	int(795 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
		//	int(350 + iScrollY),
		//	int(162),							// 4,5 인자 : 복사받을 가로, 세로 길이
		//	int(176),
		//	hGroundMemDC2,						// 비트맵을 가지고 있는 DC
		//	0,									// 비트맵 출력 시작 좌표, X,Y
		//	0,
		//	162,								// 복사할 비트맵의 가로, 세로 길이
		//	176,
		//	RGB(255, 255, 255));

		hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree4");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(421 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
			int(412 + iScrollY),
			int(157),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(103),
			hGroundMemDC2,						// 비트맵을 가지고 있는 DC
			0,									// 비트맵 출력 시작 좌표, X,Y
			0,
			157,								// 복사할 비트맵의 가로, 세로 길이
			103,
			RGB(255, 255, 255));

		m_pPlayerWorld->Render(hDC);
		m_pNpcMac->Render(hDC);
		if (!m_dwNpcOrPlayerRender)
			m_dwNpcOrPlayerRender = GetTickCount();
		//m_bNpcOrPlayer = true;


	}

	//HDC		hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree1");
	//GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
	//	int(145 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
	//	int(315 + iScrollY),
	//	int(318),							// 4,5 인자 : 복사받을 가로, 세로 길이
	//	int(330),
	//	hGroundMemDC2,						// 비트맵을 가지고 있는 DC
	//	0,									// 비트맵 출력 시작 좌표, X,Y
	//	0,
	//	318,								// 복사할 비트맵의 가로, 세로 길이
	//	330,
	//	RGB(255, 255, 255));

	//hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree3");
	//GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
	//	int(795 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
	//	int(350 + iScrollY),
	//	int(162),							// 4,5 인자 : 복사받을 가로, 세로 길이
	//	int(176),
	//	hGroundMemDC2,						// 비트맵을 가지고 있는 DC
	//	0,									// 비트맵 출력 시작 좌표, X,Y
	//	0,
	//	162,								// 복사할 비트맵의 가로, 세로 길이
	//	176,
	//	RGB(255, 255, 255));

	//hGroundMemDC2 = CBmpMgr::Get_Instance()->Find_Image(L"World_Tree4");
	//GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
	//	int(421 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
	//	int(412 + iScrollY),
	//	int(157),							// 4,5 인자 : 복사받을 가로, 세로 길이
	//	int(103),
	//	hGroundMemDC2,						// 비트맵을 가지고 있는 DC
	//	0,									// 비트맵 출력 시작 좌표, X,Y
	//	0,
	//	157,								// 복사할 비트맵의 가로, 세로 길이
	//	103,
	//	RGB(255, 255, 255));

	//CTileMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
	



	if(m_pInventory)
		m_pInventory->Render(hDC);
}
	

void CWorld::Release()
{
	g_fWorldPlayerX = dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Get_Info().fX;
	g_fWorldPlayerY = dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Get_Info().fY;

	Safe_Delete<CObj*>(m_pPlayerWorld);
	Safe_Delete<CWorldObj*>(m_pNpcMac);
	Safe_Delete<CUI*>(m_pInventory);
	//Safe_Delete<CObj*>(m_pPlayerTile);
	Safe_Delete<CWorldObj*>(m_pFlag); // 이것때문에 RUN에서 WORLD 돌아올때 오류남	

	CObjMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopAll();
}

void CWorld::Key_Input()
{
	// 맵에서 다른 씬으로 입장
	// 테스트용 코드
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
	//}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		switch (dynamic_cast<CTile*>(m_pPlayerTile)->Get_TileTag())
		{
		case TILE_STAGE:
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
			break;
		case TILE_TUTORIAL:
			CSceneMgr::Get_Instance()->Scene_Change(SC_TUTORIAL);
			break;
		case TILE_SHOP:
			CSceneMgr::Get_Instance()->Scene_Change(SC_SHOP);
			break;
		case TILE_RUN:
			CSceneMgr::Get_Instance()->Scene_Change(SC_RUN);
			break;
		case TILE_NPC:
			if (!g_bNpcCoinGet)
			{
				dynamic_cast<CNpcMac*>(m_pNpcMac)->Set_TalkNo_Plus();
				if (dynamic_cast<CNpcMac*>(m_pNpcMac)->Get_TalkNo() >= 3)
					g_bNpcCoinGet = true;
			}
			break;
		case TILE_END:
		default:
			break;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SHIFT))
	{
		dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Set_Speed(9.f);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		if(m_pInventory)
			Safe_Delete<CUI*>(m_pInventory);
		else
			PostQuitMessage(0);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_TAB))
	{
		m_pInventory = new CUIInventory;
		m_pInventory->Initialize();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_TUTORIAL);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_RUN);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_SHOP);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);
	}
	else
		dynamic_cast<CPlayerWorld*>(m_pPlayerWorld)->Set_Speed(3.f);
}

void CWorld::Interactive_Object()
{
	TILETAG tagtemp = dynamic_cast<CTile*>(m_pPlayerTile)->Get_TileTag();

	if (TILE_STAGE == tagtemp)
	{
		m_pFlag->Set_Pos(850.f, 650.f);
		m_pFlag->Set_StateStartFrame(1);
		dynamic_cast<CFlag*>(m_pFlag)->Set_reStart(false);
	}
	else if (TILE_TUTORIAL == tagtemp)
	{
		m_pFlag->Set_Pos(200.f, 310.f);
		m_pFlag->Set_StateStartFrame(1);
		dynamic_cast<CFlag*>(m_pFlag)->Set_reStart(false);
	}
	else if (TILE_SHOP == tagtemp)
	{
		m_pFlag->Set_Pos(1110.f, 565.f);
		m_pFlag->Set_StateStartFrame(1);
		dynamic_cast<CFlag*>(m_pFlag)->Set_reStart(false);

	}
	else if (TILE_RUN == tagtemp)
	{
		m_pFlag->Set_Pos(1360.f, 330.f);
		m_pFlag->Set_StateStartFrame(1);
		dynamic_cast<CFlag*>(m_pFlag)->Set_reStart(false);

	}
	else if (TILE_NPC == tagtemp)
	{
		if (!g_bNpcCoinGet)
			dynamic_cast<CNpcMac*>(m_pNpcMac)->Set_State(1);\
	}
	else
	{
		m_pFlag->Set_StateStartFrame(0);
		dynamic_cast<CNpcMac*>(m_pNpcMac)->Set_State(0);
		dynamic_cast<CNpcMac*>(m_pNpcMac)->Set_TalkNo_Init();
		dynamic_cast<CFlag*>(m_pFlag)->Set_reStart(true);
	}
}

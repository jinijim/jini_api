#include "stdafx.h"
#include "Stage.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"
#include "AbstractFactoryUI.h"

#include "Player.h"
#include "MonsterPotato.h"
#include "MonsterPotatoBullet.h"
#include "MonsterOnion.h"
#include "UI_Message.h"
#include "UI_HP.h"
#include "UI_Weapon.h"
#include "EffectPlayerDust.h"
#include "EffectScene.h"


CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	g_iClearIndex = 1;
	m_pPlayer = nullptr;
	m_pMonsterPotato = nullptr;
	m_pMonsterOnion = nullptr;

	m_bMonsterOnionSpawn = false;
	m_dwMonsterOnionSpawn = long(0);
	m_dwWIn = long(0);
	m_bFinish = false;

	CLineMgr::Get_Instance()->Initialize(LINE_STAGE);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200, 300));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Weapon>::Create(8, 500));
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Message>::Create(0, 0, 4));
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_HP>::Create(10, 565));

	// 사운드 관련
	m_dwAnnounce = GetTickCount();
	m_bAnnounce = false;
	CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_announcer_0001_b.wav", SOUND_EFFECT, g_fSound_EFFECT);
	CSoundMgr::Get_Instance()->PlayBGM(L"Stage_MUS_BotanicPanic.wav", g_fSound_BG);
	//CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_BGM, 0.3f);

	SpawnPotato();
}


void CStage::Update(void)
{
	// intro 사운드
	if (!m_bAnnounce && 2000 < GetTickCount() - m_dwAnnounce)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_announcer_0002_e.wav", SOUND_EFFECT, g_fSound_EFFECT);
		//CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_BGM, 0.6f);
		m_bAnnounce = true;
	}

	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	SpawnOnion();
	Win();
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);
	}
}

void CStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	 
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Stage");
	BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundMemDC, 80, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);

	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Stage2");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(iScrollX),						// 2,3 인자 :  복사받을 위치 X, Y
		int(iScrollY),
		int(800),							// 4,5 인자 : 복사받을 가로, 세로 길이
		int(600),
		hGroundMemDC,						// 비트맵을 가지고 있는 DC
		0,									// 비트맵 출력 시작 좌표, X,Y
		0,
		800,								// 복사할 비트맵의 가로, 세로 길이
		600,
		RGB(255, 255, 255));				// 제거하고자 하는 색상

	//cout << iScrollX << "\t" << iScrollY << "\t" << "\t" << "\t" << m_pPlayer->Get_Info().fX << "\t" << m_pPlayer->Get_Info().fY << "\t" << endl;

	CUIMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

	CLineMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	/*CUIMgr::Get_Instance()->Release();*/

	CSoundMgr::Get_Instance()->StopAll();
}

void CStage::SpawnPotato()
{
	CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Potato_RiseGround.wav", SOUND_MONSTER, g_fSound_MONSTER);
	m_pMonsterPotato = CAbstractFactory<CMonsterPotato>::Create(670, 320);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonsterPotato);
}

void CStage::SpawnOnion()
{
	// 감자가 죽으면, 양파 스폰 타이며 시작
	if (m_pMonsterPotato->Get_Dead() && m_dwMonsterOnionSpawn == 0)
	{
		m_dwMonsterOnionSpawn = GetTickCount();
	}

	// 감자가 죽고 2초 지나면 양파 스폰
	else if (m_dwMonsterOnionSpawn && GetTickCount() - m_dwMonsterOnionSpawn > 4000)
	{
		if (m_bMonsterOnionSpawn == false)
		{
			m_pMonsterOnion = CAbstractFactory<CMonsterOnion>::Create(370, 320);
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pMonsterOnion);
			CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Onion_Rise.wav", SOUND_MONSTER, g_fSound_MONSTER);
			m_bMonsterOnionSpawn = true;
		}
	}
}

void CStage::Win()
{
	if (m_bMonsterOnionSpawn && /*m_pMonsterPotato->Get_Dead() && */m_pMonsterOnion->Get_Dead())
	{
		if (m_dwWIn == 0)
			m_dwWIn = GetTickCount();

		if (!m_bFinish && GetTickCount() - m_dwWIn > 3000)
		{
			CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Message>::Create(0, 200, 1));
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_platforming_outro_bravo_c.wav", SOUND_EFFECT, g_fSound_EFFECT);
			m_bFinish = true;
		}

		// 3초 후 씬 전환
		if (GetTickCount() - m_dwWIn > 4500)
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_CLEAR);
		}
	}	

	//if (m_pPlayer != nullptr)
	//{
	//	if (m_pPlayer->Get_Dead() == true)
	//	{
	//		m_bFinish = true;

	//		if (m_dwWIn == 0)
	//			m_dwWIn = GetTickCount();

	//		// 3초 후 씬 전환
	//		if (m_bFinish && GetTickCount() - m_dwWIn > 2000)
	//		{
	//			CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Message>::Create(0, 200, 3));
	//		}

	//		if (GetTickCount() - m_dwWIn > 5000)
	//			CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);
	//	}
	//}
	
}

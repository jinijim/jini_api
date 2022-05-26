#include "stdafx.h"
#include "RunnGun.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "AbstractFactoryUI.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"

#include "Block.h"
#include "Cylinder.h"
#include "Arrow.h"
//#include "Mouse.h"
//#include "PlayerWorld.h"
#include "ObjRun_Collision.h"
#include "ObjRun_NonCollision.h"
#include "MonsterTrampoline.h"
#include "MonsterBalloon.h"
#include "MonsterCrown.h"
#include "MonsterCannon.h"
#include "MonsterCannonBar.h"
#include "MonsterMachine.h"
#include "ObjRun_Alphabet.h"
#include "MonsterHotDog.h"
#include "UI_Message.h"
#include "UI_HP.h"
#include "UI_Weapon.h"
#include "UI_Jump.h"
#include "UI_Coin.h"
#include "Coin.h"

CRunnGun::CRunnGun()
{
}

CRunnGun::~CRunnGun()
{
	Release();
}

void CRunnGun::Initialize()
{
	g_iClearIndex = 2;

	m_pPlayer = nullptr;
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200, 300));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	m_bCannonDead = false;
	m_dwWIn = long(0);
	m_bFinish = false;

	// 오브젝트 생성
	//코인
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(2242.f, 100.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(4131.f, 150.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(6520.f, -20.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(8475.f, 450.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(12500.f, -350.f, 1));

	// NonColl - 배경
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(400.f, 320.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(830.f, 320.f, 2));

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(3870.f, 250.f, 16));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(3617.f, 200.f, 4));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(4410.f, 200.f, 6));

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(4800.f, 280.f, 10));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(5250.f, 200.f, 19));


	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(8600.f, 200.f, 18));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(8100.f, 200.f, 7));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(8370.f, 360.f, 9));

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(9370.f, 100.f, 3));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(9450.f, 250.f, 13));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(9000.f, 280.f, 1));

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_NonCollision>::Create(10000.f, 230.f, 11));

	// - 공연장 1
	m_pTram = CAbstractFactory<CMonsterTrampoline>::Create(2000.f, 450.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pTram);

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(1600.f, 250.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(2020.f, 250.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(2430.f, 250.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(2840.f, 250.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterBalloon>::Create(1800.f, 100.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterBalloon>::Create(2200.f, 100.f, 2));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterBalloon>::Create(2600.f, 100.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterBalloon>::Create(3000.f, 100.f, 2));

	// - 공연장 1 끝나고
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(3800.f, 450.f, 2));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterCrown>::Create(4000.f, 420.f, 1));
	m_pCrown = CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(4400.f, 450.f, 4));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterCrown>::Create(4800.f, 420.f, 2));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(5000.f, 360.f, 6));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(4990.f, 360.f, 5));

	// - 공연장 2
	m_pCannonBar = CAbstractFactory<CMonsterCannonBar>::Create(7300.f, 200.f, 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pCannonBar);
	m_pCannon1 = CAbstractFactory<CMonsterCannon>::Create(7220.f, 120.f, 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pCannon1);
	m_pCannon2 = CAbstractFactory<CMonsterCannon>::Create(7220.f, 270.f, 2);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pCannon2);
	m_pCannon3 = CAbstractFactory<CMonsterCannon>::Create(7220.f, 420.f, 3);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pCannon3);

	// - 공연장 2 끝나고
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(8100.f, 450.f, 2));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterCrown>::Create(8300.f, 420.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(8700.f, 450.f, 4));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterCrown>::Create(9100.f, 420.f, 2));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(9300.f, 360.f, 6));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(9300.f, 360.f, 5));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Collision>::Create(10200.f, 510.f, 7));


	// 전광판 알파벳
	for (int i = 0; i < 13; ++i)
	{
		float fX = 10700.f + (300 * i);
		float fY = (rand() % 350 + 1) * -1;
		CLineMgr::Get_Instance()->Insert_AlphabetfYList(fY + 140.f);
		CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CObjRun_Alphabet>::Create(fX, fY, i + 1));
	}

	//보스 앞 몬스터	
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterMachine>::Create(10000.f, 350.f)); //X : 10300
	
	// 보스
	m_pBoss = CAbstractFactory<CMonsterHotDog>::Create(14650.f, -100.f, 1);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pBoss);

	//UI
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Weapon>::Create(8, 500));
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Message>::Create(0, 0, 2));
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_HP>::Create(10, 565));
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Coin>::Create(10, 10));

	CLineMgr::Get_Instance()->Initialize(LINE_RUN);
	CSoundMgr::Get_Instance()->PlayBGM(L"Run_MUS_FunfairFever.wav", /*SOUND_BG, */g_fSound_BG);
	CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_level_announcer_0002_a.wav", SOUND_EFFECT, g_fSound_EFFECT);
}

void CRunnGun::Update()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	//다시 살려
	if (m_pPlayer->Get_Info().fX < 10300.f )
		CScrollMgr::Get_Instance()->Scroll_LockY();

	if (m_pPlayer->Get_Info().fX > 14890.f)
	{
		CScrollMgr::Get_Instance()->Set_ScrollYLock(CScrollMgr::Get_Instance()->Get_ScrollY());
		CScrollMgr::Get_Instance()->Set_ScrollXLock(-14505);
	}

	if (m_pCrown != nullptr && m_pCrown->Get_Dead())
	{
		CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Jump>::Create(8, 500));
		CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Message>::Create(0, 0, 5));

		m_pCrown = nullptr;
	}

	// 대포 한마리라도 죽으면, 다죽여라
	if (!m_bCannonDead)
	{
		if (m_pCannon1->Get_Dead() || m_pCannon2->Get_Dead() || m_pCannon3->Get_Dead())
		{
			m_pCannonBar->Set_Dead();
			m_pCannon1->Set_Dead();
			m_pCannon2->Set_Dead();
			m_pCannon3->Set_Dead();
			m_bCannonDead = true;
			CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_level_platform_cannon_droop_01.wav", SOUND_MONSTER, g_fSound_MONSTER);
		}
	}

	// 스테이지 승리하면 실행
	Win();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);
}

void CRunnGun::Late_Update()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Update();

	//살려야돼
	CCollisionMgr::Collision_RectExInfoCollision(CObjMgr::Get_Instance()->Get_List(OBJ_OBJECT), CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER));
	//CCollisionMgr::Collision_RectExTram(m_pTram, m_pPlayer);

//	if(!(m_pPlayer->Get_Dead()))
//		cout << dynamic_cast<CPlayer*>(m_pPlayer)->Get_fYStd() << "\t" << iScrollX << "\t" << iScrollY << "\t" << "\t" << "\t" << m_pPlayer->Get_Info().fX << "\t" << m_pPlayer->Get_Info().fY << "\t" << endl;
}

void CRunnGun::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// =======================================
	// 맨 뒤에 그려질 것 (배경, 충돌X오브젝트 등)
	// 기본 배경 (산과 들)
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run");
	BitBlt(hDC, /*(m_iBGIndex) **/ 0/* + iScrollX*/ , -450 + iScrollY, 1600, 1100, hGroundMemDC, 0, 0, SRCCOPY);

	// 첫번째 천막
	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run3");
	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(900 + iScrollX),				// 2,3 인자 :  복사받을 위치 X, Y
		int(0 + iScrollY),
		int(2700),							// 4,5 인자 : 복사받을 가로, 세로 길이
		int(610),
		hGroundMemDC,						// 비트맵을 가지고 있는 DC
		0,									// 비트맵 출력 시작 좌표, X,Y
		0,
		2700,								// 복사할 비트맵의 가로, 세로 길이
		610,
		RGB(255, 255, 255));				// 제거하고자 하는 색상

	// 두번째 천막
	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run2");
	GdiTransparentBlt(hDC, 					
		int(5200 + iScrollX),						
		int(0 + iScrollY),
		int(2700),							
		int(610),
		hGroundMemDC,						
		0,									
		0,
		2700,								
		610,
		RGB(255, 255, 255));


	// 세번째 영역 전광판
	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run4_back");
	GdiTransparentBlt(hDC,
		int(10200 + iScrollX),
		int(-550 + iScrollY),
		int(5610),
		int(857),
		hGroundMemDC,
		0,
		0,
		5610,
		857,
		RGB(255, 255, 255));

	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run4");
	GdiTransparentBlt(hDC,
		int(10200 + iScrollX),
		int(-550 + iScrollY),
		int(5610),
		int(857),
		hGroundMemDC,
		0,
		0,
		5610,
		857,
		RGB(255, 255, 255));



	// =======================================
	// 중간에 그려질 것 (몬스터, 충돌 오브젝트 등)

	CObjMgr::Get_Instance()->Render(hDC);


	// =======================================
	// 맨 앞에 그려질 것
	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run3_front");
	GdiTransparentBlt(hDC,
		int(900 + iScrollX),
		int(0 + iScrollY),
		int(2700),
		int(610),
		hGroundMemDC,
		0,
		0,
		2700,
		610,
		RGB(255, 255, 255));

	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run3_front");
	GdiTransparentBlt(hDC,
		int(5200 + iScrollX),
		int(0 + iScrollY),
		int(2700),
		int(610),
		hGroundMemDC,
		0,
		0,
		2700,
		610,
		RGB(255, 255, 255));

	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Run4_front");
	GdiTransparentBlt(hDC,
		int(10000 + iScrollX),
		int(-690 + iScrollY),
		int(5610),
		int(857),
		hGroundMemDC,
		0,
		0,
		5610,
		857,
		RGB(255, 255, 255));

	// 테스트
	//CLineMgr::Get_Instance()->Render(hDC);

	// UI 등
	CUIMgr::Get_Instance()->Render(hDC);
}

void CRunnGun::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_OBJECT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CLineMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopAll();
}

void CRunnGun::Win()
{
	if (m_pBoss->Get_Dead())
	{
		if (!m_bFinish && m_pPlayer->Get_Info().fX > 14890.f)
		{
			CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Message>::Create(0, 0, 1));
			CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_platforming_outro_bravo_c.wav", SOUND_EFFECT, g_fSound_EFFECT);
			m_bFinish = true;
		}

		if (m_bFinish && m_dwWIn == 0)
		{
			m_dwWIn = GetTickCount();
		}
	
		// 3초 후 씬 전환
		if (m_bFinish && GetTickCount() - m_dwWIn > 3000)
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_CLEAR);
		}
	}

	//if (m_pPlayer->Get_Dead())
	//{
	//	m_bFinish = true;

	//	if (m_dwWIn == 0)
	//		m_dwWIn = GetTickCount();

	//	// 3초 후 씬 전환
	//	if (m_bFinish && GetTickCount() - m_dwWIn > 2000)
	//	{
	//		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);
	//	}
	//}
}

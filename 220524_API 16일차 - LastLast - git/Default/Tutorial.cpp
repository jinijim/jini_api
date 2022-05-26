#include "stdafx.h"
#include "Tutorial.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "AbstractFactoryUI.h"

#include "Player.h"
//#include "Block.h"
#include "Cylinder.h"
//#include "Arrow.h"
#include "Coin.h"
#include "TutorialParry.h"
#include "TutorialBell.h"
#include "UI_Message.h"


CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
	Release();
}

void CTutorial::Initialize()
{
	CLineMgr::Get_Instance()->Initialize(LINE_TUTORIAL);
	CSoundMgr::Get_Instance()->PlayBGM(L"Tutorial_MUS_Tutorial.wav", g_fSound_BG);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(430, 435));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	/*CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CArrow>::Create(160, 300));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CBlock>::Create(300, 400));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CCylinder>::Create(650, 400));*/

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CCylinder>::Create(1914, 400)); 
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CCylinder>::Create(2938, 400));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CCoin>::Create(3415.f, 280.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTutorialParry>::Create(2770.f, 280.f, 1));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CTutorialBell>::Create(2271.f, 133.f, 1));
}

void CTutorial::Update()
{
	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_LockY();

	// World 돌아가기
	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);

	// Exit 나가기
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN) && m_pPlayer->Get_Info().fX > 3773)
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);
}

void CTutorial::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CCollisionMgr::Collision_RectExInfoCollision(CObjMgr::Get_Instance()->Get_List(OBJ_OBJECT), CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER));
}

void CTutorial::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Tutorial_");
	BitBlt(hDC, iScrollX, iScrollY, 4200, 604, hGroundMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);


	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground_Tutorial2");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(0),						// 2,3 인자 :  복사받을 위치 X, Y
		int(0),
		int(800),							// 4,5 인자 : 복사받을 가로, 세로 길이
		int(600),
		hGroundMemDC,						// 비트맵을 가지고 있는 DC
		0,									// 비트맵 출력 시작 좌표, X,Y
		0,
		800,								// 복사할 비트맵의 가로, 세로 길이
		600,
		RGB(255, 255, 255));				// 제거하고자 하는 색상
	//cout << iScrollX << "\t" << iScrollY << "\t" << "\t" << "\t" << m_pPlayer->Get_Info().fX << "\t" << m_pPlayer->Get_Info().fY << "\t" << endl;
}

void CTutorial::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_OBJECT);
	CLineMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopAll();
}

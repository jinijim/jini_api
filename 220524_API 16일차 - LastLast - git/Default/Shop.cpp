#include "stdafx.h"
#include "Shop.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "AbstractFactoryUI.h"
#include "AbstractFactory.h"

#include "UI_Coin.h"
#include "Shop_Piggy.h"
#include "Item.h"

CShop::CShop()
{
}


CShop::~CShop()
{
	Release();
}

void CShop::Initialize()
{
	m_dwExit = long(0);
	m_iChoose = -1;
	CSoundMgr::Get_Instance()->PlayBGM(L"Shop_MUS_PorkrindsEmporium.wav", g_fSound_BG);
	//CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_BGM, 0.6f);

	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CShop_Piggy>::Create(430.f, 200.f));
	m_pPiggy = CObjMgr::Get_Instance()->Get_ListBack(OBJ_OBJECT);
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CItem>::Create(70.f, 300.f, 0));
	m_pItem1 = CObjMgr::Get_Instance()->Get_ListBack(OBJ_OBJECT);
	if(g_iItemSale1)
		dynamic_cast<CItem*>(m_pItem1)->Set_State(0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CItem>::Create(160.f, 300.f, 1));
	m_pItem2 = CObjMgr::Get_Instance()->Get_ListBack(OBJ_OBJECT);
	if (g_iItemSale2)
		dynamic_cast<CItem*>(m_pItem2)->Set_State(0);
	CObjMgr::Get_Instance()->Add_Object(OBJ_OBJECT, CAbstractFactory<CItem>::Create(250.f, 300.f, 2));
	m_pItem3 = CObjMgr::Get_Instance()->Get_ListBack(OBJ_OBJECT);
	if (g_iItemSale3)
		dynamic_cast<CItem*>(m_pItem3)->Set_State(0);

	CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_pig_welcome.wav", SOUND_MONSTER, g_fSound_MONSTER);
	CUIMgr::Get_Instance()->Add_Object(CAbstractFactoryUI<CUI_Coin>::Create(10, 10));
}

void CShop::Update()
{
	if (m_dwExit && GetTickCount() - m_dwExit > 2000)
		CSceneMgr::Get_Instance()->Scene_Change(SC_WORLD);
	
	KeyInput();

	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();

	switch (m_iChoose)
	{
	case 0:
		if (dynamic_cast<CItem*>(m_pItem1)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem1)->Set_State(2);
		if (dynamic_cast<CItem*>(m_pItem2)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem2)->Set_State(1);
		if (dynamic_cast<CItem*>(m_pItem3)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem3)->Set_State(1);
		break;
	case 1:
		if (dynamic_cast<CItem*>(m_pItem1)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem1)->Set_State(1);
		if (dynamic_cast<CItem*>(m_pItem2)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem2)->Set_State(2);
		if (dynamic_cast<CItem*>(m_pItem3)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem3)->Set_State(1);
		break;
	case 2:
		if (dynamic_cast<CItem*>(m_pItem1)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem1)->Set_State(1);
		if (dynamic_cast<CItem*>(m_pItem2)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem2)->Set_State(1);
		if (dynamic_cast<CItem*>(m_pItem3)->Get_State() != 0)
			dynamic_cast<CItem*>(m_pItem3)->Set_State(2);
		break;
	}

	IfSaleNext();
}

void CShop::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CUIMgr::Get_Instance()->Late_Update();
}

void CShop::Render(HDC hDC)
{
	// 배경
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shop_BG_Full");
	BitBlt(hDC, 0, 0, 800, 600, hGroundMemDC, 0, 0, SRCCOPY);

	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shop_BG_Front");
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

	//Item Info  
	if (m_iChoose != -1)
	{
		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shop_Item_Info");
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(0),						// 2,3 인자 :  복사받을 위치 X, Y
			int(325),
			int(400),							// 4,5 인자 : 복사받을 가로, 세로 길이
			int(300),
			hGroundMemDC,						// 비트맵을 가지고 있는 DC
			m_iChoose * 400,									// 비트맵 출력 시작 좌표, X,Y
			0,
			400,								// 복사할 비트맵의 가로, 세로 길이
			300,
			RGB(255, 255, 255));
	}


	hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BG_Front");
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

	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CShop::Release()
{
	CObjMgr::Get_Instance()->Destroy_Instance();
	CUIMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->StopAll();
}

void CShop::KeyInput()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		m_pPiggy->Set_eState(1);
		CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_pig_goodbye.wav", SOUND_MONSTER, g_fSound_MONSTER);
		if (!m_dwExit)
		{
			m_dwExit = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_navigate_item.wav", SOUND_EFFECT, g_fSound_EFFECT);

		++m_iChoose;

		if (m_iChoose > 2)
			m_iChoose = 0;
	}
	// 구매 부분
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		switch (m_iChoose)
		{
		case 0 :
			if (g_iCoin >= 2)
			{
				g_iCoin -= 2;
				g_iItemSale1 = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_purchase.wav", SOUND_EFFECT, g_fSound_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_piggy_purchase_grunt.wav", SOUND_MONSTER, g_fSound_MONSTER);
				dynamic_cast<CItem*>(m_pItem1)->Set_State(0);
			}
			else
			{
				dynamic_cast<CItem*>(m_pItem1)->Set_Move(true);
			}
			break;
		case 1:
			if (g_iCoin >= 4)
			{
				g_iCoin -= 4;
				g_iItemSale2 = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_purchase.wav", SOUND_EFFECT, g_fSound_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_piggy_purchase_grunt.wav", SOUND_MONSTER, g_fSound_MONSTER);
				dynamic_cast<CItem*>(m_pItem2)->Set_State(0);
			}
			else
			{
				dynamic_cast<CItem*>(m_pItem2)->Set_Move(true);
			}
			break;
		case 2:
			if (g_iCoin >= 2)
			{
				g_iCoin -= 2; 
				g_iItemSale3 = true;
				CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_purchase.wav", SOUND_EFFECT, g_fSound_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"Shop_sfx_store_piggy_purchase_grunt.wav", SOUND_MONSTER, g_fSound_MONSTER);
				dynamic_cast<CItem*>(m_pItem3)->Set_State(0);
				g_iHp += 2;
			}
			else
			{
				dynamic_cast<CItem*>(m_pItem3)->Set_Move(true);
			}
			break;
		}
	}
}

void CShop::IfSaleNext()
{
	if (m_iChoose == 0 && dynamic_cast<CItem*>(m_pItem1)->Get_State() == 0)
	{
		++m_iChoose;
	}

	if (m_iChoose == 1 && dynamic_cast<CItem*>(m_pItem2)->Get_State() == 0)
	{
		++m_iChoose;
	}

	if (m_iChoose == 2 && dynamic_cast<CItem*>(m_pItem3)->Get_State() == 0)
	{
		if (dynamic_cast<CItem*>(m_pItem1)->Get_State() == 0)
			m_iChoose = 1;

		if (dynamic_cast<CItem*>(m_pItem2)->Get_State() == 0)
			m_iChoose = -1;
		else
			m_iChoose = 0;
	}
}

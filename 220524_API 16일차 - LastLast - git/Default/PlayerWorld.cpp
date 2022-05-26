#include "stdafx.h"
#include "PlayerWorld.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "EffectPlayerDust.h"

CPlayerWorld::CPlayerWorld()
{
	ZeroMemory(&m_tInfoCollision, sizeof(INFO));
}


CPlayerWorld::~CPlayerWorld()
{
	Release();
}


void CPlayerWorld::Initialize()
{
	m_tInfo.fCX = 103.f;
	m_tInfo.fCY = 113.f;

	m_fSpeed = 4.f;

	m_pFrameKey = L"Player";
	m_eCurState = IDLE_DOWN;
	m_bStretch = false;

	m_dwPlayerWalkSound = long(0);
}

int CPlayerWorld::Update()
{
	Key_Input();
	OffSet();

	Update_InfoCollision();
	Update_Rect();					// 모든 연산이 끝난 뒤에 최종적인 좌표를 완성
	//Update_RectCollision(0.f, 0.f, 0.f);		// 충돌 렉트 별도 설정

	//// 플레이어가 서있는 타일 위치를 받아옴 - 상호작용 용도
	//m_iTileIndex = CTileMgr::Get_Instance()->Check_Tile(m_tInfoCollision.fX, m_tInfoCollision.fY);

	//CObjMgr::Get_Instance()->Update();

	return OBJ_NOEVENT;
}

void CPlayerWorld::Late_Update()
{
	//CObjMgr::Get_Instance()->Late_Update();

	Motion_Change();
	Move_Frame();
}

void CPlayerWorld::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC		hStretchDC = CBmpMgr::Get_Instance()->Find_Image(L"Stretch");

	if (!m_bStretch)
	{
		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),		// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),					// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,								// 비트맵을 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,					// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));				// 제거하고자 하는 색상
	}
	else
	{
		StretchBlt(hStretchDC,		// 출력할 이미지 핸들
			0,						// 복사 받을 이미지 시작 좌표(Left, Top 좌표)
			0,
			m_tInfo.fCX,			// 출력할 이미지 가로 세로 사이즈	
			m_tInfo.fCY,
			hMemDC,					// 반전해서 출력하고자 하는 텍스처 이미지
			m_tFrame.iFrameStart * (int)m_tInfo.fCX + m_tInfo.fCX,	// 가져올 이미지의 시작점 x,y좌표							// 비트맵 출력 시작 좌표, X,Y
			m_tFrame.iMotion * (int)m_tInfo.fCY,
			-m_tInfo.fCX,			// 복사할 비트맵의 가로, 세로 길이
			m_tInfo.fCY,
			SRCCOPY);

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top + iScrollY),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hStretchDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));						// 제거하고자 하는 색상
	}
	
	//CObjMgr::Get_Instance()->Render(hDC);

	//충돌 Rect Test
	//Rectangle(hDC, (int)m_tInfoCollision.fX - m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY - m_tInfoCollision.fCY * 0.5 + iScrollY, (int)m_tInfoCollision.fX + m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY + m_tInfoCollision.fCY * 0.5 + iScrollY);
}

void CPlayerWorld::Release()
{
}


void CPlayerWorld::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case RUN_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN_UPRIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case IDLE_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN_DOWNRIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case IDLE_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 150;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case WIN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 80;
			m_tFrame.dwTime = GetTickCount();
			break;

		case IDLE_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPlayerWorld::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_bStretch = false;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_eCurState = RUN_DOWNRIGHT;
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_eCurState = RUN_UPRIGHT;
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else
		{
			m_eCurState = RUN_RIGHT;
			m_tInfo.fX += m_fSpeed;
			if (GetTickCount() - m_dwDustTime > 400)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectPlayerDust>::Create(m_tInfo.fX - (rand() % 3 * 10), m_tInfo.fY + 20, rand() % 6));
				m_dwDustTime = GetTickCount();
			}
		}

		if (m_dwPlayerWalkSound + 300.f < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"World_sfx_player_map_walk_0001.wav", SOUND_PLAYER, g_fSound_PLAYER);
			m_dwPlayerWalkSound = GetTickCount();
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_bStretch = true;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_eCurState = RUN_DOWNRIGHT;
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_eCurState = RUN_UPRIGHT;
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else
		{
			m_eCurState = RUN_RIGHT;
			m_tInfo.fX -= m_fSpeed;
			if (GetTickCount() - m_dwDustTime > 400)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectPlayerDust>::Create(m_tInfo.fX - (rand() % 3 * 10), m_tInfo.fY + 20, rand() % 6));
				m_dwDustTime = GetTickCount();
			}
		}

		if (m_dwPlayerWalkSound + 300.f < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"World_sfx_player_map_walk_0001.wav", SOUND_PLAYER, g_fSound_PLAYER);
			m_dwPlayerWalkSound = GetTickCount();
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = RUN_UP;

		if (m_dwPlayerWalkSound + 300.f < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"World_sfx_player_map_walk_0001.wav", SOUND_PLAYER, g_fSound_PLAYER);
			m_dwPlayerWalkSound = GetTickCount();
		}

		if (GetTickCount() - m_dwDustTime > 400)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectPlayerDust>::Create(m_tInfo.fX, m_tInfo.fY + (rand() % 3 * 10), rand() % 6));
			m_dwDustTime = GetTickCount();
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurState = RUN_DOWN;

		if (m_dwPlayerWalkSound + 300.f < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"World_sfx_player_map_walk_0001.wav", SOUND_PLAYER, g_fSound_PLAYER);
			m_dwPlayerWalkSound = GetTickCount();
		}

		if (GetTickCount() - m_dwDustTime > 400)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectPlayerDust>::Create(m_tInfo.fX, m_tInfo.fY - 50, rand() % 6));
			m_dwDustTime = GetTickCount();
		}
	}
	else
	{
		switch(m_eCurState)
		{
		case RUN_UP:
		case RUN_UPRIGHT:
		case IDLE_UP:
			m_eCurState = IDLE_UP;
		break;
		case RUN_RIGHT:
		case IDLE_RIGHT:
			m_eCurState = IDLE_RIGHT;
			break;
		case RUN_DOWNRIGHT:
		case RUN_DOWN:
		case IDLE_DOWN:
			m_eCurState = IDLE_DOWN;
			break;
		}
		
		//m_tFrame.iFrameStart = 0;
		//m_tFrame.iFrameEnd = 0;
		//	//m_eCurState = IDLE;
	}
}

void CPlayerWorld::OffSet()
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 100;
	int		iItvY = 100;

	if (iOffSetX - iItvX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItvX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffSetY - iItvY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItvY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayerWorld::Update_InfoCollision()
{
	m_tInfoCollision.fX = m_tInfo.fX;
	m_tInfoCollision.fY = m_tInfo.fY + 30.f;
	m_tInfoCollision.fCX = 32.f;
	m_tInfoCollision.fCY = 32.f;
}



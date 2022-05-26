#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	m_iDrawID = 0;
	//m_iOption = 0;
	m_iIndex = 0;
	m_TileTag = TILE_END;

}

int CTile::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	//Update_InfoCollision();

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	HDC		hMemDC;

	switch (m_TileTag)
	{
	case TILE_STAGE :
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile_Stage");
			break;
	case TILE_TUTORIAL :
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile_Tutorial");
			break;
	case TILE_SHOP :
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile_Shop");
		break;
	case TILE_RUN :
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile_Run");
		break;
	case TILE_END:
	default :
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile_Collision");
		break;

	case TILE_NPC:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile_NPC");
		break;
	}


	//BitBlt(hDC,
	//	m_tRect.left + iScrollX,
	//	m_tRect.top + iScrollY,
	//	TILECX,
	//	TILECY,
	//	hMemDC,
	//	TILECX * m_iDrawID,
	//	0,
	//	SRCCOPY);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left + iScrollX),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top + iScrollY),
		TILECX,				// 4,5 ���� : ������� ����, ���� ����
		TILECY,
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		TILECX * m_iDrawID,							// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		TILECX,				// ������ ��Ʈ���� ����, ���� ����
		TILECY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����

	// �ε��� ���
	//static TCHAR	m_szIndex[16];
	//swprintf_s(m_szIndex, L"%d", m_iIndexTemp);
	//TextOut(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_szIndex, lstrlen(m_szIndex));
}

void CTile::Release()
{

}

void CTile::Motion_Change()
{
}

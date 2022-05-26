#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"

CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	// 화면사이즈, 타일개수에 따라 전체 타일 생성
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float		fX = (TILECX >> 1) + float(TILECX * j);
			float		fY = (TILECY >> 1) + float(TILECY * i);

			CObj*	pTile = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pTile);
		}
	}
}

void CTileMgr::Update()
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	// 타일 컬링 : 화면에 해당하는 타일만 그리도록 제한

	int	iCullX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	int	iCullWidth = WINCX / TILECX + iCullX + 2;
	int	iCullHeight = WINCY / TILECY + iCullY + 2;

	for (int i = iCullY; i < iCullHeight; ++i)
	{
		for (int j = iCullX; j < iCullWidth; ++j)
		{
			int	iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() < (size_t)iIndex)
				continue;

			dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Index(iIndex);
			m_vecTile[iIndex]->Render(hDC);
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}


void CTileMgr::Picking_Tile(int _mode, POINT _pt, const int& _iDrawID, const int& _iOption, const TILETAG& _tag)
{
	int		x = _pt.x / TILECX;
	int		y = _pt.y / TILECY;

	int	iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	if (0 == _mode) // 충돌, Draw 전환
	{
		//타일 전환
		if (0 == dynamic_cast<CTile*>(m_vecTile[iIndex])->Get_DrawID())
		{
			dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(1);
			return;
		}
		else if (1 == dynamic_cast<CTile*>(m_vecTile[iIndex])->Get_DrawID())
		{
			dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(0);
			return;
		}
	}
	else if (1 == _mode) // Tag 변경 전환
	{
		dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);
		dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_TileTag(_tag);
	}
}

void CTileMgr::Save_Tile()
{
	HANDLE		hFile = CreateFile(L"../Data/Tile_World.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int		iDrawID = 0, iOption = 0;
	TILETAG TileTag = TILE_END;
	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();
		TileTag = dynamic_cast<CTile*>(iter)->Get_TileTag();

		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &TileTag, sizeof(TILETAG), &dwByte, NULL);
	}
	CloseHandle(hFile);
}

void CTileMgr::Load_Tile()
{
	HANDLE		hFile = CreateFile(L"../Data/Tile_World.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	INFO		tInfo{};
	int			iDrawID = 0, iOption = 0;
	TILETAG		TileTag = TILE_END;
	DWORD		dwByte = 0;

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &TileTag, sizeof(TILETAG), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj*		pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pObj)->Set_Option(iOption);

	/*	switch (TileTag)
		{
		case 0:*/
			dynamic_cast<CTile*>(pObj)->Set_TileTag(TileTag);
		//	break;
		//case 1:
		//	dynamic_cast<CTile*>(pObj)->Set_TileTag(TILE_TUTORIAL);
		//	break;
		//case 2:
		//	dynamic_cast<CTile*>(pObj)->Set_TileTag(TILE_SHOP);
		//	break;
		//case 3:
		//	dynamic_cast<CTile*>(pObj)->Set_TileTag(TILE_RUN);
		//	break;
		//case 4:
		//	dynamic_cast<CTile*>(pObj)->Set_TileTag(TILE_END);
		//	break;
		//}
		
		m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
}

CObj* CTileMgr::Check_Tile(float _fX, float _fY)
{
	for (auto& _iter : m_vecTile)
	{
		if (_fX >= _iter->Get_Rect().left &&
			_fX < _iter->Get_Rect().right &&
			_fY >= _iter->Get_Rect().top &&
			_fY < _iter->Get_Rect().bottom)
		{
			return _iter;
		}
	}
	return nullptr;
}

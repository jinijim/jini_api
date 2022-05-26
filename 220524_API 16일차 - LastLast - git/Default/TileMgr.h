#pragma once

#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public :
	const vector<CObj*>&	Get_vecTile()	{ return m_vecTile;}

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	void		Picking_Tile(int _mode, POINT _pt, const int& _iDrawID, const int& _iOption, const TILETAG& _tag);
	void		Save_Tile();
	void		Load_Tile();
	CObj*		Check_Tile(float _fX, float _fY);

public:
	static		CTileMgr*		Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTileMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CTileMgr*		m_pInstance;
	vector<CObj*>			m_vecTile;
};


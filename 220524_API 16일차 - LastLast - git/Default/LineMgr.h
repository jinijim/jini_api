#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(LINENO _NO);
	void		Update();
	void		Render(HDC hDC);
	void		Release();

	bool		Collision_Line(float& _fX, float& _fY, float* pY);
	bool		Collision_LineDown(float& _fX, float& _fY, float* pY);
	
	void		Insert_AlphabetfYList(float _fY);

public:
	static		CLineMgr*		Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
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
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_LineList;
	list<CLine*>			m_MoveLineList;

	vector<float>				m_vecAlphabetfY;
	//list<CLine*>			m_LineList_Tutorial;
	LINENO					m_LineNo;

};

// (자유 낙하 공식)을 이용하여 점프를 구현하라
// Y = 힘 * sin(각도) * 시간 - 1/2(중력계수(9.8) * 시간 * 시간)
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

// (���� ���� ����)�� �̿��Ͽ� ������ �����϶�
// Y = �� * sin(����) * �ð� - 1/2(�߷°��(9.8) * �ð� * �ð�)
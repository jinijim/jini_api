#pragma once

#include "UI.h"

class CUIMgr
{
public:
	CUIMgr();
	~CUIMgr();

public:
	//CUI*			Get_Player() { return m_ObjList[OBJ_PLAYER].back(); }
	//CUI*			Get_Target(OBJID eID, OBJTAG eTagID, CObj* pObj);
	CUI*			Get_ListBack() { return m_UIList.back(); }
	//list<CUI*>	Get_ParryList() { return m_ParryList; }
	list<CUI*>		Get_List() { return m_UIList; }

public:
	void		Add_Object( CUI* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

private:
	list<CUI*>	m_UIList;

public:
	static		CUIMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
		}
		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CUIMgr*			m_pInstance;
};


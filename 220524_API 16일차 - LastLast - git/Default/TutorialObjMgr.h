#pragma once

#include "TutorialObj.h"

class CTutorialObjMgr
{
private:
	CTutorialObjMgr();
	~CTutorialObjMgr();

public:
	CObj*			Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*			Get_Target(OBJID eID, OBJTAG eTagID, CObj* pObj);
	CObj*			Get_ListBack(OBJID _eID) { return m_ObjList[_eID].back(); }
	list<CObj*>		Get_ParryList() { return m_ParryList; }

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Add_ObjectParry(CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJID eID);

private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*> m_ParryList;


public:
	static		CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	static CObjMgr*			m_pInstance;

};


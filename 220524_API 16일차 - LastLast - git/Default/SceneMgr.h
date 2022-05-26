#pragma once

//#include "Logo.h"
//#include "MyMenu.h"
//#include "MyEdit.h"
#include "Stage.h"
#include "World.h"
#include "Tutorial.h"
#include "RunnGun.h"
#include "Shop.h"
#include "Loading.h"
#include "ScoreBoard.h"


class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
public :
	CScene*		Get_Scene() { return m_pScene; }
	SCENEID		Get_SceneID() { return m_eCurScene; }

public:
	void		Scene_Change(SCENEID eID);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release(void);

public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;


};


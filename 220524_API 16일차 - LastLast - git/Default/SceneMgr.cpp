#include "stdafx.h"
#include "SceneMgr.h"
#include "MyEdit.h"
#include "ScrollMgr.h"


CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_END), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

// FSM(finite state machine) : 유한 상태 기계, 자신이 취할 수 있는 유한한 개수의 상태

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		/*case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;
			*/

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_WORLD:
			m_pScene = new CWorld;
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			break;

		case SC_TUTORIAL:
			m_pScene = new CTutorial;
			break;

		case SC_RUN:
			m_pScene = new CRunnGun;
			break;

		case SC_SHOP:
			m_pScene = new CShop;
			break;

		case SC_LOADING:
			m_pScene = new CLoading;
			break;

		case SC_CLEAR:
			m_pScene = new CScoreBoard;
			break;

		}

		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
		CScrollMgr::Get_Instance()->Set_Scroll_Init();
	}
}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}

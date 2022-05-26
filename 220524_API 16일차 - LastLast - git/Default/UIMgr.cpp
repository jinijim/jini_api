#include "stdafx.h"
#include "UIMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}


CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Add_Object(CUI * pObj)
{
	if (nullptr == pObj)
		return;

	m_UIList.push_back(pObj);
}

int CUIMgr::Update(void)
{
	for (auto& iter = m_UIList.begin();
		iter != m_UIList.end(); )
	{
		int iResult = (*iter)->Update();

		if (OBJ_DEAD == iResult)
		{
			Safe_Delete<CUI*>(*iter);
			iter = m_UIList.erase(iter);
		}
		else
			++iter;
	}
	return 0;
}

void CUIMgr::Late_Update(void)
{
	for (auto& iter : m_UIList)
		iter->Late_Update();
}

void CUIMgr::Render(HDC hDC)
{
	for (auto& iter : m_UIList)
		iter->Render(hDC);
}

void CUIMgr::Release(void)
{
	for (auto& iter : m_UIList)
		Safe_Delete<CUI*>(iter);
	m_UIList.clear();
}

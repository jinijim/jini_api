#include "stdafx.h"
#include "TutorialObjMgr.h"
#include "CollisionMgr.h"

CTutorialObjMgr* CTutorialObjMgr::m_pInstance = nullptr;

CTutorialObjMgr::CTutorialObjMgr()
{
}


CTutorialObjMgr::~CTutorialObjMgr()
{
	Release();
}

CTutorialObjMgr* CTutorialObjMgr::Get_Target(OBJID eID, OBJTAG eTagID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*		pTarget = nullptr;
	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		if (iter->Get_Tag() != TAG_END)			// 태그로도 찾기 수정 (TAGEND는 상관없고 특정TAG 보냈을때만 찾기)
		{
			if (iter->Get_Tag() != eTagID)
				continue;
		}


		float	fWidth = abs(pObj->Get_Info().fX - iter->Get_Info().fX);
		float	fHeight = abs(pObj->Get_Info().fY - iter->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CTutorialObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if ((eID >= OBJ_END) || (nullptr == pObj))
		return;

	m_ObjList[eID].push_back(pObj);
}

void CTutorialObjMgr::Add_ObjectParry(CObj * pObj)
{
	m_ParryList.push_back(pObj);
}

int CTutorialObjMgr::Update(void)
{
	// 패링리스트는 비어있을 수 있으므로  리스트에서 지워주기 체크
	for (auto& iter = m_ParryList.begin();
		iter != m_ParryList.end(); )
	{
		if ((*iter)->Get_Dead())
		{
			iter = m_ParryList.erase(iter);
		}
		else
			++iter;
	}


	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	// _DEBUG : cout << "총알 개수 : " << m_ObjList[OBJ_BULLET].size() << endl;

	return 0;
}

void CTutorialObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CTutorialObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}
}

void CTutorialObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			Safe_Delete<CObj*>(iter);

		m_ObjList[i].clear();
	}
}


void CTutorialObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}


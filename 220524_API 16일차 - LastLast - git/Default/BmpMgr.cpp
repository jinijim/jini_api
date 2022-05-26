#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr*		CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImageKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey));

	if (iter == m_mapBit.end())			// 맵에 해당 키가 없으면 새로 넣는다
	{
		CMyBmp*		pBmp = new CMyBmp;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImageKey, pBmp);
	}
}

HDC CBmpMgr::Find_Image(const TCHAR * pImageKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImageKey));

	if (iter == m_mapBit.end())
		return nullptr;


	return iter->second->Get_MemDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}

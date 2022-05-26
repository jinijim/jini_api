#include "stdafx.h"
#include "TutorialObj.h"

CTutorialObj::CTutorialObj()
	: m_eCurState(0), m_ePreState(99)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CTutorialObj::~CTutorialObj()
{
}

void CTutorialObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CTutorialObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}


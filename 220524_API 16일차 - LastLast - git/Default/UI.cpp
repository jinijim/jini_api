#include "stdafx.h"
#include "UI.h"


CUI::CUI()
	: m_bDead(false), m_iOption(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CUI::~CUI()
{
}

void CUI::Update_Rect(void)
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CUI::Move_Frame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CUI::Move_Frame_MultiLine(int _iX, int _iY)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > _iX)
		{
			m_tFrame.iFrameStart = 0;
			++m_tFrame.iMotion;
		}
	}
}

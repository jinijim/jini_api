#pragma once

#include "Include.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX() { return m_fScrollX; }
	float		Get_ScrollY() { return m_fScrollY; }

	void		Set_Scroll_Init()	{ m_fScrollX = 0.f; m_fScrollY = 0.f; }
	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Set_ScrollY(float _fY) { m_fScrollY += _fY; }
	void		Set_ScrollYLock(float _fY) { m_fScrollY = _fY; }
	void		Set_ScrollXLock(float _fX) { m_fScrollX = _fX; }
	void		Scroll_Lock();
	void		Scroll_LockX();
	void		Scroll_LockY();

public:
	static		CScrollMgr*		Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
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
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX = 0.f;
	float					m_fScrollY = 0.f;
};


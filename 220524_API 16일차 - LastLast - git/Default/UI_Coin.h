#pragma once
#include "UI.h"

class CUI_Coin :
	public CUI
{
public:
	CUI_Coin();
	virtual ~CUI_Coin();

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	//virtual void	Motion_Change()		override;

private:
	//DWORD			m_dwBirthTime;
	//	DWORD			m_dwAttackTime;
	//	int				m_iPhase;
	//CObj*			m_pPlayer;
	//int				m_iPlayerHp;

	//int				m_iX;
	//int				m_iY;
};


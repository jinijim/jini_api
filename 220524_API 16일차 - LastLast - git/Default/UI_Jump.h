#pragma once
#include "UI.h"
class CUI_Jump :
	public CUI
{
public:
	CUI_Jump();
	virtual ~CUI_Jump();

//public:
//	void			Set_bMove(bool _b) { m_bMove = _b; }

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	//virtual void	Motion_Change()		override;
/*
public:
	virtual void	Move();*/


private:
	DWORD			m_dwMoveTime;
	bool			m_bMove;

	int				m_iX;
	int				m_iY;
};


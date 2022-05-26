#pragma once
#include "Obj.h"


class CShop_Piggy :
	public CObj
{
public:
	CShop_Piggy();
	virtual ~CShop_Piggy();

public:
	enum STATE { IDLE, BYE, END };

//public :
//	void	Set_State(int _iState) { m_eCurState = _iState; }
//
public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

};


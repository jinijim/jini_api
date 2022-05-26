#pragma once
#include "Obj.h"
class CCoin :
	public CObj
{
public:
	CCoin();
	virtual ~CCoin();

public:
	enum STATE { IDLE, DEAD, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

private:
	/*float			m_fBirthX;*/
};


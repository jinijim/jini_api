#pragma once
#include "Obj.h"

class CMonsterCrown :
	public CObj
{
public:
	CMonsterCrown();
	virtual ~CMonsterCrown();

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
	float			m_fBirthX;
};


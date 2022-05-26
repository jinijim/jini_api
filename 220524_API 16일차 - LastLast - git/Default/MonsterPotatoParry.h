#pragma once
#include "Obj.h"
class CMonsterPotatoParry :
	public CObj
{
public:
	CMonsterPotatoParry();
	virtual ~CMonsterPotatoParry();

public:
	enum STATE { IDLE, DEAD, END };

public:
	virtual void	Initialize(void)		override;
	virtual int		Update(void)			override;
	virtual	void	Late_Update(void)		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release(void)			override;
	virtual void	Motion_Change(void)		override;
};


#pragma once
#include "Obj.h"
class CMonsterOnionParry :
	public CObj
{
public:
	CMonsterOnionParry();
	virtual ~CMonsterOnionParry();

public:
	enum STATE { IDLE, DEAD, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

};


#pragma once
#include "Obj.h"
class CMonsterPotatoBullet : 
	public CObj
{
public:
	CMonsterPotatoBullet();
	virtual ~CMonsterPotatoBullet();

public:
	enum STATE { IDLE, ATTACK, DEAD, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;
};


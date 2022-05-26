#pragma once
#include "Obj.h"
class CEffectPlayerDust :
	public CObj
{
public:
	CEffectPlayerDust();
	virtual ~CEffectPlayerDust();

public:
	enum STATE { IDLE, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

private:
	DWORD			m_dwDeadTime;
};


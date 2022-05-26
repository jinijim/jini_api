#pragma once
#include "Obj.h"
class CEffectScene :
	public CObj
{
public:
	CEffectScene();
	virtual ~CEffectScene();

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


#pragma once
#include "WorldObj.h"
class CCoinBig :
	public CWorldObj
{
public:
	CCoinBig(float _fX, float _fY);
	virtual ~CCoinBig();

public:
	virtual void	Initialize()		override;
	virtual void	Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

private :
	DWORD			m_dwRenderTime;
};


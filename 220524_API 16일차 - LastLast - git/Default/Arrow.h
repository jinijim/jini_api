#pragma once
#include "Obj.h"
class CArrow :
	public CObj
{
public:
	CArrow();
	virtual ~CArrow();
public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

};


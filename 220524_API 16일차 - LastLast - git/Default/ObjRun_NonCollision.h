#pragma once
#include "Obj.h"
class CObjRun_NonCollision :
	public CObj
{
public:
	CObjRun_NonCollision();
	virtual ~CObjRun_NonCollision();


public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

};


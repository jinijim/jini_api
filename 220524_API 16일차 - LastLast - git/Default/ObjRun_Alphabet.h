#pragma once
#include "Obj.h"
class CObjRun_Alphabet :
	public CObj
{
public:
	CObjRun_Alphabet();
	virtual ~CObjRun_Alphabet();

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;
};


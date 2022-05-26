#pragma once
#include "Obj.h"

class CBlock :
	public CObj
{
public:
	CBlock();
	virtual ~CBlock();

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;



//private :
//	int				m_BlockNo;

};


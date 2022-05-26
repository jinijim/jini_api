#pragma once
#include "Obj.h"
class CObjRun_Collision :
	public CObj
{
public:
	CObjRun_Collision();
	virtual ~CObjRun_Collision();

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

	virtual	void	Update_InfoCollision();



//private:
//	int				m_iNo;
};


#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	enum STATE { IDLE, DEAD, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

//
private :
//	STATE			m_ePreState;
//	STATE			m_eCurState;
	DWORD m_dwDeadMotionTime;
	bool m_bDeathOut;
};


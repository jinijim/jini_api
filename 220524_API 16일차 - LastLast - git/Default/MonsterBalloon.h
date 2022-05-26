#pragma once
#include "Obj.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

class CMonsterBalloon :
	public CObj
{
public:
	CMonsterBalloon();
	virtual ~CMonsterBalloon();

public:
	enum STATE { IDLE, DEAD, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

public:
	void			Set_Phase();

private:
	DWORD		m_dwPhaseTime;
	DWORD		m_dwAttackTime;
	int			m_iPhase;
	float		m_fBirthX;

	CObj*		m_pPlayer;
	bool		m_bDown;

	/*
	CObj*		m_pCannonBar;*/
};


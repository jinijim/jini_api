#pragma once
#include "Obj.h"
//#include "MonsterCannonBar.h"

class CMonsterCannon :
	public CObj
{
public:
	CMonsterCannon();
	virtual ~CMonsterCannon();

public:
	enum STATE { IDLE, ATTACK, DEAD, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

public:
	void			Attack();


private:
	DWORD		m_dwPhaseTime;
	DWORD		m_dwAttackTime;
	DWORD		m_dwMotionTime;

	//int		m_iPhase;
	//float		m_fBirthX;
/*
	CObj*		m_pCannonBar;*/

	CObj*			m_pPlayer;
};


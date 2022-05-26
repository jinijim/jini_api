#pragma once
#include "Obj.h"
class CMonsterMachine :
	public CObj
{
public:
	CMonsterMachine();
	virtual ~CMonsterMachine();

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
	void			Set_Phase();

private:
	DWORD			m_dwPhaseTime;
	DWORD			m_dwAttackTime;
	DWORD			m_dwAttackSoundTime;


	CObj*			m_pPlayer;
};


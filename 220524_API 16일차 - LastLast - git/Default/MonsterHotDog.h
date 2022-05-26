#pragma once
#include "Obj.h"
class CMonsterHotDog :
	public CObj
{
public:
	CMonsterHotDog();
	virtual ~CMonsterHotDog();

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
	//DWORD			m_dwPhaseTime;
	DWORD			m_dwAttackTime;
	//int				m_iPhase;

	bool			m_bAttack;

	float			m_fBirthX;

	CObj*			m_pPlayer;
};


#pragma once
#include "Obj.h"
class CMonsterOnion :
	public CObj
{
public:
	CMonsterOnion();
	virtual ~CMonsterOnion();

public:
	enum STATE { BIRTH, IDLE, ATTACK, DEAD, END };

//public :
//	void			Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

public:
	virtual void	Initialize(void)		override;
	virtual int		Update(void)			override;
	virtual	void	Late_Update(void)		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release(void)			override;
	virtual void	Motion_Change(void)		override;

public:
	void			Set_Phase();


private:
	DWORD			m_dwPhaseTime;
	DWORD			m_dwAttackTime;

	bool			m_bSoundCrying;
	int				m_iPhase;

	CObj*			m_pPlayer;
};


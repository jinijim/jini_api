#pragma once
#include "Obj.h"
#include "Scene.h"

class CMonsterPotato : 
	public CObj
{
public:
	CMonsterPotato();
	virtual ~CMonsterPotato();

public:
	enum STATE { IDLE, ATTACK, DEAD, END };

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

public :
	void			Set_Phase();
	

private :
	DWORD			m_dwPhaseTime;
	DWORD			m_dwAttackTime;
	int				m_iPhase;
};


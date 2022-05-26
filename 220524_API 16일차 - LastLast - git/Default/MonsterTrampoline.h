#pragma once
#include "Obj.h"
class CMonsterTrampoline :
	public CObj
{
public:
	CMonsterTrampoline();
	virtual ~CMonsterTrampoline();

public:
	enum STATE { IDLE, JUMP, END };

public :
	void			Set_bJump(bool _b) { m_bJump = _b; }
public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;
	
	virtual  void	Update_InfoCollision() override;

public:
	void			Move();

private:
	//DWORD			m_dwPhaseTime;
	//DWORD			m_dwAttackTime;
	CObj*			m_pPlayer;
	bool			m_bJump;
	DWORD			m_dwMotionTime;
	float			m_fXBirth;
	bool			m_bJumpSound;
};



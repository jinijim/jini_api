#pragma once
#include "UI.h"
#include "Obj.h"

class CUI_HP :
	public CUI
{
public:
	CUI_HP();
	virtual ~CUI_HP();


public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	//virtual void	Motion_Change()		override;

public :
	void			Move();

private:
	//DWORD			m_dwBirthTime;
	//	DWORD			m_dwAttackTime;
	//	int				m_iPhase;
	CObj*			m_pPlayer;
	int				m_iPlayerHp;
	int				m_iPlayerHpBefore;

	bool			m_bMove;
	DWORD			m_dwMoveTime;

	DWORD			m_dwMoveCoolTime;

	/*int				m_iX;
	int				m_iY;*/
	float			m_fBirthX;
	//float			m_fBirthY;
	float			m_fSpeed;

	int				m_MoveIndex;
};


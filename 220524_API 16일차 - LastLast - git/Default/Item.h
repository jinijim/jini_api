#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

public :
	void			Set_State(int _iState) { m_iState = _iState; }
	const int&		Get_State() { return m_iState; }
	void			Set_Move(bool _bMove) { m_bMove = _bMove; }
public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

public :
	void			Move();


private :
	int	m_iState;
	float m_fBirthY;
	DWORD m_dwMoveCoolTime;
	DWORD m_dwMoveTime;

	bool m_bMove;
};


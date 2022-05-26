#pragma once
#include "Obj.h"
class CPlayerWorld :
	public CObj
{
public:
	CPlayerWorld();
	~CPlayerWorld();

public:
	enum STATE {  RUN_UP, RUN_UPRIGHT, IDLE_RIGHT, RUN_RIGHT, RUN_DOWNRIGHT, IDLE_DOWN, RUN_DOWN, WIN, IDLE_UP, END };

public :
	void			Set_Speed(const float& _fSpeed) { m_fSpeed = _fSpeed; }

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

	virtual		void	Update_InfoCollision();

public:
	void		Key_Input();
	void		OffSet();

private :
	bool		m_bStretch;
	DWORD		m_dwPlayerWalkSound;
	DWORD		m_dwDustTime;

	//int		m_iTileIndex;
};


#pragma once
#include "Include.h"

class CTutorialObj
{
public:
	CTutorialObj();
	~CTutorialObj();

public:
	enum STATE { IDLE, LIVE, END };

public:
	void		Set_Pos(const float& _fX, const float& _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void		Set_State(const int& _state) { m_eCurState = _state; }
public:
	virtual		void	Initialize()		PURE;
	virtual		void	Update()			PURE;
	virtual		void	Late_Update()		PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release()			PURE;
	virtual		void	Motion_Change()		PURE;

protected:
	void		Update_Rect();
	void		Move_Frame();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;

	TCHAR*		m_pFrameKey;
	int			m_ePreState;
	int			m_eCurState;

};


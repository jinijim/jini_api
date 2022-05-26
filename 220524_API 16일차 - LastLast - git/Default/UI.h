#pragma once
#include "Include.h"

class CUI
{
public:
	CUI();
	virtual ~CUI();

public :
	void	Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX;	m_tInfo.fY = _fY; }
	void	Set_Option(const int& _iOption) { m_iOption = _iOption; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;
	//virtual		void	Motion_Change(void) PURE;

protected:
	void		Update_Rect(void);
	void		Move_Frame(void);
	void		Move_Frame_MultiLine(int _iX, int _iY);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;

	bool		m_bDead;

	int			m_iOption;
};


#pragma once
#include "WorldObj.h"
class CNpcMac :
	public CWorldObj
{
public:
	CNpcMac();
	virtual ~CNpcMac();

public :
	void			Set_State(const int& _State)		{ m_eCurState = _State; }
	void			Set_TalkNo_Plus()					{ ++m_iTalkNo; }
	void			Set_TalkNo_Init()					{ m_iTalkNo = -1; }
	int				Get_TalkNo()						{ return m_iTalkNo; }

public:
	virtual void	Initialize()		override;
	virtual void	Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

public :
	//void			OffSet();
	void			Render_Talk(HDC hDC);

private:
	//int		m_iFlagNo;
	int			m_iTalkNo;

	bool		m_bCoinGet;
	CWorldObj*  m_pCoin;


};


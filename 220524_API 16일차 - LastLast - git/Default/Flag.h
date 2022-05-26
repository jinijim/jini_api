#pragma once
#include "WorldObj.h"
class CFlag :
	public CWorldObj
{
public:
	CFlag();
	virtual ~CFlag();

public :
	void			Set_reStart(bool _b) { m_reStart = _b; }

public:
	virtual void	Initialize()		override;
	virtual void	Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

public :
	void			Move_Frame_Middle(int _i);

private :
	//int		m_iFlagNo;
	bool		m_reStart;
};


#pragma once
#include "UI.h"
#include "Obj.h"


class CUIInventory :
	public CUI
{
public:
	CUIInventory();
	virtual ~CUIInventory();

public :
	void			Set_Depth(int _i) { m_iDepth = _i; }

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;

private :
	//CObj*			m_pPlayer;
	int				m_iDepth;
	int				m_iChoose;
};


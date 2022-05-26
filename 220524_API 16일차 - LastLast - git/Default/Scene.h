#pragma once

#include "Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	void		Set_Gage(int _iGage) { m_iGage = _iGage; }

public:
	virtual void	Initialize() PURE;
	virtual void	Update() PURE;
	virtual void	Late_Update() PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release() PURE;

private :
	int			m_iGage;
};


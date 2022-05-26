#pragma once

#include "Include.h"
#include "Obj.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	~CLine();

public:
	const LINE& Get_Info() const { return m_tInfo; }
	//void Set_Info(float _LPointX, float _LPointY, float _RPointX, float _RPointY ) 
	//{ 
	//	m_tInfo.tLPoint.fX = _LPointX;
	//	m_tInfo.tLPoint.fY = _LPointY;
	//	m_tInfo.tRPoint.fX = _RPointX;
	//	m_tInfo.tRPoint.fY = _RPointY;
	//}
	void Set_InfoMoveY(float _MinY, float _MaxY);


public:
	void	Render(HDC hDC);

private:
	LINE		m_tInfo;
	float		m_fSpeed = 2.f;
};


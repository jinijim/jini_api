#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*	Create()
	{
		CObj*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create(float _fX, float _fY)
	{
		CObj*	pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}

	static CObj*	Create(float _fX, float _fY, float _fAngle)
	{
		CObj*	pObj = new T;

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);
		pObj->Initialize();

		return pObj;
	}

	// Run Obj 积己侩 or 可记 汲沥侩
	static CObj*	Create(float _fX, float _fY, int _iNo)
	{
		CObj*	pObj = new T;

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Option(_iNo);
		pObj->Initialize();

		return pObj;
	}
};


#pragma once

#include "UI.h"

template<typename T>
class CAbstractFactoryUI
{
public:
	CAbstractFactoryUI() {}
	~CAbstractFactoryUI() {}

public:
	static CUI*	Create()
	{
		CUI*	pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CUI*	Create(float _fX, float _fY)
	{
		CUI*	pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}

	// Run Obj 积己侩 or 可记 汲沥侩
	static CUI*	Create(float _fX, float _fY, int _iNo)
	{
		CUI*	pObj = new T;

		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Option(_iNo);
		pObj->Initialize();

		return pObj;
	}
};


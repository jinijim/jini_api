#pragma once
#include "Scene.h"
#include "Obj.h"

class CShop :
	public CScene
{
public:
	CShop();
	virtual ~CShop();

public:
	virtual void Initialize()	override;
	virtual void Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()		override;

public:
	void		KeyInput();
	void		IfSaleNext();


private:
	DWORD	m_dwExit;

	CObj*	m_pPiggy;

	CObj*	m_pItem1;
	CObj*	m_pItem2;
	CObj*	m_pItem3;

	int		m_iChoose;
	int     m_iChooseStd;
};


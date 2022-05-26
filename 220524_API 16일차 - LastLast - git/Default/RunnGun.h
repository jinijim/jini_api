#pragma once
#include "Scene.h"
#include "Obj.h"

class CRunnGun :
	public CScene
{
public:
	CRunnGun();
	virtual ~CRunnGun();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

private :
	void		Win();


private:
	CObj*	m_pPlayer;
	//CObj* m_pMouse;

	CObj*	m_pCrown;
	CObj*	m_pCannonBar;
	CObj*	m_pCannon1;
	CObj*	m_pCannon2;
	CObj*	m_pCannon3;
	CObj*	m_pTram;
	CObj*	m_pBoss;
	
	//CObj* m_pPlayerWorld;

	bool	m_bCannonDead;
	
	DWORD	m_dwWIn;
	bool	m_bFinish;
};


#pragma once
#include "Scene.h"
#include "Obj.h"

class CStage : 
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public :
	void		 Set_Gage(int _iGage) { m_iGage = _iGage; }

public:
	virtual void Initialize()	override;
	virtual void Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()		override;

public :
	void		SpawnPotato();
	void		SpawnOnion();
	void		Win();

private :
	CObj*	m_pPlayer;
	CObj*	m_pMonsterPotato;
	CObj*	m_pMonsterOnion;

	bool	m_bMonsterOnionSpawn;
	DWORD	m_dwMonsterOnionSpawn;
	DWORD	m_dwWIn;

	DWORD	m_dwAnnounce;
	bool    m_bAnnounce;
	bool	m_bFinish;

	int		m_iGage;
};


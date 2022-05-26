#pragma once
#include "Scene.h"
#include "Obj.h"
#include "WorldObj.h"
#include "UI.h"

class CWorld : public CScene
{
public:
	CWorld();
	virtual ~CWorld();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public :
	void			Key_Input();
	void			Interactive_Object();

private:
	CObj*			m_pPlayerWorld;
	vector<CObj*>	m_vecTile;
	CObj*			m_pPlayerTile; //타일 객체 포인터

	CWorldObj*		m_pFlag;
	CWorldObj*		m_pNpcMac;
	bool			m_bNpcOrPlayer;
	DWORD			m_dwNpcOrPlayerRender;

	bool			m_bInventoryCreate;
	bool			m_bInventory;

	CUI*			m_pInventory;
};


#pragma once
#include "Scene.h"
#include "Obj.h"
#include "TutorialObj.h"

class CTutorial :
	public CScene
{
public:
	CTutorial();
	virtual ~CTutorial();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

private :
	CObj* m_pPlayer;

	CTutorialObj* m_pBlock;
};


#pragma once
#include "Scene.h"
class CLoading :
	public CScene
{
public:
	CLoading();
	virtual ~CLoading();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

protected:
	void		Move_Frame_MultiLine(int _iX, int _iY);

private:
	DWORD		m_dwExitTime;
	FRAME		m_tFrame;
};


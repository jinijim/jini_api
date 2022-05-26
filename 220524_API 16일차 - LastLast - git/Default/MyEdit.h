#pragma once
#include "Scene.h"
class CMyEdit : public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();

private:
	float		m_fSpeed;
	TILETAG		m_Tag;

};


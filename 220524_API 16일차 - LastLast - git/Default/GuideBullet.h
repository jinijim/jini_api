#pragma once
#include "Obj.h"
class CGuideBullet :
	public CObj
{
public:
	CGuideBullet();
	virtual ~CGuideBullet();

public:
	enum STATE { IDLE, DEAD, END };

public :
	void	Set_PlayerFrameKey(TCHAR* _Key) { m_pPlayerFrameKey = _Key; }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Motion_Change() override;

public :
	void	AngleSetting();

private :
	CObj*		m_pPlayer;
	TCHAR*		m_pPlayerFrameKey;

	float		m_fAngleOriginal;
	CObj*		m_pTargetOriginal;
	
	bool		m_bAngleFirst;

	DWORD		m_AngleTime;
	DWORD		m_AngleTime2;

	float		m_fTempX;
	float		m_fTempY;

	DWORD		m_DeathTime;

};


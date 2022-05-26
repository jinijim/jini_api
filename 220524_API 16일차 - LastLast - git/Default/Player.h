#pragma once
#include "Obj.h"
#include "Scene.h"


class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	enum STATE	{ IDLE, RUN, RUN_ATTACK, JUMP, DOWN, DOWN_ATTACK, UP_ATTACK, DASH, ATTACK, HIT /*= 90*/, PARRY, DEAD, END };
	enum GUN	{ GUN_TOY, GUN_MISSILE, GUN_END };

public :
	void		Set_ParryKill(bool _b)	{ m_bParryKill = _b; }
	void		Set_fStdY(float _y)		{ m_fYStd = _y; }
	//void		Set_bFloar(bool _b) { m_bFloar = _b; }
	void		Set_bJump(bool _b)		{ m_bJump = _b; }
	void		Set_Jump_Stop();

	bool		Get_ParryKill()			{ return m_bParryKill; }
	float		Get_fYStd()				{ return m_fYStd; }
	int			Get_iGun()				{ return m_iGun; }

public:
	virtual void	Initialize(void)		override;
	virtual int		Update(void)			override;
	virtual	void	Late_Update(void)		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release(void)			override;
	virtual void	Motion_Change(void)		override;

	virtual void	Update_InfoCollision();

private:
	void		Key_Input(void);
	void		Jumping(void);
	void		Dash(void);
	void		Hitted(void);
	void		OffSet();
	void		Move_Rock();

public :
	void		Parring(void);
	void		Insert_Bullet(float _fX, float _fY, float _angle);
	void		JumpSetting(void);
	void		ParrySetting(bool _bParryMontion);


private:
	CScene*		m_pScene;

	float		m_fYStd;
	float		m_fYStdBefore;
	bool		m_bfall;

	//bool		m_bFloar;
	bool		m_bDash;
	bool		m_bDashLeftRight;
	bool		m_bJump;		// 점프 상태 확인
	bool		m_bJumpBefore;
	float		m_fJumpPower;	// 점프 힘
	float		m_fJumpTime;	// 점프 중 진행 시간
	bool		m_bJumpDown;
	bool		m_bJumpParring;
	bool		m_bParryKill;
	bool		m_bParryMotion;		// 패링이랑 비슷하지만 트램펄린 점프 여부 (Tram이면 패링모션 안함)
	int			m_iGun;
	float		m_fCTemp;
	bool		m_bSuperMode;
	//int			m_iDashIndex;

	DWORD		m_dwBulletCoolTime;
	DWORD		m_dwDashCoolTime;
	DWORD		m_dwParryTime;
	DWORD		m_dwHitSoundTime;
	DWORD		m_dwDustTime;
	DWORD		m_dwDashTime;
	DWORD		m_dwDownTime;

	TCHAR*		m_pFrameKeyBefore;

};
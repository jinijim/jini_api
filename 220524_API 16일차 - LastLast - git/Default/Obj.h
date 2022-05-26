#pragma once
#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
	
public:
	void	Set_Pos(float _fX, float _fY)			{	m_tInfo.fX = _fX;	m_tInfo.fY = _fY; }
//	void	Set_Dir(DIRECTION eDir)					{ m_eDir = eDir; }
	void	Set_Dead()								{ m_bDead = true; /*m_dwDeadMotionTime = GetTickCount();*/ }
	void	Set_Angle(float _fAngle)				{ m_fAngle = _fAngle; }
	void	Set_Target(CObj* _pTarget)				{ m_pTarget = _pTarget; }

	void	Set_PosX(float _fX)						{ m_tInfo.fX += _fX; }
	void	Set_PosY(float _fY)						{ m_tInfo.fY += _fY; }
	void	Set_PosY2(float _fY)					{ m_tInfo.fY = _fY; }
	void	Set_PosYBefore(/*float _fY*/)			{ m_tInfo.fY = m_fYBefore; }
	void	Set_bHit(bool _b)						{ m_bHit = _b; }
	void	Set_bSuper(bool _b)						{ m_bSuper = _b; }
	void	Set_eState(int _iState)					{ m_eCurState = _iState; }
	void	Set_Option(const int& _iOption)			{ m_iOption = _iOption; }
	void	Set_HPPlus(const int& _iHp)				{ m_iHp += _iHp; }
	void	Set_Damage(const int& _iDamage);

	const int&		Get_Hp() const					{ return m_iHp; }
	const bool&		Get_Dead() const				{ return m_bDead; }
	const int&		Get_Attack(void) const			{ return m_iAttack; }
	const OBJTAG&	Get_Tag(void) const				{ return m_Tag; }
	const bool&		Get_bHit(void) const			{ return m_bHit; }
	const bool&		Get_bSuper(void) const			{ return m_bSuper; }
	//const int		Get_eState(void) const			{ return m_eCurState; }
	TCHAR*&			Get_FrameKey(void) 				{ return m_pFrameKey; }
	bool			Get_Parry()						{ return m_bParry; }
	float			Get_YBefore()					{ return m_fYBefore; }
	bool			Get_bCollision()				{ return m_bCollision; }

	const INFO&		Get_Info(void)					{ return m_tInfo; }
	const INFO&		Get_InfoCollision()				{ return m_tInfoCollision; }
	const RECT&		Get_Rect(void) const			{ return m_tRect; }
	const RECT&		Get_RectCollision(void) const	{ return m_tRectCollision; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;
	virtual		void	Motion_Change(void) PURE;

	virtual		void	Update_InfoCollision();

protected:
	void		Update_Rect(void);
	void		Update_RectCollision(float _fTempLeft, float _fTempTop, float _fTempRight, float _fTempBottom);
	void		Move_Frame(void);
	void		Move_Frame_MultiLine(int _iX, int _iY);


protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	INFO		m_tInfoCollision;
	RECT		m_tRectCollision;
	FRAME		m_tFrame;

	float		m_fSpeed;
	float		m_fAngle;

	float		m_fYBefore;


	//DIRECTION	m_eDir;
	bool		m_bDead;
	bool		m_bDeadEffect;

	CObj*		m_pTarget;
	
	TCHAR*		m_pFrameKey;
	int			m_ePreState;
	int			m_eCurState;

	int			m_iHp;
	int			m_iAttack;

	bool		m_bHit;
	bool		m_bSuper;
	DWORD		m_dwHitCoolTime;

	OBJTAG		m_Tag;	

	DWORD		m_dwDeadMotionTime;

	bool		m_bParry;

	bool		m_bCollision;
	int			m_iOption;

};


#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f),/* m_eDir(DIR_END),*/ m_bDead(false), m_bDeadEffect(false), m_fAngle(0.f), m_iHp(0), m_iAttack(0), m_eCurState(0), m_ePreState(99), m_bHit(false), m_bSuper(false), m_bParry(false), m_bCollision(true), m_iOption(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tRectCollision, sizeof(RECT));
	m_dwDeadMotionTime = long(0);
}

CObj::~CObj()
{
}

void CObj::Set_Damage(const int & _iDamage)
{
	if (!m_bHit && !m_bSuper /*&& !m_bParry*/)
	{
		m_iHp -= _iDamage;
		m_dwHitCoolTime = GetTickCount();

		if (TAG_PLAYER == m_Tag)
		{
			m_bHit = true;
			m_bSuper = true;
		}
	}
}

void CObj::Update_Rect(void)
{
	m_tRect.left   = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top    = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
 	m_tRect.right  = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Update_RectCollision(float _fTempLeft, float _fTempTop, float _fTempRight, float _fTempBottom)
{
	m_tRectCollision.left = (long)(m_tRect.left + _fTempLeft);
	m_tRectCollision.top = (long)(m_tRect.top + _fTempTop);
	m_tRectCollision.right = (long)(m_tRect.right - _fTempRight);
	m_tRectCollision.bottom = (long)(m_tRect.bottom - _fTempBottom);
}

void CObj::Update_InfoCollision()
{
	m_tInfoCollision.fX = m_tInfo.fX;
	m_tInfoCollision.fY = m_tInfo.fY;
	m_tInfoCollision.fCX = m_tInfo.fCX;
	m_tInfoCollision.fCY = m_tInfo.fCY;
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CObj::Move_Frame_MultiLine(int _iX, int _iY)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > _iX)
		{
			m_tFrame.iFrameStart = 0;
			++m_tFrame.iMotion;

			if (m_tFrame.iMotion >= _iY)
				m_tFrame.iMotion = 0;
		}
	}
}

//bool CObj::Move_Frame(void)
//{
//	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
//	{
//		m_tFrame.iFrameStart++;
//
//		m_tFrame.dwTime = GetTickCount();
//
//		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
//		{
//			m_tFrame.iFrameStart = 0;
//			return true;
//		}
//	}
//	return false;
//}

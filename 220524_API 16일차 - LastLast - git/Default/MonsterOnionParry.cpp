#include "stdafx.h"
#include "MonsterOnionParry.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CMonsterOnionParry::CMonsterOnionParry()
{
	m_Tag = TAG_MONSTER;
}


CMonsterOnionParry::~CMonsterOnionParry()
{
	Release();
}

void CMonsterOnionParry::Initialize()
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 80.f;

	m_fSpeed = 5.f;

	m_iHp = 2;
	m_iAttack = 1;

	m_bParry = true;


	m_pFrameKey = L"Boss_Onion_Parry";
	m_eCurState = IDLE;

	//m_tFrame.iFrameStart = 0;
	//m_tFrame.iFrameEnd = 3;
	//m_tFrame.iMotion = 0;
	//m_tFrame.dwSpeed = 100;
	//m_tFrame.dwTime = GetTickCount();

	////패링 리스트에 별도 추가
	CObjMgr::Get_Instance()->Add_ObjectParry(this);
}

int CMonsterOnionParry::Update()
{
	if (m_bDead || !m_iHp)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;
	Update_Rect();
	Update_RectCollision(15.f, 15.f, 15.f, 15.f);

	return OBJ_NOEVENT;
}

void CMonsterOnionParry::Late_Update()
{
	if (0 >= m_tRect.right || WINCX <= m_tRect.left ||
		0 >= m_tRect.bottom || WINCY <= m_tRect.top)
		m_bDead = true;

	Motion_Change();
	Move_Frame();
}

void CMonsterOnionParry::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),				// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	//Rectangle(hDC, (int)m_tRectCollision.left, (int)m_tRectCollision.top, (int)m_tRectCollision.right, (int)m_tRectCollision.bottom);
}

void CMonsterOnionParry::Release()
{
}

void CMonsterOnionParry::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

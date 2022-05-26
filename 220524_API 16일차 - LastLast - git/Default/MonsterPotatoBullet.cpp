#include "stdafx.h"
#include "MonsterPotatoBullet.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CMonsterPotatoBullet::CMonsterPotatoBullet()
{
	m_Tag = TAG_MONSTER;
}


CMonsterPotatoBullet::~CMonsterPotatoBullet()
{
	Release();
}

void CMonsterPotatoBullet::Initialize(void)
{
	m_tInfo.fCX = 135.f;
	m_tInfo.fCY = 140.f;

	m_fSpeed = 5.f;

	m_iHp = 2;
	m_iAttack = 1;

	m_pFrameKey = L"Boss_Potato_Bullet";
	m_eCurState = IDLE;
}

int CMonsterPotatoBullet::Update(void)
{
	if (m_bDead || !m_iHp)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Stage_sfx_level_veggies_Potato_Worm_Explode_01.wav", SOUND_MONSTER, g_fSound_MONSTER);
		return OBJ_DEAD;

	}

	m_tInfo.fX -= m_fSpeed;
	Update_Rect();
	Update_RectCollision(35.f, 50.f, 25.f, 30.f);

	return OBJ_NOEVENT;
}

void CMonsterPotatoBullet::Late_Update(void)
{
	if (0 >= m_tRect.right || WINCX <= m_tRect.left ||
		0 >= m_tRect.bottom || WINCY <= m_tRect.top)
		m_bDead = true;

	Motion_Change();
	Move_Frame();
}

void CMonsterPotatoBullet::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),				// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top ),
		int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
	
	//Rectangle(hDC, (int)m_tRectCollision.left, (int)m_tRectCollision.top, (int)m_tRectCollision.right, (int)m_tRectCollision.bottom);
}

void CMonsterPotatoBullet::Release(void)
{

}

void CMonsterPotatoBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

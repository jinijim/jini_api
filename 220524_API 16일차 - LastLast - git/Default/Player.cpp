#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
//#include "Shield.h"
//#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#include "Bullet.h"
#include "GuideBullet.h"
#include "Stage.h"
#include "CollisionMgr.h"
#include "UI_Weapon.h"
#include "EffectPlayerDust.h"

CPlayer::CPlayer()
{
	m_Tag = TAG_PLAYER;
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fCX = 140.f;
	m_tInfo.fCY = 160.f;
	m_fSpeed = 7.f;
	m_fYStd = 800.f;

	m_iHp = g_iHp;
	m_iGun = GUN_TOY;

	m_bDash = false;
	m_bDashLeftRight = false; // right : false
	m_bJump = false;
	m_bJumpBefore = false;
	m_fJumpPower = 17.f;
	m_fJumpTime = 0.f;
	m_bJumpParring = false;
	m_bParryKill = false;
	m_bJumpDown = false;
	m_bfall = false;
	m_bSuperMode = false;

	m_dwBulletCoolTime = GetTickCount();
	m_dwParryTime = GetTickCount();
	m_dwHitSoundTime = GetTickCount();
	m_dwDustTime = GetTickCount();
	m_dwDeadMotionTime = long(0);
	m_dwDashTime = long(0);
	m_dwDashCoolTime = long(0);
	m_dwDownTime = long(0);

	m_pFrameKey = L"Player_RIGHT";

	m_pScene = CSceneMgr::Get_Instance()->Get_Scene();
}

int CPlayer::Update(void)
{
	if (m_bDead || !m_iHp)
	{
		if (m_dwDeadMotionTime == 0)
			m_dwDeadMotionTime = GetTickCount();
		m_bDead = true;
		m_eCurState = DEAD;

		if(GetTickCount() - m_dwDeadMotionTime > 2000)
			return OBJ_DEAD;
		
		return OBJ_NOEVENT;
	}

	// 중력 적용
	if (!m_bJump && m_tInfo.fY < m_fYStd - m_tInfo.fCY * 0.5f)
	{
		m_tInfo.fY += 10.f;
	}

	// Y기준선보다 떨어지지 않게 적용
	//if (m_tInfo.fY > m_fYStd - m_tInfo.fCY * 0.5f /*&& CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY)*/)
	//	m_tInfo.fY = m_fYStd - m_tInfo.fCY * 0.5f;
	if (m_tInfo.fY > m_fYStd - m_tInfo.fCY * 0.5f)
		m_tInfo.fY = m_fYStd - m_tInfo.fCY * 0.5f;

	// 떨어졌을때 죽음
	if (m_tInfo.fY > 650.f)
	{
		Set_Damage(1);
		m_bfall = true;
	}

	Key_Input();
	Jumping();
	Dash();
	Hitted();

	//튜토리얼, 런앤건 일때만 스크롤 오프셋 적용
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_TUTORIAL || CSceneMgr::Get_Instance()->Get_SceneID() == SC_RUN)
	{
		OffSet();
		if (m_tInfo.fX > 14890.f)
		{
			m_tInfo.fX += 3.f;
			m_eCurState = RUN;
		}
	}
	
	//렉트 설정
	Update_Rect();		
	Update_InfoCollision();

	// 상태에 따라 충돌 렉트 별도 설정
	if(DOWN_ATTACK == m_eCurState || DOWN == m_eCurState)
		Update_RectCollision(40.f, 100.f, 40.f, 10.f);		
	else if (JUMP == m_eCurState)
		Update_RectCollision(40.f, 50.f, 40.f, 50.f);
	else
		Update_RectCollision(40.f, 50.f, 40.f, 10.f);		

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	// 이전 Y값 저장
	m_fYBefore = m_tInfo.fY;
	m_fYStdBefore = m_fYStd;
	m_pFrameKeyBefore = m_pFrameKey;
	Motion_Change();
	Move_Frame();


	if (m_bSuperMode)
		m_bSuper = true;

}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left + iScrollX),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top + iScrollY),
		int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(m_tInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,								// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상
	
	//Rectangle(hDC, (int)m_tRectCollision.left + iScrollX, (int)m_tRectCollision.top, (int)m_tRectCollision.right + iScrollX, (int)m_tRectCollision.bottom);
	//Rectangle(hDC, (int)m_tInfoCollision.fX - m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY - m_tInfoCollision.fCY * 0.5 + iScrollY, (int)m_tInfoCollision.fX + m_tInfoCollision.fCX * 0.5 + iScrollX, (int)m_tInfoCollision.fY + m_tInfoCollision.fCY * 0.5 + iScrollY);
	//Rectangle(hDC, (int)m_tInfo.fX - m_tInfo.fCX * 0.5 + iScrollX, (int)m_tInfo.fY - m_tInfo.fCY * 0.5 + iScrollY, (int)m_tInfo.fX + m_tInfo.fCX * 0.5 + iScrollX, (int)m_tInfo.fY + m_tInfo.fCY * 0.5 + iScrollY);
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;
	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT) && !m_bHit)		// Hit 당했을 때, 부동 처리
	{
		if (!m_bDash)
		{
			m_pFrameKey = L"Player_RIGHT";
		}
		
		if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY) && !m_bJump)
		{
			m_fYStd = fY - m_tInfo.fCY * 0.5;
		}

		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			m_fJumpPower = 16.f;
			CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_jump_01.wav", SOUND_PLAYER, g_fSound_PLAYER);
			JumpSetting();
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			m_eCurState = RUN_ATTACK;
			m_tInfo.fX += m_fSpeed;
			Insert_Bullet(m_tInfo.fX + 70.f, m_tInfo.fY + 10.f, 0.f);	
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
		{
			if (!m_dwDashCoolTime)
			{
				m_bDash = true;
				m_dwDashTime = GetTickCount();
				m_eCurState = DASH;
				m_tInfo.fCX = 350.f;
				m_bDashLeftRight = false;
				m_dwDashCoolTime = GetTickCount();
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			if (CLineMgr::Get_Instance()->Collision_LineDown(m_tInfo.fX, m_tInfo.fY, &fY))
				m_fYStd = fY - m_tInfo.fCY * 0.5;
			m_eCurState = DOWN;
		}
		else
		{
			if (!m_bDash)
			{
				m_eCurState = RUN;
				m_pFrameKey = L"Player_RIGHT";
				m_tInfo.fCX = 140.f;
			}
			m_tInfo.fX += m_fSpeed;

			if (GetTickCount() - m_dwDustTime > 500 && !m_bJump)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectPlayerDust>::Create(m_tInfo.fX - (rand() % 3 * 40), m_tInfo.fY + 20, rand() % 6));
				m_dwDustTime = GetTickCount();
			}
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT) && !m_bHit)
	{
		if (!m_bDash)
		{
			m_pFrameKey = L"Player_LEFT";
		}

		if (CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY) && !m_bJump)
			m_fYStd = fY - m_tInfo.fCY * 0.5;


		if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			m_fJumpPower = 16.f;
			CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_jump_01.wav", SOUND_PLAYER, g_fSound_PLAYER);
			JumpSetting();
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			m_eCurState = RUN_ATTACK;
			m_tInfo.fX -= m_fSpeed;
			Insert_Bullet(m_tInfo.fX + 70.f, m_tInfo.fY - 10.f, 180.f);

		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_SHIFT))
		{
			if (!m_dwDashCoolTime)
			{
				m_bDash = true;
				m_dwDashTime = GetTickCount();
				m_eCurState = DASH;
				m_tInfo.fCX = 350.f;
				m_bDashLeftRight = true;
				m_dwDashCoolTime = GetTickCount();
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			if (CLineMgr::Get_Instance()->Collision_LineDown(m_tInfo.fX, m_tInfo.fY, &fY))
				m_fYStd = fY - m_tInfo.fCY * 0.5;
			m_eCurState = DOWN;
		}
		else
		{
			if (!m_bDash)
			{
				m_eCurState = RUN;
				m_pFrameKey = L"Player_LEFT";
				m_tInfo.fCX = 140.f;
			}
			m_tInfo.fX -= m_fSpeed;

			if (GetTickCount() - m_dwDustTime > 500 && !m_bJump)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectPlayerDust>::Create(m_tInfo.fX - (rand() % 3 * 40), m_tInfo.fY + 20, rand() % 6));
				m_dwDustTime = GetTickCount();
			}
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN) && !m_bHit)
	{
		if (CLineMgr::Get_Instance()->Collision_LineDown(m_tInfo.fX, m_tInfo.fY, &fY))
			m_fYStd = fY - m_tInfo.fCY * 0.5;

		if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			//if(!m_dwDownTime)
				m_eCurState = DOWN_ATTACK;

			if (L"Player_RIGHT" == m_pFrameKey)
				Insert_Bullet(m_tInfo.fX + 70.f, m_tInfo.fY + 20.f, 0.f);
			else if (L"Player_LEFT" == m_pFrameKey)
				Insert_Bullet(m_tInfo.fX - 70.f, m_tInfo.fY + 20.f, 180.f);
		}
		//else if (CKeyMgr::Get_Instance()->Key_Down('Z'))k
		//{
		//	if (!m_dwDownTime)
		//		m_dwDownTime = GetTickCount();
		//}
		else
		{
			//if (GetTickCount() - m_dwDownTime < 1000)
			//{
			//	m_eCurState = JUMP;
			//	m_tInfo.fY += 130.f;
			//	//m_fYStd += 100.f;
			//}
			//else
			//	m_dwDownTime = long(0);

			//if (!m_dwDownTime)
				m_eCurState = DOWN;
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP) && !m_bHit)
	{
		if (CLineMgr::Get_Instance()->Collision_LineDown(m_tInfo.fX, m_tInfo.fY, &fY))
			m_fYStd = fY - m_tInfo.fCY * 0.5;

		if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
		{
			m_eCurState = UP_ATTACK;
			Insert_Bullet(m_tInfo.fX + 40.f, m_tInfo.fY - 30.f, 90.f);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		{
			JumpSetting();
			CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_jump_01.wav", SOUND_PLAYER, g_fSound_PLAYER);
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('Z') && !m_bHit)
	{
		JumpSetting();
		CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_jump_01.wav", SOUND_PLAYER, g_fSound_PLAYER);
		CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CEffectPlayerDust>::Create(m_tInfo.fX, m_tInfo.fY + 20, rand() % 6));

		if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
			m_tInfo.fX -= m_fSpeed;
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
			m_tInfo.fX += m_fSpeed;
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing('X') && !m_bHit)
	{
		m_eCurState = ATTACK;

		if(L"Player_RIGHT" == m_pFrameKey)
			Insert_Bullet(m_tInfo.fX + 70.f, m_tInfo.fY + 10.f, 0.f);
		else if (L"Player_LEFT" == m_pFrameKey)
			Insert_Bullet(m_tInfo.fX - 70.f, m_tInfo.fY + 10.f, 180.f);

	}
	// 무기 변경
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_CONTROL))
	{
		++m_iGun;
		if (m_iGun == GUN_END)
			m_iGun = 0;
	}
	// 임시
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SHIFT)) 
	{
		m_fSpeed = 30.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_bSuperMode = true;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		m_bSuperMode = false;
	}
	// 아무것도 안눌렀을 떄 원상 복구
	else
	{
		if (m_pFrameKeyBefore == L"Player_LEFT" || m_pFrameKeyBefore == L"Player_DASH_LEFT")
			m_pFrameKey = L"Player_LEFT";
		else
			m_pFrameKey = L"Player_RIGHT";
		
		m_tInfo.fCX = 140.f;
		m_eCurState = IDLE;
		m_fSpeed = 7.f;
		m_fJumpPower = 17.f;
	}
}

void CPlayer::Jumping(void)
{
	float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);


	if (m_bJump)
	{
		m_tInfo.fY -= m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		
		if (!m_bDash)
		{
			m_fJumpTime += 0.2f;
			m_eCurState = JUMP;
			m_tInfo.fCX = 140.f;
		}


		CCollisionMgr::Collision_RectExParry(CObjMgr::Get_Instance()->Get_ParryList(), this);
		
		if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_RUN)
			CCollisionMgr::Collision_RectExTram(CObjMgr::Get_Instance()->Get_Tram(), this);

		Parring();

		if (m_fJumpTime > 4.3f)
		{
			bool bLineCol2 = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

			if (bLineCol2 && (fY < m_tInfo.fY + m_tInfo.fCY * 0.5))
			{
				m_bJump = false;
				m_bJumpBefore = false;
				m_fJumpTime = 0.f;
				m_fYStd = fY;
				m_bParry = false;
				m_bJumpParring = false;
				m_eCurState = IDLE;
				m_tInfo.fCX = 140.f;
			}
		}
	}
	else if (bLineCol)
	{
		m_fYStd = fY - 5;
	}
}

void CPlayer::Dash(void)
{
	if (m_bDash && !m_bDashLeftRight && !m_bHit)
	{
		m_pFrameKey = L"Player_DASH_RIGHT";
		m_tInfo.fX += 7.f;
		m_tInfo.fY = m_fYBefore;

		m_tRectCollision.left = (long)(m_tRect.left + 40);
		m_tRectCollision.top = (long)(m_tRect.top + 50);
		m_tRectCollision.right = (long)(m_tRect.right - 40);
		m_tRectCollision.bottom = (long)(m_tRect.bottom - 10);

		if (GetTickCount() - m_dwDashTime > 300)
		{
			m_bDash = false;
			m_tInfo.fCX = 140.f;
			//m_pFrameKey = L"Player_RIGHT";
			//m_eCurState = IDLE;
		}
	}
	else if (m_bDash && m_bDashLeftRight && !m_bHit)
	{
		m_pFrameKey = L"Player_DASH_LEFT";
		m_tInfo.fX -= 7.f;
		m_tInfo.fY = m_fYBefore;

		m_tRectCollision.left = (long)(m_tRect.left + 40);
		m_tRectCollision.top = (long)(m_tRect.top + 50);
		m_tRectCollision.right = (long)(m_tRect.right - 40);
		m_tRectCollision.bottom = (long)(m_tRect.bottom - 10);

		if (GetTickCount() - m_dwDashTime > 300)
		{
			m_bDash = false;
			m_tInfo.fCX = 140.f;
			//m_pFrameKey = L"Player_LEFT";
			//m_eCurState = IDLE;
		}
	}

	if (GetTickCount() - m_dwDashCoolTime > 800)
		m_dwDashCoolTime = long(0);
}

void CPlayer::Hitted(void)
{
	if (m_bHit)
	{		
		m_eCurState = HIT;
		m_pFrameKey = L"Player_RIGHT";
		m_tInfo.fCX = 140.f;

		if (1000 < GetTickCount() - m_dwHitSoundTime)
		{
			if(!m_bfall)
				CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_hit_01.wav", SOUND_PLAYER, g_fSound_PLAYER);
			m_dwHitSoundTime = GetTickCount();
		}

		// Hit 스프라이트 해제
		if (1000 < GetTickCount() - m_dwHitCoolTime && 2000 > GetTickCount() - m_dwHitCoolTime)
		{
			m_eCurState = IDLE;
			if (m_bfall)
			{
				m_tInfo.fY = 10.f;
				m_tInfo.fX -= 200.f;
			}
			
			m_bHit = false;
			m_bfall = false;
		}
	}

	if(m_bSuper)
	{
		// 무적모드 해제
		if (2000 < GetTickCount() - m_dwHitCoolTime)
		{
			m_bSuper = false;
			m_dwHitCoolTime = GetTickCount();
		}
	}
}

void CPlayer::Parring(void)
{
	/*float		fY = 0.f;
	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);
*/
	if (m_bParry)
	{
		if (m_bParryMotion && !m_bDash)
		{
			m_eCurState = PARRY;
		}
		else if (!m_bDash)
		{
			m_eCurState = JUMP;
			m_fJumpPower = 18.f;
		}

		if (!m_bJumpParring)
		{
			m_fJumpTime = 0.f;
			m_bJumpParring = true;
			m_bJump = true;
			m_bJumpBefore = true;
		}
		/*m_tInfo.fY -= m_fJumpPower* 0.7 * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f;
		m_fJumpTime += 0.2f;*/

		//패링점프하다가 Y선가면 고정
		//if (bLineCol && (fY < m_tInfo.fY + m_tInfo.fCY * 0.5))
		//{
		//	//m_bParry = false;
		//	m_bJump = false;
		//	m_bJumpBefore = false;
		//	m_fJumpTime = 0.f;
		//	m_fYStd = fY;
		//}

		//if (1000 < GetTickCount() - m_dwParryTime)
		//{
		//	/*m_eCurState = IDLE;*/
		//	//m_bParry = false;
		//	//m_bHit = false;
		//	m_dwParryTime = GetTickCount();
		//}
	}
}

//template<typename T>
//CObj* CPlayer::Create_Bullet(void)
//{
//	CObj*		pBullet = CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);
//
//	return pBullet;
//}
//
//CObj* CPlayer::Create_Shield(void)
//{
//	CObj*		pShield = CAbstractFactory<CShield>::Create();
//	pShield->Set_Target(this);
//
//	return pShield;
//}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN_ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 40;
			m_tFrame.dwTime = GetTickCount();
			break;
			
		case JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 5;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 3;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DOWN_ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case UP_ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 7;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DASH:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 30;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 6;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 8;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		case PARRY:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.iMotion = 10;
			m_tFrame.dwSpeed = 30;
			m_tFrame.dwTime = GetTickCount();
			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iMotion = 9;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPlayer::Update_InfoCollision()
{
	m_tInfoCollision.fX = m_tInfo.fX;
	m_tInfoCollision.fY = m_tInfo.fY;
	m_tInfoCollision.fCX = m_tInfo.fCX * 0.7f;
	m_tInfoCollision.fCY = m_tInfo.fCY;
}

void CPlayer::Insert_Bullet(float _fX, float _fY, float _angle)
{
	switch (m_iGun)
	{
	case GUN_TOY:
		if (m_dwBulletCoolTime + 120.f < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_weapon_arc_fire_01.wav", SOUND_PLAYER, g_fSound_PLAYER);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(_fX, _fY, _angle));
			m_dwBulletCoolTime = GetTickCount();
		}
		break;
	case GUN_MISSILE:
		if (m_dwBulletCoolTime + 150.f < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_weapon_wideshot_fire_start_001.wav", SOUND_PLAYER, g_fSound_PLAYER);
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CGuideBullet>::Create(_fX, _fY, _angle));
			dynamic_cast<CGuideBullet*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_BULLET))->Set_PlayerFrameKey(m_pFrameKey);
			m_dwBulletCoolTime = GetTickCount();
		}
		break;
	}
}

void CPlayer::JumpSetting(void)
{
	m_eCurState = JUMP;

	if (!m_bJump)	// 첫 점프 시
	{
		m_bJump = true;
	}
	else if (m_bJump && !m_bJumpBefore)	// 두번째 점프 시
	{
		m_fJumpTime = 0.f;
		m_bJumpBefore = true;
	}
	return;
}

void CPlayer::ParrySetting(bool _bParryMontion)
{
	if (!m_bParry)
	{
		m_bParry = true;
		m_bSuper = true;
		m_bJumpParring = false;
		m_bParryKill = false;
		//m_eCurState = PARRY;
		m_pScene->Set_Gage(10);
		m_bParryMotion = _bParryMontion;
	}
}

void CPlayer::OffSet()
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 10;
	int		iItvY = 10;

	if (iOffSetX - iItvX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX + iItvX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffSetY - iItvY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetY + iItvY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

	//if (m_tInfo.fX > 10434)
	if(CScrollMgr::Get_Instance()->Get_ScrollY() > 441.f || m_tInfo.fX > 10434)
		CScrollMgr::Get_Instance()->Set_ScrollYLock(441.f);
}

void CPlayer::Move_Rock()
{
	if (m_tInfo.fX - m_tInfo.fCX * 0.5 < 50)
		m_tInfo.fX = 50.f;
	if (m_tInfo.fY - m_tInfo.fCY * 0.5 < 50)
		m_tInfo.fY = 50.f;
}

void CPlayer::Set_Jump_Stop()
{
	m_bJump = false;
	m_bJumpBefore = false;
	m_fJumpTime = 0.f;
	
	m_bParry = false;
	m_bJumpParring = false;
	m_eCurState = IDLE;
}
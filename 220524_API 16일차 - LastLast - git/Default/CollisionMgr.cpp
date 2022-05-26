#include "stdafx.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "Tile.h"
#include "PlayerWorld.h"
#include "Player.h"
#include "MonsterTrampoline.h"


DWORD CCollisionMgr::m_dwCollisionCoolTime = 0;
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

// 플레이어 - 몬스터 데미지
void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	//if (0 == m_dwCollisionCoolTime)
	//	m_dwCollisionCoolTime = GetTickCount();

	//if (GetTickCount() - m_dwCollisionCoolTime > 100 )
	//{
		RECT		rc{};

		for (auto& Dest : _Dest)
		{
			for (auto& Sour : _Sour)
			{
				if (Sour->Get_Dead() == true)
					continue;

				if (IntersectRect(&rc, &(Dest->Get_RectCollision()), &(Sour->Get_RectCollision())))
				{
					if ((Dest->Get_Tag() == TAG_PLAYER) && !Dest->Get_bSuper() && !Dest->Get_Parry() && (Sour->Get_Tag() != TAG_ITEM))	//충돌한게 플레이어고, 피격상태 + 무적모드 + 아이템  아닐 때만
					{
						// 충돌체와 위치비교하여 밀려나게
						if (Dest->Get_Info().fX < Sour->Get_Info().fX)	
							Dest->Set_PosX(-30.f);
						else
							Dest->Set_PosX(30.f);
					}

					if (Sour->Get_Tag() == TAG_ITEM)	// 아이템이면 체력 1만 깎고, 코인
					{
						Sour->Set_Damage(1);
						++g_iCoin;
						CSoundMgr::Get_Instance()->PlaySound(L"Run_sfx_coin_pickup_03.wav", SOUND_EFFECT, g_fSound_EFFECT);
					}
					else  // 아이템 아니면 공격력대로 체력 깎음
					{
						Sour->Set_Damage(Dest->Get_Attack());
						Dest->Set_Damage(Sour->Get_Attack()); // 플레이어 체력 깎음
					}
						
				}
			}
		}	
		/*m_dwCollisionCoolTime = GetTickCount();
	}*/
}

////패리 테스트
//void CCollisionMgr::Collision_RectParry(list<CObj*> _Dest, CObj* _Sour)
//{
//	RECT		rc{};
//
//	for (auto& Dest : _Dest)
//	{
//			if (IntersectRect(&rc, &(Dest->Get_RectCollision()), &(_Sour->Get_RectCollision())))
//			{
//				//if (Dest->Get_Tag() == TAG_PLAYER && !Dest->Get_bSuper())	//충돌한게 플레이어고, 무적모드 아닐 때만
//				//{
//					//if (Dest->Get_Info().fX < _Sour->Get_Info().fX)	//충돌체와 위치비교하여 밀려나게
//					//	Dest->Set_PosX(-30.f);
//					//else
//					//	Dest->Set_PosX(30.f);
//				//}
//				//if (Dest->Get_Info().fX > _Sour->Get_Info().fX)	//충돌체와 위치비교하여 밀려나게
//				//{
//					dynamic_cast<CPlayer*>(_Sour)->ParrySetting();
//				//}
//			}
//	}
//}

//현재 안씀 - 원본							// 고정되어 있는 물체  // 움직이는 물체		
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY > Sour->Get_Info().fY)
						Sour->Set_PosY(-fY);
						//Sour->Set_PosYBefore(/*Sour->Get_YBefore()*/);
					
					else // 하 충돌
						Sour->Set_PosY(fY);
						//Sour->Set_PosYBefore(/*Sour->Get_YBefore()*/);

				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						Sour->Set_PosX(-fX);

					// 우 충돌
					else
						Sour->Set_PosX(fX);
				}
			}
		}
	}
}


//튜토리얼 / Run Object 좌우 충돌용
								// 고정되어 있는 물체  // 움직이는 물체	(플레이어)	
void CCollisionMgr::Collision_RectExInfoCollision(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		if (Dest->Get_bCollision() == false)
			continue;

		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			//충돌했다면,
			if (Check_RectInfoCollision(Dest, Sour, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					//// 상 충돌
					//if (Dest->Get_Info().fY > Sour->Get_Info().fY)
					//{
					//	//Sour->Set_PosY(-fY);
					//	dynamic_cast<CPlayer*>(Sour)->Set_fStdY(Dest->Get_Rect().top);
					//	dynamic_cast<CPlayer*>(Sour)->Set_Jump_Stop();
					//}

					////else // 하 충돌
					////	Sour->Set_PosY(fY);

					//// 상 충돌
					//if (Dest->Get_Info().fY > Sour->Get_Info().fY)
					//{
					//	//Sour->Set_PosY(-fY);
					//	//Sour->Set_PosYBefore(/*Sour->Get_YBefore()*/);
					//	dynamic_cast<CPlayer*>(Sour)->Set_fStdY(Sour->Get_YBefore());
					//}
					//	

					//else // 하 충돌
					//	 //Sour->Set_PosY(fY);
					//	Sour->Set_PosYBefore(/*Sour->Get_YBefore()*/);

				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						Sour->Set_PosX(-fX);

					// 우 충돌
					else
						Sour->Set_PosX(fX);
				}
			}
		}
	}
}

//월드 타일 충돌
//Dest : World Tile , Sour : Player
void CCollisionMgr::Collision_RectExVec(vector<CObj*> _Dest, CObj* _Sour)
{
	for (auto& Dest : _Dest)
	{
	/*	for (auto& Sour : _Sour)
		{*/
		if (0 == dynamic_cast<CTile*>(Dest)->Get_DrawID())
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_RectWorld(Dest, _Sour, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_Info().fY > dynamic_cast<CPlayerWorld*>(_Sour)->Get_InfoCollision().fY)
						_Sour->Set_PosY(-fY);

					else // 하 충돌
						_Sour->Set_PosY(fY);

				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_Info().fX > _Sour->Get_Info().fX)
						_Sour->Set_PosX(-fX);

					// 우 충돌
					else
						_Sour->Set_PosX(fX);
				}
			}
		}	
		//}
	}
}

// 패리 충돌
void CCollisionMgr::Collision_RectExParry(list<CObj*> _Dest, CObj* _Sour)
{
	for (auto& Dest : _Dest)
	{
		if (Dest->Get_Tag() == TAG_TRAMPOLIN)
			continue;

		float	fX = 0.f, fY = 0.f;

		if (Check_Rect(Dest, _Sour, &fX, &fY))
		{
			// 상하 충돌
			if (fX > fY)
			{
				// 상 충돌
				if (Dest->Get_Info().fY > _Sour->Get_Info().fY)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"Player_sfx_player_parry_slap_01.wav", SOUND_PLAYER, g_fSound_PLAYER);

					dynamic_cast<CPlayer*>(_Sour)->ParrySetting(true);

					if (dynamic_cast<CPlayer*>(_Sour)->Get_ParryKill() == false)
					{
						Dest->Set_Dead();
						dynamic_cast<CPlayer*>(_Sour)->Set_ParryKill(true);
					}

				}
			}
		}
	}
}

// 트램 충돌
void CCollisionMgr::Collision_RectExTram(CObj* _Dest, CObj* _Sour)
{
	float	fX = 0.f, fY = 0.f;

	if (Check_RectTram(_Dest, _Sour, &fX, &fY))
	{
		// 상하 충돌
		if (fX > fY)
		{
			// 상 충돌
			if (_Dest->Get_Info().fY > _Sour->Get_Info().fY)
			{
				dynamic_cast<CPlayer*>(_Sour)->ParrySetting(false);
				dynamic_cast<CMonsterTrampoline*>(_Dest)->Set_bJump(true);
			}
		}
	}
}



bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float		fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f * 0.7f;
	float		fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f * 0.7f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}
	
	return false;
}

bool CCollisionMgr::Check_RectTram(CObj* pDest, CObj* pSour, float *pX, float* pY)
{
	float		fWidth = abs(pDest->Get_InfoCollision().fX - pSour->Get_InfoCollision().fX);
	float		fHeight = abs(pDest->Get_InfoCollision().fY - pSour->Get_InfoCollision().fY);

	float		fCX = (pDest->Get_InfoCollision().fCX + pSour->Get_InfoCollision().fCX) * 0.5f * 0.7f;
	float		fCY = (pDest->Get_InfoCollision().fCY + pSour->Get_InfoCollision().fCY) * 0.5f * 0.7f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

//bool CCollisionMgr::Check_RectParry(CObj* pDest, CObj* pSour, float *pX, float* pY)
//{
//	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX);
//	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY);
//
//	float		fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
//	float		fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;
//
//	if ((fCX > fWidth) && (fCY > fHeight))
//	{
//		*pX = fCX - fWidth;
//		*pY = fCY - fHeight;
//
//		return true;
//	}
//
//	return false;
//}

// World용 충돌 (InfoCollision으로 충돌)
bool CCollisionMgr::Check_RectWorld(CObj * pDest, CObj * pSour, float * pX, float * pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSour->Get_InfoCollision().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSour->Get_InfoCollision().fY);

	float		fCX = (pDest->Get_Info().fCX + pSour->Get_InfoCollision().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSour->Get_InfoCollision().fCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}
	return false;
}

//tutorial, Run - InfoCollision 충돌
bool CCollisionMgr::Check_RectInfoCollision(CObj * pDest, CObj * pSour, float * pX, float * pY)
{
	float		fWidth = abs(pDest->Get_InfoCollision().fX - pSour->Get_InfoCollision().fX);
	float		fHeight = abs(pDest->Get_InfoCollision().fY - pSour->Get_InfoCollision().fY);

	float		fCX = (pDest->Get_InfoCollision().fCX + pSour->Get_InfoCollision().fCX) * 0.5f;
	float		fCY = (pDest->Get_InfoCollision().fCY + pSour->Get_InfoCollision().fCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}
	return false;
}

//bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
//{
//	
//	// abs : 절대값을 구해주는 함수
//	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
//	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);
//
//	// sqrt : 루트를 씌워주는 함수
//	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
//
//	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
//
//	return fRadius > fDiagonal;
//}
//
//void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
//{
//
//	for (auto& Dest : _Dest)
//	{
//		for (auto& Sour : _Sour)
//		{
//			if (Check_Sphere(Dest, Sour))
//			{
//				Dest->Set_Dead();
//				Sour->Set_Dead();
//			}
//		}
//	}
//}

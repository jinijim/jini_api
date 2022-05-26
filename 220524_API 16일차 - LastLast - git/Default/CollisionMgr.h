#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool		Check_Sphere(CObj* pDest, CObj* pSour);
	static bool		Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY);
	static bool		Check_RectTram(CObj* pDest, CObj* pSour, float *pX, float* pY);

	//static bool	Check_RectParry(CObj* pDest, CObj* pSour, float *pX, float* pY);
	static bool		Check_RectWorld(CObj* pDest, CObj* pSour, float *pX, float* pY);
	static bool		Check_RectInfoCollision(CObj* pDest, CObj* pSour, float *pX, float* pY);


	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_RectExInfoCollision(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_RectExVec(vector<CObj*> _Dest, CObj* _Sour);
	static void		Collision_RectExParry(list<CObj*> _Dest, CObj* _Sour);
	static void		Collision_RectExTram(CObj* _Dest, CObj* _Sour);
	static void		Collision_RectParry(list<CObj*> _Dest, CObj* _Sour);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);

private :
	static DWORD	m_dwCollisionCoolTime;
};


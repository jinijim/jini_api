#pragma once

#define		WINCX		800
#define		WINCY		600

#define		PI			3.141592f

#define		PURE		= 0

#define		OBJ_NOEVENT  0
#define		OBJ_DEAD	 1

#define		VK_MAX		 0xff

#define		TILECX		32
#define		TILECY		32

#define		TILEX		60
#define		TILEY		40

#define		TILEXSCROLL		25
#define		TILEYSCROLL		19



extern HWND		g_hWnd;
extern float	g_fWorldPlayerX;
extern float	g_fWorldPlayerY;
extern int		g_iCoin;
extern float	g_fSound_BG;
extern float	g_fSound_PLAYER;
extern float	g_fSound_EFFECT;
extern float	g_fSound_MONSTER;
extern bool     g_bNpcCoinGet;
extern int		g_iHp;

extern int		g_iClearIndex;

extern bool		g_iItemSale1;
extern bool		g_iItemSale2;
extern bool		g_iItemSale3;

//extern bool		g_bGunGet;
//extern bool		g_bGuideGunGet;
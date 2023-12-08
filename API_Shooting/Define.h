#pragma once

#define         WINCX      800
#define         WINCY      600

#define         ScreenSize_minX 0
#define         ScreenSize_minY 0
#define         ScreenSize_maxX WINCX
#define         ScreenSize_maxY WINCY

#define         PURE      = 0

#define         OBJ_NOEVENT      0
#define         OBJ_DEAD      1
#define         OBJ_DELETE      2
#define         PI         3.141592f
#define         RADIAN        PI/180
extern         HWND      g_hWnd;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX;
	float fCY;

}INFO;

enum DIRECTION
{
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_END
};

enum OBJID
{
	PLAYER,
	BULLET,
	MONSTER,
	PET,
	MOUSE,
	ITEM,
	SHIELD,
	BOMB,
	PARTICLE,
	ENEMYBULLET,
	OBJ_END
};

enum BULLETID
{
	BULLET_NONE,
	BULLET_PIERCE,
	BULLET_CHASE,

	BULLET_TARGET,
	BULLET_BOSS,
	BULLET_END
};

enum ITEMID
{
	ITEM_NONE1,
	ITEM_NONE2,
	ITEM_NONE3,
	ITEM_POWER,
	ITEM_HP,
	ITEM_BOMB,
	ITEM_BULLET,
	ITEM_END
};

enum MONSTERID
{
	MONSTER_BOSS,
	MONSTER_NORMAL,
	MONSTER_BULLET,
	MONSTER_END
};

enum PATTERNID
{
	PATTERN_NONE,
	PATTERN_A,
	PATTERN_B,
	PATTERN_C,
	PATTERN_D,
	PATTERN_E,
	PATTERN_F,
	PATTERN_G,
	PATTERN_BOSS,
	PATTERN_REST,
	PATTERN_END
};

enum PLAYERSTATE
{
	PLAYER_NONE,
	PLAYER_INVI,
	PLAYER_END
};

enum UIID
{
	UI_TREE,
	UI_BOMBBOX,
	UI_BOSSHPBAR,
	UI_BULLETPOWERBOX,
	UI_BULLETTYPEBOX,
	UI_HPBOX,
	UI_SCOREBOX,
	UI_ENDSCREEN,
	UI_END
};

//Ãß°¡
enum BGID
{
	BG_STAR,
	BG_BUILDING,
	BG_TREE,
	BG_END
};
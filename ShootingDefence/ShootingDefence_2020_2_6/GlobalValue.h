#pragma once

enum CT_Type   //CharicType
{
	CT_None = 0,
	CT_Nanami,
	CT_Zombi1,
	CT_Zombi2,
	CT_Zombi3,
	CT_Zombi4,
	CT_Zombi6,
	CT_Zombi8,
	CT_Boss,
	CTT_Length,
};

enum AniState
{
	AS_None,
	Idle,
	Front_Walk,
	Back_Walk,
	Left_Walk,
	Right_Walk,
	AniLength,
};

enum GameState
{
	GAME_READY = 0,
	GAME_START,
	NEXT_LEVEL,
	GAME_OVER,
};

extern GameState g_GameState;

extern int  g_TimeOut;
extern int  g_DiffLevel;    //≥≠¿Ãµµ
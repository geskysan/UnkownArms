//=============================================================================
//
// マップ処理 [map.h]
// Author : 小川 朔哉
//
//=============================================================================
#pragma once
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJ		128		// 最大オブジェクト数
#define MAP_SPLIT	3		// マップの分割数
#define BYTE		256		// 最大バイト数

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef enum
{
	OBJ_NONE,
	OBJ_BLOCK,
	OBJ_PLAYER,
	OBJ_MAX

}OBJ_TYPE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);
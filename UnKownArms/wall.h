//=============================================================================
//
// 壁処理 [wall.h]
// Author : 小川 朔哉
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

#define MAX_WALL	128

typedef struct
{
	D3DXVECTOR3 pos;		//地面の位置
	D3DXVECTOR3 rot;		//地面の回転
	D3DXVECTOR3 scl;		//地面の大きさ
	D3DXMATRIX g_mtxWorld;	//地面のワールドマトリックス
	int			iKind;		//種類
	bool		bUse;		//使用フラグ

}MESH_WALL;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void CreateWall(D3DXVECTOR3 pos, int iKind);
#endif //_FIELD_H_
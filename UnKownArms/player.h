//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 小川 朔哉
//
//=============================================================================
#pragma once
#include "main.h"
#include "mode.h"

//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define MAX_PARTS		10

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct {
	D3DXVECTOR3			pos;
	D3DXVECTOR3			rot;
	D3DXVECTOR3			scl;
	D3DXVECTOR3			move;
	D3DXVECTOR3			rotDest;
	D3DXMATRIX			mtxWorld;		//ワールドマトリックス
	bool				bUse;
	int					IdxShadow;
	MODEL				aModel[MAX_PARTS];

}PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void CreatePlayer(D3DXVECTOR3 pos);
PLAYER GetPlayer(void);
void SetPosition(D3DXVECTOR3 pos);
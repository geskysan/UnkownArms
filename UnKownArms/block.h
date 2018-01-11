//=============================================================================
//
// ブロック処理 [block.h]
// Author : 小川 朔哉
//
//=============================================================================
#pragma once
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BLOCK	514

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	D3DXMATRIX mtxWorld;
	bool bUse;
	int ikind;
}BLOCK;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void CreateBlock(D3DXVECTOR3 pos, int iKind);
void MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice);
BLOCK GetBlock(void);
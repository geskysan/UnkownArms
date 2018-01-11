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
}BLOCK_TOP;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBlockTop(void);
void UninitBlockTop(void);
void UpdateBlockTop(void);
void DrawBlockTop(void);
void CreateBlockTop(D3DXVECTOR3 pos, int iKind);
void MakeVertexBlockTop(LPDIRECT3DDEVICE9 pDevice);
BLOCK_TOP GetBlockTop(void);
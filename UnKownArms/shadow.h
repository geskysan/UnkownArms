//=============================================================================
//
// 影の処理 [shadow.h]
// Author : 小川 朔哉
//
//=============================================================================
#pragma once

#include "main.h"

#define MAX_SHADOW	128

//*****************************************************************************
// 構造体
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	bool bUse;
}Shadow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 scl);
void SetPositionShadow(D3DXVECTOR3 pos, D3DXVECTOR3 scl,int IdxShadow);
//=============================================================================
//
// �^�C�g����ʔw�i���� [titleback.h]
// Author : ���� ���
//
//=============================================================================
#pragma once
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
}Titleback;

void InitTitleback(void);
void UninitTitleback(void);
void UpdateTitleback(void);
void DrawTitleback(void);
void MakeVertexTitleback(LPDIRECT3DDEVICE9 pDevice);
//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���� ���
//
//=============================================================================
#pragma once
#include "main.h"
#include "mode.h"

//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define MAX_PARTS		10

//*****************************************************************************
// �\����
//*****************************************************************************
typedef struct {
	D3DXVECTOR3			pos;
	D3DXVECTOR3			rot;
	D3DXVECTOR3			scl;
	D3DXVECTOR3			move;
	D3DXVECTOR3			rotDest;
	D3DXMATRIX			mtxWorld;		//���[���h�}�g���b�N�X
	bool				bUse;
	int					IdxShadow;
	MODEL				aModel[MAX_PARTS];

}PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void CreatePlayer(D3DXVECTOR3 pos);
PLAYER GetPlayer(void);
void SetPosition(D3DXVECTOR3 pos);
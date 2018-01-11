//=============================================================================
//
// �Ǐ��� [wall.h]
// Author : ���� ���
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

#define MAX_WALL	128

typedef struct
{
	D3DXVECTOR3 pos;		//�n�ʂ̈ʒu
	D3DXVECTOR3 rot;		//�n�ʂ̉�]
	D3DXVECTOR3 scl;		//�n�ʂ̑傫��
	D3DXMATRIX g_mtxWorld;	//�n�ʂ̃��[���h�}�g���b�N�X
	int			iKind;		//���
	bool		bUse;		//�g�p�t���O

}MESH_WALL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void CreateWall(D3DXVECTOR3 pos, int iKind);
#endif //_FIELD_H_
//=============================================================================
//
// �}�b�v���� [map.cpp]
// Author : ���� ���
//
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "field.h"
#include "wall.h"
#include "block.h"
#include "blocktop.h"
#include "player.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJ_X 30
#define MAX_OBJ_Z 30

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
OBJ_TYPE g_Object;
int obj;
//=============================================================================
// ����������
//=============================================================================
void InitMap()
{
	InitField();
	InitBlock();
	InitBlockTop();

	// �t�@�C���\����
	FILE *fp;

	bool bMapFlag = false;
	int OBJ_SIZE_X = 50;
	int OBJ_SIZE_Z = 50;
	char line[BYTE];

	// �t�@�C�����w��
	char *fname = "data/MAP/map.csv";

	// �t�@�C���I�[�v��
	fp = fopen(fname, "r");

	if (!fp)
	{
		MessageBox(NULL, "�}�b�v�f�[�^��ǂݍ��߂܂���ł����B\n", NULL, MB_OK);
	}

	for (int nCntMap_Z = 0; nCntMap_Z < MAX_OBJ_Z; nCntMap_Z++)
	{
		for (int nCntMap_X = 0; nCntMap_X < MAX_OBJ_X; nCntMap_X++)
		{
			// �ǂݍ���
			fscanf(fp, "%d,", &g_Object);

			switch (g_Object)
			{
				 //��
			case OBJ_NONE:
				break;

				// �u���b�N
			case OBJ_BLOCK:
				CreateBlock(D3DXVECTOR3(-750 + OBJ_SIZE_X*nCntMap_X, 0, 750 + OBJ_SIZE_Z*-nCntMap_Z), 0);
				break;

			case OBJ_PLAYER:
				//CreatePlayer(D3DXVECTOR3(-750 + OBJ_SIZE_X*nCntMap_X, 20.f, 750 + OBJ_SIZE_Z*-nCntMap_Z));
				break;
			}
		}
	}

	fclose(fp);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMap()
{
	UninitField();
	UninitBlock();
	UninitBlockTop();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMap()
{
	UpdateField();
	//UpdateBlock();
	UpdateBlockTop();
	PrintDebug("%d\n", obj);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMap()
{
	DrawField();
	DrawBlock();
	DrawBlockTop();
}
//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author : ���� ���
//
//=============================================================================
#include "block.h"
#include "blocktop.h"
#include "player.h"
#include "collision.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_VERTEX	8
#define MAX_PRI		10
#define MAX_IDX		10

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureBlock = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffBlock = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
BLOCK g_Block[MAX_BLOCK];

//=============================================================================
// ����������
//=============================================================================
void InitBlock()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureBlock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++) {

		g_Block[nCntBlock].pos = vector3NS::ZERO;
		g_Block[nCntBlock].rot = vector3NS::ZERO;
		g_Block[nCntBlock].scl = vector3NS::ONE;
		g_Block[nCntBlock].bUse = false;
	}

	// ���_���̍쐬
	MakeVertexBlock(pDevice);
	//�C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * MAX_IDX * MAX_BLOCK, //�C���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffBlock,
		NULL);

	WORD *pIdx;
	g_pIdxBuffBlock->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 0;
	pIdx[1] = 4;
	pIdx[2] = 1;
	pIdx[3] = 5;
	pIdx[4] = 2;
	pIdx[5] = 6;
	pIdx[6] = 3;
	pIdx[7] = 7;
	pIdx[8] = 0;
	pIdx[9] = 4;

	g_pIdxBuffBlock->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitBlock()
{
		// �C���f�b�N�X�o�b�t�@�̉��
		if (g_pIdxBuffBlock)
		{
			g_pIdxBuffBlock->Release();
			g_pIdxBuffBlock = NULL;
		}

		// �e�N�X�`���̉��
		if (g_pTextureBlock)
		{
			g_pTextureBlock->Release();
			g_pTextureBlock = NULL;
		}
		// �o�b�t�@�̉��
		if (g_pVtxBuffBlock)
		{
			g_pVtxBuffBlock->Release();
			g_pVtxBuffBlock = NULL;
		}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock()
{
	PLAYER pPlayer;
	pPlayer = GetPlayer();
	D3DXVECTOR3 PastPos;
	D3DXVECTOR3 VecToPos;
	PastPos = pPlayer.pos;
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (CollisionRectangle(g_Block[nCntBlock].pos, pPlayer.pos) && g_Block[nCntBlock].bUse)
		{

			PrintDebug("������\n");
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock()
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++) {
		if (g_Block[nCntBlock].bUse)
		{
			D3DXMATRIX g_mtxScl;			//�X�P�[���}�g���b�N�X
			D3DXMATRIX g_mtxRot;			//��]�}�g���b�N�X
			D3DXMATRIX g_mtxTransForm;		//�ړ��}�g���b�N�X
			D3DMATERIAL9 matDef;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&g_mtxScl, g_Block[nCntBlock].scl.x, g_Block[nCntBlock].scl.y, g_Block[nCntBlock].scl.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &g_mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_Block[nCntBlock].rot.y, g_Block[nCntBlock].rot.x, g_Block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &g_mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&g_mtxTransForm, g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y, g_Block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &g_mtxTransForm);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlock].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_3D));
			pDevice->SetIndices(g_pIdxBuffBlock);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureBlock);
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				MAX_IDX,		// ���_��
				0,
				MAX_PRI);		// �v���~�e�B�u��(�|���S����)
		}
	}
}

//=============================================================================
// �u���b�N�̐����i �O�� �j
//=============================================================================
void CreateBlock(D3DXVECTOR3 pos, int ikind)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false) {
			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].ikind = ikind;
			g_Block[nCntBlock].bUse = true;

			// ��W�쐬
			CreateBlockTop(pos, ikind);
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock, NULL);

	VERTEX_3D *pVtx;

	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlockTop = 0; nCntBlockTop < MAX_BLOCK; nCntBlockTop++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE * 2, OBJ_SIZE);
		pVtx[1].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE * 2, OBJ_SIZE);
		pVtx[2].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE * 2, -OBJ_SIZE);
		pVtx[3].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE * 2, -OBJ_SIZE);
		pVtx[4].pos = D3DXVECTOR3(-OBJ_SIZE, 0.f, OBJ_SIZE);
		pVtx[5].pos = D3DXVECTOR3(OBJ_SIZE, 0.f, OBJ_SIZE);
		pVtx[6].pos = D3DXVECTOR3(OBJ_SIZE, 0.f, -OBJ_SIZE);
		pVtx[7].pos = D3DXVECTOR3(-OBJ_SIZE, 0.f, -OBJ_SIZE);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[1].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[2].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[3].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[4].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[5].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[6].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[7].nor = D3DXVECTOR3(0.f, 0.f, -1.f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(2, 0);
		pVtx[3].tex = D3DXVECTOR2(3, 0);
		pVtx[4].tex = D3DXVECTOR2(0, 1);
		pVtx[5].tex = D3DXVECTOR2(1, 1);
		pVtx[6].tex = D3DXVECTOR2(2, 1);
		pVtx[7].tex = D3DXVECTOR2(3, 1);

		pVtx +=8;
	}

	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̏��擾
//=============================================================================
BLOCK GetBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++) 
	{
		return g_Block[nCntBlock];
	}
}
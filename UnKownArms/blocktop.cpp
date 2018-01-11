//=============================================================================
//
// �t�B�[���h���� [field.cpp]
// Author : ���� ���
//
//=============================================================================
#include "blocktop.h"
#include "block.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_VERTEX	4
#define MAX_PRI		2
#define MAX_IDX		4

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlockTop = NULL;
LPDIRECT3DTEXTURE9		g_pTextureBlockTop = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffBlockTop = NULL; // �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
BLOCK_TOP g_BlockTop[MAX_BLOCK];

//=============================================================================
// ����������
//=============================================================================
void InitBlockTop()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureBlockTop);

	for (int nCntBlockTop = 0; nCntBlockTop < MAX_BLOCK; nCntBlockTop++) {

		g_BlockTop[nCntBlockTop].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
		g_BlockTop[nCntBlockTop].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		g_BlockTop[nCntBlockTop].scl = D3DXVECTOR3(1.f, 1.f, 1.f);
		g_BlockTop[nCntBlockTop].bUse = false;
	}

	// ���_���̍쐬
	MakeVertexBlockTop(pDevice);
	//�C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * MAX_IDX * MAX_BLOCK, //�C���f�b�N�X��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffBlockTop,
		NULL);

	WORD *pIdx;
	g_pIdxBuffBlockTop->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 3;
	pIdx[3] = 2;

	g_pIdxBuffBlockTop->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void UninitBlockTop()
{
	// �C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffBlockTop)
	{
		g_pIdxBuffBlockTop->Release();
		g_pIdxBuffBlockTop = NULL;
	}

	// �e�N�X�`���̉��
	if (g_pTextureBlockTop)
	{
		g_pTextureBlockTop->Release();
		g_pTextureBlockTop = NULL;
	}
	// �o�b�t�@�̉��
	if (g_pVtxBuffBlockTop)
	{
		g_pVtxBuffBlockTop->Release();
		g_pVtxBuffBlockTop = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlockTop()
{
	PrintDebug("unko\n");
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlockTop()
{
	for (int nCntBlockTop = 0; nCntBlockTop < MAX_BLOCK; nCntBlockTop++) {
		if (g_BlockTop[nCntBlockTop].bUse)
		{
			D3DXMATRIX g_mtxScl;			//�X�P�[���}�g���b�N�X
			D3DXMATRIX g_mtxRot;			//��]�}�g���b�N�X
			D3DXMATRIX g_mtxTransForm;		//�ړ��}�g���b�N�X
			D3DMATERIAL9 matDef;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_BlockTop[nCntBlockTop].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&g_mtxScl, g_BlockTop[nCntBlockTop].scl.x, g_BlockTop[nCntBlockTop].scl.y, g_BlockTop[nCntBlockTop].scl.z);
			D3DXMatrixMultiply(&g_BlockTop[nCntBlockTop].mtxWorld, &g_BlockTop[nCntBlockTop].mtxWorld, &g_mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_BlockTop[nCntBlockTop].rot.y, g_BlockTop[nCntBlockTop].rot.x, g_BlockTop[nCntBlockTop].rot.z);
			D3DXMatrixMultiply(&g_BlockTop[nCntBlockTop].mtxWorld, &g_BlockTop[nCntBlockTop].mtxWorld, &g_mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&g_mtxTransForm, g_BlockTop[nCntBlockTop].pos.x, g_BlockTop[nCntBlockTop].pos.y, g_BlockTop[nCntBlockTop].pos.z);
			D3DXMatrixMultiply(&g_BlockTop[nCntBlockTop].mtxWorld, &g_BlockTop[nCntBlockTop].mtxWorld, &g_mtxTransForm);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_BlockTop[nCntBlockTop].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBlockTop, 0, sizeof(VERTEX_3D));
			pDevice->SetIndices(g_pIdxBuffBlockTop);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureBlockTop);
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
// �u���b�N�̐����i �ӂ� �j
//=============================================================================
void CreateBlockTop(D3DXVECTOR3 pos, int ikind)
{
	for (int nCntBlockTop = 0; nCntBlockTop < MAX_BLOCK; nCntBlockTop++)
	{
		if (g_BlockTop[nCntBlockTop].bUse == false) {
			g_BlockTop[nCntBlockTop].pos = pos;
			g_BlockTop[nCntBlockTop].ikind = ikind;
			g_BlockTop[nCntBlockTop].bUse = true;
			break;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBlockTop(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlockTop, NULL);

	VERTEX_3D *pVtx;

	g_pVtxBuffBlockTop->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlockTop = 0; nCntBlockTop < MAX_BLOCK; nCntBlockTop++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE * 2, OBJ_SIZE);
		pVtx[1].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE * 2, OBJ_SIZE);
		pVtx[2].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE * 2, -OBJ_SIZE);
		pVtx[3].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE * 2, -OBJ_SIZE);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[1].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[2].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[3].nor = D3DXVECTOR3(0.f, 0.f, -1.f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 0.5);
		pVtx[1].tex = D3DXVECTOR2(0.5, 0.5);
		pVtx[2].tex = D3DXVECTOR2(0.5, 0);
		pVtx[3].tex = D3DXVECTOR2(0, 0);

		pVtx += 4;
	}

	g_pVtxBuffBlockTop->Unlock();
}

BLOCK_TOP GetBlockTop()
{
	for (int nCntBlockTop = 0; nCntBlockTop < MAX_BLOCK; nCntBlockTop++)
	{
		return g_BlockTop[nCntBlockTop];
	}
}
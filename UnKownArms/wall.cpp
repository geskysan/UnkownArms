//=============================================================================
//
// �ǂ̏��� [wall.cpp]
// Author : ����@���
//
//=============================================================================
#include "wall.h"
#include "Input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);
#define X	1
#define Z	1

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;	// �e�N�X�`���ւ̃|�C���^
MESH_WALL g_aMeshWall[MAX_WALL];
int g_WallBertex;
int g_WallPri;
//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++) 
	{	
		g_aMeshWall[nCntWall].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
		g_aMeshWall[nCntWall].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		g_aMeshWall[nCntWall].scl = D3DXVECTOR3(1, 1, 1);
		g_aMeshWall[nCntWall].bUse = false;
	}

	g_WallBertex = (X + 1) * (Z + 1);		//���_�������߂�
	g_WallPri = (X*Z) * 2 + (Z - 1) * 4;	//�|���S���������߂�

	// ���_���̍쐬
	MakeVertexWall(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
	// �e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX g_mtxScl;
	D3DXMATRIX g_mtxRot;
	D3DXMATRIX g_mtxTransForm;
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++) {
		if (g_aMeshWall[nCntWall].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshWall[nCntWall].g_mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&g_mtxScl, g_aMeshWall[nCntWall].scl.x, g_aMeshWall[nCntWall].scl.y, g_aMeshWall[nCntWall].scl.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].g_mtxWorld, &g_aMeshWall[nCntWall].g_mtxWorld, &g_mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_aMeshWall[nCntWall].rot.y, g_aMeshWall[nCntWall].rot.x, g_aMeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].g_mtxWorld, &g_aMeshWall[nCntWall].g_mtxWorld, &g_mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&g_mtxTransForm, g_aMeshWall[nCntWall].pos.x, g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].g_mtxWorld, &g_aMeshWall[nCntWall].g_mtxWorld, &g_mtxTransForm);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntWall].g_mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureWall);
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_WallBertex,//���_��
				0,
				g_WallPri);//�v���~�e�B�u��(�|���S����)
		}
	}
}

//=============================================================================
// �ǂ̐���
//=============================================================================
void CreateWall(D3DXVECTOR3 pos, int iKind)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aMeshWall[nCntWall].pos = pos;
		g_aMeshWall[nCntWall].iKind = iKind;
		g_aMeshWall[nCntWall].bUse = true;
		break;
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_WallBertex*MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall, NULL);

	VERTEX_3D *pVtx;

	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-OBJ_SIZE, 0.f, 0.f);
		pVtx[1].pos = D3DXVECTOR3(OBJ_SIZE, 0.f, 0.f);
		pVtx[2].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE, 0.f);
		pVtx[3].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE, 0.f);

		//�@���̐ݒ�
		for (int i = 0; i < g_WallBertex; i++) {
			pVtx[i].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		}

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);

		pVtx += 4;
	}

	g_pVtxBuffWall->Unlock();
}
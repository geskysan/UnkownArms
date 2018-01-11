//=============================================================================
//
// �e�̏��� [shadow.cpp]
// Author : ����@���
//
//=============================================================================
#include "shadow.h"
#include "player.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;

Shadow g_shadow[MAX_SHADOW];

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER pModel;

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++) {
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.f, 0.f, 0.f);
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.f, 0.f, 0.f);
		g_shadow[nCntShadow].scl = D3DXVECTOR3(1.f, 1.f, 1.f);
		g_shadow[nCntShadow].bUse = false;
	}
	// ���_���̍쐬
	MakeVertexShadow(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
	// �e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	D3DXMATRIX g_mtxScl, g_mtxRot, g_mtxTransForm;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++) {

		if (g_shadow[nCntShadow].bUse)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&g_mtxScl, g_shadow[nCntShadow].scl.x, g_shadow[nCntShadow].scl.y, g_shadow[nCntShadow].scl.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &g_mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_shadow[nCntShadow].rot.y, g_shadow[nCntShadow].rot.x, g_shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &g_mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&g_mtxTransForm, g_shadow[nCntShadow].pos.x, g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &g_mtxTransForm);


			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureShadow);
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorld);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + nCntShadow * 4, 2);

			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow, NULL);

	VERTEX_3D *pVtx;
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-25.f, 0.f, -25.f);
		pVtx[1].pos = D3DXVECTOR3(-25.f, 0.f, 25.f);
		pVtx[2].pos = D3DXVECTOR3(25.f, 0.f, -25.f);
		pVtx[3].pos = D3DXVECTOR3(25.f, 0.f, 25.f);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
		pVtx[3].nor = D3DXVECTOR3(0, 1, 0);


		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 125);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 125);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 125);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 125);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(0, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 1);
	}
	g_pVtxBuffShadow->Unlock();
}

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	VERTEX_3D *pVtx;
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = pos;
		g_shadow[nCntShadow].scl = scl;
		g_shadow[nCntShadow].bUse = true;
		break;

		pVtx[0].pos.x = g_shadow[nCntShadow].pos.x - 25;
		pVtx[0].pos.y = 0.f;
		pVtx[0].pos.z = g_shadow[nCntShadow].pos.z - 25;

		pVtx[1].pos.x = g_shadow[nCntShadow].pos.x + 25;
		pVtx[1].pos.y = 0.f;
		pVtx[1].pos.z = g_shadow[nCntShadow].pos.z - 25;

		pVtx[2].pos.x = g_shadow[nCntShadow].pos.x - 25;
		pVtx[2].pos.y = 0.f;
		pVtx[2].pos.z = g_shadow[nCntShadow].pos.z + 25;

		pVtx[3].pos.x = g_shadow[nCntShadow].pos.x + 25;
		pVtx[3].pos.y = 0.f;
		pVtx[3].pos.z = g_shadow[nCntShadow].pos.z + 25;
	}
	return nCntShadow;
}

void SetPositionShadow(D3DXVECTOR3 pos, D3DXVECTOR3 scl,int IdxShadow)
{

	VERTEX_3D *pVtx;
	int nCntShadow;
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = pos;
		g_shadow[nCntShadow].scl = scl;
		g_shadow[nCntShadow].bUse = true;
		break;

		pVtx[0].pos.x = g_shadow[nCntShadow].pos.x - 25;
		pVtx[0].pos.y = 0.f;
		pVtx[0].pos.z = g_shadow[nCntShadow].pos.z - 25;

		pVtx[1].pos.x = g_shadow[nCntShadow].pos.x + 25;
		pVtx[1].pos.y = 0.f;
		pVtx[1].pos.z = g_shadow[nCntShadow].pos.z - 25;

		pVtx[2].pos.x = g_shadow[nCntShadow].pos.x - 25;
		pVtx[2].pos.y = 0.f;
		pVtx[2].pos.z = g_shadow[nCntShadow].pos.z + 25;

		pVtx[3].pos.x = g_shadow[nCntShadow].pos.x + 25;
		pVtx[3].pos.y = 0.f;
		pVtx[3].pos.z = g_shadow[nCntShadow].pos.z + 25;
	}
}
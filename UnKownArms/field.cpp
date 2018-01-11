//=============================================================================
//
// �t�B�[���h���� [field.cpp]
// Author : ���� ���
//
//=============================================================================
#include "field.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
#define V	1
#define H	1

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;
LPDIRECT3DTEXTURE9		g_pTextureField = NULL;	// �e�N�X�`���ւ̃|�C���^

FIELD g_Field;
int g_FieldVtx;		// ���_��
int g_FieldPri;		// �|���S����

//=============================================================================
// ����������
//=============================================================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field_back.jpg", &g_pTextureField);

	g_Field.pos = D3DXVECTOR3(0.f, 0.f, 0.f);
	g_Field.rot = D3DXVECTOR3(0.f, 0.f, 0.f);
	g_Field.scl = D3DXVECTOR3(1.f, 1.f, 1.f);
	g_Field.bUse = true;

	g_FieldVtx = (V + 1) * (H + 1);				//���_�������߂�
	g_FieldPri = (V * H) * 2 + (H - 1) * 4;		//�|���S���������߂�

	// ���_���̍쐬
	MakeVertexField(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
	// �e�N�X�`���̊J��
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{
	
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	if (g_Field.bUse)
	{
		D3DXMATRIX g_mtxScl, g_mtxRot, g_mtxTransForm;
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Field.mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&g_mtxScl, g_Field.scl.x, g_Field.scl.y, g_Field.scl.z);
		D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &g_mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_Field.rot.y, g_Field.rot.x, g_Field.rot.z);
		D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &g_mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&g_mtxTransForm, g_Field.pos.x, g_Field.pos.y, g_Field.pos.z);
		D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &g_mtxTransForm);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Field.mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, g_pTextureField);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_FieldVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField, NULL);


	VERTEX_3D *pVtx;
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-1000.f, 0.f, -1000.f);
	pVtx[1].pos = D3DXVECTOR3(-1000.f, 0.f, 1000.f);
	pVtx[2].pos = D3DXVECTOR3(1000.f, 0.f, -1000.f);
	pVtx[3].pos = D3DXVECTOR3(1000.f, 0.f, 1000.f);


	//�@���̐ݒ�
	for (int i = 0; i < g_FieldVtx; i++) {
		pVtx[i].nor = D3DXVECTOR3(0, 0, -1);
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

	g_pVtxBuffField->Unlock();
}

FIELD GetField(void)
{
	return g_Field;
}
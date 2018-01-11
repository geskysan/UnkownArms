//=============================================================================
// �t�F�[�h�̏��� [fade.cpp]
//=============================================================================
#include "fade.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;

D3DXCOLOR g_col;
MODE ModeNext = MODE_TITLE;
FADE g_Fade = FADE_IN;


//=============================================================================
// ����������
//=============================================================================
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.jpg", &g_pTextureFade);

	g_col = D3DXCOLOR(0, 0, 0, 1);
	
	// ���_���̍쐬
	MakeVertexFade(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
	// �e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	VERTEX_3D *pVtx;
	if (g_Fade != FADE_NONE)
	{
		if (g_Fade == FADE_IN)
		{
 			g_col.a -= 0.01f;
			if (g_col.a <= 0.f)
			{
				g_col.a = 0.f;
				g_Fade = FADE_NONE;
			}
		}
		else if (g_Fade == FADE_OUT)
		{
			g_col.a += 0.01f;
			if (g_col.a >= 1.f)
			{
				g_col.a = 1.f;
				g_Fade = FADE_IN;

				//���̉�ʁi���[�h�j�̐ݒ�
				SetMode(ModeNext);
			}
		}

		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].col = g_col;
		pVtx[1].col = g_col;
		pVtx[2].col = g_col;
		pVtx[3].col = g_col;
		g_pVtxBuffFade->Unlock();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade(void)
{
	D3DXMATRIX mtxWorldTitleback;
	D3DXMATRIX mtxView;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorldTitleback);

	// ��]�𔽉f
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	mtxWorldTitleback._11 = mtxView._11;
	mtxWorldTitleback._12 = mtxView._21;
	mtxWorldTitleback._13 = mtxView._31;
	mtxWorldTitleback._21 = mtxView._12;
	mtxWorldTitleback._22 = mtxView._22;
	mtxWorldTitleback._23 = mtxView._32;
	mtxWorldTitleback._31 = mtxView._13;
	mtxWorldTitleback._32 = mtxView._23;
	mtxWorldTitleback._33 = mtxView._33;

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldTitleback);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, g_pTextureFade);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade, NULL);

	VERTEX_3D *pVtx;
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-WIDTH_SIZE, -HEIGHT_SIZE, 0);
	pVtx[1].pos = D3DXVECTOR3(-WIDTH_SIZE, HEIGHT_SIZE, 0);
	pVtx[2].pos = D3DXVECTOR3(WIDTH_SIZE, -HEIGHT_SIZE, 0);
	pVtx[3].pos = D3DXVECTOR3(WIDTH_SIZE, HEIGHT_SIZE, 0);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[1].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[2].nor = D3DXVECTOR3(0, 1, 0);
	pVtx[3].nor = D3DXVECTOR3(0, 1, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(0, 1);
	pVtx[2].tex = D3DXVECTOR2(1, 0);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	g_pVtxBuffFade->Unlock();
}

void SetFade(MODE mode)
{
	g_Fade = FADE_OUT;
	ModeNext = mode;
}

FADE GetFade(void)
{
	return g_Fade;
}
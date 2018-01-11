//=============================================================================
//�@���C�g���� [light.h]
//=============================================================================
#include "light.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_aLight[3]; //���C�g�̏��

					   //=============================================================================
					   // ����������
					   //=============================================================================
void InitLight(void)
{
	SetLight();
}
//=============================================================================
// �I������
//=============================================================================
void UninitLight(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdataLight(void)
{

}
//=============================================================================
// ���C�g�̐ݒ�
//=============================================================================
void SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	ZeroMemory(&g_aLight, sizeof(D3DLIGHT9));

	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// �g�U��
	g_aLight[0].Diffuse.r = 1.0f;
	g_aLight[0].Diffuse.g = 1.0f;
	g_aLight[0].Diffuse.b = 1.0f;

	// ����
	g_aLight[0].Ambient.r = 0.50f;
	g_aLight[0].Ambient.g = 0.50f;
	g_aLight[0].Ambient.b = 0.50f;

	//���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.20f, 3.00f, 1.80f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);
	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_aLight[0]);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9�\���̂�0�ŃN���A����
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ���C�g�̃^�C�v�̐ݒ�
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// �g�U��
	g_aLight[1].Diffuse.r = 0.25f;
	g_aLight[1].Diffuse.g = 0.25f;
	g_aLight[1].Diffuse.b = 0.25f;

	// ����
	g_aLight[1].Ambient.r = 0.20f;
	g_aLight[1].Ambient.g = 0.20f;
	g_aLight[1].Ambient.b = 0.20f;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-0.20f, -3.00f, -1.80f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &g_aLight[1]);

	// ���C�g�̐ݒ�
	pDevice->LightEnable(1, TRUE);

	// ���C�e�B���O���[�h
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
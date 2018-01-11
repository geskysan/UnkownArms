//=============================================================================
// �J�������� [camera.cpp]
//=============================================================================
#include "camera.h"
#include "Input.h"
#include "player.h"
#include "debugproc.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.f, 250.f, -150.f);		// �J�����̎��_
	g_camera.posR = D3DXVECTOR3(0.f, 0.f, 0.f);				// �J�����̒����_
	g_camera.vecU = D3DXVECTOR3(0.f, 1.f, 0.f);				// �J�����̏�̕���
	g_camera.fDistance = 250.f;
	SetCamera();
}
//=============================================================================
// �I������
//=============================================================================
void UnintCamera(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdataCamera(void)
{
	PLAYER pPlayer = GetPlayer();

	PrintDebug("posV : %f %f %f\n", g_camera.posV.x, g_camera.posV.y, g_camera.posV.z);

	g_camera.posV = D3DXVECTOR3(pPlayer.pos.x, pPlayer.pos.y + 250.f, pPlayer.pos.z - 150.f);
	g_camera.posR = pPlayer.pos;

	/*if (GetKeyboardPress(DIK_W))
	{
		g_camera.posV.x += sinf(g_camera.rot.y)*2.f;
		g_camera.posV.z += cosf(g_camera.rot.y)*2.f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_S))
	{
		g_camera.posV.x -= sinf(g_camera.rot.y)*2.f;
		g_camera.posV.z -= cosf(g_camera.rot.y)*2.f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_A))
	{
		g_camera.posV.x -= cosf(g_camera.rot.y)*2.f;
		g_camera.posV.z += sinf(g_camera.rot.y)*2.f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_D))
	{
		g_camera.posV.x += cosf(g_camera.rot.y)*2.f;
		g_camera.posV.z -= sinf(g_camera.rot.y)*2.f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*g_camera.fDistance;
	}*/
	if (GetKeyboardPress(DIK_Q))
	{
		g_camera.rot.y += 0.01f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_E))
	{
		g_camera.rot.y -= 0.01f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y)*g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_Z))
	{
		g_camera.rot.y += 0.01f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y)*g_camera.fDistance;
	}
	if (GetKeyboardPress(DIK_C))
	{
		g_camera.rot.y -= 0.01f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y)*g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y)*g_camera.fDistance;
	}
}

//=============================================================================
// �J�����̐ݒ�
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(60.f), SCREEN_WIDTH/SCREEN_HEIGHT, 10.f, 1000.f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,			// �J�����̎��_
		&g_camera.posR,			// �J�����̒����_
		&g_camera.vecU);		// �J�����̏�̕���

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=============================================================================
// �J�����̏��擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}
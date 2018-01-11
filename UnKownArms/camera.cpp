//=============================================================================
// カメラ処理 [camera.cpp]
//=============================================================================
#include "camera.h"
#include "Input.h"
#include "player.h"
#include "debugproc.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_camera;

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.f, 250.f, -150.f);		// カメラの視点
	g_camera.posR = D3DXVECTOR3(0.f, 0.f, 0.f);				// カメラの注視点
	g_camera.vecU = D3DXVECTOR3(0.f, 1.f, 0.f);				// カメラの上の方向
	g_camera.fDistance = 250.f;
	SetCamera();
}
//=============================================================================
// 終了処理
//=============================================================================
void UnintCamera(void)
{

}
//=============================================================================
// 更新処理
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
// カメラの設定
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(60.f), SCREEN_WIDTH/SCREEN_HEIGHT, 10.f, 1000.f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,			// カメラの視点
		&g_camera.posR,			// カメラの注視点
		&g_camera.vecU);		// カメラの上の方向

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=============================================================================
// カメラの情報取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}
//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 小川 朔哉
//
//=============================================================================
#include <math.h>
#include "player.h"
#include "block.h"
#include "Input.h"
#include "camera.h"
#include "shadow.h"
#include "collision.h"
#include "debugproc.h"

#define MOVE		10.f
#define ROTATION	0.05f

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH			g_pMeshPlayer = NULL;
LPD3DXBUFFER		g_pBuffMatPlayer = NULL;
DWORD				g_nNumMatPlayer = 0;

PLAYER g_Player;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/airplane000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_nNumMatPlayer,
		&g_pMeshPlayer);

	g_Player.pos = D3DXVECTOR3(600.f, 0.f, -600.f);
	g_Player.rot = vector3NS::ZERO;
	g_Player.scl = vector3NS::ONE;
	g_Player.bUse = true;
	g_Player.IdxShadow= SetShadow(D3DXVECTOR3(g_Player.pos.x, 0, g_Player.pos.z), D3DXVECTOR3(1.f, 1.f, 1.f));
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer()
{
	// メッシュの解放
	if (g_pMeshPlayer)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	// バッファの解放
	if (g_pBuffMatPlayer)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer()
{
	Camera *pCamera;
	pCamera = GetCamera();
	float fDifRot;

	{

	}

	/*移動処理*/
	if (GetKeyboardPress(DIK_W))
	{
		if (GetKeyboardPress(DIK_D))	// d右上
		{
			g_Player.move.x -= sinf(pCamera->rot.y - D3DX_PI*0.75f);
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI*0.75f);
			g_Player.rotDest.y = D3DX_PI*-0.75f + pCamera->rot.y;
		}

		else if (GetKeyboardPress(DIK_A))	// 左上
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI*0.25f);
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI*0.25f);
			g_Player.rotDest.y = D3DX_PI*0.75f + pCamera->rot.y;
		}

		else	// 上
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI);
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI);
			g_Player.rotDest.y = D3DX_PI*-1.f + pCamera->rot.y;
		}
	}

	else if (GetKeyboardPress(DIK_S))
	{
		if (GetKeyboardPress(DIK_D))	// 右下
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI*-0.75);
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI*-0.75);
			g_Player.rotDest.y = D3DX_PI*-0.25f + pCamera->rot.y;
		}

		else if (GetKeyboardPress(DIK_A))	// 左下
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI*0.75);
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI*0.75);
			g_Player.rotDest.y = D3DX_PI*0.25f + pCamera->rot.y;
		}
		else	//下
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI);
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI);
			g_Player.rotDest.y = D3DX_PI * 0 + pCamera->rot.y;
		}
	}

	else if (GetKeyboardPress(DIK_A))	// 左
	{
		g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI*0.5f);
		g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI*0.5f);
		g_Player.rotDest.y = D3DX_PI*0.5f + pCamera->rot.y;
	}

	else if (GetKeyboardPress(DIK_D))	// 右
	{
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI*0.5f);
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI*0.5f);
		g_Player.rotDest.y = D3DX_PI*-0.5f + pCamera->rot.y;
	}

	//差分を求める
	fDifRot = g_Player.rot.y - g_Player.rot.y;
	if (fDifRot > D3DX_PI)
		fDifRot -= D3DX_PI * 2;
	else if (fDifRot < D3DX_PI)
		fDifRot += D3DX_PI * 2;

	g_Player.pos += g_Player.move;
	g_Player.rot = g_Player.rotDest + g_Player.rot;
	g_Player.move += (D3DXVECTOR3(0, 0, 0) - g_Player.move) * 0.2f;
	g_Player.rot += (D3DXVECTOR3(0, 0, 0) - g_Player.rot) * 0.5f;

	//影の追従処理
	// SetPositionShadow(D3DXVECTOR3(g_Player.pos.x, 0, g_Player.pos.z), D3DXVECTOR3(1.f, 1.f, 1.f), g_Player.IdxShadow);

	PrintDebug("pos : %f , %f , %f\n", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer()
{
	if (g_Player.bUse)
	{
		D3DXMATRIX g_mtxScl;			//スケールマトリックス
		D3DXMATRIX g_mtxRot;			//回転マトリックス
		D3DXMATRIX g_mtxTransForm;		//移動マトリックス
		D3DMATERIAL9 matDef;

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&g_mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &g_mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &g_mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&g_mtxTransForm, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &g_mtxTransForm);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアル情報に対するポインタを取得
		D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

		// モデルの描画
		for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// 描画
			g_pMeshPlayer->DrawSubset(nCntMat);
		}

		// マテリアルを元に戻す
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// プレイヤーの初期位置設定
//=============================================================================
void CreatePlayer(D3DXVECTOR3 pos)
{
	if (g_Player.bUse == false)
	{
		g_Player.pos = pos;
		g_Player.bUse = true;
	}
}

//=============================================================================
// プレイヤーの情報取得
//=============================================================================
PLAYER GetPlayer(void)
{
	return g_Player;
}

void SetPosition(D3DXVECTOR3 pos)
{
	g_Player.pos = pos;
}
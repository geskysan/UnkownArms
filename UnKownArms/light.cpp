//=============================================================================
//　ライト処理 [light.h]
//=============================================================================
#include "light.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_aLight[3]; //ライトの情報

					   //=============================================================================
					   // 初期化処理
					   //=============================================================================
void InitLight(void)
{
	SetLight();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitLight(void)
{

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdataLight(void)
{

}
//=============================================================================
// ライトの設定
//=============================================================================
void SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	ZeroMemory(&g_aLight, sizeof(D3DLIGHT9));

	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[0].Diffuse.r = 1.0f;
	g_aLight[0].Diffuse.g = 1.0f;
	g_aLight[0].Diffuse.b = 1.0f;

	// 環境光
	g_aLight[0].Ambient.r = 0.50f;
	g_aLight[0].Ambient.g = 0.50f;
	g_aLight[0].Ambient.b = 0.50f;

	//ライトの方向の設定
	vecDir = D3DXVECTOR3(0.20f, 3.00f, 1.80f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);
	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_aLight[0]);

	// ライトの設定
	pDevice->LightEnable(0, TRUE);


	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[1].Diffuse.r = 0.25f;
	g_aLight[1].Diffuse.g = 0.25f;
	g_aLight[1].Diffuse.b = 0.25f;

	// 環境光
	g_aLight[1].Ambient.r = 0.20f;
	g_aLight[1].Ambient.g = 0.20f;
	g_aLight[1].Ambient.b = 0.20f;

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(-0.20f, -3.00f, -1.80f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(1, &g_aLight[1]);

	// ライトの設定
	pDevice->LightEnable(1, TRUE);

	// ライティングモード
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
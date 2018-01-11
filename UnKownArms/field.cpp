//=============================================================================
//
// フィールド処理 [field.cpp]
// Author : 小川 朔哉
//
//=============================================================================
#include "field.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
#define V	1
#define H	1

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;
LPDIRECT3DTEXTURE9		g_pTextureField = NULL;	// テクスチャへのポインタ

FIELD g_Field;
int g_FieldVtx;		// 頂点数
int g_FieldPri;		// ポリゴン数

//=============================================================================
// 初期化処理
//=============================================================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field_back.jpg", &g_pTextureField);

	g_Field.pos = D3DXVECTOR3(0.f, 0.f, 0.f);
	g_Field.rot = D3DXVECTOR3(0.f, 0.f, 0.f);
	g_Field.scl = D3DXVECTOR3(1.f, 1.f, 1.f);
	g_Field.bUse = true;

	g_FieldVtx = (V + 1) * (H + 1);				//頂点数を求める
	g_FieldPri = (V * H) * 2 + (H - 1) * 4;		//ポリゴン数を求める

	// 頂点情報の作成
	MakeVertexField(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
	// テクスチャの開放
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
	
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	if (g_Field.bUse)
	{
		D3DXMATRIX g_mtxScl, g_mtxRot, g_mtxTransForm;
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Field.mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&g_mtxScl, g_Field.scl.x, g_Field.scl.y, g_Field.scl.z);
		D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &g_mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_Field.rot.y, g_Field.rot.x, g_Field.rot.z);
		D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &g_mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&g_mtxTransForm, g_Field.pos.x, g_Field.pos.y, g_Field.pos.z);
		D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &g_mtxTransForm);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Field.mtxWorld);

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);
		pDevice->SetTexture(0, g_pTextureField);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// 頂点情報の作成
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

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-1000.f, 0.f, -1000.f);
	pVtx[1].pos = D3DXVECTOR3(-1000.f, 0.f, 1000.f);
	pVtx[2].pos = D3DXVECTOR3(1000.f, 0.f, -1000.f);
	pVtx[3].pos = D3DXVECTOR3(1000.f, 0.f, 1000.f);


	//法線の設定
	for (int i = 0; i < g_FieldVtx; i++) {
		pVtx[i].nor = D3DXVECTOR3(0, 0, -1);
	}

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
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
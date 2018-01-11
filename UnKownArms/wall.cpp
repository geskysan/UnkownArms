//=============================================================================
//
// 壁の処理 [wall.cpp]
// Author : 小川　朔哉
//
//=============================================================================
#include "wall.h"
#include "Input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);
#define X	1
#define Z	1

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;	// テクスチャへのポインタ
MESH_WALL g_aMeshWall[MAX_WALL];
int g_WallBertex;
int g_WallPri;
//=============================================================================
// 初期化処理
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

	g_WallBertex = (X + 1) * (Z + 1);		//頂点数を求める
	g_WallPri = (X*Z) * 2 + (Z - 1) * 4;	//ポリゴン数を求める

	// 頂点情報の作成
	MakeVertexWall(pDevice);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitWall(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
	// テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateWall(void)
{

}
//=============================================================================
// 描画処理
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
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aMeshWall[nCntWall].g_mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&g_mtxScl, g_aMeshWall[nCntWall].scl.x, g_aMeshWall[nCntWall].scl.y, g_aMeshWall[nCntWall].scl.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].g_mtxWorld, &g_aMeshWall[nCntWall].g_mtxWorld, &g_mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_aMeshWall[nCntWall].rot.y, g_aMeshWall[nCntWall].rot.x, g_aMeshWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].g_mtxWorld, &g_aMeshWall[nCntWall].g_mtxWorld, &g_mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&g_mtxTransForm, g_aMeshWall[nCntWall].pos.x, g_aMeshWall[nCntWall].pos.y, g_aMeshWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntWall].g_mtxWorld, &g_aMeshWall[nCntWall].g_mtxWorld, &g_mtxTransForm);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntWall].g_mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureWall);
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				g_WallBertex,//頂点数
				0,
				g_WallPri);//プリミティブ数(ポリゴン数)
		}
	}
}

//=============================================================================
// 壁の生成
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
// 頂点情報の作成
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
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-OBJ_SIZE, 0.f, 0.f);
		pVtx[1].pos = D3DXVECTOR3(OBJ_SIZE, 0.f, 0.f);
		pVtx[2].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE, 0.f);
		pVtx[3].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE, 0.f);

		//法線の設定
		for (int i = 0; i < g_WallBertex; i++) {
			pVtx[i].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
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

		pVtx += 4;
	}

	g_pVtxBuffWall->Unlock();
}
//=============================================================================
//
// ブロック処理 [block.cpp]
// Author : 小川 朔哉
//
//=============================================================================
#include "block.h"
#include "blocktop.h"
#include "player.h"
#include "collision.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_VERTEX	8
#define MAX_PRI		10
#define MAX_IDX		10

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9		g_pTextureBlock = NULL;		// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffBlock = NULL;		// インデックスバッファへのポインタ
BLOCK g_Block[MAX_BLOCK];

//=============================================================================
// 初期化処理
//=============================================================================
void InitBlock()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureBlock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++) {

		g_Block[nCntBlock].pos = vector3NS::ZERO;
		g_Block[nCntBlock].rot = vector3NS::ZERO;
		g_Block[nCntBlock].scl = vector3NS::ONE;
		g_Block[nCntBlock].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexBlock(pDevice);
	//インデックスバッファを生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * MAX_IDX * MAX_BLOCK, //インデックス数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffBlock,
		NULL);

	WORD *pIdx;
	g_pIdxBuffBlock->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 0;
	pIdx[1] = 4;
	pIdx[2] = 1;
	pIdx[3] = 5;
	pIdx[4] = 2;
	pIdx[5] = 6;
	pIdx[6] = 3;
	pIdx[7] = 7;
	pIdx[8] = 0;
	pIdx[9] = 4;

	g_pIdxBuffBlock->Unlock();
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBlock()
{
		// インデックスバッファの解放
		if (g_pIdxBuffBlock)
		{
			g_pIdxBuffBlock->Release();
			g_pIdxBuffBlock = NULL;
		}

		// テクスチャの解放
		if (g_pTextureBlock)
		{
			g_pTextureBlock->Release();
			g_pTextureBlock = NULL;
		}
		// バッファの解放
		if (g_pVtxBuffBlock)
		{
			g_pVtxBuffBlock->Release();
			g_pVtxBuffBlock = NULL;
		}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateBlock()
{
	PLAYER pPlayer;
	pPlayer = GetPlayer();
	D3DXVECTOR3 PastPos;
	D3DXVECTOR3 VecToPos;
	PastPos = pPlayer.pos;
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (CollisionRectangle(g_Block[nCntBlock].pos, pPlayer.pos) && g_Block[nCntBlock].bUse)
		{

			PrintDebug("当たり\n");
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawBlock()
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++) {
		if (g_Block[nCntBlock].bUse)
		{
			D3DXMATRIX g_mtxScl;			//スケールマトリックス
			D3DXMATRIX g_mtxRot;			//回転マトリックス
			D3DXMATRIX g_mtxTransForm;		//移動マトリックス
			D3DMATERIAL9 matDef;

			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&g_mtxScl, g_Block[nCntBlock].scl.x, g_Block[nCntBlock].scl.y, g_Block[nCntBlock].scl.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &g_mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&g_mtxRot, g_Block[nCntBlock].rot.y, g_Block[nCntBlock].rot.x, g_Block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &g_mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&g_mtxTransForm, g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y, g_Block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &g_mtxTransForm);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlock].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_3D));
			pDevice->SetIndices(g_pIdxBuffBlock);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureBlock);
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				0,
				0,
				MAX_IDX,		// 頂点数
				0,
				MAX_PRI);		// プリミティブ数(ポリゴン数)
		}
	}
}

//=============================================================================
// ブロックの生成（ 外壁 ）
//=============================================================================
void CreateBlock(D3DXVECTOR3 pos, int ikind)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false) {
			g_Block[nCntBlock].pos = pos;
			g_Block[nCntBlock].ikind = ikind;
			g_Block[nCntBlock].bUse = true;

			// 上蓋作成
			CreateBlockTop(pos, ikind);
			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_VERTEX * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock, NULL);

	VERTEX_3D *pVtx;

	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlockTop = 0; nCntBlockTop < MAX_BLOCK; nCntBlockTop++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE * 2, OBJ_SIZE);
		pVtx[1].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE * 2, OBJ_SIZE);
		pVtx[2].pos = D3DXVECTOR3(OBJ_SIZE, OBJ_SIZE * 2, -OBJ_SIZE);
		pVtx[3].pos = D3DXVECTOR3(-OBJ_SIZE, OBJ_SIZE * 2, -OBJ_SIZE);
		pVtx[4].pos = D3DXVECTOR3(-OBJ_SIZE, 0.f, OBJ_SIZE);
		pVtx[5].pos = D3DXVECTOR3(OBJ_SIZE, 0.f, OBJ_SIZE);
		pVtx[6].pos = D3DXVECTOR3(OBJ_SIZE, 0.f, -OBJ_SIZE);
		pVtx[7].pos = D3DXVECTOR3(-OBJ_SIZE, 0.f, -OBJ_SIZE);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[1].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[2].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[3].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[4].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[5].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[6].nor = D3DXVECTOR3(0.f, 0.f, -1.f);
		pVtx[7].nor = D3DXVECTOR3(0.f, 0.f, -1.f);

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0, 0);
		pVtx[1].tex = D3DXVECTOR2(1, 0);
		pVtx[2].tex = D3DXVECTOR2(2, 0);
		pVtx[3].tex = D3DXVECTOR2(3, 0);
		pVtx[4].tex = D3DXVECTOR2(0, 1);
		pVtx[5].tex = D3DXVECTOR2(1, 1);
		pVtx[6].tex = D3DXVECTOR2(2, 1);
		pVtx[7].tex = D3DXVECTOR2(3, 1);

		pVtx +=8;
	}

	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの情報取得
//=============================================================================
BLOCK GetBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++) 
	{
		return g_Block[nCntBlock];
	}
}
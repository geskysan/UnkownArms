//=============================================================================
//
// マップ処理 [map.cpp]
// Author : 小川 朔哉
//
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "field.h"
#include "wall.h"
#include "block.h"
#include "blocktop.h"
#include "player.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJ_X 30
#define MAX_OBJ_Z 30

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJ_TYPE g_Object;
int obj;
//=============================================================================
// 初期化処理
//=============================================================================
void InitMap()
{
	InitField();
	InitBlock();
	InitBlockTop();

	// ファイル構造体
	FILE *fp;

	bool bMapFlag = false;
	int OBJ_SIZE_X = 50;
	int OBJ_SIZE_Z = 50;
	char line[BYTE];

	// ファイル名指定
	char *fname = "data/MAP/map.csv";

	// ファイルオープン
	fp = fopen(fname, "r");

	if (!fp)
	{
		MessageBox(NULL, "マップデータを読み込めませんでした。\n", NULL, MB_OK);
	}

	for (int nCntMap_Z = 0; nCntMap_Z < MAX_OBJ_Z; nCntMap_Z++)
	{
		for (int nCntMap_X = 0; nCntMap_X < MAX_OBJ_X; nCntMap_X++)
		{
			// 読み込み
			fscanf(fp, "%d,", &g_Object);

			switch (g_Object)
			{
				 //空白
			case OBJ_NONE:
				break;

				// ブロック
			case OBJ_BLOCK:
				CreateBlock(D3DXVECTOR3(-750 + OBJ_SIZE_X*nCntMap_X, 0, 750 + OBJ_SIZE_Z*-nCntMap_Z), 0);
				break;

			case OBJ_PLAYER:
				//CreatePlayer(D3DXVECTOR3(-750 + OBJ_SIZE_X*nCntMap_X, 20.f, 750 + OBJ_SIZE_Z*-nCntMap_Z));
				break;
			}
		}
	}

	fclose(fp);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMap()
{
	UninitField();
	UninitBlock();
	UninitBlockTop();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMap()
{
	UpdateField();
	//UpdateBlock();
	UpdateBlockTop();
	PrintDebug("%d\n", obj);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMap()
{
	DrawField();
	DrawBlock();
	DrawBlockTop();
}
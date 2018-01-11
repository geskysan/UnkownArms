//=============================================================================
//
// メイン処理 [main.h]
// Author : 小川　朔哉
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用
#include "dinput.h"

//*****************************************************************************
// ライブラリファイル
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄ頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1280.f)	// ウインドウの幅
#define SCREEN_HEIGHT	(720.f)	// ウインドウの高さ

#define WIDTH_SIZE		(320)
#define HEIGHT_SIZE		(280)

#define OBJ_SIZE		(25)

//*********************************************************
// 定数定義
//*********************************************************
namespace colorNS
{
	const D3DXCOLOR _WHITE = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const D3DXCOLOR _BLACK = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR _RED = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR _GREEN = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR _BLUE = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	const D3DXCOLOR _TRANS = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	const D3DXCOLOR _BACKGROUND = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
}

namespace vector3NS
{
	const D3DXVECTOR3 ZERO = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const D3DXVECTOR3 ONE = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	const D3DXVECTOR3 UP = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	const D3DXVECTOR3 RIGHT = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	const D3DXVECTOR3 FORWARD = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

//*****************************************************************************
// 構造体
//*****************************************************************************
//２Ｄの構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標polygon
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//３Ｄの構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;

// モード
typedef enum
{
	MODE_TITLE=0,
	MODE_GAMEMAIN,
	MODE_END,
}MODE;

// Ｘファイル構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	LPD3DXMESH pMesh;		// メッシュ
	LPD3DXBUFFER pBuffMat;
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	DWORD nNumMat;
	int nIdxModelParent;	// 親モデルのインデックス

}MODEL;

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);


LPDIRECT3DDEVICE9 GetDevice(void);

#endif
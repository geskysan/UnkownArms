#pragma once
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	LENGTH_STRING_BUFF		(1024)		// デバッグ表示のバッファ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitDebug(void);
void UninitDebug(void);
void DrawDebug(void);
void PrintDebug(char *fmt, ...);
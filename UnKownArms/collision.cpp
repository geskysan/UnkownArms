//=============================================================================
//
// 当たり判定処理 [collision.cpp]
// Author : 小川 朔哉
//
//=============================================================================
#include "collision.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_VEC	4

//=============================================================================
// 汎用当たり判定
//=============================================================================
bool CollisionRay(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, LPD3DXMESH pMesh)
{
	//レイ判定準備
	D3DXVECTOR3 vDir[4];
	vDir[0] = D3DXVECTOR3(0, 0, 1);//↑
	vDir[1] = D3DXVECTOR3(0, 0, -1);//↓
	vDir[2] = D3DXVECTOR3(1, 0, 0);//→
	vDir[3] = D3DXVECTOR3(-1, 0, 0);//←

									//あたり判定
	D3DXVECTOR3 vRayPoint;
	FLOAT		fDist = 0.0f;	//距離
	BOOL		bHit;	//あたってる場合TRUEが入る

	vRayPoint = pos + -1 * pos2;
	//メッシュとレイの判定
	for (int i = 0; i < 4; i++)
	{
		D3DXIntersect(
			pMesh,
			&vRayPoint,
			&vDir[i],
			&bHit,
			NULL,
			NULL,
			NULL,
			&fDist,
			NULL,
			NULL);

		if (bHit)
		{
			if (fDist < 10)
			{
				pos += vDir[i] * (fDist - 10);
				return true;
			}
		}
	}
	return false;
}

//=============================================================================
// 矩形の当たり判定
//=============================================================================
bool CollisionRectangle(D3DXVECTOR3 pos, D3DXVECTOR3 PlayerPos)
{
	if (pos.x + OBJ_SIZE > PlayerPos.x && pos.x - OBJ_SIZE < PlayerPos.x &&
		pos.z + OBJ_SIZE > PlayerPos.z && pos.z - OBJ_SIZE < PlayerPos.z)
	{
		return true;
	}
	return false;
}
//=============================================================================
//
// �����蔻�菈�� [collision.cpp]
// Author : ���� ���
//
//=============================================================================
#include "collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_VEC	4

//=============================================================================
// �ėp�����蔻��
//=============================================================================
bool CollisionRay(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, LPD3DXMESH pMesh)
{
	//���C���菀��
	D3DXVECTOR3 vDir[4];
	vDir[0] = D3DXVECTOR3(0, 0, 1);//��
	vDir[1] = D3DXVECTOR3(0, 0, -1);//��
	vDir[2] = D3DXVECTOR3(1, 0, 0);//��
	vDir[3] = D3DXVECTOR3(-1, 0, 0);//��

									//�����蔻��
	D3DXVECTOR3 vRayPoint;
	FLOAT		fDist = 0.0f;	//����
	BOOL		bHit;	//�������Ă�ꍇTRUE������

	vRayPoint = pos + -1 * pos2;
	//���b�V���ƃ��C�̔���
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
// ��`�̓����蔻��
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
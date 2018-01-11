//=============================================================================
//
// ���C������ [main.h]
// Author : ����@���
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"

//*****************************************************************************
// ���C�u�����t�@�C��
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1280.f)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720.f)	// �E�C���h�E�̍���

#define WIDTH_SIZE		(320)
#define HEIGHT_SIZE		(280)

#define OBJ_SIZE		(25)

//*********************************************************
// �萔��`
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
// �\����
//*****************************************************************************
//�Q�c�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���Wpolygon
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//�R�c�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

// ���[�h
typedef enum
{
	MODE_TITLE=0,
	MODE_GAMEMAIN,
	MODE_END,
}MODE;

// �w�t�@�C���\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	LPD3DXMESH pMesh;		// ���b�V��
	LPD3DXBUFFER pBuffMat;
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	DWORD nNumMat;
	int nIdxModelParent;	// �e���f���̃C���f�b�N�X

}MODEL;

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);


LPDIRECT3DDEVICE9 GetDevice(void);

#endif
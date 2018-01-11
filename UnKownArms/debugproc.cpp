//=============================================================================
//
// �f�o�b�O���� [debugproc.cpp]
// Author : 
//
//=============================================================================
#include <stdio.h>
#include <stdarg.h>
#include "debugproc.h"

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
LPD3DXFONT m_pFont = NULL;
char m_aStr[LENGTH_STRING_BUFF] = { "\0" };
bool m_bDisp = true;

//=============================================================================
// ����������
//=============================================================================
void InitDebug()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �o�b�t�@�N���A
	memset(m_aStr, 0, sizeof m_aStr);

	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�j�R�J", &m_pFont);
}

//=============================================================================
// �J������
//=============================================================================
void UninitDebug(void)
{
	if (m_pFont != NULL)
	{// ���\���p�t�H���g�̊J��
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//=============================================================================
// �������ݏ���
//=============================================================================
void PrintDebug(char *fmt, ...)
{
#ifdef _DEBUG
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
		pParam[5], pParam[6], pParam[7], pParam[8],
		pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;			// �ψ�������������ׂɎg�p����ϐ�
	char *pCur;
	char aBuf[256] = { "\0" };
	char aWk[32];

	// �ψ����ɃA�N�Z�X����O�̏�������
	va_start(list, fmt);

	pCur = fmt;
	for (; *pCur; ++pCur)
	{
		if (*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch (*pCur)
			{
			case 'd':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// �ψ����ɃA�N�Z�X���Ă��̕ϐ������o������
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}

		strcat(aBuf, aWk);
	}

	// �ψ����ɃA�N�Z�X������̏I������
	va_end(list);

#endif
	if ((strlen(m_aStr) + strlen(aBuf)) < sizeof m_aStr - 1)
	{
		strcat(m_aStr, aBuf);
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawDebug(void)
{
#ifdef _DEBUG
	if (m_bDisp)
	{
		RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 255, 255, 255));

		// �o�b�t�@�N���A
		memset(m_aStr, 0, sizeof m_aStr);
	}
#endif
}


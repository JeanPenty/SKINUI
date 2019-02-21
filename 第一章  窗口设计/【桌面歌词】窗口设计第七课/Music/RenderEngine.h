#ifndef RENDERENGINE_HEAD_FILE
#define RENDERENGINE_HEAD_FILE

#pragma once

class CRenderEngine
{
	//��������
public:
	static short 					m_cxSpacing;	//�ַ����
	static short 					m_cwBlank;		//�ո���Ŀ��

public:
	CRenderEngine(void);
	~CRenderEngine(void);

	//���ܺ���
public:
	//��ȡ���ֳߴ��С
	static SIZE GetDrawSize(HDC hDC,LPTSTR lpszText,UINT uFormat,bool& bHaveOffsety,short& yOffset);
	//�����ַ�
	static short CalcOffsety(HDC hDC);
	//ƫ����
	static bool IsYOffset(UINT uChar);
	//�Ƿ�����
	static bool IsDoubleByteChar(UINT uChar);
};

#endif
#ifndef MEMORY_DC_HEAD_FILE
#define MEMORY_DC_HEAD_FILE

#pragma once

#include "SkinUI.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�ڴ�DC��
class SKINUI_CLASS CMemoryDC : public CDC 
{
	//��������
private:
	CBitmap						m_bitmap;										// ��Ļ��λͼ
	CBitmap*					m_oldBitmap;									// ���λͼ����
	CDC*						m_pDC;											// ���澭������CDC
	CRect						m_rect;											// �����λ�������
	BOOL						m_bMemDC;										// �Ƿ�Ϊ�ڴ�DC

	//��������
public:
	//���캯������
	CMemoryDC(CDC* pDC, CRect rect = CRect(0,0,0,0), BOOL bCopyFirst = FALSE);

	//��������
	~CMemoryDC();

	// ����ʹ��ָ��
	CMemoryDC* operator->();

	// ����ʹ��ָ��
	operator CMemoryDC*();
};

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


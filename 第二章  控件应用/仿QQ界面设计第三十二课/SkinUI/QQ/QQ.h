// QQ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "GlobalUnits.h"
#include "Expression.h"
// CQQApp:
// �йش����ʵ�֣������ QQ.cpp
//

class CQQApp : public CWinApp
{
protected:
	CExpressionManager		m_ExpressionManager;

public:
	CQQApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQQApp theApp;
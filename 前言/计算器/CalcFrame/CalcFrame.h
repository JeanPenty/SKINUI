// CalcFrame.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCalcFrameApp:
// �йش����ʵ�֣������ CalcFrame.cpp
//

class CCalcFrameApp : public CWinApp
{
public:
	CCalcFrameApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCalcFrameApp theApp;
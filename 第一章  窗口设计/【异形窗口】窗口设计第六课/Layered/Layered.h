// Layered.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLayeredApp:
// �йش����ʵ�֣������ Layered.cpp
//

class CLayeredApp : public CWinApp
{
protected:
	ULONG_PTR			m_GdiplusToken;

public:
	CLayeredApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CLayeredApp theApp;
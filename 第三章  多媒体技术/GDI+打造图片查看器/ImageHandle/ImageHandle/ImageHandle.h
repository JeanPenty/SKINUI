// ImageHandle.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CImageHandleApp:
// �йش����ʵ�֣������ ImageHandle.cpp
//
class CImageHandleApp : public CWinApp
{
public:
	CImageHandleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CImageHandleApp theApp;

// 360Safe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy360SafeApp:
// �йش����ʵ�֣������ 360Safe.cpp
//

class CMy360SafeApp : public CWinAppEx
{
public:
	CMy360SafeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy360SafeApp theApp;
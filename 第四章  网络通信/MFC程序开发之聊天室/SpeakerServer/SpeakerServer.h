// SpeakerServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpeakerServerApp:
// �йش����ʵ�֣������ SpeakerServer.cpp
//

class CSpeakerServerApp : public CWinApp
{
public:
	CSpeakerServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSpeakerServerApp theApp;
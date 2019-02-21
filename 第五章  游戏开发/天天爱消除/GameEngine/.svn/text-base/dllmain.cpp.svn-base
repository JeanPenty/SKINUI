// dllmain.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE GameEngineDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// 如果使用 lpReserved，请将此移除
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("GameEngine.DLL 正在初始化!\n");
		
		// 扩展 DLL 一次性初始化
		if (!AfxInitExtensionModule(GameEngineDLL, hInstance))
			return 0;

		AfxInitRichEdit2();

		new CDynLinkLibrary(GameEngineDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("GameEngine.DLL 正在终止!\n");

		// 在调用析构函数之前终止该库
		AfxTermExtensionModule(GameEngineDLL);
	}
	return 1;   // 确定
}

// GMusic.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "GMusic.h"
#include "GMusicDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGMusicApp

BEGIN_MESSAGE_MAP(CGMusicApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGMusicApp 构造

CGMusicApp::CGMusicApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_szDefaultSkin[0]=0;
}


// 唯一的一个 CGMusicApp 对象

CGMusicApp theApp;


// CGMusicApp 初始化

BOOL CGMusicApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//_CrtSetBreakAlloc(241);
	CWinApp::InitInstance();

	AfxEnableControlContainer();

	RenderEngine->GetWorkDirectory(m_szDefaultSkin,MAX_PATH);
	StrCat(m_szDefaultSkin,TEXT("\\Res\\Skin\\1\\bk.jpg"));
	CFileFind find;
	if ( find.FindFile(m_szDefaultSkin) == FALSE )
	{
		AfxMessageBox(TEXT("资源加载失败"));
		return FALSE;
	}

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CGMusicDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

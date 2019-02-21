// Demo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Demo.h"

CGameEngine g_GameEngine;
//////////////////////////////////////////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	return g_GameEngine.InitInstance(hInstance,TEXT("Win32 引擎测试"));
}

//////////////////////////////////////////////////////////////////////////

CGameEngine::CGameEngine()
{
}

VOID CGameEngine::InitGameView( CD3DDevice * pD3DDevice, INT nWidth, INT nHeight )
{
	//创建控件
	cCRect rcCreate(0,0,0,0);
	m_btStart.ActiveWindow(rcCreate,WS_VISIBLE,1000,&m_VirtualEngine,NULL);
	m_btStart.SetButtonImage(TextureManager->InitWithTexture(pD3DDevice,TEXT("D:\\windows\\Documents\\Visual Studio 2008\\Projects\\GameEngine\\GamePeng\\res\\BT_CLOSE.png")));

	m_btStart.GetClientRect(rcCreate);
	m_btStart.SetWindowPos(100,100,0,0,SWP_NOSIZE);
	m_btStart.SetEvent(this,Button_selector(CGameEngine::OnStartGame));
}

void CGameEngine::OnStartGame()
{
	MessageBox(NULL,TEXT("start"),NULL,MB_OK);
}

LRESULT CGameEngine::WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	CWindowImpl::WindowProc(hWnd,uMessage,wParam,lParam);
	
	if ( uMessage == WM_DESTROY )
	{
		PostQuitMessage(0);
	}

	return ::DefWindowProc(hWnd,uMessage,wParam,lParam);
}

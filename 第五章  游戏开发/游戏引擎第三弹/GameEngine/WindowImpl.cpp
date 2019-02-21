// GameFrameView.cpp : 实现文件
//

#include "stdafx.h"
#include "WindowImpl.h"
#include "resource.h"

// CWindowImpl

//渲染消息
#define WM_D3D_RENDER				WM_USER+300							//渲染消息

//构造函数
CWindowImpl::CWindowImpl()
{
	//状态变量
	m_bInitD3D=false;
	m_hRenderThread=NULL;
	m_hOwnWnd = NULL;

	//帧数统计
	m_dwDrawBenchmark=0;
	m_dwDrawLastCount=0;
	m_dwDrawCurrentCount=0L;
}

//析构函数
CWindowImpl::~CWindowImpl()
{
}

//配置设备
VOID CWindowImpl::OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	//设置变量
	m_bInitD3D=true;

	//虚拟设备
	m_VirtualEngine.SetD3DDevice(&m_D3DDevice);

	//配置窗口
	InitGameView(pD3DDevice,nWidth,nHeight);

	StartRenderThread();

	return;
}

//丢失设备
VOID CWindowImpl::OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//重置设备
VOID CWindowImpl::OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//渲染窗口
VOID CWindowImpl::OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{	
	//动画驱动
	CartoonMovie();

	//绘画窗口
	DrawGameView(pD3DDevice,nWidth,nHeight);

	//虚拟框架
	m_VirtualEngine.DrawWindows(pD3DDevice);

#ifdef _DEBUG
	TCHAR szBuffer[MAX_PATH]=TEXT("");
	_sntprintf_s(szBuffer,CountArray(szBuffer),-1,TEXT("FPS:%ld"),pD3DDevice->CalcFPS());
	m_VirtualEngine.m_D3DDefaultFont.DrawText(pD3DDevice,szBuffer,cCRect(0,0,100,100),DT_LEFT|DT_TOP|DT_SINGLELINE,D3DCOLOR_XRGB(255,0,0));
#endif

	//设置变量
	m_dwDrawCurrentCount++;

	//累计判断
	if ((GetTickCount()-m_dwDrawBenchmark)>=1000L)
	{
		//设置变量
		m_dwDrawLastCount=m_dwDrawCurrentCount;

		//统计还原
		m_dwDrawCurrentCount=0L;
		m_dwDrawBenchmark=GetTickCount();
	}

	return;
}

//消息解释
LRESULT CWindowImpl::WindowProc(HWND hWnd,UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	switch ( nMessage )
	{
	case WM_SIZE:
		{
			int cx = LOWORD(lParam);
			int cy = HIWORD(lParam);
	
			//重置设备
			if (m_bInitD3D==false)
			{
				if ((cx>=0L)&&(cy>0L))
				{
					//配置环境
					if (m_D3DDirect.CreateD3DDirect()==false)
					{
						assert(FALSE);
						return false;
					}

					//创建设备
					if (m_D3DDevice.CreateD3DDevice(m_hOwnWnd,this)==false)
					{
						assert(FALSE);
						return false;
					}
				}
			}
			else
			{
				//重置设备
				m_D3DDevice.ResetD3DDevice();
			}

			RectifyControl(cx,cy);
			
			break;
		}
	case WM_CREATE:
		{
			m_hOwnWnd = hWnd;

			if ( m_hOwnWnd == NULL ) return false;
			
#ifdef _DEBUG
			HINSTANCE hInstance = (HINSTANCE)::GetWindowLong(m_hOwnWnd,GWL_HINSTANCE);
			//HINSTANCE hInstance = GetModuleHandle(GAME_ENGINE_DLL_NAME);
			
			m_TraceDialog.Create(hInstance,m_hOwnWnd);
			m_TraceDialog.ShowWindow(SW_SHOW);
#endif

			TraceService->TraceString(TraceLevel_Normal,TEXT("GameEngine Start\n"));

			D3DSound->CreateD3DSound(m_hOwnWnd);
			
			break;
		}
	case WM_PAINT:
		{
			if (m_bInitD3D==true) m_D3DDevice.RenderD3DDevice();

			break;
		}
	case WM_D3D_RENDER:
		{
			//渲染设备
			if (m_bInitD3D==true)
			{
				m_D3DDevice.RenderD3DDevice();
			}

			break;
		}
	}

	//虚拟框架
 	if (m_VirtualEngine.DefWindowProc(nMessage,wParam,lParam)==false)
 	{
 		return 0;
 	}

	return cCWnd::WindowProc(hWnd,nMessage,wParam,lParam);
}

//渲染线程
VOID CWindowImpl::StartRenderThread()
{
	//效验状态
	assert(m_hRenderThread==NULL);
	if (m_hRenderThread!=NULL) return;

	//创建线程
	m_hRenderThread=(HANDLE)::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)D3DRenderThread,(LPVOID)m_hOwnWnd,0L,0L);
	//m_hRenderThread=(HANDLE)::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)D3DRenderThread,(CWindowImpl*)this,0L,0L);

	return;
}

//渲染消息
void CWindowImpl::OnMessageD3DRender()
{
	//渲染设备
	if (m_bInitD3D==true)
	{
		m_D3DDevice.RenderD3DDevice();
	}
}

//渲染线程
VOID CWindowImpl::D3DRenderThread(LPVOID pThreadData)
{
	//效验参数
	assert(pThreadData!=NULL);
	if (pThreadData==NULL) return;

	CWindowImpl*pGameFrameView = (CWindowImpl*)pThreadData;

	int nPaintingTime = 0;
	
	//渲染循环
	while (TRUE)
	{
 		//渲染等待
 		if( nPaintingTime >= 5 )
 		{
 			Sleep(1);
 		}
 		else
 		{
 			Sleep(5 - nPaintingTime);
 		}

		//发送消息
		int nTime = timeGetTime();

		//pGameFrameView->OnMessageD3DRender();

		::SendMessage((HWND)pThreadData,WM_D3D_RENDER,0L,0L);

 		nPaintingTime = timeGetTime() - nTime;
	}

	return;
}

VOID CWindowImpl::SetLogFile( LPCTSTR lpszNameFile )
{
	TraceService->SetLogFile(lpszNameFile);
}

INT CWindowImpl::InitInstance(HINSTANCE hInstance,LPCTSTR lpszWindowName)
{
	//初始化RichEdit
	InitRichEdit;

	//局中显示窗口
	int nWidth=800 + GetSystemMetrics(SM_CXFIXEDFRAME)*2;
	int nHeight=600 + GetSystemMetrics(SM_CYFIXEDFRAME)*2 + GetSystemMetrics(SM_CYCAPTION);

	if( cCWnd::CreateEx(hInstance,0,TEXT("EngineFrame"),lpszWindowName,WS_OVERLAPPEDWINDOW,
		(GetSystemMetrics(SM_CXSCREEN)-nWidth)/2, (GetSystemMetrics(SM_CYSCREEN)-nHeight)/2, nWidth, nHeight,NULL,NULL) == FALSE )
	{
		return 0;
	}

	//显示窗口
	ShowWindow(SW_SHOW);

	//主消息循环:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

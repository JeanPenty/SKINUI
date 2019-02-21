// GameFrameView.cpp : 实现文件
//

#include "stdafx.h"
#include "GameFrameView.h"
#include "resource.h"
#include "D3DSound.h"

// CGameFrameView

IMPLEMENT_DYNAMIC(CGameFrameView, CWnd)

//渲染消息
#define WM_D3D_RENDER				WM_USER+300							//渲染消息

//构造函数
CGameFrameView::CGameFrameView(UINT nIDTemplate,CWnd* pParent): CDialog(nIDTemplate, pParent)
{
	//状态变量
	m_bInitD3D=false;
	m_hRenderThread=NULL;

	//帧数统计
	m_dwDrawBenchmark=0;
	m_dwDrawLastCount=0;
	m_dwDrawCurrentCount=0L;
}

//析构函数
CGameFrameView::~CGameFrameView()
{
}


BEGIN_MESSAGE_MAP(CGameFrameView, CDialog)

	//系统消息
	ON_WM_SIZE()
	ON_WM_PAINT()

	//自定消息
	ON_MESSAGE(WM_D3D_RENDER, OnMessageD3DRender)

	ON_WM_CREATE()
END_MESSAGE_MAP()

//配置设备
VOID CGameFrameView::OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
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
VOID CGameFrameView::OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//重置设备
VOID CGameFrameView::OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//渲染窗口
VOID CGameFrameView::OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{	
	//动画驱动
	CartoonMovie();

	//绘画窗口
	DrawGameView(pD3DDevice,nWidth,nHeight);

	//虚拟框架
	m_VirtualEngine.DrawWindows(pD3DDevice);

#ifdef _DEBUG
	CString str;
	str.Format(TEXT("FPS:%ld"),pD3DDevice->CalcFPS());
	m_VirtualEngine.m_D3DDefaultFont.DrawText(pD3DDevice,str,CRect(0,0,100,100),DT_LEFT|DT_TOP|DT_SINGLELINE,D3DCOLOR_XRGB(255,0,0));
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
BOOL CGameFrameView::PreTranslateMessage(MSG * pMsg)
{
	//虚拟框架
	if (m_VirtualEngine.PreTranslateMessage(pMsg->message,pMsg->wParam,pMsg->lParam)==true)
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//消息解释
LRESULT CGameFrameView::DefWindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	//虚拟框架
	if (m_VirtualEngine.DefWindowProc(nMessage,wParam,lParam)==true)
	{
		return 0L;
	}

	return __super::DefWindowProc(nMessage,wParam,lParam);
}

//渲染线程
VOID CGameFrameView::StartRenderThread()
{
	//效验状态
	ASSERT(m_hRenderThread==NULL);
	if (m_hRenderThread!=NULL) return;

	//创建线程
	m_hRenderThread=(HANDLE)::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)D3DRenderThread,(LPVOID)(m_hWnd),0L,0L);
	//m_hRenderThread=(HANDLE)::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)D3DRenderThread,(CGameFrameView*)(this),0L,0L);

	return;
}
//绘画函数
VOID CGameFrameView::OnPaint()
{
	CPaintDC dc(this);

	//渲染设备
	if (m_bInitD3D==true) m_D3DDevice.RenderD3DDevice();

	return;
}

//位置变化
VOID CGameFrameView::OnSize(UINT nType, INT cx, INT cy)
{
	//重置设备
	if (m_bInitD3D==false)
	{
		if ((cx>=0L)&&(cy>0L))
		{
			//配置环境
			if (m_D3DDirect.CreateD3DDirect()==false)
			{
				ASSERT(FALSE);
				return;
			}

			//创建设备
			if (m_D3DDevice.CreateD3DDevice(m_hWnd,this)==false)
			{
				ASSERT(FALSE);
				return;
			}
		}
	}
	else
	{
		//重置设备
		m_D3DDevice.ResetD3DDevice();
	}

	RectifyControl(cx,cy);

	//CDialog::OnSize(nType, cx, cy);
}

//创建消息
INT CGameFrameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifdef _DEBUG
	m_TraceDialog.Create(IDD_DEBUG);
	m_TraceDialog.ShowWindow(SW_SHOW);
#endif

	TraceService->TraceString(TraceLevel_Normal,TEXT("GameEngine Start\n"));

	D3DSound->CreateD3DSound(GetSafeHwnd());

	return 0;
}

//渲染消息
LRESULT CGameFrameView::OnMessageD3DRender(WPARAM wParam, LPARAM lParam)
{
	//渲染设备
	if (m_bInitD3D==true)
	{
		m_D3DDevice.RenderD3DDevice();
	}

	return 0L;
}

//渲染线程
VOID CGameFrameView::D3DRenderThread(LPVOID pThreadData)
{
	//效验参数
	ASSERT(pThreadData!=NULL);
	if (pThreadData==NULL) return;

	//CGameFrameView *pGameFrameView = (CGameFrameView*)pThreadData;

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


		//pGameFrameView->OnMessageD3DRender(0,0);
	
		::SendMessage((HWND)pThreadData,WM_D3D_RENDER,0L,0L);
		nPaintingTime = timeGetTime() - nTime;
	}

	return;
}

VOID CGameFrameView::SetLogFile( LPCTSTR lpszNameFile )
{
	TraceService->SetLogFile(lpszNameFile);
}

// GameFrameView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameFrameView.h"
#include "resource.h"
#include "D3DSound.h"

// CGameFrameView

IMPLEMENT_DYNAMIC(CGameFrameView, CWnd)

//��Ⱦ��Ϣ
#define WM_D3D_RENDER				WM_USER+300							//��Ⱦ��Ϣ

//���캯��
CGameFrameView::CGameFrameView(UINT nIDTemplate,CWnd* pParent): CDialog(nIDTemplate, pParent)
{
	//״̬����
	m_bInitD3D=false;
	m_hRenderThread=NULL;

	//֡��ͳ��
	m_dwDrawBenchmark=0;
	m_dwDrawLastCount=0;
	m_dwDrawCurrentCount=0L;
}

//��������
CGameFrameView::~CGameFrameView()
{
}


BEGIN_MESSAGE_MAP(CGameFrameView, CDialog)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_PAINT()

	//�Զ���Ϣ
	ON_MESSAGE(WM_D3D_RENDER, OnMessageD3DRender)

	ON_WM_CREATE()
END_MESSAGE_MAP()

//�����豸
VOID CGameFrameView::OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	//���ñ���
	m_bInitD3D=true;

	//�����豸
	m_VirtualEngine.SetD3DDevice(&m_D3DDevice);

	//���ô���
	InitGameView(pD3DDevice,nWidth,nHeight);

	StartRenderThread();

	return;
}

//��ʧ�豸
VOID CGameFrameView::OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//�����豸
VOID CGameFrameView::OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//��Ⱦ����
VOID CGameFrameView::OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{	
	//��������
	CartoonMovie();

	//�滭����
	DrawGameView(pD3DDevice,nWidth,nHeight);

	//������
	m_VirtualEngine.DrawWindows(pD3DDevice);

#ifdef _DEBUG
	CString str;
	str.Format(TEXT("FPS:%ld"),pD3DDevice->CalcFPS());
	m_VirtualEngine.m_D3DDefaultFont.DrawText(pD3DDevice,str,CRect(0,0,100,100),DT_LEFT|DT_TOP|DT_SINGLELINE,D3DCOLOR_XRGB(255,0,0));
#endif

	//���ñ���
	m_dwDrawCurrentCount++;

	//�ۼ��ж�
	if ((GetTickCount()-m_dwDrawBenchmark)>=1000L)
	{
		//���ñ���
		m_dwDrawLastCount=m_dwDrawCurrentCount;

		//ͳ�ƻ�ԭ
		m_dwDrawCurrentCount=0L;
		m_dwDrawBenchmark=GetTickCount();
	}

	return;
}

//��Ϣ����
BOOL CGameFrameView::PreTranslateMessage(MSG * pMsg)
{
	//������
	if (m_VirtualEngine.PreTranslateMessage(pMsg->message,pMsg->wParam,pMsg->lParam)==true)
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//��Ϣ����
LRESULT CGameFrameView::DefWindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	//������
	if (m_VirtualEngine.DefWindowProc(nMessage,wParam,lParam)==true)
	{
		return 0L;
	}

	return __super::DefWindowProc(nMessage,wParam,lParam);
}

//��Ⱦ�߳�
VOID CGameFrameView::StartRenderThread()
{
	//Ч��״̬
	ASSERT(m_hRenderThread==NULL);
	if (m_hRenderThread!=NULL) return;

	//�����߳�
	m_hRenderThread=(HANDLE)::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)D3DRenderThread,(LPVOID)(m_hWnd),0L,0L);
	//m_hRenderThread=(HANDLE)::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)D3DRenderThread,(CGameFrameView*)(this),0L,0L);

	return;
}
//�滭����
VOID CGameFrameView::OnPaint()
{
	CPaintDC dc(this);

	//��Ⱦ�豸
	if (m_bInitD3D==true) m_D3DDevice.RenderD3DDevice();

	return;
}

//λ�ñ仯
VOID CGameFrameView::OnSize(UINT nType, INT cx, INT cy)
{
	//�����豸
	if (m_bInitD3D==false)
	{
		if ((cx>=0L)&&(cy>0L))
		{
			//���û���
			if (m_D3DDirect.CreateD3DDirect()==false)
			{
				ASSERT(FALSE);
				return;
			}

			//�����豸
			if (m_D3DDevice.CreateD3DDevice(m_hWnd,this)==false)
			{
				ASSERT(FALSE);
				return;
			}
		}
	}
	else
	{
		//�����豸
		m_D3DDevice.ResetD3DDevice();
	}

	RectifyControl(cx,cy);

	//CDialog::OnSize(nType, cx, cy);
}

//������Ϣ
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

//��Ⱦ��Ϣ
LRESULT CGameFrameView::OnMessageD3DRender(WPARAM wParam, LPARAM lParam)
{
	//��Ⱦ�豸
	if (m_bInitD3D==true)
	{
		m_D3DDevice.RenderD3DDevice();
	}

	return 0L;
}

//��Ⱦ�߳�
VOID CGameFrameView::D3DRenderThread(LPVOID pThreadData)
{
	//Ч�����
	ASSERT(pThreadData!=NULL);
	if (pThreadData==NULL) return;

	//CGameFrameView *pGameFrameView = (CGameFrameView*)pThreadData;

	int nPaintingTime = 0;
	
	//��Ⱦѭ��
	while (TRUE)
	{
		//��Ⱦ�ȴ�
		if( nPaintingTime >= 5 )
		{
			Sleep(1);
		}
		else
		{
			Sleep(5 - nPaintingTime);
		}

		//������Ϣ
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

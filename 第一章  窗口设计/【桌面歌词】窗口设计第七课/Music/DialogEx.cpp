// DialogEx.cpp : 实现文件
//

#include "stdafx.h"
#include "DialogEx.h"
#include <atlimage.h>

// CDialogEx 对话框
#define		IDC_WND_MAX			WM_USER+0x01
#define		IDC_WND_MIN			WM_USER+0x02

//边框宽度
#define		BORDERWIDTH			3

IMPLEMENT_DYNAMIC(CDialogEx, CDialog)

CDialogEx::CDialogEx(UINT nIDTemplate, CWnd * pParentWnd) 
	: CDialog(nIDTemplate,pParentWnd)
{
	m_bIsInit = false;
	m_bIsZoomed = false;
	m_bExtrude = true;
}

CDialogEx::~CDialogEx()
{
}

void CDialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogEx, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDialogEx 消息处理程序
BOOL CDialogEx::OnInitDialog()
{
	CDialog::OnInitDialog();

	//设置属性,去除标题栏和边框
	RemoveBorder();

	CRect rcControl(0,0,0,0);

	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDCANCEL);
	m_btClose.SetButtonImage(AfxGetInstanceHandle(),TEXT("CLOSESSIZE"));

	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDC_WND_MAX);
	m_btMax.SetButtonImage(AfxGetInstanceHandle(),TEXT("MAXSSIZE"));
	
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDC_WND_MIN);
	m_btMin.SetButtonImage(AfxGetInstanceHandle(),TEXT("MINSSIZE"));

	m_bIsInit = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDialogEx::RemoveBorder()
{
	DWORD dwStyle = GetStyle();
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	dwNewStyle&=dwStyle;
	SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);
	DWORD dwExStyle = GetExStyle();
	DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle&=dwExStyle;
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);
}

bool CDialogEx::LoadBackSkin( LPCTSTR pszResourcePath )
{
	return m_ImageBack.LoadImage(pszResourcePath);
}

bool CDialogEx::LoadBackSkin( HINSTANCE hInstance, LPCTSTR pszResourceName )
{
	return m_ImageBack.LoadImage(hInstance,pszResourceName);
}

void CDialogEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CDC BufferDC;
	CBitmap BufferBmp;
	BufferDC.CreateCompatibleDC(&dc);
	BufferBmp.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	BufferDC.SelectObject(&BufferBmp);

	BufferDC.FillSolidRect(&rcClient,RGB(255,255,255));

 	m_ImageBack.DrawImage(&BufferDC,0,0,rcClient.Width(),rcClient.Height());
 	
	//此处划分客户区，采用缓冲机制进行Client绘制
	CRect rcNewClient;
	rcNewClient.left = m_bExtrude ? BORDERWIDTH : 0;
	rcNewClient.top = m_bExtrude ? BORDERWIDTH : 0;
	rcNewClient.right = rcClient.right-(m_bExtrude ? BORDERWIDTH*2 : 0);
	rcNewClient.bottom = rcClient.bottom-(m_bExtrude ? BORDERWIDTH*2 : 0);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcNewClient.Width(),rcNewClient.Height(),32);

	//创建 DC
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	pBufferDC->SetBkMode(TRANSPARENT);

	// 	PrintWindow(pBufferDC,PW_CLIENTONLY);
	m_ImageBack.DrawImage(pBufferDC,0,0,rcNewClient.Width(),rcNewClient.Height(),rcNewClient.left,rcNewClient.top,rcNewClient.Width(),rcNewClient.Height());

	BufferDC.SelectObject(BufferBmp);
	
	//绘制客户区
	OnClientDraw(pBufferDC,rcNewClient.Width(),rcNewClient.Height());

	//绘画界面
	BufferDC.BitBlt(0,0,rcNewClient.Width(),rcNewClient.Height(),pBufferDC,0,0,SRCCOPY);

	//绘画界面
	dc.BitBlt(rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//清理资源
	BufferDC.DeleteDC();
	BufferBmp.DeleteObject();
}

void CDialogEx::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if( !m_bIsInit ) return;

	//变量定义
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

	//锁定屏幕
	LockWindowUpdate();

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);

	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btClose,NULL,cx-rcButton.Width()-2,2,0,0,uFlags);
	DeferWindowPos(hDwp,m_btMax,NULL,cx-rcButton.Width()*2-2,2,0,0,uFlags);
	DeferWindowPos(hDwp,m_btMin,NULL,cx-rcButton.Width()*3-2,2,0,0,uFlags);

	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	//解除锁定
	UnlockWindowUpdate();
}

BOOL CDialogEx::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_WND_MAX:	//最大化消息
		{
			//如果子类没有自己的操作就执行默认操作
			if( !OnMaxSize())
			{
				static CRect rcClient(0,0,0,0);

				if ( m_bIsZoomed )
				{
					MoveWindow(&rcClient);

					m_bIsZoomed = false;
				}
				else 
				{
					GetWindowRect(&rcClient);

					CRect rc;
					SystemParametersInfo(SPI_GETWORKAREA,0,&rc,0); 
					MoveWindow(&rc);

					m_bIsZoomed = true;
				}
			}

			break;
		}
	case IDC_WND_MIN:	//最小化消息
		{
			ShowWindow(SW_MINIMIZE);
			break;
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CDialogEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	//模拟标题
	if (!m_bIsZoomed)
	{
		//模拟标题
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

		return;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

LRESULT CDialogEx::OnNcHitTest(CPoint point)
{
	if( m_bExtrude )
	{
		CRect rcWindow;
		GetWindowRect(&rcWindow);

		if ((point.x <= rcWindow.left+BORDERWIDTH) && (point.y>BORDERWIDTH) && (point.y<rcWindow.bottom-BORDERWIDTH*2) )
			return HTLEFT;
		else if ((point.x >= rcWindow.right-BORDERWIDTH) && (point.y>BORDERWIDTH) && (point.y<rcWindow.bottom-BORDERWIDTH*2) )
			return HTRIGHT;
		else if ((point.y <= rcWindow.top+BORDERWIDTH) && (point.x>BORDERWIDTH) && (point.x<rcWindow.right-BORDERWIDTH*2))
			return HTTOP;
		else if ((point.y >= rcWindow.bottom-BORDERWIDTH) && (point.x>BORDERWIDTH) && (point.x<rcWindow.right-BORDERWIDTH*2))
			return HTBOTTOM;
		else if ((point.x <= rcWindow.left+BORDERWIDTH*2) && (point.y <= rcWindow.top+BORDERWIDTH*2))
			return HTTOPLEFT;
		else if ((point.x >= rcWindow.right-BORDERWIDTH*2) && (point.y <= rcWindow.top+BORDERWIDTH*2))
			return HTTOPRIGHT;
		else if ((point.x <= rcWindow.left+BORDERWIDTH*2) && (point.y >= rcWindow.bottom-BORDERWIDTH*2))
			return HTBOTTOMLEFT;
		else if ((point.x >= rcWindow.right-BORDERWIDTH*2) && (point.y >= rcWindow.bottom-BORDERWIDTH*2))
			return HTBOTTOMRIGHT;
		else
			return CWnd::OnNcHitTest(point);

		return 0;
	}
	else
		return CDialog::OnNcHitTest(point);
}

void CDialogEx::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if( m_bExtrude )
	{
		if (nHitTest == HTTOP)		
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTBOTTOM)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTLEFT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTRIGHT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTTOPLEFT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTTOPRIGHT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTBOTTOMLEFT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTBOTTOMRIGHT)
			SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest==HTCAPTION)
			SendMessage(WM_SYSCOMMAND, SC_MOVE | 4, MAKELPARAM(point.x, point.y));
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}

// GoBangDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GoBang.h"
#include "GoBangDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGoBangDlg 对话框
CGoBangDlg::CGoBangDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGoBangDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGoBangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGoBangDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CGoBangDlg 消息处理程序

BOOL CGoBangDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("MANUAL_BACK"));
	if ( m_ImageBack.IsNull() ) return FALSE;
	
	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

	//棋盘控制
	m_ChessBorad.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(32,35,515,515),this,NULL);
	m_ChessBorad.CleanChess();
	m_ChessBorad.SetSelectMode(SM_NO_SELECT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGoBangDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		m_ImageBack.BitBlt(dc,0,0);

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGoBangDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGoBangDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CDialog::OnLButtonDown(nFlags, point);
}

void CGoBangDlg::SetOption( bool bWhiteColor,bool bIGo )
{
	m_ChessBorad.SetOption(bWhiteColor,bIGo);
}

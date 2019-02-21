// LandmineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Landmine.h"
#include "LandmineDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLandmineDlg 对话框
CLandmineDlg::CLandmineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLandmineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLandmineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLandmineDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_START, &CLandmineDlg::OnStart)
	ON_COMMAND(ID_LOW, &CLandmineDlg::OnLow)
	ON_COMMAND(ID_MID, &CLandmineDlg::OnMid)
	ON_COMMAND(ID_HIGH, &CLandmineDlg::OnHigh)
	ON_COMMAND(ID_CUSTOM, &CLandmineDlg::OnCustom)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLandmineDlg 消息处理程序

BOOL CLandmineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_MenuBar.LoadMenu(IDR_MENU1); 
	SetMenu(&m_MenuBar);

	m_GameFrame.OnInitResource();
	m_GameFrame.SetChessMap(9,9,10);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLandmineDlg::OnPaint()
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
		
		CRect rcClient;
		GetClientRect(&rcClient);

		m_GameFrame.OnRender(&dc,rcClient.Width(),rcClient.Height());

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLandmineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLandmineDlg::OnStart()
{
	m_GameFrame.ReStartGame();
	Invalidate(FALSE);
}

void CLandmineDlg::OnLow()
{
	m_GameFrame.SetChessMap(9,9,10);
	Invalidate(FALSE);
}

void CLandmineDlg::OnMid()
{
	m_GameFrame.SetChessMap(16,16,40);
	Invalidate(FALSE);
}

void CLandmineDlg::OnHigh()
{
	m_GameFrame.SetChessMap(30,16,99);
	Invalidate(FALSE);
}

void CLandmineDlg::OnCustom()
{
	COptionDlg OptionDlg;
	if ( OptionDlg.DoModal() == IDOK )
	{
		m_GameFrame.SetChessMap(OptionDlg.m_nRowCount,OptionDlg.m_nColCount,OptionDlg.m_nMineCount);
		Invalidate(FALSE);
	}
}

void CLandmineDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_GameFrame.OnLButtonDown(point);

	CDialog::OnLButtonDown(nFlags, point);
}

void CLandmineDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_GameFrame.OnRButtonDown(point);

	CDialog::OnRButtonDown(nFlags, point);
}

void CLandmineDlg::OnTimer(UINT_PTR nIDEvent)
{
	m_GameFrame.OnTimer(nIDEvent);

	CDialog::OnTimer(nIDEvent);
}

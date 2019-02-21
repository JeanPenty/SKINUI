
// 360SafeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "360Safe.h"
#include "360SafeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy360SafeDlg 对话框




CMy360SafeDlg::CMy360SafeDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CMy360SafeDlg::IDD,TEXT("360Safe.xml"), pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy360SafeDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy360SafeDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(5006,OnBnClickCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMy360SafeDlg 消息处理程序

BOOL CMy360SafeDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	((CSkinTabCtrl*)GetDlgItem(5900))->SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy360SafeDlg::OnPaint()
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
		CSkinDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy360SafeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy360SafeDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	__super::OnLButtonDown(nFlags,point);
}

void CMy360SafeDlg::OnBnClickCheck()
{
	for (int i=2;i<7;i++)
	{
		GetString(i)->bVisible = false;
	}

	GetString(7)->bVisible = true;
	GetImage(7)->bVisible = false;

	GetDlgItem(5006)->ShowWindow(SW_HIDE);

	Invalidate(FALSE);
}


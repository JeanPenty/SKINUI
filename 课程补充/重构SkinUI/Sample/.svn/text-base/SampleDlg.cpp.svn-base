
// SampleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sample.h"
#include "SampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSampleDlg 对话框




CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CSampleDlg::IDD,TEXT("Sample.xml"), pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSampleDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CSampleDlg 消息处理程序

BOOL CSampleDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

 	CSkinComboBox*pComBox = (CSkinComboBox*)GetDlgItem(5006);
	if( CHECK_HWND(pComBox) )
	{
		pComBox->SetItemHeight(-1,23);
		pComBox->AddString(TEXT("这是程序添加的"));
		pComBox->SetCurSel(0);
	}

	pComBox = (CSkinComboBox*)GetDlgItem(5007);
	if( CHECK_HWND(pComBox) )
	{
		pComBox->SetItemHeight(-1,23);
		pComBox->SetCurSel(0);
	}

	CSkinListCtrl*pListCtrl = (CSkinListCtrl*)GetDlgItem(5010);
	//if( CHECK_HWND(pListCtrl) )
	{
		pListCtrl->InsertColumn( 0, TEXT("文件名"), LVCFMT_LEFT, 150 );
		pListCtrl->InsertColumn( 1, TEXT("大小"), LVCFMT_LEFT, 100 );
		pListCtrl->InsertColumn( 2, TEXT("修改时间"), LVCFMT_LEFT, 150 );

		for (int i=0;i<8;i++)
		{
			pListCtrl->InsertItem(i,TEXT("跟我学MFC.zip"));
			pListCtrl->SetItemText(i,1,TEXT("126MB"));
			pListCtrl->SetItemText(i,2,TEXT("2013-10-17 18:13"));
		}

		pListCtrl->InsertImage(0,TEXT("Res\\ListCtrl\\DocType.png"));
		pListCtrl->InsertImage(1,TEXT("Res\\ListCtrl\\FolderType.png"));
		pListCtrl->InsertImage(2,TEXT("Res\\ListCtrl\\ImgType.png"));
		pListCtrl->InsertImage(3,TEXT("Res\\ListCtrl\\PdfType.png"));
		pListCtrl->InsertImage(4,TEXT("Res\\ListCtrl\\PptType.png"));
		pListCtrl->InsertImage(5,TEXT("Res\\ListCtrl\\RarType.png"));
		pListCtrl->InsertImage(7,TEXT("Res\\ListCtrl\\RarType.png"));
	}

	SetTimer(0,50,NULL);

 	TCHAR szWorkDirectory[MAX_PATH]={0};
 	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);
 	StrCat(szWorkDirectory,TEXT("\\Res\\Flash\\noon.swf"));
 
 	CRect rcClient;
 	GetClientRect(&rcClient);
// 
// 	m_FlashControl.Create(NULL,WS_VISIBLE|WS_VISIBLE,CRect(0,0,0,0),this,3000);
// 	//m_FlashControl.Init(this);
// 	m_FlashControl.LoadMovie(0,szWorkDirectory);
// 	m_FlashControl.Play();
// 	m_FlashControl.SetWindowPos(NULL,rcClient.Width()-250,100,rcClient.Width()-15,250,SWP_NOACTIVATE);

// 	CFlashControl* pFlashControl = (CFlashControl*)GetDlgItem(5631);
// 	pFlashControl->LoadMovie(0,szWorkDirectory);
// 	pFlashControl->Play();
// 	pFlashControl->SetWindowPos(NULL,rcClient.Width()-250,100,rcClient.Width()-15,250,SWP_NOACTIVATE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSampleDlg::OnTimer( UINT_PTR nIDEvent )
{
	if ( nIDEvent == 0 )
	{
		((CSkinProgressCtrl*)GetDlgItem(5011))->StepIt();
		((CSkinProgressCtrl*)GetDlgItem(5012))->StepIt();
	}
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSampleDlg::OnPaint()
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
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSampleDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	//if( !IsZoomed() )
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

void CSampleDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	__super::OnRButtonDown(nFlags,point);

	//构造菜单
	CSkinMenu MainMenu;
	MainMenu.CreatePopupMenu();

	MainMenu.AppendMenu(4000,TEXT("子节点"),0,0,MF_POPUP);
	MainMenu.AppendMenu(4001,TEXT("子节点"),TEXT("Res\\Button\\message.png"));

 	MainMenu.SetMenuBarImage(TEXT("Res\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
 	MainMenu.SetMenuBackImage(TEXT("Res\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
 	MainMenu.SetMenuHovenImage(TEXT("Res\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
 	MainMenu.SetSeparatorImage(TEXT("Res\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
 	MainMenu.SetCheckImage(TEXT("Res\\Menu\\menu_check.png"));
 	MainMenu.SetArrowImage(TEXT("Res\\Menu\\menu_arrow.png"));

	//MainMenu.SetFrameColor(RGB(255,0,0));
	//显示菜单
	MainMenu.TrackPopupMenu(this);
}


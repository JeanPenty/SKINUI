// ControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "ControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CControlDlg 对话框




CControlDlg::CControlDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsInit = false;
}

void CControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	//DDX_Control(pDX,IDC_LISTBAR,m_ListBoxEx);
}

BEGIN_MESSAGE_MAP(CControlDlg, CSkinDialog)
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_MESSAGE(WM_ACTIVE_ITEM,OnActiveItem)
END_MESSAGE_MAP()


// CControlDlg 消息处理程序

BOOL CControlDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetExtrude(true);
	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("BACK_VIEW"));
	m_ImageLogo.LoadImage(AfxGetInstanceHandle(),TEXT("LOGO"));


	HDC hParentDC = GetBackDC();
	CRect rcControl(0,0,0,0);

	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDCANCEL);
	m_btClose.SetBackImage(TEXT("Res\\Button\\btn_close_normal.png"),TEXT("Res\\Button\\btn_close_highlight.png"),TEXT("Res\\Button\\btn_close_down.png"),TEXT("Res\\Button\\btn_close_normal.png"));
	m_btClose.SetButtonType(en_PushButton);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(39,20);

	m_btMinSize.Create(NULL,WS_CHILD|WS_VISIBLE,rcControl,this,IDCANCEL);
	m_btMinSize.SetBackImage(TEXT("Res\\Button\\btn_mini_normal.png"),TEXT("Res\\Button\\btn_mini_highlight.png"),TEXT("Res\\Button\\btn_mini_down.png"),TEXT("Res\\Button\\btn_mini_normal.png"));
	m_btMinSize.SetButtonType(en_PushButton);
	m_btMinSize.SetParentBack(hParentDC);
	m_btMinSize.SetSize(28,20);

	m_ListBoxEx.Create(WS_CHILD|WS_VISIBLE| LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS,rcControl,this,IDC_LISTBAR);
	m_ListBoxEx.SetItemHeight(26);
	
	m_ListBoxEx.AddString(TEXT("Button"));
	m_ListBoxEx.AddString(TEXT("Edit"));
	m_ListBoxEx.AddString(TEXT("Combo Box"));
	m_ListBoxEx.AddString(TEXT("List Box"));
	m_ListBoxEx.AddString(TEXT("Scroll Bar"));
	m_ListBoxEx.AddString(TEXT("Slider Control"));
	m_ListBoxEx.AddString(TEXT("Progress Control"));
	m_ListBoxEx.AddString(TEXT("List Control"));
	m_ListBoxEx.AddString(TEXT("Tree Control"));
	m_ListBoxEx.AddString(TEXT("Tab Control"));
	m_ListBoxEx.AddString(TEXT("Rich Edit"));
	m_ListBoxEx.AddString(TEXT("Menu"));
	m_ListBoxEx.AddString(TEXT("Hot Key"));
	m_ListBoxEx.AddString(TEXT("IP Address Control"));


	//设置变量
	m_wActiveIndex=0xFF;

	//基本配置
	m_ArrayControl.push_back(&m_ButtonDlg);
	m_ArrayControl.push_back(&m_EditDlg);
	m_ArrayControl.push_back(&m_ComBoxDlg);
	m_ArrayControl.push_back(&m_ListBoxDlg);
	m_ArrayControl.push_back(&m_ScrollDlg);
	m_ArrayControl.push_back(&m_SliderDlg);
	m_ArrayControl.push_back(&m_ProgressDlg);
	m_ArrayControl.push_back(&m_ListCtrlDlg);
	m_ArrayControl.push_back(&m_TreeCtrlDlg);
	m_ArrayControl.push_back(&m_TabCtrlDlg);
	m_ArrayControl.push_back(&m_RichEditDlg);
	m_ArrayControl.push_back(&m_MenuDlg);

	//激活子项
	ActiveOptionItem(m_ArrayControl.size()-1);
	m_ListBoxEx.SetCurSel(m_ArrayControl.size()-1);

	m_bIsInit = true;

	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CControlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CSkinDialog::OnLButtonDown(nFlags, point);
}

void CControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CSkinDialog::OnSize(nType, cx, cy);

	if( !m_bIsInit ) return;

	RectifyControl(cx, cy);
}

void CControlDlg::RectifyControl( int cx, int cy )
{
	//变量定义
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//锁定屏幕
	LockWindowUpdate();

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);

	CRect rcButton;
	m_btClose.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btClose,NULL,cx-rcButton.Width(),0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMinSize,NULL,cx-rcButton.Width()-28,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_ListBoxEx,NULL,1,85,130,cy-86,uFlags);

	if( m_ArrayControl[m_wActiveIndex] != NULL )
	{
		DeferWindowPos(hDwp,m_ArrayControl[m_wActiveIndex]->GetSafeHwnd(),NULL,131,85,cx-135,cy-86,uFlags);	
	}

	EndDeferWindowPos(hDwp);

	//重画界面
	Invalidate(FALSE);
	UpdateWindow();

	//解除锁定
	UnlockWindowUpdate();
}

LRESULT CControlDlg::OnActiveItem( WPARAM wParam,LPARAM lParam )
{
	int nItem = int(wParam);

	ActiveOptionItem(nItem);

	return 0L;
}

//激活配置
bool CControlDlg::ActiveOptionItem( WORD wIndex )
{
	//判断状态
	if (m_wActiveIndex==wIndex)
	{
		m_ArrayControl[m_wActiveIndex]->SetFocus();
		return true;
	}

 	if ( wIndex+1 > m_ArrayControl.size() )
 	{
 		return true;
 	}

	//保存旧项
	CDlgControlItem * pControlItem=NULL;
	if (m_wActiveIndex<m_ArrayControl.size()) pControlItem=m_ArrayControl[m_wActiveIndex];

	//创建新项
	m_wActiveIndex=wIndex;

	CRect rcClient,rcItemRect;
	GetWindowRect(&rcClient);

	rcItemRect.left = 131;
	rcItemRect.top = 85;
	rcItemRect.right = rcClient.Width()-1;
	rcItemRect.bottom = rcClient.Height()-1;

	CString strItemText;
	m_ListBoxEx.GetText(m_wActiveIndex,strItemText);
	m_ArrayControl[m_wActiveIndex]->ShowControlItem(rcItemRect,this,strItemText);

	//激活新项
	m_ArrayControl[m_wActiveIndex]->SetFocus();
	if (pControlItem!=NULL) pControlItem->ShowWindow(SW_HIDE);

	if ( wIndex == 7 ) 
	{
		SetWindowPos(NULL,0,0,1024,730,SWP_NOMOVE);
		CenterWindow();
	}
	else if ( wIndex == 8 ) 
	{
		SetWindowPos(NULL,0,0,850,450,SWP_NOMOVE);
		CenterWindow();
	}
	else if ( wIndex == 10 ) 
	{
		SetWindowPos(NULL,0,0,950,450,SWP_NOMOVE);
		CenterWindow();
	}
	else 
		SetWindowPos(NULL,0,0,625,450,SWP_NOMOVE);

	return true;
}

void CControlDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	m_ImageBack.Draw(pDC,0,0,nWidth,nHeight,2,86,4,4);
	m_ImageLogo.DrawImage(pDC,10,5,20,20);
}

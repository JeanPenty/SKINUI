// TabCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TabCtrlDlg.h"
#include "Resource.h"

// CTabCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CTabCtrlDlg, CDlgControlItem)

CTabCtrlDlg::CTabCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_TAB, pParent)
{

}

CTabCtrlDlg::~CTabCtrlDlg()
{
}

void CTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TAB1,m_TabCtrl);
	DDX_Control(pDX,IDC_TAB2,m_TabCtrl1);
	DDX_Control(pDX,IDC_TAB3,m_TabCtrl2);
	DDX_Control(pDX,IDC_TAB4,m_TabCtrl3);
	DDX_Control(pDX,IDC_TAB5,m_TabCtrl4);
}


BEGIN_MESSAGE_MAP(CTabCtrlDlg, CDlgControlItem)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabCtrlDlg::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_DROPDOWN, IDC_TAB5, &CTabCtrlDlg::OnTcnDropDownTab1)
END_MESSAGE_MAP()


// CTabCtrlDlg 消息处理程序

BOOL CTabCtrlDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	CString str;
	for (int i=0;i<15;i++)
	{
		str.Format(TEXT("Item%d"),i);
		m_TabCtrl.InsertItem(i,str);

		m_TabCtrl1.InsertItem(i,str);
		m_TabCtrl2.InsertItem(i,str);
	}

	InitQQTabCtrl();
	InitQQSafeTabCtrl();

	TCHAR szWorkDirectory[MAX_PATH]={0};
	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);
	StrCat(szWorkDirectory,TEXT("\\Res\\main.jpg"));

	m_ImageBack.LoadImage(szWorkDirectory);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTabCtrlDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	switch ( m_TabCtrl.GetCurSel())
	{
	case 0:
		{
			AfxMessageBox(TEXT("Item1被选中"));
			break;
		}
	case 1:
		{
			AfxMessageBox(TEXT("Item2被选中"));
			break;
		}
	}
	*pResult = 0;
}

BOOL CTabCtrlDlg::InitQQTabCtrl()
{
	int nIndex = m_TabCtrl4.AddItem(0, STCI_STYLE_DROPDOWN);
	
	m_TabCtrl4.SetItemToolTipText(nIndex, TEXT("联系人"));
	m_TabCtrl4.SetItemIconImage(nIndex, TEXT("Res\\TabCtrl\\icon_contacts_normal.png"),
		TEXT("Res\\TabCtrl\\icon_contacts_selected.png"));

	nIndex = m_TabCtrl4.AddItem(1, STCI_STYLE_DROPDOWN);
	m_TabCtrl4.SetItemToolTipText(nIndex, TEXT("朋友"));
	m_TabCtrl4.SetItemIconImage(nIndex, TEXT("Res\\TabCtrl\\FriendSocial_TabBtn_Normal.png"),
		TEXT("Res\\TabCtrl\\FriendSocial_TabBtn_Focus.png"));

	nIndex = m_TabCtrl4.AddItem(2, STCI_STYLE_DROPDOWN);
	m_TabCtrl4.SetItemToolTipText(nIndex, TEXT("群/讨论组"));
	m_TabCtrl4.SetItemIconImage(nIndex, TEXT("Res\\TabCtrl\\icon_group_normal.png"),
		TEXT("Res\\TabCtrl\\icon_group_selected.png"));

	nIndex = m_TabCtrl4.AddItem(3, STCI_STYLE_BUTTON);
	m_TabCtrl4.SetItemToolTipText(nIndex, TEXT("微博"));
	m_TabCtrl4.SetItemIconImage(nIndex, TEXT("Res\\TabCtrl\\WBlog_TabBtn_Normal_Msg.png"),
		TEXT("Res\\TabCtrl\\WBlog_TabBtn_Focus.png"));

	nIndex = m_TabCtrl4.AddItem(4, STCI_STYLE_DROPDOWN);
	m_TabCtrl4.SetItemToolTipText(nIndex, TEXT("最近联系人"));
	m_TabCtrl4.SetItemIconImage(nIndex, TEXT("Res\\TabCtrl\\icon_last_normal.png"),
		TEXT("Res\\TabCtrl\\icon_last_selected.png"));

	m_TabCtrl4.SetBackImage(TEXT("Res\\TabCtrl\\main_tab_bkg.png"), CRect(5,1,5,1));
	m_TabCtrl4.SetItemsImage(NULL, TEXT("Res\\TabCtrl\\main_tab_highlight.png"), 
		TEXT("Res\\TabCtrl\\main_tab_check.png"), CRect(5,1,5,1));
	
	m_TabCtrl4.SetItemsArrowImage(TEXT("Res\\TabCtrl\\main_tabbtn_highlight.png"), 
		TEXT("Res\\TabCtrl\\main_tabbtn_down.png"));

	m_TabCtrl4.SetParentBack(GetBackDC());
	m_TabCtrl4.SetItemSize(CSize(75,35),&CSize(56,19));
	m_TabCtrl4.SetWindowPos(NULL,0,0,380,35,SWP_NOMOVE);

	m_TabCtrl4.SetCurSel(0);

	return TRUE;
}

BOOL CTabCtrlDlg::InitQQSafeTabCtrl()
{
	m_TabCtrl3.SetParentBack(GetBackDC());

	for (int i=0;i<3;i++)
	{
		m_TabCtrl3.AddItem(i);
	}

	m_TabCtrl3.m_colNormalText = RGB(255,255,255);
	static CFont font;
	font.CreateFont(20,0,0,0,FW_BOLD,0,FALSE,0,0,0,0,0,0,TEXT("微软雅黑"));

	m_TabCtrl3.SetCtrlFont(font);

	m_TabCtrl3.SetItemSize(CSize(120,45));
	m_TabCtrl3.SetItemText(0,TEXT("首页"));
	m_TabCtrl3.SetItemText(1,TEXT("杀毒"));
	m_TabCtrl3.SetItemText(2,TEXT("清理垃圾"));

	m_TabCtrl3.SetItemIconImage(0, TEXT("Res\\TabCtrl\\plugin_87.png"),
		TEXT("Res\\TabCtrl\\plugin_87.png"));

	m_TabCtrl3.SetItemIconImage(1, TEXT("Res\\TabCtrl\\plugin_706.png"),
		TEXT("Res\\TabCtrl\\plugin_706.png"));

	m_TabCtrl3.SetItemIconImage(2, TEXT("Res\\TabCtrl\\plugin_2061.png"),
		TEXT("Res\\TabCtrl\\plugin_2061.png"));

	m_TabCtrl3.SetBackImage(TEXT("Res\\TabCtrl\\back.png"),&CRect(2,2,2,2));
	m_TabCtrl3.SetItemsImage(NULL,TEXT("Res\\TabCtrl\\Hoven.png"),TEXT("Res\\TabCtrl\\down.png"),&CRect(2,2,2,2));

	//m_TabCtrl3.SetLeftTop(10,10);
	m_TabCtrl3.SetCurSel(0);
	m_TabCtrl3.SetWindowPos(NULL,0,0,363,45,SWP_NOMOVE);

	return TRUE;
}

void CTabCtrlDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	m_ImageBack.DrawImage(pDC,0,0,nWidth,nHeight);
}

void CTabCtrlDlg::OnTcnDropDownTab1( NMHDR *pNMHDR, LRESULT *pResult )
{
	CMenu menu;
	if (menu.CreatePopupMenu()==FALSE) return;

	switch ( m_TabCtrl4.GetCurSel() )
	{
	case 0:
		{
			menu.AppendMenu(0,2000,TEXT("头像显示"));
			menu.AppendMenu(0,2001,TEXT("名称显示"));
			menu.AppendMenu(0,2002,TEXT("列表显示"));
		}
		break;
	case 1:
		{
			menu.AppendMenu(0,2000,TEXT("访问朋友网"));
			menu.AppendMenu(0,2001,TEXT("显示QQ号"));
			menu.AppendMenu(0,2002,TEXT("显示信息"));
		}
		break;
	case 2:
		{
			menu.AppendMenu(0,2000,TEXT("图标显示"));
			menu.AppendMenu(0,2001,TEXT("列表显示"));
			menu.AppendMenu(0,2002,TEXT("访问QQ群官网"));
		}
		break;
	case 4:
		{
			menu.AppendMenu(0,2000,TEXT("漫游会话列表"));
			menu.AppendMenu(0,2001,TEXT("清空会话列表"));
		}
		break;
	}


	CPoint pt;
	GetCursorPos(&pt);

	CRect rcControl;
	m_TabCtrl4.GetWindowRect(rcControl);
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,pt.x,rcControl.bottom+3,this);
}

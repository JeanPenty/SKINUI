// TreeCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TreeCtrlDlg.h"
#include "Resource.h"

// CTreeCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CTreeCtrlDlg, CDlgControlItem)

CTreeCtrlDlg::CTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_TREE, pParent)
{

}

CTreeCtrlDlg::~CTreeCtrlDlg()
{
}

void CTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TREE1,m_TreeCtrl);
	DDX_Control(pDX,IDC_TREE2,m_TreeCtrl1);
}


BEGIN_MESSAGE_MAP(CTreeCtrlDlg, CDlgControlItem)
	ON_BN_CLICKED(IDC_BUTTON1, &CTreeCtrlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON14, &CTreeCtrlDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON2, &CTreeCtrlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTreeCtrlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTreeCtrlDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTreeCtrlDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON10, &CTreeCtrlDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CTreeCtrlDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON21, &CTreeCtrlDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CTreeCtrlDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON7, &CTreeCtrlDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON13, &CTreeCtrlDlg::OnBnClickedButton13)
END_MESSAGE_MAP()


// CTreeCtrlDlg 消息处理程序

BOOL CTreeCtrlDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	//设置属性
	m_TreeCtrl.SetItemHeight(26);

	//加载图标
	if (m_StatusImage.GetSafeHandle()==NULL)
	{
		CBitmap Image;
		BITMAP ImageInfo;
		Image.LoadBitmap(IDB_SERVER_LIST_IMAGE);
		Image.GetBitmap(&ImageInfo);
		m_StatusImage.Create(18,ImageInfo.bmHeight,ILC_COLOR16|ILC_MASK,0,0);
		m_StatusImage.Add(&Image,RGB(255,0,255));
		m_TreeCtrl.SetImageList(&m_StatusImage,TVSIL_NORMAL);
	}

	//父节点
	HTREEITEM Root=m_TreeCtrl.InsertItem(TEXT("gym游戏中心"),0,0,TVI_ROOT,TVI_LAST);

	//斗地主游戏
	HTREEITEM GameItem1=m_TreeCtrl.InsertItem(TEXT("斗地主"),7,6,Root,TVI_LAST);
	
		HTREEITEM Room_Item1_1=m_TreeCtrl.InsertItem(TEXT("网通站点"),8,6,GameItem1,TVI_LAST);
			HTREEITEM Room_Item1_1_1=m_TreeCtrl.InsertItem(TEXT("初级房"),9,6,Room_Item1_1,TVI_LAST);
			HTREEITEM Room_Item1_1_2=m_TreeCtrl.InsertItem(TEXT("高级房"),9,6,Room_Item1_1,TVI_LAST);
			HTREEITEM Room_Item1_1_3=m_TreeCtrl.InsertItem(TEXT("VIP房"),9,6,Room_Item1_1,TVI_LAST);
	
	
		HTREEITEM Room_Item1_2=m_TreeCtrl.InsertItem(TEXT("电信站点"),8,6,GameItem1,TVI_LAST);
			HTREEITEM Room_Item1_2_1=m_TreeCtrl.InsertItem(TEXT("没有合适的房间"),9,6,Room_Item1_2,TVI_LAST);

		HTREEITEM Room_Item1_3=m_TreeCtrl.InsertItem(TEXT("其他站点"),8,6,GameItem1,TVI_LAST);
			HTREEITEM Room_Item1_3_1=m_TreeCtrl.InsertItem(TEXT("没有合适的房间"),9,6,Room_Item1_3,TVI_LAST);


	//虎虎生威游戏
	HTREEITEM GameItem2=m_TreeCtrl.InsertItem(TEXT("虎虎生威"),7,6,Root,TVI_LAST);

		HTREEITEM Room_Item2_1=m_TreeCtrl.InsertItem(TEXT("没有合适的站点"),8,6,GameItem2,TVI_LAST);

	//百人牌九游戏
	HTREEITEM GameItem3=m_TreeCtrl.InsertItem(TEXT("百人牌九"),7,6,Root,TVI_LAST);

		HTREEITEM Room_Item3_1=m_TreeCtrl.InsertItem(TEXT("没有合适的站点"),8,6,GameItem3,TVI_LAST);

	//展开所有节点
	ExpandAllItem(&m_TreeCtrl,m_TreeCtrl.GetRootItem());

	//m_TreeCtrl.SetButtonImage(TEXT("Res\\TreeCtrl\\Button.png"));
	//////////////////////////////////////////////////////////////////////////
	//重绘控件
	InitTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CTreeCtrlDlg::SetItemHeight(HTREEITEM hItem)
{
	int nOldHeight = m_TreeCtrl.GetItemHeight();
	TVITEMEX itemEx;
	itemEx.mask = TVIF_INTEGRAL;
	itemEx.hItem = hItem;
	itemEx.iIntegral = 2;
	BOOL bRet = (BOOL)m_TreeCtrl.SendMessage(TVM_SETITEM, 0, LPARAM(&itemEx));

	return bRet ? 0 : -1;
}

void CTreeCtrlDlg::ExpandAllItem(CTreeCtrl *pTreeCtrl,HTREEITEM hTreeItem,bool bExpand /*= true*/)
{
	if( pTreeCtrl == NULL && pTreeCtrl->GetSafeHwnd() == NULL ) return;
	if(!pTreeCtrl->ItemHasChildren(hTreeItem)) return;

	HTREEITEM hNextItem = pTreeCtrl->GetChildItem(hTreeItem);
	
	while (hNextItem != NULL)
	{
		ExpandAllItem(pTreeCtrl,hNextItem);
		hNextItem = pTreeCtrl->GetNextItem(hNextItem, TVGN_NEXT);
	}

	pTreeCtrl->Expand(hTreeItem,bExpand?TVE_EXPAND:TVE_COLLAPSE);
}

void CTreeCtrlDlg::OnBnClickedButton1()
{
	ExpandAllItem(&m_TreeCtrl,m_TreeCtrl.GetRootItem(),true);
}

void CTreeCtrlDlg::OnBnClickedButton14()
{
	ExpandAllItem(&m_TreeCtrl,m_TreeCtrl.GetRootItem(),false);
}

void CTreeCtrlDlg::OnBnClickedButton2()
{
	HTREEITEM hSelectItem = m_TreeCtrl.GetSelectedItem();

	m_TreeCtrl.DeleteItem(hSelectItem);
}

void CTreeCtrlDlg::OnBnClickedButton3()
{
	m_TreeCtrl.DeleteAllItems();
}

void CTreeCtrlDlg::OnBnClickedButton4()
{
	CString str;
	str.Format(TEXT("节点的总数量为:%d"),m_TreeCtrl.GetCount());
	AfxMessageBox(str);
}

void CTreeCtrlDlg::OnBnClickedButton5()
{
	m_TreeCtrl.SetBkColor(RGB(255,0,0));
}

void CTreeCtrlDlg::OnBnClickedButton10()
{
	m_TreeCtrl.SetTextColor(RGB(0,0,255));
}

void CTreeCtrlDlg::OnBnClickedButton11()
{
	if ( m_TreeCtrl.GetParentItem(m_TreeCtrl.GetSelectedItem()) )
		AfxMessageBox(TEXT("有父节点"));
	else AfxMessageBox(TEXT("无父节点"));
}

void CTreeCtrlDlg::OnBnClickedButton21()
{
	if ( m_TreeCtrl.ItemHasChildren(m_TreeCtrl.GetSelectedItem()) )
		AfxMessageBox(TEXT("有子节点"));
	else AfxMessageBox(TEXT("无子节点"));
}

void CTreeCtrlDlg::OnBnClickedButton22()
{
	AfxMessageBox(m_TreeCtrl.GetItemText(m_TreeCtrl.GetSelectedItem()));
}

void CTreeCtrlDlg::OnBnClickedButton7()
{
	if ( m_TreeCtrl.GetCheck(m_TreeCtrl.GetSelectedItem()) )
		AfxMessageBox(TEXT("被Check"));
	else AfxMessageBox(TEXT("无Check"));
}

void CTreeCtrlDlg::OnBnClickedButton13()
{
	DWORD dwAddStyle = m_TreeCtrl.GetStyle();
	DWORD dwRemoveStyle = 0;

	SetStyle(IDC_CHECK2,TVS_CHECKBOXES,dwAddStyle, dwRemoveStyle);
	SetStyle(IDC_CHECK4,TVS_HASBUTTONS,dwAddStyle, dwRemoveStyle);

	SetStyle(IDC_CHECK5,TVS_HASLINES,dwAddStyle, dwRemoveStyle);
	SetStyle(IDC_CHECK8,TVS_DISABLEDRAGDROP,dwAddStyle, dwRemoveStyle);

	SetStyle(IDC_CHECK7,TVS_EDITLABELS,dwAddStyle, dwRemoveStyle);
	SetStyle(IDC_CHECK6,TVS_LINESATROOT,dwAddStyle, dwRemoveStyle);

	SetStyle(IDC_CHECK9,TVS_SHOWSELALWAYS,dwAddStyle, dwRemoveStyle);
	SetStyle(IDC_CHECK10,TVS_TRACKSELECT,dwAddStyle, dwRemoveStyle);
	SetStyle(IDC_CHECK11,TVS_FULLROWSELECT,dwAddStyle, dwRemoveStyle);

	m_TreeCtrl.ModifyStyle(0,dwAddStyle);
	m_TreeCtrl.ModifyStyle(dwRemoveStyle,0);
	
	if ( dwRemoveStyle & TVS_CHECKBOXES)
		RemoveCheck(m_TreeCtrl.GetRootItem());
}

void CTreeCtrlDlg::SetStyle( UINT ID,DWORD dwStyle,DWORD &dwAddStyle, DWORD &dwRemoveStyle )
{
	if ( IsDlgButtonChecked(ID))
		dwAddStyle |= dwStyle;
	else if( dwAddStyle & dwStyle)
		dwRemoveStyle |= dwStyle;
}

void CTreeCtrlDlg::RemoveCheck( HTREEITEM hTreeItem )
{
	m_TreeCtrl.SetItemState(hTreeItem ,INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);

	HTREEITEM hNextItem = m_TreeCtrl.GetChildItem(hTreeItem);

	while (hNextItem != NULL)
	{
		m_TreeCtrl.SetItemState(hNextItem ,INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);

		RemoveCheck(hNextItem);
		hNextItem = m_TreeCtrl.GetNextItem(hNextItem, TVGN_NEXT);
	}
}

void CTreeCtrlDlg::InitTree()
{
	m_TreeCtrl1.SetItemHeight(26);
	m_TreeCtrl1.SetImageList(&m_StatusImage,TVSIL_NORMAL);

	HTREEITEM Root1=m_TreeCtrl1.InsertItem(TEXT("我的下载"),0,0,TVI_ROOT,TVI_LAST);

	HTREEITEM GameItem1=m_TreeCtrl1.InsertItem(TEXT("全部任务"),7,6,Root1,TVI_LAST);
	HTREEITEM GameItem2=m_TreeCtrl1.InsertItem(TEXT("正在下载"),7,6,Root1,TVI_LAST);
	HTREEITEM GameItem3=m_TreeCtrl1.InsertItem(TEXT("已完成"),7,6,Root1,TVI_LAST);
		HTREEITEM Room_Item3_1=m_TreeCtrl1.InsertItem(TEXT("影视"),8,6,GameItem3,TVI_LAST);
		HTREEITEM Room_Item3_2=m_TreeCtrl1.InsertItem(TEXT("音乐"),8,6,GameItem3,TVI_LAST);
		HTREEITEM Room_Item3_3=m_TreeCtrl1.InsertItem(TEXT("软件"),8,6,GameItem3,TVI_LAST);
		HTREEITEM Room_Item3_4=m_TreeCtrl1.InsertItem(TEXT("游戏"),8,6,GameItem3,TVI_LAST);


	HTREEITEM GameItem4=m_TreeCtrl1.InsertItem(TEXT("私人空间"),7,6,Root1,TVI_LAST);
	HTREEITEM GameItem5=m_TreeCtrl1.InsertItem(TEXT("垃圾箱"),7,6,Root1,TVI_LAST);
	HTREEITEM GameItem6=m_TreeCtrl1.InsertItem(TEXT("iPad视频"),7,6,Root1,TVI_LAST);


	HTREEITEM Root2=m_TreeCtrl1.InsertItem(TEXT("远程服务"),0,0,TVI_ROOT,TVI_LAST);
		HTREEITEM ServerItem1=m_TreeCtrl1.InsertItem(TEXT("离线下载"),7,6,Root2,TVI_LAST);
		HTREEITEM ServerItem2=m_TreeCtrl1.InsertItem(TEXT("高清片库"),7,6,Root2,TVI_LAST);

	HTREEITEM Root3=m_TreeCtrl1.InsertItem(TEXT("移动设备"),0,0,TVI_ROOT,TVI_LAST);
		HTREEITEM DeviceItem1=m_TreeCtrl1.InsertItem(TEXT("连接向导"),7,6,Root3,TVI_LAST);
		HTREEITEM DeviceItem2=m_TreeCtrl1.InsertItem(TEXT("我的iPad"),7,6,Root3,TVI_LAST);
	
	ExpandAllItem(&m_TreeCtrl1,Root1);
	ExpandAllItem(&m_TreeCtrl1,Root2);
	ExpandAllItem(&m_TreeCtrl1,Root3);

	//+-按钮
	m_TreeCtrl1.SetButtonImage(TEXT("Res\\TreeCtrl\\Button.png"));
	m_TreeCtrl1.SetHovenImage(TEXT("Res\\TreeCtrl\\LIST_ITEM_SELECT.png"),CRect(2,2,2,2));
	m_TreeCtrl1.SetPressImage(TEXT("Res\\TreeCtrl\\LIST_ITEM_DOWN.png"),CRect(2,2,2,2));
	m_TreeCtrl1.SetScrollImage(&m_TreeCtrl1,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));

	m_TreeCtrl1.m_colNormalText = RGB(1,55,102);

	//插入图标
	m_TreeCtrl1.InsertImage(DeviceItem2,TEXT("Res\\TreeCtrl\\offdown_lefttab.png"));
	m_TreeCtrl1.InsertImage(ServerItem1,TEXT("Res\\TreeCtrl\\offdown_lefttab.png"));
	m_TreeCtrl1.InsertImage(GameItem6,TEXT("Res\\TreeCtrl\\offdown_lefttab.png"));
}

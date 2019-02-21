// ListCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ListCtrlDlg.h"
#include "Resource.h"

// CListCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CListCtrlDlg, CDlgControlItem)

CListCtrlDlg::CListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_LISTCTRL, pParent)
{

}

CListCtrlDlg::~CListCtrlDlg()
{
}

void CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_ListCtrl1);
	DDX_Control(pDX,IDC_LIST2,m_ListCtrl2);
	DDX_Control(pDX,IDC_LIST3,m_ListCtrl3);
	DDX_Control(pDX,IDC_LIST4,m_ListCtrl4);
	DDX_Control(pDX,IDC_LIST5,m_ListCtrl5);
	DDX_Control(pDX,IDC_LIST6,m_ListCtrl6);
}


BEGIN_MESSAGE_MAP(CListCtrlDlg, CDlgControlItem)
	ON_BN_CLICKED(IDC_BUTTON1,OnBnClickInsert)
	ON_BN_CLICKED(IDC_BUTTON2,OnBnClickCheckState)
	ON_BN_CLICKED(IDC_BUTTON3,OnBnClickSel)
	ON_BN_CLICKED(IDC_BUTTON14,OnBnClickInfo)
	ON_BN_CLICKED(IDC_BUTTON15,OnBnClickVis)
	ON_BN_CLICKED(IDC_BUTTON16,OnBnClickUnSel)
	ON_BN_CLICKED(IDC_BUTTON17,OnBnClickHead)
	ON_BN_CLICKED(IDC_BUTTON18,OnBnClickRemoveAll)
	ON_BN_CLICKED(IDC_BUTTON19,OnBnClickRemoveItem)
	ON_BN_CLICKED(IDC_BUTTON20,OnBnClickRemove)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, OnLclickList4)
	ON_NOTIFY(NM_RCLICK, IDC_LIST4, OnRclickList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CListCtrlDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CListCtrlDlg::OnBnClickedButton8)
END_MESSAGE_MAP()

BOOL CListCtrlDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	//加载背景图
	if (m_StatusImage.GetSafeHandle()==NULL)
	{
		CBitmap Image;
		BITMAP ImageInfo;
		Image.LoadBitmap(IDB_SERVER_LIST_IMAGE);
		Image.GetBitmap(&ImageInfo);
		m_StatusImage.Create(18,ImageInfo.bmHeight,ILC_COLOR16|ILC_MASK,0,0);
		m_StatusImage.Add(&Image,RGB(255,0,255));
	}

	if ( m_ImageList1.GetSafeHandle() == NULL )
	{
		m_ImageList1.Create(80,80,ILC_MASK|ILC_COLOR32, 0, 0);
		m_ImageList1.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

		m_ListCtrl1.SetImageList(&m_ImageList1, LVSIL_NORMAL);
	}
	
	m_ListCtrl2.SetImageList(&m_StatusImage,LVSIL_SMALL);
	m_ListCtrl3.SetImageList(&m_StatusImage,LVSIL_SMALL);
	m_ListCtrl4.SetImageList(&m_StatusImage,LVSIL_SMALL);

	for (int i=0;i<40;i++)
	{
		m_ListCtrl1.InsertItem(i, TEXT("Item"));
		m_ListCtrl2.InsertItem(i, TEXT("Item"));
		m_ListCtrl3.InsertItem(i, TEXT("Item"));
	}

	//////////////////////////////////////////////////////////////////////////
	m_ListCtrl4.InsertColumn( 0, TEXT("Main_1"), LVCFMT_LEFT, 70 );
	m_ListCtrl4.InsertColumn( 1, TEXT("Main_2"), LVCFMT_LEFT, 70 );
	m_ListCtrl4.InsertColumn( 2, TEXT("Main_3"), LVCFMT_LEFT, 70 );

	m_ListCtrl4.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//////////////////////////////////////////////////////////////////////////
	//重绘控件5调用过程--Report
	m_ListCtrl5.m_SkinHeaderCtrl.SetBackImage(TEXT("Res\\ListCtrl\\folder_nav_item_bg_hover.png"),&CRect(2,2,2,2));
	m_ListCtrl5.m_SkinHeaderCtrl.SetPressImage(TEXT("Res\\ListCtrl\\folder_nav_item_bg_pressed.png"),&CRect(2,2,2,2));
	m_ListCtrl5.m_SkinHeaderCtrl.SetGridImage(TEXT("Res\\ListCtrl\\category_sep.png"));
	m_ListCtrl5.SetHovenImage(TEXT("Res\\ListCtrl\\item_bg_hover.png"),&CRect(2,2,2,2));
	m_ListCtrl5.SetSelectImage(TEXT("Res\\ListCtrl\\item_bg_selected.png"),&CRect(2,2,2,2));
	m_ListCtrl5.SetCheckImage(TEXT("Res\\ListCtrl\\check.png"),TEXT("Res\\ListCtrl\\uncheck.png"));
	m_ListCtrl5.SetScrollImage(&m_ListCtrl5,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));

	m_ListCtrl5.InsertColumn( 0, TEXT("文件名"), LVCFMT_LEFT, 150 );
	m_ListCtrl5.InsertColumn( 1, TEXT("大小"), LVCFMT_LEFT, 100 );
	m_ListCtrl5.InsertColumn( 2, TEXT("修改时间"), LVCFMT_LEFT, 150 );

	for (int i=0;i<8;i++)
	{
		m_ListCtrl5.InsertItem(i,TEXT("跟我学MFC.zip"));
		m_ListCtrl5.SetItemText(i,1,TEXT("126MB"));
		m_ListCtrl5.SetItemText(i,2,TEXT("2013-10-17 18:13"));
	}

	m_ListCtrl5.InsertImage(0,TEXT("Res\\ListCtrl\\DocType.png"));
	m_ListCtrl5.InsertImage(1,TEXT("Res\\ListCtrl\\FolderType.png"));
	m_ListCtrl5.InsertImage(2,TEXT("Res\\ListCtrl\\ImgType.png"));
	m_ListCtrl5.InsertImage(3,TEXT("Res\\ListCtrl\\PdfType.png"));
	m_ListCtrl5.InsertImage(4,TEXT("Res\\ListCtrl\\PptType.png"));
	m_ListCtrl5.InsertImage(5,TEXT("Res\\ListCtrl\\RarType.png"));
	//m_ListCtrl5.InsertImage(6,TEXT("Res\\ListCtrl\\VsdType.png"));
	m_ListCtrl5.InsertImage(7,TEXT("Res\\ListCtrl\\VideoType.png"));

	//更新资源图片
	m_ListCtrl5.InsertImage(0,TEXT("Res\\ListCtrl\\VideoType.png"));

	m_ListCtrl5.SetItemHeight(30);

	//////////////////////////////////////////////////////////////////////////
	//重绘控件6调用过程--Report
	m_ListCtrl6.InsertColumn( 0, TEXT("类型"), LVCFMT_LEFT, 50 );
	m_ListCtrl6.InsertColumn( 1, TEXT("文件名"), LVCFMT_LEFT, 80 );
	m_ListCtrl6.InsertColumn( 2, TEXT("大小"), LVCFMT_LEFT, 50 );

	m_ListCtrl6.m_SkinHeaderCtrl.SetBackImage(TEXT("Res\\ListCtrl\\folder_nav_item_bg_hover.png"),&CRect(2,2,2,2));
	m_ListCtrl6.m_SkinHeaderCtrl.SetPressImage(TEXT("Res\\ListCtrl\\folder_nav_item_bg_pressed.png"),&CRect(2,2,2,2));
	m_ListCtrl6.m_SkinHeaderCtrl.SetGridImage(TEXT("Res\\ListCtrl\\category_sep.png"));
	m_ListCtrl6.SetHovenImage(TEXT("Res\\ListCtrl\\item_bg_hover.png"),&CRect(2,2,2,2));
	m_ListCtrl6.SetSelectImage(TEXT("Res\\ListCtrl\\item_bg_selected.png"),&CRect(2,2,2,2));
	m_ListCtrl6.SetScrollImage(&m_ListCtrl6,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));

	for (int i=0;i<8;i++)
	{
		m_ListCtrl6.InsertItem(i,NULL);
		m_ListCtrl6.SetItemText(i,1,TEXT("跟我学MFC.zip"));
		m_ListCtrl6.SetItemText(i,2,TEXT("126MB"));
		m_ListCtrl6.InsertImage(i,TEXT("Res\\ListCtrl\\DocType.png"));
	}

	m_ListCtrl6.SetItemHeight(30);
	//标头控件禁止拖动
	m_ListCtrl6.m_SkinHeaderCtrl.EnableWindow(FALSE);
	m_ListCtrl6.m_SkinHeaderCtrl.SetLockCount(1);

	return TRUE;
}

void CListCtrlDlg::OnBnClickInsert()
{
	int nCount = m_ListCtrl4.GetItemCount();
	int nRow = m_ListCtrl4.InsertItem(LVIF_IMAGE|LVIF_TEXT|LVIF_PARAM,0,TEXT("Item_1"),0,0,2,0);

	m_ListCtrl4.SetItemText(nRow, 1, TEXT("Item_2"));
	m_ListCtrl4.SetItemText(nRow, 2, TEXT("Item_3"));
}	

void CListCtrlDlg::OnBnClickCheckState()
{
	CString str,str1=TEXT("被Check的行数分别为：");

	for(int i=0; i<m_ListCtrl4.GetItemCount(); i++)
	{
		if( m_ListCtrl4.GetCheck(i))
		{
			str.Format(TEXT("[%d]"),i);
			str1+=str;
		}
	}

	AfxMessageBox(str1);
}

void CListCtrlDlg::OnBnClickSel()
{
	//方法一：
	CString str,str1=TEXT("选中的行数分别为：");
	for(int i=0; i<m_ListCtrl4.GetItemCount(); i++)
	{
		if( m_ListCtrl4.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			str.Format(TEXT("[%d]"),i);
			str1+=str;
		}
	}

	//方法二：
 	POSITION pos = m_ListCtrl4.GetFirstSelectedItemPosition();
 	if (pos == NULL)
	{
		str1 = TEXT("没有选中任何节点");
	}
 	else
 	{
 		while (pos)
 		{
 			int nItem = m_ListCtrl4.GetNextSelectedItem(pos);
 			
			str.Format(TEXT("[%d]"),nItem);
 			str1+=str;
 		}
 	}

	AfxMessageBox(str1);
	m_ListCtrl4.SetFocus();
}

void CListCtrlDlg::OnBnClickInfo()
{
	TCHAR szBuffer[MAX_PATH]=TEXT("");
	CString str=TEXT("节点信息分别为：");

	//获取列数
	int nColumnCount = m_ListCtrl4.GetHeaderCtrl()->GetItemCount();

	LVITEM lvi;
	lvi.iItem = m_ListCtrl4.GetItemCount()-1;
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = CountArray(szBuffer);

	for (int i=0;i<nColumnCount; i++)
	{
		lvi.iSubItem = i;
		lvi.pszText = szBuffer;
		m_ListCtrl4.GetItem(&lvi);

		str+=TEXT("[");
		str+=szBuffer;
		str+=TEXT("] ");
	}

	AfxMessageBox(str);
}

void CListCtrlDlg::OnBnClickVis()
{
	int nItem = m_ListCtrl4.GetItemCount()-1;
	m_ListCtrl4.EnsureVisible(nItem, FALSE);

	m_ListCtrl4.SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);
	m_ListCtrl4.SetSelectionMark(nItem);
	m_ListCtrl4.SetFocus();
}

void CListCtrlDlg::OnBnClickUnSel()
{
	for(int i=0; i<m_ListCtrl4.GetItemCount(); i++)
	{
		if( m_ListCtrl4.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			m_ListCtrl4.SetItemState(i,0,LVIS_SELECTED);
		}
	}

	m_ListCtrl4.SetSelectionMark(-1);
	m_ListCtrl4.SetFocus();
}

void CListCtrlDlg::OnBnClickHead()
{
	LVCOLUMN lvcol;
	TCHAR  szBuffer[MAX_PATH]=TEXT("");

	int nColumnIndex;;

	CString str=TEXT("标题头文本分别为：");

	nColumnIndex = 0;
	lvcol.mask = LVCF_TEXT;
	lvcol.pszText = szBuffer;
	lvcol.cchTextMax = CountArray(szBuffer);

	while(m_ListCtrl4.GetColumn(nColumnIndex, &lvcol))
	{ 
		str+=TEXT("[");
		str+= lvcol.pszText;
		str+=TEXT("]");

		nColumnIndex++;
	}

	AfxMessageBox(str);
}

void CListCtrlDlg::OnBnClickRemoveAll()
{
	//方法一：
	//while( m_ListCtrl4.DeleteColumn(0) );

	//方法二：
	int nColumnCount = m_ListCtrl4.GetHeaderCtrl()->GetItemCount();

	for (int i=nColumnCount-1; i>=0; i--)
		m_ListCtrl4.DeleteColumn (i);

	m_ListCtrl4.SetFocus();
}

void CListCtrlDlg::OnBnClickRemoveItem()
{
	m_ListCtrl4.DeleteAllItems();
}

void CListCtrlDlg::OnBnClickRemove()
{
	m_ListCtrl4.DeleteItem(m_ListCtrl4.GetItemCount()-1);
}

void CListCtrlDlg::OnLclickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	//方法一：
	//DWORD dwPos = GetMessagePos();
	//CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

	//m_ListCtrl4.ScreenToClient(&point);

	//LVHITTESTINFO lvinfo;
	//lvinfo.pt = point;
	//lvinfo.flags = LVHT_ABOVE;
	//int nItem = m_ListCtrl4.SubItemHitTest(&lvinfo);

	//if(nItem != -1)
	//{
	//	CString str;
	//	str.Format(TEXT("单击的是第%d行第%d列"), lvinfo.iItem, lvinfo.iSubItem);
	//	AfxMessageBox(str);
	//}
       
   
	// 方法二:
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		CString str;
		str.Format(TEXT("单击的是第%d行第%d列"),pNMListView->iItem, pNMListView->iSubItem);
		AfxMessageBox(str);
	}

	//知道了第几行第几列，也就可以获取里面的数据什么的了

	*pResult = 0;
}

void CListCtrlDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		if (menu.CreatePopupMenu()==FALSE) return;
		menu.AppendMenu(0,2000,TEXT("菜单节点"));
		menu.AppendMenu(0,2001,TEXT("菜单节点"));
		menu.AppendMenu(0,2002,TEXT("菜单节点"));

		menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,this);
	} 
	*pResult = 0;
}


// CListCtrlDlg 消息处理程序

void CListCtrlDlg::OnBnClickedButton4()
{
	CString str,str1=TEXT("被Check的行数分别为：");

	for(int i=0; i<m_ListCtrl5.GetItemCount(); i++)
	{
		if( m_ListCtrl5.GetCheck(i))
		{
			str.Format(TEXT("[%d]"),i);
			str1+=str;
		}
	}

	AfxMessageBox(str1);
}

void CListCtrlDlg::OnBnClickedButton8()
{
	CSkinHeaderCtrl *pHeadWnd = &m_ListCtrl6.m_SkinHeaderCtrl;

	pHeadWnd->EnableWindow(!pHeadWnd->IsWindowEnabled());
}

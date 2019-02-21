// QQDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "QQDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQDlg 对话框


CQQDlg::CQQDlg(CWnd* pParent /*=NULL*/)
	: CSkinManager(IDD_QQ_DIALOG, pParent,en_Wnd_MinimizeBox)
{
	m_pImageSearch = NULL;
	m_pImageSearchText = NULL;
	m_bShowEdit = false;
}

CQQDlg::~CQQDlg()
{
}

void CQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinManager::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT_WRITE,m_EditWrite);
	DDX_Control(pDX,IDC_EDIT_SEARCH,m_EditSearch);
}

BEGIN_MESSAGE_MAP(CQQDlg, CSkinManager)
	ON_MESSAGE(WM_USER_LOGON,OnLogonMessage)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
 	ON_WM_NCHITTEST()
 	ON_WM_SIZING()
 	ON_WM_MOVING()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
	ON_EN_KILLFOCUS(IDC_EDIT_WRITE, &CQQDlg::OnEnKillfocusEditPass)
	ON_EN_KILLFOCUS(IDC_EDIT_SEARCH, &CQQDlg::OnEnKillfocusEditSearch)
	ON_WM_SETCURSOR()
	ON_NOTIFY(TCN_DROPDOWN, IDC_TABCTRL, &CQQDlg::OnTcnDropDownMenu)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, &CQQDlg::OnTcnSelchangeType)
	ON_NOTIFY(NM_DBLCLK, IDC_BUDDYLIST, &CQQDlg::OnBnClickOpenChat)
END_MESSAGE_MAP()



// CQQDlg 消息处理程序

BOOL CQQDlg::OnInitDialog()
{
	CSkinManager::OnInitDialog();

	//隐藏窗口
	SetWindowPos(NULL,0,0,0,0,NULL);

	//创建登陆窗口
	m_LogonDlg.Create(IDD_LOGON,this);
	m_LogonDlg.CenterWindow();
	m_LogonDlg.ShowWindow(SW_SHOW);

	srand(unsigned int(time(NULL)));
	SetExtrude(true);
	SetClipChild(true);

	m_HideWindow.SetHideWindow(GetSafeHwnd());

	return TRUE;
}

LRESULT CQQDlg::OnLogonMessage( WPARAM wParam,LPARAM lParam )
{
	//销毁登陆
	m_LogonDlg.PostMessage(WM_CLOSE);

	//更新资源
	UpdataResource();

	SetWindowPos(NULL,0,0,281,700,SWP_SHOWWINDOW);
	CenterWindow();  

	return TRUE;
}

void CQQDlg::OnDestroy()
{
	CSkinManager::OnDestroy();

	RenderEngine->RemoveImage(m_pImageSearch);
	RenderEngine->RemoveImage(m_pImageSearchText);

	m_ftName.DeleteObject();
}

void CQQDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	CSkinManager::DrawClientArea(pDC,nWidth,nHeight);

	if ( m_pImageSearch != NULL && !m_pImageSearch->IsNull() )
	{
		m_pImageSearch->Draw(pDC,CRect(1,140,nWidth-1,140+m_pImageSearch->GetHeight()),CRect(3,3,25,3));
		m_pImageSearchText->DrawImage(pDC,5,150);

		if ( m_bShowEdit )
		{
			pDC->FillSolidRect(1,140,nWidth-1,m_pImageSearch->GetHeight(),RGB(255,255,255));
		}
	}

	//绘制边框
	RenderEngine->DrawRoundRect(pDC->GetSafeHdc(),CRect(0,0,nWidth-1,nHeight-1),6,6,1,RGB(92,89,82));
	
	pDC->SetBkMode(TRANSPARENT);

	CFont *pOldFont=pDC->SelectObject(&m_ftName);
	pDC->DrawText(m_StrName,CRect(7,45,125,72),DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);
	pDC->SelectObject(pOldFont);  

}

void CQQDlg::OnSize(UINT nType, int cx, int cy)
{
	CSkinManager::OnSize(nType, cx, cy);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//控制按钮
	DeferWindowPos(hDwp,m_btSkin,NULL,cx-97,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btWrite,NULL,7,75,cx-68,23,uFlags);
	DeferWindowPos(hDwp,m_EditSearch,NULL,6,146,cx-30,17,uFlags);
	DeferWindowPos(hDwp,m_EditWrite,NULL,7,75,cx-68,23,uFlags);
	DeferWindowPos(hDwp,m_btClearSearch,NULL,cx-20,140,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btState,NULL,7+GetNameLength(),55,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_TabCtrl,NULL,1,172,cx,35,uFlags);
	if( m_TabCtrl.GetSafeHwnd() )
		m_TabCtrl.SetItemSize(CSize((cx-2)/3-1,35),&CSize((cx-2)/3-20,20));

	DeferWindowPos(hDwp,m_BuddyList,NULL,1,207,cx-3,cy-282,uFlags);
	DeferWindowPos(hDwp,m_GroupList,NULL,1,207,cx-3,cy-282,uFlags);
	DeferWindowPos(hDwp,m_MsgList,NULL,1,207,cx-3,cy-282,uFlags);

	for (int i=0;i<5;i++)
	{
		DeferWindowPos(hDwp,m_btQQApp[i],NULL,5+27*i,cy-53,0,0,uFlags|SWP_NOSIZE);
	}

	DeferWindowPos(hDwp,m_btMenu,NULL,5,cy-25,0,0,uFlags|SWP_NOSIZE);

	for (int i =0;i<4;i++)
	{
		DeferWindowPos(hDwp,m_btTool[i],NULL,35+27*i,cy-25,0,0,uFlags|SWP_NOSIZE);
	}

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();
}

void CQQDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	SetFocus();

	if ( PtInRect(&CRect(1,140,rcClient.Width()-1,171),point) )
	{
		m_bShowEdit = true;
		m_EditSearch.ShowWindow(SW_SHOW);
		m_btClearSearch.ShowWindow(SW_SHOW);
		m_EditSearch.SetFocus();
		InvalidateRect(&CRect(1,140,rcClient.Width()-1,171),FALSE);
	}
  	else
  		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CSkinManager::OnLButtonDown(nFlags, point);
}

void CQQDlg::UpdataResource()
{
	HDC hParentDC = GetBackDC();

	CRect rcClient;
	GetClientRect(&rcClient);

	m_pImageSearch = RenderEngine->GetImage(TEXT("QQ\\Main\\serach_edit.png"));
	m_pImageSearchText = RenderEngine->GetImage(TEXT("QQ\\Main\\serach_edit_text.png"));

	m_ftName.CreateFont(30,0,0,0,FW_NORMAL,0,FALSE,0,0,0,0,0,0,TEXT("微软雅黑"));
	m_StrName = TEXT("丄偙寵ル");
	m_StrNote = TEXT("编辑个性签名");

	m_btSkin.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-97,0,0,0),this,IDC_WNDSKIN);
	m_btSkin.SetBackImage(TEXT("\\QQ\\Main\\btn_Skin_normal.png"),TEXT("\\QQ\\Main\\btn_Skin_highlight.png"),TEXT("\\QQ\\Main\\btn_Skin_down.png"),TEXT("\\QQ\\Main\\btn_Skin_normal.png"));
	m_btSkin.SetButtonType(en_PushButton);
	m_btSkin.SetParentBack(hParentDC);
	m_btSkin.SetSize(28,20);

	m_btWrite.Create(m_StrNote,WS_VISIBLE|WS_CHILD,CRect(7,75,rcClient.Width()-68,98),this,IDC_BT_WRITE);
	m_btWrite.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL,&CRect(3,3,3,3));
	m_btWrite.SetButtonType(en_IconButton);
	m_btWrite.SetParentBack(hParentDC);
	m_btWrite.SetTextAlign(DT_LEFT|DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	m_btWrite.SetSize(rcClient.Width()-68,23);

	m_btClearSearch.Create(NULL,WS_CHILD,CRect(rcClient.Width()-22,140,0,0),this,0);
	m_btClearSearch.SetBackImage(TEXT("\\QQ\\Main\\main_search_delhighlight.png"),TEXT("\\QQ\\Main\\main_search_delhighlight.png"),TEXT("\\QQ\\Main\\main_search_deldown.png"),TEXT("\\QQ\\Main\\main_search_delhighlight.png"));
	m_btClearSearch.SetButtonType(en_PushButton);
	m_btClearSearch.SetParentBack(hParentDC);
	m_btClearSearch.SetSize(18,28);

	m_btState.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(7+GetNameLength(),55,0,0),this,0);
	m_btState.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
	m_btState.SetIconImage(TEXT("QQ\\Status\\imonline.png"));
	m_btState.SetButtonType(en_IconButton);
	m_btState.SetParentBack(hParentDC);
	m_btState.SetSize(19,19);

	//App
	for (int i =0;i<5;i++)
	{
		m_btQQApp[i].Create(NULL,WS_VISIBLE|WS_CHILD,CRect(5+27*i,rcClient.Height()-53,0,0),this,0);
		m_btQQApp[i].SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);

		m_btQQApp[i].SetButtonType(en_IconButton);
		m_btQQApp[i].SetParentBack(hParentDC);
		m_btQQApp[i].SetSize(20,20);
	}

 	m_btQQApp[0].SetIconImage(TEXT("QQ\\Main\\app1.png"));
 	m_btQQApp[1].SetIconImage(TEXT("QQ\\Main\\app2.png"));
 	m_btQQApp[2].SetIconImage(TEXT("QQ\\Main\\app3.png"));
 	m_btQQApp[3].SetIconImage(TEXT("QQ\\Main\\app4.png"));
 	m_btQQApp[4].SetIconImage(TEXT("QQ\\Main\\app5.png"));
	
	//qq菜单按钮
	m_btMenu.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(5,rcClient.Height()-25,0,0),this,IDC_MAINMENU);
	m_btMenu.SetBackImage(TEXT("QQ\\Main\\menu_btn_normal.png"),TEXT("QQ\\Main\\menu_btn_highlight.png"),TEXT("QQ\\Main\\menu_btn_highlight.png"),TEXT("QQ\\Main\\menu_btn_normal.png"));
	m_btMenu.SetButtonType(en_PushButton);
	m_btMenu.SetParentBack(hParentDC);
	m_btMenu.SetSize(21,20);
	
	//QQ工具按钮
	for (int i =0;i<4;i++)
	{
		m_btTool[i].Create(NULL,WS_VISIBLE|WS_CHILD,CRect(35+27*i,rcClient.Height()-25,0,0),this,0);
		m_btTool[i].SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
		m_btTool[i].SetButtonType(en_IconButton);
		m_btTool[i].SetParentBack(hParentDC);
		m_btTool[i].SetSize(20,20);
	}

	m_btTool[0].SetIconImage(TEXT("QQ\\Main\\Tools.png"));
	m_btTool[1].SetIconImage(TEXT("QQ\\Main\\message.png"));
	m_btTool[2].SetIconImage(TEXT("QQ\\Main\\filemanager.png"));
	m_btTool[3].SetIconImage(TEXT("QQ\\Main\\Finger_Normal.png"));
	m_btTool[3].SetWindowText(TEXT("查找"));
	m_btTool[3].SetSize(55,20);

	//QQ应用按钮
	CString str;
	for (int i =0;i<4;i++)
	{
		str.Format(TEXT("%d "),i+1);
		m_btApply[i].Create(str,WS_VISIBLE|WS_CHILD,CRect(5+37*i,114,0,0),this,0);
		m_btApply[i].SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
		m_btApply[i].SetButtonType(en_IconButton);
		m_btApply[i].SetParentBack(hParentDC);
		m_btApply[i].SetSize(30,20);
	}
	m_btApply[0].SetIconImage(TEXT("QQ\\Main\\qzoneicon.png"));
	m_btApply[1].SetIconImage(TEXT("QQ\\Main\\wblogicon.png"));
	m_btApply[2].SetIconImage(TEXT("QQ\\Main\\friendicon.png"));
	m_btApply[3].SetIconImage(TEXT("QQ\\Main\\qqshowicon.png"));

	InitTabCtrl();

	//好友列表
	InitBuddyList();
	//群列表
	InitGroupList();
	//消息列表
	InitMsgList();
}

void CQQDlg::InitTabCtrl()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	m_TabCtrl.Create(WS_VISIBLE|WS_CHILD|TCS_FIXEDWIDTH,CRect(1,172,rcClient.Width()-1,207),this,IDC_TABCTRL);

	int nIndex = m_TabCtrl.AddItem(0, STCI_STYLE_DROPDOWN);
	m_TabCtrl.SetItemToolTipText(nIndex, TEXT("联系人"));
	m_TabCtrl.SetItemIconImage(nIndex, TEXT("QQ\\Main\\icon_contacts_normal.png"),
		TEXT("QQ\\Main\\icon_contacts_selected.png"));

	nIndex = m_TabCtrl.AddItem(1, STCI_STYLE_DROPDOWN);
	m_TabCtrl.SetItemToolTipText(nIndex, TEXT("会话"));
	m_TabCtrl.SetItemIconImage(nIndex, TEXT("QQ\\Main\\icon_last_normal.png"),
		TEXT("QQ\\Main\\icon_last_selected.png"));

	nIndex = m_TabCtrl.AddItem(2, STCI_STYLE_DROPDOWN);
	m_TabCtrl.SetItemToolTipText(nIndex, TEXT("群/讨论组"));
	m_TabCtrl.SetItemIconImage(nIndex, TEXT("QQ\\Main\\icon_group_normal.png"),
		TEXT("QQ\\Main\\icon_group_selected.png"));

	m_TabCtrl.SetItemsImage(NULL, TEXT("QQ\\Main\\tab_dots_highlight.png"), 
		TEXT("QQ\\Main\\tab_dots_down.png"), CRect(5,5,5,5));

	m_TabCtrl.SetItemsArrowImage(TEXT("QQ\\Main\\main_tabbtn_highlight.png"), 
		TEXT("QQ\\Main\\main_tabbtn_down.png"));

	m_TabCtrl.SetParentBack(GetBackDC());
	m_TabCtrl.SetItemSize(CSize((rcClient.Width()-2)/3-1,35),&CSize((rcClient.Width()-2)/3-20,20));

	m_TabCtrl.SetCurSel(0);
}

void CQQDlg::InitBuddyList()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	m_BuddyList.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(1,207,rcClient.Width()-2,rcClient.Height()-60),this,IDC_BUDDYLIST);
	m_BuddyList.SetMargin(CRect(2,0,2,0));
	m_BuddyList.SetBgPic(TEXT("QQ\\BuddyList\\Bg.png"));
	m_BuddyList.SetBuddyTeamHotBgPic(TEXT("QQ\\BuddyList\\BuddyTeamHotBg.png"));
	m_BuddyList.SetBuddyItemHotBgPic(TEXT("QQ\\BuddyList\\BuddyItemHotBg.png"), CRect(1,1,1,1));
	m_BuddyList.SetBuddyItemSelBgPic(TEXT("QQ\\BuddyList\\BuddyItemSelBg.png"), CRect(1,1,1,1));
	m_BuddyList.SetHeadFramePic(TEXT("QQ\\BuddyList\\Padding4Select.png"), CRect(6,6,6,6));
	m_BuddyList.SetNormalArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTexture.png"));
	m_BuddyList.SetHotArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_BuddyList.SetSelArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_BuddyList.SetNormalExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTexture.png"));
	m_BuddyList.SetHotExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_BuddyList.SetSelExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_BuddyList.SetStdGGHeadPic(TEXT("QQ\\BuddyList\\trad_boy.png"));
	m_BuddyList.SetStdMMHeadPic(TEXT("QQ\\BuddyList\\trad_girl.png"));
	m_BuddyList.SetStyle(BLC_BIG_ICON_STYLE);
	m_BuddyList.SetShowBigIconInSel(TRUE);
	m_BuddyList.SetBuddyTeamHeight(24);
	m_BuddyList.SetBuddyItemHeightInBigIcon(54);
	m_BuddyList.SetBuddyItemHeightInSmallIcon(28);
	m_BuddyList.SetBuddyItemHeightInStandardIcon(24);
	m_BuddyList.SetBuddyItemPadding(1);

	//插入跟节点
	LPCTSTR lpszRootName[] = {TEXT("我的好友"),TEXT("陌生人"),TEXT("黑名单")};

	int nTeamIndex = 0;

	TCHAR szWorkDirectory[MAX_PATH]={0};
	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);

	CString strQQ,StrNick,StrMark,StrFace;

	int nItemCount = 0;

	for (int i=0;i<CountArray(lpszRootName);i++)
	{
		//插入根节点
		nTeamIndex = m_BuddyList.AddBuddyTeam(i);
		m_BuddyList.SetBuddyTeamName(nTeamIndex, lpszRootName[i]);
		m_BuddyList.SetBuddyTeamMaxCnt(nTeamIndex, 10);
		m_BuddyList.SetBuddyTeamCurCnt(nTeamIndex, 10);
		m_BuddyList.SetBuddyTeamExpand(nTeamIndex, FALSE);

		nItemCount = 5+rand()%10;

		//插入子节点
		for (int j=0;j<nItemCount;j++)
		{
			int nIndex = m_BuddyList.AddBuddyItem(nTeamIndex, 5);

			strQQ.Format(TEXT("%u"),100000+rand()%1000000000);
			m_BuddyList.SetBuddyItemQQNum(nTeamIndex, nIndex, strQQ);

			StrNick.Format(TEXT("昵称_%d"),j+1);
			m_BuddyList.SetBuddyItemNickName(nTeamIndex, nIndex, StrNick);

			StrMark.Format(TEXT("%s-备注_%d"),m_BuddyList.GetBuddyTeamName(nTeamIndex),j+1);
			m_BuddyList.SetBuddyItemMarkName(nTeamIndex, nIndex, StrMark);
			m_BuddyList.SetBuddyItemGender(nTeamIndex, nIndex, (i%2==0)?TRUE:FALSE);

			StrFace.Format(TEXT("%s\\QQ\\HeadFace\\%d.png"),szWorkDirectory,(1+rand()%264));
			m_BuddyList.SetBuddyItemHeadPic(nTeamIndex, nIndex, StrFace, ((nItemCount-2)>j ? false:true));
			m_BuddyList.SetBuddyItemOnline(nTeamIndex, nIndex, ((nItemCount-2)<j ? false:true), FALSE);
			m_BuddyList.SetBuddyItemSign(nTeamIndex,nIndex,TEXT("跟我一起学MFC 【http://www.gymsaga.com】"));
		}
	}

	//QQ头像闪动--QQ消息
	m_BuddyList.SetBuddyItemHeadFlashAnim(nTeamIndex,0,TRUE);

	//上线,下线动画
	m_BuddyList.SetBuddyItemOnline(nTeamIndex,1,FALSE,TRUE);
}

void CQQDlg::InitGroupList()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	m_GroupList.Create(NULL,NULL,WS_CHILD,CRect(1,207,rcClient.Width()-2,rcClient.Height()-60),this,0);
	m_GroupList.SetMargin(CRect(2,0,2,0));
	m_GroupList.SetBgPic(TEXT("QQ\\BuddyList\\Bg.png"));
	m_GroupList.SetBuddyTeamHotBgPic(TEXT("QQ\\BuddyList\\BuddyTeamHotBg.png"));
	m_GroupList.SetBuddyItemHotBgPic(TEXT("QQ\\BuddyList\\BuddyItemHotBg.png"), CRect(1,1,1,1));
	m_GroupList.SetBuddyItemSelBgPic(TEXT("QQ\\BuddyList\\BuddyItemSelBg.png"), CRect(1,1,1,1));
	m_GroupList.SetHeadFramePic(TEXT("QQ\\BuddyList\\Padding4Select.png"), CRect(6,6,6,6));
	m_GroupList.SetNormalArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTexture.png"));
	m_GroupList.SetHotArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_GroupList.SetSelArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_GroupList.SetNormalExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTexture.png"));
	m_GroupList.SetHotExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_GroupList.SetSelExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_GroupList.SetStdGGHeadPic(TEXT("QQ\\BuddyList\\trad_boy.png"));
	m_GroupList.SetStdMMHeadPic(TEXT("QQ\\BuddyList\\trad_girl.png"));
	m_GroupList.SetStyle(BLC_BIG_ICON_STYLE);
	m_GroupList.SetShowBigIconInSel(TRUE);
	m_GroupList.SetBuddyTeamHeight(24);
	m_GroupList.SetBuddyItemHeightInBigIcon(54);
	m_GroupList.SetBuddyItemHeightInSmallIcon(28);
	m_GroupList.SetBuddyItemHeightInStandardIcon(24);
	m_GroupList.SetBuddyItemPadding(1);


	int nGroupCount = 5;

	int nTeamIndex = m_GroupList.AddBuddyTeam(0);
	m_GroupList.SetBuddyTeamName(nTeamIndex, TEXT("我的QQ群"));
	m_GroupList.SetBuddyTeamMaxCnt(nTeamIndex, nGroupCount);
	m_GroupList.SetBuddyTeamCurCnt(nTeamIndex, nGroupCount);
	m_GroupList.SetBuddyTeamExpand(nTeamIndex, FALSE);

	TCHAR szWorkDirectory[MAX_PATH]={0};
	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);
	StrCat(szWorkDirectory,TEXT("\\QQ\\BuddyList\\DefGroupHeadPic.jpg"));

	for (int i = 0; i < nGroupCount; i++)
	{
		int nIndex = m_GroupList.AddBuddyItem(nTeamIndex, i);
		m_GroupList.SetBuddyItemNickName(nTeamIndex, nIndex,TEXT("跟我一起学MFC"));
		m_GroupList.SetBuddyItemHeadPic(nTeamIndex, nIndex, szWorkDirectory, FALSE);
	}
}

void CQQDlg::InitMsgList()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	m_MsgList.Create(NULL,NULL,WS_CHILD,CRect(1,207,rcClient.Width()-2,rcClient.Height()-60),this,0);
	m_MsgList.SetMargin(CRect(2,0,2,0));
	m_MsgList.SetBgPic(TEXT("QQ\\BuddyList\\Bg.png"));
	m_MsgList.SetBuddyTeamHotBgPic(TEXT("QQ\\BuddyList\\BuddyTeamHotBg.png"));
	m_MsgList.SetBuddyItemHotBgPic(TEXT("QQ\\BuddyList\\BuddyItemHotBg.png"), CRect(1,1,1,1));
	m_MsgList.SetBuddyItemSelBgPic(TEXT("QQ\\BuddyList\\BuddyItemSelBg.png"), CRect(1,1,1,1));
	m_MsgList.SetHeadFramePic(TEXT("QQ\\BuddyList\\Padding4Select.png"), CRect(6,6,6,6));
	m_MsgList.SetNormalArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTexture.png"));
	m_MsgList.SetHotArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_MsgList.SetSelArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_collapseTextureHighlight.png"));
	m_MsgList.SetNormalExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTexture.png"));
	m_MsgList.SetHotExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_MsgList.SetSelExpArrowPic(TEXT("QQ\\BuddyList\\MainPanel_FolderNode_expandTextureHighlight.png"));
	m_MsgList.SetStdGGHeadPic(TEXT("QQ\\BuddyList\\trad_boy.png"));
	m_MsgList.SetStdMMHeadPic(TEXT("QQ\\BuddyList\\trad_girl.png"));
	m_MsgList.SetStyle(BLC_BIG_ICON_STYLE);
	m_MsgList.SetShowBigIconInSel(TRUE);
	m_MsgList.SetBuddyTeamHeight(24);
	m_MsgList.SetBuddyItemHeightInBigIcon(54);
	m_MsgList.SetBuddyItemHeightInSmallIcon(28);
	m_MsgList.SetBuddyItemHeightInStandardIcon(24);
	m_MsgList.SetBuddyItemPadding(1);

	int nTeamIndex = m_MsgList.AddBuddyTeam(-1);
	m_MsgList.SetBuddyTeamName(nTeamIndex, TEXT("最近联系人"));
	m_MsgList.SetBuddyTeamExpand(nTeamIndex, FALSE);

	int nRecentCount = 20;

	TCHAR szWorkDirectory[MAX_PATH]={0};
	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);

	CString StrFace,StrGroup;

	for (int i = 0; i < nRecentCount; i++)
	{
		if ( (rand()%100)%2 == 0)
		{
			//插入好友
			CString strQQNum;
			strQQNum.Format(TEXT("%u"),100000+rand()%1000000000 );

			BOOL bGender = (i%2==0)?TRUE:FALSE;
			BOOL bGray = (i%3==0)?FALSE:TRUE;

			StrFace.Format(TEXT("%s\\QQ\\HeadFace\\%d.png"),szWorkDirectory,(1+rand()%264));

			int nIndex = m_MsgList.AddBuddyItem(nTeamIndex, i);
			m_MsgList.SetBuddyItemQQNum(nTeamIndex, nIndex, strQQNum);
			m_MsgList.SetBuddyItemNickName(nTeamIndex, nIndex, TEXT("联系人-昵称"));
			m_MsgList.SetBuddyItemMarkName(nTeamIndex, nIndex, TEXT("联系人-备注"));
			m_MsgList.SetBuddyItemSign(nTeamIndex,nIndex,TEXT("跟我一起学MFC 【http://www.gymsaga.com】"));
			m_MsgList.SetBuddyItemGender(nTeamIndex, nIndex, bGender);
			m_MsgList.SetBuddyItemHeadPic(nTeamIndex, nIndex, StrFace, bGray);
		}
		else
		{
			//插入群
			StrGroup.Format(TEXT("%s\\QQ\\BuddyList\\DefGroupHeadPic.jpg"),szWorkDirectory);
			int nIndex = m_MsgList.AddBuddyItem(nTeamIndex, i);
			m_MsgList.SetBuddyItemNickName(nTeamIndex, nIndex, TEXT("跟我一起学MFC"));
			m_MsgList.SetBuddyItemHeadPic(nTeamIndex, nIndex, StrGroup, FALSE);
		}
	}

	m_MsgList.SetBuddyTeamMaxCnt(nTeamIndex, nRecentCount);
	m_MsgList.SetBuddyTeamCurCnt(nTeamIndex, nRecentCount);
}

BOOL CQQDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CQQDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMaxTrackSize.x = 545;
	lpMMI->ptMinTrackSize.x = WND_MINSIZE_X;
	lpMMI->ptMinTrackSize.y = WND_MINSIZE_Y;

	CSkinManager::OnGetMinMaxInfo(lpMMI);
}

void CQQDlg::OnEnKillfocusEditPass()
{
	CString str;
	m_EditWrite.GetWindowText(str);
	if( str.GetLength() != 0 )
		m_btWrite.SetWindowText(str);

	m_EditWrite.ShowWindow(SW_HIDE);
	m_btWrite.ShowWindow(SW_SHOW);
}

void CQQDlg::OnEnKillfocusEditSearch()
{
	m_bShowEdit = false;

	CRect rcClient;
	GetClientRect(&rcClient);

	m_EditSearch.ShowWindow(SW_HIDE);
	if(m_btClearSearch.GetSafeHwnd())
		m_btClearSearch.ShowWindow(SW_HIDE);
	InvalidateRect(&CRect(1,140,rcClient.Width()-1,171),FALSE);
}

BOOL CQQDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	if ( PtInRect(&CRect(1,140,rcClient.Width()-30,171),point) )
	{
		SetCursor(LoadCursor(NULL,IDC_IBEAM));
		return TRUE;
	}

	return CSkinManager::OnSetCursor(pWnd, nHitTest, message);
}

int CQQDlg::GetNameLength()
{
	CDC*pDC = GetDC();
	SIZE szText = RenderEngine->GetTextSize(pDC->GetSafeHdc(),m_StrName,m_ftName,0);
	ReleaseDC(pDC);
	if( szText.cx >125) szText.cx = 125;
	return szText.cx;
}

void CQQDlg::OnTcnDropDownMenu( NMHDR *pNMHDR, LRESULT *pResult )
{
	//构造菜单
	CSkinMenu MainMenu;
	if (!MainMenu.CreatePopupMenu()) return;

	//创建子菜单
	CSkinMenu SubMenu;
	SubMenu.CreateMenu();

	switch ( m_TabCtrl.GetCurSel() )
	{
	case 0:
		{
			SubMenu.AppendMenu(3000,TEXT("大头像"),NULL,NULL,MF_POPUP);
			SubMenu.AppendMenu(3001,TEXT("小头像"),NULL,NULL,MF_POPUP);

			SubMenu.AppendSeparator();
			SubMenu.AppendMenu(3002,TEXT("选中时显示大头像"),NULL,NULL,MF_POPUP);
			SubMenu.AppendSeparator();

			SubMenu.AppendMenu(3003,TEXT("显示我的头像"),NULL,NULL,MF_POPUP | MF_CHECKED);

			SubMenu.SetMenuBarImage(TEXT("QQ\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
			SubMenu.SetMenuBackImage(TEXT("QQ\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
			SubMenu.SetMenuHovenImage(TEXT("QQ\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
			SubMenu.SetSeparatorImage(TEXT("QQ\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
			SubMenu.SetCheckImage(TEXT("QQ\\Menu\\menu_check.png"));

			//设置Check属性--当前显示为大头像
			if( m_BuddyList.GetStyle() == BLC_BIG_ICON_STYLE )
			{
				SubMenu.CheckMenuItem(3000,MF_POPUP|MF_CHECKED);
				SubMenu.EnableMenuItem(3002,MF_POPUP|MF_GRAYED);
			}

			//当前显示为小头像
			if( m_BuddyList.GetStyle() == BLC_SMALL_ICON_STYLE )
			{
				SubMenu.CheckMenuItem(3001,MF_POPUP|MF_CHECKED);
				SubMenu.EnableMenuItem(3002,MF_POPUP|MF_ENABLED);
				SubMenu.CheckMenuItem(3002,MF_POPUP|MF_CHECKED);
			}

			//当前显示为正常头像
			if( m_BuddyList.GetStyle() == BLC_STANDARD_ICON_STYLE )
			{
				SubMenu.CheckMenuItem(3001,MF_POPUP|MF_CHECKED);
				SubMenu.CheckMenuItem(3002,MF_POPUP|MF_ENABLED);
				SubMenu.CheckMenuItem(3002,MF_POPUP|MF_UNCHECKED);
			}

			MainMenu.InsertMenu((UINT)SubMenu.m_hMenu,TEXT("头像显示"),4000,TEXT("QQ\\Menu\\modehead.png"),NULL,MF_POPUP|MF_STRING|MF_BYPOSITION);
			MainMenu.AppendMenu(4001,TEXT("名称显示"));
			MainMenu.AppendMenu(4002,TEXT("列表显示"));
			MainMenu.AppendSeparator();

			MainMenu.AppendMenu(4003,TEXT("排列显示"));
			MainMenu.AppendMenu(4004,TEXT("刷新好友列表"));
			MainMenu.AppendSeparator();

			MainMenu.AppendMenu(4005,TEXT("显示在线联系人"));
			MainMenu.AppendSeparator();

			MainMenu.AppendMenu(4006,TEXT("显示企业分组"));
			MainMenu.AppendMenu(4007,TEXT("显示陌生人分组"));
			MainMenu.AppendMenu(4008,TEXT("显示黑名单"));
		}
		break;
	case 1:
		{
			MainMenu.AppendMenu(5000,TEXT("漫游会话列表"),NULL,NULL,MF_POPUP | MF_CHECKED);
			MainMenu.AppendMenu(5001,TEXT("清空会话列表"));
		}
		break;
	case 2:
		{
			SubMenu.AppendMenu(3000,TEXT("大图标"),NULL,NULL,MF_POPUP);
			SubMenu.AppendMenu(3001,TEXT("小图标"),NULL,NULL,MF_POPUP);

			SubMenu.AppendSeparator();
			SubMenu.AppendMenu(3002,TEXT("选中时显示大图标"),NULL,NULL,MF_POPUP|MF_DISABLED);
		

			SubMenu.SetMenuBarImage(TEXT("QQ\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
			SubMenu.SetMenuBackImage(TEXT("QQ\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
			SubMenu.SetMenuHovenImage(TEXT("QQ\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
			SubMenu.SetSeparatorImage(TEXT("QQ\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
			SubMenu.SetCheckImage(TEXT("QQ\\Menu\\menu_check.png"));

			//设置Check属性--当前显示为大头像
			if( m_GroupList.GetStyle() == BLC_BIG_ICON_STYLE )
			{
				SubMenu.CheckMenuItem(3000,MF_POPUP|MF_CHECKED);
				SubMenu.EnableMenuItem(3002,MF_POPUP|MF_GRAYED);
			}

			//当前显示为小头像
			if( m_GroupList.GetStyle() == BLC_SMALL_ICON_STYLE )
			{
				SubMenu.CheckMenuItem(3001,MF_POPUP|MF_CHECKED);
				SubMenu.EnableMenuItem(3002,MF_POPUP|MF_ENABLED);
				SubMenu.CheckMenuItem(3002,MF_POPUP|MF_CHECKED);
			}

			//当前显示为正常头像
			if( m_GroupList.GetStyle() == BLC_STANDARD_ICON_STYLE )
			{
				SubMenu.CheckMenuItem(3001,MF_POPUP|MF_CHECKED);
				SubMenu.CheckMenuItem(3002,MF_POPUP|MF_ENABLED);
				SubMenu.CheckMenuItem(3002,MF_POPUP|MF_UNCHECKED);
			}

			MainMenu.InsertMenu((UINT)SubMenu.m_hMenu,TEXT("图标显示"),4000,TEXT("QQ\\Menu\\modehead.png"),NULL,MF_POPUP|MF_STRING|MF_BYPOSITION);
			MainMenu.AppendMenu(4001,TEXT("列表显示"));
			
			MainMenu.AppendSeparator();
			MainMenu.AppendMenu(4002,TEXT("访问QQ群官网"),TEXT("QQ\\Menu\\groupmainpage.png"));
			MainMenu.AppendMenu(4003,TEXT("所有群消息设置    "));

			MainMenu.AppendSeparator();
			MainMenu.AppendMenu(4004,TEXT("查找添加群"));
			MainMenu.AppendMenu(4005,TEXT("创建一个群"));

			MainMenu.AppendSeparator();
			MainMenu.AppendMenu(4006,TEXT("添加群分组"));
		}
		break;
	}

	MainMenu.SetMenuBarImage(TEXT("QQ\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
	MainMenu.SetMenuBackImage(TEXT("QQ\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
	MainMenu.SetMenuHovenImage(TEXT("QQ\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
	MainMenu.SetSeparatorImage(TEXT("QQ\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
	MainMenu.SetCheckImage(TEXT("QQ\\Menu\\menu_check.png"));
	MainMenu.SetArrowImage(TEXT("QQ\\Menu\\menu_arrow.png"));

	CPoint pt;
	GetCursorPos(&pt);

	CRect rcControl;
	m_TabCtrl.GetWindowRect(rcControl);
	MainMenu.TrackPopupMenu(pt.x,rcControl.bottom+3,this);
}

void CQQDlg::OnTcnSelchangeType( NMHDR *pNMHDR, LRESULT *pResult )
{
	switch ( m_TabCtrl.GetCurSel() )
	{
	case 0:
		{
			m_BuddyList.ShowWindow(SW_SHOW);
			m_MsgList.ShowWindow(SW_HIDE);
			m_GroupList.ShowWindow(SW_HIDE);
		}
		break;
	case 1:
		{
			m_BuddyList.ShowWindow(SW_HIDE);
			m_MsgList.ShowWindow(SW_SHOW);
			m_GroupList.ShowWindow(SW_HIDE);
		}
		break;
	case 2:
		{
			m_BuddyList.ShowWindow(SW_HIDE);
			m_MsgList.ShowWindow(SW_HIDE);
			m_GroupList.ShowWindow(SW_SHOW);
		}
		break;
	}
}


BOOL CQQDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch ( LOWORD( wParam))
	{
	case IDC_MAINMENU:
		{
			//构造菜单
			CSkinMenu MainMenu;
			if (!MainMenu.CreatePopupMenu()) return FALSE;
			
			MainMenu.AppendSeparator();
			MainMenu.AppendMenu(2002,TEXT("所有服务"),TEXT("QQ\\Menu\\school_mood.png"));
			MainMenu.AppendMenu(2002,TEXT("QQ会员"),TEXT("QQ\\Menu\\vip_head.png"));
			MainMenu.AppendMenu(2002,TEXT("我的QQ中心"),TEXT("QQ\\Menu\\1.png"));
			
			MainMenu.AppendSeparator();
			MainMenu.AppendMenu(2002,TEXT("工具"),TEXT("QQ\\Menu\\2.png"));
			MainMenu.AppendMenu(2002,TEXT("软件升级"),TEXT("QQ\\Menu\\app_icon_16.png"));
			MainMenu.AppendSeparator();

			MainMenu.AppendMenu(2002,TEXT("安全中心"),TEXT("QQ\\Menu\\QQSafe.png"));
			MainMenu.AppendMenu(2002,TEXT("帮助"),TEXT("QQ\\Menu\\16.png"));

			MainMenu.AppendSeparator();
			MainMenu.AppendMenu(2002,TEXT("好友管理器   "),TEXT("QQ\\Menu\\contactmgr.png"));
			MainMenu.AppendMenu(2002,TEXT("修改密码"),TEXT("QQ\\Menu\\password.png"));
			MainMenu.AppendMenu(2002,TEXT("更改用户"),TEXT("QQ\\Menu\\safe.png"));
			MainMenu.AppendMenu(2002,TEXT("锁定QQ"),TEXT("QQ\\Menu\\lock20.png"));
			MainMenu.AppendMenu(1,TEXT("退出"),TEXT("QQ\\Menu\\AppMenuExt_MoveToBlackList.png"));

			MainMenu.SetMenuBarImage(TEXT("QQ\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
			MainMenu.SetMenuBackImage(TEXT("QQ\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
			MainMenu.SetMenuHovenImage(TEXT("QQ\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
			MainMenu.SetSeparatorImage(TEXT("QQ\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
			MainMenu.SetCheckImage(TEXT("QQ\\Menu\\menu_check.png"));
			MainMenu.SetArrowImage(TEXT("QQ\\Menu\\menu_arrow.png"));

			CPoint pt;
			GetCursorPos(&pt);

			CRect rcControl;
			m_btMenu.GetWindowRect(rcControl);
			((CMenu*)&MainMenu)->TrackPopupMenu(TPM_LEFTBUTTON|TPM_BOTTOMALIGN,rcControl.left,rcControl.top,this);
		}
		break;
	case IDC_WNDMIN:
		{
			ShowWindow(SW_MINIMIZE);
			break;
		}
	case IDC_WNDSKIN:
		{
			if ( m_SkinManager.GetSafeHwnd() == NULL )
			{
				m_SkinManager.Create(IDD_SKIN);
			}

			m_SkinManager.ShowWindow(SW_SHOW);
			m_SkinManager.CenterWindow(GetDesktopWindow());

			break;
		}
	case IDC_BT_WRITE:
		{
			m_EditWrite.ShowWindow(SW_SHOW);
			m_EditWrite.SetFocus();
			
			m_btWrite.ShowWindow(SW_HIDE);

			break;
		}
	case 3000:			//大头像
		{
			if ( m_BuddyList.IsWindowVisible() )
			{
				m_BuddyList.SetStyle(BLC_BIG_ICON_STYLE);
				m_BuddyList.Invalidate(FALSE);
			}

			if ( m_GroupList.IsWindowVisible() )
			{
				m_GroupList.SetStyle(BLC_BIG_ICON_STYLE);
				m_GroupList.Invalidate(FALSE);
			}
			break;
		}
	case 3001:			//小头像
		{
			if ( m_BuddyList.IsWindowVisible() )
			{
				m_BuddyList.SetStyle(BLC_SMALL_ICON_STYLE);
				m_BuddyList.Invalidate(FALSE);
			}

			if ( m_GroupList.IsWindowVisible() )
			{
				m_GroupList.SetStyle(BLC_SMALL_ICON_STYLE);
				m_GroupList.Invalidate(FALSE);
			}

			break;
		}
	case 3002:			//小头像
		{
			if ( m_BuddyList.IsWindowVisible() )
			{
				m_BuddyList.SetStyle(BLC_STANDARD_ICON_STYLE);
				m_BuddyList.Invalidate(FALSE);
			}

			if ( m_GroupList.IsWindowVisible() )
			{
				m_GroupList.SetStyle(BLC_STANDARD_ICON_STYLE);
				m_GroupList.Invalidate(FALSE);
			}

			break;
		}
	}

	return CSkinManager::OnCommand(wParam, lParam);
}

void CQQDlg::OnTimer( UINT nIDEvent )
{
	m_HideWindow.HideLoop(nIDEvent);

	CSkinManager::OnTimer(nIDEvent);
}

LRESULT CQQDlg::OnNcHitTest( CPoint point )
{
	m_HideWindow.BeginHide(point);

	return CSkinManager::OnNcHitTest(point);
}

void CQQDlg::OnSizing( UINT fwSide, LPRECT pRect )
{
	CSkinManager::OnSizing(fwSide, pRect);
	m_HideWindow.FixSizing(fwSide,pRect); 
}

void CQQDlg::OnMoving( UINT fwSide, LPRECT pRect )
{
	CSkinManager::OnMoving(fwSide, pRect);
	m_HideWindow.FixMoving(fwSide,pRect);
}

void CQQDlg::OnBnClickOpenChat( NMHDR *pNMHDR, LRESULT *pResult )
{
	int nSelTeamIndex = m_BuddyList.GetSelTeamIndex();
	int nSelIndex = m_BuddyList.GetSelIndex();

	if ( m_BuddyList.IsBuddyItemHasMsg(nSelTeamIndex,nSelIndex) )
	{
		m_BuddyList.SetBuddyItemHeadFlashAnim(nSelTeamIndex,nSelIndex,FALSE);
	}

	for (int i=0;i<GlobalUnits->m_ChatArray.size();i++)
	{
		CChatDlg * pChatDlg = GlobalUnits->m_ChatArray.at(i);
		if ( StrCmp(pChatDlg->m_pBuddyItem->m_strQQNum, m_BuddyList.GetBuddyItemQQNum(nSelTeamIndex,nSelIndex) ) == 0 )
		{
			pChatDlg->ShowWindow(SW_SHOW);
			pChatDlg->SetForegroundWindow();

			return;
		}
	}

	CChatDlg *pChatDlg = new CChatDlg;
	pChatDlg->Create(IDD_CHAT,GetDesktopWindow());
	pChatDlg->ShowWindow(SW_SHOW);
	pChatDlg->CenterWindow(GetDesktopWindow());

	pChatDlg->m_pBuddyItem = m_BuddyList.GetBuddyItemByIndex(nSelTeamIndex,nSelIndex);
	
	GlobalUnits->m_ChatArray.push_back(pChatDlg);
}


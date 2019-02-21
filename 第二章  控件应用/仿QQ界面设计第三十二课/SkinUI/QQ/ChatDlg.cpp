// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "ChatDlg.h"
#include "GlobalUnits.h"

// CChatDlg 对话框
LPCTSTR pszQuickMsg[]={TEXT("哦"),TEXT("好了，好了，我知道了"),TEXT("是吗？"),TEXT("不会是真的吧？")};

IMPLEMENT_DYNAMIC(CChatDlg, CSkinManager)

//////////////////////////////////////////////////////////////////////////

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CSkinManager(IDD_CHAT, pParent)
{
	m_pBuddyItem = NULL;
	m_pFacePadding = NULL;
	m_pQQShow1 = NULL;
	m_pQQShow2 = NULL;
	m_pExpressionControl=NULL;

	ZeroMemory(&m_cfRich,sizeof m_cfRich);
}

CChatDlg::~CChatDlg()
{
	//销毁窗口
	if(m_pExpressionControl && IsWindow(m_pExpressionControl->m_hWnd)) m_pExpressionControl->DestroyWindow();

	//删除对象
	SafeDelete(m_pExpressionControl);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinManager::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_COMBO_FONT,m_comFont);
	DDX_Control(pDX,IDC_COMBO_SIZE,m_comSize);
}


BEGIN_MESSAGE_MAP(CChatDlg, CSkinManager)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BT_FONT,OnBnClickFont)
	ON_CBN_SELCHANGE(IDC_COMBO_FONT, &CChatDlg::OnCbnSelchangeFont)  
	ON_CBN_SELCHANGE(IDC_COMBO_SIZE, &CChatDlg::OnCbnSelchangeSize)  
END_MESSAGE_MAP()

void CChatDlg::OnDestroy()
{
	CSkinManager::OnDestroy();

	RenderEngine->RemoveImage(m_pFacePadding);
	RenderEngine->RemoveImage(m_pQQShow1);
	RenderEngine->RemoveImage(m_pQQShow2);

	//删除对象
	SafeDelete(m_pExpressionControl);

	if (m_tbTool.GetSafeHwnd())
		m_tbTool.DestroyWindow();
}

void CChatDlg::OnSize( UINT nType, int cx, int cy )
{
	CSkinManager::OnSize(nType,cx,cy);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//控制按钮
	int nTop = 0;
	if( m_btBold.GetSafeHwnd() != NULL && m_btBold.IsWindowVisible() ) nTop=-30;
	DeferWindowPos(hDwp,m_RecEdit,NULL,6,98,cx-158,cy-170-88+nTop,uFlags);
	DeferWindowPos(hDwp,m_SendEdit,NULL,6,cy-130,cx-158,95,uFlags);

	for (int i=0;i<8;i++)
	{
		DeferWindowPos(hDwp,m_btFun[i],NULL,5+27*i,cy-152,0,0,uFlags|SWP_NOSIZE);
	}

	DeferWindowPos(hDwp,m_btMsg,NULL,cx-240,cy-152,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btSend,NULL,cx-234,cy-28,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btSendArrow,NULL,cx-173,cy-28,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btCancel,NULL,cx-309,cy-28,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_comFont,NULL,5,cy-183,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_comSize,NULL,130,cy-183,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btBold,NULL,215,cy-183,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btItalic,NULL,245,cy-183,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btUnderLine,NULL,275,cy-183,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btColor,NULL,305,cy-183,0,0,uFlags|SWP_NOSIZE);

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();
}

void CChatDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	CSkinManager::DrawClientArea(pDC,nWidth,nHeight);

	pDC->FillSolidRect(2,98,nWidth-4,nHeight-100,COLOR_BACK);

	if ( m_pBuddyItem != NULL )
	{
		//绘制头像
		if ( CHECK_IMAGE(m_pBuddyItem->m_lpHeadImg) )
		{
			m_pBuddyItem->m_lpHeadImg->DrawImage(pDC,8,8,40,40);
		}

		//绘制头像边框
		if ( CHECK_IMAGE(m_pFacePadding) )
		{
			m_pFacePadding->DrawImage(pDC,5,5);
		}

		CFont ftMark;
		ftMark.CreateFont(23,0,0,0,FW_NORMAL,0,FALSE,0,0,0,0,0,0,TEXT("微软雅黑"));
		CFont *pOldFont=pDC->SelectObject(&ftMark);
		pDC->DrawText(m_pBuddyItem->m_strMarkName,CRect(60,7,300,35),DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);
		pDC->SelectObject(pOldFont);  
		ftMark.DeleteObject();

		CFont ftSign;
		ftSign.CreateFont(18,0,0,0,FW_NORMAL,0,FALSE,0,0,0,0,0,0,TEXT("微软雅黑"));
		pOldFont=pDC->SelectObject(&ftSign);
		pDC->DrawText(m_pBuddyItem->m_strSign,CRect(60,32,nWidth-65,60),DT_LEFT|DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS);
		pDC->SelectObject(pOldFont);  
		ftSign.DeleteObject();
	}

	if ( CHECK_IMAGE(m_pQQShow1) )
		m_pQQShow1->DrawImage(pDC,nWidth-m_pQQShow1->GetWidth()-5,98);

	if ( CHECK_IMAGE(m_pQQShow2) )
		m_pQQShow2->DrawImage(pDC,nWidth-m_pQQShow2->GetWidth()-5,nHeight-195,m_pQQShow2->GetWidth(),190);
}

BOOL CChatDlg::OnInitDialog()
{
	CSkinManager::OnInitDialog();

	SetExtrude(true);
	m_bShowLogo = false;

	m_pFacePadding = RenderEngine->GetImage(TEXT("QQ\\ChatFrame\\Padding4Normal.png"));
	m_pQQShow1 = RenderEngine->GetImage(TEXT("QQ\\ChatFrame\\QQShow1.png"));
	m_pQQShow2 = RenderEngine->GetImage(TEXT("QQ\\ChatFrame\\QQShow2.png"));
	
	DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_MULTILINE|ES_AUTOVSCROLL|WS_VSCROLL|ES_WANTRETURN;

	HDC hParentDC = GetBackDC();

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcRecv = CRect(6,98,rcClient.Width()-158,rcClient.Height()-165);
	m_RecEdit.Create(dwStyle|ES_READONLY,rcRecv,this,0);
	m_RecEdit.SetParentBack(hParentDC);
	m_RecEdit.SetBackgroundColor(FALSE,COLOR_BACK);
	m_RecEdit.SetScrollImage(&m_RecEdit,TEXT("QQ\\ScrollBar\\SKIN_SCROLL.bmp"));

	CRect rcSend = CRect(6, rcClient.Height()-130,rcClient.Width()-158, rcClient.Height()-35);
	m_SendEdit.Create(dwStyle,rcSend,this,IDC_RICH_SEND);
	//m_SendEdit.SetWindowPos(NULL,6, rcClient.Height()-130,rcClient.Width()-158, rcClient.Height()-35,NULL);
	m_SendEdit.SetParentBack(hParentDC);
	m_SendEdit.SetBackgroundColor(FALSE,COLOR_BACK);

	ZeroMemory(&m_cfRich,sizeof m_cfRich);
	m_cfRich.cbSize = sizeof CHARFORMAT2;
	m_cfRich.yHeight = 18*12;
	m_cfRich.dwMask = CFM_COLOR | CFM_SIZE | CFM_FACE | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE;
	m_cfRich.dwEffects = CFE_ALLCAPS;
	m_cfRich.crTextColor = RGB(0,0,0);
	StrCpy(m_cfRich.szFaceName,TEXT("宋体"));

	SetRichFormat();

	for (int i =0;i<8;i++)
	{
		m_btFun[i].Create(NULL,WS_VISIBLE|WS_CHILD,CRect(5+27*i,rcClient.Height()-152,0,0),this,IDC_BT_FONT+i);
		m_btFun[i].SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);

		m_btFun[i].SetButtonType(en_IconButton);
		m_btFun[i].SetParentBack(hParentDC);
		m_btFun[i].SetSize(20,20);
	}

	m_btFun[0].SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_font.png"));
	m_btFun[1].SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_face.png"));
	m_btFun[2].SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_richface.png"));
	m_btFun[3].SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_flirtationface.png"));
	m_btFun[4].SetIconImage(TEXT("QQ\\ChatFrame\\AM_MenuICON.png"));
	m_btFun[5].SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_inputassist.png"));
	m_btFun[6].SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_sendpic.png"));
	m_btFun[7].SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_cut.png"));


	m_btMsg.Create(TEXT("消息记录"),WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-240,rcClient.Height()-152,0,0),this,0);
	m_btMsg.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
	m_btMsg.SetIconImage(TEXT("QQ\\ChatFrame\\aio_quickbar_register.png"));
	m_btMsg.SetButtonType(en_IconButton);
	m_btMsg.SetParentBack(hParentDC);
	m_btMsg.SetSize(85,20);
	m_btMsg.SetPushed(true);

	m_btSend.Create(TEXT("发送&(S)"),WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-234,rcClient.Height()-28,0,0),this,IDC_BT_SEND);
	m_btSend.SetBackImage(TEXT("QQ\\Button\\btnleft_normal.png"),TEXT("QQ\\Button\\btnleft_highlight.png"),TEXT("QQ\\Button\\btnleft_down.png"),TEXT("QQ\\Button\\btnleft_focus.png"));
	m_btSend.SetButtonType(en_PushButton);
	m_btSend.SetParentBack(hParentDC);
	m_btSend.SetSize(64,22);

	m_btSendArrow.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-173,rcClient.Height()-28,0,0),this,IDC_WNDSKIN);
	m_btSendArrow.SetBackImage(TEXT("QQ\\Button\\btnright_normal.png"),TEXT("QQ\\Button\\btnright_highlight.png"),TEXT("QQ\\Button\\btnright_down.png"),TEXT("QQ\\Button\\btnright_fouce.png"));
	m_btSendArrow.SetButtonType(en_PushButton);
	m_btSendArrow.SetParentBack(hParentDC);
	m_btSendArrow.SetSize(20,22);

	m_btCancel.Create(TEXT("关闭&(C)"),WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-309,rcClient.Height()-28,0,0),this,IDCANCEL);
	m_btCancel.SetBackImage(TEXT("QQ\\Button\\btn_normal.png"),TEXT("QQ\\Button\\btn_highlight.png"),TEXT("QQ\\Button\\btn_down.png"),TEXT("QQ\\Button\\btn_focus.png"));
	m_btCancel.SetButtonType(en_PushButton);
	m_btCancel.SetParentBack(hParentDC);
	m_btCancel.SetSize(69,22);

	//字体
	m_comFont.SetWindowPos(NULL,5,rcClient.Height()-183,120,150,NULL);
	m_comFont.SetBgNormalPic(TEXT("QQ\\ComboBox\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_comFont.SetBgHotPic(TEXT("QQ\\ComboBox\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_comFont.SetArrowNormalPic(TEXT("QQ\\ComboBox\\inputbtn_normal.png"));
	m_comFont.SetArrowHotPic(TEXT("QQ\\ComboBox\\inputbtn_highlight.png"));
	m_comFont.SetArrowPushedPic(TEXT("QQ\\ComboBox\\inputbtn_down.png"));
	m_comFont.SetParentBack(hParentDC);
	m_comFont.SetArrowWidth(23);
	m_comFont.SetItemHeight(-1, 22);
	m_comFont.SetDropList();
	m_comFont.SetAllItemHeight(20);

	CSkinComboBox_ListBox *pFontListBox = m_comFont.GetListBoxWnd();
	if ( pFontListBox != NULL )
	{
		pFontListBox->SetBackNormalImage(TEXT("QQ\\Edit\\frameBorderEffect_mouseDownDraw.png"),CRect(3,3,3,3));
		pFontListBox->SetSelectImage(TEXT("QQ\\ComboBox\\listitem_select.png"),CRect(3,3,3,3));
		pFontListBox->SetFrameColor(RGB(55,141,192));
	}

	m_comSize.SetWindowPos(NULL,130,rcClient.Height()-183,50,150,NULL);
	m_comSize.SetBgNormalPic(TEXT("QQ\\ComboBox\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_comSize.SetBgHotPic(TEXT("QQ\\ComboBox\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_comSize.SetArrowNormalPic(TEXT("QQ\\ComboBox\\inputbtn_normal.png"));
	m_comSize.SetArrowHotPic(TEXT("QQ\\ComboBox\\inputbtn_highlight.png"));
	m_comSize.SetArrowPushedPic(TEXT("QQ\\ComboBox\\inputbtn_down.png"));
	m_comSize.SetParentBack(hParentDC);
	m_comSize.SetArrowWidth(23);
	m_comSize.SetItemHeight(-1, 22);
	m_comSize.SetDropList();
	m_comSize.SetAllItemHeight(20);

	CSkinComboBox_ListBox *pSizeListBox = m_comSize.GetListBoxWnd();
	if ( pSizeListBox != NULL )
	{
		pSizeListBox->SetBackNormalImage(TEXT("QQ\\Edit\\frameBorderEffect_mouseDownDraw.png"),CRect(3,3,3,3));
		pSizeListBox->SetSelectImage(TEXT("QQ\\ComboBox\\listitem_select.png"),CRect(3,3,3,3));
		pSizeListBox->SetFrameColor(RGB(55,141,192));
	}

	CString str;
	for(int i=9;i<23;i++)
	{
		str.Format(TEXT("%d"),i);
		m_comSize.AddString(str);
	}

	m_comSize.SetCurSel(4);

	m_btBold.Create(NULL,WS_CHILD,CRect(215,rcClient.Height()-183,0,0),this,IDC_BOLD);
	m_btBold.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
	m_btBold.SetIconImage(TEXT("QQ\\ChatFrame\\MidToolbarExtUp_Font\\Bold.png"));
	m_btBold.SetButtonType(en_IconButton);
	m_btBold.SetParentBack(hParentDC);
	m_btBold.SetSize(30,25);
	m_btBold.SetPushed(true);

	m_btItalic.Create(NULL,WS_CHILD,CRect(245,rcClient.Height()-183,0,0),this,IDC_ITALIC);
	m_btItalic.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
	m_btItalic.SetIconImage(TEXT("QQ\\ChatFrame\\MidToolbarExtUp_Font\\Italic.png"));
	m_btItalic.SetButtonType(en_IconButton);
	m_btItalic.SetParentBack(hParentDC);
	m_btItalic.SetSize(30,25);
	m_btItalic.SetPushed(true);

	m_btUnderLine.Create(NULL,WS_CHILD,CRect(275,rcClient.Height()-183,0,0),this,IDC_UNDERLINE);
	m_btUnderLine.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
	m_btUnderLine.SetIconImage(TEXT("QQ\\ChatFrame\\MidToolbarExtUp_Font\\underline.png"));
	m_btUnderLine.SetButtonType(en_IconButton);
	m_btUnderLine.SetParentBack(hParentDC);
	m_btUnderLine.SetSize(30,25);
	m_btUnderLine.SetPushed(true);

	m_btColor.Create(NULL,WS_CHILD,CRect(305,rcClient.Height()-183,0,0),this,IDC_COLOR);
	m_btColor.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
	m_btColor.SetIconImage(TEXT("QQ\\ChatFrame\\MidToolbarExtUp_Font\\color.png"));
	m_btColor.SetButtonType(en_IconButton);
	m_btColor.SetParentBack(hParentDC);
	m_btColor.SetSize(30,25);

	EnumerateFonts(); 

	CRect rcTopToolBar(3, 55, 3+386, 55+44);
	m_tbTool.Create(WS_CHILD|WS_VISIBLE,rcTopToolBar,this, 0);
	m_tbTool.ShowWindow(SW_SHOW);

	int nIndex = m_tbTool.AddItem(101, STBI_STYLE_DROPDOWN);
	m_tbTool.SetItemSize(nIndex, 52, 40, 40, 12);
	m_tbTool.SetItemPadding(nIndex, 1);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("开始视频会话"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemLeftBgPic(nIndex, TEXT("QQ\\ChatFrame\\aio_toolbar_leftnormal.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_leftdown.png"), CRect(0,0,0,0));
	m_tbTool.SetItemRightBgPic(nIndex, TEXT("QQ\\ChatFrame\\aio_toolbar_rightnormal.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_rightdown.png"), CRect(0,0,0,0));
	m_tbTool.SetItemArrowPic(nIndex, TEXT("QQ\\ChatFrame\\aio_littletoolbar_arrow.png"));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\video.png"));

	nIndex = m_tbTool.AddItem(102, STBI_STYLE_DROPDOWN);
	m_tbTool.SetItemSize(nIndex, 52, 40, 40, 12);
	m_tbTool.SetItemPadding(nIndex, 1);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("开始语音会话"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemLeftBgPic(nIndex, TEXT("QQ\\ChatFrame\\aio_toolbar_leftnormal.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_leftdown.png"), CRect(0,0,0,0));
	m_tbTool.SetItemRightBgPic(nIndex, TEXT("QQ\\ChatFrame\\aio_toolbar_rightnormal.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_rightdown.png"), CRect(0,0,0,0));
	m_tbTool.SetItemArrowPic(nIndex, TEXT("QQ\\ChatFrame\\aio_littletoolbar_arrow.png"));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\audio.png"));

	nIndex = m_tbTool.AddItem(103, STBI_STYLE_DROPDOWN);
	m_tbTool.SetItemSize(nIndex, 52, 40, 40, 12);
	m_tbTool.SetItemPadding(nIndex, 1);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("传送文件"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemLeftBgPic(nIndex, TEXT("QQ\\ChatFrame\\aio_toolbar_leftnormal.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_leftdown.png"), CRect(0,0,0,0));
	m_tbTool.SetItemRightBgPic(nIndex, TEXT("QQ\\ChatFrame\\aio_toolbar_rightnormal.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_rightdown.png"), CRect(0,0,0,0));
	m_tbTool.SetItemArrowPic(nIndex, TEXT("QQ\\ChatFrame\\aio_littletoolbar_arrow.png"));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\sendfile.png"));

	nIndex = m_tbTool.AddItem(104, STBI_STYLE_BUTTON);
	m_tbTool.SetItemSize(nIndex, 36, 40);
	m_tbTool.SetItemPadding(nIndex, 2);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("发送短信"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\sendsms.png"));

	nIndex = m_tbTool.AddItem(105, STBI_STYLE_BUTTON);
	m_tbTool.SetItemSize(nIndex, 36, 40);
	m_tbTool.SetItemPadding(nIndex, 2);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("创建讨论组"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\create_disc_group.png"));

	nIndex = m_tbTool.AddItem(106, STBI_STYLE_WHOLEDROPDOWN);
	m_tbTool.SetItemSize(nIndex, 44, 40, 34, 10);
	m_tbTool.SetItemPadding(nIndex, 2);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("举报"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemArrowPic(nIndex, TEXT("QQ\\ChatFrame\\aio_littletoolbar_arrow.png"));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\report.png"));

	nIndex = m_tbTool.AddItem(107, STBI_STYLE_WHOLEDROPDOWN);
	m_tbTool.SetItemSize(nIndex, 44, 40, 34, 10);
	m_tbTool.SetItemPadding(nIndex, 2);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("应用"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), TEXT("QQ\\ChatFrame\\aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemArrowPic(nIndex, TEXT("QQ\\ChatFrame\\aio_littletoolbar_arrow.png"));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\app.png"));

	nIndex = m_tbTool.AddItem(108, STBI_STYLE_BUTTON);
	m_tbTool.SetItemSize(nIndex, 36, 40);
	m_tbTool.SetItemPadding(nIndex, 2);
	m_tbTool.SetItemToolTipText(nIndex, TEXT("远程协助"));
	m_tbTool.SetItemBgPic(nIndex, NULL, TEXT("QQ\\ChatFrame\\aio_toolbar_highligh.png"), 
		TEXT("aio_toolbar_down.png"), CRect(3,3,3,3));
	m_tbTool.SetItemIconPic(nIndex, TEXT("QQ\\ChatFrame\\TopToolBar\\remote_assistance.png"));

	m_tbTool.SetLeftTop(2, 2);
	m_tbTool.SetParentBack(hParentDC);

	return TRUE;
}

void CChatDlg::OnCancel()
{
	vector<CChatDlg*>::iterator iter = GlobalUnits->m_ChatArray.begin();

	for (;iter != GlobalUnits->m_ChatArray.end(); ++iter )
	{
		CChatDlg* pChatDlg = *iter;

		if( StrCmp(pChatDlg->m_pBuddyItem->m_strQQNum,m_pBuddyItem->m_strQQNum) == 0 )
		{
			pChatDlg->DestroyWindow();

			SafeDelete(pChatDlg);

			GlobalUnits->m_ChatArray.erase(iter);

			return;
		}
	}

	__super::OnCancel();
}

void CChatDlg::OnGetMinMaxInfo( MINMAXINFO* lpMMI )
{
	lpMMI->ptMinTrackSize.x = 543;
	lpMMI->ptMinTrackSize.y = 500;

	CSkinManager::OnGetMinMaxInfo(lpMMI);
}

void CChatDlg::OnBnClickFont()
{
	static bool bShow = true;

	CRect rcClient;
	GetClientRect(&rcClient);

	if( bShow )
	{
		m_comFont.ShowWindow(SW_SHOW);
		m_comSize.ShowWindow(SW_SHOW);
		m_btColor.ShowWindow(SW_SHOW);
		m_btBold.ShowWindow(SW_SHOW);
		m_btItalic.ShowWindow(SW_SHOW);
		m_btUnderLine.ShowWindow(SW_SHOW);

		m_RecEdit.SetWindowPos(NULL,6,98,rcClient.Width()-158,rcClient.Height()-282,NULL);

		bShow = false;
	}
	else
	{
		m_comFont.ShowWindow(SW_HIDE);
		m_comSize.ShowWindow(SW_HIDE);
		m_btColor.ShowWindow(SW_HIDE);
		m_btBold.ShowWindow(SW_HIDE);
		m_btItalic.ShowWindow(SW_HIDE);
		m_btUnderLine.ShowWindow(SW_HIDE);

		m_RecEdit.SetWindowPos(NULL,6,98,rcClient.Width()-158,rcClient.Height()-252,NULL);

		bShow = true;
	}
}

BOOL CALLBACK CChatDlg::EnumFamScreenCallBackEx(ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* lpntm, int FontType, LPVOID pThis)
{
	if (FontType&RASTER_FONTTYPE)
	{
		return TRUE;
	}

	CString str;

	if (FontType & TRUETYPE_FONTTYPE)
	{
		str=((pelf)->elfLogFont.lfFaceName);
	}

	int i=((CChatDlg *)pThis)->m_comFont.AddString(str);

	return TRUE;
}

BOOL CChatDlg::EnumerateFonts()
{
	HDC hDC;
	hDC=::GetWindowDC(NULL);
	LOGFONT lf;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfCharSet=GB2312_CHARSET;

	if (!::EnumFontFamiliesEx(hDC,&lf,(FONTENUMPROC)EnumFamScreenCallBackEx,(LPARAM)this,(DWORD) 0))
	{
		return FALSE;
	}

	::ReleaseDC(NULL,hDC);

	CString strCurrentFont;
	CString strPreFont=TEXT("");

	int nCount=m_comFont.GetCount();

	// 删除重复项
	for (int i=nCount;i>0;i--)
	{
		m_comFont.GetLBText((i-1),strCurrentFont);

		if (strCurrentFont==strPreFont)
		{
			m_comFont.DeleteString(i-1);
		}

		strPreFont=strCurrentFont;
	}

	// 删除@字体  循环次序 为 从高到低   因为删除某个元素后， 各个位置可能改变
	nCount=m_comFont.GetCount();
	for (int i=nCount-1;i>=0;i--)
	{
		m_comFont.GetLBText(i,strCurrentFont);
		strCurrentFont=strCurrentFont.Left(1);

		if (strCurrentFont==TEXT("@"))
		{
			m_comFont.DeleteString(i);
		}
	}

	//设置当前选中项
	CString temp;
	for (int i=0;i<m_comFont.GetCount();i++)
	{
		m_comFont.GetLBText(i,temp);

		if (temp.Compare(m_cfRich.szFaceName)==0)
		{
			m_comFont.SetCurSel(i);
			break;
		}
	}
	

	return TRUE;
}

BOOL CChatDlg::OnCommand( WPARAM wParam, LPARAM lParam )
{
	switch ( LOWORD( wParam))
	{
	case IDC_BOLD:
		{		
			static bool bBold = true;

			if ( bBold )
				m_cfRich.dwEffects |= CFE_BOLD;
			else
				m_cfRich.dwEffects &= ~CFE_BOLD;

			bBold = !bBold;
				
			SetRichFormat();

			break;
		}
	case IDC_ITALIC:
		{
			static bool bItalic = true;

			if ( bItalic )
				m_cfRich.dwEffects |= CFE_ITALIC;
			else
				m_cfRich.dwEffects &= ~CFE_ITALIC;
			
			bItalic = !bItalic;

			SetRichFormat();

			break;
		}
	case IDC_UNDERLINE:
		{
			static bool bLine = true;

			if ( bLine )
				m_cfRich.dwEffects |= CFE_UNDERLINE;
			else
				m_cfRich.dwEffects &= ~CFE_UNDERLINE;
			
			bLine = !bLine;
			
			SetRichFormat();

			break;
		}
	case IDC_COLOR:
		{
			CColorDialog dlg;

			if( dlg.DoModal() == IDOK )
			{
				m_cfRich.crTextColor = dlg.GetColor();

				SetRichFormat();
			}

			break;
		}
	case IDC_BT_SEND:
		{
			CString str;
			m_SendEdit.GetWindowText(str);

			if ( str.GetLength() == 0 )
			{
				//构造菜单
				CSkinMenu MainMenu;
				if (!MainMenu.CreatePopupMenu()) return FALSE;

				MainMenu.AppendMenu(3500,pszQuickMsg[0],0,0,MF_CHECKED);
				MainMenu.AppendMenu(3501,pszQuickMsg[1]);
				MainMenu.AppendMenu(3502,pszQuickMsg[2]);
				MainMenu.AppendMenu(3503,pszQuickMsg[3]);
				MainMenu.AppendSeparator();
				MainMenu.AppendMenu(0,TEXT("进行快捷回复菜单设置"));

				MainMenu.SetMenuBarImage(TEXT("QQ\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
				MainMenu.SetMenuBackImage(TEXT("QQ\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
				MainMenu.SetMenuHovenImage(TEXT("QQ\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
				MainMenu.SetSeparatorImage(TEXT("QQ\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
				MainMenu.SetCheckImage(TEXT("QQ\\Menu\\menu_check.png"));
				MainMenu.SetArrowImage(TEXT("QQ\\Menu\\menu_arrow.png"));

				CRect rcControl;
				m_btSend.GetWindowRect(&rcControl);
				MainMenu.TrackPopupMenu(rcControl.left,rcControl.bottom+5,this);
			}
			else
			{
				InsertReciveMsg();
			}

			break;
		}
	case 3500:
	case 3501:
	case 3502:
	case 3503:
		{
			m_SendEdit.SetWindowText(pszQuickMsg[LOWORD( wParam)-3500]);
			InsertReciveMsg();
			
			break;
		}
	case (IDC_BT_FONT+1):
		{
			//创建表情
			CRect rcButton;
			m_btFun[1].GetWindowRect(&rcButton);

			//创建窗口
			if (m_pExpressionControl==NULL)
			{
				m_pExpressionControl=new CExpressionControl;
			}

			//显示窗口
			m_pExpressionControl->ShowExpression(this,rcButton.left,rcButton.top,this);
		}
	}

	return CSkinManager::OnCommand(wParam, lParam);
}

void CChatDlg::OnCbnSelchangeFont()
{
	CString  StrFont;
	int i=m_comFont.GetCurSel();
	m_comFont.GetLBText(i,StrFont);

	StrCpy(m_cfRich.szFaceName,StrFont);

	SetRichFormat();
}

void CChatDlg::OnCbnSelchangeSize()
{
	m_cfRich.yHeight = 18*(9+m_comSize.GetCurSel());

	SetRichFormat();
}

void CChatDlg::SetRichFormat()
{
	m_SendEdit.SetSel(0, -1);
	m_SendEdit.SetWordCharFormat(m_cfRich);
	m_SendEdit.SetSel(-1, -1);

	m_SendEdit.SetFocus();
}

void CChatDlg::InsertReciveMsg()
{
	CString strTime;

	CTime tm =CTime::GetCurrentTime();
	strTime=tm.Format(TEXT("%Y/%m/%d %X\n"));
	strTime.Insert(0,TEXT("丄偙寵ル"));

	CHARFORMAT2 cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT2));
	cf2.cbSize = sizeof(CHARFORMAT2);
	cf2.dwMask = CFM_COLOR | CFM_SIZE | CFM_FACE | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE;
	cf2.dwEffects = CFE_ALLCAPS |CFE_BOLD;
	cf2.yHeight = 18*10;
	cf2.crTextColor = RGB(0,128,64);
	StrCpy(cf2.szFaceName,TEXT("微软雅黑"));

	m_RecEdit.InsertString(strTime,cf2);

	CString str;
	m_SendEdit.GetWindowText(str);

	m_RecEdit.TranslateInsertString(str,m_cfRich);

	m_RecEdit.ReplaceSel(TEXT("\n"));
	m_SendEdit.CleanScreen();

	m_MsgInfoArray.clear();
}

VOID CChatDlg::OnExpressionSelect( CExpression * pExpression, tagExpressionInfo * pExpressionInfo )
{
	//获取路径
	TCHAR szImagePath[MAX_PATH]=TEXT("");
	pExpression->GetExpressionPath(szImagePath,CountArray(szImagePath));

	CString strTime;

	CTime tm =CTime::GetCurrentTime();
	strTime=tm.Format(TEXT("%Y/%m/%d %X\n"));
	strTime.Insert(0,TEXT("丄偙寵ル"));

	CHARFORMAT2 cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT2));
	cf2.cbSize = sizeof(CHARFORMAT2);
	cf2.dwMask = CFM_COLOR | CFM_SIZE | CFM_FACE | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE;
	cf2.dwEffects = CFE_ALLCAPS |CFE_BOLD;
	cf2.yHeight = 18*10;
	cf2.crTextColor = RGB(0,128,64);
	StrCpy(cf2.szFaceName,TEXT("微软雅黑"));

	m_RecEdit.InsertString(strTime,cf2);
	m_RecEdit.InsertImage(szImagePath);
	m_RecEdit.ReplaceSel(TEXT("\n"));
}

// CChatDlg 消息处理程序

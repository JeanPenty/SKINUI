// LogonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "LogonDlg.h"

#define IDC_CLOSE					2001
#define IDC_MIN						2002
#define IDC_FINDACCOUNT				2003
#define IDC_APPLYACCOUNT			2004
#define IDC_REMPASS					2005
#define IDC_AUTOLOGON				2006
#define IDC_LOGON					2007
#define IDC_STATE					2008

//计时器
#define IDI_LOGON_STATE				100
#define IDI_GIF						101
// CLogonDlg 对话框

IMPLEMENT_DYNAMIC(CLogonDlg, CSkinDialog)

CLogonDlg::CLogonDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(IDD_LOGON, pParent)
{
	m_pImageBack = NULL;
	m_pImageFace = NULL;
	m_pImageLogo = NULL;
	m_pImageShadow = NULL;
	m_bLogoning = false;
	m_nFrameIndex = 0;
}

CLogonDlg::~CLogonDlg()
{
}

void CLogonDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_ACCOUNT,m_ComAccount);
	DDX_Control(pDX,IDC_EDIT_PASS,m_EtPassWord);
}


BEGIN_MESSAGE_MAP(CLogonDlg, CSkinDialog)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_EDIT_CLICK,OnClickPass)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CLogonDlg 消息处理程序

BOOL CLogonDlg::OnInitDialog()
{
	__super::OnInitDialog();

	HDC hParentDC = GetBackDC();

	m_pImageBack = RenderEngine->GetImage(TEXT("QQ\\logon\\noon.png"));
	m_pImageFace = RenderEngine->GetImage(TEXT("QQ\\logon\\DefaultFace.png"));
	m_pImageLogo = RenderEngine->GetImage(TEXT("QQ\\Main_Title.png"));
	m_pImageShadow = RenderEngine->GetImage(TEXT("QQ\\logon\\facebg.png"));
	
	if( m_pImageBack == NULL || m_pImageBack->IsNull() )
	{
		AfxMessageBox(TEXT("加载资源失败"));
		return FALSE;
	}

	int nWidth = m_pImageBack->GetWidth();
	int nHeight = m_pImageBack->GetHeight();

	TCHAR szWorkDirectory[MAX_PATH]={0};
	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);
	StrCat(szWorkDirectory,TEXT("\\QQ\\logon\\loading.gif"));
	m_GifLogon.LoadFromFile(szWorkDirectory);
	//开启计时器
	SetTimer(IDI_GIF,150,NULL);

	//LoadFlash(nWidth, nHeight);

	m_btClose.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(nWidth-41,-1,0,0),this,IDC_CLOSE);
 	m_btClose.SetBackImage(TEXT("\\QQ\\Button\\btn_close_normal.png"),TEXT("\\QQ\\Button\\btn_close_highlight.png"),TEXT("\\QQ\\Button\\btn_close_down.png"),TEXT("\\QQ\\Button\\btn_close_normal.png"));
 	m_btClose.SetButtonType(en_PushButton);
 	m_btClose.SetParentBack(hParentDC);
 	m_btClose.SetSize(39,20);

	m_btMin.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(nWidth-69,-1,0,0),this,IDC_MIN);
	m_btMin.SetBackImage(TEXT("\\QQ\\Button\\btn_mini_normal.png"),TEXT("\\QQ\\Button\\btn_mini_highlight.png"),TEXT("\\QQ\\Button\\btn_mini_down.png"),TEXT("\\QQ\\Button\\btn_mini_normal.png"));
	m_btMin.SetButtonType(en_PushButton);
	m_btMin.SetParentBack(hParentDC);
	m_btMin.SetSize(28,20);

	m_btFindPass.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(311,185,0,0),this,IDC_FINDACCOUNT);
	m_btFindPass.SetBackImage(TEXT("\\QQ\\logon\\mima.png"),TEXT("\\QQ\\logon\\mima_hover.png"),TEXT("\\QQ\\logon\\mima_press.png"),TEXT("\\QQ\\logon\\mima.png"));
	m_btFindPass.SetButtonType(en_PushButton);
	m_btFindPass.SetParentBack(hParentDC);
	m_btFindPass.SetSize(51,16);

	m_btApplyAcoount.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(311,150,0,0),this,IDC_APPLYACCOUNT);
	m_btApplyAcoount.SetBackImage(TEXT("\\QQ\\logon\\zhuce.png"),TEXT("\\QQ\\logon\\zhuce_hover.png"),TEXT("\\QQ\\logon\\zhuce_press.png"),TEXT("\\QQ\\logon\\zhuce.png"));
	m_btApplyAcoount.SetButtonType(en_PushButton);
	m_btApplyAcoount.SetParentBack(hParentDC);
	m_btApplyAcoount.SetSize(51,16);

	m_btRemPass.Create(TEXT("记住密码"),WS_VISIBLE|WS_CHILD|BS_AUTOCHECKBOX,CRect(112,212,0,0),this,IDC_REMPASS);
	m_btRemPass.SetCheckImage(TEXT("QQ\\CheckBox\\checkbox_normal.png"),TEXT("QQ\\CheckBox\\checkbox_hightlight.png"),TEXT("QQ\\CheckBox\\checkbox_tick_normal.png"),TEXT("QQ\\CheckBox\\checkbox_tick_highlight.png"));
	m_btRemPass.SetButtonType(en_CheckButton);
	m_btRemPass.SetParentBack(hParentDC);
	m_btRemPass.SetSize(67,15);
	m_btRemPass.m_colNormalText = RGB(0,27,47);

	m_btAutoLogon.Create(TEXT("自动登录"),WS_VISIBLE|WS_CHILD|BS_AUTOCHECKBOX,CRect(192,212,0,0),this,IDC_AUTOLOGON);
	m_btAutoLogon.SetCheckImage(TEXT("QQ\\CheckBox\\checkbox_normal.png"),TEXT("QQ\\CheckBox\\checkbox_hightlight.png"),TEXT("QQ\\CheckBox\\checkbox_tick_normal.png"),TEXT("QQ\\CheckBox\\checkbox_tick_highlight.png"));
	m_btAutoLogon.SetButtonType(en_CheckButton);
	m_btAutoLogon.SetParentBack(hParentDC);
	m_btAutoLogon.SetSize(67,15);
	m_btAutoLogon.m_colNormalText = RGB(0,27,47);

	m_btLogon.Create(TEXT("登     陆"),WS_VISIBLE|WS_CHILD,CRect(115,252,0,0),this,IDC_LOGON);
	m_btLogon.SetBackImage(TEXT("\\QQ\\logon\\button_login_normal.png"),TEXT("\\QQ\\logon\\button_login_hover.png"),TEXT("\\QQ\\logon\\button_login_down.png"),TEXT("\\QQ\\logon\\button_login_normal.png"));
	m_btLogon.SetButtonType(en_PushButton);
	m_btLogon.SetParentBack(hParentDC);
	m_btLogon.SetSize(162,38);

	m_btState.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(88,211,0,0),this,IDC_STATE);
	m_btState.SetBackImage(NULL,TEXT("QQ\\Button\\allbtn_highlight.png"),TEXT("QQ\\Button\\allbtn_down.png"),NULL);
	m_btState.SetIconImage(TEXT("QQ\\Status\\imonline.png"));
	m_btState.SetButtonType(en_IconButton);
	m_btState.SetParentBack(hParentDC);
	m_btState.SetSize(15,15);
	
	RenderEngine->AddFont(TEXT("微软雅黑"),13,false,false,false);
	m_ComAccount.SetWindowPos(NULL,113,145,188,100,SWP_DRAWFRAME);
	m_ComAccount.SetFont(CFont::FromHandle(RenderEngine->GetEndFont()));
	m_ComAccount.SetBgNormalPic(TEXT("QQ\\ComboBox\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_ComAccount.SetBgHotPic(TEXT("QQ\\ComboBox\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_ComAccount.SetArrowNormalPic(TEXT("QQ\\ComboBox\\login_inputbtn_normal.png"));
	m_ComAccount.SetArrowHotPic(TEXT("QQ\\ComboBox\\login_inputbtn_highlight.png"));
	m_ComAccount.SetArrowPushedPic(TEXT("QQ\\ComboBox\\login_inputbtn_down.png"));
	m_ComAccount.SetParentBack(hParentDC);
	m_ComAccount.SetArrowWidth(23);
	m_ComAccount.SetDefaultText(TEXT("QQ号码/手机/邮箱"));
	m_ComAccount.SetItemHeight(-1, 24);

	CSkinComboBox_ListBox *pListBox = m_ComAccount.GetListBoxWnd();
	if ( pListBox != NULL )
	{
		pListBox->SetFrameColor(RGB(55,141,192));
	}

	m_EtPassWord.SetBackNormalImage(TEXT("QQ\\Edit\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_EtPassWord.SetBackHotImage(TEXT("QQ\\Edit\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_EtPassWord.SetIconImage(TEXT("QQ\\Edit\\keyboard.png"));
	m_EtPassWord.SetPasswordChar(0x25CF);
	m_EtPassWord.SetFont(CFont::FromHandle(RenderEngine->GetEndFont()));
	m_EtPassWord.SetClientPoint(CPoint(3,3));
	m_EtPassWord.SetDefaultText(TEXT("密码"));
	m_EtPassWord.SetWindowPos(NULL,113,178,188,26,SWP_NOCOPYBITS);

	m_ComAccount.SetFocus();

	SetWindowPos(&wndTopMost,0,0,nWidth,nHeight,SWP_NOMOVE);

	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,nWidth,nHeight,8,8);
	SetWindowRgn(rgn,TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLogonDlg::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pImageBack);
	RenderEngine->RemoveImage(m_pImageFace);
	RenderEngine->RemoveImage(m_pImageLogo);
	RenderEngine->RemoveImage(m_pImageShadow);
}

void CLogonDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	m_pImageBack->DrawImage(pDC,0,0,nWidth-1,nHeight-1);
	
	m_pImageLogo->DrawImage(pDC,5,5);

	if ( m_bLogoning )
	{
		m_pImageShadow->DrawImage(pDC,(nWidth-m_pImageShadow->GetWidth())/2,143);
		m_pImageFace->DrawImage(pDC,(nWidth-m_pImageShadow->GetWidth())/2+2,147,80,80);
		m_GifLogon.DrawImageFrame(pDC,2,240,m_nFrameIndex);
	}
	else
	{
		m_pImageShadow->DrawImage(pDC,20,143);
		m_pImageFace->DrawImage(pDC,22,147,76,76);
	}
}

void CLogonDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CSkinDialog::OnLButtonDown(nFlags, point);
}

BOOL CLogonDlg::OnCommand( WPARAM wParam, LPARAM lParam )
{
	switch ( LOWORD(wParam) )
	{
	case IDC_CLOSE:
		{
			OnCancel();
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
		break;
	case IDC_MIN:
		{
			ShowWindow(SW_MINIMIZE);
			break;
		}
	case IDC_LOGON:
		{
			if ( m_bLogoning )
			{
				m_btLogon.SetWindowText(TEXT("登     陆"));
				KillTimer(IDI_LOGON_STATE);
				m_bLogoning = false;
				ShowControl(SW_SHOW);
			}
			else
			{
				m_btLogon.SetWindowText(TEXT("取     消"));
				SetTimer(IDI_LOGON_STATE,30,NULL);
				m_bLogoning = true;
				ShowControl(SW_HIDE);
			}

			Invalidate(FALSE);

			break;
		}
	case IDC_AUTOLOGON:
		{
			if ( IsDlgButtonChecked(IDC_REMPASS) == BST_UNCHECKED )
			{
				CheckDlgButton(IDC_REMPASS,BST_CHECKED);
			}
			break;
		}
	case IDC_REMPASS:
		{
			CheckDlgButton(IDC_AUTOLOGON,BST_UNCHECKED);
			break;
		}
	case IDC_APPLYACCOUNT:
		{
			OpenLink(TEXT("http://url.cn/KPQn6Q"));
			break;
		}
	case IDC_FINDACCOUNT:
		{
			OpenLink(TEXT("https://aq.qq.com/cn2/findpsw/pc/pc_find_pwd_input_account"));
			break;
		}
	case IDC_STATE:
		{
			CSkinMenu StateMenu;
			StateMenu.CreatePopupMenu();

			StateMenu.AppendMenu(4000,TEXT("我在线上"),TEXT("QQ\\Status\\imonline.png"));
			StateMenu.AppendMenu(4001,TEXT("Q我吧"),TEXT("QQ\\Status\\Qme.png"));
			StateMenu.AppendSeparator();

			StateMenu.AppendMenu(4002,TEXT("离开"),TEXT("QQ\\Status\\away.png"));
			StateMenu.AppendMenu(4003,TEXT("忙碌"),TEXT("QQ\\Status\\busy.png"));
			StateMenu.AppendMenu(4004,TEXT("请勿打扰"),TEXT("QQ\\Status\\mute.png"));
			StateMenu.AppendSeparator();

			StateMenu.AppendMenu(4005,TEXT("隐身"),TEXT("QQ\\Status\\invisible.png"));
		
			StateMenu.SetMenuBarImage(TEXT("QQ\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
			StateMenu.SetMenuBackImage(TEXT("QQ\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
			StateMenu.SetMenuHovenImage(TEXT("QQ\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
			StateMenu.SetSeparatorImage(TEXT("QQ\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));

			CRect rcControl;
			m_btState.GetWindowRect(&rcControl);

			StateMenu.TrackPopupMenu(rcControl.left,rcControl.bottom,this);
			
			break;
		}
		//////////////////////////////////////////////////////////////////////////
		//菜单消息
	case 4000:
		{
			m_btState.SetIconImage(TEXT("QQ\\Status\\imonline.png"));
			m_btState.Invalidate(FALSE);
			break;
		}
	case 4001:
		{
			m_btState.SetIconImage(TEXT("QQ\\Status\\Qme.png"));
			m_btState.Invalidate(FALSE);
			break;
		}
	case 4002:
		{
			m_btState.SetIconImage(TEXT("QQ\\Status\\away.png"));
			m_btState.Invalidate(FALSE);
			break;
		}
	case 4003:
		{
			m_btState.SetIconImage(TEXT("QQ\\Status\\busy.png"));
			m_btState.Invalidate(FALSE);
			break;
		}
	case 4004:
		{
			m_btState.SetIconImage(TEXT("QQ\\Status\\mute.png"));
			m_btState.Invalidate(FALSE);
			break;
		}
	case 4005:
		{
			m_btState.SetIconImage(TEXT("QQ\\Status\\invisible.png"));
			m_btState.Invalidate(FALSE);
			break;
		}
	}
	return CSkinDialog::OnCommand(wParam, lParam);
}

LRESULT CLogonDlg::OnClickPass( WPARAM wParam, LPARAM lParam )
{
	if ( wParam == IDC_EDIT_PASS )
	{
		//创建键盘
		if (m_PasswordKeyboard.m_hWnd==NULL)
		{
			m_PasswordKeyboard.Create(IDD_PASSWORD_KEYBOARD,this);
		}

		//显示窗口
		UINT uFlags=SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW;
		
		//获取位置
		CRect rcWindow;
		m_EtPassWord.GetWindowRect(&rcWindow);
		m_PasswordKeyboard.SetBuddy(&m_EtPassWord);
		m_PasswordKeyboard.m_colFrameNormal = RGB(44,173,229);
		m_PasswordKeyboard.SetWindowPos(NULL,rcWindow.left,rcWindow.bottom,0,0,uFlags);
	}

	return TRUE;
}

void CLogonDlg::LoadFlash( int nWidth, int nHeight )
{
	TCHAR szWorkDirectory[MAX_PATH]={0};
	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);
	StrCat(szWorkDirectory,TEXT("\\QQ\\logon\\noon.swf"));

	m_FlashControl.Create(NULL,WS_VISIBLE|WS_VISIBLE,CRect(0,0,0,0),this,3000);
	m_FlashControl.Init(this);
	m_FlashControl.LoadMovie(0,szWorkDirectory);
	m_FlashControl.Play();
	m_FlashControl.SetWindowPos(NULL,2,3,nWidth-5,140,SWP_NOACTIVATE);
}

void CLogonDlg::OnDraw( CDC*pDC,int nWidth,int nHeight )
{
	////创建缓冲
	//CDC BufferDC;
	//CBitmap ImageBuffer;
	//BufferDC.CreateCompatibleDC(pDC);
	//ImageBuffer.CreateCompatibleBitmap(pDC,nWidth,nHeight);

	////设置环境
	//BufferDC.SelectObject(&ImageBuffer);

	//if( m_pImageShadow!= NULL && m_pImageShadow->IsNull() == false )
	//	m_pImageShadow->DrawImage(&BufferDC,0,nHeight-m_pImageShadow->GetHeight(),nWidth,m_pImageShadow->GetHeight());

	////绘画界面
	//pDC->BitBlt(0,0,nWidth,nHeight,&BufferDC,0,0,SRCCOPY);

	////清理资源
	//BufferDC.DeleteDC();
	//ImageBuffer.DeleteObject();
}

void CLogonDlg::OnTimer(UINT_PTR nIDEvent)
{
	if ( nIDEvent == IDI_LOGON_STATE )
	{
		static int nTime = 0;

		//大约2秒后显示主窗口
#ifdef _DEBUG
		if ( nTime++ >= 20 )
#else
		if ( nTime++ >= 33*2 )
#endif
		{
			KillTimer(IDI_LOGON_STATE);
			GetParent()->PostMessage(WM_USER_LOGON);
			m_bLogoning = false;
		}
	}

	//GIF动画
	if ( nIDEvent == IDI_GIF )
	{
 		if ( ++m_nFrameIndex >= m_GifLogon.GetFrameCount() )
 		{
			m_nFrameIndex = 0;
 		}

 		InvalidateRect(&CRect(2,240,2+m_GifLogon.GetWidth(),240+m_GifLogon.GetHeight()),FALSE);
	}

	__super::OnTimer(nIDEvent);
}

void CLogonDlg::ShowControl(int nCmdShow)
{
	m_btFindPass.ShowWindow(nCmdShow);
	m_btApplyAcoount.ShowWindow(nCmdShow);
	m_btRemPass.ShowWindow(nCmdShow);
	m_btAutoLogon.ShowWindow(nCmdShow);
	m_btState.ShowWindow(nCmdShow);
	m_ComAccount.ShowWindow(nCmdShow);
	m_EtPassWord.ShowWindow(nCmdShow);

	if( m_PasswordKeyboard.GetSafeHwnd() )
		m_PasswordKeyboard.ShowWindow(nCmdShow);
}

BOOL CLogonDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

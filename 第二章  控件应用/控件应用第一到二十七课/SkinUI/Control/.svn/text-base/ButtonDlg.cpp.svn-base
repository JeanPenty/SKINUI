// ButtonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ButtonDlg.h"
#include "resource.h"

// CButtonDlg 对话框

IMPLEMENT_DYNAMIC(CButtonDlg, CDlgControlItem)

CButtonDlg::CButtonDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_BUTTON, pParent)
{
}

CButtonDlg::~CButtonDlg()
{
}

void CButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_BUTTON2,m_Button2);
	DDX_Control(pDX,IDC_BUTTON3,m_Button3);
	DDX_Control(pDX,IDC_BUTTON4,m_Button4);
	DDX_Control(pDX,IDC_CHECK3,m_Button5);
	DDX_Control(pDX,IDC_RADIO6,m_Button6);
	DDX_Control(pDX,IDC_BUTTON5,m_Button7);
	DDX_Control(pDX,IDC_BUTTON6,m_Button8);
	DDX_Control(pDX,IDC_BUTTON7,m_Button9);
}


BEGIN_MESSAGE_MAP(CButtonDlg, CDlgControlItem)
	//ON_BN_CLICKED(IDC_BUTTON1, &CButtonDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &CButtonDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON2, &CButtonDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CButtonDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CButtonDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CButtonDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CButtonDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CButtonDlg 消息处理程序
BOOL CButtonDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	//设置选中
 	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(BST_CHECKED);
 	CheckDlgButton(IDC_CHECK2,BST_CHECKED);

	//获取是否选中
	UINT uCheck = IsDlgButtonChecked(IDC_CHECK1);
	if( ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == BST_CHECKED ){}

	//如果此类控件比较多，可以通过这个判断哪个被选中了
	INT uCheckID = GetCheckedRadioButton( IDC_CHECK1, IDC_CHECK2);
	
	HDC hParentDC = GetBackDC();

	m_Button2.SetBackImage(TEXT("Res\\Button\\login_btn_normal.png"),TEXT("Res\\Button\\login_btn_highlight.png"),TEXT("Res\\Button\\login_btn_down.png"),TEXT("Res\\Button\\login_btn_focus.png"));
	m_Button2.SetButtonType(en_PushButton);
	m_Button2.SetParentBack(hParentDC);
	m_Button2.SetSize(86,30);

	m_Button3.SetBackImage(TEXT("Res\\Button\\btn_close_normal.png"),TEXT("Res\\Button\\btn_close_highlight.png"),TEXT("Res\\Button\\btn_close_down.png"),TEXT("Res\\Button\\btn_close_normal.png"));
	m_Button3.SetButtonType(en_PushButton);
	m_Button3.SetParentBack(hParentDC);
	m_Button3.SetSize(39,20);

	m_Button4.SetBackImage(TEXT("Res\\Button\\tank_normal.png"),TEXT("Res\\Button\\tank_highlight.png"),TEXT("Res\\Button\\tank_down.png"),TEXT("Res\\Button\\tank_normal.png"));
	m_Button4.SetButtonType(en_PushButton);
	m_Button4.SetParentBack(hParentDC);
	m_Button4.SetSize(130,130);

	m_Button5.SetCheckImage(TEXT("Res\\Button\\checkbox_normal.png"),TEXT("Res\\Button\\checkbox_hightlight.png"),TEXT("Res\\Button\\checkbox_tick_normal.png"),TEXT("Res\\Button\\checkbox_tick_highlight.png"));
	m_Button5.SetButtonType(en_CheckButton);
	m_Button5.SetParentBack(hParentDC);
	m_Button5.SetSize(68,15);
	m_Button5.SetCheck(BST_CHECKED);

	m_Button6.SetCheckImage(TEXT("Res\\Button\\radiobtn_normal.png"),TEXT("Res\\Button\\radiobtn_highlight.png"),TEXT("Res\\Button\\radiobtn_tick_normal.png"),TEXT("Res\\Button\\radiobtn_tick_highlight.png"));
	m_Button6.SetButtonType(en_RadioButton);
	m_Button6.SetParentBack(hParentDC);
	m_Button6.SetSize(100,15);
	
	m_Button7.SetBackImage(NULL,TEXT("Res\\Button\\allbtn_highlight.png"),TEXT("Res\\Button\\allbtn_down.png"),NULL);
	m_Button7.SetIconImage(TEXT("Res\\Button\\message.png"));
	m_Button7.SetButtonType(en_IconButton);
	m_Button7.SetParentBack(hParentDC);
	m_Button7.SetSize(22,22);

	m_Button8.SetBackImage(
							NULL,
							TEXT("Res\\Button\\allbtn_highlight.png"),
							TEXT("Res\\Button\\allbtn_down.png"),
							NULL,
							&CRect(3,3,3,3)
							);
	m_Button8.SetIconImage(TEXT("Res\\Button\\QQSafe.png"));
	m_Button8.SetButtonType(en_IconButton);
	m_Button8.SetParentBack(hParentDC);
	m_Button8.SetSize(85,22);

	static CMenu menu;
	menu.LoadMenu(IDR_MENU1);

	CMenu *PopupMenu = menu.GetSubMenu(0);

	m_Button9.SetBackImage(NULL,TEXT("Res\\Button\\menubtn_highlight.png"),TEXT("Res\\Button\\menubtn_highlight.png"),NULL);
	m_Button9.SetIconImage(TEXT("Res\\Button\\imonline.png"));
	m_Button9.SetMenuImage(TEXT("Res\\Button\\MainPanel_FolderNode_expandTexture.png"));
	m_Button9.SetButtonType(en_MenuButton);
	m_Button9.SetParentBack(hParentDC);
	m_Button9.SetMenu(PopupMenu->m_hMenu);
	m_Button9.SetSize(35,22);

	TCHAR szWorkDirectory[MAX_PATH]={0};
	RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);
	StrCat(szWorkDirectory,TEXT("\\Res\\BACK.jpg"));

	m_ImageBack.LoadImage(szWorkDirectory);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CButtonDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CButtonDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
// 	if (LOWORD(wParam) == IDC_BUTTON1 )
// 	{
// 		MessageBox(TEXT("IDC_BUTTON1"));
// 	}

	return CDlgControlItem::OnCommand(wParam, lParam);
}

LRESULT CButtonDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
 	if ( message == WM_COMMAND )
 	{
 		if (LOWORD(wParam) == IDC_BUTTON1 )
 		{
			OpenLink(TEXT("http://www.gymsaga.com/project/388.html"));
 		}
 	}

	return CDlgControlItem::DefWindowProc(message, wParam, lParam);
}

void CButtonDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	CRect rcClient;
	GetClientRect(&rcClient);

	m_ImageBack.DrawImage(pDC,rcClient);
}

void CButtonDlg::OnBnClickedButton7()
{
// 	CMenu menu;
// 	if (menu.CreatePopupMenu()==FALSE) return;
// 
// 	menu.AppendMenu(0,1000,TEXT("Item1"));
// 	menu.AppendMenu(0,1001,TEXT("Item2"));
// 
// 	//显示菜单
// 	CPoint pt;
// 	GetCursorPos(&pt);
// 	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,pt.x,pt.y,this);

	
}

void CButtonDlg::OnBnClickedButton2()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/388.html"));
}

void CButtonDlg::OnBnClickedButton3()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/388.html"));
}

void CButtonDlg::OnBnClickedButton4()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/388.html"));
}

void CButtonDlg::OnBnClickedButton5()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/388.html"));
}

void CButtonDlg::OnBnClickedButton6()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/388.html"));
}

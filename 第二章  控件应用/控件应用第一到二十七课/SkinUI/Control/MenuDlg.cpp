// MenuDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MenuDlg.h"
#include "Resource.h"

// CMenuDlg 对话框

IMPLEMENT_DYNAMIC(CMenuDlg, CDlgControlItem)

CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_MENU, pParent)
{

}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDlgControlItem)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CMenuDlg 消息处理程序

BOOL CMenuDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

 	//m_MenuBar.LoadMenu(IDR_MENU2); 
 	//SetMenu(&m_MenuBar);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMenuDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	//构造菜单
	CSkinMenu MainMenu;
	MainMenu.CreatePopupMenu();

	//创建子菜单
	CSkinMenu SubMenu;
	SubMenu.CreateMenu();
	SubMenu.AppendMenu(3000,TEXT("主面板"),TEXT("Res\\Status\\busy.png"),0,MF_POPUP);
	SubMenu.AppendMenu(3001,TEXT("设置"),TEXT("Res\\Status\\busy.png"),0,MF_POPUP);
	SubMenu.AppendMenu(3002,TEXT("QQ消息管理器"),TEXT("Res\\Status\\busy.png"),0,MF_POPUP);
	SubMenu.SetMenuBarImage(TEXT("Res\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
	SubMenu.SetMenuBackImage(TEXT("Res\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
	SubMenu.SetMenuHovenImage(TEXT("Res\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
	SubMenu.SetSeparatorImage(TEXT("Res\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
	SubMenu.SetCheckImage(TEXT("Res\\Menu\\menu_check.png"));


	//建立菜单
	MainMenu.AppendMenu(4000,TEXT("我在线上"),TEXT("Res\\Status\\imonline.png"),TEXT("Res\\Status\\invisible.png"),MF_POPUP);
	MainMenu.AppendMenu(4001,TEXT("Q我吧"),TEXT("Res\\Status\\Qme.png"));
	MainMenu.AppendMenu(4002,TEXT("离开"),TEXT("Res\\Status\\away.png"));
	MainMenu.AppendSeparator();
	MainMenu.AppendMenu(4003,TEXT("忙碌"),TEXT("Res\\Status\\busy.png"));
	MainMenu.AppendMenu(4004,TEXT("请勿打扰"),TEXT("Res\\Status\\mute.png"));
	MainMenu.AppendMenu(4005,TEXT("离线"),TEXT("Res\\Status\\imoffline.png"));
	MainMenu.AppendSeparator();
	MainMenu.AppendMenu(4006,TEXT("添加状态信息"));
	MainMenu.AppendMenu(4006,TEXT("锁定QQ  Ctrl + Alt + L"),TEXT("Res\\Menu\\lock20.png"));
	MainMenu.InsertMenu((UINT)SubMenu.m_hMenu,TEXT("打开"),4008,0,0,MF_POPUP|MF_STRING|MF_BYPOSITION);
	
	MainMenu.SetMenuBarImage(TEXT("Res\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
	MainMenu.SetMenuBackImage(TEXT("Res\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
	MainMenu.SetMenuHovenImage(TEXT("Res\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
	MainMenu.SetSeparatorImage(TEXT("Res\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
	MainMenu.SetCheckImage(TEXT("Res\\Menu\\menu_check.png"));
	MainMenu.SetArrowImage(TEXT("Res\\Menu\\menu_arrow.png"));

	//MainMenu.SetFrameColor(RGB(255,0,0));
	//显示菜单
	MainMenu.TrackPopupMenu(this);

	__super::OnRButtonDown(nFlags,point);
}

BOOL CMenuDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case 3000:
		AfxMessageBox(TEXT("打开主面板"));
		break;
	}

	return CDlgControlItem::OnCommand(wParam, lParam);
}

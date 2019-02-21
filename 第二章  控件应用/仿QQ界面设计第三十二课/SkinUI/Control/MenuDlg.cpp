// MenuDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MenuDlg.h"
#include "Resource.h"

// CMenuDlg �Ի���

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


// CMenuDlg ��Ϣ�������

BOOL CMenuDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

 	//m_MenuBar.LoadMenu(IDR_MENU2); 
 	//SetMenu(&m_MenuBar);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMenuDlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	//����˵�
	CSkinMenu MainMenu;
	MainMenu.CreatePopupMenu();

	//�����Ӳ˵�
	CSkinMenu SubMenu;
	SubMenu.CreateMenu();
	SubMenu.AppendMenu(3000,TEXT("�����"),TEXT("Res\\Status\\busy.png"),0,MF_POPUP);
	SubMenu.AppendMenu(3001,TEXT("����"),TEXT("Res\\Status\\busy.png"),0,MF_POPUP);
	SubMenu.AppendMenu(3002,TEXT("QQ��Ϣ������"),TEXT("Res\\Status\\busy.png"),0,MF_POPUP);
	SubMenu.SetMenuBarImage(TEXT("Res\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
	SubMenu.SetMenuBackImage(TEXT("Res\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
	SubMenu.SetMenuHovenImage(TEXT("Res\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
	SubMenu.SetSeparatorImage(TEXT("Res\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
	SubMenu.SetCheckImage(TEXT("Res\\Menu\\menu_check.png"));


	//�����˵�
	MainMenu.AppendMenu(4000,TEXT("��������"),TEXT("Res\\Status\\imonline.png"),TEXT("Res\\Status\\invisible.png"),MF_POPUP);
	MainMenu.AppendMenu(4001,TEXT("Q�Ұ�"),TEXT("Res\\Status\\Qme.png"));
	MainMenu.AppendMenu(4002,TEXT("�뿪"),TEXT("Res\\Status\\away.png"));
	MainMenu.AppendSeparator();
	MainMenu.AppendMenu(4003,TEXT("æµ"),TEXT("Res\\Status\\busy.png"));
	MainMenu.AppendMenu(4004,TEXT("�������"),TEXT("Res\\Status\\mute.png"));
	MainMenu.AppendMenu(4005,TEXT("����"),TEXT("Res\\Status\\imoffline.png"));
	MainMenu.AppendSeparator();
	MainMenu.AppendMenu(4006,TEXT("���״̬��Ϣ"));
	MainMenu.AppendMenu(4006,TEXT("����QQ  Ctrl + Alt + L"),TEXT("Res\\Menu\\lock20.png"));
	MainMenu.InsertMenu((UINT)SubMenu.m_hMenu,TEXT("��"),4008,0,0,MF_POPUP|MF_STRING|MF_BYPOSITION);
	
	MainMenu.SetMenuBarImage(TEXT("Res\\Menu\\menu_left_bg.png"),&CRect(2,2,2,2));
	MainMenu.SetMenuBackImage(TEXT("Res\\Menu\\menu_right_bg.png"),&CRect(2,2,2,2));
	MainMenu.SetMenuHovenImage(TEXT("Res\\Menu\\menu_selected.png"),&CRect(2,2,2,2));
	MainMenu.SetSeparatorImage(TEXT("Res\\Menu\\menu_separtor.png"),&CRect(2,2,2,2));
	MainMenu.SetCheckImage(TEXT("Res\\Menu\\menu_check.png"));
	MainMenu.SetArrowImage(TEXT("Res\\Menu\\menu_arrow.png"));

	//MainMenu.SetFrameColor(RGB(255,0,0));
	//��ʾ�˵�
	MainMenu.TrackPopupMenu(this);

	__super::OnRButtonDown(nFlags,point);
}

BOOL CMenuDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case 3000:
		AfxMessageBox(TEXT("�������"));
		break;
	}

	return CDlgControlItem::OnCommand(wParam, lParam);
}

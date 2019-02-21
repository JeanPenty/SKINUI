// EditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "EditDlg.h"


// CEditDlg 对话框

IMPLEMENT_DYNAMIC(CEditDlg, CDlgControlItem)

CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_EDIT, pParent)
{
	m_dwStyle = 0;
}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT5,m_Edit);
 	DDX_Control(pDX,IDC_EDIT6,m_SkinEdit1);
 	DDX_Control(pDX,IDC_EDIT7,m_SkinEdit2);
	//DDX_Control(pDX,IDC_EDIT8,m_SkinEdit5);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDlgControlItem)
	ON_BN_CLICKED(IDC_BUTTON2, &CEditDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CEditDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CEditDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CEditDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CEditDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CEditDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CEditDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON13, &CEditDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON12, &CEditDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON1, &CEditDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_EDIT8, &CEditDlg::OnBnClickedPassWord)
	ON_BN_CLICKED(IDC_EDIT9, &CEditDlg::OnBnClickedFind)
END_MESSAGE_MAP()

void CEditDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	//
}


// CEditDlg 消息处理程序

BOOL CEditDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	m_dwStyle = GetDlgItem(IDC_EDIT5)->GetStyle();

	HDC hParentDC = GetBackDC();

	m_SkinEdit1.SetBackNormalImage(TEXT("Res\\Edit\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_SkinEdit1.SetBackHotImage(TEXT("Res\\Edit\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_SkinEdit1.SetDefaultText(TEXT("这是默认字符串"));
	m_SkinEdit1.SetDefaultTextMode(TRUE);
	m_SkinEdit1.SetParentBack(hParentDC);
	
	m_SkinEdit2.SetBackNormalImage(TEXT("Res\\Edit\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_SkinEdit2.SetBackHotImage(TEXT("Res\\Edit\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	//m_SkinEdit2.SetIconImage(TEXT("Res\\Edit\\keyboard.png"));
	m_SkinEdit2.SetWindowText(TEXT("这个控件是失效的"));
	//m_SkinEdit2.SetWindowPos(NULL,0,0,150,28,SWP_NOMOVE);
	m_SkinEdit2.SetParentBack(hParentDC);

 	RenderEngine->AddFont(TEXT("宋体"),8,false,false,false);
	m_SkinEdit3.Create(0,CRect(0,0,0,0),this,IDC_EDIT8);
	m_SkinEdit3.SetBackNormalImage(TEXT("Res\\Edit\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_SkinEdit3.SetBackHotImage(TEXT("Res\\Edit\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_SkinEdit3.SetIconImage(TEXT("Res\\Edit\\keyboard.png"));
	m_SkinEdit3.SetPasswordChar(0x25CF);
 	m_SkinEdit3.SetFont(CFont::FromHandle(RenderEngine->GetFont(0)));
	m_SkinEdit3.SetClientPoint(CPoint(3,3));
	m_SkinEdit3.SetParentBack(hParentDC);
	m_SkinEdit3.MoveWindow(240,280,210,24);

	static CSkinEdit m_SkinEdit4;
	m_SkinEdit4.SubclassWindow(GetDlgItem(IDC_EDIT2)->GetSafeHwnd());
	m_SkinEdit4.SetBackNormalImage(TEXT("Res\\Edit\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_SkinEdit4.SetBackHotImage(TEXT("Res\\Edit\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_SkinEdit4.SetScrollImage(&m_SkinEdit4,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));
	m_SkinEdit4.SetParentBack(hParentDC);

	m_SkinEdit5.Create(0,CRect(0,0,0,0),this,IDC_EDIT9);
	m_SkinEdit5.SetBackNormalImage(TEXT("Res\\Edit\\searchback.png"), CRect(9,9,9,9));
	RenderEngine->AddFont(TEXT("宋体"),12,false,false,false);
 	m_SkinEdit5.SetFont(CFont::FromHandle(RenderEngine->GetEndFont()));
	m_SkinEdit5.SetIconImage(TEXT("Res\\Edit\\group_seach.png"),true);
	m_SkinEdit5.SetClientPoint(CPoint(3,5));
	m_SkinEdit5.SetParentBack(hParentDC);
	m_SkinEdit5.MoveWindow(220,245,210,28);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CEditDlg::OnBnClickedButton2()
{
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT5);
	
	static bool bSet = true;

	SetWindowLong(pEdit->GetSafeHwnd(),GWL_STYLE,bSet?m_dwStyle|ES_NUMBER:m_dwStyle);

	pEdit->SetWindowText(TEXT("输入一下其他字符试试"));
	pEdit->SetSel(0,-1);
	pEdit->SetFocus();

	bSet=!bSet;
}

void CEditDlg::OnBnClickedButton3()
{	
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT5);

	static bool bSet = true;

	pEdit->SetPasswordChar(bSet?'*':NULL); 
	pEdit->SetSel(0,-1);
	pEdit->SetFocus();

	bSet=!bSet;
}

void CEditDlg::OnBnClickedButton4()
{
	CString str;

	//第一种
// 	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT5);
// 	pEdit->GetWindowText(str);

	//第二种
	GetDlgItemText(IDC_EDIT5,str);

	MessageBox(str);
}

void CEditDlg::OnBnClickedButton8()
{
	m_Edit.SetSel(0,-1);
	m_Edit.Copy();
}

void CEditDlg::OnBnClickedButton9()
{
	m_Edit.Paste();
}

void CEditDlg::OnBnClickedButton10()
{
	m_Edit.SetSel(0,-1);
	m_Edit.Cut();
}

void CEditDlg::OnBnClickedButton11()
{
	m_Edit.SetSel(0,-1);
	m_Edit.Clear();
}

void CEditDlg::OnBnClickedButton13()
{
	if( m_Edit.CanUndo() )
		m_Edit.Undo();
}

void CEditDlg::OnBnClickedButton12()
{
	static BOOL bOnlyRead = TRUE;

	m_Edit.SetReadOnly(bOnlyRead);

	bOnlyRead = !bOnlyRead;
}

void CEditDlg::OnBnClickedButton1()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/397.html"));
}

void CEditDlg::OnBnClickedPassWord()
{
	CString str;
	m_SkinEdit3.GetWindowText(str);

	MessageBox(str);
}

void CEditDlg::OnBnClickedFind()
{
	CString str;
	m_SkinEdit5.GetWindowText(str);

	MessageBox(TEXT("搜索")+str);
}

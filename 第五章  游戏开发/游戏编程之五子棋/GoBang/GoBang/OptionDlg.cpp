// OptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GoBang.h"
#include "OptionDlg.h"
#include "GoBangDlg.h"

// COptionDlg 对话框

IMPLEMENT_DYNAMIC(COptionDlg, CDialog)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPTION, pParent)
{

}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	ON_BN_CLICKED(IDOK, &COptionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COptionDlg 消息处理程序


BOOL COptionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CheckDlgButton(IDC_RADIO1,BST_CHECKED);
	CheckDlgButton(IDC_ME,BST_CHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void COptionDlg::OnBnClickedOk()
{
	bool bWhite = (IsDlgButtonChecked(IDC_RADIO1)==BST_CHECKED);
	bool bMe = (IsDlgButtonChecked(IDC_ME)==BST_CHECKED);

	((CGoBangDlg*)AfxGetMainWnd())->SetOption(bWhite,bMe);

	OnOK();
}
// OptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Landmine.h"
#include "OptionDlg.h"


// COptionDlg 对话框

IMPLEMENT_DYNAMIC(COptionDlg, CDialog)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPTION, pParent)
{
	m_nRowCount = 0;
	m_nColCount = 0;
	m_nMineCount = 0;
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

void COptionDlg::OnBnClickedOk()
{
	//获取数值
	m_nRowCount = GetDlgItemInt(IDC_EDIT_X);
	m_nColCount = GetDlgItemInt(IDC_EDIT_Y);
	m_nMineCount = GetDlgItemInt(IDC_EDIT_COUNT);

	//划定范围，目的是不让玩家乱写，弄的不是太小就是太大，影响用户体验
	if ( m_nRowCount<9 ) m_nRowCount = 9;
	if ( m_nColCount<9 ) m_nColCount = 9;
	if ( m_nMineCount<9 ) m_nMineCount = 10;

	if ( m_nRowCount>30 ) m_nRowCount = 30;
	if ( m_nColCount>30 ) m_nColCount = 30;
	if ( m_nMineCount>666 ) m_nMineCount = 667;

	OnOK();
}

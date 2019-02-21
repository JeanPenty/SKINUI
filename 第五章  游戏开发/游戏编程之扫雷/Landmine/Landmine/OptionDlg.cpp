// OptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Landmine.h"
#include "OptionDlg.h"


// COptionDlg �Ի���

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


// COptionDlg ��Ϣ�������

void COptionDlg::OnBnClickedOk()
{
	//��ȡ��ֵ
	m_nRowCount = GetDlgItemInt(IDC_EDIT_X);
	m_nColCount = GetDlgItemInt(IDC_EDIT_Y);
	m_nMineCount = GetDlgItemInt(IDC_EDIT_COUNT);

	//������Χ��Ŀ���ǲ��������д��Ū�Ĳ���̫С����̫��Ӱ���û�����
	if ( m_nRowCount<9 ) m_nRowCount = 9;
	if ( m_nColCount<9 ) m_nColCount = 9;
	if ( m_nMineCount<9 ) m_nMineCount = 10;

	if ( m_nRowCount>30 ) m_nRowCount = 30;
	if ( m_nColCount>30 ) m_nColCount = 30;
	if ( m_nMineCount>666 ) m_nMineCount = 667;

	OnOK();
}

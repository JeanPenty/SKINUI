// OptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Weather.h"
#include "OptionDlg.h"
#include "ParseJson.h"
#include <Shlwapi.h>

LPCTSTR szProvince[]=
{
	TEXT("������"),TEXT("�Ϻ���"),TEXT("�����"),TEXT("������"),TEXT("����ʡ"),TEXT("������ʡ"),TEXT("����ʡ"),TEXT("����������"),TEXT("�½�ά���������"),
	TEXT("���Ļ���������"),TEXT("�ຣʡ"),TEXT("����ʡ"),TEXT("����ʡ"),TEXT("����������"),TEXT("�Ĵ�ʡ"),TEXT("����ʡ"),TEXT("����ʡ"),TEXT("ɽ��ʡ"),
	TEXT("�ӱ�ʡ"),TEXT("ɽ��ʡ"),TEXT("����ʡ"),TEXT("����ʡ"),TEXT("����ʡ"),TEXT("����ʡ"),TEXT("����ʡ"),TEXT("����ʡ"),TEXT("�㽭ʡ"),
	TEXT("����ʡ"),TEXT("̨��ʡ"),TEXT("����ʡ"),TEXT("�㶫ʡ"),TEXT("����ر�������"),TEXT("����")
};

// COptionDlg �Ի���

IMPLEMENT_DYNAMIC(COptionDlg, CDialog)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{

}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_PROVINCE,m_comProvince);
	DDX_Control(pDX,IDC_CITY,m_comCity);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_PROVINCE, &COptionDlg::OnCbnSelchangeProvince)
	ON_BN_CLICKED(IDOK, &COptionDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK2, &COptionDlg::OnNMClickSyslink2)
END_MESSAGE_MAP()


// COptionDlg ��Ϣ�������

BOOL COptionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i=0;i<CountArray(szProvince);i++)
	{
		m_comProvince.AddString(szProvince[i]);
	}

	m_comProvince.SetCurSel(0);

	SetCityList(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void COptionDlg::SetCityList(int nSel)
{
	m_comCity.ResetContent();

	CString strText;
	m_comProvince.GetLBText(nSel,strText);

	CityInfoArray *pCityArray = CParseJson::GetInstance()->GetCityArray();
	CityInfoArray::iterator iter = pCityArray->begin();

	for (;iter != pCityArray->end(); ++iter )
	{
		if ( StrCmp((*iter)->strProvince,strText ) == 0 )
		{
			m_comCity.AddString((*iter)->strTitle);
		}
	}

	m_comCity.SetCurSel(0);
}

void COptionDlg::OnCbnSelchangeProvince()
{
	SetCityList(m_comProvince.GetCurSel());
}

void COptionDlg::OnBnClickedOk()
{
	m_comProvince.GetLBText(m_comProvince.GetCurSel(),m_strProvince);
	m_comCity.GetLBText(m_comCity.GetCurSel(),m_strCity);

	OnOK();
}

void COptionDlg::OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(NULL,TEXT("open"),TEXT("http://www.gymsaga.com"),NULL,NULL,SW_SHOWNORMAL);

	*pResult = 0;
}

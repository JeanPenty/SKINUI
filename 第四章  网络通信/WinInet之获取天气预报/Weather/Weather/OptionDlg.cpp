// OptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Weather.h"
#include "OptionDlg.h"
#include "ParseJson.h"
#include <Shlwapi.h>

LPCTSTR szProvince[]=
{
	TEXT("北京市"),TEXT("上海市"),TEXT("天津市"),TEXT("重庆市"),TEXT("吉林省"),TEXT("黑龙江省"),TEXT("辽宁省"),TEXT("内蒙自治区"),TEXT("新疆维吾尔自治区"),
	TEXT("宁夏回族自治区"),TEXT("青海省"),TEXT("甘肃省"),TEXT("陕西省"),TEXT("西藏自治区"),TEXT("四川省"),TEXT("贵州省"),TEXT("云南省"),TEXT("山西省"),
	TEXT("河北省"),TEXT("山东省"),TEXT("河南省"),TEXT("安徽省"),TEXT("江苏省"),TEXT("湖北省"),TEXT("湖南省"),TEXT("江西省"),TEXT("浙江省"),
	TEXT("福建省"),TEXT("台湾省"),TEXT("广西省"),TEXT("广东省"),TEXT("香港特别行政区"),TEXT("澳门")
};

// COptionDlg 对话框

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


// COptionDlg 消息处理程序

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
	// 异常: OCX 属性页应返回 FALSE
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

// LogonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "LogonDlg.h"


// CLogonDlg 对话框

IMPLEMENT_DYNAMIC(CLogonDlg, CDialog)

CLogonDlg::CLogonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGON, pParent)
{

}

CLogonDlg::~CLogonDlg()
{
}

void CLogonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogonDlg, CDialog)
	ON_BN_CLICKED(IDC_LOGON, &CLogonDlg::OnBnClickedLogon)
END_MESSAGE_MAP()


// CLogonDlg 消息处理程序

BOOL CLogonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//限制字符
	((CEdit*)GetDlgItem(IDC_USERNAME))->LimitText(32);
	((CEdit*)GetDlgItem(IDC_PASSWORD))->LimitText(32);

	//服务器地址
	TCHAR szServerAddr[33] = TEXT("127.0.0.1");

	CT2CA CurrentServer(szServerAddr);
	DWORD dwServerAddrIP=inet_addr(CurrentServer);
	if (dwServerAddrIP==INADDR_NONE)
	{
		LPHOSTENT lpHost=gethostbyname(CurrentServer);
		if (lpHost!=NULL) dwServerAddrIP=((LPIN_ADDR)lpHost->h_addr)->s_addr;
	}

	CIPAddressCtrl * pServerIP=(CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS);
	pServerIP->SetAddress(ntohl(dwServerAddrIP));

	//默认端口
	SetDlgItemInt(IDC_PORT,1038);

	//默认用户名
	SetDlgItemInt(IDC_USERNAME,GetTickCount());
	//默认密码
	SetDlgItemText(IDC_PASSWORD,TEXT("123456"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLogonDlg::OnBnClickedLogon()
{
	tagLogonInfo *pLogonInfo = new tagLogonInfo;

	//设置ip
	DWORD dwLogonIP=INADDR_NONE;
	BYTE * pAddrByte=(BYTE *)&dwLogonIP;
	((CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS))->GetAddress(dwLogonIP);
	_sntprintf_s(pLogonInfo->szServerAddr,CountArray(pLogonInfo->szServerAddr),TEXT("%d.%d.%d.%d"),pAddrByte[3],pAddrByte[2],pAddrByte[1],pAddrByte[0]);

	pLogonInfo->nPort = GetDlgItemInt(IDC_PORT);

	GetDlgItemText(IDC_USERNAME,pLogonInfo->szUserName,CountArray(pLogonInfo->szUserName));
	GetDlgItemText(IDC_PASSWORD,pLogonInfo->szPassWord,CountArray(pLogonInfo->szPassWord));

	//发送消息
	AfxGetMainWnd()->PostMessage(WM_USER_LOGON,(WPARAM)pLogonInfo);
}


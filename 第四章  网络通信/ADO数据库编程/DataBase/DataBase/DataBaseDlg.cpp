// DataBaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataBase.h"
#include "DataBaseDlg.h"
#include "DataBaseManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDataBaseDlg 对话框

//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))


CDataBaseDlg::CDataBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataBaseDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CDataBaseDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_QUERY, &CDataBaseDlg::OnBnClickedQuery)
	ON_BN_CLICKED(IDC_QUERY2, &CDataBaseDlg::OnBnClickedQuery2)
END_MESSAGE_MAP()


// CDataBaseDlg 消息处理程序

BOOL CDataBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS))->SetAddress(inet_addr(CT2CA(TEXT("1.0.0.127"))));
	SetDlgItemText(IDC_PORT,TEXT("1433"));
	SetDlgItemText(IDC_DATANAME,TEXT("master"));
	SetDlgItemText(IDC_USERNAME,TEXT("sa"));
	SetDlgItemText(IDC_USERPASS,TEXT("sa"));

	m_ListCtrl.InsertColumn( 0, TEXT("UserID"), LVCFMT_LEFT, 50 );
	m_ListCtrl.InsertColumn( 1, TEXT("NickName"), LVCFMT_LEFT, 100 );
	m_ListCtrl.InsertColumn( 2, TEXT("LogonPass"), LVCFMT_LEFT, 100 );
	m_ListCtrl.InsertColumn( 3, TEXT("Experience"), LVCFMT_LEFT, 100 );
	m_ListCtrl.InsertColumn( 4, TEXT("Gender"), LVCFMT_LEFT, 50 );
	m_ListCtrl.InsertColumn( 5, TEXT("IsAndroid"), LVCFMT_LEFT, 100 );

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDataBaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDataBaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDataBaseDlg::OnBnClickedQuery()
{
	ExecuteQuery(false);
}

void CDataBaseDlg::OnBnClickedQuery2()
{
	ExecuteQuery(true);
}

void CDataBaseDlg::ExecuteQuery(bool bSentence)
{
	DWORD dwDataBaseAddr = 0;
	WORD wDataBasePort = 0;

	CString szDataBaseName,szDataBaseUser,szDataBasePass;

	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS))->GetAddress(dwDataBaseAddr);
	wDataBasePort = GetDlgItemInt(IDC_PORT);
	GetDlgItemText(IDC_DATANAME,szDataBaseName);
	GetDlgItemText(IDC_USERNAME,szDataBaseUser);
	GetDlgItemText(IDC_USERPASS,szDataBasePass);

	//创建数据库
	CDataBaseHelper   ServerInfoDBAide;
	CDataBase		ServerInfoDBModule;

	try
	{
		//转化地址
		TCHAR szDataBaseAdr[16]=TEXT("");
		BYTE * pcbDataBaseAdr=(BYTE *)&dwDataBaseAddr;
		_sntprintf_s(szDataBaseAdr,-1,TEXT("%d.%d.%d.%d"),pcbDataBaseAdr[3],pcbDataBaseAdr[2],pcbDataBaseAdr[1],pcbDataBaseAdr[0]);

		//连接数据库
		ServerInfoDBModule.SetConnectionInfo(szDataBaseAdr,wDataBasePort,szDataBaseName,szDataBaseUser,szDataBasePass);

		//发起连接
		ServerInfoDBModule.OpenConnection();
		ServerInfoDBAide.SetDataBase(&ServerInfoDBModule);

		//执行命令
		ServerInfoDBAide.ResetParameter();

		if( bSentence )
			ServerInfoDBAide.ExecuteSentence(TEXT("SELECT * FROM UserData"),true);
		else
			ServerInfoDBAide.ExecuteProcess(TEXT("GSP_LoadUserData"),true);

		//变量定义
		TCHAR szNickName[32];
		TCHAR szLogonPass[32];
		CString strUserID,strExperience;

		//清空节点
		m_ListCtrl.DeleteAllItems();

		//读取信息
		while (ServerInfoDBModule.IsRecordsetEnd()==false)
		{
			//读取信息
			DWORD dwUserID=ServerInfoDBAide.GetValue_WORD(TEXT("UserID"));
			LONG lExperience=ServerInfoDBAide.GetValue_LONG(TEXT("Experience"));
			BYTE cbGender=ServerInfoDBAide.GetValue_BYTE(TEXT("Gender"));
			BYTE cbIsAndroid = ServerInfoDBAide.GetValue_BYTE(TEXT("IsAndroid"));

			ServerInfoDBAide.GetValue_String(TEXT("NickName"),szNickName,CountArray(szNickName));
			ServerInfoDBAide.GetValue_String(TEXT("LogonPass"),szLogonPass,CountArray(szLogonPass));

			//插入节点
			strUserID.Format(TEXT("%d"),dwUserID);
			strExperience.Format(TEXT("%ld"),lExperience);

			int nCount = m_ListCtrl.GetItemCount();
			int nRow = m_ListCtrl.InsertItem(LVIF_IMAGE|LVIF_TEXT|LVIF_PARAM,0,strUserID,0,0,2,0);

			m_ListCtrl.SetItemText(nRow, 1, szNickName);
			m_ListCtrl.SetItemText(nRow, 2, szLogonPass);
			m_ListCtrl.SetItemText(nRow, 3, strExperience);
			m_ListCtrl.SetItemText(nRow, 4, cbGender?TEXT("男"):TEXT("女"));
			m_ListCtrl.SetItemText(nRow, 5, cbIsAndroid?TEXT("是"):TEXT("否"));

			//移动记录
			ServerInfoDBModule.MoveToNext();
		}

		//关闭记录
		ServerInfoDBModule.CloseRecordset();

		return;
	}
	catch (CADOError * pIException)
	{
		//错误信息
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		AfxMessageBox(pszDescribe);

		return;
	}
}

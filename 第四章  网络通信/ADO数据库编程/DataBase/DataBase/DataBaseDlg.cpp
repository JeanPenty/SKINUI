// DataBaseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataBase.h"
#include "DataBaseDlg.h"
#include "DataBaseManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDataBaseDlg �Ի���

//����ά��
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


// CDataBaseDlg ��Ϣ�������

BOOL CDataBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDataBaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	//�������ݿ�
	CDataBaseHelper   ServerInfoDBAide;
	CDataBase		ServerInfoDBModule;

	try
	{
		//ת����ַ
		TCHAR szDataBaseAdr[16]=TEXT("");
		BYTE * pcbDataBaseAdr=(BYTE *)&dwDataBaseAddr;
		_sntprintf_s(szDataBaseAdr,-1,TEXT("%d.%d.%d.%d"),pcbDataBaseAdr[3],pcbDataBaseAdr[2],pcbDataBaseAdr[1],pcbDataBaseAdr[0]);

		//�������ݿ�
		ServerInfoDBModule.SetConnectionInfo(szDataBaseAdr,wDataBasePort,szDataBaseName,szDataBaseUser,szDataBasePass);

		//��������
		ServerInfoDBModule.OpenConnection();
		ServerInfoDBAide.SetDataBase(&ServerInfoDBModule);

		//ִ������
		ServerInfoDBAide.ResetParameter();

		if( bSentence )
			ServerInfoDBAide.ExecuteSentence(TEXT("SELECT * FROM UserData"),true);
		else
			ServerInfoDBAide.ExecuteProcess(TEXT("GSP_LoadUserData"),true);

		//��������
		TCHAR szNickName[32];
		TCHAR szLogonPass[32];
		CString strUserID,strExperience;

		//��սڵ�
		m_ListCtrl.DeleteAllItems();

		//��ȡ��Ϣ
		while (ServerInfoDBModule.IsRecordsetEnd()==false)
		{
			//��ȡ��Ϣ
			DWORD dwUserID=ServerInfoDBAide.GetValue_WORD(TEXT("UserID"));
			LONG lExperience=ServerInfoDBAide.GetValue_LONG(TEXT("Experience"));
			BYTE cbGender=ServerInfoDBAide.GetValue_BYTE(TEXT("Gender"));
			BYTE cbIsAndroid = ServerInfoDBAide.GetValue_BYTE(TEXT("IsAndroid"));

			ServerInfoDBAide.GetValue_String(TEXT("NickName"),szNickName,CountArray(szNickName));
			ServerInfoDBAide.GetValue_String(TEXT("LogonPass"),szLogonPass,CountArray(szLogonPass));

			//����ڵ�
			strUserID.Format(TEXT("%d"),dwUserID);
			strExperience.Format(TEXT("%ld"),lExperience);

			int nCount = m_ListCtrl.GetItemCount();
			int nRow = m_ListCtrl.InsertItem(LVIF_IMAGE|LVIF_TEXT|LVIF_PARAM,0,strUserID,0,0,2,0);

			m_ListCtrl.SetItemText(nRow, 1, szNickName);
			m_ListCtrl.SetItemText(nRow, 2, szLogonPass);
			m_ListCtrl.SetItemText(nRow, 3, strExperience);
			m_ListCtrl.SetItemText(nRow, 4, cbGender?TEXT("��"):TEXT("Ů"));
			m_ListCtrl.SetItemText(nRow, 5, cbIsAndroid?TEXT("��"):TEXT("��"));

			//�ƶ���¼
			ServerInfoDBModule.MoveToNext();
		}

		//�رռ�¼
		ServerInfoDBModule.CloseRecordset();

		return;
	}
	catch (CADOError * pIException)
	{
		//������Ϣ
		LPCTSTR pszDescribe=pIException->GetExceptionDescribe();
		AfxMessageBox(pszDescribe);

		return;
	}
}

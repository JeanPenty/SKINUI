#pragma once


// CLogonDlg �Ի���
struct tagLogonInfo
{
	UINT	nPort;							//����˿�
	TCHAR	szUserName[33];					//�û��ʺ�
	TCHAR	szPassWord[33];					//�û�����
	TCHAR	szServerAddr[33];				//�����ַ
};

#define WM_USER_LOGON				WM_USER+0x01
//////////////////////////////////////////////////////////////////////////

class CLogonDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogonDlg)

public:
	CLogonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogonDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	virtual BOOL OnInitDialog();
	
public:
	//��½��Ϣ
	afx_msg void OnBnClickedLogon();


	DECLARE_MESSAGE_MAP()
};

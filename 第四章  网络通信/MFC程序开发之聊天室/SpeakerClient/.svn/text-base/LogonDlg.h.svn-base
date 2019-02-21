#pragma once


// CLogonDlg 对话框
struct tagLogonInfo
{
	UINT	nPort;							//服务端口
	TCHAR	szUserName[33];					//用户帐号
	TCHAR	szPassWord[33];					//用户密码
	TCHAR	szServerAddr[33];				//服务地址
};

#define WM_USER_LOGON				WM_USER+0x01
//////////////////////////////////////////////////////////////////////////

class CLogonDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogonDlg)

public:
	CLogonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogonDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	virtual BOOL OnInitDialog();
	
public:
	//登陆消息
	afx_msg void OnBnClickedLogon();


	DECLARE_MESSAGE_MAP()
};

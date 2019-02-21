// SpeakerClientDlg.h : 头文件
//

#pragma once

#include "TCPScoketClient.h"
#include "LogonDlg.h"

// CSpeakerClientDlg 对话框
class CSpeakerClientDlg : public CDialog,public ITCPScoketClient
{
protected:
	CTCPScoketClient			m_TCPScoketClient;			//SCOKET接口
	tagUserData					m_UserData;					//用户数据
	
	HICON						m_hIcon;					//程序图标
	CLogonDlg					m_LogonDlg;					//登陆窗口
	CListBox					m_ListUser;					//用户列表

	//构造
public:
	CSpeakerClientDlg(CWnd* pParent = NULL);

protected:
	//初始化
	virtual BOOL OnInitDialog();
	//控件绑定
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	//窗口退出
	virtual void OnCancel();
	
	//网络消息
public:
	//接收消息
	virtual void OnReceive(int nErrorCode);
	//关闭事件
	virtual void OnClose(int nErrorCode);
	//子消息事件
	bool OnEventTCPSocketRead( WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);

	//功能函数
public:
	//跟踪提醒
	void SetTraceString(LPCTSTR lpStr, ...);

	//消息实现
protected:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//发送消息
	afx_msg void OnBnClickedSend();
	//登陆消息
	LRESULT OnLogonMessage(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

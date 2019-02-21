// SpeakerServerDlg.h : 头文件
//

#pragma once
#include "TCPSocketService.h"
#include "TraceRichEdit.h"
#include "UserManager.h"

#include <map>
using namespace std;
		
//绑定数据
struct tagBindParameter 
{
	CTCPSocketService		* pTCPSocketService;		//绑定套接字
	DWORD					dwUserID;					//用户标识
};

typedef map<SOCKET,tagBindParameter*>			CTCPSocketItemMap;

// CSpeakerServerDlg 对话框
class CSpeakerServerDlg : public CDialog,public ITCPSocketService
{
protected:
	CTCPSocketService			m_TCPSocketListen;				//SOCKET套接字
	CTraceRichEdit				m_TraceRichEdit;				//Rich控件
	CUserManager				*m_pUserManager;				//用户管理

	CTCPSocketItemMap			m_TCPSocketItemMap;				//连接套接字
	HICON						m_hIcon;						//程序图标

	//构造
public:
	CSpeakerServerDlg(CWnd* pParent = NULL);	// 标准构造函数

protected:
	//初始化
	virtual BOOL OnInitDialog();
	//绑定控件
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	//退出消息
	virtual void OnCancel();

	//网络消息
public:
	//接收消息
	virtual void OnReceive(SOCKET hSocket);
	//监听消息
	virtual void OnAccept();
	//关闭消息
	virtual void OnClose(SOCKET hSocket);

	//功能函数
public:
	//子消息事件
	bool OnEventTCPSocketRead( SOCKET hSocket,WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
	//群发消息
	VOID SendDataBatch(WORD wMainCmdID, WORD wSubCmdID,VOID * pData=NULL, WORD wDataSize=NULL);
	//发送用户列表
	VOID SendUserItem(CTCPSocketService *pTCPSocketService,tagUserData *pUserData);

	//实现
protected:
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//启动消息
	afx_msg void OnBnClickedStart();
	//停止消息
	afx_msg void OnBnClickedStop();

	DECLARE_MESSAGE_MAP()
};

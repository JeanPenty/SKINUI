// SpeakerClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SpeakerClient.h"
#include "SpeakerClientDlg.h"
#include "LogonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpeakerClientDlg 对话框

CSpeakerClientDlg::CSpeakerClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SPEAKERCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ZeroMemory(&m_UserData,sizeof m_UserData);
}

void CSpeakerClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LISTUSER,m_ListUser);
}

BEGIN_MESSAGE_MAP(CSpeakerClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SEND, &CSpeakerClientDlg::OnBnClickedSend)
	ON_MESSAGE(WM_USER_LOGON,OnLogonMessage)
END_MESSAGE_MAP()


// CSpeakerClientDlg 消息处理程序

BOOL CSpeakerClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetTraceString(TEXT("未连接"));

	//创建登陆窗口
	m_LogonDlg.Create(IDD_LOGON,this);
	m_LogonDlg.CenterWindow();
	m_LogonDlg.ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSpeakerClientDlg::OnPaint()
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
HCURSOR CSpeakerClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSpeakerClientDlg::OnReceive( int nErrorCode )
{
	//接收消息
	BYTE cbDataBuffer[SOCKET_TCP_BUFFER];
	m_TCPScoketClient.Receive(cbDataBuffer,CountArray(cbDataBuffer) );

	//解析数据
	TCP_Command * pCommand=(TCP_Command *)cbDataBuffer;

	//解释数据
	WORD wPacketSize = pCommand->wPacketSize;
	WORD wDataSize = wPacketSize-sizeof(TCP_Command);

	//数据包效验
	if ( wPacketSize > SOCKET_TCP_BUFFER+sizeof TCP_Command )
	{
		SetTraceString(TEXT("数据包太大，已拒绝"));
		return;
	}

	//子消息处理事件
	if( !OnEventTCPSocketRead(pCommand->wMainCmdID,pCommand->wSubCmdID,pCommand+1,wDataSize) )
	{
		SetTraceString(TEXT("收到未处理的数据包,wMainCmdID:%d,wSubCmdID:%d"),pCommand->wMainCmdID,pCommand->wSubCmdID);
		return;
	}
}

void CSpeakerClientDlg::OnClose( int nErrorCode )
{
	AfxMessageBox(TEXT("服务器连接失败，可能服务器已关闭或本机网络断开"));
}

void CSpeakerClientDlg::OnCancel()
{
	//关闭套接字
	m_TCPScoketClient.Close();

	CDialog::OnCancel();
}

void CSpeakerClientDlg::SetTraceString( LPCTSTR lpStr, ... )
{
	CString StrTraceString;

	va_list argList;
	va_start( argList, lpStr );
	StrTraceString.FormatV( lpStr, argList );
	va_end( argList );

	SetDlgItemText(IDC_STATE,StrTraceString);
}

void CSpeakerClientDlg::OnBnClickedSend()
{
	//设置数据
	CMD_CS_CHATMSG _UserChat_Msg;
	ZeroMemory(&_UserChat_Msg,sizeof _UserChat_Msg);

	GetDlgItemText(IDC_EDITCHAT,_UserChat_Msg.szDescribe,CountArray(_UserChat_Msg.szDescribe));

	//效验数据
	if ( _UserChat_Msg.szDescribe[0] == TEXT('\0') )
	{
		SetTraceString(TEXT("聊天内容为空，请先输入您想说的话"));
		return;
	}

	//发送数据
	m_TCPScoketClient.SendData(MDM_GP_USER,SUB_CS_USERT_CHAT,&_UserChat_Msg,sizeof _UserChat_Msg);
}

bool CSpeakerClientDlg::OnEventTCPSocketRead( WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize )
{
	switch ( wMainCmdID )
	{
	case MDM_GP_LOGON:		//登陆消息
		{
			if ( wSubCmdID == SUB_SC_USERCOME)		//用户进入
			{
				CMD_SC_USERCOME *pUserCome = (CMD_SC_USERCOME*)pData;	
				
				//插入数据
				if( m_ListUser.FindString(-1,pUserCome->szUserName) == LB_ERR )
				{
					//设置自己信息
					if ( m_UserData.dwUserID == 0 )
					{
						_sntprintf_s(m_UserData.szUserName,CountArray(m_UserData.szUserName),pUserCome->szUserName);
						m_UserData.dwUserID = m_UserData.dwUserID;

						SetWindowText(m_UserData.szUserName);
					}

					//添加用户列表
					m_ListUser.AddString(pUserCome->szUserName);
					m_ListUser.SetItemData(m_ListUser.GetCount()-1,pUserCome->dwUserID);
				}
				
				return true;
			}
			break;
		}
	case MDM_GP_USER:			//用户消息
		{
			if ( wSubCmdID == SUB_CS_USERT_CHAT )			//聊天消息
			{
				CMD_SC_CHATMSG *pCHATMSG = (CMD_SC_CHATMSG*)pData;	

				//设置聊天数据
				static CString str;

				CString StrDescribe;
				StrDescribe.Format(TEXT("%s  %04d-%02d-%02d %02d:%02d:%02d\r\n"),pCHATMSG->szSendUserName,pCHATMSG->SystemTime.wYear, pCHATMSG->SystemTime.wMonth, 
					pCHATMSG->SystemTime.wDay, pCHATMSG->SystemTime.wHour, pCHATMSG->SystemTime.wMinute, pCHATMSG->SystemTime.wSecond);
				
				str += StrDescribe;
				str += pCHATMSG->szDescribe;
				str += TEXT("\r\n");

				SetDlgItemText(IDC_CHATRECV,str);

				return true;
			}
			else if ( wSubCmdID == SUB_SC_DELETE )			//用户退出消息
			{
				CMD_DC_DELETE *pDeleteUser = (CMD_DC_DELETE*)pData;

				int nIndex = m_ListUser.FindString(-1,pDeleteUser->szUserName);
				if ( nIndex != LB_ERR )
				{
					m_ListUser.DeleteString(nIndex);
				}

				return true;
				
			}
			break;
		}
	}
	return false;
}

//登陆消息
LRESULT CSpeakerClientDlg::OnLogonMessage( WPARAM wParam,LPARAM lParam )
{
	tagLogonInfo *pLogonInfo = (tagLogonInfo*)wParam;

	//关闭之前socket
	m_TCPScoketClient.Close();

	//初始化套接字
	if ( !m_TCPScoketClient.Create() )
	{
		SetTraceString(TEXT("套接字创建失败"));
		SafeDelete(pLogonInfo);
		return FALSE;
	}

	//创建连接
	if( m_TCPScoketClient.Connect(pLogonInfo->szServerAddr,pLogonInfo->nPort) == FALSE )
	{
		int nErrorCode = m_TCPScoketClient.GetLastError();

		if ( nErrorCode !=WSAEWOULDBLOCK )
		{
			SetTraceString(TEXT("连接服务器失败,错误码：%d"),nErrorCode);
			SafeDelete(pLogonInfo);
			return FALSE;
		}
	}

	//设置接口
	m_TCPScoketClient.SetTCPSocketService(this);

	//构建数据
	CMD_CS_LOGON UserLogon;
	ZeroMemory(&UserLogon,sizeof UserLogon);

	_sntprintf_s(UserLogon.szUserName,CountArray(UserLogon.szUserName),pLogonInfo->szUserName);
	_sntprintf_s(UserLogon.szPassWord,CountArray(UserLogon.szPassWord),pLogonInfo->szPassWord);

	//发送登陆请求
	m_TCPScoketClient.SendData(MDM_GP_LOGON,SUB_CS_LOGON,&UserLogon,sizeof UserLogon);

	//设置界面
	SetTraceString(TEXT("连接服务器成功"));
	m_LogonDlg.PostMessage(WM_CLOSE);

	//清理数据
	SafeDelete(pLogonInfo);

	return TRUE;
}

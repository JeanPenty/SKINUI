// SpeakerServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SpeakerServer.h"
#include "SpeakerServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpeakerServerDlg 对话框
CSpeakerServerDlg::CSpeakerServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SPEAKERSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TCPSocketItemMap.clear();
}

void CSpeakerServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_RICHEDIT21,m_TraceRichEdit);
}

BEGIN_MESSAGE_MAP(CSpeakerServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START, &CSpeakerServerDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CSpeakerServerDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CSpeakerServerDlg 消息处理程序

BOOL CSpeakerServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetDlgItemInt(IDC_PORT,1038);
	SetDlgItemInt(IDC_MAX,1024);

	m_pUserManager = CUserManager::GetInstance();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSpeakerServerDlg::OnPaint()
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
HCURSOR CSpeakerServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSpeakerServerDlg::OnBnClickedStart()
{
	UINT uPort = GetDlgItemInt(IDC_PORT);

	//创建套接字
	if ( !m_TCPSocketListen.Create(uPort) )
	{
		m_TraceRichEdit.TraceString(TEXT("绑定监听端口失败,请确认该端口没有被其它程序占用"),TraceLevel_Warning);
		return;
	}

	//监听套接字
	if( !m_TCPSocketListen.Listen() )
	{
		m_TraceRichEdit.TraceString(TEXT("监听失败"),TraceLevel_Warning);
		return;
	}

	UINT uMaxConnect = GetDlgItemInt(IDC_MAX);

	//设置接口
	m_TCPSocketListen.SetTCPSocketService(this);

	//更新界面
	m_TraceRichEdit.TraceString(TEXT("服务器启动成功"),TraceLevel_Normal);
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
}

void CSpeakerServerDlg::OnReceive(SOCKET hSocket)
{
	BYTE cbDataBuffer[SOCKET_TCP_BUFFER];

	CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.find(hSocket);
	if ( iter == m_TCPSocketItemMap.end() ) return;
	
	//接收数据
	iter->second->pTCPSocketService->Receive(cbDataBuffer,CountArray(cbDataBuffer) );

	//解析数据
	TCP_Command * pCommand=(TCP_Command *)cbDataBuffer;
	
	//解释数据
	WORD wPacketSize = pCommand->wPacketSize;
	WORD wDataSize = wPacketSize-sizeof(TCP_Command);

	//数据包效验
	if ( wPacketSize > SOCKET_TCP_BUFFER+sizeof TCP_Command )
	{
		m_TraceRichEdit.TraceString(TEXT("数据包太大，已拒绝"),TraceLevel_Warning);
		return;
	}

	//子消息处理事件
	if( !OnEventTCPSocketRead(hSocket,pCommand->wMainCmdID,pCommand->wSubCmdID,pCommand+1,wDataSize) )
	{
		BYTE * pClientIP=(BYTE *)&iter->second->pTCPSocketService->m_dwClientAddr;
		m_TraceRichEdit.TraceString(TraceLevel_Warning,TEXT("收到伪数据包或未处理的数据包,wMainCmdID:%d,wSubCmdID:%d,来源IP:%d.%d.%d.%d"),pCommand->wMainCmdID,pCommand->wSubCmdID,pClientIP[0],pClientIP[1],pClientIP[2],pClientIP[3]);

		return;
	}
}

void CSpeakerServerDlg::OnAccept()
{
	//承载能力
	if ( m_TCPSocketItemMap.size() > GetDlgItemInt(IDC_MAX) )
	{
		m_TraceRichEdit.TraceString(TEXT("服务器承载人数已满，已过滤其他连接"),TraceLevel_Warning);
		return;
	}

	//绑定套接字
	CTCPSocketService *pTCPSocketConnect = new CTCPSocketService;

 	try
 	{
 		SOCKADDR_IN	SocketAddr;
 		int nBufferSize = sizeof(SocketAddr);
 
		//绑定套接字
 		m_TCPSocketListen.Accept(*pTCPSocketConnect,(SOCKADDR *) &SocketAddr, &nBufferSize);
 		if (pTCPSocketConnect->m_hSocket == INVALID_SOCKET) throw TEXT("无效的连接套接字");
 
		//获取客户端IP
 		pTCPSocketConnect->m_dwClientAddr = SocketAddr.sin_addr.S_un.S_addr;
 		pTCPSocketConnect->SetTCPSocketService(this);

		//绑定数据
		bool bActive = true;

		CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.begin();

		for (;iter!= m_TCPSocketItemMap.end();iter++)
		{
			if ( pTCPSocketConnect->m_hSocket == iter->first )
			{
				bActive = false;
				break;
			}
		}

		//插入数据
		if ( bActive )
		{
			tagBindParameter *pBindParameter = new tagBindParameter;
			pBindParameter->pTCPSocketService = pTCPSocketConnect;
			pBindParameter->dwUserID = 0;

			m_TCPSocketItemMap.insert(pair<SOCKET,tagBindParameter*>(pTCPSocketConnect->m_hSocket,pBindParameter));
		}
 	}
 	catch (...)
 	{
		if (pTCPSocketConnect->m_hSocket != INVALID_SOCKET)	pTCPSocketConnect->Close();
 	}
}

void CSpeakerServerDlg::OnClose(SOCKET hSocket)
{
	CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.find(hSocket);
	if ( iter == m_TCPSocketItemMap.end() ) return;

	//获取用户
	m_TraceRichEdit.TraceString(TraceLevel_Normal,TEXT("%s退出了服务器"),m_pUserManager->GetUserName(iter->second->dwUserID));

	//删除用户
	CMD_DC_DELETE _DC_DELETE;
	ZeroMemory(&_DC_DELETE,sizeof _DC_DELETE);

	_sntprintf_s(_DC_DELETE.szUserName,CountArray(_DC_DELETE.szUserName),m_pUserManager->GetUserName(iter->second->dwUserID));

	//群发消息
	SendDataBatch(MDM_GP_USER,SUB_SC_DELETE,&_DC_DELETE,sizeof _DC_DELETE);

	//销毁数据
	m_pUserManager->RemoveUserItem(iter->second->dwUserID);
	iter->second->pTCPSocketService->Close();
	SafeDelete(iter->second->pTCPSocketService);
	SafeDelete(iter->second);

	m_TCPSocketItemMap.erase(iter);
}

void CSpeakerServerDlg::OnBnClickedStop()
{
	//关闭监听套接字
	m_TCPSocketListen.Close();

	//关闭连接套接字
	CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.begin();
	for (;iter != m_TCPSocketItemMap.end(); ++iter)
	{
		iter->second->pTCPSocketService->Close();
		SafeDelete(iter->second->pTCPSocketService);
		SafeDelete(iter->second);
	}

	//更新界面
	m_TraceRichEdit.TraceString(TEXT("服务器关闭成功"),TraceLevel_Normal);

	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
}

void CSpeakerServerDlg::OnCancel()
{
	if ( m_TCPSocketListen.m_hSocket != INVALID_SOCKET )
	{
		if ( AfxMessageBox(TEXT("确定退出服务器吗?其它所有用户将失去连接"),MB_YESNO|MB_ICONQUESTION) == IDYES )
		{
			CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.begin();

			for (;iter != m_TCPSocketItemMap.end(); ++iter)
			{
				iter->second->pTCPSocketService->Close();
				SafeDelete(iter->second->pTCPSocketService);
				SafeDelete(iter->second);
			}
		}
	}

	__super::OnCancel();
}

bool CSpeakerServerDlg::OnEventTCPSocketRead( SOCKET hSocket,WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize )
{
	//获取绑定套接字
	CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.find(hSocket);
	if ( iter == m_TCPSocketItemMap.end() ) return false;

	CTCPSocketService *pTCPSocketService = iter->second->pTCPSocketService;

	switch ( wMainCmdID )
	{
	case MDM_GP_LOGON:
		{
			if ( wSubCmdID == SUB_CS_LOGON )
			{
				//效验数据
				ASSERT( wDataSize == sizeof CMD_CS_LOGON );
				if ( wDataSize != sizeof CMD_CS_LOGON ) return false;
				
				//获取数据
				CMD_CS_LOGON *pUserLogon = (CMD_CS_LOGON*)pData;

				m_TraceRichEdit.TraceString(TraceLevel_Normal,TEXT("%s登陆服务器"),pUserLogon->szUserName);

				tagUserData *pUserData = new tagUserData;
				//随机给用户分配一个UserID，UserID一般存储于数据库中，是一个独一无二的数字，
				//一般在数据库表中设为主键，是整个游戏或者软件识别用户的唯一依据,这里我们没有涉及到数据库，暂时随机取一个数值代替
				
				//其次，我们应该通过数据库SQL语句查询或者存储过程等方法，或在数据库中做密码的效验也好，
				//或在查询到用户的密码在服务器中进行判断也好，不管什么方法，此处一般需要进行用户密码的效验，这样才可以判定用户是否可以登陆了
				
				pUserData->dwUserID = GetTickCount();
				_sntprintf_s(pUserData->szUserName,CountArray(pUserData->szUserName),pUserLogon->szUserName);
				_sntprintf_s(pUserData->szPassWord,CountArray(pUserData->szPassWord),pUserLogon->szPassWord);

				//更新绑定数据
				CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.find(hSocket);
				if ( iter != m_TCPSocketItemMap.end() )
					iter->second->dwUserID = pUserData->dwUserID;

				//群发登陆消息
				SendUserItem(NULL,pUserData);

				//发送在线用户
				CUserItemArray::iterator pUserItemSend = m_pUserManager->GetUserItemArray()->begin();
				for (;pUserItemSend!=m_pUserManager->GetUserItemArray()->end();pUserItemSend++ )
					SendUserItem(pTCPSocketService,pUserItemSend->second);

				//插入数据
				m_pUserManager->InsertUserItem(pUserData);
				
				return true;
			}
		}
		break;
	case MDM_GP_USER:
		{
			if ( wSubCmdID == SUB_CS_USERT_CHAT )
			{
				//获取数据
				CMD_CS_CHATMSG *pCHATMSG = (CMD_CS_CHATMSG*)pData;

				//这里其实需要做很多的效验，如dwSendUserID的有效性，字符串是否为空等，这里就不做这些效验了
				CMD_SC_CHATMSG _SC_CHATMSG;
				ZeroMemory(&_SC_CHATMSG,sizeof _SC_CHATMSG);

				//获取时间
				GetLocalTime(&_SC_CHATMSG.SystemTime);
				_sntprintf_s(_SC_CHATMSG.szSendUserName,CountArray(_SC_CHATMSG.szSendUserName),m_pUserManager->GetUserName(iter->second->dwUserID));
				_sntprintf_s(_SC_CHATMSG.szDescribe,CountArray(_SC_CHATMSG.szDescribe),pCHATMSG->szDescribe);

				SendDataBatch(MDM_GP_USER,SUB_CS_USERT_CHAT,&_SC_CHATMSG,sizeof _SC_CHATMSG);
				
				return true;
			}
		}
		break;
	}


	return false;
}

//发送用户列表
VOID CSpeakerServerDlg::SendUserItem(CTCPSocketService *pTCPSocketService,tagUserData *pUserData)
{
	//效验数据
	ASSERT( pUserData != NULL );
	if ( pUserData == NULL ) return;

	//构建数据
	CMD_SC_USERCOME _UserCome;
	ZeroMemory(&_UserCome,sizeof _UserCome);

	_UserCome.dwUserID = pUserData->dwUserID;
	_sntprintf_s(_UserCome.szUserName,CountArray(_UserCome.szUserName),pUserData->szUserName);

	if ( pTCPSocketService == NULL )
	{
		//群发用户进入消息
		SendDataBatch(MDM_GP_LOGON,SUB_SC_USERCOME,&_UserCome,sizeof _UserCome);
	}
	else
	{
		pTCPSocketService->SendData(MDM_GP_LOGON,SUB_SC_USERCOME,&_UserCome,sizeof _UserCome);
	}

	//延迟一下
	Sleep(5);

	return;
}

VOID CSpeakerServerDlg::SendDataBatch( WORD wMainCmdID, WORD wSubCmdID,VOID * pData, WORD wDataSize )
{
	//枚举数据
	CTCPSocketItemMap::iterator iter = m_TCPSocketItemMap.begin();

	for (;iter != m_TCPSocketItemMap.end();iter++)
	{
		iter->second->pTCPSocketService->SendData(wMainCmdID,wSubCmdID,pData,wDataSize);
	}
}

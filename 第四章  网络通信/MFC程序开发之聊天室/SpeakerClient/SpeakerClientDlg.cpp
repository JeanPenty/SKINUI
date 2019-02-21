// SpeakerClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SpeakerClient.h"
#include "SpeakerClientDlg.h"
#include "LogonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpeakerClientDlg �Ի���

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


// CSpeakerClientDlg ��Ϣ�������

BOOL CSpeakerClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SetTraceString(TEXT("δ����"));

	//������½����
	m_LogonDlg.Create(IDD_LOGON,this);
	m_LogonDlg.CenterWindow();
	m_LogonDlg.ShowWindow(SW_SHOW);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSpeakerClientDlg::OnPaint()
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
HCURSOR CSpeakerClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSpeakerClientDlg::OnReceive( int nErrorCode )
{
	//������Ϣ
	BYTE cbDataBuffer[SOCKET_TCP_BUFFER];
	m_TCPScoketClient.Receive(cbDataBuffer,CountArray(cbDataBuffer) );

	//��������
	TCP_Command * pCommand=(TCP_Command *)cbDataBuffer;

	//��������
	WORD wPacketSize = pCommand->wPacketSize;
	WORD wDataSize = wPacketSize-sizeof(TCP_Command);

	//���ݰ�Ч��
	if ( wPacketSize > SOCKET_TCP_BUFFER+sizeof TCP_Command )
	{
		SetTraceString(TEXT("���ݰ�̫���Ѿܾ�"));
		return;
	}

	//����Ϣ�����¼�
	if( !OnEventTCPSocketRead(pCommand->wMainCmdID,pCommand->wSubCmdID,pCommand+1,wDataSize) )
	{
		SetTraceString(TEXT("�յ�δ��������ݰ�,wMainCmdID:%d,wSubCmdID:%d"),pCommand->wMainCmdID,pCommand->wSubCmdID);
		return;
	}
}

void CSpeakerClientDlg::OnClose( int nErrorCode )
{
	AfxMessageBox(TEXT("����������ʧ�ܣ����ܷ������ѹرջ򱾻�����Ͽ�"));
}

void CSpeakerClientDlg::OnCancel()
{
	//�ر��׽���
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
	//��������
	CMD_CS_CHATMSG _UserChat_Msg;
	ZeroMemory(&_UserChat_Msg,sizeof _UserChat_Msg);

	GetDlgItemText(IDC_EDITCHAT,_UserChat_Msg.szDescribe,CountArray(_UserChat_Msg.szDescribe));

	//Ч������
	if ( _UserChat_Msg.szDescribe[0] == TEXT('\0') )
	{
		SetTraceString(TEXT("��������Ϊ�գ�������������˵�Ļ�"));
		return;
	}

	//��������
	m_TCPScoketClient.SendData(MDM_GP_USER,SUB_CS_USERT_CHAT,&_UserChat_Msg,sizeof _UserChat_Msg);
}

bool CSpeakerClientDlg::OnEventTCPSocketRead( WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize )
{
	switch ( wMainCmdID )
	{
	case MDM_GP_LOGON:		//��½��Ϣ
		{
			if ( wSubCmdID == SUB_SC_USERCOME)		//�û�����
			{
				CMD_SC_USERCOME *pUserCome = (CMD_SC_USERCOME*)pData;	
				
				//��������
				if( m_ListUser.FindString(-1,pUserCome->szUserName) == LB_ERR )
				{
					//�����Լ���Ϣ
					if ( m_UserData.dwUserID == 0 )
					{
						_sntprintf_s(m_UserData.szUserName,CountArray(m_UserData.szUserName),pUserCome->szUserName);
						m_UserData.dwUserID = m_UserData.dwUserID;

						SetWindowText(m_UserData.szUserName);
					}

					//����û��б�
					m_ListUser.AddString(pUserCome->szUserName);
					m_ListUser.SetItemData(m_ListUser.GetCount()-1,pUserCome->dwUserID);
				}
				
				return true;
			}
			break;
		}
	case MDM_GP_USER:			//�û���Ϣ
		{
			if ( wSubCmdID == SUB_CS_USERT_CHAT )			//������Ϣ
			{
				CMD_SC_CHATMSG *pCHATMSG = (CMD_SC_CHATMSG*)pData;	

				//������������
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
			else if ( wSubCmdID == SUB_SC_DELETE )			//�û��˳���Ϣ
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

//��½��Ϣ
LRESULT CSpeakerClientDlg::OnLogonMessage( WPARAM wParam,LPARAM lParam )
{
	tagLogonInfo *pLogonInfo = (tagLogonInfo*)wParam;

	//�ر�֮ǰsocket
	m_TCPScoketClient.Close();

	//��ʼ���׽���
	if ( !m_TCPScoketClient.Create() )
	{
		SetTraceString(TEXT("�׽��ִ���ʧ��"));
		SafeDelete(pLogonInfo);
		return FALSE;
	}

	//��������
	if( m_TCPScoketClient.Connect(pLogonInfo->szServerAddr,pLogonInfo->nPort) == FALSE )
	{
		int nErrorCode = m_TCPScoketClient.GetLastError();

		if ( nErrorCode !=WSAEWOULDBLOCK )
		{
			SetTraceString(TEXT("���ӷ�����ʧ��,�����룺%d"),nErrorCode);
			SafeDelete(pLogonInfo);
			return FALSE;
		}
	}

	//���ýӿ�
	m_TCPScoketClient.SetTCPSocketService(this);

	//��������
	CMD_CS_LOGON UserLogon;
	ZeroMemory(&UserLogon,sizeof UserLogon);

	_sntprintf_s(UserLogon.szUserName,CountArray(UserLogon.szUserName),pLogonInfo->szUserName);
	_sntprintf_s(UserLogon.szPassWord,CountArray(UserLogon.szPassWord),pLogonInfo->szPassWord);

	//���͵�½����
	m_TCPScoketClient.SendData(MDM_GP_LOGON,SUB_CS_LOGON,&UserLogon,sizeof UserLogon);

	//���ý���
	SetTraceString(TEXT("���ӷ������ɹ�"));
	m_LogonDlg.PostMessage(WM_CLOSE);

	//��������
	SafeDelete(pLogonInfo);

	return TRUE;
}

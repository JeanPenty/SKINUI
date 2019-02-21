#ifndef MESSAGE_HEAD_FILE
#define MESSAGE_HEAD_FILE

#pragma once

#define SOCKET_TCP_BUFFER			16384								//���绺��

//��������
struct TCP_Command
{
	WORD							wMainCmdID;							//��������
	WORD							wSubCmdID;							//��������
	WORD							wPacketSize;						//���ݴ�С
};

//�û���Ϣ
struct tagUserData
{
	TCHAR		szUserName[33];
	TCHAR		szPassWord[33];

	DWORD		dwUserID;
	//...����Ϸ���û����룬���飬��ң���Ա�ȵ���Ϣ
};

//////////////////////////////////////////////////////////////////////////
//��¼������
#define MDM_GP_LOGON					1								//��¼

#define SUB_CS_LOGON					1								//�ʺŵ�¼Client->Server
#define SUB_SC_USERCOME					2								//�û���½Server->Client
//////////////////////////////////////////////////////////////////////////
struct CMD_CS_LOGON									
{
	TCHAR		szUserName[33];											//�û��ǳ�
	TCHAR		szPassWord[33];											//�û�����
};

struct CMD_SC_USERCOME
{
	DWORD		dwUserID;												//�û���ʶ
	TCHAR		szUserName[33];											//�û��ǳ�
};

//////////////////////////////////////////////////////////////////////////
//����������
#define MDM_GP_USER						2								//�û���Ϣ

#define SUB_CS_USERT_CHAT				1								//������ϢClient->Server
#define SUB_SC_USERT_CHAT				2								//������ϢServer->Client
#define SUB_SC_DELETE					3								//ɾ���û�Server->Client


struct CMD_CS_CHATMSG 
{
	TCHAR				szDescribe[1024];								//��������
};

struct CMD_SC_CHATMSG
{
	TCHAR				szSendUserName[33];								//�û��ǳ�
	TCHAR				szDescribe[1024];								//��������
	SYSTEMTIME			SystemTime;										//ϵͳʱ��
};

struct CMD_DC_DELETE
{
	TCHAR		szUserName[33];											//�û��ǳ�
};
//////////////////////////////////////////////////////////////////////////

#endif
#ifndef MESSAGE_HEAD_FILE
#define MESSAGE_HEAD_FILE

#pragma once

#define SOCKET_TCP_BUFFER			16384								//网络缓冲

//网络命令
struct TCP_Command
{
	WORD							wMainCmdID;							//主命令码
	WORD							wSubCmdID;							//子命令码
	WORD							wPacketSize;						//数据大小
};

//用户信息
struct tagUserData
{
	TCHAR		szUserName[33];
	TCHAR		szPassWord[33];

	DWORD		dwUserID;
	//...如游戏中用户密码，经验，金币，会员等等信息
};

//////////////////////////////////////////////////////////////////////////
//登录命令码
#define MDM_GP_LOGON					1								//登录

#define SUB_CS_LOGON					1								//帐号登录Client->Server
#define SUB_SC_USERCOME					2								//用户登陆Server->Client
//////////////////////////////////////////////////////////////////////////
struct CMD_CS_LOGON									
{
	TCHAR		szUserName[33];											//用户昵称
	TCHAR		szPassWord[33];											//用户密码
};

struct CMD_SC_USERCOME
{
	DWORD		dwUserID;												//用户标识
	TCHAR		szUserName[33];											//用户昵称
};

//////////////////////////////////////////////////////////////////////////
//聊天命令码
#define MDM_GP_USER						2								//用户消息

#define SUB_CS_USERT_CHAT				1								//聊天消息Client->Server
#define SUB_SC_USERT_CHAT				2								//聊天消息Server->Client
#define SUB_SC_DELETE					3								//删除用户Server->Client


struct CMD_CS_CHATMSG 
{
	TCHAR				szDescribe[1024];								//聊天内容
};

struct CMD_SC_CHATMSG
{
	TCHAR				szSendUserName[33];								//用户昵称
	TCHAR				szDescribe[1024];								//聊天内容
	SYSTEMTIME			SystemTime;										//系统时间
};

struct CMD_DC_DELETE
{
	TCHAR		szUserName[33];											//用户昵称
};
//////////////////////////////////////////////////////////////////////////

#endif
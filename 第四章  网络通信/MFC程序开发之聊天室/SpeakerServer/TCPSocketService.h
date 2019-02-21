#pragma once

 //CTCPSocketService 命令目标

interface ITCPSocketService
{
	//接收事件
	virtual void OnReceive(SOCKET hSocket)=NULL;
	//监听事件
	virtual void OnAccept()=NULL;
	//关闭事件
	virtual void OnClose(SOCKET hSocket)=NULL;
};

//////////////////////////////////////////////////////////////////////////

class CTCPSocketService : public CAsyncSocket
{
protected:
	ITCPSocketService			* m_pTCPSocketService;			//网络接口

public:
	DWORD						m_dwClientAddr;					//客户端IP

public:
	CTCPSocketService();
	virtual ~CTCPSocketService();

	//
	void SetTCPSocketService( ITCPSocketService*pTCPSocketService );

	//继承函数
public:
	//
	virtual void OnReceive(int nErrorCode);
	//
	virtual void OnAccept(int nErrorCode);
	//
	virtual void OnClose(int nErrorCode);

 	//操作接口
 public:
 	//发送函数
 	virtual WORD SendData(WORD wMainCmdID, WORD wSubCmdID);
 	//发送函数
 	virtual WORD SendData(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
 
 	//辅助函数
 protected:
 	//发送数据
 	WORD SendDataBuffer(VOID * pBuffer, WORD wSendSize);
};



#pragma once

interface ITCPScoketClient
{
	//
	virtual void OnReceive(int nErrorCode)=NULL;
	//
	virtual void OnClose(int nErrorCode)=NULL;
};

// CTCPScoketClient 命令目标

class CTCPScoketClient : public CAsyncSocket
{
protected:
	ITCPScoketClient		* m_pTCPSocketClient;

public:
	CTCPScoketClient();
	virtual ~CTCPScoketClient();

	//
	void SetTCPSocketService( ITCPScoketClient*pTCPSocketClient );

	//继承函数
public:
	//
	virtual void OnReceive(int nErrorCode);
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



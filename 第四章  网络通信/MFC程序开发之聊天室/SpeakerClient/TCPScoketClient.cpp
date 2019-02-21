// TCPScoketClient.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SpeakerClient.h"
#include "TCPScoketClient.h"


// CTCPScoketClient

CTCPScoketClient::CTCPScoketClient()
{
	m_pTCPSocketClient = NULL;
}

CTCPScoketClient::~CTCPScoketClient()
{
}

void CTCPScoketClient::SetTCPSocketService( ITCPScoketClient*pTCPSocketClient )
{
	m_pTCPSocketClient = pTCPSocketClient;
}

void CTCPScoketClient::OnReceive( int nErrorCode )
{
	if( m_pTCPSocketClient == NULL ) return;

	m_pTCPSocketClient->OnReceive(nErrorCode);
}

void CTCPScoketClient::OnClose( int nErrorCode )
{
	if( m_pTCPSocketClient == NULL ) return;

	m_pTCPSocketClient->OnClose(nErrorCode);
}

WORD CTCPScoketClient::SendData( WORD wMainCmdID, WORD wSubCmdID )
{
	//Ч��״̬
	if (m_hSocket==INVALID_SOCKET) return false;

	//��������
	BYTE cbDataBuffer[SOCKET_TCP_BUFFER];

	TCP_Command * pCommand=(TCP_Command *)cbDataBuffer;
	pCommand->wMainCmdID=wMainCmdID;
	pCommand->wSubCmdID=wSubCmdID;
	pCommand->wPacketSize = sizeof TCP_Command;

	return SendDataBuffer(pCommand,sizeof TCP_Command);
}

WORD CTCPScoketClient::SendData( WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize )
{
	//Ч��״̬
	if (m_hSocket==INVALID_SOCKET) return false;
	if ( wDataSize > SOCKET_TCP_BUFFER-sizeof TCP_Command ) return false;

	//��������
	BYTE cbDataBuffer[SOCKET_TCP_BUFFER];

	TCP_Command * pCommand=(TCP_Command *)cbDataBuffer;
	pCommand->wMainCmdID=wMainCmdID;
	pCommand->wSubCmdID=wSubCmdID;
	pCommand->wPacketSize = sizeof TCP_Command+wDataSize;

	CopyMemory(pCommand+1,pData,wDataSize);

	return SendDataBuffer(pCommand,sizeof(TCP_Command)+wDataSize);
}

WORD CTCPScoketClient::SendDataBuffer( VOID * pBuffer, WORD wSendSize )
{
	//Ч�����
	ASSERT(wSendSize!=0);
	ASSERT(pBuffer!=NULL);

	//��������
	WORD wSended=0;
	while (wSended<wSendSize)
	{
		int nErrorCode=Send((char *)pBuffer+wSended,wSendSize-wSended,0);
		if (nErrorCode==SOCKET_ERROR)
		{
			if (WSAGetLastError()==WSAEWOULDBLOCK)
				return true;

			return false;
		}
		wSended+=nErrorCode;
	}

	return true;
}


// CTCPScoketClient ��Ա����

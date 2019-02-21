// TCPSocketService.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SpeakerServer.h"
#include "TCPSocketService.h"


// CTCPSocketService

CTCPSocketService::CTCPSocketService()
{
	m_pTCPSocketService = NULL;
	m_dwClientAddr = 0;
}


CTCPSocketService::~CTCPSocketService()
{
}

void CTCPSocketService::SetTCPSocketService( ITCPSocketService*pTCPSocketService )
{
	m_pTCPSocketService = pTCPSocketService;
}

void CTCPSocketService::OnReceive(int nErrorCode)
{
	if( m_pTCPSocketService == NULL ) return;
	m_pTCPSocketService->OnReceive(m_hSocket);
}

void CTCPSocketService::OnAccept( int nErrorCode )
{
	if( m_pTCPSocketService == NULL ) return;
	m_pTCPSocketService->OnAccept();
}

void CTCPSocketService::OnClose( int nErrorCode )
{
	if( m_pTCPSocketService == NULL ) return;
	m_pTCPSocketService->OnClose(m_hSocket);
}

WORD CTCPSocketService::SendData( WORD wMainCmdID, WORD wSubCmdID )
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

WORD CTCPSocketService::SendData( WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize )
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

WORD CTCPSocketService::SendDataBuffer( VOID * pBuffer, WORD wSendSize )
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


// CTCPSocketService ��Ա����

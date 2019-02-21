// TraceRichEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "TraceDebug.h"
// CTraceRichEdit


// CTraceRichEdit 消息处理程序



CTraceService::CTraceService()
{
	m_pTraceService = NULL;
	m_szLogFile[0]=0;
}

void CTraceService::SetInterFace( ITraceService *pTraceService )
{	
	assert( pTraceService != NULL );
	if ( pTraceService == NULL ) return;

	m_pTraceService = pTraceService;
}

bool CTraceService::TraceString( LPCTSTR pszString, enTraceLevel TraceLevel )
{
	if ( m_pTraceService == NULL ) return false;

	return m_pTraceService->TraceString(pszString,TraceLevel);
}

bool CTraceService::TraceString( enTraceLevel TraceLevel,LPCTSTR pszString, ... )
{
	//当没有调试窗口时，将默认采用文本的形式记录，但前提需要事先设置文件名称
	if ( m_pTraceService == NULL ) 
	{
		if(!m_szLogFile[0]) return false;

		HANDLE hOpenFile = (HANDLE)CreateFile(m_szLogFile, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
		if(hOpenFile == INVALID_HANDLE_VALUE ) return false;
		
		cCString StrTraceString;
		va_list argList;
		va_start( argList, pszString );
		StrTraceString.FormatV( pszString, argList );
		va_end( argList );

		DWORD RSize;
		int fileSize = GetFileSize(hOpenFile, NULL);
		WriteFile(hOpenFile, StrTraceString, fileSize, &RSize, NULL);

		return true;
	}
	else
	{
		cCString StrTraceString;
		va_list argList;
		va_start( argList, pszString );
		StrTraceString.FormatV( pszString, argList );
		va_end( argList );

		return m_pTraceService->TraceString(StrTraceString,TraceLevel);
	}
}

CTraceService* CTraceService::GetInstance()
{
	static CTraceService _Instance;

	return &_Instance;
}

void CTraceService::SetLogFile( LPCTSTR lpszFileName )
{
	TCHAR szWorkDirectory[MAX_PATH];
	CTextureManager::GetInstance()->GetWorkDirectory(szWorkDirectory,CountArray(szWorkDirectory));

	_sntprintf_s(m_szLogFile,CountArray(m_szLogFile),TEXT("%s\\%s"),szWorkDirectory,lpszFileName);

	HANDLE hOpenFile = (HANDLE)CreateFile(m_szLogFile, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS | TRUNCATE_EXISTING, NULL, NULL);
	if(hOpenFile == INVALID_HANDLE_VALUE ) m_szLogFile[0]=0;


// 	FILE *hf=NULL;
// 	fopen_s(&hf,cCString(m_szLogFile),"w");
// 	if(!hf) m_szLogFile[0]=0;
// 	else fclose(hf);
}
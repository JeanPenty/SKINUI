#include "StdAfx.h"
#include "HttpWeather.h"
#include "gzip/GZipHelper.h"

const TCHAR szHeaders[] = TEXT("Accept: text/*\r\nUser-Agent: LCD's Infobay Http Client\r\n");


CHttpWeather::CHttpWeather(void)
{
}

CHttpWeather::~CHttpWeather(void)
{
	m_StrError.ReleaseBuffer();
}

CString CHttpWeather::GetHttpFile( LPCTSTR lpURL )
{
	DWORD dwRetcode=-1;
	DWORD dwServiceType =0;

	CString strServerName=TEXT("");
	CString strObject=TEXT("");
	INTERNET_PORT nPort=0;
	DWORD  dwHttpRequestFlags = INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT;

	CString StrContent=TEXT("");
	CString strNewLocation=TEXT("");
	CString str_FlagTemp=TEXT("");

	CInternetSession session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;

	try
	{
		if(!OnInitSession(session))
		{
			return NULL;
		}

		if (!AfxParseURL( lpURL, dwServiceType, strServerName, strObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)
		{
			m_StrError = TEXT("非法的URL");
			return NULL;
		}

		pServer = session.GetHttpConnection(strServerName, nPort);

		if(pServer==NULL)
		{
			m_StrError = TEXT("无法与服务器建立连接");
			return NULL;
		}

		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject, NULL, 1, NULL, NULL, dwHttpRequestFlags);

		if(pFile==NULL)
		{
			m_StrError = TEXT("无法与服务器建立连接");
			return NULL;
		}

		//////////////////////////////////////////////////////////////////////////
		try
		{
			if(!pFile->AddRequestHeaders(szHeaders)|| !pFile->SendRequest())
			{
				m_StrError = TEXT("网络错误－无法发送请求报头");
				return NULL;
			}
		}
		catch (CInternetException* ex) 
		{
			StrContent.Empty();
			m_StrError = TEXT("无法发送http报头,可能网络状况有问题");
			ex->Delete();
			return NULL;		
		}
		//////////////////////////////////////////////////////////////////////////

		if(!pFile->QueryInfoStatusCode(dwRetcode))
		{
			m_StrError = TEXT("网络错误－无法查询反馈代码");
			return NULL;
		}

		if(dwRetcode>=200&&dwRetcode<300)
		{		    		
			try
			{
				//读取文件
				TCHAR szBuffer[4096];

				DWORD dwDownLoadSize=0;
				UINT uReadCount=0;

				while ( (uReadCount=pFile->Read(szBuffer,sizeof(szBuffer))) > 0 )
				{	
					StrContent.Append(szBuffer);
					
					//设置变量
					dwDownLoadSize+=uReadCount;
				}
				
				//解压gzip
				GZIP *pHttpFile = (GZIP *)StrContent.GetBuffer();
				CGZIP2A unCompress(pHttpFile,dwDownLoadSize);
				
				CA2CT unCpString(unCompress.psz);
				
				m_pszHttpFile.Format(TEXT("%s"),unCpString);

				StrContent.ReleaseBuffer();
				if (pFile != NULL) SafeDelete(pFile);
				if (pServer != NULL) SafeDelete(pServer);

				session.Close();

				return m_pszHttpFile;
			}
			catch (CInternetException* pEx)
			{
				m_StrError = TEXT("接收数据错误");
				pEx->Delete();
				return NULL;
			}

			return StrContent;
		}
		else 	
		{
			StrContent.Empty();
			OnProcessError(dwRetcode,session,pServer,pFile);

			return NULL;
		}
	}
	catch (CInternetException* pEx)
	{
		m_StrError = TEXT("网络错误");

		pEx->Delete();   
		return NULL;
	}

	return NULL;
}

BOOL CHttpWeather::OnInitSession( CInternetSession& session )
{
	//超时设置很重要！如果设置太小回引起服务器超时，如果设置太大则回引起线程挂起。
	//在重试连接之间的等待的延时值在毫秒级。
	//网络连接请求时间超时值在数毫秒级。如果连接请求时间超过这个超时值，请求将被取消。缺省的超时值是无限的。
	//在网络连接请求时的重试次数。如果一个连接企图在指定的重试次数后仍失败，则请求被取消。缺省值为5。
	try
	{
		if( !session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000)||
			!session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000)||
			!session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 3)||
			!session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT,60000)||	
			!session.EnableStatusCallback(TRUE))
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	catch(CInternetException* pEx)
	{
		pEx->GetErrorMessage(m_StrError.GetBuffer(0),1023);
		pEx->Delete();

		return FALSE;
	}
}

int CHttpWeather::OnProcessError( int dwRetcode,CInternetSession& session,CHttpConnection* pServer,CHttpFile* pFile )
{
	switch( dwRetcode )
	{
	case 100:
		m_StrError = TEXT("客户方错误-继续 [Continue]");
		break;
		//
	case 101:
		m_StrError = TEXT("客户方错误-交换协议 [witching Protocols]");
		break;
		//
	case 204:
		m_StrError = TEXT("网页内容为空 [No Content]");
		break;
		//------------------------------------------------------------
	case 400:
		m_StrError = TEXT("错误请求 [Bad Request]");
		break;
		//
	case 401:
		m_StrError = TEXT("网页需要验证信息 [Unauthorized]");
		break;
		//
	case 402:
		m_StrError = TEXT("网页需要付费 [Payment Required]");
		break;
		//
	case 403:
		m_StrError = TEXT("禁止访问 [Forbidden]");
		break;
		//
	case 404://
		m_StrError = TEXT("没有找到网页 [Not Found]");
		break;
		//
	case 405:
		m_StrError = TEXT("不允许Http访问该文件 [Method Not Allowed]");
		break;
		//
	case 406:
		m_StrError = TEXT("该文件不允许访问 [Not Acceptable]");
		break;
		//
	case 407:
		m_StrError = TEXT("该文件需要代理认证 [Proxy Authentication Required]");
		break;
		//
	case 408:
		m_StrError = TEXT("对该文件请求超时 [Request Time-out]");
		break;
		//
	case 409:
		m_StrError = TEXT("对该文件访问冲突 [Conflict]");
		break;
		//
	case 410:
		m_StrError = TEXT("对该文件访问失败 [Gone]");
		break;
		//
	case 411:
		m_StrError = TEXT("该文件需要长度信息 [Length Required]");
		break;
		//
	case 412:
		m_StrError = TEXT("请求条件失败 [Precondition Failed]");
		break;
		//
	case 413:
		m_StrError = TEXT("请求文件实体太大 [Request Entity Too Large]");
		break;
		//
	case 414:
		m_StrError = TEXT("请求的URI太长 [Request-URI Too Large]");
		break;
		//
	case 415:
		m_StrError = TEXT("不支持媒体类型 [Unsupported Media Type]");
		break;
		//
	case 416:
		m_StrError = TEXT("队列请求失败 [Requested range not satisfiable]");
		break;
		//
	case 417:
		m_StrError = TEXT("预期失败 [Expectation Failed]");
		break;
		//--------------------------------------------------------------
	case 500:
		m_StrError = TEXT("服务器内部错误 [Internal Server Error]");
		break;
		//
	case 501:
		m_StrError = TEXT("未实现请求 [Not Implemented]");
		break;
		//
	case 502:
		m_StrError = TEXT("网关失败 [Bad Gateway]");
		break;
		//
	case 503:
		m_StrError = TEXT("没有找到服务器 [Service Unavailable]");
		break;
		//
	case 504:
		m_StrError = TEXT("网关超时 [Gateway Time-out]");
		break;
		//
	case 505:
		m_StrError = TEXT("服务器不支持系统使用的HTTP版本 [HTTP Version not supported]");
		break;
		//
	}

	try
	{
		if (pFile != NULL) SafeDelete(pFile);
		if (pServer != NULL) SafeDelete(pServer);

		session.Close();

		return FALSE;
	}
	catch (CInternetException* pEx)
	{
		pEx->GetErrorMessage(m_StrError.GetBuffer(0),1024);
		pEx->Delete();

		return FALSE;
	}
}
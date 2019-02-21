#pragma once

#include <afxinet.h>

class CHttpWeather
{
protected:
	CString							m_StrError;
	CString							m_pszHttpFile;

public:
	CHttpWeather(void);
	virtual ~CHttpWeather(void);

	void ConvertUtf8ToGBK( CString& strGBK );

	BOOL OnInitSession(CInternetSession& session);

	CString GetHttpFile(LPCTSTR lpURL);

	int OnProcessError(int dwRetcode,CInternetSession& session,CHttpConnection* pServer,CHttpFile* pFile);
};

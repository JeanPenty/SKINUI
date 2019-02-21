#include "StdAfx.h"
#include "ParseJson.h"
#include <Shlwapi.h>
#include "gzip/GZipHelper.h"

CParseJson::CParseJson(void)
{
	m_CityInfoArray.clear();
}

CParseJson::~CParseJson(void)
{
 	CityInfoArray::iterator iter = m_CityInfoArray.begin();
 
 	for (;iter != m_CityInfoArray.end();++iter)
 	{
 		SafeDelete(*iter);
 	}
 
 	m_CityInfoArray.clear();
}


CParseJson* CParseJson::GetInstance()
{
	static CParseJson _Instance;

	return &_Instance;
}

void ConvertGBKToUtf8(CString &szString)
{
	DWORD dwNum=MultiByteToWideChar(CP_ACP,0,(LPCSTR)(LPCTSTR)szString,-1,NULL,0);
	wchar_t *pwText = new wchar_t[dwNum+1];
	memset(pwText,0,dwNum+1);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(LPCTSTR)szString, -1,pwText, dwNum+1);

	CT2CA CurrentServer(pwText);

	szString = CurrentServer;

	SafeDeleteArray(pwText);
}

void ConvertGBKToUtf8(LPCTSTR lpszString,TCHAR* pOutString,int nSize)
{
	DWORD dwNum=MultiByteToWideChar(CP_ACP,0,(LPCSTR)lpszString,-1,NULL,0);
	wchar_t *pwText = new wchar_t[dwNum+1];
	memset(pwText,0,dwNum+1);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)lpszString, -1,pwText, dwNum+1);

	_sntprintf_s(pOutString,-1,nSize,pwText);

	SafeDeleteArray(pwText);
}

bool CParseJson::SetCityJsonData( LPCTSTR lpszData )
{
	ASSERT(lpszData != NULL);
	if ( lpszData == NULL ) return false;

	CString str = lpszData;
	ConvertGBKToUtf8(str);

	Json::Reader reader;
	Json::Value root;

	CT2CA CityString(str);

	if( !reader.parse((const char*)CityString, root, false) ) 
		return false;

	CityInfoArray::iterator iter = m_CityInfoArray.begin();

	for (int i=0;i<root.size();i++)
	{
 		tagCityInfo *pCityInfo = new tagCityInfo;

 		Json::Value valTitleValue = root[i]["title"];
 		std::string strTitleValue = valTitleValue.asString();
		ConvertGBKToUtf8((LPCTSTR)strTitleValue.c_str(),pCityInfo->strTitle,CountArray(pCityInfo->strTitle));

 		Json::Value valCodeValue = root[i]["code"];
 		std::string strCodeValue = valCodeValue.asString();
		ConvertGBKToUtf8((LPCTSTR)strCodeValue.c_str(),pCityInfo->strCode,CountArray(pCityInfo->strCode));

 		Json::Value valJcValue = root[i]["spell"];
 		std::string strJcValue = valJcValue.asString();
		ConvertGBKToUtf8((LPCTSTR)strJcValue.c_str(),pCityInfo->strJc,CountArray(pCityInfo->strJc));

 		Json::Value valProviceValue = root[i]["province"];
 		std::string strProviceValue = valProviceValue.asString();
		ConvertGBKToUtf8((LPCTSTR)strProviceValue.c_str(),pCityInfo->strProvince,CountArray(pCityInfo->strProvince));

 		m_CityInfoArray.push_back(pCityInfo);
	}

	return true;
}

LPCTSTR CParseJson::GetCode(LPCTSTR lpTitle,LPCTSTR lpszProvince/*=NULL*/)
{
 	CityInfoArray::iterator iter = m_CityInfoArray.begin();

	for (;iter!=m_CityInfoArray.end();++iter)
	{
		tagCityInfo *pCityInfo = *iter;

		if ( StrCmp(pCityInfo->strTitle,lpTitle)==0 )
		{
			if ( lpszProvince != NULL )
			{
				if( StrCmp(pCityInfo->strTitle,lpTitle)==0 )
					return pCityInfo->strCode;
				else continue;
			}

			return pCityInfo->strCode;
		}
	}

	return NULL;
}

LPCTSTR CParseJson::GetJc(LPCTSTR lpTitle,LPCTSTR lpszProvince/*=NULL*/)
{
	CityInfoArray::iterator iter = m_CityInfoArray.begin();

	for (;iter!=m_CityInfoArray.end();++iter)
	{
		tagCityInfo *pCityInfo = *iter;

		if ( StrCmp(pCityInfo->strTitle,lpTitle)==0 )
		{
			if ( lpszProvince != NULL )
			{
				if( StrCmp(pCityInfo->strTitle,lpTitle)==0 )
					return pCityInfo->strJc;
				else continue;
			}

			return pCityInfo->strJc;
		}
	}

	return NULL;
}

bool CParseJson::SetWeatherJsonData( LPCTSTR lpszData )
{
	ASSERT(lpszData != NULL);
	if ( lpszData == NULL ) return false;

	Json::Reader reader;

	CString strData = lpszData;
	strData = strData.Right(strData.GetLength()-strData.Find(TEXT("="))-1);
	strData = strData.Left(strData.GetLength()-1);

	CT2CA CurrentServer(strData);

	if( !reader.parse((const char*)CurrentServer, m_WeatherRoot, false) ) 
		return NULL;

	return true;
}

LPCTSTR CParseJson::GetData( CString &lpKey )
{
	if( m_WeatherRoot.empty() ) return NULL;

	Json::Value valDataValue = m_WeatherRoot[CT2CA(lpKey)];
	std::string strDataValue = valDataValue.asString();

	//Ω‚—πgzip
	GZIP *pHttpFile = (GZIP *)strDataValue.data();
	CGZIP2A unCompress(pHttpFile,strDataValue.length());

	CA2CT unCpString(unCompress.psz);

	lpKey.Format(TEXT("%s"),unCpString);

	return lpKey;
}

CityInfoArray * CParseJson::GetCityArray()
{
	return &m_CityInfoArray;
}

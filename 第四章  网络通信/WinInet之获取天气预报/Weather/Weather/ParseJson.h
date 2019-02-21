#pragma once

#include <vector>
using namespace std;

struct tagCityInfo
{
 	TCHAR			strTitle[64];
 	TCHAR			strCode[64];
 	TCHAR			strJc[64];
 	TCHAR			strProvince[64];
};

typedef vector<tagCityInfo*>		CityInfoArray;

class CParseJson
{
protected:
	Json::Value				m_WeatherRoot;
	CityInfoArray			m_CityInfoArray;

public:
	CParseJson(void);
	virtual ~CParseJson(void);

	static CParseJson*GetInstance();

	//���б��
public:
	//��������
	bool SetCityJsonData(LPCTSTR lpszData);
	//��ȡ����
	LPCTSTR GetCode(LPCTSTR lpTitle,LPCTSTR lpszProvince=NULL);
	//��ȡƴ��
	LPCTSTR GetJc(LPCTSTR lpTitle,LPCTSTR lpszProvince=NULL);

	CityInfoArray *GetCityArray();

	//���б��
public:
	//��������
	bool SetWeatherJsonData(LPCTSTR lpszData);
	//��ȡ����
	LPCTSTR GetData(CString &lpKey);
};

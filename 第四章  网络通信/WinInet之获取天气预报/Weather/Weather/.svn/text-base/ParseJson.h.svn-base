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

	//城市编号
public:
	//设置数据
	bool SetCityJsonData(LPCTSTR lpszData);
	//获取代码
	LPCTSTR GetCode(LPCTSTR lpTitle,LPCTSTR lpszProvince=NULL);
	//获取拼音
	LPCTSTR GetJc(LPCTSTR lpTitle,LPCTSTR lpszProvince=NULL);

	CityInfoArray *GetCityArray();

	//城市编号
public:
	//设置数据
	bool SetWeatherJsonData(LPCTSTR lpszData);
	//获取代码
	LPCTSTR GetData(CString &lpKey);
};

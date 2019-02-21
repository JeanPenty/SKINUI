#pragma once
#include "GameEngineHead.h"

//输出等级
enum enTraceLevel
{
	TraceLevel_Info					=0,									//信息消息
	TraceLevel_Normal				=1,									//普通消息
	TraceLevel_Warning				=2,									//警告消息
	TraceLevel_Exception			=3,									//异常消息
	TraceLevel_Debug				=4,									//调试消息
};

//事件输出
interface ITraceService
{
	//字串输出
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel)=NULL;
	//字串输出
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...)=NULL;
};


// CTraceRichEdit
//////////////////////////////////////////////////////////////////////////
//追踪服务
class GAME_ENGINE_CLASS CTraceService
{
protected:
	ITraceService						* m_pTraceService;
	TCHAR								m_szLogFile[MAX_PATH];

public:
	CTraceService();

	static CTraceService*GetInstance();

public:
	//设置接口
	void SetInterFace(ITraceService *pTraceService);
	//设置文件
	void SetLogFile(LPCTSTR lpszFileName);
	//字串输出
	bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//字串输出
	bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);
};

#define TraceService	CTraceService::GetInstance()
//////////////////////////////////////////////////////////////////////////



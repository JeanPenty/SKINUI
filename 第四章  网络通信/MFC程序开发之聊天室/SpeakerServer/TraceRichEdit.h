#pragma once


//输出等级
enum enTraceLevel
{
	TraceLevel_Info					=0,									//信息消息
	TraceLevel_Normal				=1,									//普通消息
	TraceLevel_Warning				=2,									//警告消息
	TraceLevel_Exception			=3,									//异常消息
	TraceLevel_Debug				=4,									//调试消息
};

// CTraceRichEdit
//////////////////////////////////////////////////////////////////////////

class CTraceRichEdit : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CTraceRichEdit)

public:
	CTraceRichEdit();
	virtual ~CTraceRichEdit();

	//字串输出
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//字串输出
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);

	//辅助函数
private:
	//配置服务
	VOID InitializeService();
	//获取颜色
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
	//插入字串
	bool InsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);

protected:
	DECLARE_MESSAGE_MAP()
};



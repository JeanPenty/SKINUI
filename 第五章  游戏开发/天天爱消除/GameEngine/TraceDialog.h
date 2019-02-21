#pragma once


// CTraceDialog 对话框
#include "TraceDebug.h"
#include "GameEngineHead.h"

class CTraceRichEdit : public CRichEditCtrl,public ITraceService
{
	DECLARE_DYNAMIC(CTraceRichEdit)

public:
	CTraceRichEdit();
	virtual ~CTraceRichEdit();

public:
	//配置服务
	void InitService();
	//字串输出
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//字串输出
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);

	//辅助函数
private:
	//获取颜色
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
	//插入字串
	bool InsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);

protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

class CTraceDialog : public CDialog
{
	DECLARE_DYNAMIC(CTraceDialog)

protected:
	CTraceRichEdit					m_TraceEdit;

public:
	CTraceDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTraceDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


#ifndef TRACE_HEAD_FILE
#define TRACE_HEAD_FILE

#pragma once

class GAME_ENGINE_CLASS IRichEditState
{
protected:
	HINSTANCE				m_hInstRichEdit;

public:
	IRichEditState();
	~IRichEditState();

	static IRichEditState*GetInstance();
};

//如果需要使用RichEdit控件必须先调用InitRichEdit宏才可以创建成功
#define InitRichEdit	IRichEditState::GetInstance()

//////////////////////////////////////////////////////////////////////////

// CTraceDialog 对话框
#include <Richedit.h>

class CTraceRichEdit : public ITraceService, public cCWnd
{
public:
	CTraceRichEdit();
	virtual ~CTraceRichEdit();

	//窗口属性
public:
	//创建窗口
	BOOL Create( HINSTANCE hInstance,DWORD dwStyle, const RECT& rect, HWND hParentWnd, UINT nID);

	//功能函数
public:
	//配置服务
	void InitService();
	//字串输出
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//字串输出
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);

	//控件属性
public:
	//设置选择
	void SetSel(long nStartChar, long nEndChar);
	//设置格式
	BOOL SetWordCharFormat(CHARFORMAT2 &cf);
	//设置文本
	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
	//设置背景颜色
	COLORREF SetBackgroundColor(BOOL bSysColor, COLORREF cr);

	//辅助函数
private:
	//获取颜色
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
};

//////////////////////////////////////////////////////////////////////////
//调试窗口
class CTraceDialog : public cCWnd
{
protected:
	CTraceRichEdit					m_TraceEdit;				//RichEdit控件

public:
	CTraceDialog();
	virtual ~CTraceDialog();
	
	//窗口事件
public:
	//创建窗口
	BOOL Create(HINSTANCE hInstance, HWND hParentWnd);
	//窗口回调
	virtual LRESULT WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );
};

#endif
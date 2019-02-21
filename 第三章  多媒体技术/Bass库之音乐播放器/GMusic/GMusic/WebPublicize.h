#ifndef WEB_PUBLICIZE_HEAD_FILE
#define WEB_PUBLICIZE_HEAD_FILE

#pragma once

#include "WebBrowser.h"

//////////////////////////////////////////////////////////////////////////////////

//浏览状态
#define BROWSER_STATUS_LOAD			0									//加载状态
#define BROWSER_STATUS_ERROR		1									//错误状态
#define BROWSER_STATUS_FINISH		2									//完成状态

//////////////////////////////////////////////////////////////////////////////////

//广告控件
class CWebPublicize : public CWnd
{
	//状态变量
protected:
	BYTE							m_cbStatus;							//浏览状态

	//控件变量
protected:
	CWebBrowser						m_WebBrowser;						//广告窗口
	
	//函数定义
public:
	//构造函数
	CWebPublicize();
	//析构函数
	virtual ~CWebPublicize();

	//信息接口
public:
	//获取状态
	BYTE GetBrowserStatus() { return m_cbStatus; }
	//获取窗口
	CWebBrowser * GetWebBrowser() { return &m_WebBrowser; }

	//浏览函数
public:
	//浏览函数
	VOID Navigate(LPCTSTR pszURL);
	//浏览函数
	VOID Navigate(LPCTSTR pszURL, VARIANT * Flags, VARIANT * TargetFrameName, VARIANT * PostData, VARIANT * Headers);

	//重置函数
protected:
	//状态通知
	virtual VOID OnBrowserStatus(BYTE cbStatus);
	//位置函数
	virtual VOID GetWebBrowserRect(CRect&rcWebBrowser);
	//绘画界面
	virtual VOID DrawPublicizeView(CDC * pDC, INT nWidth, INT nHeight, BYTE cbStatus);

	//消息函数
public:
	//重画消息
	VOID OnPaint();
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//
	BOOL OnEraseBkgnd(CDC* pDC);

	VOID OnTimer(UINT nIDEvent);

	//消息函数
protected:
	//导航完成
	VOID OnDocumentCompleteWeb(LPDISPATCH pDisp, VARIANT FAR * URL);
	//导航错误
	VOID OnNavigateErrorWeb(LPDISPATCH pDisp, VARIANT FAR * URL, VARIANT FAR * Frame, VARIANT FAR * StatusCode, BOOL FAR * Cancel);
	//导航开始
	VOID OnBeforeNavigate2Web(LPDISPATCH pDisp, VARIANT FAR * URL, VARIANT FAR * Flags, VARIANT FAR * TargetFrameName, VARIANT FAR * PostData, VARIANT FAR * Headers, BOOL FAR * Cancel);

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif
#include "StdAfx.h"
#include "WebPublicize.h"
#include <ExDispid.h>

//#import <mshtml.tlb>
#include <MsHTML.h>
//////////////////////////////////////////////////////////////////////////////////

//进度定义
#define MAX_LOAD_INDEX				20									//最大索引
#define IDI_LOAD_TIMER				100									//加载时间

//常量定义
#define IDC_WEB_BROWSER				100									//窗口标识

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWebPublicize, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CWebPublicize, CWnd)
	ON_EVENT(CWebPublicize, IDC_WEB_BROWSER, DISPID_DOCUMENTCOMPLETE, OnDocumentCompleteWeb, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CWebPublicize, IDC_WEB_BROWSER, DISPID_NAVIGATEERROR, OnNavigateErrorWeb, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	ON_EVENT(CWebPublicize, IDC_WEB_BROWSER, DISPID_BEFORENAVIGATE2, OnBeforeNavigate2Web, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CWebPublicize::CWebPublicize()
{
	//设置变量
	m_cbStatus=BROWSER_STATUS_LOAD;

	return;
}

//析构函数
CWebPublicize::~CWebPublicize()
{
}

//浏览函数
VOID CWebPublicize::Navigate(LPCTSTR pszURL)
{
	//创建窗口
	if (m_WebBrowser.m_hWnd==NULL)
	{
		CRect rcCreate(0,0,0,0);
		m_WebBrowser.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_WEB_BROWSER);
		//m_WebBrowser.put_Silent(TRUE);
	}

	//浏览页面
	m_WebBrowser.Navigate(pszURL,NULL,NULL,NULL,NULL);

	return;
}

//浏览函数
VOID CWebPublicize::Navigate(LPCTSTR pszURL, VARIANT * Flags, VARIANT * TargetFrameName, VARIANT * PostData, VARIANT * Headers)
{
	//创建窗口
	if (m_WebBrowser.m_hWnd==NULL)
	{
		CRect rcCreate(0,0,0,0);
		m_WebBrowser.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_WEB_BROWSER);
	}

	//浏览页面
	m_WebBrowser.Navigate(pszURL,NULL,NULL,NULL,NULL);

	return;
}

//状态通知
VOID CWebPublicize::OnBrowserStatus(BYTE cbStatus)
{
	switch (cbStatus)
	{
	case BROWSER_STATUS_LOAD:		//加载状态
		{
			SetTimer(IDI_LOAD_TIMER,50,NULL);
			return;
		}
	case BROWSER_STATUS_FINISH:		//完成状态
		{
			KillTimer(IDI_LOAD_TIMER);
			return;
		}
	}

	return;
}

//位置函数
VOID CWebPublicize::GetWebBrowserRect(CRect&rcWebBrowser)
{
	//获取位置
	GetClientRect(&rcWebBrowser);

	return;
}

//绘画界面
VOID CWebPublicize::DrawPublicizeView(CDC * pDC, INT nWidth, INT nHeight, BYTE cbStatus)
{
	//绘画背景
	pDC->FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));

	//绘画界面
	INT nYDrawPos=nHeight/2;
	INT nXDrawPos=nWidth/2;

	//创建字体
	CFont Font;
	Font.CreateFont(-12,0,0,0,800,0,0,0,134,3,2,ANTIALIASED_QUALITY,2,TEXT("宋体"));

	//设置设备
	pDC->SelectObject(Font);
	pDC->SetTextColor(RGB(30,30,30));

	//输出字体
	LPCTSTR pszString=TEXT("正在加载页面，请稍后...");
	pDC->TextOut(nXDrawPos,nYDrawPos+20,pszString,lstrlen(pszString));

	return;
}

//重画消息
VOID CWebPublicize::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//绘画缓冲
	CDC * pBufferDC=CDC::FromHandle(ImageBuffer.GetDC());
	DrawPublicizeView(pBufferDC,rcClient.Width(),rcClient.Height(),m_cbStatus);

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	//释放资源
	ImageBuffer.ReleaseDC();

	return;
}

//位置消息
VOID CWebPublicize::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//移动窗口
	if (m_WebBrowser.m_hWnd!=NULL)
	{
		if (m_cbStatus==BROWSER_STATUS_FINISH)
		{
			//获取位置
			CRect rcWebBrowser;
			GetWebBrowserRect(rcWebBrowser);

			//移动位置
			m_WebBrowser.SetWindowPos(NULL,rcWebBrowser.left,rcWebBrowser.top,rcWebBrowser.Width(),rcWebBrowser.Height(),SWP_NOZORDER);
		}
		else
		{
			//移动位置
			m_WebBrowser.SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER);
		}
	}

	return;
}

//导航完成
VOID CWebPublicize::OnDocumentCompleteWeb(LPDISPATCH pDisp, VARIANT FAR * URL)
{
	//设置变量
	if (m_cbStatus!=BROWSER_STATUS_ERROR)
	{
		//设置变量
		m_cbStatus=BROWSER_STATUS_FINISH;

		//状态通知
		OnBrowserStatus(BROWSER_STATUS_FINISH);

 		//移动窗口
 		if (m_WebBrowser.m_hWnd!=NULL)
 		{
 			//获取位置
 			CRect rcWebBrowser;
 			GetWebBrowserRect(rcWebBrowser);
 
 			//移动位置
 			m_WebBrowser.SetWindowPos(NULL,rcWebBrowser.left,rcWebBrowser.top,rcWebBrowser.Width(),rcWebBrowser.Height(),SWP_NOZORDER);
 		}
	}

	return;
}

//导航错误
VOID CWebPublicize::OnNavigateErrorWeb(LPDISPATCH pDisp, VARIANT FAR * URL, VARIANT FAR * Frame, VARIANT FAR * StatusCode, BOOL FAR * Cancel)
{
	//设置变量
	m_cbStatus=BROWSER_STATUS_ERROR;

	//状态通知
	OnBrowserStatus(BROWSER_STATUS_ERROR);

	//移动窗口
	if (m_WebBrowser.m_hWnd!=NULL) m_WebBrowser.SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER);

	return;
}

//导航开始
VOID CWebPublicize::OnBeforeNavigate2Web(LPDISPATCH pDisp, VARIANT FAR * URL, VARIANT FAR * Flags, VARIANT FAR * TargetFrameName, VARIANT FAR * PostData, VARIANT FAR * Headers, BOOL FAR * Cancel)
{
	//设置变量
	m_cbStatus=BROWSER_STATUS_LOAD;

	//状态通知
	OnBrowserStatus(BROWSER_STATUS_LOAD);

	//移动窗口
	if (m_WebBrowser.m_hWnd!=NULL) m_WebBrowser.SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER);

	return;
// 	IHTMLDocument2 *Doc2 = (IHTMLDocument2*)m_WebBrowser.get_Document();
// 
// 	IHTMLWindow2 *pWindow = NULL;
// 	if( Doc2 != NULL && Doc2->get_parentWindow(&pWindow)!=NULL)
// 	{
// 		VARIANT v;
// 		//string order="alert('Hello World!')";
// 		pWindow->execScript(TEXT("PlaySongs"),TEXT("JavaScript"),&v);
// 		pWindow->Release();
// 	}

 	//IHTMLDocument2 *doc = (IHTMLDocument2 *)m_WebBrowser.get_Document();
 	//IHTMLWindow2 *pWindow = NULL;
 	////WideString script,language;
 	////language="JavaScript";
 	//VARIANT v;

 	//doc->get_parentWindow(&pWindow);
 	////script="alert('hello');";
 	//pWindow->execScript(TEXT("PlaySongs"),TEXT("JavaScript"),&v);
 	//pWindow->Release();

	//CComPtr<IWebBrowser2> pWB2;
	//HRESULT hr = m_WebBrowser.QueryControl( &pWB2 );

	//if(pWB2) 
	//{
	//	CComPtr <IDispatch> pdispDoc; 
	//	pWB2->get_Document(&pdispDoc);

	//	if(!pdispDoc)
	//		return FALSE;

	//	CComQIPtr <IHTMLDocument2> piDoc(pdispDoc);

	//	if(!piDoc) 
	//		return FALSE;

	//	CComPtr<IHTMLWindow2> piWindow;
	//	hr = piDoc->get_parentWindow(&piWindow);
	//	if(FAILED(hr) && !piWindow)
	//		return FALSE;

	//	VARIANT  ret;  
	//	ret.vt    =  VT_EMPTY;  
	//	ATL::CString strCode = strFunction;
	//	if(!strParam.IsEmpty())
	//		strCode += L"(" + strParam + L")";
	//	else
	//		strCode += L"()";
	//	hr  =  piWindow->execScript(CComBSTR(strCode),  L"javascript",&ret); //2个参数

	//	if(FAILED(hr))
	//		return FALSE;

	//}

//	return;
 
 	//MSHTML::IHTMLDocument2Ptr spDoc(m_WebBrowser.get_Document());
	IHTMLDocument2 *spDoc = (IHTMLDocument2 *)m_WebBrowser.get_Document();

 	if (spDoc)
 	{
		IHTMLElementCollection *p;
 		IDispatchPtr spDisp(spDoc->get_scripts(&p));
 		if (spDisp)
 		{
 			// Evaluate is the name of the script function.
 			OLECHAR FAR* szMember = TEXT("PlaySongs");
 			DISPID dispid;
 
 			HRESULT hr = spDisp->GetIDsOfNames(IID_NULL, &szMember, 1,LOCALE_SYSTEM_DEFAULT, &dispid);
 
 			if (SUCCEEDED(hr))
 			{
 				COleVariant vtResult;
 				static BYTE parms[] = VTS_BSTR;
 
 				COleDispatchDriver dispDriver(spDisp, FALSE);
 
 				dispDriver.InvokeHelper(dispid, DISPATCH_METHOD, VT_VARIANT,(void*)&vtResult, parms,"510");
 			}
 		}
 	}

	return;
}

BOOL CWebPublicize::OnEraseBkgnd( CDC* pDC )
{
	return TRUE;
}

//时间消息
VOID CWebPublicize::OnTimer(UINT nIDEvent)
{
	__super::OnTimer(nIDEvent);

	//时间处理
	if (nIDEvent==IDI_LOAD_TIMER)
	{
		//设置变量
		//m_wIndex=((m_wIndex+1)>=MAX_LOAD_INDEX)?0:(m_wIndex+1);

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

		return;
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

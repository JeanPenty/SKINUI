#ifndef WEB_BROWSER_HEAD_FILE
#define WEB_BROWSER_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////////////

//浏览窗口
class CWebBrowser : public CWnd
{
	//功能函数
public:
	CLSID const&GetClsid()
	{
		static CLSID const clsid={0x8856F961,0x340A,0x11D0,{0xA9,0x6B,0x0,0xC0,0x4F,0xD7,0x5,0xA2}};
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd * pParentWnd, UINT nID, 
		CCreateContext * pContext=NULL)
	{
		return CreateControl(GetClsid(),lpszWindowName,dwStyle,rect,pParentWnd,nID);
	}
	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd * pParentWnd, 
		UINT nID, CFile * pPersist=NULL, BOOL bStorage=FALSE, BSTR bstrLicKey=NULL)
	{ 
		return CreateControl(GetClsid(),lpszWindowName,dwStyle,rect,pParentWnd,nID,pPersist,bStorage,bstrLicKey);
	}

	//功能函数
public:
	VOID GoBack()
	{
		InvokeHelper(0x64,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	}
	VOID GoForward()
	{
		InvokeHelper(0x65,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	}
	VOID GoHome()
	{
		InvokeHelper(0x66,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	}
	VOID GoSearch()
	{
		InvokeHelper(0x67,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	}
	VOID Navigate(LPCTSTR URL, VARIANT * Flags, VARIANT * TargetFrameName, VARIANT * PostData, VARIANT * Headers)
	{
		static BYTE parms[]=VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
		InvokeHelper(0x68,DISPATCH_METHOD,VT_EMPTY,NULL,parms,URL,Flags,TargetFrameName,PostData,Headers);
	}
	VOID Refresh()
	{
		InvokeHelper(DISPID_REFRESH,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	}
	VOID Refresh2(VARIANT * Level)
	{
		static BYTE parms[]=VTS_PVARIANT;
		InvokeHelper(0x69,DISPATCH_METHOD,VT_EMPTY,NULL,parms,Level);
	}
	VOID Stop()
	{
		InvokeHelper(0x6a,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	}
	LPDISPATCH get_Application()
	{
		LPDISPATCH Result;
		InvokeHelper(0xc8,DISPATCH_PROPERTYGET,VT_DISPATCH,(VOID *)&Result,NULL);
		return Result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH Result;
		InvokeHelper(0xc9,DISPATCH_PROPERTYGET,VT_DISPATCH,(VOID *)&Result,NULL);
		return Result;
	}
	LPDISPATCH get_Container()
	{
		LPDISPATCH Result;
		InvokeHelper(0xca,DISPATCH_PROPERTYGET,VT_DISPATCH,(VOID *)&Result,NULL);
		return Result;
	}
	LPDISPATCH get_Document()
	{
		LPDISPATCH Result;
		InvokeHelper(0xcb,DISPATCH_PROPERTYGET,VT_DISPATCH,(VOID *)&Result,NULL);
		return Result;
	}
	BOOL get_TopLevelContainer()
	{
		BOOL Result;
		InvokeHelper(0xcc,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	CString get_Type()
	{
		CString Result;
		InvokeHelper(0xcd,DISPATCH_PROPERTYGET,VT_BSTR,(VOID *)&Result,NULL);
		return Result;
	}
	LONG get_Left()
	{
		LONG Result;
		InvokeHelper(0xce,DISPATCH_PROPERTYGET,VT_I4,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Left(LONG newValue)
	{
		static BYTE parms[]=VTS_I4;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	LONG get_Top()
	{
		LONG Result;
		InvokeHelper(0xcf,DISPATCH_PROPERTYGET,VT_I4,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Top(LONG newValue)
	{
		static BYTE parms[]=VTS_I4;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	LONG get_Width()
	{
		LONG Result;
		InvokeHelper(0xd0,DISPATCH_PROPERTYGET,VT_I4,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Width(LONG newValue)
	{
		static BYTE parms[]=VTS_I4;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	LONG get_Height()
	{
		LONG Result;
		InvokeHelper(0xd1,DISPATCH_PROPERTYGET,VT_I4,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Height(LONG newValue)
	{
		static BYTE parms[]=VTS_I4;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	CString get_LocationName()
	{
		CString Result;
		InvokeHelper(0xd2,DISPATCH_PROPERTYGET,VT_BSTR,(VOID *)&Result,NULL);
		return Result;
	}
	CString get_LocationURL()
	{
		CString Result;
		InvokeHelper(0xd3,DISPATCH_PROPERTYGET,VT_BSTR,(VOID *)&Result,NULL);
		return Result;
	}
	BOOL get_Busy()
	{
		BOOL Result;
		InvokeHelper(0xd4,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID Quit()
	{
		InvokeHelper(0x12c,DISPATCH_METHOD,VT_EMPTY,NULL,NULL);
	}
	VOID ClientToWindow(LONG * pcx, LONG * pcy)
	{
		static BYTE parms[]=VTS_PI4 VTS_PI4;
		InvokeHelper(0x12d,DISPATCH_METHOD,VT_EMPTY,NULL,parms,pcx,pcy);
	}
	VOID PutProperty(LPCTSTR Property, VARIANT vtValue)
	{
		static BYTE parms[]=VTS_BSTR VTS_VARIANT;
		InvokeHelper(0x12e,DISPATCH_METHOD,VT_EMPTY,NULL,parms,Property,&vtValue);
	}
	VARIANT GetProperty(LPCTSTR Property)
	{
		VARIANT Result;
		static BYTE parms[]=VTS_BSTR;
		InvokeHelper(0x12f,DISPATCH_METHOD,VT_VARIANT,(VOID *)&Result,parms,Property);
		return Result;
	}
	CString get_Name()
	{
		CString Result;
		InvokeHelper(0x0,DISPATCH_PROPERTYGET,VT_BSTR,(VOID *)&Result,NULL);
		return Result;
	}
	LONG get_HWND()
	{
		LONG Result;
		InvokeHelper(DISPID_HWND,DISPATCH_PROPERTYGET,VT_I4,(VOID *)&Result,NULL);
		return Result;
	}
	CString get_FullName()
	{
		CString Result;
		InvokeHelper(0x190,DISPATCH_PROPERTYGET,VT_BSTR,(VOID *)&Result,NULL);
		return Result;
	}
	CString get_Path()
	{
		CString Result;
		InvokeHelper(0x191,DISPATCH_PROPERTYGET,VT_BSTR,(VOID *)&Result,NULL);
		return Result;
	}
	BOOL get_Visible()
	{
		BOOL Result;
		InvokeHelper(0x192,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Visible(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x192, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_StatusBar()
	{
		BOOL Result;
		InvokeHelper(0x193,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_StatusBar(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x193, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	CString get_StatusText()
	{
		CString Result;
		InvokeHelper(0x194,DISPATCH_PROPERTYGET,VT_BSTR,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_StatusText(LPCTSTR newValue)
	{
		static BYTE parms[]=VTS_BSTR;
		InvokeHelper(0x194, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	LONG get_ToolBar()
	{
		LONG Result;
		InvokeHelper(0x195,DISPATCH_PROPERTYGET,VT_I4,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_ToolBar(LONG newValue)
	{
		static BYTE parms[]=VTS_I4;
		InvokeHelper(0x195, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_MenuBar()
	{
		BOOL Result;
		InvokeHelper(0x196,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_MenuBar(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x196, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_FullScreen()
	{
		BOOL Result;
		InvokeHelper(0x197,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_FullScreen(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x197, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	VOID Navigate2(VARIANT * URL, VARIANT * Flags, VARIANT * TargetFrameName, VARIANT * PostData, VARIANT * Headers)
	{
		static BYTE parms[]=VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
		InvokeHelper(0x1f4,DISPATCH_METHOD,VT_EMPTY,NULL,parms,URL,Flags,TargetFrameName,PostData,Headers);
	}
	LONG QueryStatusWB(LONG cmdID)
	{
		LONG Result;
		static BYTE parms[]=VTS_I4;
		InvokeHelper(0x1f5,DISPATCH_METHOD,VT_I4,(VOID *)&Result,parms,cmdID);
		return Result;
	}
	VOID ExecWB(LONG cmdID, LONG cmdexecopt, VARIANT * pvaIn, VARIANT * pvaOut)
	{
		static BYTE parms[]=VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
		InvokeHelper(0x1f6,DISPATCH_METHOD,VT_EMPTY,NULL,parms,cmdID,cmdexecopt,pvaIn,pvaOut);
	}
	VOID ShowBrowserBar(VARIANT * pvaClsid, VARIANT * pvarShow, VARIANT * pvarSize)
	{
		static BYTE parms[]=VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
		InvokeHelper(0x1f7,DISPATCH_METHOD,VT_EMPTY,NULL,parms,pvaClsid,pvarShow,pvarSize);
	}
	LONG get_ReadyState()
	{
		LONG Result;
		InvokeHelper(DISPID_READYSTATE,DISPATCH_PROPERTYGET,VT_I4,(VOID *)&Result,NULL);
		return Result;
	}
	BOOL get_Offline()
	{
		BOOL Result;
		InvokeHelper(0x226,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Offline(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x226, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_Silent()
	{
		BOOL Result;
		InvokeHelper(0x227,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Silent(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x227, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_RegisterAsBrowser()
	{
		BOOL Result;
		InvokeHelper(0x228,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_RegisterAsBrowser(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x228, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_RegisterAsDropTarget()
	{
		BOOL Result;
		InvokeHelper(0x229,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_RegisterAsDropTarget(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x229, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_TheaterMode()
	{
		BOOL Result;
		InvokeHelper(0x22a,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_TheaterMode(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x22a, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_AddressBar()
	{
		BOOL Result;
		InvokeHelper(0x22b,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_AddressBar(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x22b, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
	BOOL get_Resizable()
	{
		BOOL Result;
		InvokeHelper(0x22c,DISPATCH_PROPERTYGET,VT_BOOL,(VOID *)&Result,NULL);
		return Result;
	}
	VOID put_Resizable(BOOL newValue)
	{
		static BYTE parms[]=VTS_BOOL;
		InvokeHelper(0x22c, DISPATCH_PROPERTYPUT,VT_EMPTY,NULL,parms,newValue);
	}
};

//////////////////////////////////////////////////////////////////////////////////

#endif
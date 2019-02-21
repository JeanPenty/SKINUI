// TraceDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TraceDialog.h"
#include "resource.h"

// CTraceDialog 对话框
LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

//////////////////////////////////////////////////////////////////////////
IRichEditState::IRichEditState()
{
	m_hInstRichEdit = LoadLibrary(TEXT("RICHED20.DLL"));
}

IRichEditState::~IRichEditState()
{
	::FreeLibrary(m_hInstRichEdit);
	m_hInstRichEdit = NULL;
}

IRichEditState* IRichEditState::GetInstance()
{
	static IRichEditState _Instance;

	return &_Instance;
}

//////////////////////////////////////////////////////////////////////////
CTraceRichEdit::CTraceRichEdit()
{
	m_hWnd = NULL;
}

CTraceRichEdit::~CTraceRichEdit()
{
}

bool CTraceRichEdit::TraceString( LPCTSTR pszString, enTraceLevel TraceLevel )
{
	if ( m_hWnd == NULL ) return false;
	
	//设置格式
	CHARFORMAT2 CharFormat;
	memset(&CharFormat,0,sizeof(CharFormat));
	CharFormat.cbSize=sizeof(CharFormat); 
	CharFormat.dwMask=CFM_COLOR|CFM_FACE|CFM_SIZE;
	CharFormat.yHeight=180;
	lstrcpyn(CharFormat.szFaceName,TEXT("宋体"),sizeof(CharFormat.szFaceName));

	//获取时间
	SYSTEMTIME SystemTime;
	TCHAR szTimeBuffer[512] = {0};
	GetLocalTime(&SystemTime);
	_sntprintf_s(szTimeBuffer, sizeof(szTimeBuffer), TEXT("[%02d:%02d:%02d] "), SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
	_sntprintf_s(szTimeBuffer, sizeof(szTimeBuffer), TEXT("%s%s\n"), szTimeBuffer, pszString);
	CharFormat.crTextColor = GetTraceColor(TraceLevel);

	SetSel(-1L, -1L);
	SetWordCharFormat(CharFormat);
	ReplaceSel(szTimeBuffer);

	return true;
}

bool CTraceRichEdit::TraceString(enTraceLevel TraceLevel, LPCTSTR pszString, ... )
{
	cCString StrTraceString;

	va_list argList;
	va_start( argList, pszString );
	StrTraceString.FormatV( pszString, argList );
	va_end( argList );

	return TraceString(StrTraceString,TraceLevel);
}

COLORREF CTraceRichEdit::GetTraceColor( enTraceLevel TraceLevel )
{
	switch (TraceLevel)
	{
	case TraceLevel_Info:
		return RGB(133, 124, 129);
		break;
	case TraceLevel_Normal:
		return RGB(205, 215, 225);
		break;
	case TraceLevel_Warning:
		return RGB(255, 0, 0);
		break;
	case TraceLevel_Exception:
		return RGB(255, 0, 0);
		break;
	case TraceLevel_Debug:
		return RGB(19, 127, 140);
		break;
	}

	return RGB(0, 0, 0);
}


void CTraceRichEdit::InitService()
{
	TraceService->SetInterFace(this);
}

BOOL CTraceRichEdit::Create( HINSTANCE hInstance,DWORD dwStyle, const RECT& rect, HWND hParentWnd, UINT nID )
{
 	assert(hParentWnd != NULL);
 	assert((dwStyle & WS_POPUP) == 0);
 
 	m_hWnd = CreateWindowEx(0,RICHEDIT_CLASS,NULL, dwStyle, rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,hParentWnd,(HMENU)nID,hInstance,NULL );
 
 	return m_hWnd?TRUE:FALSE;
}

void CTraceRichEdit::SetSel( long nStartChar, long nEndChar )
{ 	 
 	CHARRANGE cr;
 	cr.cpMin = nStartChar;
 	cr.cpMax = nEndChar;
 	::SendMessage(m_hWnd, EM_EXSETSEL, 0, (LPARAM)&cr);
}

BOOL CTraceRichEdit::SetWordCharFormat(CHARFORMAT2 &cf)
{
	cf.cbSize = sizeof(CHARFORMAT2);
	return (BOOL)::SendMessage(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD, (LPARAM)&cf);
}

void CTraceRichEdit::ReplaceSel( LPCTSTR lpszNewText, BOOL bCanUndo /*= FALSE*/ )
{
	::SendMessage(m_hWnd, EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText);
}

COLORREF CTraceRichEdit::SetBackgroundColor( BOOL bSysColor, COLORREF cr )
{
	assert(::IsWindow(m_hWnd)); 
	return (COLORREF)::SendMessage(m_hWnd, EM_SETBKGNDCOLOR, bSysColor, cr);
}
//////////////////////////////////////////////////////////////////////////

CTraceDialog::CTraceDialog()
{
}

CTraceDialog::~CTraceDialog()
{
}

BOOL CTraceDialog::Create( HINSTANCE hInstance, HWND hParentWnd )
{
	return cCWnd::CreateEx(hInstance,0,TEXT("ChildWindow"),TEXT("run-time Debug"),WS_POPUP|WS_VISIBLE|WS_OVERLAPPEDWINDOW,0, 0, 480, 360,hParentWnd,0);
}

LRESULT CTraceDialog::WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	switch ( uMessage )
	{
	case WM_CREATE:
		{
			if ( m_TraceEdit.Create(m_hInstance,																				 \
				WS_CHILD | WS_VISIBLE | ES_READONLY | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_NOHIDESEL,\
				cCRect(0,0,0,0),hWnd,IDC_RICHDEBUG) )
			{
				m_TraceEdit.SetBackgroundColor(FALSE,RGB(0,0,0));
				m_TraceEdit.InitService();
			}
			
			return 0;
		}

	case WM_SIZE:
		{
			int cx = LOWORD(lParam);
			int cy = HIWORD(lParam);

			//移动准备
			HDWP hDwp=BeginDeferWindowPos(64);
			UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

			DeferWindowPos(hDwp,m_TraceEdit.m_hWnd,NULL,0,0,cx,cy,uFlags|SWP_NOMOVE);

			//结束调整
			::LockWindowUpdate(hWnd);
			EndDeferWindowPos(hDwp);
			::LockWindowUpdate(NULL);

			return 0;
		}
	}

	return cCWnd::WindowProc(hWnd, uMessage, wParam, lParam);
}



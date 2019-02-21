#include "StdAfx.h"
#include "cCWnd.h"

//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK CWndProc(HWND, UINT, WPARAM, LPARAM);

//不要把模版或者STL暴露到接口外，否则会出现C:4251警告

typedef map<HWND,cCWnd*>			CHandleMap;
CHandleMap							m_HandleMap;
//////////////////////////////////////////////////////////////////////////
cCWnd::cCWnd(void)
{
	m_hWnd = NULL;
	m_hInstance = NULL;
}

cCWnd::~cCWnd(void)
{
}

cCWnd::operator HWND() const
{ 
	return this == NULL ? NULL : m_hWnd; 
}

HWND cCWnd::GetHwnd() const
{
	return this == NULL ? NULL : m_hWnd;
}

BOOL cCWnd::Create( HINSTANCE hInstance,LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, HWND hWndParent, UINT nID, LPVOID lpParam /*= NULL*/ )
{
	assert(hWndParent != NULL);
	assert((dwStyle & WS_POPUP) == 0);

	return CreateEx(hInstance,0, lpszClassName, lpszWindowName,
		dwStyle | WS_CHILD,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		hWndParent, (HMENU)(UINT_PTR)nID, lpParam);
}

BOOL cCWnd::CreateEx( HINSTANCE hInstance,DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam /*= NULL*/ )
{
	WNDCLASS wcs;

	m_hInstance = hInstance;

	wcs.style			= CS_HREDRAW | CS_VREDRAW;
	wcs.lpfnWndProc		= CWndProc;
	wcs.cbClsExtra		= 0;
	wcs.cbWndExtra		= 0;
	wcs.hInstance		= hInstance;
	wcs.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcs.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcs.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcs.lpszMenuName	= lpszWindowName;
	wcs.lpszClassName	= lpszClassName;

	//注册窗口类
	RegisterClass(&wcs);

	m_hWnd = CreateWindowEx(dwExStyle,lpszClassName,lpszWindowName, dwStyle,x, y, nWidth, nHeight, hWndParent, nIDorHMenu,hInstance,this);

	if ( m_hWnd == NULL ) 
	{
		return FALSE;
	}

	return TRUE;
}

BOOL cCWnd::CreateEx( HINSTANCE hInstance,DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, HWND hWndParent, UINT nID, LPVOID lpParam /*= NULL*/ )
{
	return CreateEx(hInstance,dwExStyle,lpszClassName,lpszWindowName,dwStyle,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,hWndParent,(HMENU)nID,lpParam);
}

LRESULT cCWnd::WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	return ::DefWindowProc(hWnd, uMessage, wParam, lParam);
}

BOOL cCWnd::ShowWindow( int nCmdShow )
{
	return ::ShowWindow(m_hWnd,nCmdShow);
}

cCWnd* cCWnd::FromHandle( HWND hWnd )
{
	CHandleMap::iterator iter = m_HandleMap.find(hWnd);

	if ( iter == m_HandleMap.end() )
	{
		return NULL;
	}
	
	return iter->second;
}

LRESULT CALLBACK CWndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	cCWnd*pWnd = cCWnd::FromHandle(hWnd);
	if ( pWnd == NULL && uMessage == WM_NCCREATE )
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pWnd = static_cast<cCWnd*>(lpcs->lpCreateParams);
		pWnd->m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pWnd));

		m_HandleMap.insert(pair<HWND,cCWnd*>(hWnd,pWnd));
	}
	
	if ( pWnd != NULL ) return pWnd->WindowProc(hWnd, uMessage, wParam, lParam);

	return ::DefWindowProc(hWnd, uMessage, wParam, lParam);
}
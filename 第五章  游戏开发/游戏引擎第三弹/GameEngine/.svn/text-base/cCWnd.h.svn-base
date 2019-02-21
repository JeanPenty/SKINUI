#ifndef CWND_HEAD_FILE
#define CWND_HEAD_FILE

#pragma once

//窗口基类

class GAME_ENGINE_CLASS cCWnd
{
	//窗口变量
public:
	HWND							m_hWnd;
	HINSTANCE						m_hInstance;

public:
	cCWnd(void);
	virtual ~cCWnd(void);

	operator HWND() const;

	HWND GetHwnd() const;

public:
	static cCWnd*FromHandle(HWND hWnd);

	// for child windows, views, panes etc
	virtual BOOL Create(HINSTANCE hInstance,LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		HWND hWndParent, UINT nID,
		LPVOID lpParam = NULL);

	// advanced creation (allows access to extended styles)
	virtual BOOL CreateEx(HINSTANCE hInstance,DWORD dwExStyle, LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		int x, int y, int nWidth, int nHeight,
		HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);

	virtual BOOL CreateEx(HINSTANCE hInstance,DWORD dwExStyle, LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		HWND hWndParent, UINT nID,
		LPVOID lpParam = NULL);

	virtual LRESULT WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );

	BOOL ShowWindow(int nCmdShow);
};

#endif
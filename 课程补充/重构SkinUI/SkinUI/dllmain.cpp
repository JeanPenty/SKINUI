#include "Stdafx.h"
#include <AfxDllx.h>
#include "SkinUI.h"

//////////////////////////////////////////////////////////////////////////////////

//静态变量
static ULONG_PTR g_lGdiPlusToken=0L;
static AFX_EXTENSION_MODULE SkinUIDLL={NULL,NULL};

// 申明钩子
DETOUR_TRAMPOLINE(int   WINAPI SetScrollInfoT(HWND, int, LPCSCROLLINFO, BOOL), SetScrollInfo)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollInfoT(HWND, int, LPSCROLLINFO), GetScrollInfo)
DETOUR_TRAMPOLINE(int   WINAPI SetScrollPosT(HWND, int, int, BOOL), SetScrollPos)
DETOUR_TRAMPOLINE(int   WINAPI GetScrollPosT(HWND, int), GetScrollPos)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollRangeT(HWND, int, LPINT, LPINT), GetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI SetScrollRangeT(HWND, int, int, int, BOOL), SetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI ShowScrollBarT(HWND, int, BOOL), ShowScrollBar)
DETOUR_TRAMPOLINE(BOOL  WINAPI EnableScrollBarT(HWND, UINT, UINT), EnableScrollBar)


int WINAPI SetScrollInfoD(HWND hwnd, int fnBar, LPCSCROLLINFO lpsi, BOOL bRedraw)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_SetScrollInfo(hwnd, fnBar, lpsi, bRedraw);
	else
		return SetScrollInfoT(hwnd, fnBar, lpsi, bRedraw);
}

BOOL WINAPI GetScrollInfoD(HWND hwnd, int fnBar, LPSCROLLINFO lpsi)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_GetScrollInfo(hwnd, fnBar, lpsi);
	else
		return GetScrollInfoT(hwnd, fnBar, lpsi);
}

int WINAPI SetScrollPosD(HWND hwnd, int nBar, int nPos, BOOL bRedraw)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_SetScrollPos(hwnd, nBar, nPos, bRedraw);
	else
		return SetScrollPosT(hwnd, nBar, nPos, bRedraw);
}

int WINAPI GetScrollPosD(HWND hwnd, int nBar)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_GetScrollPos(hwnd, nBar);
	else
		return GetScrollPosT(hwnd, nBar);
}

BOOL WINAPI SetScrollRangeD(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_SetScrollRange(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
	else
		return SetScrollRangeT(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
}

BOOL WINAPI GetScrollRangeD(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_GetScrollRange(hwnd, nBar, lpMinPos, lpMaxPos);
	else
		return GetScrollRangeT(hwnd, nBar, lpMinPos, lpMaxPos);
}

BOOL WINAPI ShowScrollBarD(HWND hwnd, int nBar, BOOL bShow)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_ShowScrollBar(hwnd, nBar, bShow);
	else
		return ShowScrollBarT(hwnd, nBar, bShow);
}

BOOL WINAPI EnableScrollBarD(HWND hwnd, UINT wSBflags, UINT wArrows)
{
	if( SkinUI_IsValid(hwnd) )
		return SkinUI_EnableScrollBar(hwnd, wSBflags, wArrows);
	else
		return EnableScrollBarT(hwnd, wSBflags, wArrows);
}

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// 如果使用 lpReserved，请将此移除
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{		
		// 扩展 DLL 一次性初始化
		if (!AfxInitExtensionModule(SkinUIDLL, hInstance))return 0;
		new CDynLinkLibrary(SkinUIDLL);

		GdiplusStartupInput StartupInput;
		GdiplusStartup(&g_lGdiPlusToken,&StartupInput,NULL);

		//加载钩子
		DetourFunctionWithTrampoline((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
		DetourFunctionWithTrampoline((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
		DetourFunctionWithTrampoline((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
		DetourFunctionWithTrampoline((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
		DetourFunctionWithTrampoline((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
		DetourFunctionWithTrampoline((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
		DetourFunctionWithTrampoline((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
		DetourFunctionWithTrampoline((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		// 在调用析构函数之前终止该库
		AfxTermExtensionModule(SkinUIDLL);

		GdiplusShutdown(g_lGdiPlusToken);

		//卸载钩子
		DetourRemove((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
		DetourRemove((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
		DetourRemove((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
		DetourRemove((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
		DetourRemove((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
		DetourRemove((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
		DetourRemove((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
		DetourRemove((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
	}
	return 1;   // 确定
}

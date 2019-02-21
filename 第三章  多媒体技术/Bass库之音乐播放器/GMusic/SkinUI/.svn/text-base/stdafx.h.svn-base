#pragma once

//////////////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0500
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0510
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0500
#endif

#define _ATL_ATTRIBUTES
#define _AFX_ALL_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

//////////////////////////////////////////////////////////////////////////////////

//MFC 文件
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>

//图片控件
#import "ImageOle.dll" named_guids

//其他文件
#include "../SkinUI_ScrollBar/detours.h"
#include "../SkinUI_ScrollBar/SkinUI_ScrollBar.h"

//库文件
#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment (lib,"../Lib/SkinUI_ScrollBar_ud.lib")
#else
#pragma comment (lib,"../Lib/SkinUI_ScrollBar_d.lib")
#endif
#else
#ifdef _UNICODE
#pragma comment (lib,"../Lib/SkinUI_ScrollBar_u.lib")
#else
#pragma comment (lib,"../Lib/SkinUI_ScrollBar.lib")
#endif
#endif

#pragma comment (lib,"../Lib/Detours.lib")
#pragma comment(lib,"Gdiplus.lib")

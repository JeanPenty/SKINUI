#ifndef SKINUI_HEAD_FILE
#define SKINUI_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//系统头文件
#include <GdiPlus.h>
#include <Shlwapi.h>
#include <afxwin.h>
#include <vector>
#include <map>

using namespace Gdiplus;
using namespace std;

//////////////////////////////////////////////////////////////////////////

//导出定义
#ifndef SKINUI_CLASS
	#ifdef  SKINUI_DLL
		#define SKINUI_CLASS _declspec(dllexport)
	#else
		#define SKINUI_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifdef _DEBUG
	#define SKINUI_DLL_NAME	TEXT("SkinUID.dll")			//组件 DLL 名字
#else
	#define SKINUI_DLL_NAME	TEXT("SkinUI.dll")			//组件 DLL 名字
#endif

//////////////////////////////////////////////////////////////////////////
#define ON_RBN_DBLCLK(id, memberFxn) \
	ON_CONTROL(BN_CLICKED, id, memberFxn)

//////////////////////////////////////////////////////////////////////////
//ListBox Item
struct tagItemStruct
{
	UINT       itemID;
	UINT       itemWidth;
	UINT       itemHeight;
};

//导出类头文件
//////////////////////////////////////////////////////////////////////////
//平台头文件
#include "Macro.h"
#include "Function.h"
#include "MemoryDC.h"
#include "ImageEx.h"
#include "RenderManager.h"
#include "ISkinControl.h"

#ifndef SKINUI_DLL
	#include "SkinButton.h"
	#include "SkinComboBox.h"
	#include "SkinDialog.h"
	#include "SkinEdit.h"
	#include "SkinListBox.h"
	#include "SkinSliderCtrl.h"
	#include "SkinProgressCtrl.h"
	#include "SkinListCtrl.h"
	#include "SkinTreeCtrl.h"
	#include "SkinTabCtrl.h"
	#include "SkinRichEdit.h"
	#include "SkinMenu.h"
#endif


//////////////////////////////////////////////////////////////////////////

#endif
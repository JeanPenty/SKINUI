#ifndef SKINUI_HEAD_FILE
#define SKINUI_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//系统头文件
#include <GdiPlus.h>
#include <Shlwapi.h>
#include <afxwin.h>
#include <atlimage.h>
#include <vector>
#include <map>

using namespace Gdiplus;
using namespace std;

//FALSH 定义
#import "Flash.ocx" named_guids
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
	#ifdef _UNICODE
		#define SKINUI_DLL_NAME	TEXT("SkinUI_ud.dll")			//组件 DLL 名字
	#else
		#define SKINUI_DLL_NAME	TEXT("SkinUI_d.dll")			//组件 DLL 名字
	#endif
#else
	#ifdef _UNICODE
		#define SKINUI_DLL_NAME	TEXT("SkinUI_u.dll")			//组件 DLL 名字
	#else
		#define SKINUI_DLL_NAME	TEXT("SkinUI.dll")			//组件 DLL 名字
	#endif
#endif

//////////////////////////////////////////////////////////////////////////
interface IFlashContrlSink
{
public:
	//
	virtual void OnDraw(CDC*pDC,int nWidth,int nHeight)=NULL;
};
//////////////////////////////////////////////////////////////////////////
#define ON_RBN_DBLCLK(id, memberFxn) \
	ON_CONTROL(BN_CLICKED, id, memberFxn)

#define WM_EDIT_CLICK					WM_USER+0x50

#define CHECK_IMAGE(image)				((image != NULL) && (!image->IsNull()))
#define CHECK_HWND(pWnd)				((pWnd != NULL) && (!pWnd->GetSafeHwnd()))
//////////////////////////////////////////////////////////////////////////
//ListBox Item
struct tagItemStruct
{
	UINT       itemID;
	UINT       itemWidth;
	UINT       itemHeight;
};

//位置定位
enum
{
	en_LTop,
	en_RTop,
	en_LBottom,
	en_RBottom,
	en_Center
};

struct tagPositionData
{
	int			nFixedPostion[2];
	CPoint		ptPosition;
	CSize		szSize;
};

//导出类头文件
//////////////////////////////////////////////////////////////////////////
//平台头文件
#include "Macro.h"
#include "Function.h"
#include "MemoryDC.h"
#include "ImageEx.h"
#include "RenderManager.h"
#include "GifImage.h"
#include "BuildDialog.h"

#ifndef SKINUI_DLL
	#include "ISkinControl.h"
	#include "XmlManager.h"
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
	#include "FlashControl.h"
	#include "SkinToolBar.h"
#endif


//////////////////////////////////////////////////////////////////////////

#endif
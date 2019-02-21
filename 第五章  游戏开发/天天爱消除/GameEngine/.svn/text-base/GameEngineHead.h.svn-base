#ifndef GAME_ENGINE_HEAD_HEAD_FILE
#define GAME_ENGINE_HEAD_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//包含文件

//MFC 文件
#include <Afxmt.h>
#include <AtlBase.h>
#include <AfxTempl.h>
#include <MMSystem.h>

//D3D 文件
#include <D3D9.h>
#include <D3Dx9.h>

//////////////////////////////////////////////////////////////////////////////////
//公共定义

//导出定义
#ifndef GAME_ENGINE_CLASS
	#ifdef  GAME_ENGINE_DLL
		#define GAME_ENGINE_CLASS _declspec(dllexport)
	#else
		#define GAME_ENGINE_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifdef _DEBUG
	#ifdef _UNICODE
		#define GAME_ENGINE_DLL_NAME		TEXT("GameEngine_ud.dll")			//组件名字
	#else
		#define GAME_ENGINE_DLL_NAME		TEXT("GameEngine_d.dll")			//组件名字
	#endif
#else
	#ifdef _UNICODE
		#define GAME_ENGINE_DLL_NAME		TEXT("GameEngine_u.dll")			//组件名字
	#else
		#define GAME_ENGINE_DLL_NAME		TEXT("GameEngine.dll")				//组件名字
	#endif
#endif

//////////////////////////////////////////////////////////////////////////
//接口释放
#define SafeRelease(pObject) { if (pObject!=NULL) { pObject->Release(); pObject=NULL; } }

//删除指针
#define SafeDelete(pData) { try { delete pData; } catch (...) { ASSERT(FALSE); } pData=NULL; } 

//关闭句柄
#define SafeCloseHandle(hHandle) { if (hHandle!=NULL) { CloseHandle(hHandle); hHandle=NULL; } }

//删除数组
#define SafeDeleteArray(pData) { try { delete [] pData; } catch (...) { ASSERT(FALSE); } pData=NULL; } 

//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

#define Check_Image(pData)		( (pData != NULL) && (!pData->IsNull()) )
//////////////////////////////////////////////////////////////////////////

//资源信息
struct tagResourceInfo
{
	DWORD							dwSize;								//资源大小
	LPVOID							pcbBuffer;							//资源内存
};

#ifndef M_PI
	#define M_PI	3.14159265358979323846f
	#define M_PI_2	1.57079632679489661923f
	#define M_PI_4	0.785398163397448309616f
	#define M_1_PI	0.318309886183790671538f
	#define M_2_PI	0.636619772367581343076f
#endif

//////////////////////////////////////////////////////////////////////////////////
//导出文件

#ifndef GAME_ENGINE_DLL

	//D3D 引擎
	#include "D3DFont.h"
	#include "D3DDirect.h"
	#include "D3DDevice.h"
	#include "D3DSprite.h"
	#include "D3DTexture.h"
	#include "GameFrameView.h"

	//声音引擎
	#include "D3DSound.h"

	//游戏引擎
	#include "LapseCount.h"
	#include "VirtualEngine.h"
	#include "VirtualWindow.h"
	#include "VirtualButton.h"
	#include "VirtualSlider.h"
	#include "VirtualListBox.h"

	//事件驱动
	#include "MsgEvent.h"

	//管理引擎
	#include "TextureManager.h"

#endif

//////////////////////////////////////////////////////////////////////////////////

#endif
#ifndef VIRTUAL_ENGINE_HEAD_FILE
#define VIRTUAL_ENGINE_HEAD_FILE

#pragma once

#include "D3DDevice.h"
#include "GameEngineHead.h"
#include "D3DFont.h"
//////////////////////////////////////////////////////////////////////////////////

//类说明
class CVirtualEngine;
class CVirtualWindow;

//窗口数组
typedef CArray<CVirtualWindow *,CVirtualWindow *> CVirtualWindowPtrArray;				//窗口数组

//////////////////////////////////////////////////////////////////////////////////

//虚拟引擎
class GAME_ENGINE_CLASS CVirtualEngine
{
	//友元定义
	friend class CVirtualWindow;

	//配置变量
protected:
	CD3DDevice *					m_pD3DDevice;						//设备对象
	
public:
	CD3DFont						m_D3DDefaultFont;					//默认字体

	//状态变量
protected:
	CVirtualWindow *				m_pWindowLeave;						//离开窗口
	CVirtualWindow *				m_pWindowCapture;					//捕获窗口

	//内核变量
protected:
	CVirtualWindowPtrArray			m_VirtualWindowPtrArray;			//窗口数组---管理视图中所有控件窗口
	CVirtualWindowPtrArray			m_CaptureWindowPtrArray;			//窗口数组

	//函数定义
public:
	//构造函数
	CVirtualEngine();
	//析构函数
	virtual ~CVirtualEngine();

	//配置函数
public:
	//获取设备
	CD3DDevice * GetD3DDevice() { return m_pD3DDevice; }
	//设置设备
	VOID SetD3DDevice(CD3DDevice * pD3DDevice);

	//驱动函数
public:
	//绘画窗口
	bool DrawWindows(CD3DDevice * pD3DDevice);
	//消息处理
	bool DefWindowProc(UINT uMessage, WPARAM wParam, LPARAM lParam);
	//消息解释
	bool PreTranslateMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);
	//请求焦点
	VOID RequestFocus( CVirtualWindow * pVirtualWindow );

	//捕获函数
public:
	//离开注册
	bool RegisterLeave(CVirtualWindow * pVirtualWindow, bool bRegister);
	//扑获注册
	bool RegisterCapture(CVirtualWindow * pVirtualWindow, bool bRegister);

	//更新函数
private:
	//更新窗口
	VOID InvalidWindow();
	//更新窗口
	VOID InvalidWindow(INT nXPos, INT nYPos, INT nWidth, INT nHeight);

	//窗口搜索
private:
	//获取窗口
	CVirtualWindow * SwitchToWindow(INT nXMousePos, INT nYMousePos);
	//获取窗口
	CVirtualWindow * SwitchToWindow(CVirtualWindow * pVirtualWindow, INT nXMousePos, INT nYMousePos);
};

//////////////////////////////////////////////////////////////////////////////////

#endif
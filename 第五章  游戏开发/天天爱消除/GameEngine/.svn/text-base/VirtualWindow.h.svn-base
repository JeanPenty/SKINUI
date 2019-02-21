#ifndef VIRTUAL_WINDOW_HEAD_FILE
#define VIRTUAL_WINDOW_HEAD_FILE

#pragma once

#include "GameEngineHead.h"
#include "VirtualEngine.h"
#include "MsgEvent.h"

//////////////////////////////////////////////////////////////////////////

//虚拟窗口
class GAME_ENGINE_CLASS CVirtualWindow : public CMsgEvent
{
	//友元定义
	friend class CVirtualEngine;
	friend class CVirtualButton;

	//窗口属性
protected:
	bool							m_bActive;							//激活标志
	bool							m_bEnable;							//启用标志
	bool							m_bVisible;							//显示标志

	//属性变量
protected:
	UINT							m_uWindowID;						//窗口标识
	BOOL							m_bCaption;							//窗口拖动
	BOOL							m_bDrag;							//窗口拖动

	//位置变量
protected:
	CSize							m_WindowSize;						//窗口大小
	CPoint							m_BenchmarkPos;						//基准位置

	//内核变量
protected:
	CD3DFont *						m_pDefaultFont;
	CVirtualWindow *				m_pParentWindow;					//上层窗口
	CVirtualEngine *				m_pVirtualEngine;					//虚拟框架
	CVirtualWindowPtrArray			m_VirtualWindowPtrArray;			//窗口数组

	//函数定义
public:
	//构造函数
	CVirtualWindow();
	//析构函数
	virtual ~CVirtualWindow();

	//窗口标识
public:
	//获取标识
	UINT GetWindowID() { return m_uWindowID; }
	//设置标识
	VOID SetWindowID(UINT uWindowID) { m_uWindowID=uWindowID; }

	//属性对象
public:
	//上层窗口
	CVirtualWindow * GetParentWindow() { return m_pParentWindow; }
	//虚拟框架
	CVirtualEngine * GetVirtualEngine() { return m_pVirtualEngine; }
	//
	HWND GetSafeHwnd();

	//管理函数
public:
	//删除窗口
	VOID DeleteWindow();
	//激活窗口
	bool ActiveWindow(CRect & rcWindow, DWORD dwStyle, UINT uWindowID, CVirtualEngine * pVirtualEngine, CVirtualWindow * pParentWindow);

	//窗口属性
public:
	//激活属性
	bool IsWindowActive() { return m_bActive; }
	//控制属性
	bool IsWindowEnable() { return m_bEnable; }
	//显示属性
	bool IsWindowVisible() { return m_bVisible; }

	//窗口控制
public:
	//显示窗口
	VOID ShowWindow(bool bVisible);
	//禁止窗口
	VOID EnableWindow(bool bEnable);
	//激活窗口
	VOID ActiveWindow(bool bActive);
	//更新窗口
	VOID InvalidWindow(bool bCoerce);
	//设置焦点
	VOID SetFocus();
	//销毁焦点
	VOID KillFocus();
	//禁止窗口
	VOID SetCaption(bool bCaption=true){ m_bCaption = bCaption;}

	//窗口位置
public:
	//窗口大小
	VOID GetClientRect(CRect & rcClient);
	//窗口大小
	VOID GetWindowRect(CRect & rcWindow);
	//设置位置
	VOID SetWindowPos(INT nXPos, INT nYPos, INT nWidth, INT nHeight, UINT uFlags);
	//拖动窗口
	BOOL DragWindows( UINT uMessage, INT nXMousePos, INT nYMousePos, UINT nFlags );

	//功能函数
public:
	//下属窗口
	bool IsChildWindow(CVirtualWindow * pVirtualWindow);
	BOOL ContainsPoint( POINT pt );
	void SetFont(CD3DFont*pFont);

	//系统事件
protected:
	//动画消息
	virtual VOID OnWindowMovie() { return; }
	//创建消息
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice) { return; }
	//销毁消息
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice) { return; }
	//位置消息
	virtual VOID OnWindowPosition(CD3DDevice * pD3DDevice){ return; }
	//鼠标事件
	virtual BOOL OnWindowMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);

	//重载函数
protected:
	//鼠标事件
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos)=NULL;
	//键盘事件
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam)=NULL;
	//绘画窗口
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos)=NULL;

	//内部函数
private:
	//重置窗口
	VOID ResetWindow();
	//绘画窗口
	VOID OnEventDrawChildWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);
};

//////////////////////////////////////////////////////////////////////////////////

#endif
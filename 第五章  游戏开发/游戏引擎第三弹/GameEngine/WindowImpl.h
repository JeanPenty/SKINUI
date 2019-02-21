#ifndef GAME_FRAME_VIEW_HEAD_FILE
#define GAME_FRAME_VIEW_HEAD_FILE

#pragma once

#include "Tracedialog.h"
// CWindowImpl

class GAME_ENGINE_CLASS CWindowImpl : public CMsgEvent, public ID3DDeviceSink, public cCWnd
{
	//状态变量
protected:
	bool							m_bInitD3D;							//创建标志
	HANDLE 							m_hRenderThread;					//渲染线程
	HWND							m_hOwnWnd;

	//帧数统计
protected:
	DWORD							m_dwDrawBenchmark;					//基准起点
	DWORD							m_dwDrawLastCount;					//绘画次数
	DWORD							m_dwDrawCurrentCount;				//绘画次数

	//组件变量
public:
	CD3DDirect						m_D3DDirect;						//环境对象
	CD3DDevice						m_D3DDevice;						//设备对象
	CVirtualEngine					m_VirtualEngine;					//虚拟引擎
	CTraceDialog					m_TraceDialog;

	//函数定义
public:
	//构造函数
	CWindowImpl();
	//析构函数
	virtual ~CWindowImpl();

	//界面函数
private:
	//调整控件
	virtual VOID RectifyControl(INT nWidth, INT nHeight){}
	//动画驱动
	virtual VOID CartoonMovie(){}
	//配置界面
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight){}
	//绘画界面
	virtual VOID DrawGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight){}

	//设备接口
protected:
	//配置设备
	virtual VOID OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//丢失设备
	virtual VOID OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//重置设备
	virtual VOID OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//渲染窗口
	virtual VOID OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//重载函数
protected:
	//默认回调
	virtual LRESULT WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );

	//功能函数
public:
	//渲染线程
	VOID StartRenderThread();
	//
	VOID SetLogFile(LPCTSTR lpszNameFile);
	//
	INT InitInstance(HINSTANCE hInstance,LPCTSTR lpszWindowName);

	//自定消息
protected:
	//渲染消息
	void OnMessageD3DRender();

	//静态函数
private:
	//渲染线程
	static VOID D3DRenderThread(LPVOID pThreadData);
};

#endif

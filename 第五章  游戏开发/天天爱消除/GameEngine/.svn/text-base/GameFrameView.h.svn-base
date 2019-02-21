#ifndef GAME_FRAME_VIEW_HEAD_FILE
#define GAME_FRAME_VIEW_HEAD_FILE

#pragma once

#include "GameEngineHead.h"
#include "D3DDevice.h"
#include "D3DDirect.h"
#include "VirtualEngine.h"
#include "VirtualWindow.h"
#include "Tracedialog.h"
// CGameFrameView

class GAME_ENGINE_CLASS CGameFrameView : public CDialog,public CMsgEvent, public ID3DDeviceSink
{
	DECLARE_DYNAMIC(CGameFrameView)
	
	//状态变量
protected:
	bool							m_bInitD3D;							//创建标志
	HANDLE 							m_hRenderThread;					//渲染线程

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
	CGameFrameView(UINT nIDTemplate,CWnd* pParent = NULL);
	//析构函数
	virtual ~CGameFrameView();

	//界面函数
private:
	//调整控件
	virtual VOID RectifyControl(INT nWidth, INT nHeight)=NULL;
	//动画驱动
	virtual VOID CartoonMovie()=NULL;
	//配置界面
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;
	//绘画界面
	virtual VOID DrawGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)=NULL;

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
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//默认回调
	virtual LRESULT DefWindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam);

	//功能函数
public:
	//渲染线程
	VOID StartRenderThread();
	//
	VOID SetLogFile(LPCTSTR lpszNameFile);

	//消息映射
protected:
	//绘画函数
	VOID OnPaint();
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//创建消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	//自定消息
protected:
	//数据消息
	LRESULT OnMessageD3DStatus(WPARAM wParam, LPARAM lParam);
	//渲染消息
	LRESULT OnMessageD3DRender(WPARAM wParam, LPARAM lParam);

	//静态函数
private:
	//渲染线程
	static VOID D3DRenderThread(LPVOID pThreadData);

protected:
	DECLARE_MESSAGE_MAP()
};

#endif

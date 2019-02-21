#ifndef LAYERED_HEAD_FILE
#define LAYERED_HEAD_FILE

#pragma once
#include "ImageEx.h"
#include <atlimage.h>

//分层窗口
class CLayeredWindow : public CWnd
{
	DECLARE_DYNAMIC(CLayeredWindow)
	
	//变量定义
protected:
	CWnd *							m_pWndControl;						//控件窗口

	//函数定义
public:
	//构造函数
	CLayeredWindow();
	//析构函数
	virtual ~CLayeredWindow();

	//功能函数
public:
	//创建窗口
	VOID CreateLayered(CWnd * pWndControl, CRect & rcWindow);
	//设置区域
	VOID InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);
	//设置区域
	VOID InitLayeredArea(CImageEx & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);

	//消息映射
protected:
	//关闭消息
	VOID OnClose();
	//焦点消息
	VOID OnSetFocus(CWnd * pOldWnd);

	//静态函数
protected:
	//枚举函数
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
class CLayeredDialog : public CDialog
{
	DECLARE_DYNAMIC(CLayeredDialog)

	//变量定义
protected:
	CImageEx					m_ImageBack;			//背景图片
	CLayeredWindow				m_LayeredWindow;		//分层窗口

	//函数定义
public:
	//构造函数
	CLayeredDialog(UINT uTemplate, CWnd* pParent = NULL); 
	//析构函数
	virtual ~CLayeredDialog();

protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange* pDX);
	//绘画消息
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight){}

	//基本函数
public:
	//初始化
	void SetLayeredDialog(HINSTANCE hInstance,LPCTSTR lpResource,CSize szSizeLT,CSize szSizeRB);
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//去除边框
	void RemoveBorder();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
#endif

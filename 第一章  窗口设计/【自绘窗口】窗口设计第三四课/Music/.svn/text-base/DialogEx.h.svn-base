#pragma once


// CDialogEx 对话框
#include "ImageEx.h"
#include "ButtonEx.h"

class CDialogEx : public CDialog
{
	DECLARE_DYNAMIC(CDialogEx)
	
	//加载资源
protected:
	CImageEx 					m_ImageBack;		//背景图片

	//控件变量
protected:
	CButtonEx					m_btClose;			//关闭按钮
	CButtonEx					m_btMax;			//最大化按钮
	CButtonEx					m_btMin;			//最小化按钮

	//基本变量
protected:
	bool						m_bIsInit;			//是否已经初始化
	bool						m_bIsZoomed;		//是否最大化
	bool						m_bExtrude;			//是否可以拉伸

public:
	CDialogEx(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogEx();

protected:
	//DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);    
	//初始化
	virtual BOOL OnInitDialog();
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//消息函数
protected:
	//绘制消息
	afx_msg void OnPaint();
	//窗口大小
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//鼠标按下
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//点击消息
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//鼠标按下
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	//基本函数
public:
	//背景图片
	bool LoadBackSkin(LPCTSTR pszResourcePath);
	//加载图片
	bool LoadBackSkin(HINSTANCE hInstance, LPCTSTR pszResourceName);
	//移除边框
	void RemoveBorder();
	//设置拉伸
	inline void SetExtrude(bool bExtrude){ m_bExtrude = bExtrude;}

	//派生函数
public:
	//最大化
	virtual	bool OnMaxSize(){ return false; }
	//客户区
	virtual void OnClientDraw(CDC*pDC,INT nWidth,INT nHeight){}

	DECLARE_MESSAGE_MAP()
};

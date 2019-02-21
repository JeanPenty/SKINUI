#pragma once


// CButtonEx
#include "ImageEx.h"

class CButtonEx : public CButton
{
	DECLARE_DYNAMIC(CButtonEx)
	
	//变量定义
protected:
	bool								m_bExpand;						//是否拉伸
	bool								m_bHovering;					//盘旋标志
	COLORREF							m_crTextColor;					//字体颜色
	CImageEx							m_ImageBack;					//按钮位图

	//函数定义
public:
	//构造函数
	CButtonEx();
	//析构函数
	virtual ~CButtonEx();

	//重载函数
protected:
	//控件子类化
	virtual void PreSubclassWindow();
	//界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//设置函数
public:
	//调整位置
	bool FixButtonSize();
	//设置颜色
	bool SetTextColor(COLORREF crTextColor);
	//加载位图
	bool SetButtonImage(LPCTSTR pszFileName, bool bExpandImage=false);
	//加载位图
	bool SetButtonImage(HINSTANCE hInstance,LPCTSTR pszResourceName, bool bExpandImage=false);

	//消息函数
protected:
	//建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//鼠标离开
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//重绘背景
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()
};



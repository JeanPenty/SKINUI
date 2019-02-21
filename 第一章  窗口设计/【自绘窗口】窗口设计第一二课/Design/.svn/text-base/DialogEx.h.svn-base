#pragma once


// CDialogEx 对话框
#include "ImageEx.h"

class CDialogEx : public CDialog
{
	DECLARE_DYNAMIC(CDialogEx)
	
	enum
	{
		en_Normal,
		en_Hoven,
		en_Press
	};
	//按钮状态
private:
	BYTE						m_cbNowHotIndex[3];					//现在焦点
	BYTE						m_cbNowButtonIndex;					//按钮索引
	BYTE						m_cbButtonState[3];					//按钮状态
	CRect						m_rcButton[3];						//按钮位置

	//加载资源
protected:
	CImageEx 					m_ImageTitleL;
	CImageEx 					m_ImageTitleM;
	CImageEx 					m_ImageTitleM_Spe;
	CImageEx 					m_ImageTitleR;

	CImageEx 					m_ImageBt_Close;
	CImageEx 					m_ImageBt_Max;
	CImageEx 					m_ImageBt_Res;
	CImageEx 					m_ImageBt_Min;

public:
	CDialogEx(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogEx();

	//消息映射
public:
	//修改尺寸
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	//非客户区绘制
	afx_msg void OnNcPaint();
	//窗口尺寸
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//非客户区鼠标移动
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	//非客户区鼠标移开
	afx_msg void OnNcMouseLeave();
	//非客户区鼠标按下
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	//非客户区鼠标抬起
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);

protected:
	//DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);    
	//消息循环
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//初始化
	virtual BOOL OnInitDialog();

	//绘制函数
public:
	//绘制标题
	void DrawTitleBar(CDC*pDC);
	//绘制按钮
	void DrawTitleButton(CDC*pDC);

	DECLARE_MESSAGE_MAP()
};

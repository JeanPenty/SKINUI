// LandmineDlg.h : 头文件
//

#pragma once
#include "GameFrame.h"
#include "OptionDlg.h"

// CLandmineDlg 对话框
class CLandmineDlg : public CDialog
{
// 构造
public:
	CLandmineDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LANDMINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CGameFrame			m_GameFrame;
	CMenu				m_MenuBar;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	afx_msg void OnLow();
	afx_msg void OnMid();
	afx_msg void OnHigh();
	afx_msg void OnCustom();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

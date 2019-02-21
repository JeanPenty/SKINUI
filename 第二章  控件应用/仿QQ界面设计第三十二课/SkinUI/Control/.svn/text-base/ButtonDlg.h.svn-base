#pragma once

#include "DlgControlItem.h"

// CButtonDlg 对话框

class CButtonDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CButtonDlg)

protected:
	CSkinButton				m_Button2;
	CSkinButton				m_Button3;
	CSkinButton				m_Button4;
	CSkinButton				m_Button5;
	CSkinButton				m_Button6;
	CSkinButton				m_Button7;
	CSkinButton				m_Button8;
	CSkinButton				m_Button9;
	CImageEx				m_ImageBack;

public:
	CButtonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CButtonDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	virtual BOOL OnInitDialog();
	
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//接口函数
protected:
	//绘制函数
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	
	//消息函数
protected:
	//按钮响应
	afx_msg void OnBnClickedButton1();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};

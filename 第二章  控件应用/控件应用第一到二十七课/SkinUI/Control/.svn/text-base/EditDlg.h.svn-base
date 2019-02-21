#pragma once
#include "DlgControlItem.h"

// CEditDlg 对话框

class CEditDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CEditDlg)
protected:
	DWORD						m_dwStyle;
	CEdit						m_Edit;
	CSkinEdit					m_SkinEdit1;
	CSkinEdit					m_SkinEdit2;
	CSkinEdit					m_SkinEdit3;
	CSkinEdit					m_SkinEdit5;
public:
	CEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	//接口函数
protected:
	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedPassWord();
	afx_msg void OnBnClickedFind();
};

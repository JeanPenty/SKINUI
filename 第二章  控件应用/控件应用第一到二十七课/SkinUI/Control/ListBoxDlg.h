#pragma once


// CListBoxDlg 对话框
#include "DlgControlItem.h"

class CListBoxDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CListBoxDlg)

protected:
	CSkinListBox			m_ListBox;
	CSkinListBox			m_ListBox2;

public:
	CListBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CListBoxDlg();

// 对话框数据
	enum { IDD = IDD_LISTBOXDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnRbnDblclkList1();
	afx_msg void OnRbnDblclkList2();
};

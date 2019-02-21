#pragma once

#include "DlgControlItem.h"
// CComBoxDlg 对话框

class CComBoxDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CComBoxDlg)

protected:
	CComboBox				m_ComboBox1;
	CComboBox				m_ComboBox2;

	CComboBox				m_ComboBox3;
	CComboBox				m_ComboBox4;
	
	CSkinComboBox			m_SkinComboBox;
	CSkinComboBox			m_SkinComboBox2;

public:
	CComBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CComBoxDlg();

// 对话框数据
	enum { IDD = IDD_COMBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void SetCombox(LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpItemKeyName,CComboBox * pCComboBox );

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton5();
	//Edit移开
	LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
};

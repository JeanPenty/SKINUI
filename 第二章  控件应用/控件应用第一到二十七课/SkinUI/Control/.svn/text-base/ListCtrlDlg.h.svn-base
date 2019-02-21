#pragma once

#include "DlgControlItem.h"

// CListCtrlDlg 对话框

class CListCtrlDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CListCtrlDlg)

protected:
	CListCtrl					m_ListCtrl1;
	CListCtrl					m_ListCtrl2;
	CListCtrl					m_ListCtrl3;
	CListCtrl					m_ListCtrl4;
	CSkinListCtrl				m_ListCtrl5;
	CSkinListCtrl				m_ListCtrl6;

	CImageList					m_StatusImage;						//状态位图
	CImageList					m_ImageList1;

public:
	CListCtrlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CListCtrlDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickInsert();
	afx_msg void OnBnClickCheckState();
	afx_msg void OnBnClickSel();
	afx_msg void OnBnClickInfo();
	afx_msg void OnBnClickVis();
	afx_msg void OnBnClickUnSel();
	afx_msg void OnBnClickHead();
	afx_msg void OnBnClickRemoveAll();
	afx_msg void OnBnClickRemoveItem();
	afx_msg void OnBnClickRemove();
	afx_msg void OnLclickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
};

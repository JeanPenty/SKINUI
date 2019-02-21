#pragma once

#include "DlgControlItem.h"
// CTreeCtrlDlg 对话框

class CTreeCtrlDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CTreeCtrlDlg)
protected:
	CTreeCtrl				m_TreeCtrl;
	CSkinTreeCtrl			m_TreeCtrl1;
	CImageList				m_StatusImage;

public:
	CTreeCtrlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTreeCtrlDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	int SetItemHeight(HTREEITEM hItem);
	void ExpandAllItem(CTreeCtrl *pTreeCtrl,HTREEITEM hTreeItem,bool bExpand = true);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void InitTree();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton13();

	void RemoveCheck( HTREEITEM hTreeItem );

	void SetStyle( UINT ID,DWORD dwStyle,DWORD &dwAddStyle, DWORD &dwRemoveStyle );

};

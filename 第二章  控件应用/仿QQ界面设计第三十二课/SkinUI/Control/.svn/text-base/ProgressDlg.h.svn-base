#pragma once

#include "DlgControlItem.h"
// CProgressDlg 对话框

class CProgressDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CProgressDlg)

protected:
	CSkinProgressCtrl					m_ProgressCtrl1;
	CSkinProgressCtrl					m_ProgressCtrl2;

public:
	CProgressDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgressDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
};

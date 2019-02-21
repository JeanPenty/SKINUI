#pragma once

#include "DlgControlItem.h"
// CProgressDlg �Ի���

class CProgressDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CProgressDlg)

protected:
	CSkinProgressCtrl					m_ProgressCtrl1;
	CSkinProgressCtrl					m_ProgressCtrl2;

public:
	CProgressDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProgressDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
};

#pragma once
#include "DlgControlItem.h"

// CScrollDlg 对话框

class CScrollDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CScrollDlg)
protected:
	CScrollBar				m_ScrollBar1;
	CScrollBar				m_ScrollBar2;

	int						m_nCurrentPos;
public:
	CScrollDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScrollDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void Start();
	afx_msg void Stop();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};

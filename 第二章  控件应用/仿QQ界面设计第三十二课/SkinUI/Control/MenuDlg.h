#pragma once

#include "DlgControlItem.h"

// CMenuDlg 对话框

class CMenuDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CMenuDlg)
protected:
	CMenu				m_MenuBar;

public:
	CMenuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMenuDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//鼠标右键
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

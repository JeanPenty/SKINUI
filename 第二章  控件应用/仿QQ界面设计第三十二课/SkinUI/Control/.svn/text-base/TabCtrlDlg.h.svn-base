#pragma once

#include "DlgControlItem.h"
// CTabCtrlDlg 对话框

class CTabCtrlDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CTabCtrlDlg)
protected:
	CTabCtrl				m_TabCtrl;
	CTabCtrl				m_TabCtrl1;
	CTabCtrl				m_TabCtrl2;

	CSkinTabCtrl			m_TabCtrl3;
	CSkinTabCtrl			m_TabCtrl4;

	CImageEx				m_ImageBack;

public:
	CTabCtrlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabCtrlDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnDropDownTab1(NMHDR *pNMHDR, LRESULT *pResult);
	BOOL InitQQTabCtrl();
	BOOL InitQQSafeTabCtrl();
};

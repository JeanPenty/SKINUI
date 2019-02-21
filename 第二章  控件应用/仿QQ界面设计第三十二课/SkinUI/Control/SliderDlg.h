#pragma once

#include "DlgControlItem.h"
// CSliderDlg 对话框

class CSliderDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CSliderDlg)

protected:
	CSliderCtrl						m_SliderCtrl;
	CSliderCtrl						m_SliderCtrl2;
	CSkinSliderCtrl					m_SliderCtrl3;
	CSkinSliderCtrl					m_SliderCtrl4;

public:
	CSliderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSliderDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()
};

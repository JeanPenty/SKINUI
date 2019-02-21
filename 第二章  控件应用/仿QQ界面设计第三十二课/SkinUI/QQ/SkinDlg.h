#pragma once

#include "SkinManager.h"

#define SKIN_COUNT	15
// CSkinDlg 对话框

class CSkinDlg : public CSkinManager
{
	DECLARE_DYNAMIC(CSkinDlg)
protected:
	CImageEx			*m_pImageTest;

	CImageEx			*m_pImageSkin[SKIN_COUNT];
	bool				m_bLeftDrawExtrude[SKIN_COUNT];
	CRect				m_rcItem[SKIN_COUNT];

	int					m_nHovenItem;
	int					m_nSelItem;

public:
	CSkinDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSkinDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	virtual BOOL OnInitDialog();

	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
};

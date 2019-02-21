#pragma once

//////////////////////////////////////////////////////////////////////////
//	
//	
//	皮肤窗口
//	
//////////////////////////////////////////////////////////////////////////

#include "BaseDialog.h"

#define SKIN_COUNT	16
// CSkinDlg 对话框

class CSkinDlg : public CBaseDialog
{
	DECLARE_DYNAMIC(CSkinDlg)
protected:
	CImageEx			* m_pImageHoven;
	CImageEx			* m_pImageShadow;
	CImageEx			*m_pImageSkin[SKIN_COUNT];
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

#pragma once


// CBaseDialog 对话框

class CBaseDialog : public CSkinDialog
{
	DECLARE_DYNAMIC(CBaseDialog)

protected:
	CImageEx					*m_pImageBack;

	CSkinButton					m_btClose;
	CSkinButton					m_btMax;
	CSkinButton					m_btMin;
	bool						m_bIsZoomed;

public:
	CBaseDialog(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseDialog();

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	virtual void DrawView(CDC*pDC,int nWidth,int nHeight){}

public:
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickWindowMin();
	afx_msg void OnBnClickWindowMax();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
};

#pragma once

//////////////////////////////////////////////////////////////////////////
//	
//	
//	窗口基类，所有子窗口全部派生自这里，基类用来管理换肤等繁琐的界面操作
//	
//////////////////////////////////////////////////////////////////////////

enum AFX_WND_STYLE
{
	en_Wnd_Normal=0,			//关闭，最大化，最小化同时存在
	en_Wnd_MinimizeBox,			//无最大化按钮
	en_Wnd_CloseBox,			//只有关闭按钮
	en_Wnd_None					//无按钮
};
// CBaseDialog 对话框

class CBaseDialog : public CSkinDialog
{
	DECLARE_DYNAMIC(CBaseDialog)

protected:
	CImageEx					*m_pImageBack;
	CImageEx					* m_pShadow;

	CSkinButton					m_btClose;
	CSkinButton					m_btMax;
	CSkinButton					m_btMin;

	bool						m_bIsZoomed;
	AFX_WND_STYLE				m_enWndStyle;

public:
	CBaseDialog(UINT nIDTemplate,CWnd* pParent = NULL,AFX_WND_STYLE Style = en_Wnd_Normal);   // 标准构造函数
	virtual ~CBaseDialog();

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	virtual void DrawView(CDC*pDC,int nWidth,int nHeight){}
	
	void UpdateSkin();

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

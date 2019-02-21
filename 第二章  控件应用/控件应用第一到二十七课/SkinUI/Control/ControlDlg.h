// ControlDlg.h : 头文件
//

#pragma once
#include "ListBoxEx.h"

#include "ButtonDlg.h"
#include "EditDlg.h"
#include "ComBoxDlg.h"
#include "ListBoxDlg.h"
#include "ScrollDlg.h"
#include "SliderDlg.h"
#include "ProgressDlg.h"
#include "ListCtrlDlg.h"
#include "TreeCtrlDlg.h"
#include "TabCtrlDlg.h"
#include "RichEditDlg.h"
#include "MenuDlg.h"

typedef vector<CDlgControlItem*>			CArrayControl;

// CControlDlg 对话框
class CControlDlg : public CSkinDialog
{
protected:
	CImageEx						m_ImageBack;
	CImageEx						m_ImageLogo;
	CSkinButton						m_btClose;
	CSkinButton						m_btMinSize;
	CListBoxEx						m_ListBoxEx;

	bool							m_bIsInit;

	//变量定义
protected:
	WORD							m_wItemCount;						//子项数目
	WORD							m_wActiveIndex;						//活动索引
	CArrayControl					m_ArrayControl;

	//控件窗口
protected:
	CButtonDlg						m_ButtonDlg;
	CEditDlg						m_EditDlg;
	CComBoxDlg						m_ComBoxDlg;
	CListBoxDlg						m_ListBoxDlg;
	CScrollDlg						m_ScrollDlg;
	CSliderDlg						m_SliderDlg;
	CProgressDlg					m_ProgressDlg;
	CListCtrlDlg					m_ListCtrlDlg;
	CTreeCtrlDlg					m_TreeCtrlDlg;
	CTabCtrlDlg						m_TabCtrlDlg;
	CRichEditDlg					m_RichEditDlg;
	CMenuDlg						m_MenuDlg;

	HICON m_hIcon;

// 构造
public:
	CControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONTROL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	virtual BOOL OnInitDialog();

protected:
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	LRESULT OnActiveItem(WPARAM wParam,LPARAM lParam);

	//功能函数
public:
	//激活配置
	bool ActiveOptionItem(WORD wIndex);	
	void RectifyControl( int cx, int cy );
	
protected:
	DECLARE_MESSAGE_MAP()
};

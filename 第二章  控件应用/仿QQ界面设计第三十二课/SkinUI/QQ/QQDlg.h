// QQDlg.h : 头文件
//

#pragma once
#include "LogonDlg.h"
#include "BuddyListBox.h"
#include "HideWindow.h"
#include "SkinManager.h"
#include "SkinDlg.h"

// CQQDlg 对话框
class CQQDlg : public CSkinManager
{
protected:
	CLogonDlg						m_LogonDlg;
	CImageEx						* m_pImageSearch;
	CImageEx						* m_pImageSearchText;

	CString							m_StrName;
	CString							m_StrNote;

	//控件
protected:
	CSkinButton						m_btSkin;
	CSkinButton						m_btWrite;

	bool							m_bShowEdit;
	CEdit							m_EditWrite;
	CEdit							m_EditSearch;
	CSkinButton						m_btClearSearch;

	CSkinButton						m_btState;
	CFont							m_ftName;

	//Tab+好友列表
	CSkinTabCtrl					m_TabCtrl;
	CBuddyListBox					m_BuddyList;
	CBuddyListBox					m_GroupList;
	CBuddyListBox					m_MsgList;

	//QQ面板按钮
	CSkinButton						m_btQQApp[5];
	CSkinButton						m_btMenu;
	CSkinButton						m_btTool[4];
	CSkinButton						m_btApply[4];

	CHideWindow						m_HideWindow;
	CSkinDlg						m_SkinManager;

public:
	CQQDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQQDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	virtual BOOL OnInitDialog();

	LRESULT OnLogonMessage(WPARAM wParam,LPARAM lParam);

	void UpdataResource();

	void InitGroupList();
	void InitMsgList();

	void InitBuddyList();

	void InitTabCtrl();

	int GetNameLength();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnEnKillfocusEditPass();
	afx_msg void OnEnKillfocusEditSearch();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);

	void OnTcnDropDownMenu( NMHDR *pNMHDR, LRESULT *pResult );
	void OnTcnSelchangeType( NMHDR *pNMHDR, LRESULT *pResult );
	void OnBnClickOpenChat( NMHDR *pNMHDR, LRESULT *pResult );
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

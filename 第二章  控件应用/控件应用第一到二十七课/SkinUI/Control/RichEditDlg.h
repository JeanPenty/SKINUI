#pragma once

#include "DlgControlItem.h"
// CRichEditDlg 对话框

class CRichEditDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CRichEditDlg)
protected:
	CRichEditCtrl							m_RichEditCtrl;
	CSkinRichEdit							m_SkinRichEdit;
	CHARFORMAT2								m_cf2;

public:
	CRichEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRichEditDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	//加载回调
	static DWORD CALLBACK LoadCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);
	//保存回调
	static DWORD CALLBACK SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnRClicked();
	void InsertTips();

	void OnURLClick(NMHDR *pNmhdr, LRESULT *pResult);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton7();

	//菜单命令
protected:
	//删除信息
	VOID OnClearAll();
	//全部选择
	VOID OnSelectAll();
	//拷贝字符
	VOID OnCopyString();
};

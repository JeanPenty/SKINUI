// DataBaseDlg.h : 头文件
//

#pragma once


// CDataBaseDlg 对话框
class CDataBaseDlg : public CDialog
{
// 构造
public:
	CDataBaseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DATABASE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CListCtrl	m_ListCtrl;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedQuery2();

	void ExecuteQuery(bool bSentence);

};

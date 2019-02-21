
// 360SafeDlg.h : 头文件
//

#pragma once


// CMy360SafeDlg 对话框
class CMy360SafeDlg : public CSkinDialog
{
// 构造
public:
	CMy360SafeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY360SAFE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickCheck();

	DECLARE_MESSAGE_MAP()
};

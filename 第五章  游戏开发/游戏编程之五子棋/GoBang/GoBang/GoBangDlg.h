// GoBangDlg.h : 头文件
//

#pragma once
#include "ImageEx.h"
#include "ChessBorad.h"

// CGoBangDlg 对话框
class CGoBangDlg : public CDialog
{
// 构造
public:
	CGoBangDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GOBANG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CImageEx			m_ImageBack;
	CChessBorad			m_ChessBorad;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetOption(bool bWhiteColor,bool bIGo);
};

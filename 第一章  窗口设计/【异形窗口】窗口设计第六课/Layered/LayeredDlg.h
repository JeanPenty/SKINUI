// LayeredDlg.h : 头文件
//
/*
		我的个人博客近期将继续推出MFC实例课程讲解，如果你对此感兴趣，

			欢迎访问我的博客主页，http://www.gymsaga.com/

			MFC专栏请进 --- http://www.gymsaga.com/category/project/developc/mfc

			本次实例代码讲解地址：http://www.gymsaga.com/project/350.html

	如果你有什么不懂的，或者我讲的地方有那些不对或者不恰当的地方，也欢迎你批评指正
*/

#pragma once
#include "LayeredWindow.h"


// CLayeredDlg 对话框
class CLayeredDlg : public CLayeredDialog
{

// 构造
public:
	CLayeredDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LAYERED_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

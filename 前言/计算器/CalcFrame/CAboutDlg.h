// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
#pragma once

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
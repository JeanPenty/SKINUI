#pragma once


// COptionDlg 对话框

class COptionDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionDlg)
public:
	int					m_nRowCount;
	int					m_nColCount;
	int					m_nMineCount;

public:
	COptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

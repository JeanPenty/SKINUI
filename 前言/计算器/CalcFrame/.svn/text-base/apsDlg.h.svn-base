#pragma once


// CapsDlg 对话框

class CapsDlg : public CDialog
{
	DECLARE_DYNAMIC(CapsDlg)

protected:
	CString					m_strCap;
public:
	CapsDlg(CString Str,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CapsDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	//转换字符
	VOID SwitchScoreString(__int64 lScore, LPTSTR pszBuffer, WORD wBufferSize);

public:
	afx_msg void OnBnClickedBtCopy();
};

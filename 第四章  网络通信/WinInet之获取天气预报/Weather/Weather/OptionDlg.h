#pragma once


// COptionDlg 对话框

class COptionDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionDlg)
protected:
	CComboBox					m_comProvince;
	CComboBox					m_comCity;

public:
	CString						m_strProvince;
	CString						m_strCity;

public:
	COptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionDlg();

// 对话框数据
	enum { IDD = IDD_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void SetCityList(int nSel);

	afx_msg void OnCbnSelchangeProvince();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult);
};

// DataBaseDlg.h : ͷ�ļ�
//

#pragma once


// CDataBaseDlg �Ի���
class CDataBaseDlg : public CDialog
{
// ����
public:
	CDataBaseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DATABASE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CListCtrl	m_ListCtrl;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedQuery2();

	void ExecuteQuery(bool bSentence);

};


// SampleDlg.h : ͷ�ļ�
//

#pragma once


// CSampleDlg �Ի���
class CSampleDlg : public CSkinDialog
{
	CFlashControl					m_FlashControl;

// ����
public:
	CSampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer( UINT_PTR nIDEvent );
	DECLARE_MESSAGE_MAP()
};

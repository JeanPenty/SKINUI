
// 360SafeDlg.h : ͷ�ļ�
//

#pragma once


// CMy360SafeDlg �Ի���
class CMy360SafeDlg : public CSkinDialog
{
// ����
public:
	CMy360SafeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY360SAFE_DIALOG };

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
	afx_msg void OnBnClickCheck();

	DECLARE_MESSAGE_MAP()
};

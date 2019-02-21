// GoBangDlg.h : ͷ�ļ�
//

#pragma once
#include "ImageEx.h"
#include "ChessBorad.h"

// CGoBangDlg �Ի���
class CGoBangDlg : public CDialog
{
// ����
public:
	CGoBangDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GOBANG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CImageEx			m_ImageBack;
	CChessBorad			m_ChessBorad;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetOption(bool bWhiteColor,bool bIGo);
};

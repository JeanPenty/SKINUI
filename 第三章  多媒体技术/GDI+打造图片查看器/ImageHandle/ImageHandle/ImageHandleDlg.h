// ImageHandleDlg.h : ͷ�ļ�
//

#pragma once
#include "BaseDialog.h"
#include "GdiPlusImage.h"

//��ƪ����ʹ�õ�SkinUI�⣬�뵽��http://www.gymsaga.com���ڶ��� ��QQʵ���н��� ����Դ��

// CImageHandleDlg �Ի���
class CImageHandleDlg : public CBaseDialog
{
protected:
	CSkinButton						m_btOpen;				//�򿪰�ť
	CSkinButton						m_btSave;				//���水ť
	CSkinButton						m_btLeft;				//������ť
	CSkinButton						m_btRight;				//������ť
	CSkinButton						m_btSize;				//��С��ť
	CSkinButton						m_btLarge;				//�Ŵ�ť
	CSkinButton						m_btShrink;				//��С��ť
	CSkinSliderCtrl					m_scAlpha;
	CGdiPlusImage					m_Image;

	CPoint							m_ptPos;

	int								m_nAngle;
	float							m_fScale;

// ����
public:
	CImageHandleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IMAGEHANDLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual void DrawView(CDC*pDC,int nWidth,int nHeight);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickSize();
	afx_msg void OnBnClickLarge();
	afx_msg void OnBnClickShrink();
	afx_msg void OnBnClickOpen();
	afx_msg void OnBnClickSave();
	afx_msg void OnBnClickLeft();
	afx_msg void OnBnClickRight();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

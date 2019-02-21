#pragma once


// CDialogEx �Ի���
#include "ImageEx.h"
#include "ButtonEx.h"

class CDialogEx : public CDialog
{
	DECLARE_DYNAMIC(CDialogEx)
	
	//������Դ
protected:
	CImageEx 					m_ImageBack;		//����ͼƬ

	//�ؼ�����
protected:
	CButtonEx					m_btClose;			//�رհ�ť
	CButtonEx					m_btMax;			//��󻯰�ť
	CButtonEx					m_btMin;			//��С����ť

	//��������
protected:
	bool						m_bIsInit;			//�Ƿ��Ѿ���ʼ��
	bool						m_bIsZoomed;		//�Ƿ����
	bool						m_bExtrude;			//�Ƿ��������

public:
	CDialogEx(UINT nIDTemplate,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogEx();

protected:
	//DDX/DDV ֧��
	virtual void DoDataExchange(CDataExchange* pDX);    
	//��ʼ��
	virtual BOOL OnInitDialog();
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//��Ϣ����
protected:
	//������Ϣ
	afx_msg void OnPaint();
	//���ڴ�С
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��갴��
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//��갴��
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	//��������
public:
	//����ͼƬ
	bool LoadBackSkin(LPCTSTR pszResourcePath);
	//����ͼƬ
	bool LoadBackSkin(HINSTANCE hInstance, LPCTSTR pszResourceName);
	//�Ƴ��߿�
	void RemoveBorder();
	//��������
	inline void SetExtrude(bool bExtrude){ m_bExtrude = bExtrude;}

	//��������
public:
	//���
	virtual	bool OnMaxSize(){ return false; }
	//�ͻ���
	virtual void OnClientDraw(CDC*pDC,INT nWidth,INT nHeight){}

	DECLARE_MESSAGE_MAP()
};

#pragma once


// CSkinProgressCtrl
#include "SkinUI.h"
#include "ISkinControl.h"

class SKINUI_CLASS CSkinProgressCtrl : public CProgressCtrl,public ISkinControl
{
	DECLARE_DYNAMIC(CSkinProgressCtrl)

	//��Դ����
public:
	CImageEx * m_pBackImg, * m_pStepImg, * m_pFloatImg;

	//��������
protected:
	int						m_nFloatPos;			//������Դ����
	CSize					m_szFloatsize;			//������Դ��С

	//��������
public:
	//���캯��
	CSkinProgressCtrl();
	//��������
	virtual ~CSkinProgressCtrl();

	//���غ���
protected:
	//��������
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	//�����ؼ�
	virtual BOOL CreateControl(CWnd* pParentWnd);

	//��Դ����
public:
	//������Դ
	BOOL SetBackImage(LPCTSTR lpszFileName,bool bFixed = true);
	//������Դ
	BOOL SetStepImage(LPCTSTR lpszFileName);
	//������Դ
	BOOL SetFloatImage(LPCTSTR lpszFileName,int nTime=100);

	//��Ϣӳ��
public:
	//������Ϣ
	afx_msg void OnPaint();
	//���Ʊ���
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//������Ϣ
	afx_msg void OnDestroy();
	//ʱ����Ϣ
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//�ǿͻ���
	afx_msg void OnNcPaint();

protected:
	DECLARE_MESSAGE_MAP()
};



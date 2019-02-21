#pragma once


// CSkinSliderCtrl
#include "SkinUI.h"

class SKINUI_CLASS CSkinSliderCtrl : public CSliderCtrl,public ISkinControl
{
	DECLARE_DYNAMIC(CSkinSliderCtrl)
	
	//��Դ����
public:
	CImageEx * m_pBackImg, * m_pThumImg, * m_pDisImg, * m_pBtImg, * m_pTraceImg;

	//��������
protected:
	BOOL m_bPress, m_bHover, m_bMouseTracking;		//��ť״̬
	bool					m_bDragging;			//�Ϸű�ʶ
	CRect					m_rcThumRect;			//��������
	CRect					m_rcChannelRect;		//�켣����
	CSize					m_szThum;				//�����С

	//��������
public:
	//���캯��
	CSkinSliderCtrl();
	//��������
	virtual ~CSkinSliderCtrl();

public:
	//������Դ
	BOOL SetBackImage(LPCTSTR lpszFileName,bool bFixed = true);
	//������Դ
	BOOL SetThumImage(LPCTSTR lpszFileName);
	//������Դ
	BOOL SetDisImage(LPCTSTR lpszFileName);
	//������Դ
	BOOL SetButtonImage(LPCTSTR lpszFileName);
	//������Դ
	BOOL SetTraceImage(LPCTSTR lpszFileName,CONST LPRECT lprcNinePart=NULL);
	
	//���ܺ���
public:
	//����λ��
	void SetThumbRect(int nPos=0);
	//���ù켣
	void SetChannelRect();
	//����λ��
	void SetPos(int nPos);

	//��Ϣӳ��
public:
	//����뿪
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//������Ϣ
	afx_msg void OnPaint();
	//��������
	afx_msg void OnDestroy();
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//�������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//���̧��
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//�����ػ�
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()
};



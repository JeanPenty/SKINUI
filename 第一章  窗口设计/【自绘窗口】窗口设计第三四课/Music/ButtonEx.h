#pragma once


// CButtonEx
#include "ImageEx.h"

class CButtonEx : public CButton
{
	DECLARE_DYNAMIC(CButtonEx)
	
	//��������
protected:
	bool								m_bExpand;						//�Ƿ�����
	bool								m_bHovering;					//������־
	COLORREF							m_crTextColor;					//������ɫ
	CImageEx							m_ImageBack;					//��ťλͼ

	//��������
public:
	//���캯��
	CButtonEx();
	//��������
	virtual ~CButtonEx();

	//���غ���
protected:
	//�ؼ����໯
	virtual void PreSubclassWindow();
	//����滭����
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//���ú���
public:
	//����λ��
	bool FixButtonSize();
	//������ɫ
	bool SetTextColor(COLORREF crTextColor);
	//����λͼ
	bool SetButtonImage(LPCTSTR pszFileName, bool bExpandImage=false);
	//����λͼ
	bool SetButtonImage(HINSTANCE hInstance,LPCTSTR pszResourceName, bool bExpandImage=false);

	//��Ϣ����
protected:
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//����뿪
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//�ػ汳��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()
};



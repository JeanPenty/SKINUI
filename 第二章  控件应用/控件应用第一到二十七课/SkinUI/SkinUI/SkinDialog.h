#pragma once


#include "SkinUI.h"

class SKINUI_CLASS CSkinDialog : public CDialog,public ISkinControl
{
	DECLARE_DYNAMIC(CSkinDialog)

protected:
	ISkinControl				m_SkinControl;
	HDC							m_hMemDC;
	HBITMAP						m_hMemBmp, m_hOldBmp;
	bool						m_bExtrude;				//�Ƿ��������

public:
	CSkinDialog(UINT nIDTemplate,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSkinDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	//�ӿں���
protected:
	//�Ƴ��߿�
	void RemoveBorder();
	//��ʼ��
	virtual BOOL OnInitDialog();
	//���ڻ���
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight){}
	//
	void SetExtrude(bool bExtrude);

	//���ܺ���
public:
	//��ȡ����
	HDC GetBackDC(){ return m_hMemDC; }

	//��Ϣ����
private:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�����Ϣ
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//��갴��
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	DECLARE_MESSAGE_MAP()
};

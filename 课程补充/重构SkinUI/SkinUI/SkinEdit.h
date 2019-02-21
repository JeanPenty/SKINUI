#pragma once

#include "SkinUI.h"
#include "ISkinControl.h"

class SKINUI_CLASS CSkinEdit : public CEdit,public ISkinControl
{
	DECLARE_DYNAMIC(CSkinEdit)
	
	//��Դ����
protected:
	CImageEx 						* m_pBackImgN;			//������Դ
	CImageEx 						* m_pBackImgH;			//������Դ
	CImageEx 						* m_pIconImg;			//ͼ����Դ

	BOOL m_bFocus, m_bPress, m_bHover, m_bMouseTracking;	//״̬����
	int								m_nIconWidth;			//ͼ����
	bool							m_bHandCursor;			//�������
	CString							m_strDefText;			//Ĭ���ı�
	BOOL							m_bIsDefText;			//Ĭ��״̬
	TCHAR							m_cPwdChar;				//�����ַ�
	CPoint							m_ptClient;				//�ͻ���
							
public:
	CSkinEdit();
	virtual ~CSkinEdit();

	//��Դ����
public:
	//��������
	BOOL SetBackNormalImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	//��������
	BOOL SetBackHotImage(LPCTSTR lpszFileName,CONST LPRECT lpNinePart = NULL);
	//ͼ����Դ
	BOOL SetIconImage(LPCTSTR lpszFileName,bool bHandCursor = false);

	//���ú���
public:
	//Ĭ���ı�
	void SetDefaultText(LPCTSTR lpszText);
	//Ĭ��ģʽ
	void SetDefaultTextMode(BOOL bIsDefText);
	//ͼ��λ��
	void GetIconRect( RECT &lprcIcon );
	//�ͻ�����ʼ����
	void SetClientPoint(CPoint pt);

	//���غ���
public:
	//��������
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//��������
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	//��������
	virtual void ParseItem(CXmlNode *root);
	//�����ؼ�
	virtual BOOL CreateControl(CWnd* pParentWnd);

	//��Ϣӳ��
public:
	//�����С
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	//�ػ�ǿͻ���
	afx_msg void OnNcPaint();
	//�ػ汳��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//�������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//���̧��
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//����뿪
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//�ؼ�����
	afx_msg void OnDestroy();
	//��ȡ����
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//ʧȥ����
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//�����ʽ
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//��ɫ��ӳ��
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	//�������
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//�ǿͻ������̧��
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
};



//////////////////////////////////////////////////////////////////////////
class SKINUI_CLASS CMultiSkinEdit : public CSkinEdit 
{
	DECLARE_DYNAMIC(CMultiSkinEdit)

public:
	CMultiSkinEdit(){}
	virtual ~CMultiSkinEdit(){}

	//���غ���
public:
	//�����ؼ�
	virtual BOOL CreateControl(CWnd* pParentWnd);

protected:
	DECLARE_MESSAGE_MAP()
};
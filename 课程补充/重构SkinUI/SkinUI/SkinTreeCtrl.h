#pragma once

#include "SkinUI.h"
#include "ISkinControl.h"
// CSkinTreeCtrl
struct  tagItemInfo 
{
	HTREEITEM		hTreeItem;
	CImageEx		*pImage;
};

typedef map<HTREEITEM,tagItemInfo>	CMapItemInfo;

//////////////////////////////////////////////////////////////////////////

class SKINUI_CLASS CSkinTreeCtrl : public CTreeCtrl,public ISkinControl
{
	DECLARE_DYNAMIC(CSkinTreeCtrl)
	
	//��Դ����
protected:
	CImageEx						*m_pImageButton;					//��ť��Դ
	CImageEx						*m_pHovenImg, *m_pPressImg;			//�ڵ���Դ

	//��������
protected:
	HTREEITEM						m_hItemMouseHover;					//��������
	UINT							m_uCursorRes;						//�����Դ
	CMapItemInfo					m_MapItemInfo;						//��Դ����

	//�ڵ����ɫ
public:
	COLORREF						m_colHoven,m_colPress;				//�ڵ���ɫ

public:
	CSkinTreeCtrl();
	virtual ~CSkinTreeCtrl();

public:
	//��������
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	//�����ؼ�
	virtual BOOL CreateControl(CWnd* pParentWnd);
	//��������
	virtual void ParseItem(CXmlNode *root);

public:
	//������Դ
	BOOL SetButtonImage(LPCTSTR lpszFileName);
	//������Դ
	BOOL SetHovenImage(LPCTSTR lpszFileName,CONST LPRECT lprcNinePart=NULL);
	//������Դ
	BOOL SetPressImage(LPCTSTR lpszFileName,CONST LPRECT lprcNinePart=NULL);
	//����ͼ��
	BOOL InsertImage(HTREEITEM hTreeItem,LPCTSTR lpszFileName);
	//�������
	void SetCursorStyle(UINT uID);

	//�滭����
private:
	//�滭����
	VOID DrawTreeItem(CDC * pDC, CRect & rcClient, CRect & rcClipBox);
	//����ͼ��
	VOID DrawListImage(CDC * pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected);
	//�����ı�
	VOID DrawItemString(CDC * pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected);

	//��Ϣ����
public:
	//������Ϣ
	afx_msg void OnPaint();
	//�������
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//������Ϣ
	afx_msg void OnDestroy();

protected:
	DECLARE_MESSAGE_MAP()
};



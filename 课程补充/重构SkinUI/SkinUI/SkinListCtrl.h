#ifndef SKIN_LISTCTRL_HEAD_FILE
#define SKIN_LISTCTRL_HEAD_FILE

#pragma once

#include "SkinUI.h"
#include "ISkinControl.h"

//////////////////////////////////////////////////////////////////////////////////

//����λ��
#define SORT_AFTER					1									//����λ��
#define SORT_FRONT					-1									//ǰ��λ��

//////////////////////////////////////////////////////////////////////////////////
//ö�ٶ���

//��������
enum enSortType
{
	SortType_NoSort,				//û������
	SortType_Ascend,				//��������
	SortType_Descale,				//��������
};

//////////////////////////////////////////////////////////////////////////////////

//��ͷ�ؼ�
class SKINUI_CLASS CSkinHeaderCtrl : public CHeaderCtrl,public ISkinControl
{
	//�����б�
protected:
	UINT							m_uLockCount;						//������Ŀ
	UINT							m_uItemHeight;						//����߶�
	UINT							m_uActiveItem;						//
	bool							m_bPress;

	//��Դ����
public:
	CImageEx * m_pBackImg, * m_pPressImg, *m_pGridImg;

	//��������
public:
	//���캯��
	CSkinHeaderCtrl();
	//��������
	virtual ~CSkinHeaderCtrl();

	//��Դ����
public:
	//������Դ
	BOOL SetBackImage(LPCTSTR lpNormal,CONST LPRECT lprcNinePart=NULL);
	//������Դ
	BOOL SetPressImage(LPCTSTR lpNormal,CONST LPRECT lprcNinePart=NULL);
	//������Դ
	BOOL SetGridImage(LPCTSTR lpNormal);

	//���غ���
public:
	//�ؼ���
	virtual VOID PreSubclassWindow();
	//�ؼ���Ϣ
	virtual BOOL OnChildNotify(UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT * pLResult);

	//���ܺ���
public:
	//��������
	VOID SetLockCount(UINT uLockCount);
	//�����и�
	VOID SetItemHeight(UINT uItemHeight);

	//��Ϣ����
protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//������Ϣ
	afx_msg void OnDestroy();
	//�������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//���̧��
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////
struct  tagItemImage 
{
	CImageEx		*pImage;
	int				nItem;
};

typedef vector<tagItemImage>	CItemImgArray;

//////////////////////////////////////////////////////////////////////////

//�б�ؼ�
class SKINUI_CLASS CSkinListCtrl : public CListCtrl,public ISkinControl
{
	//���ݱ���
protected:
	bool							m_bAscendSort;						//�����־
	int								m_nHeightItem;
	UINT							m_uActiveItem;
	CItemImgArray					m_ItemImgArray;

	//��Դ����
public:
	CImageEx * m_pHovenImg, * m_pSelectImg;
	CImageEx * m_pCheckImg, * m_pUnCheckImg;

	//��������
public:
	CSkinHeaderCtrl					m_SkinHeaderCtrl;					//��ͷ�ؼ�

	//��������
public:
	//���캯��
	CSkinListCtrl();
	//��������
	virtual ~CSkinListCtrl();

	//���غ���
public:
	//�ؼ���
	virtual VOID PreSubclassWindow();
	//�滭����
	virtual VOID DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//��������
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	//��������
	virtual void ParseItem(CXmlNode *root);
	//�����ؼ�
	virtual BOOL CreateControl(CWnd* pParentWnd);

	//Report������Դ
public:
	//������Դ
	BOOL SetHovenImage(LPCTSTR lpszFileName,CONST LPRECT lprcNinePart=NULL);
	//������Դ
	BOOL SetSelectImage(LPCTSTR lpszFileName,CONST LPRECT lprcNinePart=NULL);
	//������Դ
	BOOL SetCheckImage(LPCTSTR lpszCheckName,LPCTSTR lpszUnCheckName);
	//����ͼ��
	BOOL InsertImage(int nItem,LPCTSTR lpszFileName);

	//α���غ���
public:
	//����ڵ�
	int InsertItem(const LVITEM* pItem);
	//����ڵ�
	int InsertItem(int nItem, LPCTSTR lpszItem);
	//����ڵ�
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	//����ڵ�
	int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,UINT nStateMask, int nImage, LPARAM lParam);
	//���÷��
	DWORD SetExtendedStyle(DWORD dwNewStyle);

	//�滭����
protected:
	//�滭����
	VOID DrawReportItem(CDC * pDC, INT nItem, CRect & rcSubItem, INT nColumnIndex);

	//��������
public:
	//�߶�����
	void SetItemHeight(int nHeight);

	//��Ϣ����
protected:
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//������Ϣ
	afx_msg void OnDestroy();
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//�ػ汳��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//�������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif
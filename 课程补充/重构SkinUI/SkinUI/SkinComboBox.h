#ifndef COMBOX_HEAD_FILE
#define COMBOX_HEAD_FILE

#pragma once

#include "SkinUI.h"
#include "ISkinControl.h"

#define		WM_CBO_EDIT_MOUSE_HOVER		WM_USER + 1
#define		WM_CBO_EDIT_MOUSE_LEAVE		WM_USER + 2
#define		WM_CBO_LIST_HIDE			WM_USER + 3
#define		WM_CBO_LIST_RBUTTONUP		WM_USER + 4
#define		WM_CBO_RBUTTONUP			WM_USER + 5
//////////////////////////////////////////////////////////////////////////

class SKINUI_CLASS CSkinComboBox_Edit :public CEdit,public ISkinControl
{
	//��������
protected:
	HWND			m_hOwnerWnd;			//��Ͽ���
	BOOL			m_bMouseTracking;		//����¼�
	BOOL			m_bIsDefText;			//Ĭ���ı�
	CString			m_strDefText;			//�ı�����

	//��������
public:
	//���캯��
	CSkinComboBox_Edit(void);
	//��������
	~CSkinComboBox_Edit(void);

	//���غ���
protected:
	//��Ϣѭ��
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//���ú���
public:
	//���þ��
	void SetOwnerWnd(HWND hWnd);
	//Ĭ���ı�
	void SetDefaultText(LPCTSTR lpszText);
	//Ĭ���ı�
	BOOL IsDefaultText();
	//�ı���ʽ
	void SetDefaultTextMode(BOOL bIsDefText);
	
	//��Ϣ����
public:
	//�ػ汳��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//����ƿ�
	afx_msg void OnMouseLeave();
	//���ý���
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//���ٽ���
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//��ɫ����
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	//�������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//���˫��
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//�����ʽ
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

class SKINUI_CLASS CSkinComboBox_ListBox : public CListBox,public ISkinControl
{
	//��������
protected:
	HWND							m_hOwnerWnd;			//��Ͽ���
	
	//��Դ����
public:
	CImageEx 						* m_pBackImgN;			//������Դ
	CImageEx 						* m_pSelectImg;			//ѡ����Դ

	//��������
public:
	//���캯��
	CSkinComboBox_ListBox(void);
	//��������
	~CSkinComboBox_ListBox(void);

	//���ú���
public:
	//���þ��
	void SetOwnerWnd(HWND hWnd);
	//�滭�߿�
	void DrawListFrame();

	//��Դ����
public:
	//��������
	BOOL SetBackNormalImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	//ѡ����Դ
	BOOL SetSelectImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);

	//��Ϣ����
private:
	//��ʾ����
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//��������
	afx_msg void OnDestroy();
	
	//���غ���
protected:
	//�ؼ��ػ�
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////

class SKINUI_CLASS CSkinComboBox : public CComboBox,public ISkinControl
{
	DECLARE_DYNAMIC(CSkinComboBox)

	//��Դ����
protected:
	CImageEx 							* m_lpBgImgN;		//Edit����
	CImageEx 							* m_lpBgImgH;		//Edit����
	CImageEx 							* m_lpArrowImgN;	//��ť����
	CImageEx 							* m_lpArrowImgH;	//��ť����
	CImageEx 							* m_lpArrowImgP;	//��ť����

	//״̬����
protected:
	BOOL m_bFocus, m_bPress, m_bHover, m_bMouseTracking;	//���״̬
	BOOL m_bArrowPress, m_bArrowHover;						//��ť״̬
	int									m_nArrowWidth;		//��ť���
	CRect								m_rcArrow;			//��ť����
	UINT								m_cyItemHeight;
	int									m_nEditHeight;

	//�ؼ�����
protected:
	CSkinComboBox_Edit					m_SkinComboBoxEdit;	//Edit�ؼ�
	CSkinComboBox_ListBox				m_SkinComboBoxList;	//ListBox�ؼ�

	//��������
public:
	//���캯��
	CSkinComboBox();
	//��������
	virtual ~CSkinComboBox();

	//��Դ����
public:
	//Edit����
	BOOL SetBgNormalPic(LPCTSTR lpszFileName, RECT * lpNinePart = NULL);
	//Edit����
	BOOL SetBgHotPic(LPCTSTR lpszFileName, RECT * lpNinePart = NULL);
	//��ť����
	BOOL SetArrowNormalPic(LPCTSTR lpszFileName);
	//��ť����
	BOOL SetArrowHotPic(LPCTSTR lpszFileName);
	//��ť����
	BOOL SetArrowPushedPic(LPCTSTR lpszFileName);
	//������Դ
	BOOL SetScrollImage(LPCTSTR pszFileName);

	//���ú���
public:
	//�����ı�
	void SetDefaultText(LPCTSTR lpszText);
	//Ĭ���ı�
	BOOL IsDefaultText();
	//��ť���
	void SetArrowWidth(int nWidth);
	//��ť���
	bool VerdictOverButton(CPoint MousePoint);
	//����DropList
	void SetDropList();
	//�ı���ɫ
	void SetEditTextColor(COLORREF col);
	//���ø߶�
	void SetAllItemHeight(UINT cyItemHeight);
	//���ø߶�
	void SetEditItemHeight(UINT cyItemHeight){ m_nEditHeight = cyItemHeight; }
	//
	int GetEditItemHeight(){ return m_nEditHeight; }

	//�ؼ����
public:
	//Edit���
	CSkinComboBox_Edit *GetEditWnd();
	//ListBox���
	CSkinComboBox_ListBox *GetListBoxWnd();

	//���غ���
protected:
	//���໯
	virtual void PreSubclassWindow();
	
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	//��������
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	//��������
	virtual void ParseItem(CXmlNode *root);
	//�����ؼ�
	virtual BOOL CreateControl(CWnd* pParentWnd);

	//��Ϣѭ��
public:
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�ػ汳��
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//���Ʊ���
	afx_msg void OnPaint();
	//�������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//����ƿ�
	afx_msg void OnMouseLeave();
	//��������
	afx_msg void OnDestroy();
	//���ڳߴ�
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//ListBox��Ϣ
	afx_msg LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);

	//�Զ�����Ϣ
public:
	//Edit����
	LRESULT OnEditMouseHover(WPARAM wParam, LPARAM lParam);
	//Edit�ƿ�
	LRESULT OnEditMouseLeave(WPARAM wParam, LPARAM lParam);
	//Edit�ƿ�
	LRESULT OnRButtonUp(WPARAM wParam, LPARAM lParam);
	//ListBox����
	LRESULT OnListHide(WPARAM wParam, LPARAM lParam);	

protected:	
	DECLARE_MESSAGE_MAP()
};

#endif

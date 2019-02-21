#pragma once


#include "SkinUI.h"
#include "ISkinControl.h"


class SKINUI_CLASS CSkinDialog : public CDialog,public ISkinControl,public CBuildDialog
{
	DECLARE_DYNAMIC(CSkinDialog)

protected:
	ISkinControl				m_SkinControl;
	HDC							m_hMemDC;
	HBITMAP						m_hMemBmp, m_hOldBmp;
	CRect						m_rcWindowSizeNow;

public:
	CSkinDialog(UINT nIDTemplate,LPCTSTR lpszFileName=NULL,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSkinDialog();

	//�ӿں���
protected:
	//��ʼ��
	virtual BOOL OnInitDialog();
	//��Ϣѭ��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//���ڻ���
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight){}
	// DDX/DDV ֧��
	virtual void DoDataExchange(CDataExchange* pDX);    

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
	//��������
	void SetExtrude(bool bExtrude);
	//��󻯴���
	void SetMaxWindow();

	//���ܺ���
public:
	//��ȡ����
	HDC GetBackDC(){ return m_hMemDC; }
	//�����Ӵ���
	void SetClipChild(bool bClip);

	//��Ϣ����
public:
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�����Ϣ
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//���ڳߴ�
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//���ڴ�С
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	//ˢ�±���
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//�ü��߿�
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	//�ǿͻ�������
	afx_msg BOOL OnNcActivate(BOOL bActive);
	//ϵͳ��Ϣ
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	//��̬����
protected:
	//ö�ٺ���
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

protected:
	//�����ؼ�
	void RectifyControl( int cx, int cy );

	DECLARE_MESSAGE_MAP()
};

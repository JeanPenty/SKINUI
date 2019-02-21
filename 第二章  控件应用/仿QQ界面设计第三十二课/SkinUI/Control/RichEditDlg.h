#pragma once

#include "DlgControlItem.h"
// CRichEditDlg �Ի���

class CRichEditDlg : public CDlgControlItem
{
	DECLARE_DYNAMIC(CRichEditDlg)
protected:
	CRichEditCtrl							m_RichEditCtrl;
	CSkinRichEdit							m_SkinRichEdit;
	CHARFORMAT2								m_cf2;

public:
	CRichEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRichEditDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	//���ػص�
	static DWORD CALLBACK LoadCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);
	//����ص�
	static DWORD CALLBACK SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnRClicked();
	void InsertTips();

	void OnURLClick(NMHDR *pNmhdr, LRESULT *pResult);
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton7();

	//�˵�����
protected:
	//ɾ����Ϣ
	VOID OnClearAll();
	//ȫ��ѡ��
	VOID OnSelectAll();
	//�����ַ�
	VOID OnCopyString();
};

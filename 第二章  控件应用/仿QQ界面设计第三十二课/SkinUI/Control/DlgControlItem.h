#pragma once

#include "stdafx.h"
// CDlgControlItem �Ի���
//�ڵ㴰�ڵĻ��࣬���ٴ�������

class CDlgControlItem : public CSkinDialog
{
	DECLARE_DYNAMIC(CDlgControlItem)

public:
	CDlgControlItem(UINT nIDTemplate,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgControlItem();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	//���ܺ���
public:
	//��ʾ�ؼ�
	bool ShowControlItem(const CRect & rcRect, CWnd * pParentWnd,LPCTSTR lpWindowText);

	DECLARE_MESSAGE_MAP()
};

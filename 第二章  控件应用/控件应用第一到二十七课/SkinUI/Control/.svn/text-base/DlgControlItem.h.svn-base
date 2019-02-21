#pragma once

#include "stdafx.h"
// CDlgControlItem 对话框
//节点窗口的基类，快速创建窗口

class CDlgControlItem : public CSkinDialog
{
	DECLARE_DYNAMIC(CDlgControlItem)

public:
	CDlgControlItem(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgControlItem();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	//功能函数
public:
	//显示控件
	bool ShowControlItem(const CRect & rcRect, CWnd * pParentWnd,LPCTSTR lpWindowText);

	DECLARE_MESSAGE_MAP()
};

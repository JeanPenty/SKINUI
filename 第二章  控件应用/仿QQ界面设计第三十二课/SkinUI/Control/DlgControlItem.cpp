// DlgControlItem.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DlgControlItem.h"

// CDlgControlItem 对话框

IMPLEMENT_DYNAMIC(CDlgControlItem, CSkinDialog)

CDlgControlItem::CDlgControlItem(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CSkinDialog(nIDTemplate, pParent)
{
}

CDlgControlItem::~CDlgControlItem()
{
}

void CDlgControlItem::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgControlItem, CSkinDialog)
END_MESSAGE_MAP()

//显示控件
bool CDlgControlItem::ShowControlItem( const CRect & rcRect, CWnd * pParentWnd,LPCTSTR lpWindowText )
{
	//创建窗口
	if (m_hWnd==NULL) 
	{
		//设置资源
		AfxSetResourceHandle(AfxGetInstanceHandle());

		//创建窗口
		Create(m_lpszTemplateName,pParentWnd);
		SetWindowPos(NULL,rcRect.left,rcRect.top,rcRect.Width(),rcRect.Height(),SWP_NOZORDER|SWP_NOACTIVATE);

		//创建静态控件
 		CreateWindow(TEXT("STATIC"),lpWindowText,WS_CHILD|WS_VISIBLE|SS_CENTER,0,5,rcRect.Width(),20,	\
 			GetSafeHwnd(),/*(HMENU)(UINT_PTR)IDC_STATIC*/NULL,AfxGetInstanceHandle(),NULL);

		//设置资源
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}

	//显示窗口
	ShowWindow(SW_SHOW);

	return true;
}

// CDlgControlItem 消息处理程序
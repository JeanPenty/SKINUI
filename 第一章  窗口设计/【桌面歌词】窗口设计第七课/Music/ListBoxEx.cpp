// ListBoxEx.cpp : 实现文件
//

#include "stdafx.h"
#include "Music.h"
#include "ListBoxEx.h"


// CListBoxEx

IMPLEMENT_DYNAMIC(CListBoxEx, CListBox)

CListBoxEx::CListBoxEx()
{
	m_nItemHeight = 12;
}

CListBoxEx::~CListBoxEx()
{
}


BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
END_MESSAGE_MAP()


// CListBoxEx 消息处理程序

void CListBoxEx::SetItemHeight( int nItemHeight )
{
	m_nItemHeight = nItemHeight;
}

void CListBoxEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight=m_nItemHeight;
}

void CListBoxEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	bool bIsSel = lpDrawItemStruct->itemState & ODS_SELECTED;
	
	CRect rcItem = lpDrawItemStruct->rcItem;

	//绘制背景
	pDC->FillSolidRect(rcItem,bIsSel?RGB(236,227,215):RGB(255,255,255));

	CString  strItemText;
	GetText( lpDrawItemStruct->itemID, strItemText );

	pDC->SetTextColor(bIsSel?RGB(105,146,1):RGB(60,60,60));

	CFont font;
	font.CreateFont(18,0,0,0,FW_NORMAL,0,FALSE,0,0,0,0,0,0,TEXT("微软雅黑"));
	CFont*  pOldFont = pDC->SelectObject(&font);	
	pDC->DrawText(strItemText,&CRect(rcItem.left+10,rcItem.top+9,rcItem.right-10,rcItem.bottom),DT_LEFT|DT_VCENTER);
	pDC->SelectObject(pOldFont);
	
}

int CListBoxEx::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/)
{
	// TODO:  添加您的代码以确定指定项的排序顺序
	// 返回 -1 表示项 1 排在项 2 之前
	// 返回 0 表示项 1 和项 2 顺序相同
	// 返回 1 表示项 1 排在项 2 之后

	return 0;
}
// SkinListBox.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "SkinListBox.h"

// CSkinListBox

IMPLEMENT_DYNAMIC(CSkinListBox, CListBox)

BEGIN_MESSAGE_MAP(CSkinListBox, CListBox)
	ON_WM_DESTROY()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

CSkinListBox::CSkinListBox( void )
{
	m_pBackImgN = NULL;
	m_pSelectImg = NULL;
	m_pBackImgH = NULL;
	m_nHovenItem = 0;
	nItemHeight = 20;
	m_ItemStruct.clear();
	m_bMouseTracking = false;
}

CSkinListBox::~CSkinListBox( void )
{

}

BOOL CSkinListBox::SetBackNormalImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgN);
	m_pBackImgN = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgN != NULL)
		m_pBackImgN->SetNinePart(lpNinePart);

	return (m_pBackImgN != NULL) ? TRUE : FALSE;
}

BOOL CSkinListBox::SetSelectImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pSelectImg);
	m_pSelectImg = RenderEngine->GetImage(lpszFileName);

	if (m_pSelectImg != NULL)
		m_pSelectImg->SetNinePart(lpNinePart);

	return (m_pSelectImg != NULL) ? TRUE : FALSE;
}

BOOL CSkinListBox::SetHovenImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgH);
	m_pBackImgH = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgH != NULL)
		m_pBackImgH->SetNinePart(lpNinePart);

	return (m_pBackImgH != NULL) ? TRUE : FALSE;
}

void CSkinListBox::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pSelectImg);

	RemoveScorll();
}

void CSkinListBox::OnNcPaint()
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

	CWindowDC dc(this);

	CMemoryDC MemDC(&dc,rcWindow);

	if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
		m_pBackImgN->Draw(&MemDC, rcWindow);
}

void CSkinListBox::OnRButtonUp(UINT nFlags, CPoint point)
{
	CRect rcItem(0,0,0,0);
	SetSel(-1,FALSE);

	for (int i =0; i<GetCount(); i++)
	{
		GetItemRect(i, &rcItem);

		if(rcItem.PtInRect(point))
		{
			if( IsSingleSel() )
				SetCurSel(i);
			else 
				SetSel(i);

			break;
		}
	}

	CWnd *pWnd = GetParent();
	if ( (pWnd == NULL) && (pWnd->GetSafeHwnd() != NULL) ) return;
	pWnd->PostMessage(WM_COMMAND,GetDlgCtrlID(),0);

	Invalidate(FALSE);

	__super::OnRButtonUp(nFlags, point);
}

void CSkinListBox::OnLButtonDown( UINT nFlags, CPoint point )
{
	Invalidate(FALSE);

	CListBox::OnLButtonDown(nFlags,point);
}


void CSkinListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseTracking)
	{
		TrackMouseLeave(GetSafeHwnd());

		m_bMouseTracking = TRUE;
		Invalidate(FALSE);
	}

	CRect rcItem(0,0,0,0);
	//保存旧状态，为了防止在同一个节点下因过多的刷新消耗cpu资源
	static int nOldIndex = -1;

	for (int i =0; i<GetCount(); i++)
	{
		GetItemRect(i, &rcItem);

		if(rcItem.PtInRect(point))
		{
			if( m_nHovenItem != i )  Invalidate(FALSE);

			m_nHovenItem = i;

			break;
		}
	}


	__super::OnMouseMove(nFlags, point);
}

void CSkinListBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	return;
	//没有节点就不用继续执行了
	if( GetCount()==0 ) return;

	//变量定义
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDCControl=CDC::FromHandle(lpDrawItemStruct->hDC);

 	//创建缓冲
 	CDC BufferDC;
 	CBitmap ImageBuffer;
 	BufferDC.CreateCompatibleDC(pDCControl);
 	ImageBuffer.CreateCompatibleBitmap(pDCControl,rcItem.Width(),rcItem.Height());
 
 	//设置环境
 	BufferDC.SelectObject(&ImageBuffer);
	BufferDC.SelectObject(GetCtrlFont());

	//获取字符
	CString strString;
	GetText(lpDrawItemStruct->itemID,strString);

	//计算位置
	CRect rcString;
	rcString.SetRect(4,0,rcItem.Width()-8,rcItem.Height());

	//颜色定义
	COLORREF crTextColor=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0)?m_colSelectText:m_colNormalText;

	//绘画背景
	BufferDC.FillSolidRect(0,0,rcItem.Width(),rcItem.Height(),m_colBack);

	//节点选中
	if ( (lpDrawItemStruct->itemState&ODS_SELECTED) != 0 )
	{
		if ( m_pSelectImg!= NULL && !m_pSelectImg->IsNull() )
		{
			m_pSelectImg->Draw(&BufferDC,CRect(0,0,rcItem.Width(),rcItem.Height()));
		}
	}

	//节点高亮
	else if ( m_nHovenItem == lpDrawItemStruct->itemID )
	{
		if ( m_pBackImgH!= NULL && !m_pBackImgH->IsNull() )
		{
			m_pBackImgH->Draw(&BufferDC,CRect(0,0,rcItem.Width(),rcItem.Height()));
		}
	}

	//绘画字符
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(crTextColor);
	BufferDC.DrawText(strString,&rcString,DT_VCENTER|DT_SINGLELINE);

	//绘画界面
	pDCControl->BitBlt(rcItem.left,rcItem.top,rcItem.Width(),rcItem.Height(),&BufferDC,0,0,SRCCOPY);

 	//清理资源
 	BufferDC.DeleteDC();
 	ImageBuffer.DeleteObject();
}

void CSkinListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	vector<tagItemStruct>::iterator iter = m_ItemStruct.begin();

	for (;iter != m_ItemStruct.end(); ++iter )
	{
		lpMeasureItemStruct->itemHeight = iter->itemHeight;
		lpMeasureItemStruct->itemWidth = iter->itemWidth;
	}
}

bool CSkinListBox::IsSingleSel()
{
	DWORD dwStyle = GetStyle();

	if ( ((dwStyle&LBS_EXTENDEDSEL)!=0) || ((dwStyle&LBS_MULTIPLESEL)!=0) )
	{
		return false;
	}

	return true;
}

void CSkinListBox::AddString(LPCTSTR lpszItem)
{
	InsertItem();

	__super::AddString(lpszItem);
}

int CSkinListBox::SetItemHeight( int nIndex, UINT cyItemHeight )
{
	if ( nIndex == -1 ) nItemHeight = cyItemHeight;
	
	vector<tagItemStruct>::iterator iter = m_ItemStruct.begin();

	for (;iter != m_ItemStruct.end(); ++iter )
	{
		if ( iter->itemID == nIndex )
		{
			iter->itemHeight = cyItemHeight;

			break;
		}
	}

	return __super::SetItemHeight(nIndex,cyItemHeight);
}

int CSkinListBox::DeleteString( UINT nIndex )
{
 	vector<tagItemStruct>::iterator iter = m_ItemStruct.begin();
 
 	for (;iter != m_ItemStruct.end(); ++iter )
 	{
 		if ( iter->itemID == nIndex )
 		{
 			m_ItemStruct.erase(iter);
			break;
 		}
 	}

	return CListBox::DeleteString(nIndex);
}

void CSkinListBox::InsertItem()
{
	tagItemStruct ItemStruct;
	ZeroMemory(&ItemStruct,sizeof ItemStruct);

	CRect rcClient;
	GetClientRect(&rcClient);

	ItemStruct.itemID = m_ItemStruct.size();
	ItemStruct.itemHeight = nItemHeight;
	ItemStruct.itemWidth = rcClient.Width();

	m_ItemStruct.push_back(ItemStruct);
}

void CSkinListBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC BufferDC(&dc,rcClient);

 	//创建缓冲
 	CImage ImageBuffer;
 	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);
 
 	//变量定义
 	CDC * pBufferDC=CDC::FromHandle(ImageBuffer.GetDC());

	//变量定义
	CRect rcItem;

	pBufferDC->SelectObject(GetCtrlFont());

	//绘画背景
	pBufferDC->FillSolidRect(0,0,rcClient.Width(),rcClient.Height(),m_colBack);
	DrawParentWndBg(GetSafeHwnd(),pBufferDC->GetSafeHdc());

	if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
		m_pBackImgN->Draw(pBufferDC, rcClient);

	for (int i=0;i<GetCount();i++)
	{	
		GetItemRect(i,&rcItem);

		//获取字符
		CString strString;
		GetText(i,strString);

		//计算位置
		CRect rcString;
		rcString.SetRect(rcItem.left+4,rcItem.top,rcItem.right-8,rcItem.bottom);

		bool bSelect = GetSel(i);

		//颜色定义
		COLORREF crTextColor=bSelect?m_colSelectText:m_colNormalText;

		//节点选中
		if ( bSelect )
		{
			if ( m_pSelectImg!= NULL && !m_pSelectImg->IsNull() )
			{
				m_pSelectImg->Draw(pBufferDC,CRect(rcItem.left,rcItem.top,rcItem.right,rcItem.bottom));
			}
		}

		//节点高亮
		else if ( m_nHovenItem == i )
		{
			if ( m_pBackImgH!= NULL && !m_pBackImgH->IsNull() )
			{
				m_pBackImgH->Draw(pBufferDC,CRect(rcItem.left,rcItem.top,rcItem.right,rcItem.bottom));
			}
		}

		//绘画字符
		pBufferDC->SetBkMode(TRANSPARENT);
		pBufferDC->SetTextColor(crTextColor);
		pBufferDC->DrawText(strString,&rcString,DT_VCENTER|DT_SINGLELINE);
	}

 	//绘画界面
 	BufferDC.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);
 
 	//清理资源
 	ImageBuffer.ReleaseDC();
}

LRESULT CSkinListBox::OnMouseLeave( WPARAM wparam, LPARAM lparam )
{
	m_bMouseTracking = FALSE;
	Invalidate(FALSE);

	return 0;
}

BOOL CSkinListBox::OnEraseBkgnd( CDC* pDC )
{
	return TRUE;
}


void CSkinListBox::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	Invalidate(FALSE);

	__super::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSkinListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	Invalidate(FALSE);

	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}

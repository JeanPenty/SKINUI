// MusicList.cpp : 实现文件
//

#include "stdafx.h"
#include "GMusic.h"
#include "MusicList.h"


// CMusicList

IMPLEMENT_DYNAMIC(CMusicList, CListBox)

CMusicList::CMusicList()
{
	m_nTop = 0;
	m_nPressItem = -1;
	m_SelItemArray.clear();
	m_bMouseTracking = false;
	m_pBackImgN = NULL;
	m_pSelectImg = NULL;
	m_pBackImgH = NULL;
	m_pPlayedImg = NULL;
	m_nHovenItem = 0;
	m_nPlayItem = -1;
}

CMusicList::~CMusicList()
{
}


BEGIN_MESSAGE_MAP(CMusicList, CListBox)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()



// CMusicList 消息处理程序

void CMusicList::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC BufferDC(&dc,rcClient);

	CheckScrollBarStatus();

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
		GetItemRect(i,rcItem);

		//获取字符
		CString strString;
		GetText(i,strString);

		//计算位置
		CRect rcString;
		rcString.SetRect(rcItem.left+4,rcItem.top,rcItem.right-15,rcItem.bottom);

		bool bSelect = false;//m_nPressItem;
		//
		if ( IsSingleSel() )
		{
			if( m_nPressItem == i ) bSelect = true;
		}
		else
		{
			if( GetSel(i) > 0 ) bSelect = true;
		}

		//颜色定义
		COLORREF crTextColor=bSelect?m_colSelectText:m_colNormalText;

		if ( m_nPlayItem == i && !bSelect )
		{
			m_pPlayedImg->Draw(pBufferDC,CRect(rcItem.left,rcItem.top,rcItem.right,rcItem.bottom));
		}

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

		tagMusicInfo *pMusicInfo = (tagMusicInfo *)GetItemDataPtr(i);
		if ( pMusicInfo == NULL )
			pBufferDC->DrawText(strString,&rcString,DT_VCENTER|DT_SINGLELINE);
		else
		{
			pBufferDC->DrawText(pMusicInfo->szTitle,&rcString,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
			pBufferDC->DrawText(pMusicInfo->szArtist,&rcString,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		}
	}

	m_VScrollBar.OnPaint(pBufferDC);

	//绘画界面
	BufferDC.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	//清理资源
	ImageBuffer.ReleaseDC();
}

int CMusicList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rc = CRect(rcClient.Width()-8, 0, rcClient.Width(), rcClient.Height());
	m_VScrollBar.Create(m_hWnd, 1, &rc, 1, FALSE, FALSE);

	m_VScrollBar.SetBgNormalPic(_T("Res\\ScrollBar\\scrollbar_bkg.png"));
	m_VScrollBar.SetBgHotPic(_T("Res\\ScrollBar\\scrollbar_bkg.png"));
	m_VScrollBar.SetBgPushedPic(_T("Res\\ScrollBar\\scrollbar_bkg.png"));
	m_VScrollBar.SetBgDisabledPic(_T("Res\\ScrollBar\\scrollbar_bkg.png"));

	m_VScrollBar.SetShowLeftUpBtn(TRUE);
	m_VScrollBar.SetLeftUpBtnNormalPic(_T("Res\\ScrollBar\\scrollbar_arrowup_normal.png"));
	m_VScrollBar.SetLeftUpBtnHotPic(_T("Res\\ScrollBar\\scrollbar_arrowup_highlight.png"));
	m_VScrollBar.SetLeftUpBtnPushedPic(_T("Res\\ScrollBar\\scrollbar_arrowup_down.png"));
	m_VScrollBar.SetLeftUpBtnDisabledPic(_T("Res\\ScrollBar\\scrollbar_arrowup_normal.png"));

	m_VScrollBar.SetShowRightDownBtn(TRUE);
	m_VScrollBar.SetRightDownBtnNormalPic(_T("Res\\ScrollBar\\scrollbar_arrowdown_normal.png"));
	m_VScrollBar.SetRightDownBtnHotPic(_T("Res\\ScrollBar\\scrollbar_arrowdown_highlight.png"));
	m_VScrollBar.SetRightDownBtnPushedPic(_T("Res\\ScrollBar\\scrollbar_arrowdown_down.png"));
	m_VScrollBar.SetRightDownBtnDisabledPic(_T("Res\\ScrollBar\\scrollbar_arrowdown_normal.png"));

	m_VScrollBar.SetThumbNormalPic(_T("Res\\ScrollBar\\scrollbar_bar_normal.png"), CRect(4,4,4,4));
	m_VScrollBar.SetThumbHotPic(_T("Res\\ScrollBar\\scrollbar_bar_highlight.png"), CRect(4,4,4,4));
	m_VScrollBar.SetThumbPushedPic(_T("Res\\ScrollBar\\scrollbar_bar_down.png"), CRect(4,4,4,4));
	m_VScrollBar.SetThumbDisabledPic(_T("Res\\ScrollBar\\scrollbar_bar_normal.png"), CRect(4,4,4,4));

	return 0;
}

void CMusicList::AdjustScrollBarSize()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	if (rcClient.IsRectEmpty()) return;

	if (m_VScrollBar.IsVisible())
	{
		CRect rc = CRect(rcClient.Width()-8, 0, rcClient.Width(), rcClient.Height());
		m_VScrollBar.SetRect(&rc);
	}
}
void CMusicList::OnSize(UINT nType, int cx, int cy)
{
	CListBox::OnSize(nType, cx, cy);

	AdjustScrollBarSize();
}

LRESULT CMusicList::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if ( m_VScrollBar.WindowProc(message, wParam, lParam) ) return 0;

	return CListBox::WindowProc(message, wParam, lParam);
}

void CMusicList::CheckScrollBarStatus()
{
	if ( GetSafeHwnd() == NULL ) return;

	CRect rcItemPart;
	GetItemPartRect(rcItemPart);

	int cxDisplayView = rcItemPart.Width();
	int cyDisplayView = rcItemPart.Height();

	CRect rcItem;
	GetItemRect(0,rcItem);

	int cxContentView = rcItem.Width();		
	int cyContentView = GetContentViewHeight();

	CRect rcVScrollBar;
	m_VScrollBar.GetRect(&rcVScrollBar);
	int cxVScrollBar = rcVScrollBar.Width();

	BOOL bVisibleV = m_VScrollBar.IsVisible();
	BOOL bChange2;

	int nnn = 0;
	do 
	{
		nnn++;
		bChange2 = FALSE;

		if (cyContentView > cyDisplayView)
		{
			if (!bVisibleV)
			{
				bVisibleV = TRUE;
				bChange2 = TRUE;
				cxDisplayView -= cxVScrollBar;
			}
		}
		else
		{
			if (bVisibleV)
			{
				bVisibleV = FALSE;
				bChange2 = TRUE;
				cxDisplayView += cxVScrollBar;
			}
		}

		if (bChange2)
			continue;
	} while (0);

	if (cyContentView > cyDisplayView)
	{
		m_VScrollBar.SetScrollRange(cyContentView - cyDisplayView);
		Scroll(0, 0);
		m_VScrollBar.SetVisible(TRUE);
	}
	else
	{
		m_nTop = 0;
		m_VScrollBar.SetScrollPos(0);
		m_VScrollBar.SetVisible(FALSE);
	}

	AdjustScrollBarSize();
}

BOOL CMusicList::GetItemPartRect(CRect& rect)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	//if (m_VScrollBar.IsVisible())
	{
		m_VScrollBar.GetRect(&rect);
		rect.bottom = rcClient.bottom;
	}

	return TRUE;
}

void CMusicList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rcItemPart;
	GetItemPartRect(rcItemPart);
	//GetClientRect(&rcItemPart);

	int nLineSize = 30;
	int nPageSize = rcItemPart.Height();

	switch (nSBCode)
	{
	case SB_LINEUP:
		Scroll(0, -nLineSize);
		break;

	case SB_LINEDOWN:
		Scroll(0, nLineSize);
		break;

	case SB_PAGEUP:
		Scroll(0, -nPageSize);
		break;

	case SB_PAGEDOWN:
		Scroll(0, nPageSize);
		break;

	case SB_THUMBTRACK:
		Scroll(0, 0);
		break;

	default:
		return;
	}

	Invalidate(FALSE);

	CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMusicList::Scroll(int cx, int cy)
{
	if (m_VScrollBar.IsVisible() && m_VScrollBar.IsEnabled())
	{
		int nPos = m_VScrollBar.GetScrollPos();
		m_VScrollBar.SetScrollPos(nPos + cy);
		nPos = m_VScrollBar.GetScrollPos();
		m_nTop = 0 - nPos;
	}
}

BOOL CMusicList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (!m_VScrollBar.IsVisible()) return TRUE;

	int nLineSize = 30;

	if (zDelta < 0)		// SB_LINEDOWN
		Scroll(0, nLineSize);
	else	// SB_LINEUP
		Scroll(0, -nLineSize);

	Invalidate(FALSE);

	return CListBox::OnMouseWheel(nFlags, zDelta, pt);
}

int CMusicList::GetContentViewHeight()
{
 	int nHeight = 0;

	for (int i=0;i<GetCount();i++ )
	{
		nHeight += GetItemHeight(i);
	}

	return nHeight;
}

void CMusicList::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

 	CRect rcItemPart;

 	for (int i=0;i<GetCount();i++)
 	{
 		GetItemRect(i,rcItemPart);
 
 		if (rcItemPart.PtInRect(point))
 		{
			if ( IsSingleSel() )
			{
				SetCurSel(i);
			}
			else
			{
				if ( nFlags & MK_CONTROL )
				{
					SetSel(i,TRUE);
				}
				else if ( nFlags & MK_SHIFT )
				{
					//这里需要注意，默认情况下map容器会对元素进行排序
					CSelItemArray::iterator iter = m_SelItemArray.begin();
					int nStart = (iter == m_SelItemArray.end()) ? 0 : iter->first;

					iter = (--m_SelItemArray.end());
					int nEnd = (iter == m_SelItemArray.end()) ? 0 : iter->first;

					int nClickItem = i;
					
					m_SelItemArray.clear();

					if ( nClickItem >= nEnd )
					{
						for (int i=nStart;i<=nClickItem;i++)
						{
							SetSel(i,TRUE);
						}
					}
					else
					{
						for (int i=nClickItem;i<=nEnd;i++)
						{
							SetSel(i,TRUE);
						}
					}
				}
				else
				{
					m_SelItemArray.clear();

					SetSel(i,TRUE);
				}
			}

			Invalidate(FALSE);
 			break;
 		}
 	}

	//CListBox::OnLButtonDown(nFlags, point);
}

BOOL CMusicList::GetItemRect(int nIndex, CRect& rect)
{
// 	rect = CRect(0,0,0,0);
// 
 	if (nIndex < 0 || nIndex >= GetCount())
 		return FALSE;
// 
// 	CRect rcItemPart;
// 	GetItemPartRect(rcItemPart);
// 
// 	int nLeft = 0, nTop = m_nTop + rcItemPart.top;
// 
// 	int nItemHeight = GetItemHeight(nIndex);
// 
// 	CRect rcClient;
// 	GetClientRect(rcClient);
// 
// 	int nItemWidth = rcClient.Width();
// 	nTop = m_nTop + rcItemPart.top + nIndex*nItemHeight;
// 	rect = CRect(nLeft, nTop, nLeft+nItemWidth, nTop+nItemHeight);
	
	CListBox::GetItemRect(nIndex,&rect);

	rect.top += m_nTop;
	rect.bottom += m_nTop;

	return TRUE;
}

void CMusicList::OnMouseMove(UINT nFlags, CPoint point)
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
		GetItemRect(i, rcItem);

		if(rcItem.PtInRect(point))
		{
			if( m_nHovenItem != i )  Invalidate(FALSE);

			m_nHovenItem = i;

			break;
		}
	}

	CListBox::OnMouseMove(nFlags, point);
}

void CMusicList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	SetFocus();

	CRect rcItemPart;

	for (int i=0;i<GetCount();i++)
	{
		GetItemRect(i,rcItemPart);

		if (rcItemPart.PtInRect(point))
		{
			if ( IsSingleSel() )
			{
				SetCurSel(i);
			}
			else
			{
				m_SelItemArray.clear();
				SetSel(i);
			}

			//双击事件
			::SendMessage(::GetParent(m_hWnd),WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(),LBN_DBLCLK),(LPARAM)GetSafeHwnd());

			Invalidate(FALSE);
			break;
		}
	}

	CListBox::OnLButtonDblClk(nFlags, point);
}

int CMusicList::GetSel( int nIndex ) const
{
	CSelItemArray::const_iterator iter = m_SelItemArray.find(nIndex);

	if ( iter == m_SelItemArray.end() ) return -1;
	
	return iter->second ? 1 : -1;
}

int CMusicList::SetSel( int nIndex, BOOL bSelect /*= TRUE*/ )
{
	m_SelItemArray.insert(pair<int,BOOL>(nIndex,bSelect));

	return LB_OKAY;
}

int CMusicList::SetCurSel( int nSelect )
{
	m_nPressItem = nSelect;

	return LB_OKAY;
}

int CMusicList::GetCurSel() const
{
	return m_nPressItem;

	return LB_OKAY;
}

int CMusicList::DeleteString( UINT nIndex )
{
	int nResult = CListBox::DeleteString(nIndex);

	Invalidate(FALSE);

	return nResult;
}

BOOL CMusicList::SetBackNormalImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgN);
	m_pBackImgN = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgN != NULL)
		m_pBackImgN->SetNinePart(lpNinePart);

	return (m_pBackImgN != NULL) ? TRUE : FALSE;
}

BOOL CMusicList::SetSelectImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pSelectImg);
	m_pSelectImg = RenderEngine->GetImage(lpszFileName);

	if (m_pSelectImg != NULL)
		m_pSelectImg->SetNinePart(lpNinePart);

	return (m_pSelectImg != NULL) ? TRUE : FALSE;
}


BOOL CMusicList::SetPlayedImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pPlayedImg);
	m_pPlayedImg = RenderEngine->GetImage(lpszFileName);

	if (m_pPlayedImg != NULL)
		m_pPlayedImg->SetNinePart(lpNinePart);

	return (m_pPlayedImg != NULL) ? TRUE : FALSE;
}


BOOL CMusicList::SetHovenImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgH);
	m_pBackImgH = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgH != NULL)
		m_pBackImgH->SetNinePart(lpNinePart);

	return (m_pBackImgH != NULL) ? TRUE : FALSE;
}

void CMusicList::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pSelectImg);
	RenderEngine->RemoveImage(m_pPlayedImg);

	m_VScrollBar.Destroy();
}

void CMusicList::OnRButtonUp( UINT nFlags, CPoint point )
{
	SetFocus();

	CRect rcItemPart;

	for (int i=0;i<GetCount();i++)
	{
		GetItemRect(i,rcItemPart);

		if (rcItemPart.PtInRect(point))
		{

			CWnd *pWnd = GetParent();
			if ( (pWnd == NULL) && (pWnd->GetSafeHwnd() != NULL) ) return;
			pWnd->PostMessage(WM_COMMAND,GetDlgCtrlID(),0);

			break;
		}
	}

	CListBox::OnRButtonUp(nFlags, point);
}

LRESULT CMusicList::OnMouseLeave( WPARAM wparam, LPARAM lparam )
{
	m_bMouseTracking = FALSE;
	Invalidate(FALSE);

	return 0;
}

BOOL CMusicList::OnEraseBkgnd( CDC* pDC )
{
	return TRUE;
}

bool CMusicList::IsSingleSel()
{
	DWORD dwStyle = GetStyle();

	if ( ((dwStyle&LBS_EXTENDEDSEL)!=0) || ((dwStyle&LBS_MULTIPLESEL)!=0) )
	{
		return false;
	}

	return true;
}

void CMusicList::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
	lpMeasureItemStruct->itemHeight = 30;
}

void CMusicList::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{

}

int CMusicList::AddString( LPCTSTR lpszItem )
{
	int nResult = CListBox::AddString(lpszItem);

	Invalidate(FALSE);
	
	//m_MusicInfoArray.insert();

	return nResult;
}

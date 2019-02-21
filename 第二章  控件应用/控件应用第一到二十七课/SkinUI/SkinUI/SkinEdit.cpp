// SkinEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "SkinEdit.h"


// CSkinEdit

IMPLEMENT_DYNAMIC(CSkinEdit, CEdit)

CSkinEdit::CSkinEdit()
{
	m_pBackImgN = NULL;
	m_pBackImgH = NULL;
	m_pIconImg = NULL;

	m_bFocus = m_bPress = m_bHover = m_bMouseTracking = FALSE;
	m_nIconWidth = 0;
	m_bHandCursor = false;

	m_bIsDefText = FALSE;
	m_cPwdChar = 0;
	m_ptClient.SetPoint(0,0);
}

CSkinEdit::~CSkinEdit()
{
}


BEGIN_MESSAGE_MAP(CSkinEdit, CEdit)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONUP()
END_MESSAGE_MAP()

BOOL CSkinEdit::SetBackNormalImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgN);
	m_pBackImgN = RenderEngine->GetImage(lpszFileName);
	
	if (m_pBackImgN != NULL)
		m_pBackImgN->SetNinePart(lpNinePart);

	return (m_pBackImgN != NULL) ? TRUE : FALSE;
}

BOOL CSkinEdit::SetBackHotImage( LPCTSTR lpszFileName,CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgH);
	m_pBackImgH = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgH != NULL)
		m_pBackImgH->SetNinePart(lpNinePart);

	return (m_pBackImgH != NULL) ? TRUE : FALSE;
}

BOOL CSkinEdit::SetIconImage( LPCTSTR lpszFileName,bool bHandCursor /*= false*/ )
{
	RenderEngine->RemoveImage(m_pIconImg);
	m_pIconImg = RenderEngine->GetImage(lpszFileName);

	if (m_pIconImg != NULL)
	{
		m_nIconWidth = m_pIconImg->GetWidth();
	
// 		CRect rcClient;
// 		GetClientRect(&rcClient);
// 		rcClient.right-=m_nIconWidth;
// 
// 		SetRect(&rcClient);

		//CRect rcWindow;
		//GetWindowRect(&rcWindow);
		//GetParent()->ScreenToClient(&rcWindow);
		//rcWindow.right+=1;
		//MoveWindow(rcWindow,TRUE);
	}

	m_bHandCursor = bHandCursor;

	return (m_pIconImg != NULL) ? TRUE : FALSE;
}

void CSkinEdit::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if (NULL != m_pIconImg && !m_pIconImg->IsNull())
	{
		if (bCalcValidRects)
		{
			lpncsp->rgrc[0].left += m_ptClient.x;
			lpncsp->rgrc[0].top += m_ptClient.y;
			lpncsp->rgrc[0].right -= m_nIconWidth;
			lpncsp->rgrc[1] = lpncsp->rgrc[0];
		}
	}

	CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CSkinEdit::OnNcPaint()
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	CRect rcClient;
	GetClientRect(&rcClient);

	ClientToScreen(&rcClient);
	rcClient.OffsetRect(-rcWindow.left, -rcWindow.top);

	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

	CDC *pWindowDC = GetWindowDC();
	CMemoryDC MemDC(pWindowDC,rcWindow);

	CRect rcIcon;
	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

 		CalcCenterRect(rcWindow, cxIcon, cyIcon, rcIcon);
 		rcIcon.right = rcWindow.right - 2;
 		rcIcon.left = rcIcon.right - cxIcon;
	}

	DrawParentWndBg(GetSafeHwnd(),MemDC.GetSafeHdc());

	if (m_bHover)
	{
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
		{
			m_pBackImgH->Draw(&MemDC, rcWindow);
		}
		else
		{
			if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
				m_pBackImgN->Draw(&MemDC, rcWindow);
		}
	}
	else
	{
		if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
			m_pBackImgN->Draw(&MemDC, rcWindow);
	}

 	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
 		m_pIconImg->Draw(&MemDC, rcIcon);

	pWindowDC->BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),&MemDC,0,0,SRCCOPY);

	ReleaseDC(pWindowDC);
}

BOOL CSkinEdit::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CSkinEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcIcon;
	CPoint pt;
	GetCursorPos(&pt);
	GetIconRect(rcIcon);

	if( PtInRect(&rcIcon,pt)) return;

 	m_bPress = TRUE;
// 	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	__super::OnLButtonDown(nFlags, point);
}

void CSkinEdit::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rcIcon;
	CPoint pt;
	GetCursorPos(&pt);
	GetIconRect(rcIcon);

	if( PtInRect(&rcIcon,pt)) 
	{
		return;
	}
	else
	{
		if (m_bPress)
		{
			m_bPress = FALSE;
			RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
		}
	}

	__super::OnLButtonUp(nFlags, point);
}

void CSkinEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseTracking)
	{
		TrackMouseLeave(GetSafeHwnd());

		m_bMouseTracking = TRUE;
		m_bHover = TRUE;
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	__super::OnMouseMove(nFlags, point);
}

LRESULT CSkinEdit::OnMouseLeave( WPARAM wparam, LPARAM lparam )
{
	m_bMouseTracking = FALSE;
	m_bHover = FALSE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	return TRUE;
}

void CSkinEdit::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pIconImg);
	RemoveScorll();
}

void CSkinEdit::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	if (m_bIsDefText)
	{
		m_bIsDefText = FALSE;
		SetPasswordChar(m_cPwdChar);
		SetWindowText(_T(""));
	}

	m_bFocus = TRUE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

void CSkinEdit::OnKillFocus(CWnd* pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	if (GetWindowTextLength() <= 0 && !m_strDefText.IsEmpty())
	{
		m_bIsDefText = TRUE;
		m_cPwdChar = GetPasswordChar();
		SetPasswordChar(0);
		SetWindowText(m_strDefText);
	}

	m_bFocus = FALSE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

BOOL CSkinEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CRect rcIcon;
	CPoint pt;
	GetCursorPos(&pt);
	GetIconRect(rcIcon);

	if( PtInRect(&rcIcon,pt))
	{
		if( m_bHandCursor )
			SetCursor(LoadCursor(NULL,IDC_HAND));
		else
			SetCursor(LoadCursor(NULL,IDC_ARROW));

		return TRUE;
	}

	return __super::OnSetCursor(pWnd, nHitTest, message);
}

void CSkinEdit::GetIconRect( RECT &rcIcon )
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	CalcCenterRect(rcWindow, m_nIconWidth, rcWindow.Height(), rcIcon);
	rcIcon.right = rcWindow.right - 2;
	rcIcon.left = rcIcon.right - m_nIconWidth;
}

BOOL CSkinEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return 	__super::CreateEx(
		WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_RIGHTSCROLLBAR|WS_EX_NOPARENTNOTIFY|WS_EX_CLIENTEDGE,
		TEXT("EDIT"),
		NULL,
		WS_VISIBLE|WS_CHILDWINDOW|WS_TABSTOP|ES_LEFT|ES_AUTOHSCROLL|dwStyle,
		rect,pParentWnd,nID);


	return __super::Create(dwStyle, rect, pParentWnd, nID);
}

void CSkinEdit::SetDefaultText( LPCTSTR lpszText )
{
	m_strDefText = lpszText;
}

void CSkinEdit::SetDefaultTextMode( BOOL bIsDefText )
{
	if (bIsDefText == m_bIsDefText)
		return;

	m_bIsDefText = bIsDefText;
	if (m_bIsDefText)
	{
		m_cPwdChar = GetPasswordChar();
		SetPasswordChar(0);
		SetWindowText(m_strDefText);
	}
	else
	{
		SetPasswordChar(m_cPwdChar);
		SetWindowText(_T(""));
	}
}

HBRUSH CSkinEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	if (m_bIsDefText)
		pDC->SetTextColor(m_colDefText);
	else
		pDC->SetTextColor(m_colNormalText);

	return (HBRUSH)NULL_BRUSH;
}

LRESULT CSkinEdit::OnNcHitTest(CPoint point)
{
	CRect rcIcon;
	GetIconRect(rcIcon);

	if( PtInRect(&rcIcon,point))
	{
		return HTBORDER;
	}

	return __super::OnNcHitTest(point);
}

void CSkinEdit::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	CWnd *pWnd = GetParent();

	if ( pWnd != NULL && pWnd->GetSafeHwnd() != NULL )
	{
		CRect rcIcon;
		CPoint pt;
		GetCursorPos(&pt);
		GetIconRect(rcIcon);

		if( PtInRect(&rcIcon,pt)) 
			pWnd->PostMessage(WM_COMMAND,GetDlgCtrlID());
	}

	__super::OnNcLButtonUp(nHitTest, point);
}

LRESULT CSkinEdit::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
// 	CString str;
// 	str.Format(TEXT("%x\n"),message);
// 	OutputDebugString(str);

	return __super::DefWindowProc(message, wParam, lParam);
}

void CSkinEdit::SetClientPoint( CPoint pt )
{
	m_ptClient = pt;
}

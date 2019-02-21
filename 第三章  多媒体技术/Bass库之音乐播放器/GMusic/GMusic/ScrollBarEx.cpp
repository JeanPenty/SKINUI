#include "StdAfx.h"
#include "ScrollBarEx.h"

CScrollBarEx::CScrollBarEx(void)
{
	m_hOwnerWnd = NULL;
	m_nCtrlId = 0;
	memset(&m_rcScrollBar, 0, sizeof(m_rcScrollBar));
	m_bHorizontal = TRUE;
	m_bVisible = TRUE;
	m_bEnabled = TRUE;

	m_nRange = 0;
	m_nScrollPos = 0;
	m_nLineSize = 8;

	memset(&m_ptLastMouse, 0, sizeof(m_ptLastMouse));
	m_nLastScrollPos = 0;
	m_nLastScrollOffset = 0;
	m_nScrollRepeatDelay = 0;
	m_dwUseTimerId = m_dwTimerId = 0;
	m_bMouseHover = FALSE;
	m_bCaptured = FALSE;
	m_bMouseTracking = FALSE;

	m_lpBgImgN = NULL;
	m_lpBgImgH = NULL;
	m_lpBgImgP = NULL;
	m_lpBgImgD = NULL;

	m_bShowLeftUpBtn = TRUE;
	memset(&m_rcLeftUpBtn, 0, sizeof(m_rcLeftUpBtn));
	m_dwLeftUpBtnState = 0;
	m_lpLeftUpBtnImgN = NULL;
	m_lpLeftUpBtnImgH = NULL;
	m_lpLeftUpBtnImgP = NULL;
	m_lpLeftUpBtnImgD = NULL;

	m_bShowRightDownBtn = TRUE;
	memset(&m_rcRightDownBtn, 0, sizeof(m_rcRightDownBtn));
	m_dwRightDownBtnState = 0;
	m_lpRightDownBtnImgN = NULL;
	m_lpRightDownBtnImgH = NULL;
	m_lpRightDownBtnImgP = NULL;
	m_lpRightDownBtnImgD = NULL;

	memset(&m_rcThumb, 0, sizeof(m_rcThumb));
	m_dwThumbState = 0;
	m_lpThumbImgN = NULL;
	m_lpThumbImgH = NULL;
	m_lpThumbImgP = NULL;
	m_lpThumbImgD = NULL;

	m_lpRailImgN = NULL;
	m_lpRailImgH = NULL;
	m_lpRailImgP = NULL;
	m_lpRailImgD = NULL;
}

CScrollBarEx::~CScrollBarEx(void)
{
}

BOOL CScrollBarEx::SetBgNormalPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpBgImgN);
	m_lpBgImgN = RenderEngine->GetImage(lpszFileName);
	return (m_lpBgImgN != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetBgHotPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpBgImgH);
	m_lpBgImgH = RenderEngine->GetImage(lpszFileName);
	return (m_lpBgImgH != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetBgPushedPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpBgImgP);
	m_lpBgImgP = RenderEngine->GetImage(lpszFileName);
	return (m_lpBgImgP != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetBgDisabledPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpBgImgD);
	m_lpBgImgD = RenderEngine->GetImage(lpszFileName);
	return (m_lpBgImgD != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::GetShowLeftUpBtn()
{
	return m_bShowLeftUpBtn;
}

void CScrollBarEx::SetShowLeftUpBtn(BOOL bShow)
{
	m_bShowLeftUpBtn = bShow;
	CalcScrollBarData();
}

BOOL CScrollBarEx::SetLeftUpBtnNormalPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpLeftUpBtnImgN);
	m_lpLeftUpBtnImgN = RenderEngine->GetImage(lpszFileName);
	return (m_lpLeftUpBtnImgN != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetLeftUpBtnHotPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpLeftUpBtnImgH);
	m_lpLeftUpBtnImgH = RenderEngine->GetImage(lpszFileName);
	return (m_lpLeftUpBtnImgH != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetLeftUpBtnPushedPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpLeftUpBtnImgP);
	m_lpLeftUpBtnImgP = RenderEngine->GetImage(lpszFileName);
	return (m_lpLeftUpBtnImgP != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetLeftUpBtnDisabledPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpLeftUpBtnImgD);
	m_lpLeftUpBtnImgD = RenderEngine->GetImage(lpszFileName);
	return (m_lpLeftUpBtnImgD != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::GetShowRightDownBtn()
{
	return m_bShowRightDownBtn;
}

void CScrollBarEx::SetShowRightDownBtn(BOOL bShow)
{
	m_bShowRightDownBtn = bShow;
	CalcScrollBarData();
}

BOOL CScrollBarEx::SetRightDownBtnNormalPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRightDownBtnImgN);
	m_lpRightDownBtnImgN = RenderEngine->GetImage(lpszFileName);
	return (m_lpRightDownBtnImgN != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetRightDownBtnHotPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRightDownBtnImgH);
	m_lpRightDownBtnImgH = RenderEngine->GetImage(lpszFileName);
	return (m_lpRightDownBtnImgH != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetRightDownBtnPushedPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRightDownBtnImgP);
	m_lpRightDownBtnImgP = RenderEngine->GetImage(lpszFileName);
	return (m_lpRightDownBtnImgP != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetRightDownBtnDisabledPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRightDownBtnImgD);
	m_lpRightDownBtnImgD = RenderEngine->GetImage(lpszFileName);
	return (m_lpRightDownBtnImgD != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetThumbNormalPic(LPCTSTR lpszFileName, RECT * lpNinePart/* = NULL*/)
{
	RenderEngine->RemoveImage(m_lpThumbImgN);
	m_lpThumbImgN = RenderEngine->GetImage(lpszFileName);
	if (m_lpThumbImgN != NULL && lpNinePart != NULL)
		m_lpThumbImgN->SetNinePart(lpNinePart);
	return (m_lpThumbImgN != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetThumbHotPic(LPCTSTR lpszFileName, RECT * lpNinePart/* = NULL*/)
{
	RenderEngine->RemoveImage(m_lpThumbImgH);
	m_lpThumbImgH = RenderEngine->GetImage(lpszFileName);
	if (m_lpThumbImgH != NULL && lpNinePart != NULL)
		m_lpThumbImgH->SetNinePart(lpNinePart);
	return (m_lpThumbImgH != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetThumbPushedPic(LPCTSTR lpszFileName, RECT * lpNinePart/* = NULL*/)
{
	RenderEngine->RemoveImage(m_lpThumbImgP);
	m_lpThumbImgP = RenderEngine->GetImage(lpszFileName);
	if (m_lpThumbImgP != NULL && lpNinePart != NULL)
		m_lpThumbImgP->SetNinePart(lpNinePart);
	return (m_lpThumbImgP != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetThumbDisabledPic(LPCTSTR lpszFileName, RECT * lpNinePart/* = NULL*/)
{
	RenderEngine->RemoveImage(m_lpThumbImgD);
	m_lpThumbImgD = RenderEngine->GetImage(lpszFileName);
	if (m_lpThumbImgD != NULL && lpNinePart != NULL)
		m_lpThumbImgD->SetNinePart(lpNinePart);
	return (m_lpThumbImgD != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetRailNormalPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRailImgN);
	m_lpRailImgN = RenderEngine->GetImage(lpszFileName);
	return (m_lpRailImgN != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetRailHotPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRailImgH);
	m_lpRailImgH = RenderEngine->GetImage(lpszFileName);
	return (m_lpRailImgH != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetRailPushedPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRailImgP);
	m_lpRailImgP = RenderEngine->GetImage(lpszFileName);
	return (m_lpRailImgP != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::SetRailDisabledPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpRailImgD);
	m_lpRailImgD = RenderEngine->GetImage(lpszFileName);
	return (m_lpRailImgD != NULL) ? TRUE : FALSE;
}

BOOL CScrollBarEx::Create(HWND hOwnerWnd, UINT nCtrlId, RECT * lpRect, 
							DWORD dwUseTimerId, BOOL bHorizontal/* = TRUE*/, BOOL bVisible/* = TRUE*/)
{
	m_hOwnerWnd = hOwnerWnd;
	m_nCtrlId = nCtrlId;
	if (lpRect != NULL)
		m_rcScrollBar = *lpRect;
	m_dwUseTimerId = dwUseTimerId;
	m_bHorizontal = bHorizontal;
	m_bVisible = bVisible;
	m_bEnabled = TRUE;
	return TRUE;
}

BOOL CScrollBarEx::Destroy()
{
	RenderEngine->RemoveImage(m_lpBgImgN);
	RenderEngine->RemoveImage(m_lpBgImgH);
	RenderEngine->RemoveImage(m_lpBgImgP);
	RenderEngine->RemoveImage(m_lpBgImgD);

	RenderEngine->RemoveImage(m_lpLeftUpBtnImgN);
	RenderEngine->RemoveImage(m_lpLeftUpBtnImgH);
	RenderEngine->RemoveImage(m_lpLeftUpBtnImgP);
	RenderEngine->RemoveImage(m_lpLeftUpBtnImgD);

	RenderEngine->RemoveImage(m_lpRightDownBtnImgN);
	RenderEngine->RemoveImage(m_lpRightDownBtnImgH);
	RenderEngine->RemoveImage(m_lpRightDownBtnImgP);
	RenderEngine->RemoveImage(m_lpRightDownBtnImgD);

	RenderEngine->RemoveImage(m_lpThumbImgN);
	RenderEngine->RemoveImage(m_lpThumbImgH);
	RenderEngine->RemoveImage(m_lpThumbImgP);
	RenderEngine->RemoveImage(m_lpThumbImgD);

	RenderEngine->RemoveImage(m_lpRailImgN);
	RenderEngine->RemoveImage(m_lpRailImgH);
	RenderEngine->RemoveImage(m_lpRailImgP);
	RenderEngine->RemoveImage(m_lpRailImgD);

	m_hOwnerWnd = NULL;
	m_nCtrlId = 0;
	memset(&m_rcScrollBar, 0, sizeof(m_rcScrollBar));
	m_bHorizontal = TRUE;
	m_bVisible = TRUE;
	m_bEnabled = TRUE;

	m_nRange = 0;
	m_nScrollPos = 0;
	m_nLineSize = 8;

	memset(&m_ptLastMouse, 0, sizeof(m_ptLastMouse));
	m_nLastScrollPos = 0;
	m_nLastScrollOffset = 0;
	m_nScrollRepeatDelay = 0;
	m_dwUseTimerId = m_dwTimerId = 0;
	m_bMouseHover = FALSE;
	m_bCaptured = FALSE;
	m_bMouseTracking = FALSE;

	m_bShowLeftUpBtn = TRUE;
	memset(&m_rcLeftUpBtn, 0, sizeof(m_rcLeftUpBtn));
	m_dwLeftUpBtnState = 0;

	m_bShowRightDownBtn = TRUE;
	memset(&m_rcRightDownBtn, 0, sizeof(m_rcRightDownBtn));
	m_dwRightDownBtnState = 0;

	memset(&m_rcThumb, 0, sizeof(m_rcThumb));
	m_dwThumbState = 0;

	return TRUE;
}

void CScrollBarEx::SetOwnerWnd(HWND hWnd)
{
	m_hOwnerWnd = hWnd;
}

HWND CScrollBarEx::GetOwnerWnd()
{
	return m_hOwnerWnd;
}

void CScrollBarEx::SetCtrlId(UINT nCtrlId)
{
	m_nCtrlId = nCtrlId;
}

UINT CScrollBarEx::GetCtrlId()
{
	return m_nCtrlId;
}

void CScrollBarEx::SetRect(RECT * lpRect)
{
	if (lpRect != NULL)
		m_rcScrollBar = *lpRect;
	CalcScrollBarData();
}

void CScrollBarEx::GetRect(RECT * lpRect)
{
	if (lpRect != NULL)
		*lpRect = m_rcScrollBar;
}

BOOL CScrollBarEx::IsHorizontal()
{
	return m_bHorizontal;
}

void CScrollBarEx::SetHorizontal(BOOL bHorizontal/* = TRUE*/)
{
	if (m_bHorizontal == bHorizontal)
		return;

	m_bHorizontal = bHorizontal;
	Invalidate();
}

BOOL CScrollBarEx::IsVisible()
{
	return m_bVisible;
}

void CScrollBarEx::SetVisible(BOOL bVisible/* = TRUE*/)
{
	if (m_bVisible == bVisible)
		return;

	m_bVisible = bVisible;
	Invalidate();
}

BOOL CScrollBarEx::IsEnabled()
{
	return m_bEnabled;
}

void CScrollBarEx::SetEnabled(BOOL bEnable/* = TRUE*/)
{
	if (m_bEnabled == bEnable)
		return;

	m_bEnabled = bEnable;
	if (!m_bEnabled)
	{
		m_dwLeftUpBtnState = 0;
		m_dwRightDownBtnState = 0;
		m_dwThumbState = 0;
	}
	Invalidate();
}

int CScrollBarEx::GetScrollRange()
{
	return m_nRange;
}

void CScrollBarEx::SetScrollRange(int nRange)
{
	if (m_nRange == nRange)
		return;

	m_nRange = nRange;

	if (m_nRange < 0)
		m_nRange = 0;

	if (m_nScrollPos > m_nRange)
		m_nScrollPos = m_nRange;

	CalcScrollBarData();
	Invalidate();
}

int CScrollBarEx::GetScrollPos()
{
	return m_nScrollPos;
}

void CScrollBarEx::SetScrollPos(int nPos)
{
	if (m_nScrollPos == nPos)
		return;

	m_nScrollPos = nPos;

	if (m_nScrollPos < 0)
		m_nScrollPos = 0;

	if (m_nScrollPos > m_nRange)
		m_nScrollPos = m_nRange;

	CalcScrollBarData();
	Invalidate();
}

int CScrollBarEx::GetLineSize()
{
	return m_nLineSize;
}

void CScrollBarEx::SetLineSize(int nSize)
{
	m_nLineSize = nSize;
}

LRESULT CScrollBarEx::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bMsgHandled = FALSE;

	switch (uMsg)
	{
// 	case WM_PAINT:
// 		OnPaint((HDC)wParam);
// 		break;

	case WM_LBUTTONDOWN:
		{
			CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			if (IsVisible() && IsEnabled() && ::PtInRect(&m_rcScrollBar, point))
			{
				OnLButtonDown((UINT)wParam, point);
				bMsgHandled = TRUE;
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			if (IsVisible() && IsEnabled() && IsCaptured())
			{
				OnLButtonUp((UINT)wParam, CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
				bMsgHandled = TRUE;
			}
		}
		break;

	case WM_MOUSEMOVE:
		{
			CPoint point = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			if (IsVisible() && IsEnabled() && (IsCaptured() || IsMouseTracking() || ::PtInRect(&m_rcScrollBar, point)))
			{
				OnMouseMove((UINT)wParam, point);
				bMsgHandled = TRUE;
			}
		}
		break;

	case WM_MOUSELEAVE:
		{
			if (IsMouseTracking())
			{
				OnMouseLeave();
				bMsgHandled = TRUE;
			}
		}
		break;

	case WM_TIMER:
		{
			UINT_PTR nIDEvent = (UINT_PTR)wParam;
			if (nIDEvent == m_dwTimerId)
			{
				OnTimer(nIDEvent);
				bMsgHandled = TRUE;
			}
		}
		break;

		
	case WM_KILLFOCUS:
		{
			if (IsVisible() && IsEnabled() && IsCaptured())
			{
				OnLButtonUp((UINT)wParam, CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
				bMsgHandled = TRUE;
			}
		}
		break;
	}

	return bMsgHandled;
}

void CScrollBarEx::OnPaint(CDC*pDC)
{
 	if (!m_hOwnerWnd)
 		return;

	if (!IsVisible() )
		return;

	DrawBg(pDC);
	DrawLeftUpBtn(pDC);
	DrawRightDownBtn(pDC);
	DrawThumb(pDC);
	DrawRail(pDC);
}

void CScrollBarEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!IsVisible() || !IsEnabled() || !::PtInRect(&m_rcScrollBar, point))
		return;

	::SetFocus(m_hOwnerWnd);
	SetCapture();

	m_nLastScrollOffset = 0;
	m_nScrollRepeatDelay = 0;
	m_dwTimerId = ::SetTimer(m_hOwnerWnd, m_dwUseTimerId, 50, NULL);

	if (::PtInRect(&m_rcLeftUpBtn, point))	// 左/上箭头
	{
		m_dwLeftUpBtnState |= UISTATE_PUSHED;
		if (!m_bHorizontal)		// 垂直
		{
			if (::IsWindow(m_hOwnerWnd))
				::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_LINEUP, m_nCtrlId);
			else
				SetScrollPos(m_nScrollPos - m_nLineSize);
		}
		else	// 水平
		{
			if (::IsWindow(m_hOwnerWnd))
				::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_LINELEFT, m_nCtrlId);
			else
				SetScrollPos(m_nScrollPos - m_nLineSize);
		}
	}
	else if (::PtInRect(&m_rcRightDownBtn, point))	// 右/下箭头
	{
		m_dwRightDownBtnState |= UISTATE_PUSHED;
		if (!m_bHorizontal)
		{
			if (::IsWindow(m_hOwnerWnd))
				::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_LINEDOWN, m_nCtrlId);
			else
				SetScrollPos(m_nScrollPos + m_nLineSize);
		}
		else
		{
			if (::IsWindow(m_hOwnerWnd))
				::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_LINERIGHT, m_nCtrlId);
			else
				SetScrollPos(m_nScrollPos + m_nLineSize);
		}
	}
	else if (::PtInRect(&m_rcThumb, point))	// 滑块
	{
		m_dwThumbState |= (UISTATE_CAPTURED | UISTATE_PUSHED);
		m_ptLastMouse = point;
		m_nLastScrollPos = m_nScrollPos;
	}
	else
	{
		if (!m_bHorizontal)	// 垂直
		{
			if (point.y < m_rcThumb.top)	// 上箭头和滑块之间区域
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_PAGEUP, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos + m_rcScrollBar.top - m_rcScrollBar.bottom);
			}
			else if (point.y > m_rcThumb.bottom)	// 下箭头和滑块之间区域
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_PAGEDOWN, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos - m_rcScrollBar.top + m_rcScrollBar.bottom);
			}
		}
		else	// 水平
		{
			if (point.x < m_rcThumb.left)	// 左箭头和滑块之间区域
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_PAGELEFT, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos + m_rcScrollBar.left - m_rcScrollBar.right);
			}
			else if (point.x > m_rcThumb.right)		// 右箭头和滑块之间区域
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_PAGERIGHT, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos - m_rcScrollBar.left + m_rcScrollBar.right);
			}
		}
	}
}

void CScrollBarEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!IsVisible() || !IsEnabled()/* || !::PtInRect(&m_rcScrollBar, point)*/)
		return;

	ReleaseCapture();

	m_nScrollRepeatDelay = 0;
	m_nLastScrollOffset = 0;
	::KillTimer(m_hOwnerWnd, m_dwTimerId);

	if ((m_dwThumbState & UISTATE_CAPTURED) != 0)
	{
		m_dwThumbState &= ~(UISTATE_CAPTURED | UISTATE_PUSHED);
		Invalidate();
	}
	else if((m_dwLeftUpBtnState & UISTATE_PUSHED) != 0)
	{
		m_dwLeftUpBtnState &= ~UISTATE_PUSHED;
		Invalidate();
	}
	else if((m_dwRightDownBtnState & UISTATE_PUSHED) != 0)
	{
		m_dwRightDownBtnState &= ~UISTATE_PUSHED;
		Invalidate();
	}
}

void CScrollBarEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!IsVisible() || !IsEnabled())
		return;

// 	if (::PtInRect(&m_rcScrollBar, point))
// 	{
// 		if (!m_bMouseHover)	// MouseEnter
// 			m_bMouseHover = TRUE;
// 	}
// 	else
// 	{
// 		if (m_bMouseHover)	// MouseLeave
// 			m_bMouseHover = FALSE;
// 	}

	if ((m_dwThumbState & UISTATE_CAPTURED) != 0)
	{
		if (!m_bHorizontal)
		{
			m_nLastScrollOffset = (point.y - m_ptLastMouse.y) * m_nRange / \
				(m_rcScrollBar.Height() - m_rcThumb.bottom + m_rcThumb.top - 2 * m_rcScrollBar.Width());
		}
		else
		{
			m_nLastScrollOffset = (point.x - m_ptLastMouse.x) * m_nRange / \
				(m_rcScrollBar.Width() - m_rcThumb.right + m_rcThumb.left - 2 * m_rcScrollBar.Height());
		}
	}

	if (::PtInRect(&m_rcScrollBar, point))
	{
		if (!m_bMouseHover)	// MouseEnter
		{
			m_bMouseHover = TRUE;
			m_bMouseTracking = TRUE;
			StartTrackMouseLeave();
		}

// 		if ((m_dwThumbState & UISTATE_CAPTURED) != 0)
// 		{
// 			if (!m_bHorizontal)
// 			{
// 				m_nLastScrollOffset = (point.y - m_ptLastMouse.y) * m_nRange / \
// 					(m_rcScrollBar.bottom - m_rcScrollBar.top - m_rcThumb.bottom + m_rcThumb.top - 2 * m_rcScrollBar.Width());
// 				wchar_t c[100];
// 				wsprintf(c, _T("%d\n"), m_nLastScrollOffset);
// 				::OutputDebugString(c);
// 			}
// 			else
// 			{
// 				m_nLastScrollOffset = (point.x - m_ptLastMouse.x) * m_nRange / \
// 					(m_rcScrollBar.right - m_rcScrollBar.left - m_rcThumb.right + m_rcThumb.left - 2 * m_rcScrollBar.Height());
// 			}
// 		}
		/*else */if ((m_dwLeftUpBtnState & UISTATE_PUSHED) != 0)
		{

		}
		else if ((m_dwRightDownBtnState & UISTATE_PUSHED) != 0)
		{

		}
		else
		{
			if (::PtInRect(&m_rcLeftUpBtn, point))
			{
				if ((m_dwLeftUpBtnState & UISTATE_HOT) == 0)
				{
					m_dwLeftUpBtnState |= UISTATE_HOT;
					m_dwRightDownBtnState &= ~UISTATE_HOT;
					m_dwThumbState &= ~UISTATE_HOT;
					Invalidate();
				}
			}
			else if (::PtInRect(&m_rcRightDownBtn, point))
			{
				if ((m_dwRightDownBtnState & UISTATE_HOT) == 0)
				{
					m_dwRightDownBtnState |= UISTATE_HOT;
					m_dwLeftUpBtnState &= ~UISTATE_HOT;
					m_dwThumbState &= ~UISTATE_HOT;
					Invalidate();
				}
			}
			else if (::PtInRect(&m_rcThumb, point))
			{
				if ((m_dwThumbState & UISTATE_HOT) == 0)
				{
					m_dwThumbState |= UISTATE_HOT;
					m_dwLeftUpBtnState &= ~UISTATE_HOT;
					m_dwRightDownBtnState &= ~UISTATE_HOT;
					Invalidate();
				}
			}
			else
			{
				if ((m_dwLeftUpBtnState & UISTATE_HOT) || 
					(m_dwRightDownBtnState & UISTATE_HOT) ||
					(m_dwThumbState & UISTATE_HOT))
				{
					m_dwLeftUpBtnState &= ~UISTATE_HOT;
					m_dwRightDownBtnState &= ~UISTATE_HOT;
					m_dwThumbState &= ~UISTATE_HOT;
					Invalidate();
				}
			}
		}
	}
	else
	{
		if (m_bMouseHover)	// MouseLeave
		{
			m_bMouseHover = FALSE;
			m_bMouseTracking = FALSE;

			if ((m_dwLeftUpBtnState & UISTATE_HOT) || 
				(m_dwRightDownBtnState & UISTATE_HOT) ||
				(m_dwThumbState & UISTATE_HOT))
			{
				m_dwLeftUpBtnState &= ~UISTATE_HOT;
				m_dwRightDownBtnState &= ~UISTATE_HOT;
				m_dwThumbState &= ~UISTATE_HOT;
				Invalidate();
			}
		}
	}
}

void CScrollBarEx::OnMouseLeave()
{
	if (!IsVisible() || !IsEnabled() || !m_bMouseHover)
		return;

	m_bMouseHover = FALSE;
	m_bMouseTracking = FALSE;

	if ((m_dwLeftUpBtnState & UISTATE_HOT) || 
		(m_dwRightDownBtnState & UISTATE_HOT) ||
		(m_dwThumbState & UISTATE_HOT))
	{
		m_dwLeftUpBtnState &= ~UISTATE_HOT;
		m_dwRightDownBtnState &= ~UISTATE_HOT;
		m_dwThumbState &= ~UISTATE_HOT;
		Invalidate();
	}
}

void CScrollBarEx::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_dwTimerId)
	{
		++m_nScrollRepeatDelay;
		if ((m_dwThumbState & UISTATE_CAPTURED) != 0)	// 拖动滑块
		{
			if (!m_bHorizontal)	// 垂直
			{
				SetScrollPos(m_nLastScrollPos + m_nLastScrollOffset);
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_THUMBTRACK, m_nCtrlId);	// ？
			}
			else
			{
				SetScrollPos(m_nLastScrollPos + m_nLastScrollOffset);
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_THUMBTRACK, m_nCtrlId);	// ？
			}

			Invalidate();
		}
		else if((m_dwLeftUpBtnState & UISTATE_PUSHED) != 0)	// 长按左/上箭头
		{
			if (m_nScrollRepeatDelay <= 5)
				return;

			if (!m_bHorizontal)		// 垂直
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_LINEUP, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos - m_nLineSize);
			}
			else	// 水平
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_LINELEFT, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos - m_nLineSize);
			}
		}
		else if((m_dwRightDownBtnState & UISTATE_PUSHED) != 0)	// 长按右/下箭头
		{
			if (m_nScrollRepeatDelay <= 5)
				return;

			if (!m_bHorizontal)
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_LINEDOWN, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos + m_nLineSize);
			}
			else
			{
				if (::IsWindow(m_hOwnerWnd))
					::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_LINERIGHT, m_nCtrlId);
				else
					SetScrollPos(m_nScrollPos + m_nLineSize);
			}
		}
		else
		{
			if (m_nScrollRepeatDelay <= 5)
				return;

			POINT pt = {0};
			::GetCursorPos(&pt);
			::ScreenToClient(m_hOwnerWnd, &pt);

			if (!m_bHorizontal)	// 垂直
			{
				if (pt.y < m_rcThumb.top)	// 上箭头和滑块之间区域
				{
					if (::IsWindow(m_hOwnerWnd))
						::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_PAGEUP, m_nCtrlId);
					else
						SetScrollPos(m_nScrollPos + m_rcScrollBar.top - m_rcScrollBar.bottom);
				}
				else if (pt.y > m_rcThumb.bottom)	// 下箭头和滑块之间区域
				{
					if (::IsWindow(m_hOwnerWnd))
						::SendMessage(m_hOwnerWnd, WM_VSCROLL, SB_PAGEDOWN, m_nCtrlId);
					else
						SetScrollPos(m_nScrollPos - m_rcScrollBar.top + m_rcScrollBar.bottom);
				}
			}
			else	// 水平
			{
				if (pt.x < m_rcThumb.left)	// 左箭头和滑块之间区域
				{
					if (::IsWindow(m_hOwnerWnd))
						::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_PAGELEFT, m_nCtrlId);
					else
						SetScrollPos(m_nScrollPos + m_rcScrollBar.left - m_rcScrollBar.right);
				}
				else if (pt.x > m_rcThumb.right)	// 右箭头和滑块之间区域
				{
					if (::IsWindow(m_hOwnerWnd))
						::SendMessage(m_hOwnerWnd, WM_HSCROLL, SB_PAGERIGHT, m_nCtrlId);
					else
						SetScrollPos(m_nScrollPos - m_rcScrollBar.left + m_rcScrollBar.right);
				}
			}
		}
	}
}

void CScrollBarEx::DrawBg(CDC*pDC)
{
	if (!IsEnabled()) 
		m_dwThumbState |= UISTATE_DISABLED;
	else
		m_dwThumbState &= ~UISTATE_DISABLED;

	if ((m_dwThumbState & UISTATE_DISABLED) != 0)
	{
		if (m_lpBgImgD != NULL && !m_lpBgImgD->IsNull())
			m_lpBgImgD->DrawImage(pDC, m_rcScrollBar);
	}
	else if((m_dwThumbState & UISTATE_PUSHED) != 0)
	{
		if (m_lpBgImgP != NULL && !m_lpBgImgP->IsNull())
			m_lpBgImgP->DrawImage(pDC, m_rcScrollBar);
	}
	else if((m_dwThumbState & UISTATE_HOT) != 0)
	{
		if (m_lpBgImgH != NULL && !m_lpBgImgH->IsNull())
			m_lpBgImgH->DrawImage(pDC, m_rcScrollBar);
	}
	else
	{
		if (m_lpBgImgN != NULL && !m_lpBgImgN->IsNull())
			m_lpBgImgN->DrawImage(pDC, m_rcScrollBar);
	}
}

void CScrollBarEx::DrawLeftUpBtn(CDC*pDC)
{
	if (!m_bShowLeftUpBtn)
		return;

	if (!IsEnabled())
		m_dwLeftUpBtnState |= UISTATE_DISABLED;
	else
		m_dwLeftUpBtnState &= ~ UISTATE_DISABLED;

	if ((m_dwLeftUpBtnState & UISTATE_DISABLED) != 0)
	{
		if (m_lpLeftUpBtnImgD != NULL && !m_lpLeftUpBtnImgD->IsNull())
			m_lpLeftUpBtnImgD->DrawImage(pDC, m_rcLeftUpBtn);
	}
	else if((m_dwLeftUpBtnState & UISTATE_PUSHED) != 0)
	{
		if (m_lpLeftUpBtnImgP != NULL && !m_lpLeftUpBtnImgP->IsNull())
			m_lpLeftUpBtnImgP->DrawImage(pDC, m_rcLeftUpBtn);
	}
	else if((m_dwLeftUpBtnState & UISTATE_HOT) != 0)
	{
		if (m_lpLeftUpBtnImgH != NULL && !m_lpLeftUpBtnImgH->IsNull())
			m_lpLeftUpBtnImgH->DrawImage(pDC, m_rcLeftUpBtn);
	}
	else
	{
		if (m_lpLeftUpBtnImgN != NULL && !m_lpLeftUpBtnImgN->IsNull())
			m_lpLeftUpBtnImgN->DrawImage(pDC, m_rcLeftUpBtn);
	}
}

void CScrollBarEx::DrawRightDownBtn(CDC*pDC)
{
	if (!m_bShowRightDownBtn)
		return;

	if (!IsEnabled())
		m_dwRightDownBtnState |= UISTATE_DISABLED;
	else
		m_dwRightDownBtnState &= ~ UISTATE_DISABLED;

	if ((m_dwRightDownBtnState & UISTATE_DISABLED) != 0)
	{
		if (m_lpRightDownBtnImgD != NULL && !m_lpRightDownBtnImgD->IsNull())
			m_lpRightDownBtnImgD->DrawImage(pDC, m_rcRightDownBtn);
	}
	else if ((m_dwRightDownBtnState & UISTATE_PUSHED) != 0)
	{
		if (m_lpRightDownBtnImgP != NULL && !m_lpRightDownBtnImgP->IsNull())
			m_lpRightDownBtnImgP->DrawImage(pDC, m_rcRightDownBtn);
	}
	else if ((m_dwRightDownBtnState & UISTATE_HOT) != 0)
	{
		if (m_lpRightDownBtnImgH != NULL && !m_lpRightDownBtnImgH->IsNull())
			m_lpRightDownBtnImgH->DrawImage(pDC, m_rcRightDownBtn);
	}
	else
	{
		if (m_lpRightDownBtnImgN != NULL && !m_lpRightDownBtnImgN->IsNull())
			m_lpRightDownBtnImgN->DrawImage(pDC, m_rcRightDownBtn);
	}
}

void CScrollBarEx::DrawThumb(CDC*pDC)
{
	if (m_rcThumb.left == 0 && m_rcThumb.top == 0 && m_rcThumb.right == 0 && m_rcThumb.bottom == 0)
		return;

	if (!IsEnabled())
		m_dwThumbState |= UISTATE_DISABLED;
	else
		m_dwThumbState &= ~ UISTATE_DISABLED;

	if ((m_dwThumbState & UISTATE_DISABLED) != 0)
	{
		if (m_lpThumbImgD != NULL && !m_lpThumbImgD->IsNull())
			m_lpThumbImgD->Draw(pDC, m_rcThumb);
	}
	else if ((m_dwThumbState & UISTATE_PUSHED) != 0 )
	{
		if (m_lpThumbImgP != NULL && !m_lpThumbImgP->IsNull())
			m_lpThumbImgP->Draw(pDC, m_rcThumb);
	}
	else if ((m_dwThumbState & UISTATE_HOT) != 0)
	{
		if (m_lpThumbImgH != NULL && !m_lpThumbImgH->IsNull())
			m_lpThumbImgH->Draw(pDC, m_rcThumb);
	}
	else
	{
		if (m_lpThumbImgN != NULL && !m_lpThumbImgN->IsNull())
			m_lpThumbImgN->Draw(pDC, m_rcThumb);
	}
}

void CScrollBarEx::DrawRail(CDC*pDC)
{
	if (m_rcThumb.left == 0 && m_rcThumb.top == 0 && m_rcThumb.right == 0 && m_rcThumb.bottom == 0)
		return;

	if (!IsEnabled())
		m_dwThumbState |= UISTATE_DISABLED;
	else
		m_dwThumbState &= ~ UISTATE_DISABLED;

	CRect rcRail;
	if (!m_bHorizontal)
	{
		rcRail = CRect(0,0,0,0);
	}
	else
	{
		rcRail = CRect(0,0,0,0);
	}

	if ((m_dwThumbState & UISTATE_DISABLED) != 0)
	{
		if (m_lpRailImgD != NULL && !m_lpRailImgD->IsNull())
			m_lpRailImgD->DrawImage(pDC, rcRail);
	}
	else if((m_dwThumbState & UISTATE_PUSHED) != 0)
	{
		if (m_lpRailImgP != NULL && !m_lpRailImgP->IsNull())
			m_lpRailImgP->DrawImage(pDC, rcRail);
	}
	else if((m_dwThumbState & UISTATE_HOT) != 0)
	{
		if (m_lpRailImgH != NULL && !m_lpRailImgH->IsNull())
			m_lpRailImgH->DrawImage(pDC, rcRail);
	}
	else
	{
		if (m_lpRailImgN != NULL && !m_lpRailImgN->IsNull())
			m_lpRailImgN->DrawImage(pDC, rcRail);
	}
}

BOOL CScrollBarEx::Invalidate(BOOL bErase/* = TRUE*/)
{
	if (::IsWindow(m_hOwnerWnd))
		return ::InvalidateRect(m_hOwnerWnd, &m_rcScrollBar, bErase);
	else
		return FALSE;
}

void CScrollBarEx::CalcScrollBarData()
{
	if (m_bHorizontal)	// 水平
	{
		int cx = m_rcScrollBar.Width();
		int cy = m_rcScrollBar.Height();

		if (m_bShowLeftUpBtn)
			cx -= cy;
		if (m_bShowRightDownBtn)
			cx -= cy;
		if (cx > cy)
		{
			m_rcLeftUpBtn.left = m_rcScrollBar.left;	// 计算左箭头按钮区域
			m_rcLeftUpBtn.top = m_rcScrollBar.top;
			if (m_bShowLeftUpBtn)
			{
				m_rcLeftUpBtn.right = m_rcScrollBar.left + cy;
				m_rcLeftUpBtn.bottom = m_rcScrollBar.top + cy;
			}
			else
			{
				m_rcLeftUpBtn.right = m_rcLeftUpBtn.left;
				m_rcLeftUpBtn.bottom = m_rcLeftUpBtn.top;
			}

			m_rcRightDownBtn.top = m_rcScrollBar.top;	// 计算右箭头按钮区域
			m_rcRightDownBtn.right = m_rcScrollBar.right;
			if (m_bShowRightDownBtn)
			{
				m_rcRightDownBtn.left = m_rcScrollBar.right - cy;
				m_rcRightDownBtn.bottom = m_rcScrollBar.top + cy;
			}
			else
			{
				m_rcRightDownBtn.left = m_rcRightDownBtn.right;
				m_rcRightDownBtn.bottom = m_rcRightDownBtn.top;
			}

			m_rcThumb.top = m_rcScrollBar.top;
			m_rcThumb.bottom = m_rcScrollBar.top + cy;
			if (m_nRange > 0)
			{
				int cxThumb = cx * m_rcScrollBar.Width() / (m_nRange + m_rcScrollBar.Width());
				if (cxThumb < cy)
					cxThumb = cy;

				m_rcThumb.left = m_nScrollPos * (cx - cxThumb) / m_nRange + m_rcLeftUpBtn.right;
				m_rcThumb.right = m_rcThumb.left + cxThumb;
				if (m_rcThumb.right > m_rcRightDownBtn.left)
				{
					m_rcThumb.left = m_rcRightDownBtn.left - cxThumb;
					m_rcThumb.right = m_rcRightDownBtn.left;
				}
			}
			else
			{
				m_rcThumb.left = m_rcLeftUpBtn.right;
				m_rcThumb.right = m_rcRightDownBtn.left;
			}
		}
		else
		{
			int cxButton = m_rcScrollBar.Width() / 2;
			if (cxButton > cy)
				cxButton = cy;
			m_rcLeftUpBtn.left = m_rcScrollBar.left;
			m_rcLeftUpBtn.top = m_rcScrollBar.top;
			if (m_bShowLeftUpBtn)
			{
				m_rcLeftUpBtn.right = m_rcScrollBar.left + cxButton;
				m_rcLeftUpBtn.bottom = m_rcScrollBar.top + cy;
			}
			else
			{
				m_rcLeftUpBtn.right = m_rcLeftUpBtn.left;
				m_rcLeftUpBtn.bottom = m_rcLeftUpBtn.top;
			}

			m_rcRightDownBtn.top = m_rcScrollBar.top;
			m_rcRightDownBtn.right = m_rcScrollBar.right;
			if (m_bShowRightDownBtn)
			{
				m_rcRightDownBtn.left = m_rcScrollBar.right - cxButton;
				m_rcRightDownBtn.bottom = m_rcScrollBar.top + cy;
			}
			else
			{
				m_rcRightDownBtn.left = m_rcRightDownBtn.right;
				m_rcRightDownBtn.bottom = m_rcRightDownBtn.top;
			}

			memset(&m_rcThumb, 0, sizeof(m_rcThumb));
		}
	}
	else	// 垂直
	{
		int cx = m_rcScrollBar.Width();
		int cy = m_rcScrollBar.Height();

		if (m_bShowLeftUpBtn)
			cy -= cx;
		if (m_bShowRightDownBtn)
			cy -= cx;
		if (cy > cx)
		{
			m_rcLeftUpBtn.left = m_rcScrollBar.left;
			m_rcLeftUpBtn.top = m_rcScrollBar.top;
			if (m_bShowLeftUpBtn)
			{
				m_rcLeftUpBtn.right = m_rcScrollBar.left + cx;
				m_rcLeftUpBtn.bottom = m_rcScrollBar.top + cx;
			}
			else
			{
				m_rcLeftUpBtn.right = m_rcLeftUpBtn.left;
				m_rcLeftUpBtn.bottom = m_rcLeftUpBtn.top;
			}

			m_rcRightDownBtn.left = m_rcScrollBar.left;
			m_rcRightDownBtn.bottom = m_rcScrollBar.bottom;
			if (m_bShowRightDownBtn)
			{
				m_rcRightDownBtn.top = m_rcScrollBar.bottom - cx;
				m_rcRightDownBtn.right = m_rcScrollBar.left + cx;
			}
			else
			{
				m_rcRightDownBtn.top = m_rcRightDownBtn.bottom;
				m_rcRightDownBtn.right = m_rcRightDownBtn.left;
			}

			m_rcThumb.left = m_rcScrollBar.left;
			m_rcThumb.right = m_rcScrollBar.left + cx;
			if (m_nRange > 0)
			{
				// 滚动条高度 * (显示大小 / 总大小)
				// 滚动条高度 * 显示大小 / 总大小
				int cyThumb = cy * m_rcScrollBar.Height() / (m_nRange + m_rcScrollBar.Height());
				if (cyThumb < cx)
					cyThumb = cx;

				m_rcThumb.top = m_nScrollPos * (cy - cyThumb) / m_nRange + m_rcLeftUpBtn.bottom;
				m_rcThumb.bottom = m_rcThumb.top + cyThumb;
				if (m_rcThumb.bottom > m_rcRightDownBtn.top)
				{
					m_rcThumb.top = m_rcRightDownBtn.top - cyThumb;
					m_rcThumb.bottom = m_rcRightDownBtn.top;
				}
			}
			else
			{
				m_rcThumb.top = m_rcLeftUpBtn.bottom;
				m_rcThumb.bottom = m_rcRightDownBtn.top;
			}
		}
		else
		{
			int cyButton = m_rcScrollBar.Height() / 2;
			if (cyButton > cx)
				cyButton = cx;
			m_rcLeftUpBtn.left = m_rcScrollBar.left;
			m_rcLeftUpBtn.top = m_rcScrollBar.top;
			if (m_bShowLeftUpBtn)
			{
				m_rcLeftUpBtn.right = m_rcScrollBar.left + cx;
				m_rcLeftUpBtn.bottom = m_rcScrollBar.top + cyButton;
			}
			else
			{
				m_rcLeftUpBtn.right = m_rcLeftUpBtn.left;
				m_rcLeftUpBtn.bottom = m_rcLeftUpBtn.top;
			}

			m_rcRightDownBtn.left = m_rcScrollBar.left;
			m_rcRightDownBtn.bottom = m_rcScrollBar.bottom;
			if (m_bShowRightDownBtn)
			{
				m_rcRightDownBtn.top = m_rcScrollBar.bottom - cyButton;
				m_rcRightDownBtn.right = m_rcScrollBar.left + cx;
			}
			else
			{
				m_rcRightDownBtn.top = m_rcRightDownBtn.bottom;
				m_rcRightDownBtn.right = m_rcRightDownBtn.left;
			}

			memset(&m_rcThumb, 0, sizeof(m_rcThumb));
		}
	}
}

HWND CScrollBarEx::SetCapture()
{
	m_bCaptured = TRUE;
	return ::SetCapture(m_hOwnerWnd);
}

BOOL CScrollBarEx::ReleaseCapture()
{
	m_bCaptured = FALSE;
	return ::ReleaseCapture();
}

BOOL CScrollBarEx::IsCaptured()
{
	return m_bCaptured;
}

BOOL CScrollBarEx::StartTrackMouseLeave()
{
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hOwnerWnd;
	return _TrackMouseEvent(&tme);
}

BOOL CScrollBarEx::IsMouseTracking()
{
	return m_bMouseTracking;
}
#include "StdAfx.h"
#include "ISkinControl.h"

ISkinControl::ISkinControl(void)
{
	m_hParentDC = NULL;
	m_bTransparent = FALSE;
	m_colDefText = RGB(128,128,128);
	m_colNormalText = RGB(0,0,0);
	m_colDisableText = RGB(128,128,128);
	m_colReadOnlyText = RGB(0,0,0);
	m_colSelectText = RGB(255,255,255);
	m_colFrameNormal = RGB(0,0,0);
	m_colBack=RGB(255,255,255);
	m_Font = RenderEngine->GetDeaultFont();
	m_dwTextAlign = 0;
}

ISkinControl::~ISkinControl(void)
{
	m_bTransparent = FALSE;
}

void ISkinControl::CalcCenterRect( RECT& rcDest, int cx, int cy, RECT& rcCenter )
{
	int x = ((rcDest.right-rcDest.left) - cx + 1) / 2;
	int y = ((rcDest.bottom-rcDest.top) - cy + 1) / 2;

	rcCenter.left = rcDest.left+x;
	rcCenter.top = rcDest.top+y;
	rcCenter.right = rcCenter.left+cx;
	rcCenter.bottom = rcCenter.top+cy;
}

void ISkinControl::DrawParentWndBg(HWND hWnd, HDC hDC )
{
	if( hWnd == NULL ) return;
	if ( !m_bTransparent ) return;

	HWND hParentWnd = ::GetParent(hWnd);

	CRect rcWindow;
	::GetWindowRect(hWnd,&rcWindow);
	::ScreenToClient(hParentWnd, (LPPOINT)&rcWindow); 
	::ScreenToClient(hParentWnd, ((LPPOINT)&rcWindow)+1);

	::BitBlt(hDC, 0, 0, rcWindow.Width(), rcWindow.Height(), m_hParentDC, rcWindow.left, rcWindow.top, SRCCOPY);
}

void ISkinControl::SetDefText( COLORREF colText )
{
	m_colDefText = colText;
}

void ISkinControl::SetNormalText( COLORREF colText )
{
	m_colNormalText = colText;
}

void ISkinControl::SetDisableText( COLORREF colText )
{
	m_colDisableText = colText;
}

void ISkinControl::SetSelectText( COLORREF colText )
{
	m_colSelectText = colText;
}

void ISkinControl::SetFrameColor( COLORREF colFrame )
{
	m_colFrameNormal = colFrame;
}

BOOL ISkinControl::SetScrollImage( CWnd * pOwn,LPCTSTR pszFileName )
{
	RenderEngine->RemoveImage(m_pImageScroll);
	m_pImageScroll = RenderEngine->GetImage(pszFileName);

	if ( (m_pImageScroll != NULL) && (pOwn != NULL) && (pOwn->GetSafeHwnd() != NULL) )
	{
		ASSERT(m_pImageScroll != NULL);
		if( m_pImageScroll == NULL) return FALSE;

		//ÉèÖÃ¹ö¶¯
		SkinUI_Init(pOwn->GetSafeHwnd(),m_pImageScroll->ImageToBitmap());
	}

	return TRUE;
}

void ISkinControl::RemoveScorll()
{
	RenderEngine->RemoveImage(m_pImageScroll);
}

BOOL ISkinControl::TrackMouseLeave( HWND hWnd )
{
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = hWnd;

	return _TrackMouseEvent(&tme);
}

void ISkinControl::SetCtrlFont( HFONT hFont )
{
	m_Font = hFont;
}

HFONT ISkinControl::GetCtrlFont()
{
	return m_Font;
}

void ISkinControl::SetBackColor( COLORREF colBack )
{
	m_colBack = colBack;
}

void ISkinControl::SetUnTransparent()
{
	m_bTransparent  = false;
}

void ISkinControl::SetTextAlign( WORD wTextAlign )
{
	m_dwTextAlign = wTextAlign;
}

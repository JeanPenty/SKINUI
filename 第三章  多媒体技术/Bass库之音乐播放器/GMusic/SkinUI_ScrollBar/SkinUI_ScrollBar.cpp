//////////////////////////////////////////////////////////////////////////////////

#include "internal.h"
#include "SkinUI_ScrollBar.h"
#include <Shlwapi.h>

#define WIN32_LEAN_AND_MEAN


static TCHAR g_szPropSB[] = TEXT("PROP_SkinUI");


//������涨��������ͼƬ��Դ��СΪ110*110�����Ұ������µĹ�����ͼƬ�Ļ���
static POINT ptArray[6][6] =
{
	{ {0,  0}, {19,  0}, {38,  0}, {57,  0}, {76,  0}, {95,  0} },
	{ {0, 19}, {19, 19}, {38, 19}, {57, 19}, {76, 19}, {95, 19} },
	{ {0, 38}, {19, 38}, {38, 38}, {57, 38}, {76, 38}, {95, 38} },
	{ {0, 57}, {19, 57}, {38, 57}, {57, 57}, {76, 57}, {95, 57} },
	{ {0, 76}, {19, 76}, {38, 76}, {57, 76}, {76, 76}, {95, 76} },
	{ {0, 95}, {19, 95}, {38, 95}, {57, 95}, {76, 95}, {95, 95} }
};


// Public interfaces

//----------------------------------------------------------
// Name : SkinUI_Init()
// Desc : Initialize the skin scrollbar library
//----------------------------------------------------------
BOOL WINAPI SkinUI_Init(HWND hwnd, HBITMAP hBmp)
{
	LPSB    psb;
	DWORD   dwStyle;

	if( !IsWindow(hwnd) ) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;
	}

	if( SkinUI_IsValid(hwnd) )
		return FALSE;

	// Allocates memory
	psb = (LPSB)LocalAlloc(LPTR, sizeof(SB));
	if( psb == NULL )
		return FALSE;

	ZeroMemory(psb, sizeof(SB));

	dwStyle = GetWindowLong(hwnd, GWL_STYLE);

	psb->Horz.cbSize = psb->Vert.cbSize = sizeof(SCROLLINFO);
	psb->Horz.fMask  = psb->Vert.fMask  = SIF_ALL;

	if( dwStyle & WS_HSCROLL )
		GetScrollInfo(hwnd, SB_HORZ, &psb->Horz);

	if( dwStyle & WS_VSCROLL )
		GetScrollInfo(hwnd, SB_VERT, &psb->Vert);
	
	// Is left scrollbar style
	if( GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LEFTSCROLLBAR )
		psb->fLeftScrollBar = TRUE;

	if( !hBmp ) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;
	}

	psb->hBmp = hBmp;

	// Reaplace the window procedure
	psb->hwnd = hwnd;
	psb->pfnOldProc = (WNDPROC)(LONG_PTR)SetWindowLong(hwnd, 
		GWL_WNDPROC, (LONG)(LONG_PTR)SkinUI_Proc);

	psb->fPreventStyleChange = FALSE;
	psb->fTracking = FALSE;

	// Whether richedit control
	TCHAR szClassName[255] = { 0 };
	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if( StrCmpI(szClassName, TEXT("RichEdit20A")) == 0 ||
		StrCmpI(szClassName, TEXT("RichEdit20W")) == 0 ) {
		psb->fRichEdit = TRUE;
	}
	
	// Set the window property 
	if( !SetProp(hwnd, g_szPropSB, (HANDLE)psb) )
		return FALSE;

	// Redraw the window noclient
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER |
            SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_DRAWFRAME);

	return TRUE;
}

//---------------------------------------------------------
// Name : SkinUI_Uninit()
// Desc : Finalize the skin scrollbar library
//---------------------------------------------------------
BOOL WINAPI SkinUI_Uninit(HWND hwnd)
{
	LPSB        psb;
	SCROLLINFO  vsi;
	SCROLLINFO  hsi;
	BOOL        vValid, hValid;
	UINT        vFlags, hFlags;

	if( (psb = SkinUI_GetSB(hwnd)) == NULL )
		return FALSE;

	vsi.cbSize = hsi.cbSize = sizeof(SCROLLINFO);
	vsi.fMask  = hsi.fMask = SIF_ALL | SIF_DISABLENOSCROLL;

	vValid = SkinUI_GetScrollInfo(hwnd, SB_VERT, &vsi);
	vFlags = SkinUI_GetDisableFlags(psb, TRUE);
	hValid = SkinUI_GetScrollInfo(hwnd, SB_HORZ, &hsi);
	hFlags = SkinUI_GetDisableFlags(psb, FALSE);

	// Remove the subclass procedure
	SetWindowLong(hwnd, GWL_WNDPROC, (LONG)(LONG_PTR)psb->pfnOldProc);
	RemoveProp(hwnd, g_szPropSB);
	LocalFree((HLOCAL)psb);


	// Restore system scroll parameters
	if( vValid ) {
		SetScrollInfo(hwnd, SB_VERT, &vsi, TRUE);
		EnableScrollBar(hwnd, SB_VERT, vFlags);
	}

	if( hValid ) {
		SetScrollInfo(hwnd, SB_HORZ, &hsi, TRUE);
		EnableScrollBar(hwnd, SB_HORZ, hFlags);
	}

	return TRUE;
}

//---------------------------------------------------------
// Name : SkinUI_IsValid()
// Desc : Is initialized ??
//---------------------------------------------------------
BOOL WINAPI SkinUI_IsValid(HWND hwnd)
{
	return (SkinUI_GetSB(hwnd) != NULL);
}


//---------------------------------------------------------
// Name : SkinUI_GetScrollInfo()
// Desc : Overload API GetScrollInfo()
//---------------------------------------------------------
BOOL WINAPI SkinUI_GetScrollInfo(HWND hwnd, int fnBar, LPSCROLLINFO lpsi)
{
	LPSB psb;
	LPSCROLLINFO psi;
	BOOL fCopied = FALSE;

	if( !lpsi || lpsi->cbSize != sizeof(SCROLLINFO) )
		return FALSE;

	// Is initialized ?
	if( (psb = SkinUI_GetSB(hwnd)) == NULL )
		return FALSE;

	// If be scrollbar control then call failed
	if( fnBar == SB_HORZ )
		psi = &psb->Horz;
	else if( fnBar == SB_VERT )
		psi = &psb->Vert;
	else if( fnBar == SB_CTL ) 
		return FALSE;

	if( lpsi->fMask & SIF_PAGE ) {
		lpsi->nPage = psi->nPage;
		fCopied = TRUE;
	}

	if( lpsi->fMask & SIF_POS ) {
		lpsi->nPos  = psi->nPos;
		fCopied = TRUE;
	}

	if( lpsi->fMask & SIF_TRACKPOS ) {
		lpsi->nTrackPos = psi->nTrackPos;
		fCopied = TRUE;
	}

	if( lpsi->fMask & SIF_RANGE ) {
		lpsi->nMin = psi->nMin;
		lpsi->nMax = psi->nMax;
		fCopied = TRUE;
	}

	return fCopied;
}




//---------------------------------------------------------
// Name : SkinUI_SetScrollInfo()
// Desc : Overload API SetScrollInfo()
//---------------------------------------------------------
int WINAPI SkinUI_SetScrollInfo(HWND hwnd, int fnBar, LPCSCROLLINFO psi, BOOL fRedraw)
{
	LPSB            psb;
	LPSCROLLINFO    mysi;
	int             nRet;
	DWORD           dwStyle;
	BOOL            fVert;
	UINT            wScroll;
	BOOL            fScroll;
	BOOL            fOldScroll;
	BOOL            bReturnOldPos;

	// if be scrollbar control the call failed
	if( fnBar == SB_CTL )
		return 0;

 	if( (psb = SkinUI_GetSB(hwnd)) == NULL )
		return 0;

	if( fRedraw )
		fRedraw = IsWindowVisible(hwnd);

	fVert         = (fnBar == SB_VERT);
	bReturnOldPos = (psi->fMask & SIF_POS);
	dwStyle       = GetWindowLong(hwnd, GWL_STYLE);
	wScroll       = fVert ? WS_VSCROLL : WS_HSCROLL;

	fScroll = fOldScroll = (dwStyle & wScroll) ? TRUE : FALSE;
	
	// Don't do anything if we're setting position of a nonexistent scroll bar.
	if( !(psi->fMask & SIF_RANGE) && !fOldScroll )
		return 0;

	mysi = (fVert ? &psb->Vert : &psb->Horz);

	if( !SkinUI_SetSBParms(mysi, *psi, &fScroll, &nRet, bReturnOldPos) &&
		!(psi->fMask & SIF_DISABLENOSCROLL) ) {
		if( fOldScroll && fRedraw )
			goto redrawAfterSet;
		return nRet;
	}

	if( fScroll )
		psb->style |= wScroll;
	else
		psb->style &= ~wScroll;

	// Keep the owner window scroll style
	SetWindowLong(hwnd, GWL_STYLE, dwStyle | wScroll);

	if( psi->fMask & SIF_DISABLENOSCROLL ) {
		if( fOldScroll ) {
			fScroll = ((int)mysi->nPage <= (mysi->nMax - mysi->nMin));
			psb->style |= wScroll;
			SetWindowLong(hwnd, GWL_STYLE, dwStyle | wScroll);
			SkinUI_EnableArrows(psb, fnBar, fScroll ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH);
		}
	}
	else if( fOldScroll ^ fScroll ) {
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER |
            SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_DRAWFRAME);
		return nRet;
	}

	if( fScroll && fRedraw ) {

redrawAfterSet:
		if(dwStyle & wScroll) {
			HDC hDC = GetWindowDC(hwnd);
			SkinUI_DrawThumb(psb, hDC, fVert);
			ReleaseDC(hwnd, hDC);
		}
		else {
			if( SkinUI_IsScrollInfoActive(psi) )
				SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER |
				SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_DRAWFRAME);
		}
	}

	return mysi->nPos; //lres;
}


//---------------------------------------------------------
// Name : SkinUI_GetScrollPos()
// Desc : Overload API GetScrollPos()
//---------------------------------------------------------
int WINAPI SkinUI_GetScrollPos(HWND hwnd, int nBar)
{
	LPSB psb;
	int nPos;
	if( !(psb = SkinUI_GetSB(hwnd)) )
		return FALSE;

	if( nBar == SB_HORZ )
		nPos = psb->Horz.nPos;
	else if( nBar == SB_VERT )
		nPos = psb->Vert.nPos;

	return nPos;
}


//---------------------------------------------------------
// Name : SkinUI_SetScrollPos()
// Desc : Overload API SetScrollPos()
//---------------------------------------------------------
int WINAPI SkinUI_SetScrollPos(HWND hwnd, int nBar, int nPos, BOOL fRedraw)
{
	LPSB psb;
	LPSCROLLINFO psi;
	int nOldPos;

	if( (psb = SkinUI_GetSB(hwnd)) == NULL)
		return FALSE;

	if( nBar == SB_HORZ )
		psi = &psb->Horz;
	else if( nBar == SB_VERT )
		psi = &psb->Vert;
	else
		return FALSE;

	nOldPos = psi->nPos;
	psi->nPos = nPos;

	if( fRedraw ) {
		HDC hDC = GetWindowDC(hwnd);
		SkinUI_DrawScrollBar(psb, hDC, (nBar == SB_VERT) );
		ReleaseDC(hwnd, hDC);
	}

	return nOldPos;
}


//---------------------------------------------------------
// Name : SkinUI_GetScrollRange()
// Desc : Overload API GetScrollRange()
//---------------------------------------------------------
BOOL WINAPI SkinUI_GetScrollRange(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
	LPSB psb;
	LPSCROLLINFO psi;
	if( !lpMinPos || !lpMaxPos )
		return FALSE;

	if( (psb = SkinUI_GetSB(hwnd)) == NULL )
		return FALSE;

	if( nBar == SB_HORZ )
		psi = &psb->Horz;
	else if( nBar == SB_VERT )
		psi = &psb->Vert;

	*lpMinPos = psi->nMin;
	*lpMaxPos = psi->nMax;

	return TRUE;
}


//---------------------------------------------------------
// Name : SkinUI_SetScrollRange()
// Desc : Overload API SetScrollRange()
//---------------------------------------------------------
BOOL WINAPI SkinUI_SetScrollRange(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL fRedraw)
{
	LPSB psb;
	LPSCROLLINFO psi;

	if( !(psb = SkinUI_GetSB(hwnd)) )
		return FALSE;

	if( nBar == SB_HORZ )
		psi = &psb->Horz;
	else if( nBar == SB_VERT )
		psi = &psb->Vert;

	psi->nMin = nMinPos;
	psi->nMax = nMaxPos;

	if(nMinPos == 0 && nMaxPos == 0)
		SkinUI_ShowScrollBar(hwnd, nBar, FALSE);

	if( fRedraw ) {
		HDC hDC = GetWindowDC(hwnd);
		SkinUI_DrawScrollBar(psb, hDC, (nBar == SB_VERT) );
		ReleaseDC(hwnd, hDC);
	}

	return TRUE;
}


//---------------------------------------------------------
// Name : SkinUI_ShowScrollBar()
// Desc : Overload API ShowScrollBar()
//---------------------------------------------------------
BOOL WINAPI SkinUI_ShowScrollBar(HWND hwnd, int wBar, BOOL fShow)
{
	BOOL fChanged = FALSE;
	DWORD dwStyle, dwNew;

	switch( wBar )
	{
	case SB_CTL:
		ShowWindow(hwnd, fShow ? SW_SHOW : SW_HIDE);
		break;
	case SB_HORZ:
		dwNew = WS_HSCROLL;
		break;
	case SB_VERT:
		dwNew = WS_VSCROLL;
		break;
	case SB_BOTH:
		dwNew = WS_HSCROLL | WS_VSCROLL;
		break;
	}

	dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if( !fShow ) {
		if( dwStyle & dwNew ) {
			fChanged = TRUE;
			dwStyle &= ~dwNew;
		}
	}
	else {
		if( (dwStyle & dwNew) != dwNew ) {
			fChanged = TRUE;
			dwStyle |= dwNew;
		}
	}

	if( fChanged ) {
		SetWindowLong(hwnd, GWL_STYLE, dwStyle);
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER |
            SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	}

	return TRUE;
}


//---------------------------------------------------------
// Name : SkinUI_EnableScrollBar()
// Desc : Overload API EnableScrollBar()
//---------------------------------------------------------
BOOL WINAPI SkinUI_EnableScrollBar(HWND hwnd, UINT wSBflags, UINT wArrows)
{
	LPSB psb;
	if( !(psb = SkinUI_GetSB(hwnd)) )
		return FALSE;

	if( wSBflags == SB_CTL )
		return FALSE;
	
	return SkinUI_EnableArrows(psb, wSBflags, wArrows);
}

// Internal Function


//---------------------------------------------------------
// Name : SkinUI_SetSBParms()
// Desc : Set scroll parameters
//---------------------------------------------------------
BOOL SkinUI_SetSBParms(LPSCROLLINFO psi, SCROLLINFO si, BOOL* pfScroll, int* plres, BOOL bOldPos)
{
	BOOL fChanged = FALSE;
	if( bOldPos )
		*plres = psi->nPos;

	if( si.fMask & SIF_RANGE ) {
		if( si.nMax < si.nMin )
			si.nMax = si.nMin;

		if( si.nMax != psi->nMax || si.nMin != psi->nMin ) {
			psi->nMax = si.nMax;
			psi->nMin = si.nMin;

			if( !(si.fMask & SIF_PAGE) ) {
				si.fMask |= SIF_PAGE;
				si.nPage = psi->nPage;
			}

			if( !(si.fMask & SIF_POS) ) {
				si.fMask |= SIF_POS;
				si.nPos  = psi->nPos;
			}

			fChanged = TRUE;
		}
	}

	if( si.fMask & SIF_PAGE ) {
		UINT nMaxPage = abs( psi->nMax - psi->nMin ) + 1;
		if( si.nPage > nMaxPage )
			si.nPage = nMaxPage;
		
		if( psi->nPage != si.nPage ) {
			psi->nPage = si.nPage;

			if( !(si.fMask & SIF_POS) ) {
				si.fMask |= SIF_POS;
				si.nPos  = psi->nPos;
			}

			fChanged = TRUE;
		}
	}

	if( si.fMask & SIF_POS ) {
		int nMaxPos = psi->nMax - ((psi->nPage) ? psi->nPage - 1 : 0);
		if( si.nPos < psi->nMin )
			si.nPos = psi->nMin;
		else if( si.nPos > nMaxPos )
			si.nPos = nMaxPos;

		if( psi->nPos != si.nPos ) {
			psi->nPos = si.nPos;
			fChanged = TRUE;
		}
	}

	if( si.fMask & SIF_TRACKPOS ) {
		if( psi->nTrackPos != si.nTrackPos ) {
			psi->nTrackPos = si.nTrackPos;
			fChanged = TRUE;
		}
	}

	if( !bOldPos )
		*plres = psi->nPos; // Return the new pos

	if( si.fMask & SIF_RANGE ) {
		if( *pfScroll = (psi->nMin != psi->nMax) )
			goto CheckPage;
	}
	else if( si.fMask & SIF_PAGE ) {
CheckPage:
		*pfScroll = ( (int)psi->nPage <= (psi->nMax - psi->nMin) );
	}

	return fChanged;
}


//---------------------------------------------------------
// Name : SkinUI_EnableArrows()
// Desc : Enable or Disable scrollbar arrows
//---------------------------------------------------------
BOOL SkinUI_EnableArrows(LPSB psb, int nBar, UINT wArrows)
{
	HDC hDC;
	UINT uOldFlags;
	BOOL bRetValue = FALSE;

	if( psb == NULL )
		return FALSE;

	uOldFlags = psb->flags;
	if( (hDC = GetWindowDC(psb->hwnd)) == NULL )
		return FALSE;

	// Enable or disable horizontal scrollbar
	if( nBar == SB_HORZ || nBar == SB_BOTH ) {
		if( wArrows == ESB_ENABLE_BOTH )
			psb->flags &= ~ESB_DISABLE_BOTH;
		else
			psb->flags |= wArrows;

		if( uOldFlags != psb->flags ) {
			bRetValue = TRUE;
			if( GetWindowLong(psb->hwnd, GWL_STYLE ) & WS_HSCROLL )
				SkinUI_DrawScrollBar(psb, hDC, FALSE);
		}
	}

	// Enable or disable vertical scrollbar
	if( nBar == SB_VERT || nBar == SB_BOTH ) {
		if( wArrows == ESB_ENABLE_BOTH )
			psb->flags &= ~(ESB_DISABLE_BOTH << 2);
		else
			psb->flags |= (wArrows << 2);

		if( uOldFlags != psb->flags ) {
			bRetValue = TRUE;
			if( GetWindowLong(psb->hwnd, GWL_STYLE ) & WS_VSCROLL )
				SkinUI_DrawScrollBar(psb, hDC, TRUE);
		}
	}

	ReleaseDC(psb->hwnd, hDC);

	return bRetValue;
}


//---------------------------------------------------------
// Name : SkinUI_GetDisableFlags()
// Desc : Get scrollbar disable flags
//---------------------------------------------------------
UINT SkinUI_GetDisableFlags(LPSB psb, BOOL fVert)
{
	return (fVert ? (psb->flags & 0x000c) >> 2 : psb->flags & 0x0003); 
}


//---------------------------------------------------------
// Name : SkinUI_GetSB()
// Desc : Get the skin scrollbar data structure
//---------------------------------------------------------
LPSB SkinUI_GetSB(HWND hwnd)
{
	return (LPSB)GetProp(hwnd, g_szPropSB);
}


//---------------------------------------------------------
// Name : SkinUI_IsScrollInfoActive()
// Desc : Check scroll information whether active
//---------------------------------------------------------
BOOL SkinUI_IsScrollInfoActive(LPCSCROLLINFO lpsi)
{
	if( lpsi->nPage > (UINT)lpsi->nMax || lpsi->nMax <= lpsi->nMin || lpsi->nMax == 0 )
		return FALSE;
	else
		return TRUE;
}


//----------------------------------------------------------
// Name : SkinUI_GetSizeBoxRect()
// Desc : Get the size box rect
//----------------------------------------------------------
BOOL SkinUI_GetSizeBoxRect(LPSB psb, LPRECT lprc)
{
	DWORD dwStyle;
	RECT  rect;

	SetRectEmpty(lprc);
	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);
	if( (dwStyle & WS_HSCROLL) && (dwStyle & WS_VSCROLL) ) {
		GetClientRect(psb->hwnd, &rect);
		ClientToScreen(psb->hwnd, (LPPOINT)&rect);
		ClientToScreen(psb->hwnd, ((LPPOINT)&rect)+1);

		// calculate left scroll style of size box rect 
		if( psb->fLeftScrollBar ) {
			lprc->left = rect.left - GetSystemMetrics(SM_CXVSCROLL);
			lprc->right = rect.left;
		}
		else {
			lprc->left = rect.right;
			lprc->right = rect.right + GetSystemMetrics(SM_CXVSCROLL);
		}

		lprc->top   = rect.bottom;
		lprc->bottom= rect.bottom + GetSystemMetrics(SM_CYHSCROLL);
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------
// Name : SkinUI_GetScrollBarRect()
// Desc : Get the scrollbar rect
//----------------------------------------------------------
BOOL SkinUI_GetScrollBarRect(LPSB psb, BOOL fVert, LPRECT lprc)
{
	RECT   rect;
	DWORD  dwStyle;

	if( !psb || !lprc )
		return FALSE;
	SetRectEmpty(lprc);
	GetClientRect(psb->hwnd, &rect);
	ClientToScreen(psb->hwnd, (LPPOINT)&rect);
	ClientToScreen(psb->hwnd, ((LPPOINT)&rect)+1);

	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);

	if( fVert ) {
		if( psb->fLeftScrollBar ) {
			lprc->right = lprc->left = rect.left;
			if( dwStyle & WS_VSCROLL )
				lprc->left -= GetSystemMetrics(SM_CXVSCROLL);
		}
		else {
			lprc->right = lprc->left = rect.right;
			if( dwStyle & WS_VSCROLL )
				lprc->right += GetSystemMetrics(SM_CXVSCROLL);
		}
		lprc->top = rect.top;
		lprc->bottom = rect.bottom;
	}
	else {
		lprc->top = lprc->bottom = rect.bottom;
		if( dwStyle & WS_HSCROLL )
			lprc->bottom += GetSystemMetrics(SM_CYHSCROLL);
		lprc->left = rect.left;
		lprc->right = rect.right;
	}

	return TRUE;
}


//----------------------------------------------------------
// Name : SkinUI_GetThumbRect()
// Desc :
//----------------------------------------------------------

BOOL SkinUI_GetThumbRect(LPSB psb, LPRECT lprc, BOOL fVert)
{
	if( !psb || !lprc )
		return FALSE;
	SBCALC   sbc;
	RECT     rect;
	SkinUI_SBCalc(psb, &sbc, fVert);
	GetWindowRect(psb->hwnd, &rect);
	if( fVert )
		SetRect(lprc, sbc.pxLeft, sbc.pxThumbTop, sbc.pxRight, sbc.pxThumbBottom);
	else
		SetRect(lprc, sbc.pxThumbLeft, sbc.pxTop, sbc.pxThumbRight, sbc.pxBottom);

	OffsetRect(lprc, -rect.left, -rect.top);
	return TRUE;
}

//----------------------------------------------------------
// Name : SkinUI_GetGrooveRect()
// Desc :
//----------------------------------------------------------
BOOL SkinUI_GetGrooveRect(LPSB psb, LPRECT lprc, BOOL fVert)
{
	if( !psb || !lprc )
		return FALSE;
	SBCALC   sbc;
	RECT     rect;
	SkinUI_SBCalc(psb, &sbc, fVert);
	GetWindowRect(psb->hwnd, &rect);
	if( fVert )
		SetRect(lprc, sbc.pxLeft, sbc.pxUpArrow, sbc.pxRight, sbc.pxDownArrow);
	else
		SetRect(lprc, sbc.pxUpArrow, sbc.pxTop, sbc.pxDownArrow, sbc.pxBottom);
	OffsetRect(lprc, -rect.left, -rect.top);
	return TRUE;
}


//----------------------------------------------------------
// Name : SkinUI_DrawSizeBox()
// Desc : Draw the size box
//----------------------------------------------------------

BOOL SkinUI_DrawSizeBox(LPSB psb, HDC hDC)
{
	HDC     hMemDC;
	HBITMAP hOldBmp;

	RECT rect, rc;
	GetWindowRect(psb->hwnd, &rect);
	SkinUI_GetSizeBoxRect(psb, &rc);
	OffsetRect(&rc, -rect.left, -rect.top);

	hMemDC = CreateCompatibleDC(NULL);
	hOldBmp = (HBITMAP)SelectObject(hMemDC, psb->hBmp);

	BitBlt(hDC, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 38, 57, SRCCOPY);

	// Release GDI object
	SelectObject(hMemDC, hOldBmp);
	DeleteDC(hMemDC);

	return TRUE;
}


//----------------------------------------------------------
// Name : SkinUI_DrawGroove()
// Desc :
//----------------------------------------------------------
BOOL SkinUI_DrawGroove(LPSB psb, HDC hdc, LPRECT lprc, BOOL fVert)
{
	if( !hdc || !lprc || IsRectEmpty(lprc) )
		return FALSE;

	HDC      hbmpDC;
	HBITMAP  hOldBmp;
	POINT    pt;
	int      nMode;
	hbmpDC = CreateCompatibleDC(hdc);
	hOldBmp = (HBITMAP)SelectObject(hbmpDC, psb->hBmp);

	if( fVert )
		pt = ptArray[0][4];
	else
		pt = ptArray[3][4];

	nMode = SetStretchBltMode(hdc, HALFTONE);
	StretchBlt(hdc, lprc->left, lprc->top, lprc->right - lprc->left, 
		lprc->bottom - lprc->top, hbmpDC, pt.x, pt.y, 16, 16, SRCCOPY);
	SetStretchBltMode(hdc, nMode);

	SelectObject(hbmpDC, hOldBmp);
	DeleteDC(hbmpDC);

	return TRUE;
}


//----------------------------------------------------------
// Name : SkinUI_DrawScrollBar()
// Desc : Draw the scrollbar
//----------------------------------------------------------
void SkinUI_DrawScrollBar(LPSB psb, HDC hDC, BOOL fVert)
{
	RECT rcGroove;

	SkinUI_GetGrooveRect(psb, &rcGroove, fVert);
	SkinUI_DrawGroove(psb, hDC, &rcGroove, fVert);

	if( fVert ) {
		// Draw the arrow
		SkinUI_DrawArrow(psb, hDC, fVert, HTSCROLL_LINEUP, 0);
		SkinUI_DrawArrow(psb, hDC, fVert, HTSCROLL_LINEDOWN, 0);
		
		// Draw the thumb
		if( !SkinUI_IsScrollInfoActive(&psb->Vert) )
			return ;
		SkinUI_DrawThumb(psb, hDC, fVert);
	}
	else {
		SkinUI_DrawArrow(psb, hDC, fVert, HTSCROLL_LINEUP, 0);
		SkinUI_DrawArrow(psb, hDC, fVert, HTSCROLL_LINEDOWN, 0);

		if( !SkinUI_IsScrollInfoActive(&psb->Horz) )
			return ;
		SkinUI_DrawThumb(psb, hDC, fVert);
	}
}


//----------------------------------------------------------
// Name : SkinUI_DrawArrow()
// Desc : Draw the scrollbar arrow button
//----------------------------------------------------------
BOOL SkinUI_DrawArrow(LPSB psb, HDC hdc, BOOL fVert, int nArrow, UINT uState)
{
	RECT      	rect, rc;
	SBCALC    	sbc;
	HDC       	hMemDC;
	HBITMAP   	hOldBmp;
	int       	x, y;
	POINT     	pt;

	GetWindowRect(psb->hwnd, &rect);
	SkinUI_SBCalc(psb, &sbc, fVert);

	if( uState == 0 )
		uState = SkinUI_GetState(psb, fVert, nArrow);

	hMemDC  = CreateCompatibleDC(hdc);
	hOldBmp = (HBITMAP)SelectObject(hMemDC, psb->hBmp);

	switch( nArrow )
	{
		// up or left arrow
	case HTSCROLL_LINEUP:
		if( fVert ) {
			x = 0; y = 0;
			SetRect(&rc, sbc.pxLeft, sbc.pxTop, sbc.pxRight, sbc.pxUpArrow);
		}
		else {
			x = 3; y = 0;
			SetRect(&rc, sbc.pxLeft, sbc.pxTop, sbc.pxUpArrow, sbc.pxBottom);
		}
		break;
		// right or down arrow
	case HTSCROLL_LINEDOWN:
		if( fVert ) {
			x = 0; y = 1;
			SetRect(&rc, sbc.pxLeft, sbc.pxDownArrow, sbc.pxRight, sbc.pxBottom);
		}
		else {
			x = 3; y = 1;
			SetRect(&rc, sbc.pxDownArrow, sbc.pxTop, sbc.pxRight, sbc.pxBottom);
		}
		break;
	}

	OffsetRect(&rc, -rect.left, -rect.top);

	switch( uState )
	{
	case SB_STATE_NORMAL:
		break;
	case SB_STATE_HOTTRACKED:
		x += 1;
		break;
	case SB_STATE_PRESSED:
		x += 2;
		break;
	case SB_STATE_DISABLED:
		break;
	}
	pt = ptArray[x][y];

	BitBlt(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
		hMemDC, pt.x, pt.y, SRCCOPY);

	SelectObject(hMemDC, hOldBmp);
	DeleteDC(hMemDC);

	return TRUE;
	
}

//----------------------------------------------------------
// Name : SkinUI_DrawThumb()
// Desc : Draw the thumb
//----------------------------------------------------------
void SkinUI_DrawThumb(LPSB psb, HDC hdc, BOOL fVert)
{
	SBCALC   	sbc;
	RECT     	rc, rect;
	HDC      	hSrcDC;
	HDC      	memDC;
	HBITMAP  	hOldBmp;
	HBITMAP  	hMemBitmap, hOldBitmap;
	UINT     	uState;
	int      	cx, cy;
	POINT    	pt, pt1;
	
	uState = SkinUI_GetState(psb, fVert, HTSCROLL_THUMB);

	SkinUI_SBCalc(psb, &sbc, fVert);
	GetWindowRect(psb->hwnd, &rect);

	// Chack scrollbar of size whether valid
	if( sbc.pxTop >= sbc.pxBottom || sbc.pxLeft >= sbc.pxRight )
		return ;

	// Draw the groove only
	if( (sbc.pxDownArrow - sbc.pxUpArrow) < (sbc.pxThumbBottom - sbc.pxThumbTop) ||
		uState == SB_STATE_DISABLED ) {
		SkinUI_GetGrooveRect(psb, &rc, fVert);
		SkinUI_DrawGroove(psb, hdc, &rc, fVert);
		return ;
	}

	// Padding the groove part
	if( sbc.pxUpArrow < sbc.pxThumbTop ) {
		if( fVert )
			SetRect(&rc, sbc.pxLeft, sbc.pxUpArrow,  sbc.pxRight, sbc.pxThumbTop);
		else
			SetRect(&rc, sbc.pxUpArrow, sbc.pxTop, sbc.pxThumbTop, sbc.pxBottom);
		OffsetRect(&rc, -rect.left, -rect.top);
		SkinUI_DrawGroove(psb, hdc, &rc, fVert);
	}

	if( sbc.pxThumbBottom < sbc.pxDownArrow ) {
		if( fVert )
			SetRect(&rc, sbc.pxLeft, sbc.pxThumbBottom, sbc.pxRight, sbc.pxDownArrow);
		else
			SetRect(&rc, sbc.pxThumbBottom, sbc.pxTop, sbc.pxDownArrow, sbc.pxBottom);
		OffsetRect(&rc, -rect.left, -rect.top);
		SkinUI_DrawGroove(psb, hdc, &rc, fVert);
	}

	// Draw the thumb use memory dc

	// Select scrollbar bitmap resource to dc
	hSrcDC   = CreateCompatibleDC(hdc);
	hOldBmp  = (HBITMAP)SelectObject(hSrcDC, psb->hBmp);

	// get the thumb rectangle
	SkinUI_GetThumbRect(psb, &rc, fVert);
	cx = rc.right - rc.left;
	cy = rc.bottom - rc.top;
	RECT rcMemDC = {0, 0, rc.right-rc.left, rc.bottom-rc.top};

	// create the memory dc
	memDC = CreateCompatibleDC(hdc);
	hMemBitmap = CreateCompatibleBitmap(hdc, cx, cy);
	hOldBitmap = (HBITMAP)SelectObject(memDC, hMemBitmap);
	SetBkColor(memDC, 0xFFFFFF);
	ExtTextOut(memDC, 0, 0, ETO_OPAQUE, &rcMemDC, NULL, 0, NULL);

	// Select state bitmap part
	switch( uState )
	{
	case SB_STATE_NORMAL:
		pt  = fVert ? ptArray[0][2] : ptArray[3][2];
		pt1 = fVert ? ptArray[0][3] : ptArray[3][3];
		break;
	case SB_STATE_HOTTRACKED:
		pt  = fVert ? ptArray[1][2] : ptArray[4][2];
		pt1 = fVert ? ptArray[1][3] : ptArray[4][3];
		break;
	case SB_STATE_PRESSED:
		pt  = fVert ? ptArray[2][2] : ptArray[5][2];
		pt1 = fVert ? ptArray[2][3] : ptArray[5][3];
		break;
	case SB_STATE_DISABLED:
		break;
	}

	if ( fVert ) {
		for( int i= 4; i < cy - 4; i += 8 )
			BitBlt(memDC, 0,  i, cx, 8, hSrcDC, pt.x, pt.y + 4, SRCCOPY);

		BitBlt(memDC, 0, 0, cx, 4, hSrcDC, pt.x, pt.y, SRCCOPY);
		BitBlt(memDC, 0, cy - 4, cx, 4, hSrcDC, pt.x, (pt.y + 16) - 4, SRCCOPY);
		if( cy > 16 + 8 ) {
			int y = (cy - 16) / 2;
			BitBlt(memDC, 0, y, cx, 16, hSrcDC, pt1.x, pt1.y, SRCCOPY);
		}
	}
	else {
		for( int i=4; i < cx - 4; i += 8 )
			BitBlt(memDC, i, 0, 8, cy, hSrcDC, pt.x + 4, pt.y, SRCCOPY);
		BitBlt(memDC, 0, 0, 4, cy, hSrcDC, pt.x, pt.y, SRCCOPY);
		BitBlt(memDC, cx - 4, 0, 4, cy, hSrcDC, (pt.x + 16) - 4, pt.y, SRCCOPY);
		if( cx > 16 + 8 ) {
			int x = (cx - 16) / 2;
			BitBlt(memDC, x, 0, 16, cy, hSrcDC, pt1.x, pt1.y, SRCCOPY);
		}
	}

	BitBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, memDC, 0,0, SRCCOPY);
	
	// Release the memory DC
	SelectObject(memDC, hOldBitmap);
	DeleteDC(memDC);
	DeleteObject(hMemBitmap);

	SelectObject(hSrcDC, hOldBmp);
	DeleteDC(hSrcDC);
}

//----------------------------------------------------------
// Name : SkinUI_HitTest()
// Desc : HitTest scrollbar items
//----------------------------------------------------------
UINT SkinUI_HitTest(LPSB psb, BOOL fVert, POINT pt)
{
	SBCALC  sbc;
	UINT    disFlags;
	int     x;

	SkinUI_SBCalc(psb, &sbc, fVert);

	if( pt.x < sbc.pxLeft  || pt.y < sbc.pxTop || 
		pt.x > sbc.pxRight || pt.y > sbc.pxBottom )
		return HTSCROLL_NONE;

	disFlags = SkinUI_GetDisableFlags(psb, fVert);
	x = fVert ? pt.y : pt.x;

	if( x < sbc.pxUpArrow ) {
		if( disFlags & ESB_DISABLE_BOTH || disFlags & ESB_DISABLE_LTUP )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_LINEUP;
	}
	else if( x > sbc.pxUpArrow && x < sbc.pxThumbTop ) {
		if( disFlags & ESB_DISABLE_BOTH || disFlags & ESB_DISABLE_LTUP )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_PAGEUP;
	}
	else if( (x >= sbc.pxThumbTop && x <= sbc.pxThumbBottom) &&
		(sbc.pxThumbTop > 0 && sbc.pxThumbBottom > sbc.pxThumbTop) ) {
		return HTSCROLL_THUMB;
	}
	else if( x > sbc.pxThumbBottom && x < sbc.pxDownArrow ) {
		if( disFlags & ESB_DISABLE_BOTH || disFlags & ESB_DISABLE_RTDN )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_PAGEDOWN;
	}
	else if( x >= sbc.pxDownArrow ) {
		if( disFlags & ESB_DISABLE_BOTH || disFlags & ESB_DISABLE_RTDN )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_LINEDOWN;
	}

	return HTSCROLL_NONE;
}


//----------------------------------------------------------
// Name : SkinUI_SBCalc()
// Desc : Calc the scrollbar items position and size
//----------------------------------------------------------
void SkinUI_SBCalc(LPSB psb, LPSBCALC lpcalc, BOOL fVert)
{
	RECT        	rcBar;             // the scrollbar rect
	int         	nRange;            // the scroll range
	int         	nWorkingsize;      // the scroll working size
	int         	nArrowsize;        // the arrow button of size 
	int         	nThumbsize;        // the thumb of size  
	int         	nStart;            // the thumb of start position 
	int         	nThumbpos;         // the thumn of current position
	SCROLLINFO* 	psi;

	SkinUI_GetScrollBarRect(psb, fVert, &rcBar);

	lpcalc->pxLeft   = rcBar.left;
	lpcalc->pxTop    = rcBar.top;
	lpcalc->pxRight  = rcBar.right;
	lpcalc->pxBottom = rcBar.bottom;

	if( fVert ) {
		psi = &psb->Vert;
		nArrowsize   = GetSystemMetrics(SM_CYVSCROLL);
		nWorkingsize = (rcBar.bottom - rcBar.top) - nArrowsize * 2;
		nStart = rcBar.top + nArrowsize;
		
		lpcalc->pxUpArrow = rcBar.top + nArrowsize;
		lpcalc->pxDownArrow = rcBar.bottom - nArrowsize;
	}
	else {
		psi = &psb->Horz;
		nArrowsize   = GetSystemMetrics(SM_CXHSCROLL);
		nWorkingsize = (rcBar.right - rcBar.left) - nArrowsize * 2;
		nStart = rcBar.left + nArrowsize;

		lpcalc->pxUpArrow = rcBar.left + nArrowsize;
		lpcalc->pxDownArrow = rcBar.right - nArrowsize;
	}

	nRange = (psi->nMax - psi->nMin) + 1;
	if( nRange > 0 && SkinUI_IsScrollInfoActive(psi)) {
		nThumbsize = MulDiv(psi->nPage, nWorkingsize, nRange);
		if( nThumbsize < SB_MINTHUMB_SIZE )
			nThumbsize = SB_MINTHUMB_SIZE;
		int pagesize = max(1, psi->nPage);

		nThumbpos = MulDiv(psi->nPos - psi->nMin, nWorkingsize - nThumbsize, nRange - pagesize);
		
		if( nThumbpos < 0 )
			nThumbpos = 0;

		if( nThumbpos >= nWorkingsize - nThumbsize )
			nThumbpos =  nWorkingsize - nThumbsize;

		nThumbpos += nStart;
		lpcalc->pxThumbTop = nThumbpos;
		lpcalc->pxThumbBottom = nThumbpos + nThumbsize;
	}
	else {
		lpcalc->pxThumbTop = 0;
		lpcalc->pxThumbBottom = 0;
	}	
}

//---------------------------------------------------------
// Name : SkinUI_TrackThumb()
// Desc : Track the scroll thumb
//---------------------------------------------------------
BOOL SkinUI_TrackThumb(LPSB psb, BOOL fVert, POINT pt)
{
	SBCALC        	sbclc;
	int           	nPos;
	int           	nThumbpos;
	int           	nRange;
	int           	nThumbsize;
	int           	nWorksize;
	LPSCROLLINFO  	psi;

	SkinUI_SBCalc(psb, &sbclc, fVert);
	
	if( fVert ) {
		psi = &psb->Vert;
		nThumbpos = pt.y -  psb->nOffsetPoint;
	}
	else {
		psi = &psb->Horz;
		nThumbpos = pt.x - psb->nOffsetPoint;
	}

	nPos       = 0;
	nThumbpos -= sbclc.pxUpArrow;
	nThumbsize = sbclc.pxThumbBottom - sbclc.pxThumbTop;
	nWorksize  = sbclc.pxDownArrow - sbclc.pxUpArrow;
	nRange     = (psi->nMax - psi->nMin) + 1;

	if( nThumbpos < 0 )
		nThumbpos = 0;
	if( nThumbpos > nWorksize - nThumbsize)
		nThumbpos = nWorksize - nThumbsize;

	if( nRange > 0 )
		nPos = MulDiv(nThumbpos, nRange - psi->nPage, nWorksize - nThumbsize);

	// Send the scroll message to window !!!
	if( psi->nPos != nPos ) {
		psi->nTrackPos = nPos;
		psb->nTrackPos = nPos;
		// NOTE: 2008-12-24
		// Not use the SB_THUMBTRACK flag that because of 
		// the RichEdit cannot receving the WM_MOUSEMOVE message
		if( psb->fRichEdit ) {
			DoScrollMsg(psb->hwnd, /*SB_THUMBTRACK*/SB_THUMBPOSITION, nPos, fVert);
		}
		else {
			DoScrollMsg(psb->hwnd, SB_THUMBTRACK, nPos, fVert);
		}
	}

	return TRUE;
}



//---------------------------------------------------------
// Name : SkinUI_GetState()
// Desc :
//---------------------------------------------------------
UINT SkinUI_GetState(LPSB psb, BOOL fVert, UINT nHit)
{
	BOOL 	fHotTracked;
	BOOL 	fPressed;
	BOOL 	fDisabled;
	UINT 	disFlags;
	UINT 	state;

	if( nHit == HTSCROLL_NONE )
		return 0;

	fHotTracked = fPressed = fDisabled = FALSE;

	disFlags = SkinUI_GetDisableFlags(psb, fVert);
	switch( nHit ) {
	case HTSCROLL_LINEUP:
		fDisabled = (disFlags & ESB_DISABLE_BOTH || disFlags & ESB_DISABLE_UP);
		break;
	case HTSCROLL_LINEDOWN:
		fDisabled = (disFlags & ESB_DISABLE_BOTH || disFlags & ESB_DISABLE_DOWN);
		break;
	case HTSCROLL_THUMB:
		fDisabled = (disFlags & ESB_DISABLE_BOTH);
		break;
	}

	if( nHit == psb->nLastCode && fVert == psb->fLastVert )
		fHotTracked = TRUE;

	if( !fDisabled && psb->fTracking && fHotTracked )
		fPressed = TRUE;

	if( fDisabled )
		state = SB_STATE_DISABLED;
	else if( fPressed )
		state = SB_STATE_PRESSED;
	else if( fHotTracked )
		state = SB_STATE_HOTTRACKED;
	else
		state = SB_STATE_NORMAL;
	
	return state;
}

//----------------------------------------------------------
// Name : SkinUI_Track()
// Desc :
//----------------------------------------------------------
void SkinUI_Track(LPSB psb, BOOL fVert, UINT nHit, POINT pt)
{
	UINT            disFlags;
	LPSCROLLINFO    psi;
	WORD            wSBCode;

	psi = fVert ? &psb->Vert : &psb->Horz;
	disFlags = SkinUI_GetDisableFlags(psb, fVert);

	switch( nHit )
	{
	case HTSCROLL_THUMB:
		SBCALC sbclc;
		SkinUI_SBCalc(psb, &sbclc, fVert);
		psi->nTrackPos    = psi->nPos;
		psb->nOffsetPoint = (fVert ? pt.y : pt.x) - sbclc.pxThumbTop;
		break;

	case HTSCROLL_LINEUP:
		wSBCode = SB_LINEUP;
		goto DoScroll;

	case HTSCROLL_LINEDOWN:
		wSBCode = SB_LINEDOWN;
		goto DoScroll;

	case HTSCROLL_PAGEDOWN:
		wSBCode = SB_PAGEDOWN;
		goto DoScroll;

	case HTSCROLL_PAGEUP:
		wSBCode = SB_PAGEUP;
DoScroll:
		psb->nScrollTimerMsg = MAKELONG(fVert ? WM_VSCROLL : WM_HSCROLL, wSBCode);
		DoScrollMsg(psb->hwnd, wSBCode, 0, fVert);
		SetTimer(psb->hwnd, SB_TIMER_DELAY, SB_SCROLL_DELAY, NULL);
		break;
	default:
		return;
	}

	psb->nTrackCode  = nHit;
	psb->fTrackVert  = fVert;
	psb->fTracking   = TRUE;

	SkinUI_HotTrack(psb, nHit, fVert, TRUE);
	SetCapture(psb->hwnd);

	//SkinUI_TrackLoop(psb);
}

/*
//----------------------------------------------------------
// Name : SkinUI_TrackLoop()
// Desc :
//----------------------------------------------------------
void SkinUI_TrackLoop(LPSB psb)
{
	HWND    hwnd;
	MSG     msg;
	int     cmd;
	//POINT   pt;

	if( !psb->fTracking )
		return;
	hwnd = psb->hwnd;
	while( GetCapture() == hwnd )
	{
		if( !GetMessage(&msg, hwnd, 0, 0) )
			break;

		if( !CallMsgFilter(&msg, MSGF_SCROLLBAR) )
		{
			cmd = msg.message;

			if( msg.hwnd == hwnd &&
				((cmd >= WM_MOUSEFIRST && cmd <= WM_MOUSELAST) ||
				(cmd >= WM_KEYFIRST && cmd <= WM_KEYLAST))
				)
			{
				TRACE("message loop\n");
				SkinUI_Proc(hwnd, cmd, msg.wParam, msg.lParam);
			}
		}
		else
		{
			TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
	}
}*/

//----------------------------------------------------------
// Name : SkinUI_HotTrack()
// Desc : Hot scrollbar arrow and thumb items
//----------------------------------------------------------
BOOL SkinUI_HotTrack(LPSB psb, int nHitCode, BOOL fVert, BOOL fMouseDown)
{
	HDC  	hDC;
	UINT 	oldHit;
	BOOL    oldVert;

	// Save old hittest code
	oldHit = psb->nLastCode;
	oldVert = psb->fLastVert;

	psb->nLastCode = nHitCode;
	psb->fLastVert = fVert;

	if( (hDC = GetWindowDC(psb->hwnd)) == NULL )
		return FALSE;

	if( nHitCode != oldHit || fVert != oldVert  || fMouseDown) {
		// Restore old hittest item state
		if( oldHit == HTSCROLL_LINEUP )
			SkinUI_DrawArrow(psb, hDC, oldVert, HTSCROLL_LINEUP, SB_STATE_NORMAL);
		else if( oldHit == HTSCROLL_LINEDOWN )
			SkinUI_DrawArrow(psb, hDC, oldVert, HTSCROLL_LINEDOWN, SB_STATE_NORMAL);
		else if( oldHit == HTSCROLL_THUMB )
			SkinUI_DrawThumb(psb, hDC, oldVert);
	

		// Draw new hittest item state
		if( nHitCode == HTSCROLL_LINEUP )
			SkinUI_DrawArrow(psb, hDC, fVert, HTSCROLL_LINEUP, fMouseDown ? SB_STATE_PRESSED : SB_STATE_HOTTRACKED);
		else if( nHitCode == HTSCROLL_LINEDOWN )
			SkinUI_DrawArrow(psb, hDC, fVert, HTSCROLL_LINEDOWN, fMouseDown ? SB_STATE_PRESSED : SB_STATE_HOTTRACKED);
		else if( nHitCode == HTSCROLL_THUMB)
			SkinUI_DrawThumb(psb, hDC, fVert);
	}

	ReleaseDC(psb->hwnd, hDC);
	
	return TRUE;
}

// Message handle

//----------------------------------------------------------
// Name : SkinUI_OnStyleChanged()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnStyleChanged(LPSB psb, int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	if( psb->fPreventStyleChange )
		return 0;

	if( nStyleType == GWL_EXSTYLE ) {
		BOOL fOld = psb->fLeftScrollBar;
		if( lpStyleStruct->styleNew & WS_EX_LEFTSCROLLBAR )
			psb->fLeftScrollBar = TRUE;
		else
			psb->fLeftScrollBar = FALSE;

		if( fOld != psb->fLeftScrollBar )
			SetWindowPos(psb->hwnd, NULL, 0, 0, 0, 0, SWP_NOZORDER |
				SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	}

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_STYLECHANGED, nStyleType, (LPARAM)lpStyleStruct);
}

//----------------------------------------------------------
// Name : SkinUI_OnNcCalcSize()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnNcCalcSize(LPSB psb, BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	LRESULT   lr;
	DWORD     dwStyle;
	RECT*     lprc, rect;
	
	lprc = &lpncsp->rgrc[0];
	rect = *lprc;

	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);
	
	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		psb->fPreventStyleChange = TRUE;
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle & ~(WS_VSCROLL|WS_HSCROLL));
	}

	lr = CallWindowProc(psb->pfnOldProc, psb->hwnd,
		WM_NCCALCSIZE, (WPARAM)bCalcValidRects, (LPARAM)lpncsp);

	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle);
		psb->fPreventStyleChange = FALSE;
	}

	if( (dwStyle & WS_HSCROLL) && 
		(lprc->bottom - lprc->top) > GetSystemMetrics(SM_CYHSCROLL) ) {
		lprc->bottom -= GetSystemMetrics(SM_CYHSCROLL);
	}

	if( (dwStyle & WS_VSCROLL) &&
		(lprc->right - lprc->left) > GetSystemMetrics(SM_CXVSCROLL) ) {
		if( psb->fLeftScrollBar )
			lprc->left += GetSystemMetrics(SM_CXVSCROLL);
		else
			lprc->right -= GetSystemMetrics(SM_CXVSCROLL);
	}
	return lr;
}

//----------------------------------------------------------
// Name : SkinUI_OnNcPaint()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnNcPaint(LPSB psb, HRGN hRgn)
{
	LRESULT  lr;
	DWORD    dwStyle;
	HDC      hDC;
	
	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);
	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		psb->fPreventStyleChange = TRUE;
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle & ~(WS_VSCROLL|WS_HSCROLL));
	}

	// draw frame border by system
	lr = CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCPAINT, (WPARAM)hRgn, 0);
	
	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle);
		psb->fPreventStyleChange = FALSE;
	}
	
	//hDC = GetDCEx(psb->hwnd, hRgn, DCX_WINDOW|DCX_INTERSECTRGN|DCX_CACHE );
	hDC = GetWindowDC(psb->hwnd);

	// draw the size box
	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) )
		SkinUI_DrawSizeBox(psb, hDC);

	// Draw scrollbar
	if( dwStyle & WS_VSCROLL )
		SkinUI_DrawScrollBar(psb, hDC, TRUE);
	
	if( dwStyle & WS_HSCROLL )
		SkinUI_DrawScrollBar(psb, hDC, FALSE);

	ReleaseDC(psb->hwnd, hDC);

	return lr;
}

//----------------------------------------------------------
// Name : SkinUI_OnNcHitTest()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnNcHitTest(LPSB psb, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	RECT rcHorz, rcVert, rcSize;
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);

	SkinUI_GetScrollBarRect(psb, TRUE, &rcVert);
	SkinUI_GetScrollBarRect(psb, FALSE, &rcHorz);
	SkinUI_GetSizeBoxRect(psb, &rcSize);

	if( PtInRect(&rcVert, pt) )
		return HTVSCROLL;
	else if( PtInRect(&rcHorz, pt) )
		return HTHSCROLL;
	else if( PtInRect(&rcSize, pt) )
		return HTSIZE;

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCHITTEST, wParam, lParam);
}


//----------------------------------------------------------
// Name : SkinUI_OnNcMouseMove()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnNcMouseMove(LPSB psb, WPARAM wParam, LPARAM lParam)
{
	if( wParam == HTHSCROLL || wParam == HTVSCROLL ) {
		POINT pt;
		BOOL  fVert;
		int   nHitCode;

		pt.x  = GET_X_LPARAM(lParam); 
		pt.y  = GET_Y_LPARAM(lParam);
		fVert = ( wParam == HTVSCROLL );
		nHitCode  = SkinUI_HitTest(psb, fVert, pt);
		SkinUI_HotTrack(psb, nHitCode, fVert, FALSE);
	}
	else if( wParam == HTSIZE ) {
		SkinUI_HotTrack(psb, HTSCROLL_NONE, FALSE, FALSE);
	}

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCMOUSEMOVE, wParam, lParam);
}

//---------------------------------------------------------
// Name : SkinUI_OnNcMouseLeave()
// Desc :
//---------------------------------------------------------
LRESULT SkinUI_OnNcMouseLeave(LPSB psb, WPARAM wParam, LPARAM lParam)
{
	psb->fMouseTracking = FALSE;
	if( psb->fTracking )
		return 0;

	SkinUI_HotTrack(psb, HTSCROLL_NONE, FALSE, FALSE);
	psb->nLastCode = HTSCROLL_NONE;

	return 0;
}

//----------------------------------------------------------
// Name : SkinUI_OnNcLButtonDown()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnNcLButtonDown(LPSB psb, WPARAM wParam, LPARAM lParam)
{
	if( wParam == HTHSCROLL || wParam == HTVSCROLL ) {
		POINT 			pt;
		BOOL  			fVert;
		int   			nHitCode;
		LPSCROLLINFO    psi;

		pt.x  = GET_X_LPARAM(lParam);
		pt.y  = GET_Y_LPARAM(lParam);
		fVert = (wParam == HTVSCROLL);
		
		psi = (fVert ? &psb->Vert : &psb->Horz);
		nHitCode = SkinUI_HitTest(psb, fVert, pt);
		psb->nLastCode = nHitCode;
		psb->fLastVert = fVert;
		SkinUI_Track(psb, fVert, nHitCode, pt);
		return 0;

	}
	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCLBUTTONDOWN, wParam, lParam);
}

//----------------------------------------------------------
// Name : SkinUI_OnMouseMove()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnMouseMove(LPSB psb, WPARAM wParam, LPARAM lParam)
{
	DWORD   	dwPos;
	POINT   	pt;
	UINT     	nHitCode, nHitTest;
	dwPos = 	GetMessagePos();
	pt.x  = 	GET_X_LPARAM(dwPos);
	pt.y  = 	GET_Y_LPARAM(dwPos);

	// Mouse left button down
	if( psb->fTracking && wParam & MK_LBUTTON ) {
		if( psb->nTrackCode == HTSCROLL_THUMB ) {
			SkinUI_TrackThumb(psb, psb->fTrackVert, pt);
			return 0;
		}

		nHitTest = (UINT)SkinUI_OnNcHitTest(psb, 0, dwPos);

		if( nHitTest == HTHSCROLL || nHitTest == HTVSCROLL ) {
			BOOL fVert = (nHitTest == HTVSCROLL);
			nHitCode = SkinUI_HitTest(psb, fVert, pt);

			if( nHitCode != psb->nTrackCode || fVert != psb->fTrackVert) {
				// Unallowed hot-track other hittest item
				SkinUI_HotTrack(psb, HTSCROLL_NONE, FALSE, FALSE);
			}
			else {
				SkinUI_HotTrack(psb, psb->nTrackCode, psb->fTrackVert, TRUE);
			}
		}
		else {
			SkinUI_HotTrack(psb, HTSCROLL_NONE, FALSE, FALSE);
		}
		return 0;
	}

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_MOUSEMOVE, wParam, lParam);
}

//----------------------------------------------------------
// Name : SkinUI_OnLButtonUp()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnLButtonUp(LPSB psb, WPARAM wParam, LPARAM lParam)
{
	if( psb->nTrackCode != HTSCROLL_NONE && psb->fTracking) {
		// Release mouse capture
		ReleaseCapture();

		// End scroll
		switch( psb->nTrackCode )
		{
		case HTSCROLL_LINEUP:
		case HTSCROLL_LINEDOWN:
		case HTSCROLL_PAGEUP:
		case HTSCROLL_PAGEDOWN:
			KillTimer(psb->hwnd, SB_TIMER_SCROLL);
			DoScrollMsg(psb->hwnd, SB_ENDSCROLL, 0, psb->fTrackVert);
			break;

		case HTSCROLL_THUMB:
			if( psb->fTracking ) {
				DWORD  dwPos;
				POINT  pt;
				dwPos = GetMessagePos();
				pt.x = GET_X_LPARAM(dwPos);
				pt.y = GET_Y_LPARAM(dwPos);
				DoScrollMsg(psb->hwnd, SB_THUMBPOSITION, psb->nTrackPos, psb->fTrackVert);
				DoScrollMsg(psb->hwnd, SB_ENDSCROLL, 0, psb->fTrackVert);
				psb->nLastCode = SkinUI_HitTest(psb, psb->fTrackVert, pt);
			}
			break;
		}
		
		// Clean the track parameters
		psb->nOffsetPoint    = 0;
		psb->nScrollTimerMsg = MAKELONG(WM_NULL, 0);
		psb->nTrackCode      = HTSCROLL_NONE;
		psb->fTracking       = FALSE;
		psb->nTrackPos       = 0;

		HDC hdc = GetWindowDC(psb->hwnd);
		SkinUI_DrawThumb(psb, hdc, psb->fTrackVert);
		ReleaseDC(psb->hwnd, hdc);
		return 0;
	}
	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_LBUTTONUP, wParam, lParam);
}

//----------------------------------------------------------
// Name : SkinUI_OnTimer()
// Desc :
//----------------------------------------------------------
LRESULT SkinUI_OnTimer(LPSB psb, WPARAM wParam, LPARAM lParam)
{
	
	if(wParam == SB_TIMER_SCROLL) {
		// if mouse left button released then close scroll timer 
		if( psb->nTrackCode == HTSCROLL_NONE ) {
			KillTimer(psb->hwnd, SB_TIMER_SCROLL);
			return 0;
		}

		// Timer send scroll message
		if( psb->nTrackCode == psb->nLastCode && psb->fTrackVert == psb->fLastVert )
			DoScrollMsg(psb->hwnd, HIWORD(psb->nScrollTimerMsg), 0, psb->fTrackVert);

		return 0;
	}
	else if(wParam == SB_TIMER_DELAY) {
		KillTimer(psb->hwnd, SB_TIMER_DELAY);
		SetTimer(psb->hwnd, SB_TIMER_SCROLL, SB_SCROLL_INTERVAL, 0);
		return 0;
	}
	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_TIMER, wParam, lParam);
}


//----------------------------------------------------------
// Name : SkinUI_Proc()
// Desc :
//----------------------------------------------------------
LRESULT CALLBACK SkinUI_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPSB psb = SkinUI_GetSB(hwnd);
	
	if( psb && uMsg == WM_NCMOUSEMOVE ) {
		if(!psb->fMouseTracking && !psb->fTracking) {
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = psb->hwnd;
			tme.dwFlags = TME_LEAVE|TME_NONCLIENT;
			tme.dwHoverTime = 0;
			psb->fMouseTracking = _TrackMouseEvent(&tme);
		}
	}

	switch( uMsg )
	{
	case WM_NCPAINT:
		return SkinUI_OnNcPaint(psb, (HRGN)wParam);

	case WM_NCCALCSIZE:
		return SkinUI_OnNcCalcSize(psb, (BOOL)wParam, (NCCALCSIZE_PARAMS*)lParam);

	case WM_NCHITTEST:
		return SkinUI_OnNcHitTest(psb, wParam, lParam);

	case WM_STYLECHANGED:
		return SkinUI_OnStyleChanged(psb, (int)wParam, (LPSTYLESTRUCT)lParam);

	case WM_NCLBUTTONDOWN:
		return SkinUI_OnNcLButtonDown(psb, wParam, lParam);

	case WM_NCMOUSEMOVE:
		return SkinUI_OnNcMouseMove(psb, wParam, lParam);

	case WM_MOUSEMOVE:
		return SkinUI_OnMouseMove(psb, wParam, lParam);

	case WM_LBUTTONUP:
		return SkinUI_OnLButtonUp(psb, wParam, lParam);

	case WM_NCMOUSELEAVE:		
		return SkinUI_OnNcMouseLeave(psb, wParam, lParam);

    case WM_NCLBUTTONDBLCLK:
	case WM_NCRBUTTONDBLCLK:
		return 0;

	case WM_TIMER:
		return SkinUI_OnTimer(psb, wParam, lParam);

	case WM_NCDESTROY:
		LRESULT lr = CallWindowProc(psb->pfnOldProc, hwnd, uMsg, wParam, lParam);
		SkinUI_Uninit(hwnd);
		return lr;
	}
	return CallWindowProc(psb->pfnOldProc, hwnd, uMsg, wParam, lParam);
}
#include "StdAfx.h"
#include "RenderManager.h"

CRenderManager::CRenderManager(void)
{
	m_hResInstance = NULL;

	SetDefaultFont(TEXT("����"),12,false,false,false);
}

CRenderManager::~CRenderManager(void)
{
}

//��������
CRenderManager* CRenderManager::GetInstance()
{
	static CRenderManager _Instance;

	return &_Instance;
}

static COLORREF PixelAlpha(COLORREF clrSrc, double src_darken, COLORREF clrDest, double dest_darken)
{
	return RGB (GetRValue (clrSrc) * src_darken + GetRValue (clrDest) * dest_darken, 
		GetGValue (clrSrc) * src_darken + GetGValue (clrDest) * dest_darken, 
		GetBValue (clrSrc) * src_darken + GetBValue (clrDest) * dest_darken);

}

static BOOL WINAPI AlphaBitBlt(HDC hDC, int nDestX, int nDestY, int dwWidth, int dwHeight, HDC hSrcDC, \
							   int nSrcX, int nSrcY, int wSrc, int hSrc, BLENDFUNCTION ftn)
{
	HDC hTempDC = ::CreateCompatibleDC(hDC);
	if (NULL == hTempDC)
		return FALSE;

	//Creates Source DIB
	LPBITMAPINFO lpbiSrc = NULL;
	// Fill in the BITMAPINFOHEADER
	lpbiSrc = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
	if (lpbiSrc == NULL)
	{
		::DeleteDC(hTempDC);
		return FALSE;
	}
	lpbiSrc->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbiSrc->bmiHeader.biWidth = dwWidth;
	lpbiSrc->bmiHeader.biHeight = dwHeight;
	lpbiSrc->bmiHeader.biPlanes = 1;
	lpbiSrc->bmiHeader.biBitCount = 32;
	lpbiSrc->bmiHeader.biCompression = BI_RGB;
	lpbiSrc->bmiHeader.biSizeImage = dwWidth * dwHeight;
	lpbiSrc->bmiHeader.biXPelsPerMeter = 0;
	lpbiSrc->bmiHeader.biYPelsPerMeter = 0;
	lpbiSrc->bmiHeader.biClrUsed = 0;
	lpbiSrc->bmiHeader.biClrImportant = 0;

	COLORREF* pSrcBits = NULL;
	HBITMAP hSrcDib = CreateDIBSection (
		hSrcDC, lpbiSrc, DIB_RGB_COLORS, (void **)&pSrcBits,
		NULL, NULL);

	if ((NULL == hSrcDib) || (NULL == pSrcBits)) 
	{
		delete [] lpbiSrc;
		::DeleteDC(hTempDC);
		return FALSE;
	}

	HBITMAP hOldTempBmp = (HBITMAP)::SelectObject (hTempDC, hSrcDib);
	::StretchBlt(hTempDC, 0, 0, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, wSrc, hSrc, SRCCOPY);
	::SelectObject (hTempDC, hOldTempBmp);

	//Creates Destination DIB
	LPBITMAPINFO lpbiDest = NULL;
	// Fill in the BITMAPINFOHEADER
	lpbiDest = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
	if (lpbiDest == NULL)
	{
		delete [] lpbiSrc;
		::DeleteObject(hSrcDib);
		::DeleteDC(hTempDC);
		return FALSE;
	}

	lpbiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbiDest->bmiHeader.biWidth = dwWidth;
	lpbiDest->bmiHeader.biHeight = dwHeight;
	lpbiDest->bmiHeader.biPlanes = 1;
	lpbiDest->bmiHeader.biBitCount = 32;
	lpbiDest->bmiHeader.biCompression = BI_RGB;
	lpbiDest->bmiHeader.biSizeImage = dwWidth * dwHeight;
	lpbiDest->bmiHeader.biXPelsPerMeter = 0;
	lpbiDest->bmiHeader.biYPelsPerMeter = 0;
	lpbiDest->bmiHeader.biClrUsed = 0;
	lpbiDest->bmiHeader.biClrImportant = 0;

	COLORREF* pDestBits = NULL;
	HBITMAP hDestDib = CreateDIBSection (
		hDC, lpbiDest, DIB_RGB_COLORS, (void **)&pDestBits,
		NULL, NULL);

	if ((NULL == hDestDib) || (NULL == pDestBits))
	{
		delete [] lpbiSrc;
		::DeleteObject(hSrcDib);
		::DeleteDC(hTempDC);
		return FALSE;
	}

	::SelectObject (hTempDC, hDestDib);
	::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hDC, nDestX, nDestY, SRCCOPY);
	::SelectObject (hTempDC, hOldTempBmp);

	double src_darken;
	BYTE nAlpha;

	for (int pixel = 0; pixel < dwWidth * dwHeight; pixel++, pSrcBits++, pDestBits++)
	{
		nAlpha = LOBYTE(*pSrcBits >> 24);
		src_darken = (double) (nAlpha * ftn.SourceConstantAlpha) / 255.0 / 255.0;
		if( src_darken < 0.0 ) src_darken = 0.0;
		*pDestBits = PixelAlpha(*pSrcBits, src_darken, *pDestBits, 1.0 - src_darken);
	} //for

	::SelectObject (hTempDC, hDestDib);
	::BitBlt (hDC, nDestX, nDestY, dwWidth, dwHeight, hTempDC, 0, 0, SRCCOPY);
	::SelectObject (hTempDC, hOldTempBmp);

	delete [] lpbiDest;
	::DeleteObject(hDestDib);

	delete [] lpbiSrc;
	::DeleteObject(hSrcDib);

	::DeleteDC(hTempDC);
	return TRUE;
}

bool CRenderManager::GetWorkDirectory( TCHAR szWorkDirectory[], WORD wBufferCount )
{
	//ģ��·��
	TCHAR szModulePath[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szModulePath,CountArray(szModulePath));

	//�����ļ�
	for (INT i=lstrlen(szModulePath);i>=0;i--)
	{
		if (szModulePath[i]==TEXT('\\'))
		{
			szModulePath[i]=0;
			break;
		}
	}

	//���ý��
	ASSERT(szModulePath[0]!=0);
	lstrcpyn(szWorkDirectory,szModulePath,wBufferCount);

	return true;
}

//����ɫ��
void CRenderManager::DrawColor(HDC hDC, const RECT& rc, COLORREF color)
{
	::SetBkColor(hDC, color);
	::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
}
//����ɫ��
void CRenderManager::DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps)
{
	typedef BOOL (WINAPI *LPALPHABLEND)(HDC, int, int, int, int,HDC, int, int, int, int, BLENDFUNCTION);
	static LPALPHABLEND lpAlphaBlend = (LPALPHABLEND) ::GetProcAddress(::GetModuleHandle(_T("msimg32.dll")), "AlphaBlend");
	if( lpAlphaBlend == NULL ) lpAlphaBlend = AlphaBitBlt;
	typedef BOOL (WINAPI *PGradientFill)(HDC, PTRIVERTEX, ULONG, PVOID, ULONG, ULONG);
	static PGradientFill lpGradientFill = (PGradientFill) ::GetProcAddress(::GetModuleHandle(_T("msimg32.dll")), "GradientFill");

	BYTE bAlpha = (BYTE)(((dwFirst >> 24) + (dwSecond >> 24)) >> 1);
	if( bAlpha == 0 ) return;
	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;
	RECT rcPaint = rc;
	HDC hPaintDC = hDC;
	HBITMAP hPaintBitmap = NULL;
	HBITMAP hOldPaintBitmap = NULL;
	if( bAlpha < 255 )
	{
		rcPaint.left = rcPaint.top = 0;
		rcPaint.right = cx;
		rcPaint.bottom = cy;
		hPaintDC = ::CreateCompatibleDC(hDC);
		hPaintBitmap = ::CreateCompatibleBitmap(hDC, cx, cy);
		ASSERT(hPaintDC);
		ASSERT(hPaintBitmap);
		hOldPaintBitmap = (HBITMAP) ::SelectObject(hPaintDC, hPaintBitmap);
	}

	if( lpGradientFill != NULL ) 
	{
		TRIVERTEX triv[2] = 
		{
			{ rcPaint.left, rcPaint.top, GetBValue(dwFirst) << 8, GetGValue(dwFirst) << 8, GetRValue(dwFirst) << 8, 0xFF00 },
			{ rcPaint.right, rcPaint.bottom, GetBValue(dwSecond) << 8, GetGValue(dwSecond) << 8, GetRValue(dwSecond) << 8, 0xFF00 }
		};
		GRADIENT_RECT grc = { 0, 1 };
		lpGradientFill(hPaintDC, triv, 2, &grc, 1, bVertical ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H);
	}
	else 
	{
		// Determine how many shades
		int nShift = 1;
		if( nSteps >= 64 ) nShift = 6;
		else if( nSteps >= 32 ) nShift = 5;
		else if( nSteps >= 16 ) nShift = 4;
		else if( nSteps >= 8 ) nShift = 3;
		else if( nSteps >= 4 ) nShift = 2;
		int nLines = 1 << nShift;
		
		for( int i = 0; i < nLines; i++ )
		{
			// Do a little alpha blending
			BYTE bR = (BYTE) ((GetBValue(dwSecond) * (nLines - i) + GetBValue(dwFirst) * i) >> nShift);
			BYTE bG = (BYTE) ((GetGValue(dwSecond) * (nLines - i) + GetGValue(dwFirst) * i) >> nShift);
			BYTE bB = (BYTE) ((GetRValue(dwSecond) * (nLines - i) + GetRValue(dwFirst) * i) >> nShift);
			// ... then paint with the resulting color
			HBRUSH hBrush = ::CreateSolidBrush(RGB(bR,bG,bB));
			RECT r2 = rcPaint;
			if( bVertical ) 
			{
				r2.bottom = rc.bottom - ((i * (rc.bottom - rc.top)) >> nShift);
				r2.top = rc.bottom - (((i + 1) * (rc.bottom - rc.top)) >> nShift);
				if( (r2.bottom - r2.top) > 0 ) ::FillRect(hDC, &r2, hBrush);
			}
			else 
			{
				r2.left = rc.right - (((i + 1) * (rc.right - rc.left)) >> nShift);
				r2.right = rc.right - ((i * (rc.right - rc.left)) >> nShift);
				if( (r2.right - r2.left) > 0 ) ::FillRect(hPaintDC, &r2, hBrush);
			}
			::DeleteObject(hBrush);
		}
	}

	if( bAlpha < 255 )
	{
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, bAlpha, AC_SRC_ALPHA };
		lpAlphaBlend(hDC, rc.left, rc.top, cx, cy, hPaintDC, 0, 0, cx, cy, bf);
		::SelectObject(hPaintDC, hOldPaintBitmap);
		::DeleteObject(hPaintBitmap);
		::DeleteDC(hPaintDC);
	}
}

//��������
void CRenderManager::DrawLine(HDC hDC, const RECT& rc, int nSize, COLORREF dwPenColor,int nStyle/* = PS_SOLID*/)
{
	ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);

	LOGPEN lg;
	lg.lopnColor = dwPenColor;
	lg.lopnStyle = nStyle;
	lg.lopnWidth.x = nSize;
	HPEN hPen = CreatePenIndirect(&lg);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);
	POINT ptTemp = { 0 };
	::MoveToEx(hDC, rc.left, rc.top, &ptTemp);
	::LineTo(hDC, rc.right, rc.bottom);
	::SelectObject(hDC, hOldPen);
	::DeleteObject(hPen);
}

//���ƾ���
void CRenderManager::DrawRect(HDC hDC, const RECT& rc, int nSize, COLORREF dwPenColor)
{
	ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
	HPEN hPen = ::CreatePen(PS_SOLID | PS_INSIDEFRAME, nSize, dwPenColor);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);
	::SelectObject(hDC, ::GetStockObject(HOLLOW_BRUSH));
	::Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
	::SelectObject(hDC, hOldPen);
	::DeleteObject(hPen);
}

//Բ�Ǿ���
void CRenderManager::DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, COLORREF dwPenColor)
{
	ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
	HPEN hPen = ::CreatePen(PS_SOLID | PS_INSIDEFRAME, nSize, dwPenColor);
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);
	::SelectObject(hDC, ::GetStockObject(HOLLOW_BRUSH));
	::RoundRect(hDC, rc.left, rc.top, rc.right, rc.bottom, width, height);
	::SelectObject(hDC, hOldPen);
	::DeleteObject(hPen);
}

void CRenderManager::DrawText(HDC hDC, RECT& rc, LPCTSTR pstrText, DWORD dwTextColor, HFONT hFont, UINT uStyle)
{
	ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
	if( pstrText == NULL ) return;
	::SetBkMode(hDC, TRANSPARENT);
	::SetTextColor(hDC, RGB(GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));
	HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);
	::DrawText(hDC, pstrText, -1, &rc, uStyle | DT_NOPREFIX);
	::SelectObject(hDC, hOldFont);
}

//���ֳߴ�
SIZE CRenderManager::GetTextSize(HDC hDC, LPCTSTR pstrText, HFONT hFont, UINT uStyle)
{
	SIZE size = {0,0};
	ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
	if( pstrText == NULL ) return size;
	::SetBkMode(hDC, TRANSPARENT);
	HFONT hOldFont = (HFONT)::SelectObject(hDC, hFont);
	GetTextExtentPoint32(hDC, pstrText, _tcslen(pstrText) , &size);
	::SelectObject(hDC, hOldFont);
	return size;
}

void CRenderManager::SetDefaultFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic )
{
	LOGFONT lf = { 0 };
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	_tcsncpy_s(lf.lfFaceName, pStrFontName, LF_FACESIZE);
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -nSize;
	if( bBold ) lf.lfWeight += FW_BOLD;
	if( bUnderline ) lf.lfUnderline = TRUE;
	if( bItalic ) lf.lfItalic = TRUE;
	m_hDefaultFont = ::CreateFontIndirect(&lf);

	if( m_hDefaultFont == NULL ) throw TEXT("��������ʧ��");
}

//��ȡͼƬ
CImageEx * CRenderManager::GetImage( LPCTSTR lpszFileName,LPCTSTR lpszResType/*=NULL*/ )
{
	map<LPCTSTR,tagImageInfo*>::iterator iter;
	pair<std::map<LPCTSTR, tagImageInfo *>::iterator, bool> pairInsert;
	
	tagImageInfo * pImageInfo = NULL;
	CImageEx * pImage=NULL;

	if (NULL == lpszFileName || NULL == *lpszFileName)
		return NULL;

	iter = m_ArrayImage.find(lpszFileName);
	if (iter != m_ArrayImage.end())
	{
		pImageInfo = iter->second;
		if (pImageInfo != NULL)
		{
			pImageInfo->nRef++;
			
			pImageInfo->pImage->DestroyImage();

			//·��������Դ
			if( lpszResType == NULL )
			{
				TCHAR szWorkDirectory[MAX_PATH]={0};
				GetWorkDirectory(szWorkDirectory,MAX_PATH);
				StrCat(szWorkDirectory,TEXT("\\"));
				StrCat(szWorkDirectory,lpszFileName);

				CFileFind fileFind;

				//�ж��Ƿ�exeĿ¼�µ���Դ
				if ( fileFind.FindFile(szWorkDirectory) )
					pImageInfo->pImage->LoadImage(szWorkDirectory);
				else //lpszFileNameΪ����·��
					pImageInfo->pImage->LoadImage(lpszFileName);
			}
			else
			{
				pImageInfo->pImage->LoadImage(m_hResInstance,lpszFileName,lpszResType);
			}

			return pImageInfo->pImage;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		pImageInfo = new tagImageInfo;
		pImage = new CImageEx;
		if (NULL == pImageInfo || NULL == pImage)
		{
			SafeDelete(pImageInfo);
			SafeDelete(pImage);
			return NULL;
		}

		pairInsert = m_ArrayImage.insert(pair<LPCTSTR, tagImageInfo *>(lpszFileName, pImageInfo));
		if (!pairInsert.second)
		{
			SafeDelete(pImageInfo);
			SafeDelete(pImage);
			return NULL;
		}

		bool bReturn = false;

		//·��������Դ
		if( lpszResType == NULL )
		{
			TCHAR szWorkDirectory[MAX_PATH]={0};
			GetWorkDirectory(szWorkDirectory,MAX_PATH);
			StrCat(szWorkDirectory,TEXT("\\"));
			StrCat(szWorkDirectory,lpszFileName);
			//sprintf_s(szWorkDirectory,_TRUNCATE,TEXT("\\%s"),lpszFileName);

			CFileFind fileFind;

			//�ж��Ƿ�exeĿ¼�µ���Դ
			if ( fileFind.FindFile(szWorkDirectory) )
				bReturn = pImage->LoadImage(szWorkDirectory);
			else //lpszFileNameΪ����·��
				bReturn = pImage->LoadImage(lpszFileName);
		}
		else
		{
			bReturn = pImage->LoadImage(m_hResInstance,lpszFileName,lpszResType);
		}

		if (!bReturn)
		{
			m_ArrayImage.erase(pairInsert.first);
			SafeDelete(pImageInfo);
			SafeDelete(pImage);
			return NULL;
		}

		pImageInfo->pImage = pImage;
		pImageInfo->nRef = 1;

		return pImage;
	}
}

//ɾ��ͼƬ
void CRenderManager::RemoveImage( CImageEx *&pImage )
{
	map<LPCTSTR, tagImageInfo *>::iterator iter;
	tagImageInfo * pImageInfo;

	if (NULL == pImage) return;

	for (iter = m_ArrayImage.begin(); iter != m_ArrayImage.end(); iter++)
	{
		pImageInfo = iter->second;
		if (pImageInfo != NULL)
		{
			if (pImageInfo->pImage == pImage)
			{
				pImageInfo->nRef--;
				if (pImageInfo->nRef <= 0)
				{
					pImageInfo->pImage->DestroyImage();

					SafeDelete(pImageInfo->pImage);
					SafeDelete(pImageInfo);

					m_ArrayImage.erase(iter);
				}

				pImage = NULL;
				break;
			}
		}
	}
}

//ɾ������
void CRenderManager::ClearImage()
{
	map<LPCTSTR, tagImageInfo *>::iterator iter;
	tagImageInfo * pImageInfo;

	for (iter = m_ArrayImage.begin(); iter != m_ArrayImage.end(); iter++)
	{
		pImageInfo = iter->second;
		if (pImageInfo != NULL)
		{
			if (pImageInfo->pImage != NULL)
			{
				pImageInfo->pImage->DestroyImage();
				SafeDelete(pImageInfo->pImage);
			}

			SafeDelete(pImageInfo);
		}
	}

	m_ArrayImage.clear();
}

void CRenderManager::AddFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic )
{
	LOGFONT lf = { 0 };
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	_tcsncpy_s(lf.lfFaceName, pStrFontName, LF_FACESIZE);
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -nSize;
	if( bBold ) lf.lfWeight += FW_BOLD;
	if( bUnderline ) lf.lfUnderline = TRUE;
	if( bItalic ) lf.lfItalic = TRUE;
	HFONT hFont = ::CreateFontIndirect(&lf);

	if( hFont != NULL )
		m_ArrayFont.push_back(hFont);
}

HFONT CRenderManager::GetFont( int nIndex )
{
	if ( nIndex>(int)m_ArrayFont.size() ) return NULL;
	
	return m_ArrayFont.at(nIndex);
}

HFONT CRenderManager::GetEndFont()
{
	return *(m_ArrayFont.end()-1);
}

void CRenderManager::GetRect( HWND hWnd,tagPositionData *pPositionData,CRect &rcPos )
{
	CRect rcClient;
	GetClientRect(hWnd,&rcClient);

	//////////////////////////////λ��////////////////////////////////////////////
	if (pPositionData->nFixedPostion[0] == en_LTop )
	{
		rcPos.left = pPositionData->ptPosition.x;
		rcPos.top = pPositionData->ptPosition.y;
	}
	else if (pPositionData->nFixedPostion[0] == en_RTop )
	{
		rcPos.left = rcClient.Width()-pPositionData->ptPosition.x;
		rcPos.top = pPositionData->ptPosition.y;
	}
	else if (pPositionData->nFixedPostion[0] == en_LBottom )
	{
		rcPos.left = pPositionData->ptPosition.x;
		rcPos.top = rcClient.Height()-pPositionData->ptPosition.y;
	}
	else if (pPositionData->nFixedPostion[0] == en_RBottom )
	{
		rcPos.left = rcClient.Width()-pPositionData->ptPosition.x;
		rcPos.top = rcClient.Height()-pPositionData->ptPosition.y;
	}

	///////////////////////////////��С///////////////////////////////////////////
	if (pPositionData->nFixedPostion[1] == en_LTop )
	{
		rcPos.right = pPositionData->szSize.cx;
		rcPos.bottom = pPositionData->szSize.cy;
	}
	else if (pPositionData->nFixedPostion[1] == en_RTop )
	{
		rcPos.right = rcClient.Width()-pPositionData->szSize.cx;
		rcPos.bottom = pPositionData->szSize.cy;
	}
	else if (pPositionData->nFixedPostion[1] == en_LBottom )
	{
		rcPos.right = pPositionData->szSize.cx;
		rcPos.bottom = rcClient.Height()-pPositionData->szSize.cy;
	}
	else if (pPositionData->nFixedPostion[1] == en_RBottom )
	{
		rcPos.right = rcClient.Width()-pPositionData->szSize.cx;
		rcPos.bottom = rcClient.Height()-pPositionData->szSize.cy;
	}
}


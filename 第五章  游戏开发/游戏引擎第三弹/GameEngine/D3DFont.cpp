#include "stdafx.h"
#include "D3DFont.h"

CD3DFontItemPtrArray		m_FontItemPtrActive;

//////////////////////////////////////////////////////////////////////////

CD3DFont::CD3DFont()
{
	m_uGrayLevel = 0;
	m_uMaxBufferCount = 0;

	m_pD3DXFont = NULL;

	m_FontItemPtrActive.RemoveAll();
}

CD3DFont::~CD3DFont()
{
	SafeRelease(m_pD3DXFont);
}

bool CD3DFont::DeleteFont()
{
	DeleteObject(m_Font);

	return true;
}

bool CD3DFont::CreateFont( LOGFONT & LogFont, UINT uGrayLevel )
{
	//m_Font.CreateFont(LogFont.lfHeight,LogFont.lfWidth,LogFont.lfEscapement,LogFont.lfOrientation,LogFont.lfWeight,LogFont.lfItalic,LogFont.lfUnderline,LogFont.lfStrikeOut,LogFont.lfCharSet,LogFont.lfOutPrecision,LogFont.lfClipPrecision,LogFont.lfQuality,LogFont.lfPitchAndFamily,LogFont.lfFaceName);
	m_Font = ::CreateFontIndirect(&LogFont);

	return true;
}

bool CD3DFont::CreateFont( INT nPointSize, LPCTSTR lpszFaceName, UINT uGrayLevel )
{
	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfHeight = nPointSize;
	_sntprintf_s(logFont.lfFaceName,CountArray(logFont.lfFaceName),lpszFaceName);

	return CreateFont(logFont,0);
}

bool CD3DFont::DrawText( CD3DDevice * pD3DDevice, LPCTSTR pszString, cCRect rcDraw, UINT uFormat, D3DCOLOR D3DColor )
{
	HRESULT hr = S_OK;

	if ( m_pD3DXFont == NULL )
	{
		LOGFONT LogFont;
		::GetObject(m_Font, sizeof(LOGFONT), &LogFont);

		D3DXCreateFont( pD3DDevice->GetDirect3DDevice(), LogFont.lfHeight,LogFont.lfWidth,LogFont.lfWeight, 1, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
			LogFont.lfFaceName, &m_pD3DXFont );

		m_FontItemPtrActive.Add(this);
	}

// 	D3DXMATRIX matTransform;
// 	D3DXMatrixIdentity( &matTransform );
// 	m_pManager->m_pSprite->SetTransform( &matTransform );

#ifdef _UNICODE
	hr = m_pD3DXFont->DrawText( NULL, pszString, wcslen(pszString), rcDraw, uFormat,D3DColor );
#else
	hr = m_pD3DXFont->DrawText( NULL, pszString, strlen(pszString), rcDraw, uFormat,D3DColor );
#endif
	
	if( FAILED( hr ) ) return false;

	return true;
}

bool CD3DFont::DrawText( CD3DDevice * pD3DDevice, LPCTSTR pszString, INT nXPos, INT nYPos, UINT uFormat, D3DCOLOR D3DColor )
{
	HRESULT hr = S_OK;

	if ( m_pD3DXFont == NULL )
	{
		LOGFONT LogFont;
		::GetObject(m_Font, sizeof(LOGFONT), &LogFont); 

		D3DXCreateFont( pD3DDevice->GetDirect3DDevice(), LogFont.lfHeight,LogFont.lfWidth,LogFont.lfWeight, 1, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
			LogFont.lfFaceName, &m_pD3DXFont ); 

		m_FontItemPtrActive.Add(this);
	}

	// 	D3DXMATRIX matTransform;
	// 	D3DXMatrixIdentity( &matTransform );
	// 	m_pManager->m_pSprite->SetTransform( &matTransform );

#ifdef _UNICODE
	hr = m_pD3DXFont->DrawText( NULL, pszString, wcslen(pszString), cCRect(nXPos,nYPos,0,0), uFormat | DT_NOCLIP,D3DColor );
#else
	hr = m_pD3DXFont->DrawText( NULL, pszString, strlen(pszString), cCRect(nXPos,nYPos,0,0), uFormat | DT_NOCLIP,D3DColor );
#endif
	

	if( FAILED( hr ) ) return false;

	return true;
}

VOID CD3DFont::OnDeviceLost( CD3DDevice * pD3DDevice )
{
	//�����ж�
	assert(pD3DDevice!=NULL);
	if (pD3DDevice==NULL) return;

	for (INT_PTR i=0;i<m_FontItemPtrActive.GetCount();i++)
	{
		m_FontItemPtrActive.GetAt(i)->m_pD3DXFont->OnLostDevice();
	}
}

VOID CD3DFont::OnDeviceReset( CD3DDevice * pD3DDevice )
{
	//�����ж�
	assert(pD3DDevice!=NULL);
	if (pD3DDevice==NULL) return;

	for (INT_PTR i=0;i<m_FontItemPtrActive.GetCount();i++)
	{
		m_FontItemPtrActive.GetAt(i)->m_pD3DXFont->OnResetDevice();
	}
}

#include "StdAfx.h"
#include "VirtualSlider.h"

CVirtualSlider::CVirtualSlider(void)
{
	m_pTextureBack = NULL;
	m_pTextureChannel = NULL;
	m_pTextureButton = NULL;

	m_nMin = 0;
	m_nMax = 0;

	m_nPos = 0;
	m_nButtonX = 0;

	m_bMouseDown = false;

	m_rcButtonRect.SetRect(0,0,0,0);
}

CVirtualSlider::~CVirtualSlider(void)
{
}

VOID CVirtualSlider::OnWindowDestory( CD3DDevice * pD3DDevice )
{

}

BOOL CVirtualSlider::OnEventMouse( UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos )
{
	if( !m_bEnable || !m_bVisible ) return false;

	static int nDragOffset = 0;

	switch( uMessage )
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		{
			POINT mousePoint = { nXMousePos, nYMousePos };
			RECT rcButton = { m_rcButtonRect.left+m_BenchmarkPos.x,m_rcButtonRect.top+m_BenchmarkPos.y,rcButton.left+m_rcButtonRect.Width(),rcButton.top+m_rcButtonRect.Height() };

			if( PtInRect( &rcButton, mousePoint ) )
			{
				SetFocus();
				m_bMouseDown = true;

				nDragOffset = m_nButtonX - nXMousePos;

				return true;
			} 


			if ( ContainsPoint(CPoint(nXMousePos,nYMousePos)) )
			{
				nDragOffset = 0;
				m_bMouseDown = true;

				SetFocus();

				if( nXMousePos > m_nButtonX+m_BenchmarkPos.x  )
				{
					SetPos( m_nPos+1 );
					return true;
				}

				if( nXMousePos < m_nButtonX+m_BenchmarkPos.x )
				{
					SetPos( m_nPos-1 );
					return true;
				}
			}

			break;
		}

	case WM_LBUTTONUP:
		{
			if( m_bMouseDown )
			{
				m_bMouseDown = false;
				OnEventSlider(m_nPos);

				return true;
			}

			break;
		}

	case WM_MOUSEMOVE:
		{
			if( m_bMouseDown )
			{
				float fValuePerPixel = ( float )( m_nMax - m_nMin ) / m_WindowSize.cx;

				int nPos = ( int )( 0.5f + m_nMin + fValuePerPixel * ( nXMousePos + nDragOffset ) );
				SetPos( nPos );

				return true;
			}

			break;
		}

	case WM_MOUSEWHEEL:
		{
			int nScrollAmount = int( ( short )HIWORD( nFlags ) ) / WHEEL_DELTA;
			SetPos( m_nPos - nScrollAmount );

			return true;
		}
	};

	return false;
}

VOID CVirtualSlider::OnEventDrawWindow( CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos )
{
	if ( Check_Image(m_pTextureBack) )
	{
		m_pTextureBack->DrawImage(pD3DDevice,nXOriginPos,nYOriginPos);
	}

	if ( Check_Image(m_pTextureChannel) )
	{
		m_pTextureChannel->DrawImage(pD3DDevice,nXOriginPos,nYOriginPos,m_rcButtonRect.left,m_pTextureBack->GetHeight(),0,0);
	}

	if ( Check_Image(m_pTextureButton) )
	{
		m_pTextureButton->DrawImage(pD3DDevice,nXOriginPos+m_rcButtonRect.left,nYOriginPos+m_rcButtonRect.top,m_rcButtonRect.Width(),m_rcButtonRect.Height(),0,0);
	}
}

void CVirtualSlider::SetTexture( CD3DTexture*pTextureBack,CD3DTexture*pTextureChannel,CD3DTexture*pTextureButton )
{
	m_pTextureBack = pTextureBack;
	m_pTextureChannel = pTextureChannel;
	m_pTextureButton = pTextureButton;

	if( Check_Image(m_pTextureBack) )
		SetWindowPos(m_BenchmarkPos.x,m_BenchmarkPos.y,m_BenchmarkPos.x+m_pTextureBack->GetWidth(),m_BenchmarkPos.y+m_pTextureBack->GetHeight(),0);

	UpdateRects();
}

void CVirtualSlider::SetRange( int nMin, int nMax )
{
	m_nMin = nMin;
	m_nMax = nMax;

	SetPos( m_nPos );
}

void CVirtualSlider::SetPos( int nPos )
{
	nPos = __max( m_nMin, nPos );
	nPos = __min( m_nMax, nPos );

	if( nPos == m_nPos ) return;

	m_nPos = nPos;
	OnEventSlider(m_nPos);

	UpdateRects();
}

void CVirtualSlider::UpdateRects()
{
	m_nButtonX = ( int )( ( m_nPos - m_nMin ) * ( float )m_WindowSize.cx / ( m_nMax - m_nMin ) );
	int nButtonWidth = 20,nButtonHeight=20;

	if( Check_Image( m_pTextureButton ) )
	{
		nButtonWidth = m_pTextureButton->GetWidth();
		nButtonHeight = m_pTextureButton->GetHeight();
	}

	m_rcButtonRect.left = m_nButtonX-nButtonWidth/2;
	m_rcButtonRect.top = (m_WindowSize.cy-nButtonHeight)/2;
	m_rcButtonRect.right = m_rcButtonRect.left + nButtonWidth;
	m_rcButtonRect.bottom = m_rcButtonRect.top + nButtonHeight;
}

void CVirtualSlider::GetRange( int& nMin, int& nMax ) const
{
	nMin = m_nMin; nMax = m_nMax;
}

INT CVirtualSlider::GetPos()
{
	return m_nPos;
}

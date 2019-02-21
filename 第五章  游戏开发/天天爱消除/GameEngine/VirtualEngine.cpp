#include "stdafx.h"
#include "VirtualEngine.h"
#include "VirtualWindow.h"

CVirtualEngine::CVirtualEngine()
{
	m_pD3DDevice = NULL;
	m_pWindowLeave = NULL;
	m_pWindowCapture = NULL;

	m_CaptureWindowPtrArray.RemoveAll();
}

CVirtualEngine::~CVirtualEngine()
{

}

VOID CVirtualEngine::SetD3DDevice( CD3DDevice * pD3DDevice )
{
	m_pD3DDevice=pD3DDevice;

	LOGFONT LogDefaultFont;
	ZeroMemory(&LogDefaultFont,sizeof(LogDefaultFont));

	LogDefaultFont.lfHeight=20;
	_sntprintf_s(LogDefaultFont.lfFaceName,sizeof(LogDefaultFont.lfFaceName),TEXT("微软雅黑"));
	LogDefaultFont.lfWeight=200;
	LogDefaultFont.lfCharSet=DEFAULT_CHARSET;

	m_D3DDefaultFont.CreateFont(LogDefaultFont,0);

	TraceService->TraceString(TraceLevel_Normal,TEXT("init CVirtualEngine"));
}

bool CVirtualEngine::DrawWindows( CD3DDevice * pD3DDevice )
{
	for(INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount(); i++)
	{
		CVirtualWindow * pVirtualWindow = m_VirtualWindowPtrArray.GetAt(i);

		if ( pVirtualWindow->GetParentWindow() != NULL ) continue;
		if ( pVirtualWindow == m_pWindowCapture ) continue;

		pVirtualWindow->InvalidWindow(true);
	}

	//先把父窗口画出来
	if ( m_pWindowCapture && m_pWindowCapture->GetParentWindow() != NULL )
	{
		m_pWindowCapture->GetParentWindow()->InvalidWindow(true);
	}

	//把父窗口上面的所有控件显示出来
	for (INT_PTR i=0;i<m_CaptureWindowPtrArray.GetCount();i++)
	{
		m_CaptureWindowPtrArray.GetAt(i)->InvalidWindow(true);
	}

	return true;
}

bool CVirtualEngine::DefWindowProc( UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	BOOL bHandled = false;

	switch ( uMessage )
	{
	case WM_ACTIVATEAPP:
		{
			if( m_pWindowCapture && m_pWindowCapture->IsWindowEnable() )
			{
				if( wParam )
					m_pWindowCapture->ActiveWindow(true);
				else
					m_pWindowCapture->ActiveWindow(false);
			}

			return false;
		}
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
	case WM_MOUSEWHEEL:
		{
			//消息循环：当某个窗口接收到了
			POINT mousePoint = { short( LOWORD( lParam ) ), short( HIWORD( lParam ) ) };

			if( m_pWindowCapture && m_pWindowCapture->IsWindowEnable() )
			{
 				if( m_pWindowCapture->OnWindowMouse( uMessage, wParam, mousePoint.x,mousePoint.y ) )
 				{
 					return true;
 				}
			}

			CVirtualWindow * pVirtualWindow = SwitchToWindow( mousePoint.x,mousePoint.y );
			
			if( pVirtualWindow != NULL && pVirtualWindow->IsWindowEnable() )
			{
				if( pVirtualWindow != m_pWindowLeave )
				{
					if( m_pWindowLeave ) 
					{
						m_pWindowLeave->OnWindowMouse( WM_MOUSELEAVE, wParam, mousePoint.x,mousePoint.y );
						TraceService->TraceString(TraceLevel_Normal,TEXT("VirtualWindow OnWindowMouse leave"));
					}

					m_pWindowLeave = pVirtualWindow;

					if( pVirtualWindow != NULL ) 
					{
						bHandled = pVirtualWindow->OnWindowMouse( uMessage, wParam, mousePoint.x,mousePoint.y );
						TraceService->TraceString(TraceLevel_Normal,TEXT("VirtualWindow OnWindowMouse begin"));
						if( bHandled ) return true;
					}
				}

				bHandled = pVirtualWindow->OnWindowMouse( uMessage, wParam, mousePoint.x,mousePoint.y );
				if( bHandled ) return true;
			}
			else
			{
				if( uMessage == WM_LBUTTONDOWN && m_pWindowCapture && m_pWindowCapture->GetParentWindow() != NULL)
				{
					m_pWindowCapture->ActiveWindow(false);
					//m_pWindowCapture = NULL;
				}
			}

			switch( uMessage )
			{
			case WM_MOUSEMOVE:
				{
					CVirtualWindow * pVirtualWindow = SwitchToWindow( mousePoint.x,mousePoint.y );

					if( pVirtualWindow == m_pWindowLeave ) return false;

					if( m_pWindowLeave ) 
					{
						m_pWindowLeave->OnWindowMouse( WM_MOUSELEAVE, wParam, mousePoint.x,mousePoint.y );
						TraceService->TraceString(TraceLevel_Normal,TEXT("VirtualWindow OnWindowMouse leave"));
					}
			
					m_pWindowLeave = pVirtualWindow;

					if( pVirtualWindow != NULL ) 
					{
						m_pWindowLeave->OnWindowMouse( WM_MOUSEHOVER, wParam, mousePoint.x,mousePoint.y );
						TraceService->TraceString(TraceLevel_Normal,TEXT("VirtualWindow OnWindowMouse hoven"));
					}

					return false;
				}
			}

			return false;
		}
		//键盘消息
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	case WM_CHAR:
		{
			if( m_pWindowCapture && m_pWindowCapture->IsWindowEnable() && (m_pWindowCapture->GetVirtualEngine() == this) )
			{
				if( m_pWindowCapture->OnEventKeyboard( uMessage, wParam, lParam ) )
					return true;
			}

			break;
		}
	}

	return false;
}

bool CVirtualEngine::PreTranslateMessage( UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc(uMessage,wParam,lParam);
}

bool CVirtualEngine::RegisterLeave( CVirtualWindow * pVirtualWindow, bool bRegister )
{
 	if( bRegister )
 	{
 		for(INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount(); i++)
 		{
 			if( m_VirtualWindowPtrArray.GetAt(i) == pVirtualWindow )
 			{
 				m_VirtualWindowPtrArray.RemoveAt(i);
 				return true;
 			}
 		}
 	}     

	return false;
}

bool CVirtualEngine::RegisterCapture( CVirtualWindow * pVirtualWindow, bool bRegister )
{
 	if( bRegister )
 	{	
		pVirtualWindow->SetFont(&m_D3DDefaultFont);
 		m_VirtualWindowPtrArray.Add(pVirtualWindow);
 		return true;
 	}

	return false;
}

VOID CVirtualEngine::InvalidWindow()
{
 	for(INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount(); i++)
 	{
 		m_VirtualWindowPtrArray.GetAt(i)->InvalidWindow(true);
 	}
}

VOID CVirtualEngine::InvalidWindow( INT nXPos, INT nYPos, INT nWidth, INT nHeight )
{
	//定义变量
	CRect rcRegion(nXPos,nYPos,nXPos+nWidth,nYPos+nHeight);
	CRect rcWindow(0,0,0,0);
	CRect rcDes(0,0,0,0);

 	for(INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount(); i++)
 	{
 		rcWindow.SetRect(0,0,0,0);
 		m_VirtualWindowPtrArray.GetAt(i)->GetWindowRect(rcWindow);
 
 		//规范化客户区
 		rcWindow.NormalizeRect();
 		if( rcDes.IntersectRect(rcWindow,rcRegion) )
 		{
 			m_VirtualWindowPtrArray.GetAt(i)->InvalidWindow(true);
 		}
 	}
}

CVirtualWindow * CVirtualEngine::SwitchToWindow( INT nXMousePos, INT nYMousePos )
{
 	//定义变量
 	CPoint ptMouse(nXMousePos,nYMousePos);
 	CRect rcWindow(0,0,0,0);
 
 	for(INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount(); i++)
 	{
		CVirtualWindow *pVirtualWindow = m_VirtualWindowPtrArray.GetAt(i);
 		rcWindow.SetRect(0,0,0,0);

 		pVirtualWindow->GetWindowRect(rcWindow);
 
 		//规范化客户区
 		rcWindow.NormalizeRect();
 
 		if ( PtInRect(&rcWindow,ptMouse) && pVirtualWindow->IsWindowEnable() && pVirtualWindow->IsWindowVisible() )
 		{ 
 			return pVirtualWindow;
  		}
 	}

	return NULL;
}

CVirtualWindow * CVirtualEngine::SwitchToWindow( CVirtualWindow * pVirtualWindow, INT nXMousePos, INT nYMousePos )
{
	if( pVirtualWindow == NULL ) return NULL;

	//定义变量
	CPoint ptMouse(nXMousePos,nYMousePos);
	CRect rcWindow(0,0,0,0);

	for(INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount(); i++)
	{
		rcWindow.SetRect(0,0,0,0);
		CVirtualWindow *pOwnVirtualWindow = m_VirtualWindowPtrArray.GetAt(i);

		if ( pOwnVirtualWindow->GetParentWindow() == pVirtualWindow )
		{
			pOwnVirtualWindow->GetWindowRect(rcWindow);

			//规范化客户区
			rcWindow.NormalizeRect();

			if ( PtInRect(&rcWindow,ptMouse) && pOwnVirtualWindow->IsWindowEnable() && pOwnVirtualWindow->IsWindowVisible() )
			{ 
				return pOwnVirtualWindow;
			}
		}
	}

	return NULL;
}

VOID CVirtualEngine::RequestFocus( CVirtualWindow * pVirtualWindow )
{
	if( m_pWindowCapture && (m_pWindowCapture != pVirtualWindow) )
		m_pWindowCapture->ActiveWindow(false);

	if( m_pWindowCapture == pVirtualWindow ) return;

	m_pWindowCapture = pVirtualWindow;
	
	//如果是子控件获取焦点，需要把整个父窗口上面的所有控件的z轴全部往前挪，置前显示
	if( m_pWindowCapture != NULL)
	{
		m_pWindowCapture->ActiveWindow(true);

		CVirtualWindow * pCaptureWindow = m_pWindowCapture->GetParentWindow();

		if ( pCaptureWindow != NULL )
		{
			for (int i=0;i<m_VirtualWindowPtrArray.GetCount();i++)
			{
				CVirtualWindow * pCaptureWindowTemp = m_VirtualWindowPtrArray.GetAt(i);

				if ( pCaptureWindowTemp->GetParentWindow() == pCaptureWindow )
				{
					m_CaptureWindowPtrArray.Add(pCaptureWindowTemp);
				}
			}
			
			//把父窗口自身也添加进来
			m_CaptureWindowPtrArray.Add(pCaptureWindow);
		}
		else
			m_CaptureWindowPtrArray.Add(m_pWindowCapture);
	}
	else
	{
		m_CaptureWindowPtrArray.RemoveAll();
	}
}


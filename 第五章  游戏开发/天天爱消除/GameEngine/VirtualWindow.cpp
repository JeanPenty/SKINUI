#include "stdafx.h"
#include "VirtualWindow.h"


CVirtualWindow::CVirtualWindow()
{
	//窗口属性
	m_bActive = false;							
	m_bEnable = true;							
	m_bVisible = false;							

	//属性变量
	m_uWindowID = 0;	
	m_bCaption = FALSE;	
	m_bDrag = FALSE;	

	//位置变量
	m_WindowSize.SetSize(0,0);						
	m_BenchmarkPos.SetPoint(0,0);						

	//内核变量
	m_pParentWindow = NULL;					
	m_pVirtualEngine=NULL;	
	m_pDefaultFont = NULL;
	m_VirtualWindowPtrArray.RemoveAll();	
}

CVirtualWindow::~CVirtualWindow()
{
}

VOID CVirtualWindow::DeleteWindow()
{
	if ( m_pVirtualEngine == NULL ) return;
	
	//销毁自己
	KillFocus();
	OnWindowDestory(m_pVirtualEngine->GetD3DDevice());
	m_pVirtualEngine->RegisterLeave(this,true);
	
	//销毁所有子窗口
	for (INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount();i++)
	{
		CVirtualWindow *pVirtualWindow = m_VirtualWindowPtrArray.GetAt(i);

		pVirtualWindow->KillFocus();
		pVirtualWindow->OnWindowDestory(m_pVirtualEngine->GetD3DDevice());
		m_pVirtualEngine->RegisterLeave(pVirtualWindow,true);

		TraceService->TraceString(TraceLevel_Normal,TEXT("destory Window ID:[ %d ]"),pVirtualWindow->m_uWindowID);
	}

	TraceService->TraceString(TraceLevel_Normal,TEXT("destory Window ID:[ %d ]"),m_uWindowID);

	m_VirtualWindowPtrArray.RemoveAll();
}

bool CVirtualWindow::ActiveWindow( CRect & rcWindow, DWORD dwStyle, UINT uWindowID, CVirtualEngine * pVirtualEngine, CVirtualWindow * pParentWindow )
{
	m_BenchmarkPos.SetPoint(rcWindow.left,rcWindow.top);
	m_WindowSize.SetSize(rcWindow.Width(),rcWindow.Height());

	m_uWindowID = uWindowID;

	m_pVirtualEngine = pVirtualEngine;
	m_pParentWindow = pParentWindow;
	m_bActive = true;

	if ( dwStyle & WS_VISIBLE ) m_bVisible = true;
	if ( dwStyle & WS_DISABLED ) m_bEnable = false;
	
	//创建控件
	OnWindowCreate(m_pVirtualEngine->GetD3DDevice());

	if ( pParentWindow != NULL )
	{
		pParentWindow->m_VirtualWindowPtrArray.Add(this);
	}

	m_pVirtualEngine->RegisterCapture(this,true);

	TraceService->TraceString(TraceLevel_Normal,TEXT("Create Window ID:[ %d ]"),m_uWindowID);

	return true;
}

VOID CVirtualWindow::ActiveWindow( bool bActive )
{
	m_bActive = bActive;
}

VOID CVirtualWindow::ShowWindow( bool bVisible )
{
	m_bVisible = bVisible;

	for (INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount();i++)
	{
		m_VirtualWindowPtrArray.GetAt(i)->m_bVisible = bVisible;
	}
}

VOID CVirtualWindow::EnableWindow( bool bEnable )
{
	m_bEnable = bEnable;

	for (INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount();i++)
	{
		m_VirtualWindowPtrArray.GetAt(i)->m_bEnable = bEnable;
	}
}

VOID CVirtualWindow::InvalidWindow( bool bCoerce )
{
	if ( !m_bVisible ) return;

	OnEventDrawWindow(m_pVirtualEngine->GetD3DDevice(),m_BenchmarkPos.x,m_BenchmarkPos.y);

	OnWindowMovie();

	if( bCoerce )
	{
		OnEventDrawChildWindow(m_pVirtualEngine->GetD3DDevice(),0,0);
	}
}

VOID CVirtualWindow::GetClientRect( CRect & rcClient )
{
	rcClient.SetRect(0,0,m_WindowSize.cx,m_WindowSize.cy);
}

VOID CVirtualWindow::GetWindowRect( CRect & rcWindow )
{
	rcWindow.SetRect(m_BenchmarkPos.x,m_BenchmarkPos.y,m_BenchmarkPos.x+m_WindowSize.cx,m_BenchmarkPos.y+m_WindowSize.cy);
}

VOID CVirtualWindow::SetWindowPos( INT nXPos, INT nYPos, INT nWidth, INT nHeight, UINT uFlags )
{
	int xOld = m_BenchmarkPos.x;
	int yOld = m_BenchmarkPos.y;

	if ( uFlags & SWP_HIDEWINDOW ) ShowWindow(SW_HIDE);
	if ( uFlags & SWP_NOACTIVATE ) m_bActive = false;

	if ((uFlags & (SWP_NOMOVE|SWP_NOSIZE)) != (SWP_NOMOVE|SWP_NOSIZE))
	{
		int xNew;
		int yNew;

		if (uFlags & SWP_NOMOVE) { xNew = m_BenchmarkPos.x; yNew = m_BenchmarkPos.y; }
		else { xNew = nXPos; yNew = nYPos; }

		int cxNew;
		int cyNew;

		if (uFlags & SWP_NOSIZE) { cxNew = m_WindowSize.cx; cyNew = m_WindowSize.cy; }
		else { cxNew = nWidth; cyNew = nHeight; }

		CRect rectOld(m_BenchmarkPos.x,m_BenchmarkPos.y,m_BenchmarkPos.x+m_WindowSize.cx,m_BenchmarkPos.y+m_WindowSize.cy);

		m_BenchmarkPos.SetPoint(xNew,yNew);
		m_WindowSize.SetSize(cxNew,cyNew);
	}

	if (uFlags & SWP_SHOWWINDOW) ShowWindow(true);

// 	uFlags &= ~(SWP_HIDEWINDOW|SWP_SHOWWINDOW);
// 	uFlags |= (SWP_NOMOVE|SWP_NOSIZE);

	for (INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount();i++)
	{
		CVirtualWindow *pVirtualWindow = m_VirtualWindowPtrArray.GetAt(i);

		CPoint pt(pVirtualWindow->m_BenchmarkPos.x+nXPos-xOld,pVirtualWindow->m_BenchmarkPos.y+nYPos-yOld);

		pVirtualWindow->SetWindowPos(pt.x,pt.y,0,0,SWP_NOSIZE);
	}

	OnWindowPosition(m_pVirtualEngine->GetD3DDevice());

	InvalidWindow(true);
}

//拖动窗口
BOOL CVirtualWindow::DragWindows( UINT uMessage, INT nXMousePos, INT nYMousePos, UINT nFlags )
{
	if( m_bDrag )
	{
		static INT nOldXMousePos = 0;
		static INT nOldYMousePos = 0;

		if ( uMessage == WM_LBUTTONDOWN )
		{
			nOldXMousePos = nXMousePos-m_BenchmarkPos.x;
			nOldYMousePos = nYMousePos-m_BenchmarkPos.y;

			//SetFocus();
		}

		if ( uMessage == WM_MOUSEMOVE && nFlags == MK_LBUTTON )
		{
			//基准位置
			INT nXPos=nXMousePos-nOldXMousePos;
			INT nYPos=nYMousePos-nOldYMousePos;

			SetWindowPos(nXPos,nYPos,0,0,SWP_NOSIZE);

			return TRUE;
		}
	}

	return FALSE;
}

bool CVirtualWindow::IsChildWindow( CVirtualWindow * pVirtualWindow )
{
	for (INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount();i++)
	{
		if ( m_VirtualWindowPtrArray.GetAt(i)->GetParentWindow() == pVirtualWindow )
		{
			return true;
		}
	}

	return false;
}

VOID CVirtualWindow::ResetWindow()
{
	//窗口属性
	m_bActive = false;							
	m_bEnable = true;							
	m_bVisible = false;							

	//属性变量
	m_uWindowID = 0;						

	//位置变量
	m_WindowSize.SetSize(0,0);						
	m_BenchmarkPos.SetPoint(0,0);						

	//内核变量
	m_pParentWindow = NULL;					
	m_pVirtualEngine=NULL;					
	m_VirtualWindowPtrArray.RemoveAll();	
}

VOID CVirtualWindow::OnEventDrawChildWindow( CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos )
{
	CVirtualWindow *pVirtualWindow = NULL;

	for (INT_PTR i=0;i<m_VirtualWindowPtrArray.GetCount();i++)
	{
		pVirtualWindow = m_VirtualWindowPtrArray.GetAt(i);

		//CPoint pt(pVirtualWindow->m_BenchmarkPos.x+nXOriginPos,pVirtualWindow->m_BenchmarkPos.y+nYOriginPos);
		pVirtualWindow->OnEventDrawWindow(pD3DDevice,pVirtualWindow->m_BenchmarkPos.x,pVirtualWindow->m_BenchmarkPos.y);
		pVirtualWindow->OnWindowMovie();
	}
}

HWND CVirtualWindow::GetSafeHwnd()
{
	ASSERT(m_pVirtualEngine != NULL);
	if( m_pVirtualEngine == NULL ) return NULL;

	return m_pVirtualEngine->GetD3DDevice()->GetWndDevice();
}

VOID CVirtualWindow::SetFocus()
{
	m_pVirtualEngine->RequestFocus(this);
}

VOID CVirtualWindow::KillFocus()
{
	m_pVirtualEngine->RequestFocus(NULL);
}

BOOL CVirtualWindow::OnWindowMouse( UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos )
{
	if( m_bCaption )
	{
		if( uMessage == WM_LBUTTONDOWN || uMessage == WM_LBUTTONDBLCLK )
		{
			if( nXMousePos >= m_BenchmarkPos.x && nXMousePos < m_BenchmarkPos.x + m_WindowSize.cx &&
				nYMousePos >= m_BenchmarkPos.y && nYMousePos < m_BenchmarkPos.y + m_WindowSize.cy )
			{
				SetFocus();
				m_bDrag = true;
			}
		}
		else if( uMessage == WM_LBUTTONUP && m_bDrag )
		{
			if( nXMousePos >= m_BenchmarkPos.x && nXMousePos < m_BenchmarkPos.x + m_WindowSize.cx &&
				nYMousePos >= m_BenchmarkPos.y && nYMousePos < m_BenchmarkPos.y + m_WindowSize.cy )
			{
				m_bDrag = false;
			}
		}
	}

	return OnEventMouse(uMessage, nFlags, nXMousePos, nYMousePos);
}

BOOL CVirtualWindow::ContainsPoint( POINT pt )
{
	CRect rcControl(0,0,0,0);
	GetWindowRect(rcControl);

	return PtInRect( &rcControl, pt );
}

void CVirtualWindow::SetFont( CD3DFont*pFont )
{
	m_pDefaultFont = pFont;
}

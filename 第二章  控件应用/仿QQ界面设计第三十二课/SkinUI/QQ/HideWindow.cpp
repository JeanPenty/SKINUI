#include "StdAfx.h"
#include "HideWindow.h"



#define INTERVAL    20  //����ճ��ʱ�������Ļ�߽����С���,��λΪ����
#define INFALTE     20  //��������ʱ����봰�ڱ߽����С���,��λΪ����

//��ʱ��
#define IDI_CHECKMOUSE		5000		//����뿪����
#define IDI_BEGINHIDE		5001		//�����ƶ���ʶ

#define CM_ELAPSE   		300			//����뿪����
#define BH_ELAPSE   		20			//�����ƶ�ʱ��

#define STEPS_COUNT    		7			//�ܹ�����

CHideWindow::CHideWindow(void)
{
	m_bSized = false;
	m_bTimed = false;
	m_bFinished = true;
	m_bHiding = false;

	m_nWindowHeight = WND_MINSIZE_Y;
	m_nTaskBarHeight = 30;
	m_nEdgeHeight = 0;
	m_nEdgeWidth  =0;
	m_enHideType = en_None;
	m_hOwnHwnd = NULL;
}

CHideWindow::~CHideWindow(void)
{
}

void CHideWindow::HideWindow()
{
	if( m_hOwnHwnd == NULL ) return;

	if(m_enHideType == en_None) return;

	CRect rcWindow;
	::GetWindowRect(m_hOwnHwnd,rcWindow);

	INT nHeight = rcWindow.Height();
	INT nWidth  = rcWindow.Width();

	//����
	INT nStride = 0;

	switch(m_enHideType)
	{
	case en_Top:
		{
			nStride = nHeight/STEPS_COUNT;
			rcWindow.bottom -= nStride;

			if(rcWindow.bottom <= m_nEdgeWidth)
			{
				rcWindow.bottom = m_nEdgeWidth;
				m_bFinished = true;
			}
			rcWindow.top = rcWindow.bottom - nHeight; 
		}
		break;
	case en_Bottom:
		{
			nStride = nHeight/STEPS_COUNT;
			rcWindow.top += nStride;
			if(rcWindow.top >= (GetSystemMetrics(SM_CYSCREEN) - m_nEdgeWidth))
			{
				rcWindow.top = GetSystemMetrics(SM_CYSCREEN) - m_nEdgeWidth;
				m_bFinished = true;
			}
			rcWindow.bottom = rcWindow.top + nHeight;
		}
		break;
	case en_Left:
		{
			nStride = nWidth/STEPS_COUNT;
			rcWindow.right -= nStride;
			if(rcWindow.right <= m_nEdgeWidth)
			{
				rcWindow.right = m_nEdgeWidth;
				m_bFinished = true;
			}
			rcWindow.left = rcWindow.right - nWidth;
			rcWindow.top = -m_nEdgeHeight;
			rcWindow.bottom = GetSystemMetrics(SM_CYSCREEN) - m_nTaskBarHeight;
		}
		break;
	case en_Right:
		{
			nStride = nWidth/STEPS_COUNT;
			rcWindow.left += nStride;
			if(rcWindow.left >= (GetSystemMetrics(SM_CXSCREEN) - m_nEdgeWidth))
			{
				rcWindow.left = GetSystemMetrics(SM_CXSCREEN) - m_nEdgeWidth;
				m_bFinished = true;
			}		
			rcWindow.right = rcWindow.left + nWidth;
			rcWindow.top = -m_nEdgeHeight;
			rcWindow.bottom = GetSystemMetrics(SM_CYSCREEN) - m_nTaskBarHeight;
		}
		break;
	}

	SetWindowPos(HWND_TOPMOST,rcWindow);
}

void CHideWindow::ShowWindow()
{
	if( m_hOwnHwnd == NULL ) return;
	if(m_enHideType == en_None) return;

	CRect rcWindow;
	::GetWindowRect(m_hOwnHwnd,rcWindow);

	INT nHeight = rcWindow.Height();
	INT nWidth  = rcWindow.Width();

	INT nStride = 0;

	switch(m_enHideType)
	{
	case en_Top:
		{
			nStride = nHeight/STEPS_COUNT;
			rcWindow.top += nStride;
			if(rcWindow.top >= -m_nEdgeHeight)
			{
				rcWindow.top = -m_nEdgeHeight;
				m_bFinished = true;
			}
			rcWindow.bottom = rcWindow.top + nHeight;
		}
		break;
	case en_Bottom:
		{
			nStride = nHeight/STEPS_COUNT;
			rcWindow.top -= nStride;
			if(rcWindow.top <= (GetSystemMetrics(SM_CYSCREEN) - nHeight))
			{
				rcWindow.top = GetSystemMetrics(SM_CYSCREEN) - nHeight;
				m_bFinished = true;
			}
			rcWindow.bottom = rcWindow.top + nHeight;
		}
		break;
	case en_Left:
		{
			nStride = nWidth/STEPS_COUNT;
			rcWindow.right += nStride;
			if(rcWindow.right >= nWidth)
			{
				rcWindow.right = nWidth;
				m_bFinished = true;
			}
			rcWindow.left = rcWindow.right - nWidth;
			rcWindow.top = -m_nEdgeHeight;
			rcWindow.bottom = GetSystemMetrics(SM_CYSCREEN) - m_nTaskBarHeight;
		}
		break;
	case en_Right:
		{
			nStride = nWidth/STEPS_COUNT;
			rcWindow.left -= nStride;
			if(rcWindow.left <= (GetSystemMetrics(SM_CXSCREEN) - nWidth))
			{
				rcWindow.left = GetSystemMetrics(SM_CXSCREEN) - nWidth;
				m_bFinished = true;
			}
			rcWindow.right = rcWindow.left + nWidth;
			rcWindow.top = -m_nEdgeHeight;
			rcWindow.bottom = GetSystemMetrics(SM_CYSCREEN) - m_nTaskBarHeight;
		}
		break;
	}

	SetWindowPos(HWND_TOPMOST,rcWindow);
}

BOOL CHideWindow::SetWindowPos(HWND hWndInsertAfter, LPCRECT pCRect, UINT nFlags)
{
	return ::SetWindowPos(m_hOwnHwnd,hWndInsertAfter,pCRect->left, pCRect->top,
		(pCRect->right - pCRect->left), (pCRect->bottom - pCRect->top), nFlags);
}

void CHideWindow::FixMoving(UINT fwSide, LPRECT pRect)
{
	CPoint point;
	::GetCursorPos(&point);

	INT nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	INT nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	INT nHeight = pRect->bottom - pRect->top;
	INT nWidth  = pRect->right - pRect->left;

	//ճ�����ϱ�
	if (point.y <= INTERVAL)
	{  
		pRect->bottom = nHeight - m_nEdgeHeight;
		pRect->top = -m_nEdgeHeight;
		m_enHideType = en_Top;
	}
	//ճ�����±�
	else if(point.y >= (nScreenHeight - INTERVAL - m_nTaskBarHeight))
	{   
		pRect->top = nScreenHeight - m_nTaskBarHeight - nHeight;
		pRect->bottom = nScreenHeight - m_nTaskBarHeight;
		m_enHideType = en_Bottom;
	}
	//ճ�������	
	else if (point.x < INTERVAL)
	{	
		if(!m_bSized)
		{
			CRect tRect;
			::GetWindowRect(m_hOwnHwnd,tRect);
			m_nWindowHeight = tRect.Height();			
		}
		pRect->right = nWidth;
		pRect->left = 0;
		pRect->top = -m_nEdgeHeight;
		pRect->bottom = nScreenHeight - m_nTaskBarHeight;
		m_bSized = TRUE;
		m_enHideType = en_Left;
	}
	//ճ�����ұ�
	else if(point.x >= (nScreenWidth - INTERVAL))
	{   
		if(!m_bSized)
		{
			CRect tRect;
			::GetWindowRect(m_hOwnHwnd,tRect);
			m_nWindowHeight = tRect.Height();						
		}
		pRect->left = nScreenWidth - nWidth;
		pRect->right = nScreenWidth;
		pRect->top = -m_nEdgeHeight;
		pRect->bottom = nScreenHeight - m_nTaskBarHeight;
		m_bSized = true;
		m_enHideType = en_Right;
	}
	//��ճ��
	else
	{   
		if(m_bSized)
		{  
			pRect->bottom = pRect->top + m_nWindowHeight;
			m_bSized = false;
			InvalidateRect(m_hOwnHwnd,NULL,FALSE);
			SetWindowPos(HWND_TOPMOST,CRect(pRect->left,pRect->top,pRect->right,m_nWindowHeight));
		}
		
		//���Timer������,��ر�֮
		if(m_bTimed)
		{  
			if(::KillTimer(m_hOwnHwnd,IDI_CHECKMOUSE) == 1)
				m_bTimed = false;
		}
		m_enHideType = en_None;
	}
}

void CHideWindow::FixSizing(UINT fwSide, LPRECT pRect)
{
	if( m_bFinished ) return;

	CRect rcClient(pRect);

	if(rcClient.Width() < WND_MINSIZE_X || rcClient.Height() < WND_MINSIZE_Y)
	{ 
		switch(fwSide)
		{
		case WMSZ_BOTTOM:
			{
				pRect->bottom = pRect->top + WND_MINSIZE_Y;
			}
			break;
		case WMSZ_BOTTOMLEFT:
			{
				if(rcClient.Width() <= WND_MINSIZE_X)
					pRect->left = pRect->right - WND_MINSIZE_X;
				if(rcClient.Height() <= WND_MINSIZE_Y)
					pRect->bottom = pRect->top + WND_MINSIZE_Y;
			}
			break;
		case WMSZ_BOTTOMRIGHT:
			{
				if(rcClient.Width() < WND_MINSIZE_X)
					pRect->right = pRect->left + WND_MINSIZE_X;
				if(rcClient.Height() < WND_MINSIZE_Y)
					pRect->bottom = pRect->top + WND_MINSIZE_Y;
			}
			break;
		case WMSZ_LEFT:
			{
				pRect->left = pRect->right - WND_MINSIZE_X;
			}
			break;
		case WMSZ_RIGHT:
			{
				pRect->right = pRect->left + WND_MINSIZE_X;
			}
			break;
		case WMSZ_TOP:
			{
				pRect->top = pRect->bottom - WND_MINSIZE_Y;
			}
			break;
		case WMSZ_TOPLEFT:
			{
				if(rcClient.Width() <= WND_MINSIZE_X)
					pRect->left = pRect->right - WND_MINSIZE_X;
				if(rcClient.Height() <= WND_MINSIZE_Y)
					pRect->top = pRect->bottom - WND_MINSIZE_Y;
			}
			break;
		case WMSZ_TOPRIGHT:
			{
				if(rcClient.Width() < WND_MINSIZE_X)
					pRect->right = pRect->left + WND_MINSIZE_X;
				if(rcClient.Height() < WND_MINSIZE_Y)
					pRect->top = pRect->bottom - WND_MINSIZE_Y;
			}
			break;
		}
	}
}

void CHideWindow::HideLoop( UINT nIDEvent )
{
	if(nIDEvent == IDI_CHECKMOUSE )
	{
		CPoint point;
		GetCursorPos(&point);

		CRect rcWindow;
		::GetWindowRect(m_hOwnHwnd,rcWindow);
		
		rcWindow.InflateRect(INFALTE,INFALTE); 

		if(!rcWindow.PtInRect(point))
		{
			::KillTimer(m_hOwnHwnd,IDI_CHECKMOUSE);
			m_bTimed = false;

			m_bFinished = false;			
			m_bHiding = true;
			::SetTimer(m_hOwnHwnd,IDI_BEGINHIDE,BH_ELAPSE,NULL);
		}
		::InvalidateRect(m_hOwnHwnd,NULL,FALSE);
	}
	else if(nIDEvent == IDI_BEGINHIDE)
	{
		if(m_bFinished) 
			::KillTimer(m_hOwnHwnd,IDI_BEGINHIDE);
		else
			m_bHiding ? HideWindow() : ShowWindow();	

		::InvalidateRect(m_hOwnHwnd,NULL,FALSE);
	}
}

void CHideWindow::BeginHide(CPoint point)
{
	if( (m_enHideType != en_None) && !m_bTimed && (point.x < GetSystemMetrics(SM_CXSCREEN) + INFALTE))
	{   
		::SetTimer(m_hOwnHwnd,IDI_CHECKMOUSE,CM_ELAPSE,NULL);
		m_bTimed = true;

		m_bFinished = false;
		m_bHiding = false;
		::SetTimer(m_hOwnHwnd,IDI_BEGINHIDE,BH_ELAPSE,NULL); //������ʾ����
	}
}

void CHideWindow::SetHideWindow( HWND hWnd,int nEdgeHeight/*=3*/,int nEdgeWidth/*=3*/ )
{
	m_hOwnHwnd = hWnd;

	//��ñ�Ե�߶ȺͿ��
	m_nEdgeHeight = nEdgeHeight;
	m_nEdgeWidth  = nEdgeWidth;
}


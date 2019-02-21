// SkinSliderCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinUI.h"
#include "SkinSliderCtrl.h"


// CSkinSliderCtrl

IMPLEMENT_DYNAMIC(CSkinSliderCtrl, CSliderCtrl)

CSkinSliderCtrl::CSkinSliderCtrl()
{
	m_pBackImg = m_pThumImg = m_pDisImg = m_pBtImg = m_pTraceImg = NULL;
	m_bPress = m_bHover = m_bMouseTracking = FALSE;
	m_bDragging = false;
	m_rcThumRect.SetRect(0,0,0,0);
	m_szThum.SetSize(0,0);
}

CSkinSliderCtrl::~CSkinSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CSkinSliderCtrl, CSliderCtrl)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

BOOL CSkinSliderCtrl::SetBackImage( LPCTSTR lpszFileName,bool bFixed/* = true*/ )
{
	RenderEngine->RemoveImage(m_pBackImg);

	m_pBackImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pBackImg)
		return FALSE;
	else
	{
		if(bFixed) SetWindowPos(NULL,0,0,m_pBackImg->GetWidth(),m_pBackImg->GetHeight(),SWP_NOMOVE);
		
		return TRUE;
	}
}

BOOL CSkinSliderCtrl::SetThumImage( LPCTSTR lpszFileName )
{
	RenderEngine->RemoveImage(m_pThumImg);

	m_pThumImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pThumImg)
		return FALSE;
	else
	{
		m_szThum.SetSize(m_pThumImg->GetWidth(),m_pThumImg->GetHeight());
		m_rcThumRect.SetRect(0,0,m_szThum.cx,m_szThum.cy);
		SetThumbRect();
		SetChannelRect();
		return TRUE;
	}
}

BOOL CSkinSliderCtrl::SetDisImage( LPCTSTR lpszFileName )
{
	RenderEngine->RemoveImage(m_pDisImg);

	m_pDisImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pDisImg)
		return FALSE;
	else
		return TRUE;
}

BOOL CSkinSliderCtrl::SetTraceImage( LPCTSTR lpszFileName,CONST LPRECT lprcNinePart/*=NULL*/ )
{
	RenderEngine->RemoveImage(m_pTraceImg);

	m_pTraceImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pTraceImg)
		return FALSE;
	else
	{
		m_pTraceImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CSkinSliderCtrl::SetButtonImage( LPCTSTR lpszFileName )
{
	RenderEngine->RemoveImage(m_pBtImg);

	m_pBtImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pBtImg)
		return FALSE;
	else
	{
		m_szThum.SetSize(m_pBtImg->GetWidth()/3,m_pBtImg->GetHeight());
		m_rcThumRect.SetRect(0,0,m_szThum.cx,m_szThum.cy);
		SetThumbRect();
		SetChannelRect();
		return TRUE;
	}
}

// CSkinSliderCtrl ��Ϣ�������
void CSkinSliderCtrl::OnDestroy()
{
	CSliderCtrl::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImg);
	RenderEngine->RemoveImage(m_pThumImg);
	RenderEngine->RemoveImage(m_pDisImg);
	RenderEngine->RemoveImage(m_pBtImg);
	RenderEngine->RemoveImage(m_pTraceImg);
}

void CSkinSliderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC MemDC(&dc, rcClient);

	//���Ʊ���
	DrawParentWndBg(GetSafeHwnd(),MemDC->GetSafeHdc());

	//���ƹ켣
	if ( !IsWindowEnabled() )
	{
		if (m_pDisImg != NULL && !m_pDisImg->IsNull())
		{
			m_pDisImg->DrawImage(&MemDC,0,0);
		}		
	}
	else
	{
		if (m_pBackImg != NULL && !m_pBackImg->IsNull())
		{
			m_pBackImg->DrawImage(&MemDC,0,0);
		}
	}

	//���ƺۼ�
	if (m_pTraceImg != NULL && !m_pTraceImg->IsNull())
	{
		m_pTraceImg->Draw(&MemDC,CRect(0, 0,m_rcThumRect.left,m_pTraceImg->GetHeight()));
	}

	//���ƻ���
	if (m_pThumImg != NULL && !m_pThumImg->IsNull())
	{
		m_pThumImg->DrawImage(&MemDC,m_rcThumRect.left, m_rcThumRect.top);
	}

	//���ư�ť
	if (m_pBtImg != NULL && !m_pBtImg->IsNull())
	{
		if( m_bPress )
			m_pBtImg->DrawImage(&MemDC,m_rcThumRect.left, m_rcThumRect.top,m_szThum.cx,m_szThum.cy,m_szThum.cx*2,0);
		else if ( m_bHover )
			m_pBtImg->DrawImage(&MemDC,m_rcThumRect.left, m_rcThumRect.top,m_szThum.cx,m_szThum.cy,m_szThum.cx,0);
		else 
			m_pBtImg->DrawImage(&MemDC,m_rcThumRect.left, m_rcThumRect.top,m_szThum.cx,m_szThum.cy,0,0);
	}
}

void CSkinSliderCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_bDragging )
	{
		int nMax = 0;
		int nMin = 0;
		GetRange(nMin,nMax);
		
		int nPos = 0;
		if ( GetStyle() & TBS_VERT )
			nPos = (nMax - nMin)*(point.y)/m_rcChannelRect.Height(); 
		else 
			nPos = (nMax - nMin)*(point.x)/m_rcChannelRect.Width(); 

		SetPos(nPos);

		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	//��ť�¼�
	if ( PtInRect(m_rcThumRect,point) && !m_bMouseTracking )
	{
		TrackMouseLeave(GetSafeHwnd());

		m_bMouseTracking = TRUE;
		m_bHover = TRUE;
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	__super::OnMouseMove(nFlags, point);
}

//����뿪��Ϣ
LRESULT CSkinSliderCtrl::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bMouseTracking = FALSE;
	m_bHover = FALSE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	return 0;
}

void CSkinSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ( PtInRect(&m_rcThumRect,point) )
	{
		m_bDragging = true;
		m_bPress = TRUE;
		SetCapture();

		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
 	else
 	{
 		if ( PtInRect(&m_rcChannelRect,point) )
 		{
 			int nMax = 0;  
 			int nMin = 0;  
 			GetRange(nMin,nMax);  
 
			int nPos = 0;

			if ( GetStyle() & TBS_VERT )
 				nPos = (nMax - nMin)*(point.y - m_rcChannelRect.top)/m_rcChannelRect.Height(); 
			else 
				nPos = (nMax - nMin)*(point.x - m_rcChannelRect.left)/m_rcChannelRect.Width(); 
 
 			OutputString(TEXT("Down:%d\n"),nPos);
 			nPos += nMin;
 			SetPos(nPos); 
 			RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
 			return;
 		}
 	}

	__super::OnLButtonDown(nFlags, point);
}

void CSkinSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ( PtInRect(&m_rcThumRect,point) && m_bPress) m_bPress = FALSE;

	m_bDragging = false;
	ReleaseCapture();
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	
	__super::OnLButtonUp(nFlags, point);
}

BOOL CSkinSliderCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CSkinSliderCtrl::SetThumbRect(int nPos)
{	
	CRect rcClient;
	GetClientRect(&rcClient);

	//�ж��Ƿ�����ؼ�
	if ( GetStyle() & TBS_VERT )
	{
		m_rcThumRect.left = (rcClient.Width()-m_szThum.cx)/2;
		m_rcThumRect.top = nPos;
	}
	else
	{
		m_rcThumRect.left = nPos;
		m_rcThumRect.top = (rcClient.Height()-m_szThum.cy)/2;
	}

	m_rcThumRect.right = m_rcThumRect.left+m_szThum.cx;
	m_rcThumRect.bottom = m_rcThumRect.top+m_szThum.cy;
}

void CSkinSliderCtrl::SetPos( int nPos )
{
	int nMin,nMax;
	GetRange(nMin,nMax);

	//���¶�λ����ֹ�����ͻ���
	if( nPos <= nMin ) nPos = nMin;
	if ( nPos >= nMax ) nPos = nMax;
	
	__super::SetPos(nPos);

	int nPosNew = 0;

	if ( GetStyle() & TBS_VERT )

		nPosNew = m_rcChannelRect.Height()*nPos/(nMax-nMin);
	else 
		nPosNew = m_rcChannelRect.Width()*nPos/(nMax-nMin);
	
	if( nPosNew<0 ) nPosNew = 0;

	SetThumbRect(nPosNew);

	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

void CSkinSliderCtrl::SetChannelRect()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	//���ù켣����
	if ( GetStyle() & TBS_VERT )
		m_rcChannelRect.SetRect(0,m_szThum.cy/2,rcClient.Width(),rcClient.Height()-m_szThum.cy/2);
	else 
		m_rcChannelRect.SetRect(m_szThum.cx/2,0,rcClient.Width()-m_szThum.cx/2,rcClient.Height());
}

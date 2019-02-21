// ButtonEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinButton.h"


// CSkinButton

IMPLEMENT_DYNAMIC(CSkinButton, CButton)

CSkinButton::CSkinButton()
{
	m_pBackImgN = m_pBackImgH = m_pBackImgD = m_pBackImgF = NULL;
	m_pCheckImgN = m_pCheckImgH = m_pCheckImgTickN = m_pCheckImgTickH = NULL;
	m_pArrowImg = m_pIconImg = NULL;
	
	m_bFocus = m_bPress = m_bHover = m_bMouseTracking = FALSE;
	m_nBtnType = en_PushButton;

	m_hMenu = NULL;
	m_hBackDC = NULL;
	m_bPushed = false;
}

CSkinButton::~CSkinButton()
{
}


BEGIN_MESSAGE_MAP(CSkinButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CSkinButton ��Ϣ�������
void CSkinButton::SetButtonType( UI_BUTTON_TYPE type )
{
	m_nBtnType = type;
}

//����ƶ���Ϣ
void CSkinButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseTracking)
	{
		TrackMouseLeave(GetSafeHwnd());

		m_bMouseTracking = TRUE;
		m_bHover = TRUE;
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	__super::OnMouseMove(nFlags, point);
}

//����뿪��Ϣ
LRESULT CSkinButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bMouseTracking = FALSE;
	m_bHover = FALSE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	return 0;
}

//��갴����Ϣ
void CSkinButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bPress = TRUE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	__super::OnLButtonDown(nFlags, point);
}

//���̧����Ϣ
void CSkinButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bPress)
	{
		static bool bPushed = false;

		if( !m_bPushed && !bPushed )
			m_bPress = FALSE;
		
		if ( m_bPushed )
		{
			if( bPushed ) m_bPress = FALSE;
			else m_bPress = TRUE;

			bPushed = !bPushed;
		}

				
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
		
		if (m_nBtnType == en_MenuButton)
		{
			if (::IsMenu(m_hMenu))
			{
				CRect rc;
				GetClientRect(&rc);
				ClientToScreen(&rc);
				::TrackPopupMenuEx(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
					rc.left, rc.bottom, ::GetParent(GetSafeHwnd()), NULL);
			}
		}
	}

	__super::OnLButtonUp(nFlags, point);
}

//���˫����Ϣ
void CSkinButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_bPress = TRUE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	__super::OnLButtonDown(nFlags, point);
}

//��ȡ������Ϣ
void CSkinButton::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	m_bFocus = TRUE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

//ʧȥ������Ϣ
void CSkinButton::OnKillFocus(CWnd* pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	m_bFocus = FALSE;
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

//�ػ���Ϣ
BOOL CSkinButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

//������Դ
BOOL CSkinButton::SetBackImage( LPCTSTR lpNormal, LPCTSTR lpHoven, LPCTSTR lpDown, LPCTSTR lpFocus,CONST LPRECT lprcNinePart/*=NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pBackImgD);
	RenderEngine->RemoveImage(m_pBackImgF);

	m_pBackImgN = RenderEngine->GetImage(lpNormal);
	m_pBackImgH = RenderEngine->GetImage(lpHoven);
	m_pBackImgD = RenderEngine->GetImage(lpDown);
	m_pBackImgF = RenderEngine->GetImage(lpFocus);

	if( lprcNinePart != NULL )
	{
		if (m_pBackImgN != NULL)
			m_pBackImgN->SetNinePart(lprcNinePart);

		if (m_pBackImgH != NULL)
			m_pBackImgH->SetNinePart(lprcNinePart);

		if (m_pBackImgD != NULL)
			m_pBackImgD->SetNinePart(lprcNinePart);

		if (m_pBackImgF != NULL)
			m_pBackImgF->SetNinePart(lprcNinePart);
	}

	if ((lpNormal != NULL && NULL == m_pBackImgN) || 
		(lpHoven  != NULL && NULL == m_pBackImgH) ||
		(lpDown   != NULL && NULL == m_pBackImgD) ||
		(lpFocus  != NULL && NULL == m_pBackImgF))
		return FALSE;
	else
		return TRUE;
}

//������Դ
BOOL CSkinButton::SetCheckImage( LPCTSTR lpNormal, LPCTSTR lpHoven, LPCTSTR lpTickNormal, LPCTSTR lpTickHoven )
{
	RenderEngine->RemoveImage(m_pCheckImgN);
	RenderEngine->RemoveImage(m_pCheckImgH);
	RenderEngine->RemoveImage(m_pCheckImgTickN);
	RenderEngine->RemoveImage(m_pCheckImgTickH);

	m_pCheckImgN = RenderEngine->GetImage(lpNormal);
	m_pCheckImgH = RenderEngine->GetImage(lpHoven);
	m_pCheckImgTickN = RenderEngine->GetImage(lpTickNormal);
	m_pCheckImgTickH = RenderEngine->GetImage(lpTickHoven);

	if (NULL == m_pCheckImgN || NULL == m_pCheckImgH
		|| NULL == m_pCheckImgTickN || NULL == m_pCheckImgTickH)
		return FALSE;
	else
		return TRUE;
}

//������Դ
BOOL CSkinButton::SetIconImage( LPCTSTR lpszFileName )
{
	RenderEngine->RemoveImage(m_pIconImg);

	m_pIconImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pIconImg)
		return FALSE;
	else
		return TRUE;
}

//������Դ
BOOL CSkinButton::SetMenuImage( LPCTSTR lpszFileName )
{
	RenderEngine->RemoveImage(m_pArrowImg);

	m_pArrowImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pArrowImg)
		return FALSE;
	else
		return TRUE;
}

//���ô�С
void CSkinButton::SetSize( int nWidth,int nHeight )
{
	SetWindowPos(NULL,0,0,nWidth,nHeight,SWP_NOMOVE);
}

//���ò˵�
void CSkinButton::SetMenu( HMENU hMenu )
{
	m_hMenu = hMenu;
}


//������Ϣ
void CSkinButton::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pBackImgD);
	RenderEngine->RemoveImage(m_pBackImgF);

	RenderEngine->RemoveImage(m_pCheckImgN);
	RenderEngine->RemoveImage(m_pCheckImgH);
	RenderEngine->RemoveImage(m_pCheckImgTickN);
	RenderEngine->RemoveImage(m_pCheckImgTickH);

	RenderEngine->RemoveImage(m_pArrowImg);
	RenderEngine->RemoveImage(m_pIconImg);

	m_bFocus = m_bPress = m_bHover = m_bMouseTracking = FALSE;
	m_nBtnType = en_PushButton;
	m_hMenu = NULL;
	m_dwTextAlign = 0;
	m_hBackDC = NULL;
}

//��Ϣѭ��
LRESULT CSkinButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//���RadioButton�飬ѡ������Radioʱ������Check��Ϣ
	if ( message == BM_SETCHECK )
	{
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	//����ƿ���ť֮�󣬻��������Ϣ��������Ҫ���²����ػ水ť
	if ( message == BM_SETSTATE )
	{
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
	
	return __super::DefWindowProc(message, wParam, lParam);
}

//������Ϣ
void CSkinButton::OnPaint()
{
	CPaintDC dc(this); 

	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC MemDC(&dc, rcClient);

	//���Ʊ���
	DrawParentWndBg(GetSafeHwnd(),MemDC->GetSafeHdc());

	switch (m_nBtnType)
	{
	case en_PushButton:
		DrawPushButton(&MemDC,rcClient);
		break;

	case en_CheckButton:
	case en_RadioButton:
		DrawCheckButton(&MemDC,rcClient);
		break;

	case en_IconButton:
		DrawIConButton(&MemDC,rcClient);
		break;

	case en_MenuButton:
		DrawMenuButton(MemDC,rcClient);
		break;
	}
}

//���ư�ť
void CSkinButton::DrawPushButton(CDC* pDC,RECT &rcClient)
{
	if (m_bPress)		// ����������״̬
	{
		if (m_pBackImgD != NULL && !m_pBackImgD->IsNull())
			m_pBackImgD->DrawImage(pDC, rcClient);
	}
	else if (m_bHover)	// �����ͣ״̬
	{
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
			m_pBackImgH->DrawImage(pDC, rcClient);
	}
	else if (m_bFocus)	// ����״̬
	{
		if (m_pBackImgF != NULL && !m_pBackImgF->IsNull())
			m_pBackImgF->DrawImage(pDC, rcClient);
	}
	else				// ��ͨ״̬
	{
		if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
			m_pBackImgN->DrawImage(pDC, rcClient);
	}

	if (m_bPress)
		::OffsetRect(&rcClient,1, 1);

	CString strText;
	GetWindowText(strText);

	BOOL bHasText = FALSE;
	if (strText.GetLength() > 0)
		bHasText = TRUE;

	BOOL bHasIcon = FALSE;
	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
		bHasIcon = TRUE;

	if (bHasIcon && bHasText)	// ��ͼ�������
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		int nMode = pDC->SetBkMode(TRANSPARENT);
		
		pDC->SelectObject(GetCtrlFont());

		pDC->SetTextColor(IsWindowEnabled()?m_colNormalText:m_colDisableText);
		CRect rcText(0,0,0,0);	// �������ֿ��
		pDC->DrawText(strText, &rcText, DT_SINGLELINE | DT_CALCRECT);

		int cx = cxIcon+3+rcText.Width();
		int cy = cyIcon;

		CRect rcCenter;
		CalcCenterRect(rcClient, cx, cy, rcCenter);

		CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.bottom);
		m_pIconImg->DrawImage(pDC, rcIcon);

		UINT nFormat = m_dwTextAlign ? m_dwTextAlign : DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
		rcText = CRect(rcIcon.right+3, rcClient.top, rcIcon.right+3+rcText.Width(), rcClient.bottom);
		pDC->DrawText(strText, &rcText, nFormat);

		pDC->SetBkMode(nMode);
	}
	else if (bHasIcon)	// ��ͼ��
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		CRect rcIcon;
		CalcCenterRect(rcClient, cxIcon, cyIcon, rcIcon);

		m_pIconImg->DrawImage(pDC, rcIcon);
	}
	else if (bHasText)	// ������
	{
		UINT nFormat = m_dwTextAlign ? m_dwTextAlign : DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(GetCtrlFont());
		pDC->SetTextColor(IsWindowEnabled()?m_colNormalText:m_colDisableText);
		pDC->DrawText(strText, &rcClient, nFormat);
		pDC->SetBkMode(nMode);
	}
}

void CSkinButton::DrawCheckButton( CDC* pDC,RECT &rcClient )
{
	int nWidth = 15, nHeight = 15;
	if (m_pCheckImgN != NULL && !m_pCheckImgN->IsNull())
	{
		nWidth = m_pCheckImgN->GetWidth();
		nHeight = m_pCheckImgN->GetHeight();
	}

	CRect rcCheck, rcText;

	rcCheck.left = rcClient.left;
	rcCheck.right = rcCheck.left + nWidth;
	rcCheck.top = ((rcClient.bottom-rcClient.top) - nHeight) / 2;
	rcCheck.bottom = rcCheck.top + nHeight;

	rcText = rcClient;
	rcText.left = rcCheck.right + 4;

	BOOL bChecked = ((GetCheck() == BST_CHECKED) ? TRUE : FALSE);

	if (m_bHover)	// �����ͣ״̬
	{
		if (bChecked)
		{
			if (m_pCheckImgTickH != NULL && !m_pCheckImgTickH->IsNull())
				m_pCheckImgTickH->DrawImage(pDC, rcCheck);
		}
		else
		{
			if (m_pCheckImgH != NULL && !m_pCheckImgH->IsNull())
				m_pCheckImgH->DrawImage(pDC, rcCheck);
		}
	}
	else	// ��ͨ״̬
	{
		if (bChecked)
		{
			if (m_pCheckImgTickN != NULL && !m_pCheckImgTickN->IsNull())
				m_pCheckImgTickN->DrawImage(pDC, rcCheck);
		}
		else
		{
			if (m_pCheckImgN != NULL && !m_pCheckImgN->IsNull())
				m_pCheckImgN->DrawImage(pDC, rcCheck);
		}
	}

	CString strText;
	GetWindowText(strText);

	if (strText.GetLength() > 0)
	{
		UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(GetCtrlFont());
		pDC->SetTextColor(IsWindowEnabled()?m_colNormalText:m_colDisableText);
		pDC->DrawText(strText, &rcText, nFormat);
		pDC->SetBkMode(nMode);
	}
}

void CSkinButton::DrawIConButton( CDC* pDC,RECT &rcClient )
{
	if (m_bPress)	// ����������״̬
	{
		if (m_pBackImgD != NULL && !m_pBackImgD->IsNull())
			m_pBackImgD->Draw(pDC, rcClient);
	}
	else if (m_bHover)	// �����ͣ״̬
	{
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
			m_pBackImgH->Draw(pDC, rcClient);
	}

	if (m_bPress)
		::OffsetRect(&rcClient,1, 1);

	CString strText;
	GetWindowText(strText);

	BOOL bHasText = FALSE;
	if (strText.GetLength() > 0)
		bHasText = TRUE;

	BOOL bHasIcon = FALSE;
	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
		bHasIcon = TRUE;

	if (bHasIcon && bHasText)	// ��ͼ�������
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(GetCtrlFont());

		CRect rcText(0,0,0,0);	// �������ֿ��
		pDC->DrawText(strText, &rcText, DT_SINGLELINE | DT_CALCRECT);

		int cx = cxIcon+3+rcText.Width();
		int cy = cyIcon;

		CRect rcCenter;
		CalcCenterRect(rcClient, cx, cy, rcCenter);

		CRect rcIcon(rcCenter.left, rcCenter.top, rcCenter.left+cxIcon, rcCenter.bottom);
		m_pIconImg->DrawImage(pDC, rcIcon);

		UINT nFormat = m_dwTextAlign ? m_dwTextAlign : DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;
		rcText = CRect(rcIcon.right+3, rcClient.top, rcIcon.right+3+rcText.Width(), rcClient.bottom);
		pDC->SetTextColor(IsWindowEnabled()?m_colNormalText:m_colDisableText);
		pDC->DrawText(strText, &rcText, nFormat);

		pDC->SetBkMode(nMode);	
	}
	else if (bHasIcon)	// ��ͼ��
	{
		int cxIcon = m_pIconImg->GetWidth();
		int cyIcon = m_pIconImg->GetHeight();

		CRect rcIcon;
		CalcCenterRect(rcClient, cxIcon, cyIcon, rcIcon);

		m_pIconImg->DrawImage(pDC, rcIcon);
	}
	else if (bHasText)	// ������
	{
		CRect rcText(rcClient);
		rcText.left += 2;
		rcText.right -= 2;

		UINT nFormat = m_dwTextAlign ? m_dwTextAlign : DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		int nMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(GetCtrlFont());
		pDC->SetTextColor(IsWindowEnabled()?m_colNormalText:m_colDisableText);
		pDC->DrawText(strText, &rcText, nFormat);
		pDC->SetBkMode(nMode);	
	}
}

void CSkinButton::DrawMenuButton( CDC* pDC,RECT &rcClient )
{
	if (m_bPress)	// ����������״̬
	{
		if (m_pBackImgD != NULL && !m_pBackImgD->IsNull())
			m_pBackImgD->DrawImage(pDC, rcClient);
	}
	else if (m_bHover)	// �����ͣ״̬
	{
		if (m_pBackImgH != NULL && !m_pBackImgH->IsNull())
			m_pBackImgH->DrawImage(pDC, rcClient);
	}

	CRect rcArrow(0, 0, 0, 0);

	if (m_pArrowImg != NULL && !m_pArrowImg->IsNull())
	{
		int cx = m_pArrowImg->GetWidth();
		int cy = m_pArrowImg->GetHeight();
		int x = rcClient.right - 3 - cx;
		int y = (rcClient.bottom-rcClient.top - cy + 1) / 2;
		rcArrow = CRect(x, y, x+cx, y+cy);
		m_pArrowImg->DrawImage(pDC, rcArrow);
	}

	if (m_pIconImg != NULL && !m_pIconImg->IsNull())
	{
		int cx = m_pIconImg->GetWidth();
		int cy = m_pIconImg->GetHeight();

		int nRight;
		if (rcArrow.left > 0)
			nRight = rcArrow.left;
		else
			nRight = rcClient.right;

		CRect rcIcon(rcClient.left, rcClient.top, nRight, rcClient.bottom);
		CalcCenterRect(rcIcon, cx, cy, rcIcon);
		
		if (m_bPress)
			rcIcon.OffsetRect(1, 1);
		m_pIconImg->DrawImage(pDC, rcIcon);
	}
}

void CSkinButton::SetPushed( bool bPush )
{
	m_bPushed = bPush;

	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}


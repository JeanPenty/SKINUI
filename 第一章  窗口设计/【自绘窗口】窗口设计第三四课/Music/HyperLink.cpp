#include "Stdafx.h"
#include "Resource.h"
#include "HyperLink.h"
//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CHyperLink, CStatic)

	//ϵͳ��Ϣ
	ON_WM_PAINT()
	ON_WM_CREATE()
    ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()

	//�Զ���Ϣ
	ON_MESSAGE(WM_SETTEXT, OnSetTextMesage)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeaveMessage)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CHyperLink::CHyperLink()
{
	//״̬����
	m_bVisited=false;
	m_bHovering=false;

	//���ñ���
	m_bUnderLine=true;
	m_AutoRectify=true;

	//��ɫ����
	m_crBackColor=CLR_INVALID;
	m_crHoverText=CLR_INVALID;
	m_crNormalText=CLR_INVALID;
	m_crVisitedText=CLR_INVALID;

	return;
}

//��������
CHyperLink::~CHyperLink()
{
}

//�ؼ���
VOID CHyperLink::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//���ÿؼ�
	Initialization();

	return;
}

//������Ϣ
INT CHyperLink::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ÿؼ�
	Initialization();

	return 0;
}

//�滭��Ϣ
VOID CHyperLink::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//���û���
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(GetDefaultFont());

	//�滭����
	if (m_crBackColor!=CLR_INVALID)
	{
		//�Զ�����
		dc.FillSolidRect(&rcClient,m_crBackColor);
	}
	else 
	{
		//Ĭ�ϱ���
		dc.FillSolidRect(&rcClient,m_crBackColor);
	}

	//������ɫ
	if (m_bHovering==true)
	{
		//������ɫ
		dc.SetTextColor((m_crHoverText==CLR_INVALID)?m_crHoverText:m_crHoverText);
	}
	else if (m_bVisited==true)
	{
		//������ɫ
		dc.SetTextColor((m_crVisitedText==CLR_INVALID)?m_crVisitedText:m_crVisitedText);
	}
	else
	{
		//������ɫ
		dc.SetTextColor((m_crNormalText==CLR_INVALID)?m_crNormalText:m_crNormalText);
	}

	//��ȡ��ʽ
	LONG dwStyte=GetWindowLong(m_hWnd,GWL_STYLE);
	UINT uFormat=DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	if (dwStyte&SS_RIGHT) uFormat|=DT_RIGHT;
	else if (dwStyte&SS_CENTER) uFormat|=DT_CENTER;
	else uFormat|=DT_LEFT;

	//�滭����
	CString strText;
	GetWindowText(strText);
	dc.DrawText(strText,&rcClient,uFormat);

	return;
}

//�����Ϣ
BOOL CHyperLink::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//���ù��
	::SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_HAND)));

	return TRUE;
}

//�����Ϣ
VOID CHyperLink::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//״̬�ж�
	if (m_bHovering==false)
	{
		//���ñ���
		m_bHovering=true;

		//ע����Ϣ
		TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.hwndTrack=GetSafeHwnd();
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		_TrackMouseEvent(&TrackMouseEvent);

		//�ػ�����
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//������Ϣ
LRESULT	CHyperLink::OnSetTextMesage(WPARAM wParam, LPARAM lParam)
{
	//Ĭ�ϵ���
	LRESULT lResult=Default();

	//�����ؼ�
	if (m_AutoRectify==true) RectifyControl();

	return lResult;
}

//�����Ϣ
LRESULT CHyperLink::OnMouseLeaveMessage(WPARAM wParam, LPARAM lParam)
{
	//���ñ���
	m_bHovering=false;

	//�ػ�����
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return 0;
}

//���÷���
VOID CHyperLink::SetVisited(bool bVisited)
{
	//״̬�ж�
	if (m_bVisited!=bVisited)
	{
		//���ñ���
		m_bVisited=bVisited;

		//�ػ�����
		if (m_hWnd!=NULL)
		{
			RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
		}
	}

	return;
}

//���»���
VOID CHyperLink::SetUnderLine(bool bUnderLine)
{
	//״̬�ж�
	if (m_bUnderLine!=bUnderLine)
	{
		//���ñ���
		m_bUnderLine=bUnderLine;

		//�ػ�����
		if (m_hWnd!=NULL)
		{
			RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
		}
	}

	return;
}

//���õ���
VOID CHyperLink::SetAutoRectify(bool bAutoRectify)
{
	//״̬�ж�
	if (m_AutoRectify!=bAutoRectify)
	{
		//���ñ���
		m_AutoRectify=bAutoRectify;

		//�����ؼ�
		if (m_AutoRectify==true) RectifyControl();
	}

	return;
}

//������ɫ
VOID CHyperLink::SetBackGroundColor(COLORREF crBackColor)
{
	//���ñ���
	m_crBackColor=crBackColor;

	//�ػ�����
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//������ɫ
VOID CHyperLink::SetHyperLinkTextColor(COLORREF crHoverText, COLORREF crNormalText, COLORREF crVisitedText)
{
	//���ñ���
	m_crHoverText=crHoverText;
	m_crNormalText=crNormalText;
	m_crVisitedText=crVisitedText;

	//�ػ�����
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//����λ��
VOID CHyperLink::RectifyControl()
{
	//��ȡ����
	CString strText;
	GetWindowText(strText);

	//��ȡλ��
	CRect rcControl;
	GetWindowRect(&rcControl);
	GetParent()->ScreenToClient(&rcControl);

	//���㳤��
	CClientDC ClientDC(this);
	ClientDC.SelectObject(GetDefaultFont());

	//�ƶ�λ��
	CSize Size=ClientDC.GetTextExtent(strText);
	MoveWindow(rcControl.left,rcControl.top,Size.cx,Size.cy);

	return;
}

//���ÿؼ�
VOID CHyperLink::Initialization()
{
	//��������
	if (m_AutoRectify=true) RectifyControl();

	//��������
	SetWindowLong(m_hWnd,GWL_STYLE,GetStyle()|SS_NOTIFY);

	return;
}

CFont & CHyperLink::GetDefaultFont()
{
	//��������
	if (m_DefaultFont.m_hObject==NULL)
	{
		m_DefaultFont.CreateFont(-12,0,0,0,0,0,0,0,0,3,2,ANTIALIASED_QUALITY,2,TEXT("����"));
	}

	return m_DefaultFont;
}

//////////////////////////////////////////////////////////////////////////////////


// DlgControlItem.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinDialog.h"
#include "RenderManager.h"

// CDlgControlItem 对话框

//边框宽度
CONST INT		BORDERWIDTH = 3;


IMPLEMENT_DYNAMIC(CSkinDialog, CDialog)

CSkinDialog::CSkinDialog(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	m_hMemDC = NULL;
	m_hMemBmp = m_hOldBmp = NULL;
	m_bExtrude = false;
}

CSkinDialog::~CSkinDialog()
{
	if (m_hMemDC != NULL && m_hMemBmp != NULL)
	{
		::SelectObject(m_hMemDC, m_hOldBmp);
		::DeleteObject(m_hMemBmp);
		::DeleteDC(m_hMemDC);
	}
	m_hMemDC = NULL;
	m_hMemBmp = m_hOldBmp = NULL;
}

void CSkinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()

// CDlgControlItem 消息处理程序

void CSkinDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	int cx = 0, cy = 0;

	if (m_hMemBmp != NULL)
	{
		BITMAP bmpInfo = {0};
		::GetObject(m_hMemBmp, sizeof(BITMAP), &bmpInfo);
		cx = bmpInfo.bmWidth;
		cy = bmpInfo.bmHeight;
	}

	if (rcClient.Width() != cx || rcClient.Height() != cy)
	{
		if (m_hMemDC != NULL && m_hMemBmp != NULL)
		{
			::SelectObject(m_hMemDC, m_hOldBmp);
			::DeleteObject(m_hMemBmp);
		}

		m_hMemBmp = ::CreateCompatibleBitmap(dc.GetSafeHdc(), rcClient.Width(), rcClient.Height());
		m_hOldBmp = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBmp);
	}

	RenderEngine->DrawColor(m_hMemDC,rcClient,RGB(234,241,249));

	DrawClientArea(CDC::FromHandle(m_hMemDC),rcClient.Width(), rcClient.Height());

	::BitBlt(dc.m_hDC, 0, 0, rcClient.Width(), rcClient.Height(), m_hMemDC, 0, 0, SRCCOPY);
}

BOOL CSkinDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//获取拉伸属性
	//if ( GetStyle() & WS_THICKFRAME ) m_bExtrude = true;

	//RemoveBorder();

	CRect rcClient;
	GetClientRect(&rcClient);

	HDC hDC = ::GetDC(m_hWnd);
	m_hMemDC = ::CreateCompatibleDC(hDC);
	m_hMemBmp = ::CreateCompatibleBitmap(hDC, rcClient.Width(), rcClient.Height());
	m_hOldBmp = (HBITMAP)::SelectObject(m_hMemDC, m_hMemBmp);
	::ReleaseDC(m_hWnd, hDC);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSkinDialog::RemoveBorder()
{
	DWORD dwStyle = GetStyle();
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	dwNewStyle&=dwStyle;
	SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);
	DWORD dwExStyle = GetExStyle();
	DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle&=dwExStyle;
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);
}

LRESULT CSkinDialog::OnNcHitTest(CPoint point)
{
	if( m_bExtrude )
	{
		CRect rcWindow;
		GetWindowRect(&rcWindow);

		if ((point.x <= rcWindow.left+BORDERWIDTH) && (point.y>BORDERWIDTH) && (point.y<rcWindow.bottom-BORDERWIDTH*2) )
			return HTLEFT;
		else if ((point.x >= rcWindow.right-BORDERWIDTH) && (point.y>BORDERWIDTH) && (point.y<rcWindow.bottom-BORDERWIDTH*2) )
			return HTRIGHT;
		else if ((point.y <= rcWindow.top+BORDERWIDTH) && (point.x>BORDERWIDTH) && (point.x<rcWindow.right-BORDERWIDTH*2))
			return HTTOP;
		else if ((point.y >= rcWindow.bottom-BORDERWIDTH) && (point.x>BORDERWIDTH) && (point.x<rcWindow.right-BORDERWIDTH*2))
			return HTBOTTOM;
		else if ((point.x <= rcWindow.left+BORDERWIDTH*2) && (point.y <= rcWindow.top+BORDERWIDTH*2))
			return HTTOPLEFT;
		else if ((point.x >= rcWindow.right-BORDERWIDTH*2) && (point.y <= rcWindow.top+BORDERWIDTH*2))
			return HTTOPRIGHT;
		else if ((point.x <= rcWindow.left+BORDERWIDTH*2) && (point.y >= rcWindow.bottom-BORDERWIDTH*2))
			return HTBOTTOMLEFT;
		else if ((point.x >= rcWindow.right-BORDERWIDTH*2) && (point.y >= rcWindow.bottom-BORDERWIDTH*2))
			return HTBOTTOMRIGHT;
		else
			return CWnd::OnNcHitTest(point);

		return 0;
	}
	else
		return CDialog::OnNcHitTest(point);
}

void CSkinDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if( m_bExtrude )
	{
		if (nHitTest == HTTOP)		
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTBOTTOM)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTLEFT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTRIGHT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTTOPLEFT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTTOPRIGHT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTBOTTOMLEFT)
			SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
		else if (nHitTest == HTBOTTOMRIGHT)
			SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
		else if (nHitTest==HTCAPTION)
			SendMessage(WM_SYSCOMMAND, SC_MOVE | 4, MAKELPARAM(point.x, point.y));
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CSkinDialog::SetExtrude( bool bExtrude )
{
	m_bExtrude = bExtrude;
}


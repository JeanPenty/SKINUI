// BaseDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageHandle.h"
#include "BaseDialog.h"


// CBaseDialog 对话框

IMPLEMENT_DYNAMIC(CBaseDialog, CSkinDialog)

CBaseDialog::CBaseDialog(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CSkinDialog(nIDTemplate, pParent)
{
	m_pImageBack = NULL;
	m_bIsZoomed = false;
}

CBaseDialog::~CBaseDialog()
{
}

void CBaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBaseDialog, CSkinDialog)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_WNDMIN,OnBnClickWindowMin)
	ON_BN_CLICKED(IDC_WNDMAX,OnBnClickWindowMax)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CBaseDialog 消息处理程序

BOOL CBaseDialog::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	HDC hParentDC = GetBackDC();

	SetExtrude(true);
	SetClipChild(true);

	m_pImageBack = RenderEngine->GetImage(TEXT("Res\\Back.png"));

	CRect rcClient;
	GetClientRect(&rcClient);

	m_btClose.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-53,1,0,0),this,IDCANCEL);
	m_btClose.SetBackImage(TEXT("Res\\Button\\btn_close_normal.png"),TEXT("Res\\Button\\btn_close_highlight.png"),TEXT("Res\\Button\\btn_close_down.png"),TEXT("Res\\Button\\btn_close_normal.png"));
	m_btClose.SetButtonType(en_PushButton);
	m_btClose.SetParentBack(hParentDC);
	m_btClose.SetSize(52,37);

	m_btMax.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-53-40,0,0,0),this,IDC_WNDMAX);
	m_btMax.SetBackImage(TEXT("Res\\Button\\btn_max_normal.png"),TEXT("Res\\Button\\btn_max_highlight.png"),TEXT("Res\\Button\\btn_max_down.png"),TEXT("Res\\Button\\btn_max_normal.png"));
	m_btMax.SetButtonType(en_PushButton);
	m_btMax.SetParentBack(hParentDC);
	m_btMax.SetSize(40,37);

	m_btMin.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-53-40-44,0,0,0),this,IDC_WNDMIN);
	m_btMin.SetBackImage(TEXT("Res\\Button\\btn_mini_normal.png"),TEXT("Res\\Button\\btn_mini_highlight.png"),TEXT("Res\\Button\\btn_mini_down.png"),TEXT("Res\\Button\\btn_mini_normal.png"));
	m_btMin.SetButtonType(en_PushButton);
	m_btMin.SetParentBack(hParentDC);
	m_btMin.SetSize(44,37);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBaseDialog::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(nWidth,nHeight,32);

	//变量定义
	CDC * pBufferDC=CDC::FromHandle(ImageBuffer.GetDC());

	pBufferDC->FillSolidRect(1,33,nWidth-2,nHeight-41,RGB(234,238,244));

	DrawView(pBufferDC,nWidth-2,nHeight-33-41);

	if ( CHECK_IMAGE(m_pImageBack) )
	{
		m_pImageBack->Draw(pBufferDC,CRect(0,0,nWidth-1,nHeight-1),CRect(35,35,42,42));
	}

	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(RenderEngine->GetDeaultFont());
	pBufferDC->SetTextColor(RGB(255,255,255));

	CString str;
	GetWindowText(str);

	pBufferDC->TextOut(35,10,str);

	//绘画界面
	pDC->BitBlt(0,0,nWidth,nHeight,pBufferDC,0,0,SRCCOPY);

	//清理资源
	ImageBuffer.ReleaseDC();
}


void CBaseDialog::OnDestroy()
{
	CSkinDialog::OnDestroy();

	RenderEngine->RemoveImage(m_pImageBack);
}

void CBaseDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ( !m_bIsZoomed )
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CSkinDialog::OnLButtonDown(nFlags, point);
}

void CBaseDialog::OnSize(UINT nType, int cx, int cy)
{
	CSkinDialog::OnSize(nType, cx, cy);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	DeferWindowPos(hDwp,m_btClose,NULL,cx-53,1,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,cx-53-40,0,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMin,NULL,cx-53-40-44,0,0,0,uFlags|SWP_NOSIZE);

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	//设置圆角
	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,cx,cy,4,4);
	SetWindowRgn(rgn,FALSE);

	Invalidate(FALSE);
}

BOOL CBaseDialog::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	return CSkinDialog::OnEraseBkgnd(pDC);
}

void CBaseDialog::OnBnClickWindowMin()
{
	ShowWindow(SW_MINIMIZE);
}

void CBaseDialog::OnBnClickWindowMax()
{
	static CRect rcClient(0,0,0,0);

	if ( m_bIsZoomed )
	{
		m_btMax.SetBackImage(TEXT("Res\\Button\\btn_max_normal.png"),TEXT("Res\\Button\\btn_max_highlight.png"),TEXT("Res\\Button\\btn_max_down.png"),TEXT("Res\\Button\\btn_max_normal.png"));

		MoveWindow(&rcClient);

		m_bIsZoomed = false;
	}
	else 
	{
		GetWindowRect(&rcClient);
		m_btMax.SetBackImage(TEXT("Res\\Button\\btn_restore_normal.png"),TEXT("Res\\Button\\btn_restore_highlight.png"),TEXT("Res\\Button\\btn_restore_down.png"),TEXT("Res\\Button\\btn_restore_normal.png"));

		CRect rc;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rc,0); 
		MoveWindow(&rc);

		m_bIsZoomed = true;
	}
}

void CBaseDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnBnClickWindowMax();

	CSkinDialog::OnLButtonDblClk(nFlags, point);
}

void CBaseDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
	if ( point.y < 40 )
	{
		CMenu* pSysMenu = GetSystemMenu(FALSE);
		if ( pSysMenu != NULL )
		{
			//获取光标
			CPoint MousePoint;
			GetCursorPos(&MousePoint);

			//弹出菜单
			pSysMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,MousePoint.x,MousePoint.y,this);
		}
	}

	CSkinDialog::OnRButtonDown(nFlags, point);
}

BOOL CBaseDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch ( LOWORD(wParam) )
	{
	case SC_CLOSE:SendMessage(WM_SYSCOMMAND,SC_CLOSE,0);break;
	case SC_RESTORE:SendMessage(WM_SYSCOMMAND,SC_RESTORE,0);break;
	case SC_MOVE:SendMessage(WM_SYSCOMMAND,SC_MOVE,0);break;
	case SC_SIZE:SendMessage(WM_SYSCOMMAND,SC_SIZE,0);break;
	case SC_MINIMIZE:SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);break;
	case SC_MAXIMIZE:SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);break;
	case IDM_ABOUTBOX:SendMessage(WM_SYSCOMMAND,IDM_ABOUTBOX,0);break;
	}

	return CSkinDialog::OnCommand(wParam, lParam);
}

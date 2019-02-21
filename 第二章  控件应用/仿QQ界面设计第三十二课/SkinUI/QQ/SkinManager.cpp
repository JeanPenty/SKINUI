// SkinManager.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "SkinManager.h"

// CSkinManager 对话框

IMPLEMENT_DYNAMIC(CSkinManager, CSkinDialog)

CSkinManager::CSkinManager(UINT nIDTemplate,CWnd* pParent /*=NULL*/,AFX_WND_STYLE Style/* = en_Wnd_Normal*/)
	: CSkinDialog(nIDTemplate, pParent)
{
	m_pImageBack = NULL;
	m_pImageLogo = NULL;

	m_enWndStyle = Style;
	m_bIsZoomed = false;
	m_bShowLogo = true;
}

CSkinManager::~CSkinManager()
{
	RenderEngine->RemoveImage(m_pImageBack);
	RenderEngine->RemoveImage(m_pImageLogo);
}

void CSkinManager::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinManager, CSkinDialog)
	ON_BN_CLICKED(IDC_WNDMIN,OnBnClickWindowMin)
	ON_BN_CLICKED(IDC_WNDMAX,OnBnClickWindowMax)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CSkinManager::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	pDC->FillSolidRect(0,0,nWidth,nHeight,COLOR_BACK);

	if ( m_pImageBack != NULL && !m_pImageBack->IsNull() )
	{
		m_pImageBack->DrawExtrude(pDC,CRect(0,0,nWidth,nHeight),GlobalUnits->m_bLeftDrawExtrude);
	}

	//绘制边框
	RenderEngine->DrawRoundRect(pDC->GetSafeHdc(),CRect(0,0,nWidth-1,nHeight-1),6,6,1,RGB(92,89,82));

	if ( m_bShowLogo )
	{
		if ( m_pImageLogo != NULL && !m_pImageLogo->IsNull() )
			m_pImageLogo->DrawImage(pDC,5,5);
	}
}

BOOL CSkinManager::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	HDC hParentDC = GetBackDC();

	m_pImageBack = RenderEngine->GetImage(GlobalUnits->m_szDefaultSkin);
	m_pImageLogo = RenderEngine->GetImage(TEXT("QQ\\Main_Title.png"));

	GlobalUnits->m_WindowArray.push_back(this);

	CRect rcClient;
	GetClientRect(&rcClient);

	if ( m_enWndStyle != en_Wnd_None )
	{
		m_btClose.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-41,0,0,0),this,IDCANCEL);
		m_btClose.SetBackImage(TEXT("\\QQ\\Button\\btn_close_normal.png"),TEXT("\\QQ\\Button\\btn_close_highlight.png"),TEXT("\\QQ\\Button\\btn_close_down.png"),TEXT("\\QQ\\Button\\btn_close_normal.png"));
		m_btClose.SetButtonType(en_PushButton);
		m_btClose.SetParentBack(hParentDC);
		m_btClose.SetSize(39,20);

		if ( m_enWndStyle != en_Wnd_CloseBox )
		{
			if( m_enWndStyle != en_Wnd_MinimizeBox )
			{
				m_btMax.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-69,0,0,0),this,IDC_WNDMAX);
				m_btMax.SetBackImage(TEXT("\\QQ\\Button\\btn_max_normal.png"),TEXT("\\QQ\\Button\\btn_max_highlight.png"),TEXT("\\QQ\\Button\\btn_max_down.png"),TEXT("\\QQ\\Button\\btn_max_normal.png"));
				m_btMax.SetButtonType(en_PushButton);
				m_btMax.SetParentBack(hParentDC);
				m_btMax.SetSize(28,20);
			}

			m_btMin.Create(NULL,WS_VISIBLE|WS_CHILD,CRect(rcClient.Width()-69-(m_enWndStyle==en_Wnd_Normal?28:0),0,0,0),this,IDC_WNDMIN);
			m_btMin.SetBackImage(TEXT("\\QQ\\Button\\btn_mini_normal.png"),TEXT("\\QQ\\Button\\btn_mini_highlight.png"),TEXT("\\QQ\\Button\\btn_mini_down.png"),TEXT("\\QQ\\Button\\btn_mini_normal.png"));
			m_btMin.SetButtonType(en_PushButton);
			m_btMin.SetParentBack(hParentDC);
			m_btMin.SetSize(28,20);
		}
	}

	return TRUE;
}

void CSkinManager::OnBnClickWindowMin()
{
	ShowWindow(SW_MINIMIZE);
}

void CSkinManager::OnLButtonDown( UINT nFlags, CPoint point )
{
	if( !m_bIsZoomed )
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	CSkinDialog::OnLButtonDown(nFlags, point);
}

void CSkinManager::UpdateSkin()
{
	RenderEngine->RemoveImage(m_pImageBack);
	m_pImageBack = RenderEngine->GetImage(GlobalUnits->m_szDefaultSkin);

	for (int i=0;i<GlobalUnits->m_WindowArray.size();i++)
	{
		CSkinManager * pSkinManager = GlobalUnits->m_WindowArray.at(i);

		if (pSkinManager->GetSafeHwnd() == NULL ) continue;
		
		pSkinManager->ModifyStyle(WS_CLIPCHILDREN,0);

		pSkinManager->Invalidate(FALSE);

		pSkinManager->ModifyStyle(0,WS_CLIPCHILDREN);
	}
}

void CSkinManager::OnDestroy()
{
	vector<CSkinManager*>::iterator iter = GlobalUnits->m_WindowArray.begin();

	for(; iter != GlobalUnits->m_WindowArray.end(); ++iter )
	{
		CSkinManager* pSkinManager = (CSkinManager*)*iter;
		if( pSkinManager == (CSkinManager*)this )
		{
			GlobalUnits->m_WindowArray.erase(iter);
			break;
		}
	}

	__super::OnDestroy();
}

void CSkinManager::OnBnClickWindowMax()
{
	static CRect rcClient(0,0,0,0);

	if ( m_bIsZoomed )
	{
		m_btMax.SetBackImage(TEXT("\\QQ\\Button\\btn_max_normal.png"),TEXT("\\QQ\\Button\\btn_max_highlight.png"),TEXT("\\QQ\\Button\\btn_max_down.png"),TEXT("\\QQ\\Button\\btn_max_normal.png"));

		MoveWindow(&rcClient);

		m_bIsZoomed = false;
	}
	else 
	{
		GetWindowRect(&rcClient);
		m_btMax.SetBackImage(TEXT("\\QQ\\Button\\btn_restore_normal.png"),TEXT("\\QQ\\Button\\btn_restore_highlight.png"),TEXT("\\QQ\\Button\\btn_restore_down.png"),TEXT("\\QQ\\Button\\btn_restore_normal.png"));

		CRect rc;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rc,0); 
		MoveWindow(&rc);

		m_bIsZoomed = true;
	}
}

void CSkinManager::OnSize( UINT nType, int cx, int cy )
{
	CSkinDialog::OnSize(nType, cx, cy);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	if ( m_enWndStyle != en_Wnd_None )
	{
		DeferWindowPos(hDwp,m_btClose,NULL,cx-41,0,0,0,uFlags|SWP_NOSIZE);

		if ( m_enWndStyle != en_Wnd_CloseBox )
		{
			if( m_enWndStyle != en_Wnd_MinimizeBox )
				DeferWindowPos(hDwp,m_btMax,NULL,cx-69,0,0,0,uFlags|SWP_NOSIZE);

			DeferWindowPos(hDwp,m_btMin,NULL,cx-69-(m_enWndStyle==en_Wnd_Normal?28:0),0,0,0,uFlags|SWP_NOSIZE);
		}
	}

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();

	//设置圆角
	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,cx,cy,4,4);
	SetWindowRgn(rgn,FALSE);

	//更新界面
	Invalidate(FALSE);
}

BOOL CSkinManager::OnEraseBkgnd( CDC* pDC )
{
	return TRUE;
}

void CSkinManager::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if( m_enWndStyle == en_Wnd_Normal )
		OnBnClickWindowMax();

	CSkinDialog::OnLButtonDblClk(nFlags, point);
}

// CSkinManager 消息处理程序

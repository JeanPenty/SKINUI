// SkinDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinDlg.h"
#include "resource.h"
#include "GMusic.h"

#define ITEM_WIDTH		110
#define ITEM_HEIGHT		70
#define ITEM_GAP_X		1
#define ITEM_GAP_Y		1

// CSkinDlg 对话框

IMPLEMENT_DYNAMIC(CSkinDlg, CBaseDialog)

CSkinDlg::CSkinDlg(CWnd* pParent /*=NULL*/)
	: CBaseDialog(IDD_SKIN, pParent,en_Wnd_CloseBox)
{
	ZeroMemory(m_pImageSkin,sizeof m_pImageSkin);
	ZeroMemory(&m_rcItem,sizeof m_rcItem);

	m_pImageHoven = NULL;
	m_pImageShadow = NULL;
	m_nHovenItem = 0;
	m_nSelItem = 0;
}

CSkinDlg::~CSkinDlg()
{
}

void CSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CBaseDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinDlg, CBaseDialog)
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CSkinDlg::OnInitDialog()
{
	CBaseDialog::OnInitDialog();

	m_pImageHoven = RenderEngine->GetImage(TEXT("Res\\Skin\\skin_highlight.png"));
	m_pImageShadow = RenderEngine->GetImage(TEXT("Res\\Skin\\back_shadow.png"));
	
	m_pImageSkin[0] = RenderEngine->GetImage(TEXT("Res\\Skin\\1\\small.jpg"));
	m_pImageSkin[1] = RenderEngine->GetImage(TEXT("Res\\Skin\\2\\small.jpg"));
	m_pImageSkin[2] = RenderEngine->GetImage(TEXT("Res\\Skin\\3\\small.jpg"));
	m_pImageSkin[3] = RenderEngine->GetImage(TEXT("Res\\Skin\\4\\small.jpg"));
	m_pImageSkin[4] = RenderEngine->GetImage(TEXT("Res\\Skin\\5\\small.jpg"));
	m_pImageSkin[5] = RenderEngine->GetImage(TEXT("Res\\Skin\\6\\small.jpg"));
	m_pImageSkin[6] = RenderEngine->GetImage(TEXT("Res\\Skin\\7\\small.jpg"));
	m_pImageSkin[7] = RenderEngine->GetImage(TEXT("Res\\Skin\\8\\small.jpg"));
	m_pImageSkin[8] = RenderEngine->GetImage(TEXT("Res\\Skin\\9\\small.jpg"));
	m_pImageSkin[9] = RenderEngine->GetImage(TEXT("Res\\Skin\\10\\small.jpg"));
	m_pImageSkin[10] = RenderEngine->GetImage(TEXT("Res\\Skin\\11\\small.jpg"));
	m_pImageSkin[11] = RenderEngine->GetImage(TEXT("Res\\Skin\\12\\small.jpg"));
	m_pImageSkin[12] = RenderEngine->GetImage(TEXT("Res\\Skin\\13\\small.jpg"));
	m_pImageSkin[13] = RenderEngine->GetImage(TEXT("Res\\Skin\\14\\small.jpg"));
	m_pImageSkin[14] = RenderEngine->GetImage(TEXT("Res\\Skin\\15\\small.jpg"));
	m_pImageSkin[15] = RenderEngine->GetImage(TEXT("Res\\Skin\\16\\small.jpg"));

	int nLeft = 0;
	int nTop = 0;

	for (int i=0,j=0;i<SKIN_COUNT;i++)
	{
		nLeft = 25 + (ITEM_WIDTH+ITEM_GAP_X)*(i%4); 

		if ( i%4 == 0 )
		{
			nTop = 70 + (ITEM_HEIGHT+ITEM_GAP_Y)*j;
			j++;
		}

		m_rcItem[i].SetRect(nLeft,nTop,nLeft+ITEM_WIDTH,nTop+ITEM_HEIGHT);
	}

	return TRUE;
}

void CSkinDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
	CBaseDialog::DrawClientArea(pDC,nWidth,nHeight);

	m_pImageShadow->DrawImage(pDC,0,0);

	for (int i=0,j=0;i<SKIN_COUNT;i++)
		if ( m_pImageSkin[i] != NULL && !m_pImageSkin[i]->IsNull() )
			m_pImageSkin[i]->DrawImage(pDC,m_rcItem[i]);

	if ( m_nHovenItem < SKIN_COUNT )
	{ 
 		if ( CHECK_IMAGE(m_pImageHoven) )
 			m_pImageHoven->DrawImage(pDC,m_rcItem[m_nHovenItem]);
	}

}

BOOL CSkinDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	static int nOldHoven = -1;

	for (int i=0,j=0;i<SKIN_COUNT;i++)
	{
		if ( PtInRect(&m_rcItem[i],point))
		{
			m_nHovenItem = i;

			SetCursor(LoadCursor(GetModuleHandle(SKINUI_DLL_NAME),MAKEINTRESOURCE(8000)));

			if( nOldHoven != m_nHovenItem )
			{
				nOldHoven = m_nHovenItem;
				Invalidate(FALSE);
			}

			return TRUE;
		}
	}

	return CBaseDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CSkinDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	for (int i=0,j=0;i<SKIN_COUNT;i++)
	{
		if ( PtInRect(&m_rcItem[i],point))
		{
			m_nHovenItem = i;
			
			TCHAR szWorkDirectory[MAX_PATH];
			RenderEngine->GetWorkDirectory(szWorkDirectory,MAX_PATH);

 			ZeroMemory(theApp.m_szDefaultSkin,CountArray(theApp.m_szDefaultSkin));
 			_sntprintf_s(theApp.m_szDefaultSkin,CountArray(theApp.m_szDefaultSkin),TEXT("%s\\Res\\Skin\\%d\\bk.jpg"),szWorkDirectory,i+1);
 			
			CBaseDialog::UpdateSkin();

			Invalidate(FALSE);

			break;
		}
	}

	CBaseDialog::OnLButtonDown(nFlags, point);
}

void CSkinDlg::OnDestroy()
{
	RenderEngine->RemoveImage(m_pImageHoven);
	RenderEngine->RemoveImage(m_pImageShadow);

 	for (int i=0;i<SKIN_COUNT;i++)
 	{
 		RenderEngine->RemoveImage(m_pImageSkin[i]);
 		SafeDelete(m_pImageSkin[i]);
 	}

	CBaseDialog::OnDestroy();
}


// CSkinDlg 消息处理程序

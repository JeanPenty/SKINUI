// SkinDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "SkinDlg.h"

#define ITEM_WIDTH		150
#define ITEM_HEIGHT		75
#define ITEM_GAP_X		5
#define ITEM_GAP_Y		5

// CSkinDlg 对话框

IMPLEMENT_DYNAMIC(CSkinDlg, CSkinManager)

CSkinDlg::CSkinDlg(CWnd* pParent /*=NULL*/)
	: CSkinManager(IDD_SKIN, pParent,en_Wnd_CloseBox)
{
	m_pImageTest = NULL;

	ZeroMemory(m_pImageSkin,sizeof m_pImageSkin);
	ZeroMemory(&m_rcItem,sizeof m_rcItem);
	ZeroMemory(&m_bLeftDrawExtrude,sizeof m_bLeftDrawExtrude);

	m_nHovenItem = 0;
	m_nSelItem = 0;
}

CSkinDlg::~CSkinDlg()
{

}

void CSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinManager::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSkinDlg, CSkinManager)
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CSkinDlg::OnInitDialog()
{
	CSkinManager::OnInitDialog();

	m_pImageTest = RenderEngine->GetImage(TEXT("QQ\\Skin\\fengmian_2.png"));

	m_pImageSkin[0] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main1.jpg"));
	m_pImageSkin[1] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main2.jpg"));
	m_pImageSkin[2] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main3.jpg"));
	m_pImageSkin[3] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main4.jpg"));
	m_pImageSkin[4] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main5.jpg"));
	m_pImageSkin[5] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main6.jpg"));
	m_pImageSkin[6] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main7.jpg"));
	m_pImageSkin[7] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main8.jpg"));
	m_pImageSkin[8] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main9.jpg"));
	m_pImageSkin[9] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main10.jpg"));
	m_pImageSkin[10] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main11.jpg"));
	m_pImageSkin[11] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main12.jpg"));
	m_pImageSkin[12] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main13.jpg"));
	m_pImageSkin[13] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main14.jpg"));
	m_pImageSkin[14] = RenderEngine->GetImage(TEXT("QQ\\Skin\\main15.jpg"));


	//其实这里应该是读取配置文件的，为了测试效果，就不做这个了
	for (int i=0;i<SKIN_COUNT;i++)
	{
		if( i>11 )
			m_bLeftDrawExtrude[i] = true;
		else
			m_bLeftDrawExtrude[i] = false;
	}

	int nLeft = 0;
	int nTop = 0;

	for (int i=0,j=0;i<SKIN_COUNT;i++)
	{
		nLeft = 25 + (ITEM_WIDTH+ITEM_GAP_X)*(i%3); 

		if ( i%3 == 0 )
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
	CSkinManager::DrawClientArea(pDC,nWidth,nHeight);

	pDC->FillSolidRect(1,62,nWidth-3,nHeight-64,COLOR_BACK);

	for (int i=0,j=0;i<SKIN_COUNT;i++)
		if ( m_pImageSkin[i] != NULL && !m_pImageSkin[i]->IsNull() )
			m_pImageSkin[i]->DrawImage(pDC,m_rcItem[i]);

	if ( m_nHovenItem < SKIN_COUNT )
	{
		CImageEx *pImage = m_pImageSkin[m_nHovenItem];

		if ( pImage != NULL && !pImage->IsNull() )
			pImage->DrawImage(pDC,nWidth-215,70,200,200,(m_bLeftDrawExtrude[m_nHovenItem]?0:(pImage->GetWidth()-200)),0,(m_bLeftDrawExtrude[m_nHovenItem]?pImage->GetWidth()/3:200),200);
	}

	if ( m_pImageTest != NULL && !m_pImageTest->IsNull() )
	{
		m_pImageTest->DrawImage(pDC,nWidth-215,70,200,410);
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

	return CSkinManager::OnSetCursor(pWnd, nHitTest, message);
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

			ZeroMemory(GlobalUnits->m_szDefaultSkin,CountArray(GlobalUnits->m_szDefaultSkin));
			_sntprintf_s(GlobalUnits->m_szDefaultSkin,CountArray(GlobalUnits->m_szDefaultSkin),TEXT("%s\\QQ\\Skin\\main%d.jpg"),szWorkDirectory,i+1);
			
			GlobalUnits->m_bLeftDrawExtrude = m_bLeftDrawExtrude[i];
			
			CSkinManager::UpdateSkin();

			Invalidate(FALSE);

			break;
		}
	}

	CSkinManager::OnLButtonDown(nFlags, point);
}

void CSkinDlg::OnDestroy()
{
	RenderEngine->RemoveImage(m_pImageTest);

 	for (int i=0;i<SKIN_COUNT;i++)
 	{
 		RenderEngine->RemoveImage(m_pImageSkin[i]);
 		SafeDelete(m_pImageSkin[i]);
 	}

	CSkinManager::OnDestroy();
}


// CSkinDlg 消息处理程序

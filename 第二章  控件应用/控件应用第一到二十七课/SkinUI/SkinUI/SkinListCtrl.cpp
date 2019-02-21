#include "Stdafx.h"
#include "SkinListCtrl.h"

//////////////////////////////////////////////////////////////////////////////////

//������Ϣ
struct tagSortInfo
{
	bool							bAscendSort;						//�����־
	WORD							wColumnIndex;						//�б�����
	CSkinListCtrl *					pSkinListCtrl;						//�б�ؼ�
};

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSkinListCtrl, CListCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//Ĭ������
#define LIST_STYTE					LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_ONECLICKACTIVATE

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinHeaderCtrl::CSkinHeaderCtrl()
{
	//���ñ���
	m_uLockCount=0L;
	m_uItemHeight=130;

	m_pBackImg = m_pPressImg = m_pGridImg = NULL;
	m_bPress = false;

	return;
}

//��������
CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
}

//�ؼ���
VOID CSkinHeaderCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	////��������
	//CFont Font;
	//Font.CreatePointFont(m_uItemHeight,TEXT("����"));

	////��������
	//SetFont(&Font);

	return;
}

//�ؼ���Ϣ
BOOL CSkinHeaderCtrl::OnChildNotify(UINT uMessage, WPARAM wParam, LPARAM lParam, LRESULT * pLResult)
{
	//��������
	NMHEADER * pNMHearder=(NMHEADER*)lParam;

	//�϶���Ϣ
	if ((pNMHearder->hdr.code==HDN_BEGINTRACKA)||(pNMHearder->hdr.code==HDN_BEGINTRACKW))
	{
		//��ֹ�϶�
		if (pNMHearder->iItem<(INT)m_uLockCount)
		{
			*pLResult=TRUE;
			return TRUE;
		}
	}

	return __super::OnChildNotify(uMessage,wParam,lParam,pLResult);
}

//��������
VOID CSkinHeaderCtrl::SetLockCount(UINT uLockCount)
{
	//���ñ���
	m_uLockCount=uLockCount;

	return;
}

//�����и�
VOID CSkinHeaderCtrl::SetItemHeight(UINT uItemHeight)
{
	//���ñ���
	m_uItemHeight=uItemHeight;

	////���ÿؼ�
	//if (m_hWnd!=NULL)
	//{
	//	//��������
	//	CFont Font;
	//	Font.CreatePointFont(m_uItemHeight,TEXT("����"));

	//	//��������
	//	SetFont(&Font);
	//}

	return;
}

//�ػ�����
VOID CSkinHeaderCtrl::OnPaint() 
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcRect;
	GetClientRect(&rcRect);

	CMemoryDC BufferDC(&dc,rcRect);

	//���� DC
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(m_colNormalText);
	BufferDC.SelectObject(GetCtrlFont());

	//�滭����
	if (m_pBackImg != NULL && !m_pBackImg->IsNull())
		m_pBackImg->Draw(&BufferDC,rcRect);

	if (m_pPressImg != NULL && !m_pPressImg->IsNull() && m_bPress)
	{
		CRect rcItem;
		GetItemRect(m_uActiveItem,&rcItem);

		m_pPressImg->Draw(&BufferDC,rcItem);
	}

	//�滭����
	CRect rcItem;
	HDITEM HDItem;
	TCHAR szBuffer[64];
	for (INT i=0;i<GetItemCount();i++)
	{
		//�������
		HDItem.mask=HDI_TEXT;
		HDItem.pszText=szBuffer;
		HDItem.cchTextMax=CountArray(szBuffer);

		//��ȡ��Ϣ
		GetItem(i,&HDItem);
		GetItemRect(i,&rcItem);

		if (m_pGridImg != NULL && !m_pGridImg->IsNull())
			m_pGridImg->DrawImage(&BufferDC,(rcItem.right-m_pGridImg->GetWidth()),(rcItem.Height()-m_pGridImg->GetHeight())/2);
	
		//�滭����
		rcItem.DeflateRect(3,1,3,1);
		BufferDC.DrawText(szBuffer,lstrlen(szBuffer),&rcItem,DT_END_ELLIPSIS|DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

	return;
}

//��������
BOOL CSkinHeaderCtrl::OnEraseBkgnd(CDC * pDC) 
{
	//ˢ�½���
// 	Invalidate(FALSE);
// 	UpdateWindow();

	return TRUE;
}

BOOL CSkinHeaderCtrl::SetBackImage( LPCTSTR lpNormal,CONST LPRECT lprcNinePart/*=NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImg);

	m_pBackImg = RenderEngine->GetImage(lpNormal);

	if (NULL == m_pBackImg)
		return FALSE;
	else
	{
		m_pBackImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CSkinHeaderCtrl::SetPressImage( LPCTSTR lpNormal,CONST LPRECT lprcNinePart/*=NULL*/ )
{
	RenderEngine->RemoveImage(m_pPressImg);

	m_pPressImg = RenderEngine->GetImage(lpNormal);

	if (NULL == m_pPressImg)
		return FALSE;
	else
	{
		m_pPressImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CSkinHeaderCtrl::SetGridImage( LPCTSTR lpNormal)
{
	RenderEngine->RemoveImage(m_pGridImg);

	m_pGridImg = RenderEngine->GetImage(lpNormal);

	if (NULL == m_pGridImg)
		return FALSE;
	else
	{
		return TRUE;
	}
}

void CSkinHeaderCtrl::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImg);
	RenderEngine->RemoveImage(m_pPressImg);
	RenderEngine->RemoveImage(m_pGridImg);
}

LRESULT CSkinHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 
	RECT *prc = hdl.prc; 
	WINDOWPOS *pwpos = hdl.pwpos; 

	int nHeight = 28;
	pwpos->cy = nHeight; 
	prc->top = nHeight; 

	return lResult; 
}

void CSkinHeaderCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	CRect rcItem;

	for (INT i=0;i<GetItemCount();i++)
	{
		GetItemRect(i,&rcItem);

		if ( PtInRect(&rcItem,point) )
		{
			m_bPress = true;
			m_uActiveItem = i;
			break;
		}
	}

	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	__super::OnLButtonDown(nFlags, point);
}

void CSkinHeaderCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_bPress = false;

	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	__super::OnLButtonUp(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinListCtrl::CSkinListCtrl()
{
	//���ñ���
	m_bAscendSort=false;
	m_nHeightItem = 0;
	m_uActiveItem = 0;
	m_pHovenImg = m_pSelectImg = NULL;
	m_pCheckImg = m_pUnCheckImg = NULL;

	m_colBack=RGB(255,255,255);

	return;
}

//��������
CSkinListCtrl::~CSkinListCtrl()
{
}

//�ؼ���
VOID CSkinListCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return;
}

//�滭����
VOID CSkinListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//��������
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	CMemoryDC BufferDC(pDC,rcItem);

	//��ȡ����
	INT nItemID=lpDrawItemStruct->itemID;
	INT nColumnCount=m_SkinHeaderCtrl.GetItemCount();

	//�滭����
	CRect rcClipBox;
	BufferDC.GetClipBox(&rcClipBox);

	//���û���
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(m_colNormalText);
	BufferDC.SelectObject(GetCtrlFont());
	BufferDC->FillSolidRect(&rcItem,m_colBack);

	//�滭����
	if (lpDrawItemStruct->itemState&ODS_SELECTED)
	{
		if (m_pSelectImg != NULL && !m_pSelectImg->IsNull())
			m_pSelectImg->Draw(&BufferDC,rcItem);
	}
	else if ( m_uActiveItem == nItemID )
	{
		if (m_pHovenImg != NULL && !m_pHovenImg->IsNull())
			m_pHovenImg->Draw(&BufferDC,rcItem);
	}

	//�滭����
	for (INT i=0;i<nColumnCount;i++)
	{
		//��ȡλ��
		CRect rcSubItem;
		GetSubItemRect(nItemID,i,LVIR_BOUNDS,rcSubItem);

		//�滭�ж�
		if (rcSubItem.left>rcClipBox.right) break;
		if (rcSubItem.right<rcClipBox.left) continue;

		//�滭����
		DrawReportItem(&BufferDC,nItemID,rcSubItem,i);
	}
	
	return;
}

//������Ϣ
INT CSkinListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	m_SkinHeaderCtrl.SubclassWindow(GetHeaderCtrl()->GetSafeHwnd());

	return 0;
}

//�滭����
VOID CSkinListCtrl::DrawReportItem(CDC * pDC, INT nItem, CRect & rcSubItem, INT nColumnIndex)
{
	//��ȡ����
	TCHAR szString[256]=TEXT("");
	GetItemText(nItem,nColumnIndex,szString,CountArray(szString));

	//�滭����
	rcSubItem.left+=5;

	//����CheckButton
	if( nColumnIndex == 0 )
	{
		if ((m_pCheckImg != NULL && !m_pCheckImg->IsNull()) && (m_pUnCheckImg != NULL && !m_pUnCheckImg->IsNull()))
		{
			if( GetCheck(nItem) )
				m_pCheckImg->DrawImage(pDC,rcSubItem.left+2,rcSubItem.top+(rcSubItem.Height()-m_pCheckImg->GetHeight())/2);
			else
				m_pUnCheckImg->DrawImage(pDC,rcSubItem.left+2,rcSubItem.top+(rcSubItem.Height()-m_pUnCheckImg->GetHeight())/2);

			rcSubItem.left+=(8+m_pCheckImg->GetWidth());
		}

		CItemImgArray::iterator iter = m_ItemImgArray.begin();

		for (;iter != m_ItemImgArray.end(); ++iter )
		{
			if ( iter->nItem == nItem )
			{
				CImageEx *pImage = iter->pImage;

				if (pImage != NULL && !pImage->IsNull())
				{
					pImage->DrawImage(pDC,rcSubItem.left+2,rcSubItem.top+(rcSubItem.Height()-pImage->GetHeight())/2);
					rcSubItem.left+=(8+pImage->GetWidth());
				}
				break;
			}
		}
	}

	pDC->DrawText(szString,lstrlen(szString),&rcSubItem,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	return;
}

BOOL CSkinListCtrl::OnEraseBkgnd( CDC* pDC )
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC BufferDC(pDC,&rcClient);

	BufferDC.FillSolidRect(&rcClient,m_colBack);

	return TRUE;
}

void CSkinListCtrl::SetItemHeight( int nHeight )
{
	m_nHeightItem = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);

	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void CSkinListCtrl::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
	if (m_nHeightItem>0)
	{
		lpMeasureItemStruct->itemHeight = m_nHeightItem;
	}
}

void CSkinListCtrl::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pHovenImg);
	RenderEngine->RemoveImage(m_pSelectImg);
	RenderEngine->RemoveImage(m_pCheckImg);
	RenderEngine->RemoveImage(m_pUnCheckImg);

	CItemImgArray::iterator iter = m_ItemImgArray.begin();

	for (;iter != m_ItemImgArray.end(); ++iter)
	{
		RenderEngine->RemoveImage(iter->pImage);
	}

	m_ItemImgArray.clear();

	RemoveScorll();
}

BOOL CSkinListCtrl::SetHovenImage( LPCTSTR lpszFileName,CONST LPRECT lprcNinePart/*=NULL*/ )
{
	RenderEngine->RemoveImage(m_pHovenImg);

	m_pHovenImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pHovenImg)
		return FALSE;
	else
	{
		m_pHovenImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CSkinListCtrl::SetSelectImage( LPCTSTR lpszFileName,CONST LPRECT lprcNinePart/*=NULL*/ )
{
	RenderEngine->RemoveImage(m_pSelectImg);

	m_pSelectImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pSelectImg)
		return FALSE;
	else
	{
		m_pSelectImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

BOOL CSkinListCtrl::SetCheckImage( LPCTSTR lpszCheckName,LPCTSTR lpszUnCheckName )
{
	RenderEngine->RemoveImage(m_pCheckImg);
	RenderEngine->RemoveImage(m_pUnCheckImg);

	m_pCheckImg = RenderEngine->GetImage(lpszCheckName);
	m_pUnCheckImg = RenderEngine->GetImage(lpszUnCheckName);

	if (NULL == m_pCheckImg || NULL == m_pUnCheckImg)
		return FALSE;
	else
		return TRUE;
}

BOOL CSkinListCtrl::InsertImage( int nItem,LPCTSTR lpszFileName )
{
	CItemImgArray::iterator iter = m_ItemImgArray.begin();

	for (;iter != m_ItemImgArray.end(); ++iter )
	{
		if ( iter->nItem == nItem )
		{
			//���ýڵ����ͼƬʱ�����Ǹ����µ�ͼƬ��Դ
			if( iter->pImage != NULL )
			{
				RenderEngine->RemoveImage(iter->pImage);

				iter->pImage = RenderEngine->GetImage(lpszFileName);
				
				return TRUE;
			}
		}
	}

	tagItemImage ItemImage;

	//��������
	ItemImage.nItem = nItem;
	ItemImage.pImage = RenderEngine->GetImage(lpszFileName);

	if (NULL == ItemImage.pImage)
		return FALSE;
	else
	{
		m_ItemImgArray.push_back(ItemImage);

		return TRUE;
	}
}


void CSkinListCtrl::OnMouseMove( UINT nFlags, CPoint point )
{
	CRect rcItem;

	static UINT uOldActiveItem = -1;

	for (int i=0;i<GetItemCount();i++)
	{
		GetItemRect(i,rcItem,LVIR_BOUNDS);

		if ( PtInRect(&rcItem,point) )
		{
			m_uActiveItem = i;

			if( uOldActiveItem != m_uActiveItem )
			{
				uOldActiveItem = m_uActiveItem;

				Invalidate(FALSE);
			}

			break;
		}
	}

	__super::OnMouseMove(nFlags, point);
}

void CSkinListCtrl::OnLButtonDown( UINT nFlags, CPoint point )
{
	if (m_pCheckImg != NULL && !m_pCheckImg->IsNull())
	{
		CRect rcSubItem,rcIcon;
		for (int i=0;i<GetItemCount();i++)
		{
			GetItemRect(i,rcSubItem,LVIR_BOUNDS);

			rcIcon.left = rcSubItem.left+7;
			rcIcon.top = rcSubItem.top+(rcSubItem.Height()-m_pCheckImg->GetHeight())/2;
			rcIcon.right = rcIcon.left + m_pCheckImg->GetWidth();
			rcIcon.bottom = rcIcon.top + m_pCheckImg->GetHeight();

			if ( PtInRect(&rcIcon,point) )
			{
 				SetCheck(i,!GetCheck(i));

				SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED,LVIS_FOCUSED | LVIS_SELECTED);
				SetSelectionMark(i);

				Invalidate(FALSE);
				break;
			}
		}
	}


	__super::OnLButtonDown(nFlags, point);
}

int CSkinListCtrl::InsertItem( const LVITEM* pItem )
{
	int nResult = __super::InsertItem(pItem);

	SetCheck(pItem->iItem,FALSE);

	return nResult;
}

int CSkinListCtrl::InsertItem( int nItem, LPCTSTR lpszItem )
{
	int nResult = __super::InsertItem(nItem,lpszItem);

	SetCheck(nItem,FALSE);

	return nResult;
}

int CSkinListCtrl::InsertItem( int nItem, LPCTSTR lpszItem, int nImage )
{
	int nResult = __super::InsertItem(nItem,lpszItem,nImage);

	SetCheck(nItem,FALSE);

	return nResult;
}

int CSkinListCtrl::InsertItem( UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,UINT nStateMask, int nImage, LPARAM lParam )
{
	int nResult = __super::InsertItem(nMask,nItem,lpszItem,nState,nStateMask,nImage,lParam);

	SetCheck(nItem,FALSE);

	return nResult;
}

DWORD CSkinListCtrl::SetExtendedStyle( DWORD dwNewStyle )
{
	if ( dwNewStyle & LVS_EX_CHECKBOXES )
	{
		dwNewStyle &=~LVS_EX_CHECKBOXES;
		dwNewStyle &=~LVS_EX_GRIDLINES;
	}
	
	return __super::SetExtendedStyle(dwNewStyle);
}


//////////////////////////////////////////////////////////////////////////////////

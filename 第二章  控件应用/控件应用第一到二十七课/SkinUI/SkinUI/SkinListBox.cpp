// SkinListBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "SkinListBox.h"

// CSkinListBox

IMPLEMENT_DYNAMIC(CSkinListBox, CListBox)

BEGIN_MESSAGE_MAP(CSkinListBox, CListBox)
	ON_WM_DESTROY()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

CSkinListBox::CSkinListBox( void )
{
	m_pBackImgN = NULL;
	m_pSelectImg = NULL;
	m_pBackImgH = NULL;
	m_nHovenItem = 0;
	nItemHeight = 20;
	m_ItemStruct.clear();
}

CSkinListBox::~CSkinListBox( void )
{

}

BOOL CSkinListBox::SetBackNormalImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgN);
	m_pBackImgN = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgN != NULL)
		m_pBackImgN->SetNinePart(lpNinePart);

	return (m_pBackImgN != NULL) ? TRUE : FALSE;
}

BOOL CSkinListBox::SetSelectImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pSelectImg);
	m_pSelectImg = RenderEngine->GetImage(lpszFileName);

	if (m_pSelectImg != NULL)
		m_pSelectImg->SetNinePart(lpNinePart);

	return (m_pSelectImg != NULL) ? TRUE : FALSE;
}

BOOL CSkinListBox::SetHovenImage( LPCTSTR lpszFileName, CONST LPRECT lpNinePart /*= NULL*/ )
{
	RenderEngine->RemoveImage(m_pBackImgH);
	m_pBackImgH = RenderEngine->GetImage(lpszFileName);

	if (m_pBackImgH != NULL)
		m_pBackImgH->SetNinePart(lpNinePart);

	return (m_pBackImgH != NULL) ? TRUE : FALSE;
}

void CSkinListBox::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pBackImgN);
	RenderEngine->RemoveImage(m_pBackImgH);
	RenderEngine->RemoveImage(m_pSelectImg);
}

void CSkinListBox::OnNcPaint()
{
	//�����Դû�о��ǲ�����Ʊ߿���
	if ( m_pBackImgN == NULL ) 
	{
		__super::OnNcPaint();
		return;
	}

	CRect rcWindow;
	GetWindowRect(&rcWindow);

	CRect rcClient;
	GetClientRect(&rcClient);

	ClientToScreen(&rcClient);
	rcClient.OffsetRect(-rcWindow.left, -rcWindow.top);

	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

	CDC *pWindowDC = GetWindowDC();
	CMemoryDC MemDC(pWindowDC,rcWindow);

	DrawParentWndBg(GetSafeHwnd(),MemDC.GetSafeHdc());

	if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
		m_pBackImgN->Draw(&MemDC, rcWindow);
	
	pWindowDC->BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),&MemDC,0,0,SRCCOPY);

	ReleaseDC(pWindowDC);
}

void CSkinListBox::OnRButtonUp(UINT nFlags, CPoint point)
{
	CRect rcItem(0,0,0,0);
	SetSel(-1,FALSE);

	for (int i =0; i<GetCount(); i++)
	{
		GetItemRect(i, &rcItem);

		if(rcItem.PtInRect(point))
		{
			if( IsSingleSel() )
				SetCurSel(i);
			else 
				SetSel(i);

			break;
		}
	}

	CWnd *pWnd = GetParent();
	if ( (pWnd == NULL) && (pWnd->GetSafeHwnd() != NULL) ) return;
	pWnd->PostMessage(WM_COMMAND,GetDlgCtrlID(),0);

	__super::OnRButtonUp(nFlags, point);
}

void CSkinListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rcItem(0,0,0,0);
	//�����״̬��Ϊ�˷�ֹ��ͬһ���ڵ���������ˢ������cpu��Դ
	static int nOldIndex = -1;

	for (int i =0; i<GetCount(); i++)
	{
		GetItemRect(i, &rcItem);

		if(rcItem.PtInRect(point))
		{
			if( m_nHovenItem != i )  Invalidate(FALSE);

			m_nHovenItem = i;

			break;
		}
	}


	__super::OnMouseMove(nFlags, point);
}

void CSkinListBox::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	//û�нڵ�Ͳ��ü���ִ����
	if( GetCount()==0 ) return;

	//��������
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDCControl=CDC::FromHandle(lpDrawItemStruct->hDC);

 	//��������
 	CDC BufferDC;
 	CBitmap ImageBuffer;
 	BufferDC.CreateCompatibleDC(pDCControl);
 	ImageBuffer.CreateCompatibleBitmap(pDCControl,rcItem.Width(),rcItem.Height());
 
 	//���û���
 	BufferDC.SelectObject(&ImageBuffer);
	BufferDC.SelectObject(GetCtrlFont());

	//��ȡ�ַ�
	CString strString;
	GetText(lpDrawItemStruct->itemID,strString);

	//����λ��
	CRect rcString;
	rcString.SetRect(4,0,rcItem.Width()-8,rcItem.Height());

	//��ɫ����
	COLORREF crTextColor=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0)?m_colSelectText:m_colNormalText;

	//�滭����
	BufferDC.FillSolidRect(0,0,rcItem.Width(),rcItem.Height(),m_colBack);

	//�ڵ�ѡ��
	if ( (lpDrawItemStruct->itemState&ODS_SELECTED) != 0 )
	{
		if ( m_pSelectImg!= NULL && !m_pSelectImg->IsNull() )
		{
			m_pSelectImg->Draw(&BufferDC,CRect(0,0,rcItem.Width(),rcItem.Height()));
		}
	}

	//�ڵ����
	else if ( m_nHovenItem == lpDrawItemStruct->itemID )
	{
		if ( m_pBackImgH!= NULL && !m_pBackImgH->IsNull() )
		{
			m_pBackImgH->Draw(&BufferDC,CRect(0,0,rcItem.Width(),rcItem.Height()));
		}
	}

	//�滭�ַ�
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(crTextColor);
	BufferDC.DrawText(strString,&rcString,DT_VCENTER|DT_SINGLELINE);

	//�滭����
	pDCControl->BitBlt(rcItem.left,rcItem.top,rcItem.Width(),rcItem.Height(),&BufferDC,0,0,SRCCOPY);

 	//������Դ
 	BufferDC.DeleteDC();
 	ImageBuffer.DeleteObject();
}

void CSkinListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	vector<tagItemStruct>::iterator iter = m_ItemStruct.begin();

	for (;iter != m_ItemStruct.end(); ++iter )
	{
		lpMeasureItemStruct->itemHeight = iter->itemHeight;
		lpMeasureItemStruct->itemWidth = iter->itemWidth;
	}
}

bool CSkinListBox::IsSingleSel()
{
	DWORD dwStyle = GetStyle();

	if ( ((dwStyle&LBS_EXTENDEDSEL)!=0) || ((dwStyle&LBS_MULTIPLESEL)!=0) )
	{
		return false;
	}

	return true;
}

void CSkinListBox::AddString(LPCTSTR lpszItem)
{
	InsertItem();

	__super::AddString(lpszItem);
}

int CSkinListBox::SetItemHeight( int nIndex, UINT cyItemHeight )
{
	if ( nIndex == -1 ) nItemHeight = cyItemHeight;
	
	vector<tagItemStruct>::iterator iter = m_ItemStruct.begin();

	for (;iter != m_ItemStruct.end(); ++iter )
	{
		if ( iter->itemID == nIndex )
		{
			iter->itemHeight = cyItemHeight;

			break;
		}
	}

	return __super::SetItemHeight(nIndex,cyItemHeight);
}

int CSkinListBox::DeleteString( UINT nIndex )
{
 	vector<tagItemStruct>::iterator iter = m_ItemStruct.begin();
 
 	for (;iter != m_ItemStruct.end(); ++iter )
 	{
 		if ( iter->itemID == nIndex )
 		{
 			m_ItemStruct.erase(iter);
			break;
 		}
 	}

	return __super::DeleteString(nIndex);
}

void CSkinListBox::InsertItem()
{
	tagItemStruct ItemStruct;
	ZeroMemory(&ItemStruct,sizeof ItemStruct);

	CRect rcClient;
	GetClientRect(&rcClient);

	ItemStruct.itemID = m_ItemStruct.size();
	ItemStruct.itemHeight = nItemHeight;
	ItemStruct.itemWidth = rcClient.Width();

	m_ItemStruct.push_back(ItemStruct);
}

// SkinTreeCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Resource.h"
#include "SkinTreeCtrl.h"


// CSkinTreeCtrl

IMPLEMENT_DYNAMIC(CSkinTreeCtrl, CTreeCtrl)

CSkinTreeCtrl::CSkinTreeCtrl()
{
	m_hItemMouseHover=NULL;
	m_colBack = RGB(255,255,255);
	m_uCursorRes = 0;

	m_pImageButton = NULL;
	m_pHovenImg = m_pPressImg = NULL;
	m_MapItemInfo.clear();

	m_colHoven = RGB(255,0,0);
	m_colPress = RGB(253,231,161);
}

CSkinTreeCtrl::~CSkinTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CSkinTreeCtrl, CTreeCtrl)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CSkinTreeCtrl ��Ϣ�������



void CSkinTreeCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC BufferDC(&dc,rcClient);

	//����λ��
	CRect rcClipBox;
	BufferDC.GetClipBox(&rcClipBox);

	//���Ʊ���
	BufferDC.FillSolidRect(rcClient,m_colBack);
	DrawParentWndBg(GetSafeHwnd(),BufferDC->GetSafeHdc());

	DrawTreeItem(&BufferDC,rcClient,rcClipBox);
}

VOID CSkinTreeCtrl::DrawTreeItem( CDC * pDC, CRect & rcClient, CRect & rcClipBox )
{
	//�����ж�
	HTREEITEM hItemCurrent=GetFirstVisibleItem();
	if (hItemCurrent==NULL) return;

	//��ȡ����
	UINT uTreeStyte = GetStyle();

	//�滭����
	do
	{
		//��������
		CRect rcItem;
		CRect rcRect;

		//��ȡ״̬
		HTREEITEM hParent=GetParentItem(hItemCurrent);
		UINT uItemState=GetItemState(hItemCurrent,TVIF_STATE);

		//��ȡ����
		bool bDrawChildren=(ItemHasChildren(hItemCurrent)==TRUE);
		bool bDrawSelected=(uItemState&TVIS_SELECTED)&&((this==GetFocus())||(uTreeStyte&TVS_SHOWSELALWAYS));

		//��ȡ����
		if (GetItemRect(hItemCurrent,rcItem,TRUE))
		{
			//�滭����
			if (rcItem.top>=rcClient.bottom) break;
			if (rcItem.top>=rcClipBox.bottom) continue;

			//����λ��
			rcRect.left=0;
			rcRect.top=rcItem.top+1;
			rcRect.bottom=rcItem.bottom;
			rcRect.right=rcClient.Width();

			//�滭ѡ��
			if (bDrawSelected)
			{
				if (m_pPressImg != NULL && !m_pPressImg->IsNull())
					m_pPressImg->Draw(pDC,rcRect);
				else
					pDC->FillSolidRect(&rcRect,m_colPress);
			}

			//�滭����
 			if ((bDrawSelected==false)&&(m_hItemMouseHover==hItemCurrent))
 			{
				if (m_pHovenImg != NULL && !m_pHovenImg->IsNull())
					m_pHovenImg->Draw(pDC,rcRect);
				else
 					pDC->FillSolidRect(&rcRect,m_colHoven);
 			}

			//���Ƽ�ͷ
 			if (bDrawChildren && (uTreeStyte&TVS_HASBUTTONS) )
 			{
				if (m_pImageButton != NULL && !m_pImageButton->IsNull())
				{
					//����λ��
					INT nXPos=rcItem.left-m_pImageButton->GetWidth()/2;
					INT nYPos=rcItem.top+1+(rcItem.Height()-m_pImageButton->GetHeight())/2;

					//�滭ͼ��
					INT nIndex=(uItemState&TVIS_EXPANDED)?1L:0L;
					m_pImageButton->DrawImage(pDC,nXPos,nYPos,m_pImageButton->GetWidth()/2,m_pImageButton->GetHeight(),nIndex*m_pImageButton->GetWidth()/2,0);
				
					rcItem.left += m_pImageButton->GetWidth();
					rcItem.right += m_pImageButton->GetWidth();;
				}

 			}

			//�����б�
			DrawListImage(pDC,rcItem,hItemCurrent,bDrawSelected);	

			//�����ı�
			DrawItemString(pDC,rcItem,hItemCurrent,bDrawSelected);
		}
	} while ((hItemCurrent=GetNextVisibleItem(hItemCurrent))!= NULL);
}

VOID CSkinTreeCtrl::DrawListImage( CDC * pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected )
{
	CMapItemInfo::iterator iter= m_MapItemInfo.find(hTreeItem);
	if( iter == m_MapItemInfo.end() )
	{
		CImageList *pImageList = GetImageList(TVSIL_NORMAL);
		if( pImageList == NULL ) return;

		//��ȡ����
		INT nImage,nSelectedImage;
		GetItemImage(hTreeItem,nImage,nSelectedImage);

		//��ȡ��Ϣ
		IMAGEINFO ImageInfo;
		pImageList->GetImageInfo(bSelected?nSelectedImage:nImage,&ImageInfo);

		//�滭ͼ��
		INT nImageWidth=ImageInfo.rcImage.right-ImageInfo.rcImage.left;
		INT nImageHeight=ImageInfo.rcImage.bottom-ImageInfo.rcImage.top;

		pImageList->Draw(pDC,bSelected?nSelectedImage:nImage,CPoint(rcRect.left-nImageWidth-3,rcRect.top+(rcRect.Height()-nImageHeight)/2+1),ILD_TRANSPARENT);
	}
	else
	{
		CImageEx *pImage = iter->second.pImage;
		pImage->DrawImage(pDC,rcRect.left-pImage->GetWidth()-3,rcRect.top+(rcRect.Height()-pImage->GetHeight())/2+1);
	}
}

VOID CSkinTreeCtrl::DrawItemString( CDC * pDC, CRect rcRect, HTREEITEM hTreeItem, bool bSelected )
{
	//���û���
	pDC->SelectObject(GetCtrlFont());
	pDC->SetBkMode(TRANSPARENT);

	if( !IsWindowEnabled() ) pDC->SetTextColor(m_colDisableText);
	else pDC->SetTextColor(bSelected?m_colSelectText:m_colNormalText);

	//�滭����
	rcRect.right += 5;

	CString strString=GetItemText(hTreeItem);
	pDC->DrawText(strString,rcRect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	return;
}

BOOL CSkinTreeCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//�������
	HTREEITEM hItemMouseHover=HitTest(MousePoint);

	//�ػ��ж�
	if ((hItemMouseHover!=NULL)&&(hItemMouseHover!=m_hItemMouseHover))
	{
		//���ñ���
		m_hItemMouseHover=hItemMouseHover;

		//�ػ�����
		Invalidate(FALSE);
	}

	//���ù��
	if (hItemMouseHover!=NULL)
	{
		if( m_uCursorRes )
			SetCursor(LoadCursor(GetModuleHandle(SKINUI_DLL_NAME),MAKEINTRESOURCE(m_uCursorRes)));

		return true;
	}

	return __super::OnSetCursor(pWnd, nHitTest, message);
}

void CSkinTreeCtrl::SetCursorStyle(UINT uID)
{
	m_uCursorRes = uID;
}

BOOL CSkinTreeCtrl::SetButtonImage( LPCTSTR lpszFileName )
{
	RenderEngine->RemoveImage(m_pImageButton);

	m_pImageButton = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pImageButton)
		return FALSE;
	else
		return TRUE;
}

void CSkinTreeCtrl::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pImageButton);

	CMapItemInfo::iterator iter= m_MapItemInfo.begin();

	for (;iter!= m_MapItemInfo.end();++iter)
	{
		RenderEngine->RemoveImage(iter->second.pImage);
	}
}

BOOL CSkinTreeCtrl::InsertImage( HTREEITEM hTreeItem,LPCTSTR lpszFileName )
{
	CMapItemInfo::iterator iter= m_MapItemInfo.find(hTreeItem);

	if ( iter != m_MapItemInfo.end())
	{
		CImageEx *pImage = RenderEngine->GetImage(lpszFileName);

		if (NULL == pImage)
			return FALSE;
		else
		{
			iter->second.pImage = pImage;
			return TRUE;
		}
	}
	else
	{
		tagItemInfo _ItemInfo;
		_ItemInfo.hTreeItem = hTreeItem;
		_ItemInfo.pImage = RenderEngine->GetImage(lpszFileName);

		if (NULL == _ItemInfo.pImage) return FALSE;

		m_MapItemInfo.insert(pair<HTREEITEM,tagItemInfo>(hTreeItem,_ItemInfo));

		return TRUE;
	}
}

BOOL CSkinTreeCtrl::SetHovenImage( LPCTSTR lpszFileName,CONST LPRECT lprcNinePart/*=NULL*/ )
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

BOOL CSkinTreeCtrl::SetPressImage( LPCTSTR lpszFileName,CONST LPRECT lprcNinePart/*=NULL*/ )
{
	RenderEngine->RemoveImage(m_pPressImg);

	m_pPressImg = RenderEngine->GetImage(lpszFileName);

	if (NULL == m_pPressImg)
		return FALSE;
	else
	{
		m_pPressImg->SetNinePart(lprcNinePart);
		return TRUE;
	}
}

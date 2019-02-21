/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListBoxEx.h"

#pragma warning(disable: 4018)
#pragma warning(disable: 4312)
#pragma warning(disable: 4311)
#pragma warning(disable: 4267)
#pragma warning(disable: 4244)


CListBoxEx::CListBoxEx()
{
	m_mapSTL.clear();
	m_bShowStates = false;
	m_bDoDraw     = true;
	m_bNode		  = false;
	m_nItemHeight =0;
	m_nListIndex  =0;
	m_ColFrame=RGB(84,165,213);
	m_pImageDown = m_pImageRight = NULL;
}

CListBoxEx::~CListBoxEx()
{
	ResetNodeInfo();
}

BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CListBoxEx::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	if (!m_bDoDraw) return;
	if (!lpDrawItemStruct || ((int)(lpDrawItemStruct->itemID) < 0)) return;
	ListBoxInfo* pCatInfo = (ListBoxInfo*)lpDrawItemStruct->itemData;
	if (!pCatInfo) return;

	//���Ʊ�����ɫ
	CRect rcItem = lpDrawItemStruct->rcItem;
	COLORREF crBKColor;

	CDC* pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	CMemoryDC BufferDC(pDC,rcItem);
	bool bHighlight = ((lpDrawItemStruct->itemState & ODS_SELECTED) &&!(GetStyle() & LBS_NOSEL) && IsWindowEnabled());


	if (bHighlight)
		crBKColor = lpDrawItemStruct->itemID == pCatInfo->iListIndex?RGB(223,233,239):RGB(252,236,173);
	else crBKColor=RGB(255,255,255);

	BufferDC.FillSolidRect( rcItem,crBKColor );


	//ȷ���������ڵ㰴ť��λ��
	CRect rcButton( rcItem );
	rcButton.top    += Y_MARGIN;
	rcButton.left   += X_MARGIN;
	rcButton.bottom -= Y_MARGIN + 1;
	rcButton.right   = rcButton.left + rcButton.Height();

	//���Ƹ��ڵ�
	if (lpDrawItemStruct->itemID == pCatInfo->iListIndex) 
	{
		//���Ƹ��ڵ������ť
		int nLeft = rcButton.left;
		int nTop = rcButton.top;

		if (m_pImageRight && m_pImageDown && !m_pImageRight->IsNull() && !m_pImageDown->IsNull() )
		{
			for (;nLeft < (rcButton.right - X_MARGIN); nLeft++)
			{
				if (!pCatInfo->bIsOpen)
					m_pImageRight->DrawImage(&BufferDC,5,nTop);
				else 
					m_pImageDown->DrawImage(&BufferDC,5,nTop);
			}
		}
	}
	else if (m_bShowStates) 
	{
		//���ݵ�ǰ��״̬����checkbox�ؼ�
		ListBoxStlListIter   iter;
		int  iCount = (lpDrawItemStruct->itemID - pCatInfo->iListIndex) - 1;
		for (iter = pCatInfo->lstItems.begin(); iter != pCatInfo->lstItems.end(); iter++) 
		{ 
			if (iCount <= 0) 
			{
				if (0 == (*iter).iState)         //����checkbox�ؼ�
					BufferDC.DrawFrameControl( rcButton, DFC_BUTTON, DFCS_BUTTONCHECK | DFCS_FLAT );
				else if (1 == (*iter).iState)    //����û�С̵�checkbox�ؼ�
					BufferDC.DrawFrameControl( rcButton, DFC_BUTTON, DFCS_BUTTONCHECK | DFCS_FLAT | DFCS_CHECKED );
				break;
			}
			iCount--;
		}
	}
	else
	{
		ListBoxStlListIter   iter;
		int  iCount = (lpDrawItemStruct->itemID - pCatInfo->iListIndex) - 1;
		for (iter = pCatInfo->lstItems.begin(); iter != pCatInfo->lstItems.end(); iter++) 
		{
			////���ƴ�ͷ��
			//if (GetItemHeight()==LIST_CNODE_HEIGHT_B)
			//	m_ImageFace.DrawSkinImage(pDC,rcButton.left,rcButton.top+5,FACE_BIG,FACE_BIG);
			////����Сͷ��
			//else m_ImageFace.DrawSkinImage(pDC,rcButton.left,rcButton.top+5,FACE_SMALL,FACE_SMALL);

			iCount--;
		}
	}

	//��������
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SelectObject(GetCtrlFont());

	crBKColor = IsWindowEnabled() ? m_colNormalText : m_colDisableText;
	COLORREF crOldTxt = pDC->SetTextColor( crBKColor );

	CString  sText;
	GetText( lpDrawItemStruct->itemID, sText );

	int nTextPosX = lpDrawItemStruct->rcItem.left;
	int nTextPosY = lpDrawItemStruct->rcItem.top;
	if (m_bShowStates || (lpDrawItemStruct->itemID == pCatInfo->iListIndex))
	{
		nTextPosX = rcButton.right+10;
		nTextPosY = rcButton.top+5;
	}
	else
	{
		// 		if (m_ImageFace.IsNull())
		// 		{
		// 			if (GetItemHeight()==LIST_CNODE_HEIGHT_B)
		// 			{
		// 				iTextPosX = m_ImageFace.GetSkinImageWidth()+15;
		// 				iTextPosY +=5 ;
		// 			}
		// 			else 
		// 			{
		// 				iTextPosX = m_ImageFace.GetSkinImageWidth();
		// 				iTextPosY +=9;
		// 			}
		// 		}
	}

	BufferDC.TextOut( nTextPosX, nTextPosY, sText );

	//  	//����ؼ��н���,��ô�ͻ���һ���������.
	//  	if (/*IsWindowEnabled() && */(lpDrawItemStruct->itemState & ODS_CHECKED)) 
	//  	{
	//  		pDC->DrawFocusRect( &(lpDrawItemStruct->rcItem) );
	//  	}

	BufferDC.SetTextColor( crOldTxt );
}

//�򿪣��رսڵ㣬�Լ������ͽ���Checkbox
void CListBoxEx::OnLButtonDown( UINT nFlags, CPoint point )
{
	ListBoxInfo*		 pCatInfo;
	CString              sCategory;
	CRect                rcValue;
	int                  iHeight;
	int                  iListIndex;

	//��ȡListBox�ĸ߶�
	GetWindowRect( rcValue );
	iHeight = rcValue.Height();

	for (iListIndex = GetTopIndex(); iListIndex < GetCount(); iListIndex++) 
	{
		pCatInfo = (ListBoxInfo*)GetItemData( iListIndex );
		if (!pCatInfo)
			continue;

		GetItemRect( iListIndex, rcValue );
		rcValue.top    += Y_MARGIN;
		rcValue.bottom -= Y_MARGIN + 1;
		rcValue.right   = rcValue.left + rcValue.Height()+15;

		if (rcValue.top >= iHeight)
			break;

		if (rcValue.PtInRect( point )) 
		{
			GetText( pCatInfo->iListIndex, sCategory );
			SetCurSel( iListIndex );
			if (iListIndex == pCatInfo->iListIndex) 
			{
				SetNodeState( (LPCTSTR)sCategory, !(pCatInfo->bIsOpen) );
			}
			else if (m_bShowStates) 
			{
				int iItemIndex = (iListIndex - pCatInfo->iListIndex) - 1;
				int iState = GetItemState( (LPCTSTR)sCategory, iItemIndex );
				if (0 == iState)
					SetItemState( (LPCTSTR)sCategory, iItemIndex, 1 );
				else if (1 == iState)
					SetItemState( (LPCTSTR)sCategory, iItemIndex, 0 );
			}
			break;
		}
	}
	CListBox::OnLButtonDown( nFlags, point );
}

void CListBoxEx::OnMouseMove(UINT nFlags, CPoint point)
{
	ListBoxInfo*		 pCatInfo;
	CRect                rcValue;
	int                  iHeight;
	int                  iListIndex;
	//��ȡListBox�ĸ߶�
	GetWindowRect( rcValue );
	iHeight = rcValue.Height();

	for (iListIndex = GetTopIndex(); iListIndex < GetCount(); iListIndex++) 
	{
		pCatInfo = (ListBoxInfo*)GetItemData( iListIndex );
		if (!pCatInfo)
			continue;

		GetItemRect( iListIndex, rcValue );
		rcValue.top    += Y_MARGIN;
		rcValue.bottom -= Y_MARGIN + 1;
		rcValue.right   = rcValue.left + rcValue.Width();

		if (rcValue.top >= iHeight)
			break;

		if (rcValue.PtInRect( point )) 
		{
			if (iListIndex == pCatInfo->iListIndex)
			{
				m_bNode=true;
			}
			m_rcItem=rcValue;
			static CRect rcTemp;
			m_nListIndex=iListIndex;
			break;
		}
	}
	CListBox::OnMouseMove(nFlags, point);
}
void CListBoxEx::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	ListBoxInfo*		 pCatInfo;
	CString              sCategory;
	CRect                rcValue;
	int                  iHeight;
	int                  iListIndex;

	GetWindowRect( rcValue );
	iHeight = rcValue.Height();

	for (iListIndex = GetTopIndex(); iListIndex < GetCount(); iListIndex++) 
	{
		pCatInfo = (ListBoxInfo*)GetItemData( iListIndex );
		if (!pCatInfo)
			continue;

		if (iListIndex != pCatInfo->iListIndex)
			continue;

		GetItemRect( iListIndex, rcValue );
		if (rcValue.top >= iHeight)
			break;         
		if (rcValue.PtInRect( point )) 
		{
			GetText( iListIndex, sCategory );
			SetCurSel( iListIndex );
			SetNodeState( (LPCTSTR)sCategory, !(pCatInfo->bIsOpen) );
			break;      
		}
	}
	CListBox::OnLButtonDblClk( nFlags, point );
}

void CListBoxEx::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (VK_SPACE == nChar) 
	{
		int iListIndex = GetCurSel();
		if (iListIndex != LB_ERR) 
		{
			ListBoxInfo* pInfo = (ListBoxInfo*)GetItemData( iListIndex );
			if (pInfo && (LB_ERR != (int)pInfo))
			{
				CString  sCategory;
				GetText( pInfo->iListIndex, sCategory );
				if (iListIndex == pInfo->iListIndex) 
				{
					SetNodeState( (LPCTSTR)sCategory, !(pInfo->bIsOpen) );
				}
				else if (m_bShowStates) 
				{
					int iItemIndex = (iListIndex - pInfo->iListIndex) - 1;
					int iState = GetItemState( (LPCTSTR)sCategory, iItemIndex );
					if (0 == iState)
						SetItemState( (LPCTSTR)sCategory, iItemIndex, 1 );
					else if (1 == iState)
						SetItemState( (LPCTSTR)sCategory, iItemIndex, 0 );
				}
			}
		}
	}
	CListBox::OnKeyDown( nChar, nRepCnt, nFlags );
}

//��Ӹ��ڵ�
HRESULT CListBoxEx::AddNode( LPCTSTR pCategory )
{
	ListBoxStlMapIter    iter;
	ListBoxInfo*			pCatInfo;
	ListBoxInfo*			pTempInfo;

	if (!pCategory)
		return E_POINTER;
	if (_tcslen( pCategory ) <= 0)
		return E_INVALIDARG;
	if (m_mapSTL.end() != m_mapSTL.find(CString(pCategory)))
		return E_INVALIDARG;

	try 
	{
		pCatInfo = new ListBoxInfo;
		if (!pCatInfo)
			return E_FAIL;
		pCatInfo->bIsOpen    = false;
		pCatInfo->iListIndex = -1;
		m_mapSTL.insert( ListBoxStlMap::value_type( CString(pCategory), pCatInfo ) );
	}
	catch (...) 
	{
		ASSERT(0);
		return E_FAIL;
	}

	//���Ӹ��ڵ㵽ListBox
	if (LBS_SORT & GetStyle()) 
	{
		for (iter = m_mapSTL.begin(); iter != m_mapSTL.end(); iter++) 
		{
			pTempInfo = (*iter).second;
			if (!pTempInfo || (pTempInfo == pCatInfo))
				continue;
			if ((*iter).first.CompareNoCase( pCategory ) > 0) 
			{
				if ((UINT)pCatInfo->iListIndex > (UINT)pTempInfo->iListIndex)
					pCatInfo->iListIndex = pTempInfo->iListIndex;
				pTempInfo->iListIndex++;
			}
		}
	}
	m_bDoDraw = false;
	pCatInfo->iListIndex = InsertString( pCatInfo->iListIndex, pCategory );
	SetItemData( pCatInfo->iListIndex, (DWORD)pCatInfo );
	m_bDoDraw = true;
	SetNodeItemHeight(m_nItemHeight);
	Invalidate();

	return S_OK;
}

int CListBoxEx::AddItem( LPCTSTR pCategory, LPCTSTR pItem, int iState)
{
	ListBoxInfo*				pCatInfo;
	ListBoxItemInfo			ItemInfo;
	ListBoxStlListIter		iter;
	int						iItemIndex = 0;
	int						iListIndex;

	if (!pCategory)
		return LB_ERR;

	pCatInfo = GetNodeInfo( pCategory );
	if (!pCatInfo) 
	{
		if (S_OK != AddNode( pCategory ))
			return LB_ERR;
		pCatInfo = GetNodeInfo( pCategory );
		if (!pCatInfo)
			return LB_ERR;
	}

	if (LBS_SORT & GetStyle()) 
	{
		iItemIndex = 0;
		for (iter = pCatInfo->lstItems.begin(); iter != pCatInfo->lstItems.end(); iter++) 
		{
			if ((*iter).sItem.CompareNoCase( pItem ) > 0)
				break;
			iItemIndex++;
		}
	}
	else 
	{
		iter       = pCatInfo->lstItems.end();
		iItemIndex = pCatInfo->lstItems.size();
	}
	ItemInfo.dwValue = 0;
	ItemInfo.iState  = iState;
	ItemInfo.sItem   = pItem;
	pCatInfo->lstItems.insert( iter, ItemInfo );

	if (pCatInfo->bIsOpen) 
	{
		m_bDoDraw = false;  
		iListIndex = pCatInfo->iListIndex + iItemIndex + 1;
		iListIndex = InsertString( iListIndex, pItem );
		if (iListIndex >= 0) 
		{
			SetItemData( iListIndex, (DWORD)pCatInfo );
			UpdateNodeIndexes( pCatInfo->iListIndex, 1 );
		}
		m_bDoDraw = true;
		Invalidate();
	}

	return iItemIndex;
}

int CListBoxEx::AddString( LPCTSTR pString )
{
	return CListBox::AddString( pString );
}

int CListBoxEx::InsertString( int iListIndex, LPCTSTR pString )
{
	return CListBox::InsertString( iListIndex, pString );
}
//ɾ���ڵ�
HRESULT CListBoxEx::Delete( int iListIndex )
{
	ListBoxInfo*			pInfo;
	CString              sCategory;
	HRESULT              hr = E_FAIL;

	if ((iListIndex < 0) || (iListIndex >= GetCount()))
		return E_INVALIDARG;

	pInfo = (ListBoxInfo*)GetItemData( iListIndex );
	if (!pInfo)
		return E_FAIL;

	GetText( pInfo->iListIndex, sCategory );
	if (iListIndex == pInfo->iListIndex)
		hr = DeleteNode( (LPCTSTR)sCategory );
	else
		hr = DeleteItem( (LPCTSTR)sCategory, (iListIndex - pInfo->iListIndex) - 1 );
	return hr;
}

//ɾ�����ڵ��Լ����µ������ӽڵ�
HRESULT CListBoxEx::DeleteNode( LPCTSTR pCategory )
{
	ListBoxInfo*      pInfo;
	ListBoxStlMapIter    iter;
	int                     iCount = 0;

	if (!pCategory)
		return E_POINTER;

	iter = m_mapSTL.find( CString( pCategory ) );
	if (iter == m_mapSTL.end())
		return E_INVALIDARG;
	pInfo = (*iter).second;
	if (!pInfo)
		return E_INVALIDARG;

	m_bDoDraw = false;   
	while ((ListBoxInfo*)GetItemData( pInfo->iListIndex ) == pInfo)
	{
		DeleteString( pInfo->iListIndex );
		iCount++;
	}
	UpdateNodeIndexes( pInfo->iListIndex, 0 - iCount );
	m_bDoDraw = true;   
	Invalidate();

	delete pInfo;
	(*iter).second = NULL;
	m_mapSTL.erase( iter );
	return S_OK;
}

//ɾ���ӽڵ�
HRESULT CListBoxEx::DeleteItem( LPCTSTR pCategory, int iItemIndex )
{
	ListBoxInfo*				pInfo;
	ListBoxStlListIter		iter;
	int						iValue;

	if (!pCategory)
		return E_POINTER;

	pInfo = GetNodeInfo( pCategory );
	if (!pInfo)
		return E_INVALIDARG;

	if ((iItemIndex < 0) || (iItemIndex >= pInfo->lstItems.size()))
		return E_INVALIDARG;

	if (pInfo->bIsOpen) 
	{
		m_bDoDraw = false;   
		iValue = pInfo->iListIndex + iItemIndex + 1;
		DeleteString( iValue );
		UpdateNodeIndexes( iValue, -1 );
		m_bDoDraw = true; 
		Invalidate();
	}

	iValue = 0;
	for (iter = pInfo->lstItems.begin(); iter != pInfo->lstItems.end(); iter++) 
	{
		if (iValue == iItemIndex)
			break;
		iValue++;
	}
	pInfo->lstItems.erase( iter );
	return S_OK;
}

int CListBoxEx::DeleteString( UINT iListIndex )
{
	return CListBox::DeleteString( iListIndex );
}


//����ؼ�
void CListBoxEx::ResetContent()
{
	//���ListBox
	CListBox::ResetContent();

	//���Map����
	ResetNodeInfo();
}

//����ڵ���Ϣ�����map��
void CListBoxEx::ResetNodeInfo()
{
	ListBoxStlMapIter    iter;
	ListBoxInfo*			pInfo;

	for (iter = m_mapSTL.begin(); iter != m_mapSTL.end(); iter++) 
	{
		if (pInfo = (*iter).second) 
		{
			delete pInfo;
			(*iter).second = NULL;
		}
	}
	m_mapSTL.clear();
}


//////////////////////////////////////////////////////////////////////
//���Ҹ��ڵ�
//////////////////////////////////////////////////////////////////////

//����ListBox��������û���ҵ��򷵻�-1
int CListBoxEx::FindNode( LPCTSTR pCategory )
{
	ListBoxInfo* pInfo = GetNodeInfo( pCategory );
	return (pInfo) ? pInfo->iListIndex : -1;
}

int CListBoxEx::FindItem( LPCTSTR pCategory, int iStartAfter, LPCTSTR pItem )
{
	ListBoxInfo*      pInfo;
	ListBoxStlListIter   iter;
	int                     iCount = 0;

	if (!pCategory || !pItem)
		return -1;

	pInfo = GetNodeInfo( pCategory );
	if (!pInfo)
		return -1;

	for (iter = pInfo->lstItems.begin(); iter != pInfo->lstItems.end(); iter++)
	{
		if (iCount > iStartAfter) 
		{
			if (0 == (*iter).sItem.Compare( pItem )) 
			{
				return iCount;
			}
		}
		iCount++;
	}
	return -1;
}

//�ж��Ƿ�Ϊ���ڵ�
bool CListBoxEx::IsParentNode( int iListIndex )
{
	ListBoxInfo* pInfo = (ListBoxInfo*)GetItemData( iListIndex );
	if (pInfo && (LB_ERR != (int)pInfo)) 
	{
		if (iListIndex == pInfo->iListIndex) 
		{
			return true;
		}
	}
	return false;
}

//���pString�Ǹ��ڵ�������򷵻�true���򷵻�false
bool CListBoxEx::IsParentNode( LPCTSTR pString )
{
	return (FindNode( pString ) >= 0) ? true : false;
}

//�жϸ��ڵ��Ƿ��״̬���������Ϊtrue������ڵ㲻���ڻ���������״̬�ͷ���false
bool CListBoxEx::IsNodeOpen( LPCTSTR pCategory )
{
	ListBoxInfo* pInfo = GetNodeInfo( pCategory );
	if (pInfo)
	{
		if (pInfo->bIsOpen) 
		{
			return true;
		}
	}
	return false;
}

//��ȡ���ڵ������
int CListBoxEx::GetParentNodeCount()
{
	return m_mapSTL.size();
}

//��ȡ�ڵ������
LPCTSTR CListBoxEx::GetParentNodeName( int iIndex, bool bIsListIndex /*=true*/ )
{
	ListBoxStlMapIter    iter;
	ListBoxInfo*      pInfo;

	//���Ҹ��ڵ�
	if (bIsListIndex) 
	{
		//ͨ��ListBox������ֵ��ȡ�ڵ������
		pInfo = (ListBoxInfo*)GetItemData( iIndex );
		if (pInfo && (LB_ERR != (int)pInfo)) 
		{
			for (iter = m_mapSTL.begin(); iter != m_mapSTL.end(); iter++) 
			{
				if (pInfo == (*iter).second) 
				{
					return (LPCTSTR)((*iter).first);
				}
			}
		}
	}
	else 
	{
		if ((iIndex >= 0) && (iIndex < m_mapSTL.size())) 
		{
			for (iter = m_mapSTL.begin(); iter != m_mapSTL.end(); iter++) 
			{
				if (iIndex <= 0)
					return (LPCTSTR)((*iter).first);
				iIndex--;
			}
		}
	}
	return NULL;
}

//��ȡĳ���ڵ����ӽڵ������
int CListBoxEx::GetItemCount( LPCTSTR pCategory )
{
	ListBoxInfo* pCatInfo = GetNodeInfo( pCategory );
	if (!pCatInfo)
		return -1;
	return pCatInfo->lstItems.size();
}

//�����ӽڵ����ֵ.���ʧ�ܽ�����LB_ERR
DWORD CListBoxEx::GetItemData( LPCTSTR pCategory, int iItemIndex )
{
	ListBoxInfo*      pCatInfo;
	ListBoxStlListIter   iter;

	if (!pCategory || (iItemIndex < 0))
		return LB_ERR;

	pCatInfo = GetNodeInfo( pCategory );
	if (!pCatInfo)
		return LB_ERR;

	for (iter = pCatInfo->lstItems.begin(); iter != pCatInfo->lstItems.end(); iter++) 
	{
		if (iItemIndex <= 0)
			return (*iter).dwValue;
		iItemIndex--;
	}
	return LB_ERR;
}

DWORD CListBoxEx::GetItemData( int iListIndex )
{
	return CListBox::GetItemData( iListIndex );
}
//��ȡ�ӽڵ������ֵ
int CListBoxEx::GetItemIndex( int iListIndex )
{
	ListBoxInfo* pInfo = (ListBoxInfo*)GetItemData( iListIndex );
	if (pInfo && (LB_ERR != (int)pInfo))
		return (iListIndex - pInfo->iListIndex) - 1;
	return -1;
}
//��ȡ�ӽڵ������
LPCTSTR CListBoxEx::GetItemName( LPCTSTR pCategory, int iItemIndex )
{
	ListBoxInfo*			pInfo;
	ListBoxStlListIter		iter;

	pInfo = GetNodeInfo( pCategory );
	if (!pInfo)
		return NULL;

	for (iter = pInfo->lstItems.begin(); iter != pInfo->lstItems.end(); iter++)
	{
		if (iItemIndex <= 0)
			return (LPCTSTR)((*iter).sItem);
		iItemIndex--;
	}
	return NULL;
}
//��ȡ�ӽڵ��״̬�Ƿ�ΪCheck
int CListBoxEx::GetItemState( LPCTSTR pCategory, int iItemIndex )
{
	ListBoxInfo*      pInfo;
	ListBoxStlListIter   iter;

	pInfo = GetNodeInfo( pCategory );
	if (!pInfo)
		return LB_ERR;

	if ((iItemIndex < 0) || (iItemIndex >= pInfo->lstItems.size()))
		return E_INVALIDARG;

	for (iter = pInfo->lstItems.begin(); iter != pInfo->lstItems.end(); iter++) 
	{
		if (iItemIndex <= 0)
			return (*iter).iState;
		iItemIndex--;
	}
	return LB_ERR;
}

//���ظ��ڵ����Ϣ���������NULL�����û�д˽ڵ�
ListBoxInfo* CListBoxEx::GetNodeInfo( LPCTSTR pCategory )
{
	ListBoxStlMapIter iter;

	if (!pCategory)
		return NULL;

	iter = m_mapSTL.find( CString((LPCSTR)pCategory) );
	if (iter == m_mapSTL.end())
		return NULL;
	return (*iter).second;
}

//�����ӽڵ�ķ���ֵ
HRESULT CListBoxEx::SetItemData( LPCTSTR pCategory, int iItemIndex, DWORD dwValue )
{
	ListBoxInfo*      pCatInfo;
	ListBoxStlListIter   iter;

	if (!pCategory)
		return E_POINTER;

	pCatInfo = GetNodeInfo( pCategory );
	if (!pCatInfo)
		return E_INVALIDARG;

	if ((iItemIndex < 0) || (iItemIndex >= pCatInfo->lstItems.size()))
		return E_INVALIDARG;

	for (iter = pCatInfo->lstItems.begin(); iter != pCatInfo->lstItems.end(); iter++) 
	{
		if (iItemIndex <= 0) 
		{
			(*iter).dwValue = dwValue;
			break;
		}
		iItemIndex--;
	}
	return S_OK;
}

int CListBoxEx::SetItemData( int iListIndex, DWORD dwValue )
{
	return CListBox::SetItemData( iListIndex, dwValue );
}

HRESULT CListBoxEx::SetCurSel( LPCTSTR pCategory, int iItemIndex )
{
	ListBoxInfo*   pCatInfo;

	if (!pCategory)
		return E_POINTER;

	pCatInfo = GetNodeInfo( pCategory );
	if (!pCatInfo)
		return E_INVALIDARG;

	if ((iItemIndex < 0) || (iItemIndex >= pCatInfo->lstItems.size()))
		return E_INVALIDARG;

	if (!pCatInfo->bIsOpen)
		SetNodeState( pCategory, true );

	SetCurSel( pCatInfo->iListIndex + iItemIndex + 1 );
	return S_OK;
}

int CListBoxEx::SetCurSel( int iListIndex )
{
	return CListBox::SetCurSel( iListIndex );
}

//���ø��ڵ�״̬��bOpen=trueΪ�쿪��falseΪ����
HRESULT CListBoxEx::SetNodeState( LPCTSTR pCategory, bool bOpen )
{
	ListBoxInfo*			pCatInfo;
	ListBoxStlListIter		iter;
	CString                 sBuf;
	int                     iListIndex;

	pCatInfo = GetNodeInfo( pCategory );
	if (!pCatInfo)
		return E_INVALIDARG;

	if (pCatInfo->bIsOpen == bOpen)
		return S_OK;

	pCatInfo->bIsOpen = bOpen;
	iListIndex = pCatInfo->iListIndex;
	m_bDoDraw = false;  
	if (bOpen) 
	{
		for (iter = pCatInfo->lstItems.begin(); iter != pCatInfo->lstItems.end(); iter++)
		{
			iListIndex = (iListIndex >= (GetCount() - 1)) ? -1 : iListIndex + 1;
			iListIndex = InsertString( iListIndex, (*iter).sItem );
			SetItemData( iListIndex, (DWORD)pCatInfo );
		}
		UpdateNodeIndexes( pCatInfo->iListIndex, iListIndex - pCatInfo->iListIndex );
	}
	else 
	{
		iListIndex++;
		while ((ListBoxInfo*)GetItemData( iListIndex ) == pCatInfo)
			DeleteString( iListIndex );
		UpdateNodeIndexes( pCatInfo->iListIndex, 0 - pCatInfo->lstItems.size() );
	}
	m_bDoDraw = true;          
	Invalidate();
	return S_OK;
}

//�����ӽڵ�״̬
// "iState" = 0 checkboxδ����
// "iState" = 1 checkbox����
// "iState" = 2 û��checkbox
HRESULT CListBoxEx::SetItemState( LPCTSTR pCategory, int iItemIndex, int iState )
{
	ListBoxInfo*      pCatInfo;
	ListBoxStlListIter   iter;

	pCatInfo = GetNodeInfo( pCategory );
	if (!pCatInfo)
		return E_INVALIDARG;

	if ((iItemIndex < 0) || (iItemIndex >= pCatInfo->lstItems.size()))
		return E_INVALIDARG;

	for (iter = pCatInfo->lstItems.begin(); iter != pCatInfo->lstItems.end(); iter++) 
	{
		if (iItemIndex <= 0) 
		{
			(*iter).iState = iState;
			if (m_bShowStates)
				Invalidate();
			return S_OK;
		}
		iItemIndex--;
	}
	return E_FAIL;
}

bool CListBoxEx::ShowItemStates( bool bShow)
{
	bool  bValue = m_bShowStates;
	m_bShowStates = bShow;
	Invalidate();
	return bValue;
}

void CListBoxEx::UpdateNodeIndexes( int iStartAfter, int iOffset )
{
	ListBoxStlMapIter    iter;
	ListBoxInfo*      pCatInfo;

	if (!iOffset)
		return;

	for (iter = m_mapSTL.begin(); iter != m_mapSTL.end(); iter++) 
	{
		pCatInfo = (*iter).second;
		if (!pCatInfo)
			continue;
		if (pCatInfo->iListIndex <= iStartAfter)
			continue;
		pCatInfo->iListIndex += iOffset;
	}
}

//������ĸ߶�
void CListBoxEx::SetNodeItemHeight(int nHeight)
{
	m_nItemHeight=nHeight;
	for (int i=0;i<GetCount();i++)
	{
		if(IsParentNode(i))
			SetItemHeight(i,LIST_PNODE_HEIGHT);
		else SetItemHeight(i,m_nItemHeight);
	}
	Invalidate();
}

BOOL CListBoxEx::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if (!(dwStyle & LBS_OWNERDRAWVARIABLE)) 
		dwStyle |= LBS_OWNERDRAWFIXED;
	return CListBox::Create(dwStyle, rect, pParentWnd, nID);
}

void CListBoxEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight=m_nItemHeight;
}
void CListBoxEx::OnRButtonDown(UINT nFlags, CPoint point)
{
	HWND hParent = ::GetParent(m_hWnd);
	if (hParent != NULL)
	{
		ListBoxInfo*		 pCatInfo;
		CString              sCategory;
		CRect                rcValue;
		int                  iHeight;
		int                  iListIndex;

		//��ȡListBox�ĸ߶�
		GetWindowRect( rcValue );
		iHeight = rcValue.Height();

		for (iListIndex = GetTopIndex(); iListIndex < GetCount(); iListIndex++) 
		{
			pCatInfo = (ListBoxInfo*)GetItemData( iListIndex );
			if (!pCatInfo)
				continue;

			GetItemRect( iListIndex, rcValue );
			rcValue.top    += Y_MARGIN;
			rcValue.bottom -= Y_MARGIN + 1;
			rcValue.right   = rcValue.left + rcValue.Width()+15;

			if (rcValue.top >= iHeight)
				break;

			if (rcValue.PtInRect( point )) 
			{
				GetText( pCatInfo->iListIndex, sCategory );
				SetCurSel( iListIndex );
				if (iListIndex == pCatInfo->iListIndex) 
				{
					::PostMessage(hParent,LBN_RBLCLICK,0,1);
				}
				else if (m_bShowStates) 
				{
					int iItemIndex = (iListIndex - pCatInfo->iListIndex) - 1;
					int iState = GetItemState( (LPCTSTR)sCategory, iItemIndex );
					if (0 == iState)
						SetItemState( (LPCTSTR)sCategory, iItemIndex, 1 );
					else if (1 == iState)
						SetItemState( (LPCTSTR)sCategory, iItemIndex, 0 );
				}
				break;
			}
		}
		::PostMessage(hParent,LBN_RBLCLICK,0,0);
	}
	CListBox::OnRButtonDown(nFlags, point);
}

BOOL CListBoxEx::OnEraseBkgnd(CDC* pDC)
{
	return CListBox::OnEraseBkgnd(pDC);
}

void CListBoxEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	ZeroMemory(&m_SCROLLINFO,sizeof(m_SCROLLINFO));
	SCROLLINFO lpScrollInfo;
	GetScrollInfo(SB_VERT,&lpScrollInfo);
	CopyMemory(&m_SCROLLINFO,&lpScrollInfo,sizeof(lpScrollInfo));
	CListBox::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CListBoxEx::SetArrowImage( LPCTSTR lpszRight,LPCTSTR lpszDown )
{
	RenderEngine->RemoveImage(m_pImageRight);
	RenderEngine->RemoveImage(m_pImageDown);

	m_pImageRight = RenderEngine->GetImage(lpszRight);
	m_pImageDown = RenderEngine->GetImage(lpszDown);

	if (NULL == m_pImageDown || NULL == m_pImageRight)
		return FALSE;
	else
		return TRUE;
}

void CListBoxEx::OnDestroy()
{
	__super::OnDestroy();

	RenderEngine->RemoveImage(m_pImageRight);
	RenderEngine->RemoveImage(m_pImageDown);

	RemoveScorll();
}

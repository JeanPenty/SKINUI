#include "StdAfx.h"
#include "VirtualListBox.h"

#define LISTITEM_HEIGHT			20

CVirtualListBox::CVirtualListBox(void)
{
	m_ListBoxItemArray.RemoveAll();
	m_pTextureBack = NULL;
	m_rcActive.SetRect(2,2,2,2);
}

CVirtualListBox::~CVirtualListBox(void)
{
	ResetContent();
}

VOID CVirtualListBox::OnWindowMovie()
{

}

VOID CVirtualListBox::OnWindowCreate( CD3DDevice * pD3DDevice )
{
	
}

VOID CVirtualListBox::OnWindowDestory( CD3DDevice * pD3DDevice )
{
	ResetContent();
}

VOID CVirtualListBox::OnWindowPosition( CD3DDevice * pD3DDevice )
{

}

BOOL CVirtualListBox::OnEventMouse( UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos )
{
	return FALSE;
}

BOOL CVirtualListBox::OnEventKeyboard( UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	return FALSE;
}

VOID CVirtualListBox::OnEventDrawWindow( CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos )
{
	CRect rcClient;
	GetWindowRect(rcClient);

	pD3DDevice->DrawRect(rcClient,D3DCOLOR_XRGB(255,0,0));
	if ( Check_Image( m_pTextureBack) )
	{
		m_pTextureBack->DrawImage(pD3DDevice,nXOriginPos,nYOriginPos);
	}

	if ( m_ListBoxItemArray.GetSize() > 0 )
	{
		CRect rcItem(0,0,0,0);

		rcItem.left = nXOriginPos;
		rcItem.right = rcItem.left + m_WindowSize.cx;

		for (INT_PTR i=0,j=0;i<m_ListBoxItemArray.GetSize();i++,j++)
		{
			tagListBoxItem* pItem = m_ListBoxItemArray.GetAt( i );
			
			rcItem.top = nYOriginPos+pItem->nItemHeight*j;
			rcItem.bottom = rcItem.top +pItem->nItemHeight;

			if ( rcItem.bottom > rcClient.bottom ) break;

			m_pDefaultFont->DrawText(pD3DDevice,pItem->strText,rcItem,DT_LEFT|DT_TOP,D3DCOLOR_XRGB(255,255,255));
		}
	}
}

int CVirtualListBox::AddString( LPCTSTR lpszItem )
{
	tagListBoxItem *pNewItem = new tagListBoxItem;

	if( !pNewItem )
		return -1;

	_sntprintf_s(pNewItem->strText,CountArray(pNewItem->strText),_TRUNCATE,lpszItem);
	pNewItem->pData = NULL;
	pNewItem->nItemHeight = LISTITEM_HEIGHT;
	pNewItem->bSelected = false;

	return m_ListBoxItemArray.Add( pNewItem );
}

void CVirtualListBox::ResetContent()
{
	for( int i = 0; i < m_ListBoxItemArray.GetSize(); ++i )
	{
		tagListBoxItem* pItem = m_ListBoxItemArray.GetAt( i );
		SafeDelete(pItem);
	}

	m_ListBoxItemArray.RemoveAll();
}

void CVirtualListBox::SetTexture( CD3DTexture *pBack )
{
	ASSERT( pBack != NULL );
	if ( pBack == NULL ) return;
	
	m_pTextureBack = pBack;
}

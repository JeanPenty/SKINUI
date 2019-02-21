#include "StdAfx.h"
#include "BuddyListBox.h"

BEGIN_MESSAGE_MAP(CBuddyListBox, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()

CBuddyItem::CBuddyItem(void)
{
	m_nID = 0;
	m_bOnline = FALSE;
	m_bOnlineAnim = FALSE;
	m_nOnlineAnimState = 0;
	m_bOfflineAnim = FALSE;
	m_bHeadFlashAnim = FALSE;
	m_nHeadFlashAnimState = 0;
	m_lpHeadImg = NULL;
	m_bGender = FALSE;
}

CBuddyItem::~CBuddyItem(void)
{
	if (m_lpHeadImg != NULL)
	{
		delete m_lpHeadImg;
		m_lpHeadImg = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
CBuddyRootItem::CBuddyRootItem(void)
{
	m_nID = 0;
	m_nCurCnt = -1;
	m_nMaxCnt = 0;
	m_bExpand = FALSE;
	m_nHeadFlashAnim = 0;
	m_nHeadFlashAnimState = 0;
}

CBuddyRootItem::~CBuddyRootItem(void)
{
	for (int i = 0; i < (int)m_arrBuddys.size(); i++)
	{
		CBuddyItem * lpItem = m_arrBuddys[i];
		if (lpItem != NULL)
			delete lpItem;
	}
	m_arrBuddys.clear();
}

//////////////////////////////////////////////////////////////////////////

CBuddyListBox::CBuddyListBox(void)
{
	m_colBack = RGB(255,255,255);
	m_nCurrentPos = 0;
	m_lpBgImg = NULL;
	m_lpBuddyTeamBgImgH = NULL;
	m_lpArrowImgN = NULL;
	m_lpArrowImgH = NULL;
	m_lpArrowImgS = NULL;
	m_lpExpArrowImgN = NULL;
	m_lpExpArrowImgH = NULL;
	m_lpExpArrowImgS = NULL;
	m_lpBuddyItemBgImgH = NULL;
	m_lpBuddyItemBgImgS = NULL;
	m_lpHeadFrameImg = NULL;
	m_lpStdGGHeadImg = NULL;
	m_lpStdMMHeadImg = NULL;

	m_nSelTeamIndex = m_nSelIndex = -1;
	m_nHoverTeamIndex = m_nHoverIndex = -1;
	m_nHoverSmallIconIndex = -1;
	m_nPressTeamIndex = m_nPressIndex = -1;
	m_nLeft = m_nTop = 0;
	m_bMouseTracking = FALSE;
	m_nStyle = BLC_BIG_ICON_STYLE;
	m_bShowBigIconInSel = TRUE;
	m_nBuddyTeamHeight = 0;
	m_nBuddyItemHeightInBig = 0;
	m_nBuddyItemHeightInSmall = 0;
	m_nBuddyItemHeightInStd = 0;
	m_nBuddyTeamPadding = 0;
	m_nBuddyItemPadding = 0;
	m_rcMargin = CRect(0,0,0,0);
	m_dwOnlineAnimTimerId = NULL;
	m_dwOfflineAnimTimerId = NULL;
	m_dwHeadFlashAnimTimerId = NULL;
}

CBuddyListBox::~CBuddyListBox(void)
{
}

BOOL CBuddyListBox::SetBgPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpBgImg);
	m_lpBgImg = RenderEngine->GetImage(lpszFileName);
	return (m_lpBgImg != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetBuddyTeamHotBgPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpBuddyTeamBgImgH);
	m_lpBuddyTeamBgImgH = RenderEngine->GetImage(lpszFileName);
	return (m_lpBuddyTeamBgImgH != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetBuddyItemHotBgPic(LPCTSTR lpszFileName, RECT * lpNinePart/* = NULL*/)
{
	RenderEngine->RemoveImage(m_lpBuddyItemBgImgH);
	m_lpBuddyItemBgImgH = RenderEngine->GetImage(lpszFileName);
	if (m_lpBuddyItemBgImgH != NULL)
		m_lpBuddyItemBgImgH->SetNinePart(lpNinePart);
	return (m_lpBuddyItemBgImgH != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetBuddyItemSelBgPic(LPCTSTR lpszFileName, RECT * lpNinePart/* = NULL*/)
{
	RenderEngine->RemoveImage(m_lpBuddyItemBgImgS);
	m_lpBuddyItemBgImgS = RenderEngine->GetImage(lpszFileName);
	if (m_lpBuddyItemBgImgS != NULL)
		m_lpBuddyItemBgImgS->SetNinePart(lpNinePart);
	return (m_lpBuddyItemBgImgS != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetHeadFramePic(LPCTSTR lpszFileName, RECT * lpNinePart/* = NULL*/)
{
	RenderEngine->RemoveImage(m_lpHeadFrameImg);
	m_lpHeadFrameImg = RenderEngine->GetImage(lpszFileName);
	if (m_lpHeadFrameImg != NULL)
		m_lpHeadFrameImg->SetNinePart(lpNinePart);
	return (m_lpHeadFrameImg != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetNormalArrowPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpArrowImgN);
	m_lpArrowImgN = RenderEngine->GetImage(lpszFileName);
	return (m_lpArrowImgN != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetHotArrowPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpArrowImgH);
	m_lpArrowImgH = RenderEngine->GetImage(lpszFileName);
	return (m_lpArrowImgH != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetSelArrowPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpArrowImgS);
	m_lpArrowImgS = RenderEngine->GetImage(lpszFileName);
	return (m_lpArrowImgS != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetNormalExpArrowPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpExpArrowImgN);
	m_lpExpArrowImgN = RenderEngine->GetImage(lpszFileName);
	return (m_lpExpArrowImgN != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetHotExpArrowPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpExpArrowImgH);
	m_lpExpArrowImgH = RenderEngine->GetImage(lpszFileName);
	return (m_lpExpArrowImgH != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetSelExpArrowPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpExpArrowImgS);
	m_lpExpArrowImgS = RenderEngine->GetImage(lpszFileName);
	return (m_lpExpArrowImgS != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetStdGGHeadPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpStdGGHeadImg);
	m_lpStdGGHeadImg = RenderEngine->GetImage(lpszFileName);
	return (m_lpStdGGHeadImg != NULL) ? TRUE : FALSE;
}

BOOL CBuddyListBox::SetStdMMHeadPic(LPCTSTR lpszFileName)
{
	RenderEngine->RemoveImage(m_lpStdMMHeadImg);
	m_lpStdMMHeadImg = RenderEngine->GetImage(lpszFileName);
	return (m_lpStdMMHeadImg != NULL) ? TRUE : FALSE;
}

void CBuddyListBox::SetStyle(BLCTRL_STYLE nStyle)
{
	m_nStyle = nStyle;
}

void CBuddyListBox::SetShowBigIconInSel(BOOL bShowBigIconInSel)
{
	m_bShowBigIconInSel = bShowBigIconInSel;
}

void CBuddyListBox::SetBuddyTeamHeight(int nHeight)
{
	m_nBuddyTeamHeight = nHeight;
}

void CBuddyListBox::SetBuddyItemHeightInBigIcon(int nHeight)
{
	m_nBuddyItemHeightInBig = nHeight;
}

void CBuddyListBox::SetBuddyItemHeightInSmallIcon(int nHeight)
{
	m_nBuddyItemHeightInSmall = nHeight;
}

void CBuddyListBox::SetBuddyItemHeightInStandardIcon(int nHeight)
{
	m_nBuddyItemHeightInStd = nHeight;
}

void CBuddyListBox::SetBuddyTeamPadding(int nPadding)
{
	m_nBuddyTeamPadding = nPadding;
}

void CBuddyListBox::SetBuddyItemPadding(int nPadding)
{
	m_nBuddyItemPadding = nPadding;
}

void CBuddyListBox::SetMargin(const RECT * lpMargin)
{
	if (lpMargin != NULL)
		m_rcMargin = *lpMargin;
}

int CBuddyListBox::AddBuddyTeam(int nID)
{
	CBuddyRootItem * lpItem = new CBuddyRootItem;
	if (NULL == lpItem)
		return -1;
	lpItem->m_nID = nID;
	m_arrBuddyTeamItems.push_back(lpItem);
	return m_arrBuddyTeamItems.size() - 1;
}

int CBuddyListBox::InsertBuddyTeam(int nTeamIndex, int nID)
{
	return -1;
}

BOOL CBuddyListBox::DelBuddyTeam(int nTeamIndex)
{
	if (nTeamIndex >= 0 && nTeamIndex < (int)m_arrBuddyTeamItems.size())
	{
		CBuddyRootItem * lpBuddyTeamItem = m_arrBuddyTeamItems[nTeamIndex];
		if (lpBuddyTeamItem != NULL)
			delete lpBuddyTeamItem;
		m_arrBuddyTeamItems.erase(m_arrBuddyTeamItems.begin()+nTeamIndex);
		return TRUE;
	}
	return FALSE;
}

int CBuddyListBox::AddBuddyItem(int nTeamIndex, int nID)
{
	CBuddyRootItem * lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
	if (NULL == lpTeamItem)
		return -1;
	CBuddyItem * lpItem = new CBuddyItem;
	if (NULL == lpItem)
		return -1;
	lpItem->m_nID = nID;
	lpTeamItem->m_arrBuddys.push_back(lpItem);
	return lpTeamItem->m_arrBuddys.size() - 1;
}

int CBuddyListBox::InsertBuddyItem(int nTeamIndex, int nIndex, int nID)
{
	return -1;
}

BOOL CBuddyListBox::DelBuddyItem(int nTeamIndex, int nIndex)
{
	if (nTeamIndex >= 0 && nTeamIndex < (int)m_arrBuddyTeamItems.size())
	{
		CBuddyRootItem * lpTeamItem = m_arrBuddyTeamItems[nTeamIndex];
		if (lpTeamItem != NULL)
		{
			if (nIndex >= 0 && nIndex < (int)lpTeamItem->m_arrBuddys.size())
			{
				CBuddyItem * lpBuddyItem = lpTeamItem->m_arrBuddys[nIndex];
				if (lpBuddyItem != NULL)
					delete lpBuddyItem;
				lpTeamItem->m_arrBuddys.erase(lpTeamItem->m_arrBuddys.begin()+nIndex);
				return TRUE;
			}
		}
	}
	return FALSE;
}

void CBuddyListBox::DelAllItems()
{
	for (int i = 0; i < (int)m_arrBuddyTeamItems.size(); i++)
	{
		CBuddyRootItem * lpTeamItem = m_arrBuddyTeamItems[i];
		if (lpTeamItem != NULL)
			delete lpTeamItem;
	}
	m_arrBuddyTeamItems.clear();
}

void CBuddyListBox::SetBuddyTeamID(int nTeamIndex, int nID)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		lpItem->m_nID = nID;
}

void CBuddyListBox::SetBuddyTeamName(int nTeamIndex, LPCTSTR lpszText)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		lpItem->m_strName = lpszText;
}

void CBuddyListBox::SetBuddyTeamMaxCnt(int nTeamIndex, int nMaxCnt)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		lpItem->m_nMaxCnt = nMaxCnt;
}

void CBuddyListBox::SetBuddyTeamCurCnt(int nTeamIndex, int nCurCnt)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		lpItem->m_nCurCnt = nCurCnt;
}

void CBuddyListBox::SetBuddyTeamExpand(int nTeamIndex, BOOL bExpand)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		lpItem->m_bExpand = bExpand;
}

int CBuddyListBox::GetBuddyTeamID(int nTeamIndex)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		return lpItem->m_nID;
	else
		return 0;
}

CString CBuddyListBox::GetBuddyTeamName(int nTeamIndex)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		return lpItem->m_strName;
	else
		return _T("");
}

int CBuddyListBox::GetBuddyTeamMaxCnt(int nTeamIndex)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		return lpItem->m_nMaxCnt;
	else
		return 0;
}

int CBuddyListBox::GetBuddyTeamCurCnt(int nTeamIndex)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		return lpItem->m_nCurCnt;
	else
		return 0;
}

BOOL CBuddyListBox::IsBuddyTeamExpand(int nTeamIndex)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpItem != NULL)
		return lpItem->m_bExpand;
	else
		return FALSE;
}

void CBuddyListBox::SetBuddyItemID(int nTeamIndex, int nIndex, int nID)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		lpItem->m_nID = nID;
}

void CBuddyListBox::SetBuddyItemQQNum(int nTeamIndex, int nIndex, LPCTSTR lpszText)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		lpItem->m_strQQNum = lpszText;
}

void CBuddyListBox::SetBuddyItemNickName(int nTeamIndex, int nIndex, LPCTSTR lpszText)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		lpItem->m_strNickName = lpszText;
}

void CBuddyListBox::SetBuddyItemMarkName(int nTeamIndex, int nIndex, LPCTSTR lpszText)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		lpItem->m_strMarkName = lpszText;
}

void CBuddyListBox::SetBuddyItemSign(int nTeamIndex, int nIndex, LPCTSTR lpszText)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		lpItem->m_strSign = lpszText;
}

void CBuddyListBox::SetBuddyItemGender(int nTeamIndex, int nIndex, BOOL bGender)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		lpItem->m_bGender = bGender;
}

BOOL CBuddyListBox::SetBuddyItemHeadPic(int nTeamIndex, int nIndex, LPCTSTR lpszFileName, BOOL bGray)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (NULL == lpItem)
		return FALSE;

	if (lpItem->m_lpHeadImg != NULL)
		delete lpItem->m_lpHeadImg;

	lpItem->m_lpHeadImg = new CImageEx;
	if (NULL == lpItem->m_lpHeadImg)
		return FALSE;

	BOOL bRet = lpItem->m_lpHeadImg->LoadImage(lpszFileName);
	if (!bRet)
	{
		delete lpItem->m_lpHeadImg;
		lpItem->m_lpHeadImg = NULL;
		return FALSE;
	}

	if (bGray)
		lpItem->m_lpHeadImg->SetGray();

	if (IsWindowVisible())
		Invalidate(FALSE);

	return TRUE;
}

void CBuddyListBox::SetBuddyItemHeadFlashAnim(int nTeamIndex, int nIndex, BOOL bHeadFlashAnim)
{
	CBuddyItem * lpBuddyItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (NULL == lpBuddyItem || bHeadFlashAnim == lpBuddyItem->m_bHeadFlashAnim)
		return;

	lpBuddyItem->m_bHeadFlashAnim = bHeadFlashAnim;
	lpBuddyItem->m_nHeadFlashAnimState = 0;
	if (bHeadFlashAnim)
	{
		CBuddyRootItem * lpBuddyTeam = GetBuddyTeamByIndex(nTeamIndex);
		if (lpBuddyTeam != NULL)
		{
			lpBuddyTeam->m_nHeadFlashAnim++;
		}

		if (NULL == m_dwHeadFlashAnimTimerId)	// 启动头像闪动动画计时器
			m_dwHeadFlashAnimTimerId = SetTimer(2, 250, NULL);
	}
	else
	{
		CBuddyRootItem * lpBuddyTeam = GetBuddyTeamByIndex(nTeamIndex);
		if (lpBuddyTeam != NULL)
		{
			lpBuddyTeam->m_nHeadFlashAnim--;
			if (lpBuddyTeam->m_nHeadFlashAnim <= 0)
				lpBuddyTeam->m_nHeadFlashAnimState = 0;
		}

		BOOL bHasAnim = FALSE;

		int nTeamCnt = GetBuddyTeamCount();
		for (int i = 0; i < nTeamCnt; i++)
		{
			lpBuddyTeam = GetBuddyTeamByIndex(i);
			if (lpBuddyTeam != NULL && lpBuddyTeam->m_nHeadFlashAnim > 0)
			{
				bHasAnim = TRUE;
				break;
			}
		}

		if (!bHasAnim)
		{
			KillTimer(m_dwHeadFlashAnimTimerId);
			m_dwHeadFlashAnimTimerId = NULL;

			if (IsWindowVisible())
				Invalidate(FALSE);
		}
	}
}

void CBuddyListBox::SetBuddyItemOnline(int nTeamIndex, int nIndex, BOOL bOnline, BOOL bAnim)
{
	CBuddyItem * lpBuddyItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (NULL == lpBuddyItem || bOnline == lpBuddyItem->m_bOnline)
		return;

	lpBuddyItem->m_bOnline = bOnline;
	if (bAnim)	// 显示动画
	{
		if (bOnline)	// 上线动画
		{
			lpBuddyItem->m_bOfflineAnim = FALSE;

			lpBuddyItem->m_bOnlineAnim = TRUE;
			lpBuddyItem->m_nOnlineAnimState = 0;

			if (NULL == m_dwOnlineAnimTimerId)	// 启动上线动画计时器
				m_dwOnlineAnimTimerId = SetTimer(3, 250, NULL);
		}
		else			// 下线动画
		{
			lpBuddyItem->m_bOnlineAnim = FALSE;
			lpBuddyItem->m_nOnlineAnimState = 0;

			lpBuddyItem->m_bOfflineAnim = TRUE;

			if (NULL == m_dwOfflineAnimTimerId)	// 启动下线动画计时器
				m_dwOfflineAnimTimerId = SetTimer(4, 1000, NULL);
		}
	}
}

int CBuddyListBox::GetBuddyItemID(int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		return lpItem->m_nID;
	else
		return 0;
}

CString CBuddyListBox::GetBuddyItemQQNum(int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		return lpItem->m_strQQNum;
	else
		return _T("");
}

CString CBuddyListBox::GetBuddyItemNickName(int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		return lpItem->m_strNickName;
	else
		return _T("");
}

CString CBuddyListBox::GetBuddyItemMarkName(int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		return lpItem->m_strMarkName;
	else
		return _T("");
}

CString CBuddyListBox::GetBuddyItemSign(int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		return lpItem->m_strSign;
	else
		return _T("");
}

BOOL CBuddyListBox::GetBuddyItemGender(int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		return lpItem->m_bGender;
	else
		return FALSE;
}

BOOL CBuddyListBox::IsBuddyItemHasMsg(int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (lpItem != NULL)
		return lpItem->m_bHeadFlashAnim;
	else
		return FALSE;
}

int CBuddyListBox::GetBuddyTeamCount()
{
	return m_arrBuddyTeamItems.size();
}

int CBuddyListBox::GetBuddyItemCount(int nTeamIndex)
{
	CBuddyRootItem * lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
	if (lpTeamItem != NULL)
		return lpTeamItem->m_arrBuddys.size();
	else
		return 0;
}

BOOL CBuddyListBox::GetItemIndexByID(int nID, int& nTeamIndex, int& nIndex)
{
	nTeamIndex = -1;
	nIndex = -1;

	for (int i = 0; i < (int)m_arrBuddyTeamItems.size(); i++)
	{
		CBuddyRootItem * lpTeamItem = m_arrBuddyTeamItems[i];
		if (lpTeamItem != NULL)
		{
			if (nID == lpTeamItem->m_nID)
			{
				nTeamIndex = i;
				return TRUE;
			}

			for (int j = 0; j < (int)lpTeamItem->m_arrBuddys.size(); j++)
			{
				CBuddyItem * lpItem = lpTeamItem->m_arrBuddys[j];
				if (lpItem != NULL && nID == lpItem->m_nID)
				{
					if (nID == lpItem->m_nID)
					{
						nTeamIndex = i;
						nIndex = j;
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CBuddyListBox::GetItemRectByIndex(int nTeamIndex, int nIndex, CRect& rect)
{
	CBuddyRootItem * lpTeamItem;
	CBuddyItem * lpItem;
	int nLeft = m_rcMargin.left+m_nLeft, nTop = m_nTop;
	int nBuddyTeamWidth, nBuddyItemWidth, nBuddyItemHeight;

	CRect rcClient;
	GetClientRect(&rcClient);

	int nVScrollBarWidth = 0;
	if (m_VScrollBar.IsVisible())
	{
		CRect rcVScrollBar;
		m_VScrollBar.GetRect(&rcVScrollBar);
		nVScrollBarWidth = rcVScrollBar.Width();
	}

	nBuddyTeamWidth = rcClient.Width() - m_rcMargin.left - m_rcMargin.right - nVScrollBarWidth;
	nBuddyItemWidth = nBuddyTeamWidth;
	if (BLC_BIG_ICON_STYLE == m_nStyle)
		nBuddyItemHeight = m_nBuddyItemHeightInBig;
	else if (BLC_SMALL_ICON_STYLE == m_nStyle)
		nBuddyItemHeight = m_nBuddyItemHeightInSmall;
	else
		nBuddyItemHeight = m_nBuddyItemHeightInStd;

	for (int i = 0; i < (int)m_arrBuddyTeamItems.size(); i++)
	{
		lpTeamItem = m_arrBuddyTeamItems[i];
		if (lpTeamItem != NULL)
		{
			if (-1 == nIndex && i == nTeamIndex)
			{
				rect = CRect(nLeft, nTop, nLeft+nBuddyTeamWidth, nTop+m_nBuddyTeamHeight);
				return TRUE;
			}

			nTop += m_nBuddyTeamHeight;
			nTop += m_nBuddyTeamPadding;

			if (lpTeamItem->m_bExpand)
			{
				for (int j = 0; j < (int)lpTeamItem->m_arrBuddys.size(); j++)
				{
					lpItem = lpTeamItem->m_arrBuddys[j];
					if (lpItem != NULL)
					{
						if (BLC_SMALL_ICON_STYLE == m_nStyle && m_bShowBigIconInSel
							&& (m_nSelTeamIndex == i && m_nSelIndex == j))
							nBuddyItemHeight = m_nBuddyItemHeightInBig;

						if (i == nTeamIndex && j == nIndex)
						{
							rect = CRect(nLeft, nTop, nLeft+nBuddyItemWidth, nTop+nBuddyItemHeight);
							return TRUE;
						}
						nTop += nBuddyItemHeight;
						nTop += m_nBuddyItemPadding;

						if (BLC_SMALL_ICON_STYLE == m_nStyle && m_bShowBigIconInSel
							&& (m_nSelTeamIndex == i && m_nSelIndex == j))
							nBuddyItemHeight = m_nBuddyItemHeightInSmall;
					}
				}
			}
		}
	}

	return FALSE;
}

void CBuddyListBox::GetCurSelIndex(int& nTeamIndex, int& nIndex)
{
	nTeamIndex = m_nSelTeamIndex;
	nIndex = m_nSelIndex;
}

BLCTRL_STYLE CBuddyListBox::GetStyle()
{
	return m_nStyle;
}

BOOL CBuddyListBox::IsShowBigIconInSel()
{
	return m_bShowBigIconInSel;
}

int CBuddyListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CWnd::OnCreate(lpCreateStruct);

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rc = CRect(rcClient.Width()-8, 0, rcClient.Width(), rcClient.Height());
	m_VScrollBar.Create(m_hWnd, 1, &rc, 1, FALSE, FALSE);

	m_VScrollBar.SetBgNormalPic(_T("QQ\\ScrollBar\\scrollbar_bkg.png"));
	m_VScrollBar.SetBgHotPic(_T("QQ\\ScrollBar\\scrollbar_bkg.png"));
	m_VScrollBar.SetBgPushedPic(_T("QQ\\ScrollBar\\scrollbar_bkg.png"));
	m_VScrollBar.SetBgDisabledPic(_T("QQ\\ScrollBar\\scrollbar_bkg.png"));

	m_VScrollBar.SetShowLeftUpBtn(TRUE);
	m_VScrollBar.SetLeftUpBtnNormalPic(_T("QQ\\ScrollBar\\scrollbar_arrowup_normal.png"));
	m_VScrollBar.SetLeftUpBtnHotPic(_T("QQ\\ScrollBar\\scrollbar_arrowup_highlight.png"));
	m_VScrollBar.SetLeftUpBtnPushedPic(_T("QQ\\ScrollBar\\scrollbar_arrowup_down.png"));
	m_VScrollBar.SetLeftUpBtnDisabledPic(_T("QQ\\ScrollBar\\scrollbar_arrowup_normal.png"));

	m_VScrollBar.SetShowRightDownBtn(TRUE);
	m_VScrollBar.SetRightDownBtnNormalPic(_T("QQ\\ScrollBar\\scrollbar_arrowdown_normal.png"));
	m_VScrollBar.SetRightDownBtnHotPic(_T("QQ\\ScrollBar\\scrollbar_arrowdown_highlight.png"));
	m_VScrollBar.SetRightDownBtnPushedPic(_T("QQ\\ScrollBar\\scrollbar_arrowdown_down.png"));
	m_VScrollBar.SetRightDownBtnDisabledPic(_T("QQ\\ScrollBar\\scrollbar_arrowdown_normal.png"));

	m_VScrollBar.SetThumbNormalPic(_T("QQ\\ScrollBar\\scrollbar_bar_normal.png"), CRect(4,4,4,4));
	m_VScrollBar.SetThumbHotPic(_T("QQ\\ScrollBar\\scrollbar_bar_highlight.png"), CRect(4,4,4,4));
	m_VScrollBar.SetThumbPushedPic(_T("QQ\\ScrollBar\\scrollbar_bar_down.png"), CRect(4,4,4,4));
	m_VScrollBar.SetThumbDisabledPic(_T("QQ\\ScrollBar\\scrollbar_bar_normal.png"), CRect(4,4,4,4));
	
	return 0;
}

BOOL CBuddyListBox::OnEraseBkgnd(CDC*pDC)
{
	return TRUE;
}

void CBuddyListBox::OnPaint()
{
	CPaintDC dc(this);

	CRect rcClient;
	GetClientRect(&rcClient);

	CMemoryDC BufferDC(&dc, rcClient);

	CheckScrollBarStatus();
	BufferDC.FillSolidRect(rcClient,m_colBack);
	DrawParentWndBg(GetSafeHwnd(),BufferDC.m_hDC);

	if (m_lpBgImg != NULL && !m_lpBgImg->IsNull())
		m_lpBgImg->Draw(&BufferDC, rcClient);

	CBuddyRootItem * lpTeamItem;
	for (int i = 0; i < (int)m_arrBuddyTeamItems.size(); i++)
	{
		DrawBuddyTeam(&BufferDC, i);

		lpTeamItem = m_arrBuddyTeamItems[i];
		if (lpTeamItem != NULL && lpTeamItem->m_bExpand)
		{
			for (int j = 0; j < (int)lpTeamItem->m_arrBuddys.size(); j++)
			{
				DrawBuddyItem(&BufferDC, i, j);
			}
		}
	}

	m_VScrollBar.OnPaint(&BufferDC);
}

void CBuddyListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	SetFocus();

	int nTeamIndex = -1, nIndex = -1;
	HitTest(point, nTeamIndex, nIndex);

	m_nSelTeamIndex = nTeamIndex;
	m_nSelIndex = nIndex;

	Invalidate(FALSE);

	NMHDR stNmhdr = {m_hWnd, GetDlgCtrlID(), NM_DBLCLK};
	::SendMessage(::GetParent(m_hWnd), WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&stNmhdr);
}

void CBuddyListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

	int nTeamIndex = -1, nIndex = -1;
	HitTest(point, nTeamIndex, nIndex);

	m_nPressTeamIndex = nTeamIndex;
	m_nPressIndex = nIndex;

	m_VScrollBar.OnLButtonDown(nFlags, point);

	CWnd::OnLButtonDown(nFlags, point);
}

void CBuddyListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	int nTeamIndex = -1, nIndex = -1;
	HitTest(point, nTeamIndex, nIndex);

	if (nTeamIndex != -1 && nTeamIndex == m_nPressTeamIndex
		&& nIndex == m_nPressIndex)
	{
		m_nSelTeamIndex = nTeamIndex;
		m_nSelIndex = nIndex;
		if (-1 == nIndex)		// 点击的是好友分组项
		{
			BOOL bExpand = IsBuddyTeamExpand(nTeamIndex);
			SetBuddyTeamExpand(nTeamIndex, !bExpand);
		}
		
		EnsureVisible(m_nSelTeamIndex, m_nSelIndex);
		Invalidate(FALSE);
	}

	m_nPressTeamIndex = -1;
	m_nPressIndex = -1;

	m_VScrollBar.OnLButtonUp(nFlags, point);

	CWnd::OnLButtonUp(nFlags, point);
}

void CBuddyListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_nPressTeamIndex != -1)
		return;

	if (!m_bMouseTracking)
	{
		TrackMouseLeave(GetSafeHwnd());
		m_bMouseTracking = TRUE;
	}

	int nTeamIndex = -1, nIndex = -1;
	HitTest(point, nTeamIndex, nIndex);

	if (nTeamIndex != m_nHoverTeamIndex || nIndex != m_nHoverIndex)
	{
		m_nHoverTeamIndex = nTeamIndex;
		m_nHoverIndex = nIndex;
		Invalidate(FALSE);
	}

	m_VScrollBar.OnMouseMove(nFlags, point);

	CWnd::OnMouseMove(nFlags, point);
}

void CBuddyListBox::OnMouseLeave()
{
	m_bMouseTracking = FALSE;
	if (-1 != m_nHoverTeamIndex || -1 != m_nHoverIndex)
	{
		m_nHoverTeamIndex = -1;
		m_nHoverIndex = -1;
		Invalidate(FALSE);
	}

	m_VScrollBar.OnMouseLeave();

	CWnd::OnMouseLeave();
}

void CBuddyListBox::OnTimer(UINT_PTR nIDEvent)
{
	m_VScrollBar.OnTimer(nIDEvent);

	if (nIDEvent == m_dwHeadFlashAnimTimerId)		// 头像闪动动画
	{
		OnTimer_HeadFlashAnim(nIDEvent);
	}
	else if (nIDEvent == m_dwOnlineAnimTimerId)		// 上线动画
	{
		OnTimer_OnlineAnim(nIDEvent);
	}
	else if (nIDEvent == m_dwOfflineAnimTimerId)	// 下线动画
	{
		OnTimer_OfflineAnim(nIDEvent);
	}

	CWnd::OnTimer(nIDEvent);
}

BOOL CBuddyListBox::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nLineSize = 100;

	if (zDelta < 0)		// SB_LINEDOWN
		Scroll(0, nLineSize);
	else	// SB_LINEUP
		Scroll(0, -nLineSize);

	Invalidate(FALSE);

	return TRUE;
}

void CBuddyListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (GetBuddyTeamCount() <= 0)
		return;

	switch (nChar)
	{
	case VK_UP:	// 向上光标键
		{
			if (-1 == m_nSelIndex)
			{
				if (0 == m_nSelTeamIndex)
					return;

				m_nSelTeamIndex--;
				m_nSelIndex = -1;

				if (IsBuddyTeamExpand(m_nSelTeamIndex))
				{
					int nItemCnt = GetBuddyItemCount(m_nSelTeamIndex);
					if (nItemCnt > 0)
						m_nSelIndex = nItemCnt - 1;
				}
			}
			else
			{
				if (0 == m_nSelIndex)
					m_nSelIndex = -1;
				else
					m_nSelIndex--;
			}
		}
		break;

	case VK_DOWN:	// 向下光标键
		{
			if (-1 == m_nSelIndex)
			{
				if (IsBuddyTeamExpand(m_nSelTeamIndex) &&
					GetBuddyItemCount(m_nSelTeamIndex) > 0)
				{
					m_nSelIndex = 0;
				}
				else
				{
					if ((GetBuddyTeamCount() - 1) == m_nSelTeamIndex)
						return;

					m_nSelTeamIndex++;
					m_nSelIndex = -1;
				}
			}
			else
			{
				if (GetBuddyItemCount(m_nSelTeamIndex) - 1 == m_nSelIndex)
				{
					if (GetBuddyTeamCount() - 1 == m_nSelTeamIndex)
						return;

					m_nSelTeamIndex++;
					m_nSelIndex = -1;
				}
				else
					m_nSelIndex += 1;
			}
		}
		break;

	case VK_LEFT:	// 向左光标键
		{
			if (-1 == m_nSelIndex)	// 
			{
				if (IsBuddyTeamExpand(m_nSelTeamIndex))
					SetBuddyTeamExpand(m_nSelTeamIndex, FALSE);
			}
			else
				m_nSelIndex = -1;
		}
		break;

	case VK_RIGHT:	// 向右光标键
		{
			if (-1 == m_nSelIndex)
			{
				if (!IsBuddyTeamExpand(m_nSelTeamIndex))
					SetBuddyTeamExpand(m_nSelTeamIndex, TRUE);
				else if (GetBuddyItemCount(m_nSelTeamIndex) > 0)
					m_nSelIndex = 0;
			}
		}
		break;

	case VK_PRIOR:	// PgUp键
		{
			CRect rcClient;
			GetClientRect(&rcClient);
			Scroll(0, -rcClient.Height());
			Invalidate(FALSE);
		}
		return;

	case VK_NEXT:	// PgDn键
		{
			CRect rcClient;
			GetClientRect(&rcClient);
			Scroll(0, rcClient.Height());
			Invalidate(FALSE);
		}
		return;

	case VK_HOME:	// Home键
		{
			m_nSelTeamIndex = 0;
			m_nSelIndex = -1;
		}
		break;

	case VK_END:	// End键
		{
			int TeamCnt = GetBuddyTeamCount();

			m_nSelTeamIndex = TeamCnt - 1;
			m_nSelIndex = -1;
			if (IsBuddyTeamExpand(TeamCnt - 1) &&
				GetBuddyItemCount(TeamCnt - 1) > 0)
				m_nSelIndex = GetBuddyItemCount(TeamCnt - 1) - 1;
		}
		break;

	case VK_RETURN:	// 回车键
		{
			
		}
		return;

	default:
		return;
	}

	EnsureVisible(m_nSelTeamIndex, m_nSelIndex);
	Invalidate(FALSE);

	CWnd::OnKeyDown(nChar,nRepCnt,nFlags);
}

void CBuddyListBox::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rc = CRect(rcClient.Width()-8, 0, rcClient.Width(), rcClient.Height());
	m_VScrollBar.SetRect(&rc);
	Invalidate(FALSE);
}

void CBuddyListBox::OnDestroy()
{
	CWnd::OnDestroy();

	if (m_dwHeadFlashAnimTimerId != NULL)
	{
		KillTimer(m_dwHeadFlashAnimTimerId);
		m_dwHeadFlashAnimTimerId = NULL;
	}

	if (m_ToolTipCtrl.GetSafeHwnd())
		m_ToolTipCtrl.DestroyWindow();
	m_ToolTipCtrl.m_hWnd = NULL;

	m_VScrollBar.Destroy();

	RenderEngine->RemoveImage(m_lpBgImg);
	RenderEngine->RemoveImage(m_lpBuddyTeamBgImgH);
	RenderEngine->RemoveImage(m_lpArrowImgN);
	RenderEngine->RemoveImage(m_lpArrowImgH);
	RenderEngine->RemoveImage(m_lpArrowImgS);
	RenderEngine->RemoveImage(m_lpExpArrowImgN);
	RenderEngine->RemoveImage(m_lpExpArrowImgH);
	RenderEngine->RemoveImage(m_lpExpArrowImgS);
	RenderEngine->RemoveImage(m_lpBuddyItemBgImgH);
	RenderEngine->RemoveImage(m_lpBuddyItemBgImgS);
	RenderEngine->RemoveImage(m_lpHeadFrameImg);
	RenderEngine->RemoveImage(m_lpStdGGHeadImg);
	RenderEngine->RemoveImage(m_lpStdMMHeadImg);

	RemoveScorll();

	m_nSelTeamIndex = m_nSelIndex = -1;
	m_nHoverTeamIndex = m_nHoverIndex = -1;
	m_nHoverSmallIconIndex = -1;
	m_nPressTeamIndex = m_nPressIndex = -1;
	m_nLeft = m_nTop = 0;
	m_bMouseTracking = FALSE;
	m_nStyle = BLC_BIG_ICON_STYLE;
	m_bShowBigIconInSel = TRUE;
	m_nBuddyTeamHeight = 0;
	m_nBuddyItemHeightInBig = 0;
	m_nBuddyItemHeightInSmall = 0;
	m_nBuddyItemHeightInStd = 0;
	m_nBuddyTeamPadding = 0;
	m_nBuddyItemPadding = 0;
	m_rcMargin = CRect(0,0,0,0);

	for (int i = 0; i < (int)m_arrBuddyTeamItems.size(); i++)
	{
		CBuddyRootItem * lpTeamItem = m_arrBuddyTeamItems[i];
		if (lpTeamItem != NULL)
			delete lpTeamItem;
	}
	m_arrBuddyTeamItems.clear();
}


void CBuddyListBox::DrawBuddyTeam(CDC*pDC, int nIndex)
{
	CBuddyRootItem * lpItem = GetBuddyTeamByIndex(nIndex);
	if (NULL == lpItem)
		return;

	CRect rcItem;
	GetItemRectByIndex(nIndex, -1, rcItem);

	int nArrowWidth = 12, nArrowHeight = 12;
	if (m_lpArrowImgN != NULL && !m_lpArrowImgN->IsNull())
	{
		nArrowWidth = m_lpArrowImgN->GetWidth();
		nArrowHeight = m_lpArrowImgN->GetHeight();
	}

	CRect rcArrow;
	CalcCenterRect(rcItem, nArrowWidth, nArrowHeight, rcArrow);
	rcArrow.left = rcItem.left + 2;
	rcArrow.right = rcArrow.left + nArrowWidth;

	CRect rcText(rcItem);
	rcText.left = rcArrow.right + 6;

	if (m_nSelTeamIndex == nIndex && m_nSelIndex == -1)
	{
		if (!lpItem->m_bExpand)
		{
			if (m_lpArrowImgS != NULL && !m_lpArrowImgS->IsNull())
				m_lpArrowImgS->Draw(pDC, rcArrow);
		}
		else
		{
			if (m_lpExpArrowImgS != NULL && !m_lpExpArrowImgS->IsNull())
				m_lpExpArrowImgS->Draw(pDC, rcArrow);
		}
	}
	else if (m_nHoverTeamIndex == nIndex && m_nHoverIndex == -1)
	{
		if (m_lpBuddyTeamBgImgH != NULL && !m_lpBuddyTeamBgImgH->IsNull())
			m_lpBuddyTeamBgImgH->Draw(pDC, rcItem);

		if (!lpItem->m_bExpand)
		{
			if (m_lpArrowImgH != NULL && !m_lpArrowImgH->IsNull())
				m_lpArrowImgH->Draw(pDC, rcArrow);
		}
		else
		{
			if (m_lpExpArrowImgH != NULL && !m_lpExpArrowImgH->IsNull())
				m_lpExpArrowImgH->Draw(pDC, rcArrow);
		}
	}
	else
	{
		if (!lpItem->m_bExpand)
		{
			if (m_lpArrowImgN != NULL && !m_lpArrowImgN->IsNull())
				m_lpArrowImgN->Draw(pDC, rcArrow);
		}
		else
		{
			if (m_lpExpArrowImgN != NULL && !m_lpExpArrowImgN->IsNull())
				m_lpExpArrowImgN->Draw(pDC, rcArrow);
		}
	}

	BOOL bShowText = TRUE;
	if (!lpItem->m_bExpand && lpItem->m_nHeadFlashAnim > 0)
	{
		if (1 == lpItem->m_nHeadFlashAnimState)
			bShowText = FALSE;
	}

	if (bShowText)
	{
		CString strText;
		if (lpItem->m_nCurCnt != -1)
			strText.Format(_T("%s [%d/%d]"), lpItem->m_strName, lpItem->m_nCurCnt, lpItem->m_nMaxCnt);
		else
			strText.Format(_T("%s [%d]"), lpItem->m_strName, lpItem->m_nMaxCnt);

		UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

		pDC->SetTextColor(RGB(0, 0, 0));
		int nMode = pDC->SetBkMode(TRANSPARENT);
		HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
		if (NULL == hFont)
			hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		HFONT hOldFont = (HFONT)pDC->SelectObject(hFont);
		pDC->DrawText(strText, &rcText, nFormat);
		pDC->SelectObject(hOldFont);
		pDC->SetBkMode(nMode);
	}
}

void CBuddyListBox::DrawBuddyItem(CDC*pDC, int nTeamIndex, int nIndex)
{
	int nMode = pDC->SetStretchBltMode(HALFTONE);
	if (BLC_BIG_ICON_STYLE == m_nStyle)
		DrawBuddyItemInBigIcon(pDC, nTeamIndex, nIndex);
	else if (BLC_SMALL_ICON_STYLE == m_nStyle)
		DrawBuddyItemInSmallIcon(pDC, nTeamIndex, nIndex);
	else if (BLC_STANDARD_ICON_STYLE == m_nStyle)
		DrawBuddyItemInStdIcon(pDC, nTeamIndex, nIndex);
	pDC->SetStretchBltMode(nMode);
}

void CBuddyListBox::DrawBuddyItemInBigIcon(CDC*pDC, int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (NULL == lpItem)
		return;

	CRect rcItem;
	GetItemRectByIndex(nTeamIndex, nIndex, rcItem);

	int nHeadWidth = 40, nHeadHeight = 40;

	CRect rcHead;
	CalcCenterRect(rcItem, nHeadWidth, nHeadHeight, rcHead);
	rcHead.left = rcItem.left + 6;
	rcHead.right = rcHead.left + nHeadWidth;

	int nHeadRight = rcHead.right;

	CString strName1, strName2;
	if (lpItem->m_strMarkName.GetLength() > 0)
	{
		strName1 = lpItem->m_strMarkName;
		strName2.Format(_T("(%s)"), lpItem->m_strNickName);
	}
	else
	{
		strName1 = lpItem->m_strNickName;
		strName2 = _T("");
	}

	if (m_nSelTeamIndex == nTeamIndex && m_nSelIndex == nIndex)				// 选中状态
	{
		if (m_lpBuddyItemBgImgS != NULL && !m_lpBuddyItemBgImgS->IsNull())
			m_lpBuddyItemBgImgS->Draw(pDC, rcItem);
	}
	else if (m_nHoverTeamIndex == nTeamIndex && m_nHoverIndex == nIndex)	// 高亮状态
	{
		if (m_lpBuddyItemBgImgH != NULL && !m_lpBuddyItemBgImgH->IsNull())
			m_lpBuddyItemBgImgH->Draw(pDC, rcItem);
	}
	else
	{

	}

	if (lpItem->m_bHeadFlashAnim)	// 头像闪动动画
	{
		POINT pt[] = {{-1,1},{0,0},{1,1},{0,0}};
		if (lpItem->m_nHeadFlashAnimState >= 0 && lpItem->m_nHeadFlashAnimState < 4)
			rcHead.OffsetRect(pt[lpItem->m_nHeadFlashAnimState]);
	}

	if (lpItem->m_lpHeadImg != NULL && !lpItem->m_lpHeadImg->IsNull())	// 绘制头像
		lpItem->m_lpHeadImg->Draw(pDC, rcHead);

	if (m_nSelTeamIndex == nTeamIndex && m_nSelIndex == nIndex)
	{
		CRect rcHeadFrame(rcHead);
		rcHeadFrame.left -= 3;
		rcHeadFrame.right += 3;
		rcHeadFrame.top -= 3;
		rcHeadFrame.bottom += 3;

		if (m_lpHeadFrameImg != NULL && !m_lpHeadFrameImg->IsNull())	// 绘制头像焦点框
			m_lpHeadFrameImg->Draw(pDC, rcHeadFrame);
	}

	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

	int nMode = pDC->SetBkMode(TRANSPARENT);
	HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
	if (NULL == hFont)
		hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	HFONT hOldFont = (HFONT)pDC->SelectObject(hFont);

	CRect rcName1, rcName2, rcSign;

	if (strName1.GetLength() > 0)
	{
		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(strName1,&rcText, DT_SINGLELINE | DT_CALCRECT);

		rcName1.left = nHeadRight + 6;
		rcName1.right = rcName1.left + rcText.Width();
		rcName1.top = rcItem.top + 9;
		rcName1.bottom = rcName1.top + rcText.Height();
		if (rcName1.right > rcItem.right - 10)
			rcName1.right = rcItem.right - 10;

		COLORREF clrText;
		if (lpItem->m_bOnlineAnim)
		{
			COLORREF colors[] = {RGB(255,0,0), RGB(255,192,0), RGB(37,228,226), RGB(28,197,28), RGB(0,111,225)};
			clrText = colors[lpItem->m_nOnlineAnimState % 5];
		}
		else
			clrText = RGB(0, 0, 0);
		pDC->SetTextColor(clrText);
		pDC->DrawText(strName1, &rcName1, nFormat);

		if (strName2.GetLength() > 0)
		{
			CRect rcText(0,0,0,0);	// 计算文字宽高
			pDC->DrawText(strName2, &rcText, DT_SINGLELINE | DT_CALCRECT);

			rcName2.left = rcName1.right;
			rcName2.right = rcName2.left + rcText.Width();
			rcName2.top = rcItem.top + 9;
			rcName2.bottom = rcName2.top + rcText.Height();
			if (rcName2.right > rcItem.right - 10)
				rcName2.right = rcItem.right - 10;

			pDC->SetTextColor(RGB(128, 128, 128));
			pDC->DrawText(strName2, &rcName2, nFormat);
		}
	}

	if (lpItem->m_strSign.GetLength() > 0)
	{
		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(lpItem->m_strSign,&rcText, DT_SINGLELINE | DT_CALCRECT);

		rcSign.left = nHeadRight + 6;
		rcSign.right = rcSign.left + rcText.Width();
		rcSign.top = rcName1.bottom + 10;
		rcSign.bottom = rcSign.top + rcText.Height();
		if (rcSign.right > rcItem.right - 10)
			rcSign.right = rcItem.right - 10;

		COLORREF clrText;
		if (lpItem->m_bOnlineAnim)
		{
			COLORREF colors[] = {RGB(255,0,0), RGB(255,192,0), RGB(37,228,226), RGB(28,197,28), RGB(0,111,225)};
			clrText = colors[lpItem->m_nOnlineAnimState % 5];
		}
		else
			clrText = RGB(128,128,128);
		pDC->SetTextColor(clrText);
		pDC->DrawText(lpItem->m_strSign, &rcSign, nFormat);
	}

	pDC->SelectObject(hOldFont);
	pDC->SetBkMode(nMode);
}

void CBuddyListBox::DrawBuddyItemInSmallIcon(CDC*pDC, int nTeamIndex, int nIndex)
{
	if (m_bShowBigIconInSel && m_nSelTeamIndex == nTeamIndex && m_nSelIndex == nIndex)
	{
		DrawBuddyItemInBigIcon(pDC, nTeamIndex, nIndex);
		return;
	}

	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (NULL == lpItem)
		return;

	CRect rcItem;
	GetItemRectByIndex(nTeamIndex, nIndex, rcItem);

	int nHeadWidth = 20, nHeadHeight = 20;

	CRect rcHead;
	CalcCenterRect(rcItem, nHeadWidth, nHeadHeight, rcHead);
	rcHead.left = rcItem.left + 6;
	rcHead.right = rcHead.left + nHeadWidth;

	int nHeadRight = rcHead.right;

	CString strName;
	if (lpItem->m_strMarkName.GetLength() > 0)
		strName = lpItem->m_strMarkName;
	else
		strName = lpItem->m_strNickName;

	if (m_nSelTeamIndex == nTeamIndex && m_nSelIndex == nIndex)				// 选中状态
	{
		if (m_lpBuddyItemBgImgS != NULL && !m_lpBuddyItemBgImgS->IsNull())
			m_lpBuddyItemBgImgS->Draw(pDC, rcItem);
	}
	else if (m_nHoverTeamIndex == nTeamIndex && m_nHoverIndex == nIndex)	// 高亮状态
	{
		if (m_lpBuddyItemBgImgH != NULL && !m_lpBuddyItemBgImgH->IsNull())
			m_lpBuddyItemBgImgH->Draw(pDC, rcItem);
	}
	else
	{

	}

	if (lpItem->m_bHeadFlashAnim)	// 头像闪动动画
	{
		POINT pt[] = {{-1,1},{0,0},{1,1},{0,0}};
		if (lpItem->m_nHeadFlashAnimState >= 0 && lpItem->m_nHeadFlashAnimState < 4)
			rcHead.OffsetRect(pt[lpItem->m_nHeadFlashAnimState]);
	}

	if (lpItem->m_lpHeadImg != NULL && !lpItem->m_lpHeadImg->IsNull())	// 绘制头像
		lpItem->m_lpHeadImg->Draw(pDC, rcHead);

	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

	int nMode = pDC->SetBkMode(TRANSPARENT);
	HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
	if (NULL == hFont)
		hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	HFONT hOldFont = (HFONT)pDC->SelectObject(hFont);

	CRect rcName, rcSign;

	if (strName.GetLength() > 0)
	{
		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(strName, &rcText, DT_SINGLELINE | DT_CALCRECT);

		rcName.left = nHeadRight + 6;
		rcName.right = rcName.left + rcText.Width();
		rcName.top = rcItem.top;
		rcName.bottom = rcItem.bottom;
		if (rcName.right > rcItem.right - 10)
			rcName.right = rcItem.right - 10;

		COLORREF clrText;
		if (lpItem->m_bOnlineAnim)
		{
			COLORREF colors[] = {RGB(255,0,0), RGB(255,192,0), RGB(37,228,226), RGB(28,197,28), RGB(0,111,225)};
			clrText = colors[lpItem->m_nOnlineAnimState % 5];
		}
		else
			clrText = RGB(0, 0, 0);
		pDC->SetTextColor(clrText);
		pDC->DrawText(strName, &rcName, nFormat);
	}

	if (lpItem->m_strSign.GetLength() > 0)
	{
		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(lpItem->m_strSign, &rcText, DT_SINGLELINE | DT_CALCRECT);

		rcSign.left = rcName.right + 6;
		rcSign.right = rcSign.left + rcText.Width();
		rcSign.top = rcItem.top;
		rcSign.bottom = rcItem.bottom;
		if (rcSign.right > rcItem.right - 10)
			rcSign.right = rcItem.right - 10;

		COLORREF clrText;
		if (lpItem->m_bOnlineAnim)
		{
			COLORREF colors[] = {RGB(255,0,0), RGB(255,192,0), RGB(37,228,226), RGB(28,197,28), RGB(0,111,225)};
			clrText = colors[lpItem->m_nOnlineAnimState % 5];
		}
		else
			clrText = RGB(128, 128, 128);
		pDC->SetTextColor(clrText);
		pDC->DrawText(lpItem->m_strSign, &rcSign, nFormat);
	}

	pDC->SelectObject(hOldFont);
	pDC->SetBkMode(nMode);
}

void CBuddyListBox::DrawBuddyItemInStdIcon(CDC*pDC, int nTeamIndex, int nIndex)
{
	CBuddyItem * lpItem = GetBuddyItemByIndex(nTeamIndex, nIndex);
	if (NULL == lpItem)
		return;

	CRect rcItem;
	GetItemRectByIndex(nTeamIndex, nIndex, rcItem);

	CImageEx * lpHeadImg;
	if (lpItem->m_bGender)
		lpHeadImg = m_lpStdGGHeadImg;
	else
		lpHeadImg = m_lpStdMMHeadImg;

	int nHeadWidth = 16, nHeadHeight = 16;

	CRect rcHead;
	CalcCenterRect(rcItem, nHeadWidth, nHeadHeight, rcHead);
	rcHead.left = rcItem.left + 6;
	rcHead.right = rcHead.left + nHeadWidth;

	int nHeadRight = rcHead.right;

	if (lpItem->m_bHeadFlashAnim)	// 头像闪动动画
	{
		POINT pt[] = {{-1,1},{0,0},{1,1},{0,0}};
		if (lpItem->m_nHeadFlashAnimState >= 0 && lpItem->m_nHeadFlashAnimState < 4)
			rcHead.OffsetRect(pt[lpItem->m_nHeadFlashAnimState]);
	}

	CString strName;
	if (lpItem->m_strMarkName.GetLength() > 0)
		strName = lpItem->m_strMarkName;
	else
		strName = lpItem->m_strNickName;

	if (m_nSelTeamIndex == nTeamIndex && m_nSelIndex == nIndex)
	{
		if (m_lpBuddyItemBgImgS != NULL && !m_lpBuddyItemBgImgS->IsNull())
			m_lpBuddyItemBgImgS->Draw(pDC, rcItem);

		CRect rcHeadFrame(rcHead);
		rcHeadFrame.left -= 2;
		rcHeadFrame.right += 2;
		rcHeadFrame.top -= 2;
		rcHeadFrame.bottom += 2;

		if (m_lpHeadFrameImg != NULL && !m_lpHeadFrameImg->IsNull())
			m_lpHeadFrameImg->Draw(pDC, rcHeadFrame);
	}
	else if (m_nHoverTeamIndex == nTeamIndex && m_nHoverIndex == nIndex)
	{
		if (m_lpBuddyItemBgImgH != NULL && !m_lpBuddyItemBgImgH->IsNull())
			m_lpBuddyItemBgImgH->Draw(pDC, rcItem);
	}
	else
	{

	}

	if (lpHeadImg != NULL && !lpHeadImg->IsNull())	// 绘制头像
		lpHeadImg->Draw(pDC, rcHead);

	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS;

	int nMode = pDC->SetBkMode( TRANSPARENT);
	HFONT hFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
	if (NULL == hFont)
		hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	HFONT hOldFont = (HFONT)pDC->SelectObject(hFont);

	CRect rcName, rcSign;

	if (strName.GetLength() > 0)
	{
		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(strName, &rcText, DT_SINGLELINE | DT_CALCRECT);

		rcName.left = nHeadRight + 6;
		rcName.right = rcName.left + rcText.Width();
		rcName.top = rcItem.top;
		rcName.bottom = rcItem.bottom;
		if (rcName.right > rcItem.right - 10)
			rcName.right = rcItem.right - 10;

		COLORREF clrText;
		if (lpItem->m_bOnlineAnim)
		{
			COLORREF colors[] = {RGB(255,0,0), RGB(255,192,0), RGB(37,228,226), RGB(28,197,28), RGB(0,111,225)};
			clrText = colors[lpItem->m_nOnlineAnimState % 5];
		}
		else
			clrText = RGB(0, 0, 0);
		pDC->SetTextColor(clrText);
		pDC->DrawText(strName, strName.GetLength(), &rcName, nFormat);
	}

	if (lpItem->m_strSign.GetLength() > 0)
	{
		CRect rcText(0,0,0,0);	// 计算文字宽高
		pDC->DrawText(lpItem->m_strSign, &rcText, DT_SINGLELINE | DT_CALCRECT);

		rcSign.left = rcName.right + 6;
		rcSign.right = rcSign.left + rcText.Width();
		rcSign.top = rcItem.top;
		rcSign.bottom = rcItem.bottom;
		if (rcSign.right > rcItem.right - 10)
			rcSign.right = rcItem.right - 10;

		COLORREF clrText;
		if (lpItem->m_bOnlineAnim)
		{
			COLORREF colors[] = {RGB(255,0,0), RGB(255,192,0), RGB(37,228,226), RGB(28,197,28), RGB(0,111,225)};
			clrText = colors[lpItem->m_nOnlineAnimState % 5];
		}
		else
			clrText = RGB(128, 128, 128);
		pDC->SetTextColor(clrText);
		pDC->DrawText(lpItem->m_strSign, &rcSign, nFormat);
	}

	pDC->SelectObject(hOldFont);
	pDC->SetBkMode(nMode);
}

void CBuddyListBox::HitTest(POINT pt, int& nTeamIndex, int& nIndex)
{
	CBuddyRootItem * lpTeamItem;
	CBuddyItem * lpItem;
	int nLeft = m_rcMargin.left+m_nLeft, nTop = m_nTop;
	int nBuddyTeamWidth, nBuddyItemWidth, nBuddyItemHeight;
	CRect rcItem;

	nTeamIndex = -1;
	nIndex = -1;

	CRect rcClient;
	GetClientRect(&rcClient);

	int nVScrollBarWidth = 0;
 	if (m_VScrollBar.IsVisible())
 	{
 		CRect rcVScrollBar;
 		m_VScrollBar.GetRect(&rcVScrollBar);
 		nVScrollBarWidth = rcVScrollBar.Width();
 	}

	nBuddyTeamWidth = rcClient.Width() - m_rcMargin.left - m_rcMargin.right - nVScrollBarWidth;
	nBuddyItemWidth = nBuddyTeamWidth;
	if (BLC_BIG_ICON_STYLE == m_nStyle)
		nBuddyItemHeight = m_nBuddyItemHeightInBig;
	else if (BLC_SMALL_ICON_STYLE == m_nStyle)
		nBuddyItemHeight = m_nBuddyItemHeightInSmall;
	else
		nBuddyItemHeight = m_nBuddyItemHeightInStd;

	for (int i = 0; i < (int)m_arrBuddyTeamItems.size(); i++)
	{
		lpTeamItem = m_arrBuddyTeamItems[i];
		if (lpTeamItem != NULL)
		{
			rcItem = CRect(nLeft, nTop, nLeft+nBuddyTeamWidth, nTop+m_nBuddyTeamHeight);
			if (rcItem.PtInRect(pt))
			{
				nTeamIndex = i;
				nIndex = -1;
				return;
			}

			nTop += m_nBuddyTeamHeight;
			nTop += m_nBuddyTeamPadding;

			if (lpTeamItem->m_bExpand)
			{
				for (int j = 0; j < (int)lpTeamItem->m_arrBuddys.size(); j++)
				{
					lpItem = lpTeamItem->m_arrBuddys[j];
					if (lpItem != NULL)
					{
						if (BLC_SMALL_ICON_STYLE == m_nStyle && m_bShowBigIconInSel
							&& (m_nSelTeamIndex == i && m_nSelIndex == j))
							nBuddyItemHeight = m_nBuddyItemHeightInBig;

						rcItem = CRect(nLeft, nTop, nLeft+nBuddyItemWidth, nTop+nBuddyItemHeight);
						if (rcItem.PtInRect(pt))
						{
							nTeamIndex = i;
							nIndex = j;
							return;
						}

						nTop += nBuddyItemHeight;
						nTop += m_nBuddyItemPadding;

						if (BLC_SMALL_ICON_STYLE == m_nStyle && m_bShowBigIconInSel
							&& (m_nSelTeamIndex == i && m_nSelIndex == j))
							nBuddyItemHeight = m_nBuddyItemHeightInSmall;
					}
				}
			}
		}
	}
}

CBuddyRootItem * CBuddyListBox::GetBuddyTeamByIndex(int nIndex)
{
	if (nIndex >= 0 && nIndex < (int)m_arrBuddyTeamItems.size())
		return m_arrBuddyTeamItems[nIndex];
	else
		return NULL;
}

CBuddyItem * CBuddyListBox::GetBuddyItemByIndex(int nTeamIndex, int nIndex)
{
	CBuddyRootItem * lpTeamItem;

	if (nTeamIndex >= 0 && nTeamIndex < (int)m_arrBuddyTeamItems.size())
	{
		lpTeamItem = m_arrBuddyTeamItems[nTeamIndex];
		if (lpTeamItem != NULL)
		{
			if (nIndex >= 0 && nIndex < (int)lpTeamItem->m_arrBuddys.size())
				return lpTeamItem->m_arrBuddys[nIndex];
		}
	}
	return NULL;
}

void CBuddyListBox::CheckScrollBarStatus()
{
	if (!GetSafeHwnd())
		return;

	CBuddyRootItem * lpTeamItem;
	int nLeft = m_rcMargin.left+m_nLeft, nTop = m_nTop;
	int nBuddyTeamWidth, nBuddyItemWidth, nBuddyItemHeight;
	CRect rcItem;

	CRect rcClient;
	GetClientRect(&rcClient);

	int nVScrollBarWidth = 0;
 	if (m_VScrollBar.IsVisible())
 	{
 		CRect rcVScrollBar;
 		m_VScrollBar.GetRect(&rcVScrollBar);
 		nVScrollBarWidth = rcVScrollBar.Width();
 	}

	nBuddyTeamWidth = rcClient.Width() - m_rcMargin.left - m_rcMargin.right - nVScrollBarWidth;
	nBuddyItemWidth = nBuddyTeamWidth;
	if (BLC_BIG_ICON_STYLE == m_nStyle)
		nBuddyItemHeight = m_nBuddyItemHeightInBig;
	else if (BLC_SMALL_ICON_STYLE == m_nStyle)
		nBuddyItemHeight = m_nBuddyItemHeightInSmall;
	else
		nBuddyItemHeight = m_nBuddyItemHeightInStd;

	int nHeight = (m_nBuddyTeamHeight + m_nBuddyTeamPadding) * (int)m_arrBuddyTeamItems.size();

	for (int i = 0; i < (int)m_arrBuddyTeamItems.size(); i++)
	{
		lpTeamItem = m_arrBuddyTeamItems[i];
		if (lpTeamItem != NULL)
		{
			if (lpTeamItem->m_bExpand)
			{
				nHeight += ((nBuddyItemHeight + m_nBuddyItemPadding) * (int)lpTeamItem->m_arrBuddys.size());

				if (BLC_SMALL_ICON_STYLE == m_nStyle && m_bShowBigIconInSel
					&& (m_nSelTeamIndex == i && m_nSelIndex != -1))
				{
					nHeight -= nBuddyItemHeight;
					nHeight += m_nBuddyItemHeightInBig;
				}
			}
		}
	}

 	if (nHeight > rcClient.Height())
 	{
 		m_VScrollBar.SetScrollRange(nHeight - rcClient.Height());
 		Scroll(0, 0);
 		m_VScrollBar.SetVisible(TRUE);
 	}
 	else
 	{
 		m_nTop = 0;
 		m_VScrollBar.SetScrollPos(0);
 		m_VScrollBar.SetVisible(FALSE);
 	}
}

void CBuddyListBox::Scroll(int cx, int cy)
{
 	if (m_VScrollBar.IsVisible() && m_VScrollBar.IsEnabled())
 	{
 		int nPos = m_VScrollBar.GetScrollPos();
 		m_VScrollBar.SetScrollPos(nPos + cy);
 		nPos = m_VScrollBar.GetScrollPos();
 		m_nTop = 0 - nPos;
 	}
}

void CBuddyListBox::EnsureVisible(int nTeamIndex, int nIndex)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcItem;
	GetItemRectByIndex(nTeamIndex, nIndex, rcItem);

	if (rcItem.top < rcClient.top || rcItem.bottom >= rcClient.bottom)
	{
		int cy = 0;
		if (rcItem.top < rcClient.top)
			cy = rcItem.top - rcClient.top;
		if (rcItem.bottom > rcClient.bottom)
			cy = rcItem.bottom - rcClient.bottom;
		Scroll(0, cy);
	}
}

void CBuddyListBox::SortBuddyTeam(int nTeamIndex, int nIndex)
{
	CBuddyRootItem * lpBuddyTeam = GetBuddyTeamByIndex(nTeamIndex);	// 获取要排序的分组
	if (NULL == lpBuddyTeam)
		return;

	int nItemCnt = (int)lpBuddyTeam->m_arrBuddys.size();	// 分组的好友数小于2则不用再排序
	if (nItemCnt < 2)
		return;

	CBuddyItem * lpBuddyItem1 = GetBuddyItemByIndex(nTeamIndex, nIndex);	// 获取要排序的好友
	if (NULL == lpBuddyItem1)
		return;

	lpBuddyTeam->m_arrBuddys.erase(lpBuddyTeam->m_arrBuddys.begin()+nIndex);// 先删除

	nItemCnt = (int)lpBuddyTeam->m_arrBuddys.size();

	int nInsert = nItemCnt-1;
	for (int i = 0; i < nItemCnt; i++)
	{
		CBuddyItem * lpBuddyItem2 = lpBuddyTeam->m_arrBuddys[i];
		if (lpBuddyItem2 != NULL)
		{
			if (lpBuddyItem1->m_bOnline > lpBuddyItem2->m_bOnline)
			{
				nInsert = i;
				break;
			}
			else if (lpBuddyItem1->m_bOnline == lpBuddyItem2->m_bOnline)
			{
				if (lpBuddyItem1->m_nID <= lpBuddyItem2->m_nID)
				{
					nInsert = i;
					break;
				}
			}
		}
	}

	lpBuddyTeam->m_arrBuddys.insert(lpBuddyTeam->m_arrBuddys.begin()+nInsert, lpBuddyItem1);
}

// 头像闪动动画
void CBuddyListBox::OnTimer_HeadFlashAnim(UINT_PTR nIDEvent)
{
	if (nIDEvent != m_dwHeadFlashAnimTimerId)
		return;

	int nTeamCnt = GetBuddyTeamCount();
	for (int i = 0; i < nTeamCnt; i++)
	{
		CBuddyRootItem * lpBuddyTeam = GetBuddyTeamByIndex(i);
		if (lpBuddyTeam != NULL)
		{
			if (lpBuddyTeam->m_nHeadFlashAnim > 0)
			{
				if (!lpBuddyTeam->m_bExpand)
				{
					lpBuddyTeam->m_nHeadFlashAnimState++;
					if (lpBuddyTeam->m_nHeadFlashAnimState >= 2)
						lpBuddyTeam->m_nHeadFlashAnimState = 0;
				}
				else
				{
					int nItemCnt = GetBuddyItemCount(i);
					for (int j = 0; j < nItemCnt; j++)
					{
						CBuddyItem * lpBuddyItem = GetBuddyItemByIndex(i, j);
						if (lpBuddyItem != NULL && lpBuddyItem->m_bHeadFlashAnim)
						{
							lpBuddyItem->m_nHeadFlashAnimState++;
							if (lpBuddyItem->m_nHeadFlashAnimState >= 4)
								lpBuddyItem->m_nHeadFlashAnimState = 0;
						}
					}
				}
			}
		}
	}
	Invalidate(FALSE);
}

// 上线动画
void CBuddyListBox::OnTimer_OnlineAnim(UINT_PTR nIDEvent)
{
	if (nIDEvent != m_dwOnlineAnimTimerId)
		return;

	int nAnimCnt = 0;

	int nTeamCnt = GetBuddyTeamCount();
	for (int i = 0; i < nTeamCnt; i++)
	{
		int nItemCnt = GetBuddyItemCount(i);
		for (int j = 0; j < nItemCnt; j++)
		{
			CBuddyItem * lpBuddyItem = GetBuddyItemByIndex(i, j);
			if (lpBuddyItem != NULL && lpBuddyItem->m_bOnlineAnim)
			{
				nAnimCnt++;
				lpBuddyItem->m_nOnlineAnimState++;
				if (lpBuddyItem->m_nOnlineAnimState == 5)
				{
					SortBuddyTeam(i, j);
				}
				else if (lpBuddyItem->m_nOnlineAnimState >= 5 * 5)
				{
					lpBuddyItem->m_bOnlineAnim = FALSE;
					lpBuddyItem->m_nOnlineAnimState = 0;
				}
			}
		}
	}

	if (nAnimCnt <= 0)
	{
		KillTimer(m_dwOnlineAnimTimerId);
		m_dwOnlineAnimTimerId = NULL;
	}
	Invalidate(FALSE);
}

// 下线动画
void CBuddyListBox::OnTimer_OfflineAnim(UINT_PTR nIDEvent)
{
	if (nIDEvent != m_dwOfflineAnimTimerId)
		return;

	int nTeamCnt = GetBuddyTeamCount();
	for (int i = 0; i < nTeamCnt; i++)
	{
		int nItemCnt = GetBuddyItemCount(i);
		for (int j = 0; j < nItemCnt; j++)
		{
			CBuddyItem * lpBuddyItem = GetBuddyItemByIndex(i, j);
			if (lpBuddyItem != NULL && lpBuddyItem->m_bOfflineAnim)
			{
				lpBuddyItem->m_bOfflineAnim = FALSE;
				SortBuddyTeam(i, j);
			}
		}
	}

	KillTimer(m_dwOfflineAnimTimerId);
	m_dwOfflineAnimTimerId = NULL;

	Invalidate(FALSE);
}
void CBuddyListBox::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	int nLineSize = 24;
	int nPageSize = rcClient.Height();

	switch (nSBCode)
	{
	case SB_LINEUP:
		Scroll(0, -nLineSize);
		break;

	case SB_LINEDOWN:
		Scroll(0, nLineSize);
		break;

	case SB_PAGEUP:
		Scroll(0, -nPageSize);
		break;

	case SB_PAGEDOWN:
		Scroll(0, nPageSize);
		break;

	case SB_THUMBTRACK:
		Scroll(0, 0);
		break;

	default:
		return;
	}

	Invalidate(FALSE);

	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}

UINT CBuddyListBox::OnGetDlgCode()
{
	return DLGC_HASSETSEL | DLGC_WANTARROWS | DLGC_WANTCHARS | DLGC_WANTTAB;

	return __super::OnGetDlgCode();
}

BOOL CBuddyListBox::PreTranslateMessage(MSG* pMsg)
{
	if (m_ToolTipCtrl.GetSafeHwnd())
		m_ToolTipCtrl.RelayEvent(pMsg);

	return __super::PreTranslateMessage(pMsg);
}

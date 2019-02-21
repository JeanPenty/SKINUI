// ButtonEx.cpp : 实现文件
//

#include "stdafx.h"
#include "Music.h"
#include "ButtonEx.h"


// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CButton)

CButtonEx::CButtonEx()
{
	m_bExpand=true;
	m_bHovering=false;
	m_crTextColor = RGB(0,0,0);
}

CButtonEx::~CButtonEx()
{
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CButtonEx 消息处理程序



//对象附加到现有窗口
void CButtonEx::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	SetButtonStyle(GetButtonStyle()|BS_OWNERDRAW);
}

//建立消息
int CButtonEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;
	
	SetButtonStyle(GetButtonStyle()|BS_OWNERDRAW);

	return 0;
}

//加载位图
bool CButtonEx::SetButtonImage(LPCTSTR pszFileName, bool bExpandImage)
{
	//效验参数
	ASSERT(pszFileName);
	if (pszFileName==NULL) return false;

	//加载位图
	m_bExpand=bExpandImage;
	m_ImageBack.LoadImage(pszFileName);

	//调整位置
	if (m_bExpand==false) FixButtonSize();
	if (GetSafeHwnd()) Invalidate(FALSE);

	return true;
}

//加载位图
bool CButtonEx::SetButtonImage(HINSTANCE hInstance,LPCTSTR pszResourceName, bool bExpandImage)
{
	//加载位图
	ASSERT(pszResourceName!=0);
	if (pszResourceName==NULL) return false;

	m_bExpand=bExpandImage;
	m_ImageBack.LoadImage(hInstance,pszResourceName);

	//调整位置
	if (m_bExpand==false) FixButtonSize();
	if (GetSafeHwnd()) Invalidate(FALSE);

	return true;
}

//调整位置
bool CButtonEx::FixButtonSize()
{
	if (!m_ImageBack.IsNull()&&GetSafeHwnd())
	{
		SetWindowPos(NULL,0,0,m_ImageBack.GetWidth()/4,m_ImageBack.GetHeight(),SWP_NOMOVE);
		return true;
	}
	return false;
}

//鼠标移动消息
void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bHovering==false)
	{
		//注册消息
		m_bHovering=true;
		Invalidate(FALSE);
		TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.hwndTrack=GetSafeHwnd();
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		_TrackMouseEvent(&TrackMouseEvent);
	}
	__super::OnMouseMove(nFlags, point);
}

//鼠标离开消息
LRESULT CButtonEx::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bHovering=false;
	Invalidate(FALSE);
	return 0;
}

//设置颜色
bool CButtonEx::SetTextColor(COLORREF crTextColor)
{
	m_crTextColor=crTextColor;
	if (GetSafeHwnd()) Invalidate(FALSE);
	return true;
}

//界面绘画函数
void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//定义变量
	CRect rcClient;
	GetClientRect(&rcClient);
	bool bDisable=((lpDrawItemStruct->itemState&ODS_DISABLED)!=0);
	bool bButtonDown=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0);

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	//获取文字
	CString strText;
	GetWindowText(strText);
	
	//绘制父窗口背景
	CRect rcWindow;
	CClientDC clDC(GetParent());

	GetWindowRect(rcWindow);
	GetParent()->ScreenToClient(rcWindow);

	CDC dcParent;
	CBitmap bmp,*pOldBitmap;
	dcParent.CreateCompatibleDC(&clDC);
	bmp.CreateCompatibleBitmap(&clDC,rcClient.Width(),rcClient.Height());
	pOldBitmap = dcParent.SelectObject(&bmp);
	dcParent.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&clDC,rcWindow.left,rcWindow.top,SRCCOPY);
	bmp.DeleteObject();

	//加载背景图
	if ( !m_ImageBack.IsNull() )
	{
		//计算位图位置
		int nWidth=m_ImageBack.GetWidth()/4,nDrawPos=0;
		if (bDisable) nDrawPos=nWidth*3;
		else if (bButtonDown) nDrawPos=nWidth*2;
		else if (m_bHovering) nDrawPos=nWidth*1;

		//绘画背景图
		if (m_bExpand==false) m_ImageBack.DrawImage(pDC,0,0,rcClient.Width(),rcClient.Height(),nDrawPos,0);
		else m_ImageBack.DrawImage(pDC,0,0,rcClient.Width(),rcClient.Height(),nDrawPos,0,nWidth,m_ImageBack.GetHeight());
	}
	else
	{
		//绘画默认界面
		pDC->FillSolidRect(&rcClient,GetSysColor(COLOR_BTNFACE));
		if (bButtonDown) pDC->Draw3dRect(&rcClient,GetSysColor(COLOR_WINDOWFRAME),GetSysColor(COLOR_3DHILIGHT));
		else pDC->Draw3dRect(&rcClient,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_WINDOWFRAME));
	}

	//绘画字体
	rcClient.top+=1;
	pDC->SetBkMode(TRANSPARENT);
	if (bDisable) pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	else pDC->SetTextColor(m_crTextColor);
	pDC->DrawText(strText,strText.GetLength(),rcClient,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	return;
}
BOOL CButtonEx::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

//	return CButton::OnEraseBkgnd(pDC);
}
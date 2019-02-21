// LayeredWindow.cpp : 实现文件
//

#include "stdafx.h"
#include "LayeredWindow.h"

//枚举结构
struct tagEnumChildInfo
{
	CWnd *							pWndControl;						//控制窗口
	CWnd *							pWndLayered;						//分层窗口
	CRgn *							pRegionResult;						//结果区域
};

IMPLEMENT_DYNAMIC(CLayeredWindow, CWnd)

CLayeredWindow::CLayeredWindow()
{
	//设置变量
	m_pWndControl=NULL;
}

CLayeredWindow::~CLayeredWindow()
{
}


BEGIN_MESSAGE_MAP(CLayeredWindow, CWnd)
END_MESSAGE_MAP()



//创建窗口
VOID CLayeredWindow::CreateLayered(CWnd * pWndControl, CRect & rcWindow)
{
	//效验参数
	ASSERT((pWndControl!=NULL)&&(pWndControl->m_hWnd!=NULL));
	if ((pWndControl==NULL)||(pWndControl->m_hWnd==NULL)) return;

	//设置变量
	m_pWndControl=pWndControl;

	//创建窗口
	CreateEx(WS_EX_LAYERED,TEXT("STATIC"),TEXT(""),0,rcWindow,pWndControl,0L);

	return;
}

//设置区域
VOID CLayeredWindow::InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild)
{
	//效验参数
	ASSERT((pDCImage!=NULL)&&(pDCImage->m_hDC!=NULL));
	if ((pDCImage==NULL)||(pDCImage->m_hDC==NULL)) return;

	//变量定义
	BITMAP Bitmap;
	ZeroMemory(&Bitmap,sizeof(Bitmap));

	//获取图像
	CBitmap * pBitmap=pDCImage->GetCurrentBitmap();
	if (pBitmap!=NULL) pBitmap->GetBitmap(&Bitmap);

	//获取大小
	CSize SizeImage;
	SizeImage.SetSize(Bitmap.bmWidth,Bitmap.bmHeight);

	//效验大小
	ASSERT((SizeImage.cx>0)&&(SizeImage.cy>0));
	if ((SizeImage.cx==0)||(SizeImage.cy==0)) return;

	//变量定义
	BLENDFUNCTION BlendFunction;
	ZeroMemory(&BlendFunction,sizeof(BlendFunction));

	//设置参数
	BlendFunction.BlendOp=0;
	BlendFunction.BlendFlags=0;
	BlendFunction.AlphaFormat=AC_SRC_ALPHA;
	BlendFunction.SourceConstantAlpha=cbAlpha;

	//设置分层
	CPoint ImagePoint(0,0);
	CClientDC ClientDC(this);
	UpdateLayeredWindow(&ClientDC,NULL,&SizeImage,pDCImage,&ImagePoint,0L,&BlendFunction,ULW_ALPHA);

	//创建区域
	CRgn RegionResult;
	RegionResult.CreateRectRgn(0,0,SizeImage.cx,SizeImage.cy);

	//窗口排除
	if (bUnLayeredChild==true)
	{
		//变量定义
		tagEnumChildInfo EnumChildInfo;
		ZeroMemory(&EnumChildInfo,sizeof(EnumChildInfo));

		//设置变量
		EnumChildInfo.pWndLayered=this;
		EnumChildInfo.pWndControl=m_pWndControl;
		EnumChildInfo.pRegionResult=&RegionResult;

		//枚举窗口
		ASSERT(m_pWndControl->GetSafeHwnd()!=NULL);
		EnumChildWindows(m_pWndControl->m_hWnd,EnumChildProc,(LPARAM)&EnumChildInfo);
	}

	//区域排除
	if (rcUnLayered.IsRectEmpty()==FALSE)
	{
		//创建区域
		CRgn RegionUnLayered;
		RegionUnLayered.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,PointRound.x,PointRound.y);

		//合并区域
		RegionResult.CombineRgn(&RegionResult,&RegionUnLayered,RGN_DIFF);
	}

	//设置区域
	SetWindowRgn(RegionResult,TRUE);

	return;
}

//设置区域
VOID CLayeredWindow::InitLayeredArea(CImageEx & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild)
{
	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(Image.GetWidth(),Image.GetHeight(),32);

	//绘画界面
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//绘画界面
	ASSERT(pBufferDC!=NULL);
	if (pBufferDC!=NULL) Image.DrawImage(pBufferDC,0,0);

	//创建分层
	InitLayeredArea(pBufferDC,cbAlpha,rcUnLayered,PointRound,bUnLayeredChild);

	return;
}

//关闭消息
VOID CLayeredWindow::OnClose()
{
	//投递消息
	if (m_pWndControl!=NULL)
	{
		m_pWndControl->PostMessage(WM_CLOSE);
	}

	return;
}

//焦点消息
VOID CLayeredWindow::OnSetFocus(CWnd * pOldWnd)
{
	//设置焦点
	if (m_pWndControl!=NULL)
	{
		m_pWndControl->SetFocus();
	}
}

//枚举函数
BOOL CALLBACK CLayeredWindow::EnumChildProc(HWND hWndChild, LPARAM lParam)
{
	//获取位置
	CRect rcWindow;
	::GetWindowRect(hWndChild,&rcWindow);

	//创建区域
	if ((rcWindow.Width()>0)&&(rcWindow.Height()>0))
	{
		//变量定义
		ASSERT(lParam!=0L);
		tagEnumChildInfo * pEnumChildInfo=(tagEnumChildInfo *)lParam;

		//窗口判断
		HWND hWndParent=::GetParent(hWndChild);
		if (hWndParent!=pEnumChildInfo->pWndControl->GetSafeHwnd())
		{
			return TRUE;
		}

		//转换位置
		ASSERT(pEnumChildInfo->pWndControl!=NULL);
		pEnumChildInfo->pWndControl->ScreenToClient(&rcWindow);

		//创建区域
		CRgn RgnChild;
		RgnChild.CreateRectRgn(rcWindow.left,rcWindow.top,rcWindow.right,rcWindow.bottom);

		//合并区域
		ASSERT(pEnumChildInfo->pRegionResult!=NULL);
		pEnumChildInfo->pRegionResult->CombineRgn(pEnumChildInfo->pRegionResult,&RgnChild,RGN_DIFF);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CLayeredDialog, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()

// CLayeredDialog 对话框

IMPLEMENT_DYNAMIC(CLayeredDialog, CDialog)
//////////////////////////////////////////////////////////////////////////

CLayeredDialog::CLayeredDialog(UINT uTemplate, CWnd* pParent /*=NULL*/): CDialog(uTemplate, pParent)
{
}

CLayeredDialog::~CLayeredDialog()
{
}

void CLayeredDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CLayeredDialog::SetLayeredDialog( HINSTANCE hInstance,LPCTSTR lpResource,CSize szSizeLT,CSize szSizeRB )
{
	//设置窗口
	RemoveBorder();

	//加载资源
	m_ImageBack.LoadImage(hInstance,lpResource);

	//设置大小
	CSize SizeWindow(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//计算位置
	CRect rcUnLayered;
	rcUnLayered.top=szSizeLT.cy;
	rcUnLayered.left=szSizeLT.cx;
	rcUnLayered.right=rcWindow.Width()-szSizeRB.cx;
	rcUnLayered.bottom=rcWindow.Height()-szSizeRB.cy;

	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,0,0);

	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	//分层窗口
	m_LayeredWindow.CreateLayered(this,rcWindow);
	m_LayeredWindow.InitLayeredArea(m_ImageBack,255,rcUnLayered,CPoint(0,0),false);
}

void CLayeredDialog::RemoveBorder()
{
	DWORD dwStyle = GetStyle();
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE| WS_SYSMENU |WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	dwNewStyle&=dwStyle;
	SetWindowLong(m_hWnd,GWL_STYLE,dwNewStyle);
	DWORD dwExStyle = GetExStyle();
	DWORD dwNewExStyle = WS_EX_LEFT |WS_EX_LTRREADING |WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle&=dwExStyle;
	SetWindowLong(m_hWnd,GWL_EXSTYLE,dwNewExStyle);
}

//绘画背景
BOOL CLayeredDialog::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	if ( ImageBuffer.IsNull() ) return TRUE;

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//设置缓冲
	pBufferDC->SetBkMode(TRANSPARENT);

	//绘画背景
	m_ImageBack.DrawImage(pBufferDC,0,0);

	OnDrawClientArea(pBufferDC,rcClient.Width(),rcClient.Height());

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//显示消息
VOID CLayeredDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//显示分层
	if (m_LayeredWindow.m_hWnd!=NULL)
	{
		m_LayeredWindow.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//位置改变
VOID CLayeredDialog::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//移动分层
	if ((m_LayeredWindow.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_LayeredWindow.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}
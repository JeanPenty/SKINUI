// DialogEx.cpp : 实现文件
//

#include "stdafx.h"
#include "Design.h"
#include "DialogEx.h"

CONST INT	nTitleHeight=33;
CONST INT	nFrameBorerL=2;
CONST INT	nFrameBorerR=2;
CONST INT	nFrameBorerB=2;

CONST INT	nCloseWidth=36;
CONST INT	nMaxWidth=29;
CONST INT	nMinWidth=29;

//按钮标识
#define BST_CLOSE					0									//关闭按钮
#define BST_MAX_SIZE				1									//还原按钮
#define BST_MIN_SIZE				2									//缩小按钮

//按钮状态
#define BUT_EXIST					0x01								//按钮存在
#define BUT_NORMAL					0x02								//按钮正常
#define BUT_DISABLE					0x04								//按钮禁止


//无效数值
#define INVALID_BYTE				((BYTE)(0xFF))						//无效数值
//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

// CDialogEx 对话框

IMPLEMENT_DYNAMIC(CDialogEx, CDialog)

CDialogEx::CDialogEx(UINT nIDTemplate, CWnd * pParentWnd) 
	: CDialog(nIDTemplate,pParentWnd)
{
	//按钮状态
	m_cbNowButtonIndex=INVALID_BYTE;
	ZeroMemory(m_cbNowHotIndex,sizeof(m_cbNowHotIndex));
	ZeroMemory(m_cbButtonState,sizeof(m_cbButtonState));
}

CDialogEx::~CDialogEx()
{
}

void CDialogEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogEx, CDialog)
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_SIZE()
	ON_WM_NCMOUSEMOVE()
 	ON_WM_NCMOUSELEAVE()
 	ON_WM_NCLBUTTONDOWN()
 	ON_WM_NCLBUTTONUP()
END_MESSAGE_MAP()


// CDialogEx 消息处理程序

void CDialogEx::OnNcPaint()
{
	CWindowDC dc(this);

	DrawTitleBar(&dc);

	DrawTitleButton(&dc);
}

void CDialogEx::DrawTitleBar( CDC*pDC )
{
	if ( GetSafeHwnd() == NULL ) return;
	
	CRect rtWnd, rtTitle, rtButtons;
	GetWindowRect(&rtWnd); 
	
	//标题栏位置
	rtTitle.SetRect(0,0,rtWnd.right,nTitleHeight);

	if ( !m_ImageTitleL.IsNull() )
	{
		//绘画背景
		m_ImageTitleL.BitBlt(pDC->GetSafeHdc(),0,0);

		//填充中间
		for (INT nXPos=m_ImageTitleL.GetWidth();nXPos<rtWnd.Width();nXPos+=m_ImageTitleM.GetWidth())
		{
			m_ImageTitleM.BitBlt(pDC->GetSafeHdc(),nXPos,0);
		}

		m_ImageTitleM_Spe.BitBlt(pDC->GetSafeHdc(),(rtWnd.Width()-m_ImageTitleM_Spe.GetWidth())/2,0);

		//绘画背景
		m_ImageTitleR.BitBlt(pDC->GetSafeHdc(),rtWnd.Width()-m_ImageTitleR.GetWidth(),0);
	}


	//绘制左边框
	CPoint point;
	point.x = nFrameBorerL;
	point.y = rtWnd.Height();
	pDC->FillSolidRect(0, nTitleHeight, point.x, point.y, RGB(10,10,10));
	
	//绘制下边框
	point.x = rtWnd.Width(); 
	point.y = nFrameBorerB;
	pDC->FillSolidRect(0, rtWnd.Height()-point.y, point.x, point.y, RGB(10,10,10));
	
	//绘制右边框
	point.x = nFrameBorerR;
	point.y = rtWnd.Height();
	pDC->FillSolidRect(rtWnd.Width()-point.x, nTitleHeight, point.x, point.y, RGB(10,10,10));
}

BOOL CDialogEx::OnInitDialog()
{
	CDialog::OnInitDialog();

	//变量定义
	HINSTANCE hInstance=AfxGetInstanceHandle();

	m_ImageTitleL.LoadImage(hInstance,TEXT("TITLE_L"));
	m_ImageTitleM.LoadImage(hInstance,TEXT("TITLE_M"));
	m_ImageTitleM_Spe.LoadImage(hInstance,TEXT("TITLE_M_SPE"));
	m_ImageTitleR.LoadImage(hInstance,TEXT("TITLE_R"));

	m_ImageBt_Close.LoadImage(hInstance,TEXT("BT_CLOSE"));
	m_ImageBt_Max.LoadImage(hInstance,TEXT("BT_MAX"));
	m_ImageBt_Res.LoadImage(hInstance,TEXT("BT_RESTORE"));
	m_ImageBt_Min.LoadImage(hInstance,TEXT("BT_MIN"));

	//按钮状态
	m_cbNowButtonIndex=INVALID_BYTE;
	ZeroMemory(m_cbNowHotIndex,sizeof(m_cbNowHotIndex));
	ZeroMemory(m_cbButtonState,sizeof(m_cbButtonState));

	//设置按钮
	m_cbButtonState[BST_CLOSE]=BUT_EXIST|BUT_NORMAL;
	m_cbButtonState[BST_MAX_SIZE]=BUT_EXIST|BUT_NORMAL;
	m_cbButtonState[BST_MIN_SIZE]=BUT_EXIST|BUT_NORMAL;

	return TRUE;  // return TRUE unless you set the focus to a control
}

LRESULT CDialogEx::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
 	LRESULT lrst=CDialog::DefWindowProc(message, wParam, lParam);
 
 	if (!::IsWindow(m_hWnd))
 		return lrst;
 
 	if (message==WM_MOVE||message==WM_PAINT||message==WM_NCPAINT||message==WM_NCACTIVATE ||message == WM_NOTIFY)
 	{
 		OnNcPaint();
 	}
 
 	return lrst;

	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CDialogEx::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	lpncsp->rgrc[0].top+=nTitleHeight-GetSystemMetrics(SM_CYCAPTION)-GetSystemMetrics(SM_CYSIZEFRAME);;
	lpncsp->rgrc[0].left+=nFrameBorerL-GetSystemMetrics(SM_CXFRAME);
	lpncsp->rgrc[0].right-=nFrameBorerR-GetSystemMetrics(SM_CXSIZEFRAME);
	lpncsp->rgrc[0].bottom-=nFrameBorerB-GetSystemMetrics(SM_CYSIZEFRAME);

	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CDialogEx::DrawTitleButton( CDC*pDC )
{
	if( !m_ImageBt_Close.IsNull() )	
		m_ImageBt_Close.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_CLOSE].left,m_rcButton[BST_CLOSE].top,m_rcButton[BST_CLOSE].Width(),m_rcButton[BST_CLOSE].Height(),m_cbNowHotIndex[0]*m_rcButton[BST_CLOSE].Width(),0);

	if (IsZoomed())
	{
		if( !m_ImageBt_Res.IsNull() )	
			m_ImageBt_Res.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MAX_SIZE].left,m_rcButton[BST_MAX_SIZE].top,m_rcButton[BST_MAX_SIZE].Width(),m_rcButton[BST_MAX_SIZE].Height(),m_cbNowHotIndex[1]*m_rcButton[BST_MAX_SIZE].Width(),0);
	}
	else
	{
		if( !m_ImageBt_Max.IsNull() )	
			m_ImageBt_Max.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MAX_SIZE].left,m_rcButton[BST_MAX_SIZE].top,m_rcButton[BST_MAX_SIZE].Width(),m_rcButton[BST_MAX_SIZE].Height(),m_cbNowHotIndex[1]*m_rcButton[BST_MAX_SIZE].Width(),0);
	}
	
	if( !m_ImageBt_Min.IsNull() )	
		m_ImageBt_Min.BitBlt(pDC->GetSafeHdc(),m_rcButton[BST_MIN_SIZE].left,m_rcButton[BST_MIN_SIZE].top,m_rcButton[BST_MIN_SIZE].Width(),m_rcButton[BST_MIN_SIZE].Height(),m_cbNowHotIndex[2]*m_rcButton[BST_MIN_SIZE].Width(),0);
}

void CDialogEx::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//计算偏移
	INT nYPos=1;
	INT nXPos=cx-nCloseWidth;

	//设置位置
	m_rcButton[BST_CLOSE].SetRect(nXPos,nYPos,nXPos+nCloseWidth,nYPos+31);
	m_rcButton[BST_MAX_SIZE].SetRect(nXPos-nMaxWidth,nYPos,nXPos,nYPos+31);
	m_rcButton[BST_MIN_SIZE].SetRect(nXPos-nMaxWidth-nMaxWidth,nYPos,nXPos-nMaxWidth,nYPos+31);
}

void CDialogEx::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	//将point转换为窗口坐标
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	point.Offset(-rcWindow.left,-rcWindow.top);

	//按钮搜索
	for (INT i=0;i<CountArray(m_cbButtonState);i++)
	{
		if ((m_cbButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(point)))
		{
			//当前判断
			if (m_cbNowButtonIndex==i) return;

			//清除状态
 			if (m_cbNowButtonIndex!=INVALID_BYTE)
 			{
 				m_cbNowHotIndex[m_cbNowButtonIndex]=en_Normal;
 			}

			//设置状态
			if ((m_cbButtonState[i]&BUT_EXIST)&&(!(m_cbButtonState[i]&BUT_DISABLE)))
			{
				m_cbNowButtonIndex=i;
				m_cbNowHotIndex[i] = en_Hoven;
			}

			CDC *pDC = GetWindowDC();
			DrawTitleButton(pDC);
			ReleaseDC(pDC);

			return;
		}
	}

 	//清理焦点
 	if (m_cbNowButtonIndex!=INVALID_BYTE)
 	{
 		//设置变量
 		m_cbNowButtonIndex=INVALID_BYTE;
		ZeroMemory(&m_cbNowHotIndex,sizeof m_cbNowHotIndex);

		CDC *pDC = GetWindowDC();
		DrawTitleButton(pDC);
		ReleaseDC(pDC);
 	}

	CDialog::OnNcMouseMove(nHitTest, point);
}

void CDialogEx::OnNcMouseLeave()
{
	//清理焦点
	if (m_cbNowButtonIndex!=INVALID_BYTE)
	{
		//设置变量
		m_cbNowButtonIndex=INVALID_BYTE;
		ZeroMemory(&m_cbNowHotIndex,sizeof m_cbNowHotIndex);

		CDC *pDC = GetWindowDC();
		DrawTitleButton(pDC);
		ReleaseDC(pDC);
	}

	CDialog::OnNcMouseLeave();
}

void CDialogEx::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	//将point转换为窗口坐标
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	point.Offset(-rcWindow.left,-rcWindow.top);

	//按钮搜索
	for (INT i=0;i<CountArray(m_cbButtonState);i++)
	{
		if ((m_cbButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(point)))
		{
			//清除状态
			if (m_cbNowButtonIndex!=INVALID_BYTE)
			{
				m_cbNowHotIndex[m_cbNowButtonIndex]=en_Normal;
			}

			//设置状态
			if ((m_cbButtonState[i]&BUT_EXIST)&&(!(m_cbButtonState[i]&BUT_DISABLE)))
			{
				m_cbNowButtonIndex=i;
				m_cbNowHotIndex[i] = en_Press;
			}

			CDC *pDC = GetWindowDC();
			DrawTitleButton(pDC);
			ReleaseDC(pDC);

			return;
		}
	}

	//清理焦点
	if (m_cbNowButtonIndex!=INVALID_BYTE)
	{
		//设置变量
		m_cbNowButtonIndex=INVALID_BYTE;
		ZeroMemory(&m_cbNowHotIndex,sizeof m_cbNowHotIndex);

		CDC *pDC = GetWindowDC();
		DrawTitleButton(pDC);
		ReleaseDC(pDC);
	}

	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CDialogEx::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	//将point转换为窗口坐标
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	point.Offset(-rcWindow.left,-rcWindow.top);

	//按钮搜索
	for (INT i=0;i<CountArray(m_cbButtonState);i++)
	{
		if ((m_cbButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(point)))
		{
			//设置状态
			if ((m_cbButtonState[i]&BUT_EXIST)&&(!(m_cbButtonState[i]&BUT_DISABLE)))
			{
				switch (i)
				{
				case 0:
					SendMessage(WM_CLOSE);
					break;
				case 1:
					if (IsZoomed())
						SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
					else SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));

					break;
				case 2:
					SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
					break;
				}
			}

			//设置变量
			m_cbNowButtonIndex=INVALID_BYTE;
			ZeroMemory(&m_cbNowHotIndex,sizeof m_cbNowHotIndex);

			CDC *pDC = GetWindowDC();
			DrawTitleButton(pDC);
			ReleaseDC(pDC);

			return;
		}
	}

	CDialog::OnNcLButtonUp(nHitTest, point);
}

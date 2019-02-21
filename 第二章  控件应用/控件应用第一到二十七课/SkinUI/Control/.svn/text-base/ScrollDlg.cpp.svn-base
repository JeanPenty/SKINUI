// ScrollDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScrollDlg.h"
#include "resource.h"

// CScrollDlg 对话框

IMPLEMENT_DYNAMIC(CScrollDlg, CDlgControlItem)

CScrollDlg::CScrollDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_SCROLL, pParent)
{
	m_nCurrentPos = 0;
}

CScrollDlg::~CScrollDlg()
{
}

void CScrollDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_SCROLLBAR1,m_ScrollBar1);
	DDX_Control(pDX,IDC_SCROLLBAR2,m_ScrollBar2);
}


BEGIN_MESSAGE_MAP(CScrollDlg, CDlgControlItem)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1,Start)
	ON_BN_CLICKED(IDC_BUTTON14,Stop)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


BOOL CScrollDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();
	

	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);     
	info.fMask = SIF_ALL;     
	info.nMin = 0;     
	info.nMax = 100; 
	info.nPage = 50;     
	info.nPos = 0;    
	m_ScrollBar1.SetScrollInfo(&info);

	m_ScrollBar2.SetScrollRange(0,50);
	m_ScrollBar2.SetScrollPos(20);

	//创建滚动条，并且假设滚动条要显示3倍客户区大小
	CRect rcClient;
	GetClientRect(&rcClient);

	//设置滚动条
	SCROLLINFO ScrollInfo;
	ScrollInfo.cbSize=sizeof(SCROLLINFO);
	ScrollInfo.fMask=SIF_RANGE|SIF_PAGE|SIF_POS;
	ScrollInfo.nMin=0;
	ScrollInfo.nMax=rcClient.Height()*3;
	ScrollInfo.nPage=rcClient.Height();
	ScrollInfo.nPos=m_nCurrentPos;
	SetScrollInfo(SB_VERT,&ScrollInfo,TRUE);

	SetScrollImage(this,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));

	return TRUE;
}

void CScrollDlg::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
 	int nMin,nMax,nCurpos;
 	pScrollBar->GetScrollRange(&nMin,&nMax); 
 	nCurpos=pScrollBar->GetScrollPos();
 	
 	switch(nSBCode)                
 	{
 	case SB_LINELEFT:
 		nCurpos-=5;break;   
 	case SB_LINERIGHT:
 		nCurpos+=5;break;   
 	case SB_THUMBTRACK:
 		nCurpos=nPos;break;
 	}
 	
 	if(nCurpos>nMax)  nCurpos=nMax;
	else if(nCurpos<nMin)  nCurpos=nMin;

 	pScrollBar->SetScrollPos(nCurpos);

	CDlgControlItem::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CScrollDlg::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if ( pScrollBar == NULL )
	{
		//获取参数
		RECT rcClient;
		int iLastPos=m_nCurrentPos;
		GetClientRect(&rcClient);

		//移动坐标
		switch (nSBCode)
		{
		case SB_TOP:
			{
				m_nCurrentPos=0;
				break;
			}
		case SB_BOTTOM:
			{
				m_nCurrentPos=rcClient.bottom*3;
				break;
			}
		case SB_LINEUP:
			{
				m_nCurrentPos-=10;
				break;
			}
		case SB_PAGEUP:
			{
				m_nCurrentPos-=rcClient.bottom;
				break;
			}
		case SB_LINEDOWN:
			{
				m_nCurrentPos+=10;
				break;
			}
		case SB_PAGEDOWN:
			{
				m_nCurrentPos+=rcClient.bottom;
				break;
			}
		case SB_THUMBTRACK:
			{
				m_nCurrentPos=nPos;
				break;
			}
		}

		//调整位置
		SetFocus();
		m_nCurrentPos=__min(m_nCurrentPos,rcClient.bottom*3-rcClient.bottom);
		if (m_nCurrentPos<0) m_nCurrentPos=0;
		if (iLastPos!=m_nCurrentPos)
		{
			SetScrollPos(SB_VERT,m_nCurrentPos);
			ScrollWindow(0,iLastPos-m_nCurrentPos,NULL,NULL);
		}
	}
	else
	{
		int nMin,nMax,nCurpos;
		pScrollBar->GetScrollRange(&nMin,&nMax); 
		nCurpos=pScrollBar->GetScrollPos();

		switch(nSBCode)                
		{
		case SB_LINEUP:
			nCurpos-=5;break;   
		case SB_LINEDOWN:
			nCurpos+=5;break;   
		case SB_THUMBTRACK:
			nCurpos=nPos;break;
		}

		if(nCurpos>nMax)  nCurpos=nMax;
		else if(nCurpos<nMin)  nCurpos=nMin;

		pScrollBar->SetScrollPos(nCurpos);
	}

	CDlgControlItem::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CScrollDlg::Start()
{
	SetTimer(0,100,NULL);
}

void CScrollDlg::Stop()
{
	KillTimer(0);
}

void CScrollDlg::OnTimer( UINT_PTR nIDEvent )
{
	if ( nIDEvent == 0 )
	{
		static int nVScroll=0;
		static int nHScroll=0;

		int nMaxVScroll=0,nMinVScroll=0;
		int nMaxHScroll=0,nMinHScroll=0;

		m_ScrollBar2.GetScrollRange(&nMinVScroll,&nMaxVScroll);

 		SCROLLINFO info;
 		m_ScrollBar1.GetScrollInfo(&info,SIF_ALL);
 		nHScroll = info.nPos;
 		
		nMinHScroll = info.nMin;
 		nMaxHScroll = info.nMax;

		nVScroll = m_ScrollBar2.GetScrollPos();

		if( nHScroll+info.nPage >= nMaxHScroll ) nHScroll = 0;else nHScroll+=10;
		if( nVScroll >= nMaxVScroll ) nVScroll = 0;else nVScroll+=10;

		m_ScrollBar1.SetScrollPos(nHScroll);
		m_ScrollBar2.SetScrollPos(nVScroll);
	}
}

void CScrollDlg::OnDestroy()
{
	RemoveScorll();
}


// CScrollDlg 消息处理程序

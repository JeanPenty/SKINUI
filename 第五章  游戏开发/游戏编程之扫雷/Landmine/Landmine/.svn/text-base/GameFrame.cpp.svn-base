#include "StdAfx.h"
#include "GameFrame.h"

bool CImageEx::LoadImage( HINSTANCE hInstance, LPCTSTR pszResourceName,LPCTSTR pszResourceType/*=TEXT("PNG")*/ )
{
	//查找资源
	HRSRC hResource=FindResource(hInstance,pszResourceName,pszResourceType);
	if (hResource==NULL) return false;

	//读取资源
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);

	//创建数据
	IStream * pIStream=NULL;
	if (CreateStreamOnHGlobal(NULL,TRUE,&pIStream)!=S_OK)
	{
		return false;
	}

	//写入数据
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	HRESULT hr = CImage::Load(pIStream);

	//释放资源
	pIStream->Release();
	pIStream = NULL;

	if (hr == S_OK)
	{
		return SetAlphaBit();
	}
	else
	{
		return false;
	}
}

bool CImageEx::SetAlphaBit()
{
	if(IsNull())return false;

	if ( GetBPP() == 32 )//png图像
	{
		LPVOID pBitsSrc = NULL;
		BYTE * psrc = NULL;
		BITMAP stBmpInfo;

		HBITMAP hBmp = (HBITMAP)*this;

		::GetObject(hBmp, sizeof(BITMAP), &stBmpInfo);

		if (32 != stBmpInfo.bmBitsPixel || NULL == stBmpInfo.bmBits)
			return false;

		psrc = (BYTE *) stBmpInfo.bmBits;

		for (int nPosY = 0; nPosY < abs(stBmpInfo.bmHeight); nPosY++)
		{
			for (int nPosX = stBmpInfo.bmWidth; nPosX > 0; nPosX--)
			{
				BYTE alpha  = psrc[3];
				psrc[0] = (BYTE)((psrc[0] * alpha) / 255);
				psrc[1] = (BYTE)((psrc[1] * alpha) / 255);
				psrc[2] = (BYTE)((psrc[2] * alpha) / 255);
				psrc += 4;
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

CGameFrame::CGameFrame(void)
{
	m_bGameOver = false;
	m_nCurMineCount = 0;
	m_nGameTimer = 0;
}

CGameFrame::~CGameFrame(void)
{
}

void CGameFrame::OnRender( CDC*pDC,int nWidth,int nHeight )
{
	pDC->FillSolidRect(0,0,nWidth,nHeight,RGB(51,54,61));

	HDC hDC = pDC->GetSafeHdc();

	m_ImageClock.Draw(hDC,nWidth/2-140,10);
	m_ImageFlag.Draw(hDC,nWidth/2+70,10);

	DrawNumberString(hDC,m_nCurMineCount,nWidth/2+105,22,TA_RIGHT);

	DrawClock(hDC,nWidth/2-100,15);


	int nPosX = 0,nPosY=0;

	for (int i=0;i<m_nRowCount;i++)
	{
		for (int j=0;j<m_nColCount;j++)
		{
			nPosX = Row_X+i*Cell_Width;
			nPosY = Row_Y+j*Cell_Height;

			m_ImageBack.Draw(hDC,nPosX,nPosY);

			if( m_GameLogic.m_clChessMap != NULL )
			{
				int nCount = m_GameLogic.m_clChessMap[i][j].nCount;

				if( m_GameLogic.m_clChessMap[i][j].bVisible )
				{
					if( nCount == -1 )
						m_ImageNum[9].Draw(hDC,nPosX,nPosY);
					else m_ImageNum[nCount].Draw(hDC,nPosX,nPosY);
				}
				else
				{
					if ( m_GameLogic.m_clChessMap[i][j].bFlag )
					{
						m_ImageNum[10].Draw(hDC,nPosX,nPosY);
					}

					if ( m_GameLogic.m_clChessMap[i][j].bWhy )
					{
						m_ImageNum[11].Draw(hDC,nPosX,nPosY);
					}
				}
			}
		}
	}
}

void CGameFrame::OnLButtonDown( CPoint pt )
{
	//过滤游戏结束状态
	if( m_bGameOver ) return;

	int nPosX = 0,nPosY=0;

	CRect rcItem(0,0,0,0);

	for (int i=0;i<m_nRowCount;i++)
	{
		for (int j=0;j<m_nColCount;j++)
		{
			nPosX = Row_X+i*Cell_Width;
			nPosY = Row_Y+j*Cell_Height;

			rcItem.SetRect(nPosX,nPosY,nPosX+Cell_Width,nPosY+Cell_Height);

			if ( PtInRect(&rcItem,pt) )
			{
				if( m_GameLogic.m_clChessMap != NULL )
				{
					int nCount = m_GameLogic.m_clChessMap[i][j].nCount;
					bool bVisible = m_GameLogic.m_clChessMap[i][j].bVisible;

					//是棋子过滤
					if( m_GameLogic.m_clChessMap[i][j].bFlag ) return;

					//踩中地雷
					if ( nCount == -1 )
					{
						//显示所有地雷分布
						for (int i=0;i<m_nRowCount;i++)
						{
							for (int j=0;j<m_nColCount;j++)
							{
								if ( m_GameLogic.m_clChessMap[i][j].nCount == -1 )
								{
									m_GameLogic.m_clChessMap[i][j].bVisible = true;
								}
							}
						}

						InvalidateRect(AfxGetMainWnd()->GetSafeHwnd(),NULL,FALSE);
						AfxGetMainWnd()->KillTimer(0);
						AfxMessageBox(TEXT("Game Over"));
						m_bGameOver = true;

						return;
					}

					if( !bVisible )
					{
						if ( nCount == 0 )
						{
							m_GameLogic.ShowNullLand(i,j);
							InvalidateRect(AfxGetMainWnd()->GetSafeHwnd(),NULL,FALSE);
						}
						else
						{
							m_GameLogic.m_clChessMap[i][j].bVisible = true;

							InvalidateRect(AfxGetMainWnd()->GetSafeHwnd(),&rcItem,FALSE);
						}

						return;
					}
				}
			}
		}
	}
}

void CGameFrame::OnRButtonDown( CPoint pt )
{
	//过滤游戏结束状态
	if( m_bGameOver ) return;

	int nPosX = 0,nPosY=0;

	CRect rcItem(0,0,0,0);

	for (int i=0;i<m_nRowCount;i++)
	{
		for (int j=0;j<m_nColCount;j++)
		{
			nPosX = Row_X+i*Cell_Width;
			nPosY = Row_Y+j*Cell_Height;

			rcItem.SetRect(nPosX,nPosY,nPosX+Cell_Width,nPosY+Cell_Height);

			if ( PtInRect(&rcItem,pt) )
			{
				if( m_GameLogic.m_clChessMap != NULL )
				{
					//过滤已经显示的元素
					if( m_GameLogic.m_clChessMap[i][j].bVisible ) return;

					//原来是棋子，现在就要显示问号
					if( m_GameLogic.m_clChessMap[i][j].bFlag )
					{
						m_nCurMineCount++;
						m_GameLogic.m_clChessMap[i][j].bFlag = false;
						m_GameLogic.m_clChessMap[i][j].bWhy = true;
						InvalidateRect(AfxGetMainWnd()->GetSafeHwnd(),NULL,FALSE);
						return;
					}

					//原来是问号，现在就要消失
					if( m_GameLogic.m_clChessMap[i][j].bWhy )
					{
						m_GameLogic.m_clChessMap[i][j].bWhy = false;
						InvalidateRect(AfxGetMainWnd()->GetSafeHwnd(),&rcItem,FALSE);
						return;
					}

					m_nCurMineCount--;
					m_GameLogic.m_clChessMap[i][j].bFlag = true;
					InvalidateRect(AfxGetMainWnd()->GetSafeHwnd(),NULL,FALSE);

					if ( m_GameLogic.CheckGameEnd() )
					{
						AfxGetMainWnd()->KillTimer(0);
						AfxMessageBox(TEXT("胜利"));
					}
					
					return;
				}
			}
		}
	}
}

void CGameFrame::OnInitResource()
{
	HINSTANCE hInstance = AfxGetInstanceHandle();

	m_ImageBack.LoadImage(hInstance,TEXT("CELL_BACK"));
	m_ImageClock.LoadImage(hInstance,TEXT("CLOCK"));
	m_ImageClockItem.LoadImage(hInstance,TEXT("CLOCK_ITEM"));
	m_ImageFlag.LoadImage(hInstance,TEXT("MINEFLAG"));
	
	CString str;
	for (int i=0;i<12;i++)
	{
		str.Format(TEXT("CELL_%d"),i);
		m_ImageNum[i].LoadImage(hInstance,str);
	}
}

void CGameFrame::SetChessMap( int nRowCount,int nColCount,int nMineCount/*=15*/ )
{
	m_nRowCount = nRowCount;
	m_nColCount = nColCount;
	m_nMineCount = nMineCount;
	m_nCurMineCount = nMineCount;

	m_bGameOver = false;
	
	int nWidth = nRowCount*Cell_Width+Row_X*2;
	int nHeight = nColCount*Cell_Height+Row_Y*2;

	AfxGetMainWnd()->SetWindowPos(NULL,0,0,nWidth,nHeight,SWP_NOMOVE);

	m_nGameTimer = 0;
	AfxGetMainWnd()->KillTimer(0);
	AfxGetMainWnd()->SetTimer(0,1000,NULL);

	m_GameLogic.SetChessMap(m_nRowCount,m_nColCount,nMineCount);
}

void CGameFrame::ReStartGame()
{
	SetChessMap(m_nRowCount,m_nColCount,m_nMineCount);
}

void CGameFrame::DrawNumberString( HDC hDC, LONG lNumber, INT nXPos, INT nYPos,BYTE cbAlign/*=TA_LEFT*/ )
{
	//加载资源
	INT nNumberHeight=m_ImageClockItem.GetHeight();
	INT nNumberWidth=m_ImageClockItem.GetWidth()/11;

	//计算数目
	LONG lNumberCount=0;
	LONG lNumberTemp=lNumber;
	do
	{
		lNumberCount++;
		lNumberTemp/=10;
	} while (lNumberTemp>0);

	//位置定义
	INT nYDrawPos=nYPos-nNumberHeight/2;
	INT nXDrawPos=nXPos;
	if(cbAlign==TA_RIGHT)
		nXDrawPos+=(lNumberCount-1)*nNumberWidth;

	//绘画桌号
	for (LONG i=0;i<lNumberCount;i++)
	{
		//绘画号码
		LONG lCellNumber=(LONG)(lNumber%10L);
		m_ImageClockItem.Draw(hDC,nXDrawPos,nYDrawPos,nNumberWidth,nNumberHeight,lCellNumber*nNumberWidth,0,nNumberWidth,nNumberHeight);

		//设置变量
		lNumber/=10;
		nXDrawPos-=nNumberWidth;
	};

	return;
}

void CGameFrame::OnTimer( UINT_PTR nIDEvent )
{
	if ( nIDEvent == 0 )
	{
		CRect rcClient;
		AfxGetMainWnd()->GetClientRect(&rcClient);

		m_nGameTimer++;

		InvalidateRect(AfxGetMainWnd()->GetSafeHwnd(),&CRect(rcClient.Width()/2-100,15,rcClient.Width()/2+120,50),FALSE);
	}
}

void CGameFrame::DrawClock( HDC hDC,int nXDrawPos,int nYDrawPos )
{
	//绘画时间
	WORD nClockItem1=(m_nGameTimer/60)/10;
	WORD nClockItem2=(m_nGameTimer/60)%10;
	WORD nClockItem3=(m_nGameTimer%60)/10;
	WORD nClockItem4=(m_nGameTimer%60)%10;

	INT cx = m_ImageClockItem.GetWidth()/11;
	INT cy = m_ImageClockItem.GetHeight();

	m_ImageClockItem.Draw(hDC,nXDrawPos,nYDrawPos,cx,cy,nClockItem1*cx,0,cx,cy);
	m_ImageClockItem.Draw(hDC,nXDrawPos+14,nYDrawPos,cx,cy,nClockItem2*cx,0,cx,cy);

	m_ImageClockItem.Draw(hDC,nXDrawPos+30,nYDrawPos,cx,cy,10*cx,0,cx,cy);

	m_ImageClockItem.Draw(hDC,nXDrawPos+44,nYDrawPos,cx,cy,nClockItem3*cx,0,cx,cy);
	m_ImageClockItem.Draw(hDC,nXDrawPos+58,nYDrawPos,cx,cy,nClockItem4*cx,0,cx,cy);
}

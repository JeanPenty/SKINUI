// GamePengDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePeng.h"
#include "GamePengDlg.h"
#pragma comment (lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGamePengDlg 对话框
#define IDC_START			3000


CGamePengDlg::CGamePengDlg(CWnd* pParent /*=NULL*/)
	: CGameFrameView(IDD_GAMEPENG_DIALOG, pParent)
{
	m_pTextureBomb = NULL;
	m_pTextureBack = NULL;
	m_pTextureTime = NULL;
	m_pTextureTimeThumb = NULL;
	m_pTextureChoose = NULL;
	m_nBombFrame = 0;
	m_bActionCount = 0;
	m_nBatterCount = 0;
	m_nGameTime = 0;
	m_nGameScore = 0;
	m_bPlayBatter = false;
	ZeroMemory(m_ChessInfo,sizeof(m_ChessInfo));
	ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
	ZeroMemory(&m_SoundCombo,sizeof(m_SoundCombo));
	m_ptPosition.SetPoint(0,50);
	m_bResetEffect = false;
	m_nBombAction = 0;
	m_bGameStart = false;
	m_bGameEnd = false;
	SetLogFile(TEXT("GamePeng.log"));
}

void CGamePengDlg::DoDataExchange(CDataExchange* pDX)
{
	CGameFrameView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGamePengDlg, CGameFrameView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_START,OnStartGame)
END_MESSAGE_MAP()

VOID CGamePengDlg::RectifyControl( INT nWidth, INT nHeight )
{

}

VOID CGamePengDlg::CartoonMovie()
{
	static bool bBeginTotalScore = false;;

	//游戏计时器
	if( m_nGameTime >0 && m_LapGameTime.GetLapseCount(1000) > 0 )
	{
		m_nGameTime--;

		if( m_nGameTime == 0 )
		{
			m_bGameEnd = true;
			bBeginTotalScore =true;

			D3DSound->PlaySound(m_SoundGameOver);

			return;
		}
	}

	//统计分数，主要目的就是看看当前是否还有正在移动的棋子，等待动画全部结束后在算分
	if ( bBeginTotalScore && m_LapGameTime.GetLapseCount(2000) > 0 )
	{
		if ( m_bDrawMoveFinish )
		{
			OnEndGame();
			bBeginTotalScore = false;
		}
	}
}

VOID CGamePengDlg::InitGameView( CD3DDevice * pD3DDevice, INT nWidth, INT nHeight )
{
	HINSTANCE hInstance = AfxGetInstanceHandle();

	m_pTextureBack = TextureManager->InitWithTexture(pD3DDevice,hInstance,TEXT("VIEW_BACK"),TEXT("PNG"));
	m_pTextureBomb = TextureManager->InitWithTexture(pD3DDevice,hInstance,TEXT("BOMB"),TEXT("PNG"));
	m_pTextureGameScore = TextureManager->InitWithTexture(pD3DDevice,hInstance,TEXT("GAME_SCORE_NUMBER"),TEXT("PNG"));

	m_pTextureTime = TextureManager->InitWithTexture(pD3DDevice,hInstance,TEXT("TIME_BACK"),TEXT("PNG"));
	m_pTextureTimeThumb = TextureManager->InitWithTexture(pD3DDevice,hInstance,TEXT("TIME_THUMB"),TEXT("PNG"));
	m_pTextureTimeNumber = TextureManager->InitWithTexture(pD3DDevice,hInstance,TEXT("TIME_NUMBER"),TEXT("PNG"));
	m_pTextureChoose = TextureManager->InitWithTexture(pD3DDevice,hInstance,TEXT("CHOOSE"),TEXT("PNG"));

	if(Check_Image(m_pTextureBack))
	{
		int nCaptionHeight = GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME);
		SetWindowPos(NULL,0,0,m_pTextureBack->GetWidth(),m_pTextureBack->GetHeight()+nCaptionHeight,0);
	}

	CString str;
	for (int i=0;i<TYPE_COUNT;i++)
	{
		str.Format(TEXT("CHESS%d"),i);
		m_SpriteChess[i].LoadImage(pD3DDevice,hInstance,str,TEXT("PNG"));
	}

	for (int i=0;i<6;i++)
	{
		str.Format(TEXT("COMBO%d"),i);
		m_SoundCombo[i] = D3DSound->LoadSound(hInstance,str,TEXT("SOUND"),false);
	}

	m_SoundReady = D3DSound->LoadSound(hInstance,TEXT("READY"),TEXT("SOUND"),false);
	m_SoundGameOver = D3DSound->LoadSound(hInstance,TEXT("GAMEOVER"),TEXT("SOUND"),false);
	m_SoundBack = D3DSound->LoadSound(hInstance,TEXT("GAMEBACK"),TEXT("SOUND"),true);
	D3DSound->PlaySound(m_SoundBack);

	//创建控件
	CRect rcCreate(0,0,0,0);
	m_btStart.ActiveWindow(rcCreate,WS_VISIBLE,IDC_START,&m_VirtualEngine,NULL);
	m_btStart.SetButtonImage(TextureManager->InitWithTexture(pD3DDevice,AfxGetInstanceHandle(),TEXT("BT_START"),TEXT("PNG")));

	m_btStart.GetClientRect(rcCreate);
	m_btStart.SetWindowPos(nWidth-180,nHeight,0,0,SWP_NOSIZE);

	m_ScoreView.ActiveWindow(rcCreate,0,0,&m_VirtualEngine,NULL);
	m_ScoreView.SetWindowPos((nWidth-357)/2,(nHeight-326)/2,0,0,SWP_NOSIZE);
}

VOID CGamePengDlg::DrawGameView( CD3DDevice * pD3DDevice, INT nWidth, INT nHeight )
{	
	if(Check_Image(m_pTextureBack))
		m_pTextureBack->DrawImage(pD3DDevice,0,0);

	if ( Check_Image(m_pTextureTime) )
		m_pTextureTime->DrawImage(pD3DDevice,10,15);

	if ( Check_Image(m_pTextureTimeThumb) )
	{
		int nWidth = m_nGameTime*m_pTextureTimeThumb->GetWidth()/GAME_TIME;
		m_pTextureTimeThumb->DrawImage(pD3DDevice,10,15,nWidth,m_pTextureTimeThumb->GetHeight(),0,0);
	}

	//游戏时间
	if( m_nGameTime!=0)
		DrawNumberString(pD3DDevice,m_pTextureTimeNumber,m_nGameTime,210,15);

	if ( m_bGameStart )
	{
		DrawNumberString(pD3DDevice,m_pTextureGameScore,m_nGameScore,560,220);

		//绘画棋子
		for(BYTE i=0;i<ROW_COUNT;i++) 
		{
			for(BYTE j=0;j<COL_COUNT;j++)
			{
				BYTE cbType=m_ChessInfo[i][j];

				if ( m_tagChooseInfo.bChoosed && m_tagChooseInfo.ptDownIndex.x==i && m_tagChooseInfo.ptDownIndex.y == j )
				{
					if( Check_Image(m_pTextureChoose) )
						m_pTextureChoose->DrawImage(pD3DDevice,m_ptPosition.x+i*ITEM_WIDTH,m_ptPosition.y+j*ITEM_HEIGHT);
					else pD3DDevice->FillRect(m_ptPosition.x+i*ITEM_WIDTH,m_ptPosition.y+j*ITEM_HEIGHT,ITEM_WIDTH,ITEM_HEIGHT,D3DCOLOR_XRGB(255,0,0));
				}

				if( cbType != INVALID_BYTE )
					m_SpriteChess[cbType].DrawImage(pD3DDevice,m_ptPosition.x+i*ITEM_WIDTH,m_ptPosition.y+j*ITEM_HEIGHT);
			}
		}

		CheckConnect();
	}
}

void CGamePengDlg::OnStartGame()
{
	m_bActionCount = 0;
	m_nBombFrame = 0;
	m_nBombAction = 0;
	m_nBatterCount = 0;
	m_nGameScore = 0;
	m_nGameTime = GAME_TIME;
	m_bPlayBatter = false;
	m_bGameStart = true;
	m_bGameEnd = false;
	ZeroMemory(m_ChessInfo,sizeof(m_ChessInfo));
	ZeroMemory(m_ptConnectChess,sizeof(m_ptConnectChess));
	ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));

	srand(unsigned int(time(NULL)));

	//填充棋盘
	while ( true )
	{
		for(BYTE i=0;i<ROW_COUNT;i++)
		{
			for(BYTE j=0;j<COL_COUNT;j++)
			{
				m_ChessInfo[i][j]=rand()%(TYPE_COUNT-1)+1;
			}
		}

		//提示连接
		memset(m_ptConnectChess,INVALID_BYTE,sizeof(m_ptConnectChess));
		m_GameLogic.CheckConnect(m_ChessInfo,m_ptConnectChess);

		//只要有连击就重新填充棋盘，直到棋盘的棋子没有可以相连的为止
		if(m_ptConnectChess[0].x==-1) break;
	}


	//开始音效
	D3DSound->PlaySound(m_SoundReady);

	m_ScoreView.ShowWindow(false);
	m_btStart.ShowWindow(false);
}

bool CGamePengDlg::CheckConnect()
{
	//提示连接
	memset(m_ptConnectChess,INVALID_BYTE,sizeof(m_ptConnectChess));
	m_GameLogic.CheckConnect(m_ChessInfo,m_ptConnectChess);

	//检测移动
	//若转换未完成 返回
	if(ActToStop()==false) return false;

	//检测棋盘的空位置
	m_bDrawMoveFinish=CheckBlank();
	
	//有移动则绘画移动
	if(!m_bDrawMoveFinish)
	{	
		ActToStop();

		return false;
	}

	//检测消去动画是否完成
	bool bEffectEnd=true;
	
	for(BYTE i=0;i<ALL_COUNT;i++)
	{
		if(m_ptConnectChess[i].x==-1) break;

		bool bOver = false;

		if ( m_ptConnectChess[i].x < 0 || m_ptConnectChess[i].y < 0)bOver = true;
		else bOver= SetBombEffect(m_ptConnectChess[i].x*ITEM_WIDTH+m_ptPosition.x,m_ptConnectChess[i].y*ITEM_HEIGHT+m_ptPosition.y);
		
		if(bOver==false)bEffectEnd=false;
	}

	//播放声音
	if( m_bPlayBatter )
	{
		m_nBatterCount++;
		TraceService->TraceString(TraceLevel_Debug,TEXT("连击=%d"),m_nBatterCount);
		m_bPlayBatter = false;

		//连击超出最大值默认最高连击音效
		if( m_nBatterCount >= CountArray(m_SoundCombo) )
			D3DSound->PlaySound(m_SoundCombo[CountArray(m_SoundCombo)-1]);
		else D3DSound->PlaySound(m_SoundCombo[m_nBatterCount]);
	}

	//动画完成，清除棋子
	if(bEffectEnd)
	{
		//计算得分
		m_GameLogic.CheckConnectScore(m_ChessInfo,m_ptConnectChess,m_nGameScore);

		for(BYTE i=0;i<ALL_COUNT;i++)
		{
			if(m_ptConnectChess[i].x==-1) break;

			//消去此位置的棋子
			m_ChessInfo[m_ptConnectChess[i].x][m_ptConnectChess[i].y]=0;
		}
		
		memset(m_ptConnectChess,INVALID_BYTE,sizeof(m_ptConnectChess));
	}

	return true;
}

bool CGamePengDlg::ActToStop()
{
	//无活动棋子
	if(m_bActionCount==0)
	{
		m_bDrawMoveFinish=true;
		return true;
	}

	//绘画移动
	for(BYTE i=0;i<m_bActionCount;i++)
	{
		m_bDrawMoveFinish=false;
		if(m_SpriteActionChess[i].DrawMoveSprite(&m_D3DDevice))	m_bMoveChessFinish[i]=true;
	}

	//等待动画全部绘画完成
	for(BYTE i=0;i<m_bActionCount;i++)
	{
		if(m_bMoveChessFinish[i]==false) return false;
	}

	//转为固定棋子
	for(BYTE i=0;i<m_bActionCount;i++)
	{
		int x=(m_SpriteActionChess[i].GetPos().x-m_ptPosition.x)/ITEM_WIDTH;;
		int y=(m_SpriteActionChess[i].GetPos().y-m_ptPosition.y)/ITEM_HEIGHT;;
		ASSERT(x<ROW_COUNT&&y<COL_COUNT);
		m_ChessInfo[x][y]=m_bActionChessType[i];

		if(i==m_bActionCount-1) m_bDrawMoveFinish=true;
	}

	//清除活动棋子
	if(m_bDrawMoveFinish)
	{
		m_bActionCount=0;
		for(BYTE i=0;i<ALL_COUNT;i++)
		{
			m_SpriteActionChess[i].Destory();
		}

		ZeroMemory(m_bMoveChessFinish,sizeof(m_bMoveChessFinish));
		m_GameLogic.CheckConnect(m_ChessInfo,m_ptConnectChess);
	}

	//判断是否需要还原
	if(m_tagChooseInfo.ptDownIndex!=m_tagChooseInfo.ptUpIndex&&m_GameLogic.IsValidMove(m_tagChooseInfo.ptDownIndex,m_tagChooseInfo.ptUpIndex,m_ChessInfo)==false&&m_bResumeFinish==false) 
	{
		m_bDrawMoveFinish=false;
		ResumeAction();

		return false;
	}
	else
	{
		ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
		//开启重置动画标志
		m_bResetEffect=true;
	}

	//非还原操作则重置动画
	if(m_bResetEffect==true&&m_bResumeFinish==false) 
	{		
		m_nBombAction = 0;
		m_nBombFrame = 0;
	}
	
	return true;
}


//左键按下消息
void CGamePengDlg::OnLButtonDown(UINT nFlags,CPoint point)
{
	//动画尚未完成 不允许移动
	if(m_bDrawMoveFinish==false || m_bGameEnd || !m_bGameStart ) return __super::OnLButtonDown(nFlags,point);

	//超出棋盘范围
	if(point.x<m_ptPosition.x||point.y<m_ptPosition.y||point.x>(m_ptPosition.x+ITEM_WIDTH*ROW_COUNT)||point.y>(m_ptPosition.y+ITEM_HEIGHT*COL_COUNT))
		return __super::OnLButtonDown(nFlags,point);

	//记录选择
	m_tagChooseInfo.bChoosed=true;
	m_tagChooseInfo.ptDownPoint.x=point.x;
	m_tagChooseInfo.ptDownPoint.y=point.y;
	m_tagChooseInfo.ptDownIndex.x=(m_tagChooseInfo.ptDownPoint.x-m_ptPosition.x)/ITEM_WIDTH;
	m_tagChooseInfo.ptDownIndex.y=(m_tagChooseInfo.ptDownPoint.y-m_ptPosition.y)/ITEM_HEIGHT;

	//选择的点无棋子(如正在移动的点)
	if(m_ChessInfo[m_tagChooseInfo.ptDownIndex.x][m_tagChooseInfo.ptDownIndex.y]==0)
	{
		ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
	}

	return __super::OnLButtonDown(nFlags,point);
}

//左键弹起消息
void CGamePengDlg::OnLButtonUp(UINT nFlags,CPoint point)
{
	//按下点无效
	if(m_tagChooseInfo.bChoosed==false || m_bGameEnd || !m_bGameStart )
	{
		//清除选择
		ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
		return __super::OnLButtonUp(nFlags,point);
	}

	m_nBatterCount = 0;

	//取得弹起坐标
	int xup=point.x;
	int yup=point.y;

	//转换为索引值
	m_tagChooseInfo.ptUpIndex.x=(xup-m_ptPosition.x)/ITEM_WIDTH;
	m_tagChooseInfo.ptUpIndex.y=(yup-m_ptPosition.y)/ITEM_HEIGHT;

	//按下和弹起在同一个棋子上则不动作
	if(m_tagChooseInfo.ptUpIndex.x==m_tagChooseInfo.ptDownIndex.x && m_tagChooseInfo.ptUpIndex.y==m_tagChooseInfo.ptDownIndex.y)
	{
		//清除选择
		m_tagChooseInfo.bChoosed=false;
		ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
		return;
	}
	else
	{
		//取得按下坐标
		int xdown=m_tagChooseInfo.ptDownPoint.x;
		int ydown=m_tagChooseInfo.ptDownPoint.y;

		//计算移动方向
		int xoff=xup>xdown?1:-1;
		int yoff=yup>ydown?1:-1;

		//x方向的移动大于y方向的移动
		if(  abs(xdown-xup) >= abs(ydown-yup) ) 
		{
			m_tagChooseInfo.ptUpIndex.x=m_tagChooseInfo.ptDownIndex.x+xoff;
			m_tagChooseInfo.ptUpIndex.y=m_tagChooseInfo.ptDownIndex.y;
		}
		else
		{
			m_tagChooseInfo.ptUpIndex.x=m_tagChooseInfo.ptDownIndex.x;
			m_tagChooseInfo.ptUpIndex.y=m_tagChooseInfo.ptDownIndex.y+yoff;
		}

		//非法点过滤,弹起点是正在移动的点
		if(m_ChessInfo[m_tagChooseInfo.ptUpIndex.x][m_tagChooseInfo.ptUpIndex.y]==0)
		{
			ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
			return __super::OnLButtonUp(nFlags,point);
		}

		//非法点过滤,超出棋盘
		if(m_tagChooseInfo.ptUpIndex.x<0||m_tagChooseInfo.ptUpIndex.x>=9||m_tagChooseInfo.ptUpIndex.y<0||m_tagChooseInfo.ptUpIndex.y>=9)
		{
			ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
			return __super::OnLButtonDown(nFlags,point);
		}

		//计算互换棋子的点坐标
		CPoint down(m_tagChooseInfo.ptDownIndex.x*48+m_ptPosition.x,m_tagChooseInfo.ptDownIndex.y*48+m_ptPosition.y);
		CPoint up(m_tagChooseInfo.ptUpIndex.x*48+m_ptPosition.x,m_tagChooseInfo.ptUpIndex.y*48+m_ptPosition.y);

		CString str;
		
		//按下点到弹起点
		m_bActionChessType[m_bActionCount]=m_ChessInfo[m_tagChooseInfo.ptDownIndex.x][m_tagChooseInfo.ptDownIndex.y];
		str.Format(TEXT("CHESS%d"),m_bActionChessType[m_bActionCount]);
		m_SpriteActionChess[m_bActionCount].LoadImage(&m_D3DDevice,AfxGetInstanceHandle(),str,TEXT("PNG"));
		m_SpriteActionChess[m_bActionCount].SetMovePath(down,up);
		m_bActionCount++;
		
		//弹起点到按下点
		m_bActionChessType[m_bActionCount]=m_ChessInfo[m_tagChooseInfo.ptUpIndex.x][m_tagChooseInfo.ptUpIndex.y];
		str.Format(TEXT("CHESS%d"),m_bActionChessType[m_bActionCount]);
		m_SpriteActionChess[m_bActionCount].LoadImage(&m_D3DDevice,AfxGetInstanceHandle(),str,TEXT("PNG"));
		m_SpriteActionChess[m_bActionCount].SetMovePath(up,down);
		m_bActionCount++;
		
		//清除原有棋子
		m_ChessInfo[m_tagChooseInfo.ptDownIndex.x][m_tagChooseInfo.ptDownIndex.y]=0;
		m_ChessInfo[m_tagChooseInfo.ptUpIndex.x][m_tagChooseInfo.ptUpIndex.y]=0;
		
		m_bResumeFinish=false;

		//清除选择
		m_tagChooseInfo.bChoosed=false;
	}

	return __super::OnLButtonDown(nFlags,point);
}

void CGamePengDlg::ResumeAction()
{
	//还原动画不重置效果
	m_bResetEffect=false;

	//计算互换棋子的点坐标
	CPoint down(m_tagChooseInfo.ptDownIndex.x*48+m_ptPosition.x,m_tagChooseInfo.ptDownIndex.y*48+m_ptPosition.y);
	CPoint up(m_tagChooseInfo.ptUpIndex.x*48+m_ptPosition.x,m_tagChooseInfo.ptUpIndex.y*48+m_ptPosition.y);

	//设置移动棋子
	CString str;

	//按下点到弹起点
	m_bActionChessType[m_bActionCount]=m_ChessInfo[m_tagChooseInfo.ptDownIndex.x][m_tagChooseInfo.ptDownIndex.y];
	str.Format(TEXT("CHESS%d"),m_bActionChessType[m_bActionCount]);
	m_SpriteActionChess[m_bActionCount].LoadImage(&m_D3DDevice,AfxGetInstanceHandle(),str,TEXT("PNG"));
	m_SpriteActionChess[m_bActionCount].SetMovePath(down,up);
	m_bActionCount++;
	
	//弹起点到按下点
	m_bActionChessType[m_bActionCount]=m_ChessInfo[m_tagChooseInfo.ptUpIndex.x][m_tagChooseInfo.ptUpIndex.y];
	str.Format(TEXT("CHESS%d"),m_bActionChessType[m_bActionCount]);
	m_SpriteActionChess[m_bActionCount].LoadImage(&m_D3DDevice,AfxGetInstanceHandle(),str,TEXT("PNG"));
	m_SpriteActionChess[m_bActionCount].SetMovePath(up,down);
	m_bActionCount++;

	//清除原有棋子
	m_ChessInfo[m_tagChooseInfo.ptDownIndex.x][m_tagChooseInfo.ptDownIndex.y]=0;
	m_ChessInfo[m_tagChooseInfo.ptUpIndex.x][m_tagChooseInfo.ptUpIndex.y]=0;

	m_bResumeFinish=true;
}

bool CGamePengDlg::CheckBlank()
{
	CString strResourceName;

	for(BYTE i=0;i<ROW_COUNT;i++)
	{
		for(BYTE j=0;j<COL_COUNT-1;j++)
		{
			if(m_ChessInfo[i][j]!=0&&m_ChessInfo[i][j+1]==0&&j+1<COL_COUNT)
			{
				m_bDrawMoveFinish=false;
				
				//开始位置
				int StartX=i*ITEM_WIDTH+m_ptPosition.x;
				int StartY=j*ITEM_HEIGHT+m_ptPosition.y;
				
				//停止位置
				int StopX=i*ITEM_WIDTH+m_ptPosition.x;
				int StopY=j*ITEM_HEIGHT+m_ptPosition.y;
				int y=j;
				
				do
				{
					y++;
				}while((m_ChessInfo[i][y+1]==0&&y+1<COL_COUNT));//可以继续下移
				
				StopY=y*ITEM_HEIGHT+m_ptPosition.y;

				//转为活动棋子
				m_bActionChessType[m_bActionCount]=m_ChessInfo[i][j];
				strResourceName.Format(TEXT("CHESS%d"),m_bActionChessType[m_bActionCount]);
				m_SpriteActionChess[m_bActionCount].LoadImage(&m_D3DDevice,AfxGetInstanceHandle(),strResourceName,TEXT("PNG"));

				//设置移动
				m_SpriteActionChess[m_bActionCount].SetMovePath(StartX,StartY,StopX,StopY,30);

				//移除棋子
				m_ChessInfo[i][j]=0;
				m_bActionCount++;

				//上方棋子下移
				for(BYTE k=1;k<9;k++)
				{
					if(j-k>0&&m_ChessInfo[i][j-k]!=0)
					{
						//转为活动棋子
						m_bActionChessType[m_bActionCount]=m_ChessInfo[i][j-k];
						strResourceName.Format(TEXT("CHESS%d"),m_bActionChessType[m_bActionCount]);
						m_SpriteActionChess[m_bActionCount].LoadImage(&m_D3DDevice,AfxGetInstanceHandle(),strResourceName,TEXT("PNG"));

						//设置移动
						m_SpriteActionChess[m_bActionCount].SetMovePath(StartX,StartY-ITEM_HEIGHT*(k+1),StopX,StopY-ITEM_HEIGHT*(k),30);

						//移除棋子
						m_ChessInfo[i][j-k]=0;
						m_bActionCount++;
					}
				}
			}
		}
	}

	//注入新棋子
	for(BYTE i=0;i<ROW_COUNT;i++)
	{
		if(m_ChessInfo[i][0]==0)
		{
			//转为活动棋子
			m_bActionChessType[m_bActionCount]=rand()%(TYPE_COUNT-1)+1;
			strResourceName.Format(TEXT("CHESS%d"),m_bActionChessType[m_bActionCount]);
			m_SpriteActionChess[m_bActionCount].LoadImage(&m_D3DDevice,AfxGetInstanceHandle(),strResourceName,TEXT("PNG"));

			//设置移动
			//开始位置
			int StartX=i*ITEM_WIDTH+m_ptPosition.x;
			int StartY=m_ptPosition.y-ITEM_HEIGHT;
			
			//停止位置
			int StopX=i*ITEM_WIDTH+m_ptPosition.x;
			int StopY=m_ptPosition.y;

			m_SpriteActionChess[m_bActionCount].SetMovePath(StartX,StartY,StopX,StopY,CHESS_DOWN_SPEED);

			//移除棋子
			m_bActionCount++;
		}
	}

	//在此清除选择信息
	if(m_bActionCount!=0)
	{
		ZeroMemory(&m_tagChooseInfo,sizeof(m_tagChooseInfo));
		m_nBombAction = 0;
		m_nBombFrame = 0;
	}

	return (m_bActionCount==0);
}

bool CGamePengDlg::SetBombEffect(int x,int y)
{
	if( m_nBombAction >= 1 ) return true;

	if ( Check_Image(m_pTextureBomb) )
	{
		int nWidth = m_pTextureBomb->GetWidth()/24;
		int nHeight = m_pTextureBomb->GetHeight(); 

		m_pTextureBomb->DrawImage(&m_D3DDevice,x,y,nWidth,nHeight,nWidth*m_nBombFrame,0,nWidth,nHeight);
	}

	if ( m_nBombFrame == 0 )
	{
		m_bPlayBatter = true;
	}

	if ( m_LapseBomb.GetLapseCount(33) > 0 )
	{
		m_nBombFrame++;
	}

	if( m_nBombFrame >= 24 )
	{
		m_bPlayBatter = false;
		m_nBombFrame = 0;
		m_nBombAction++;
	}

	return false;
}

void CGamePengDlg::OnEndGame()
{
	m_ScoreView.SetGameScore(m_nGameScore,m_pTextureGameScore);

	m_btStart.ShowWindow(true);
	m_ScoreView.ShowWindow(true);
}

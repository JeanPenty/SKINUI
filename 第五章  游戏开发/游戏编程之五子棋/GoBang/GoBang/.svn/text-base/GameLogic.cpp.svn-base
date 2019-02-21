#include "StdAfx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameLogic::CGameLogic()
{
	//设置变量
	memset(m_cbStepCount,0,sizeof(m_cbStepCount));
	memset(m_cbIdentifier,0,sizeof(m_cbIdentifier));
	memset(m_cbChessBorad,0,sizeof(m_cbChessBorad));

	m_cbAndroidColor = NO_CHESS;
	m_cbXCursor=255;
	m_cbYCursor=255;

	return;
}

//析构函数
CGameLogic::~CGameLogic()
{
}

//获取步数
BYTE CGameLogic::GetStepCount(BYTE cbColor)
{
	ASSERT((cbColor==BLACK_CHESS)||(cbColor==WHITE_CHESS));
	return m_cbStepCount[(cbColor==BLACK_CHESS)?0:1];
}

//获取棋谱
const tagChessManual * CGameLogic::GetLastChessManual()
{
	INT_PTR nManualCount=m_ChessManualInfo.GetCount();
	return (nManualCount>0)?&m_ChessManualInfo[nManualCount-1]:NULL;
}

//初始逻辑
void CGameLogic::InitGameLogic()
{
	//清理棋谱
	m_ChessManualInfo.RemoveAll();

	//棋子变量
	memset(m_cbStepCount,0,sizeof(m_cbStepCount));
	memset(m_cbIdentifier,0,sizeof(m_cbIdentifier));
	memset(m_cbChessBorad,0,sizeof(m_cbChessBorad));

	return;
}

//悔棋控制
bool CGameLogic::RegretChess(WORD wStepCount)
{
	//效验参数
	ASSERT(wStepCount<=(WORD)m_ChessManualInfo.GetCount());

	//变量定义
	tagChessManual * pChessManual=NULL;
	INT_PTR nManualCount=m_ChessManualInfo.GetCount();

	//悔棋操作
	for (WORD i=0;i<wStepCount;i++)
	{
		//变量定义
		pChessManual=&m_ChessManualInfo[nManualCount-i-1];

		//棋盘变量
		m_cbStepCount[(pChessManual->cbColor==BLACK_CHESS)?0:1]--;
		m_cbChessBorad[pChessManual->cbXPos][pChessManual->cbYPos]=NO_CHESS;
	}

	//删除棋谱
	m_ChessManualInfo.RemoveAt(nManualCount-wStepCount,wStepCount);

	return true;
}

//放置棋子
BYTE CGameLogic::PlaceChess(BYTE cbXPos, BYTE cbYPos, BYTE cbColor)
{
	//效验参数
	ASSERT((cbXPos<15)&&(cbYPos<15));
	ASSERT(m_cbChessBorad[cbXPos][cbYPos]==NO_CHESS);
	if ((cbXPos>=15)||(cbYPos>=15)) return false;
	if (m_cbChessBorad[cbXPos][cbYPos]!=NO_CHESS) return false;

	//禁手判断
	if (cbColor==BLACK_CHESS)
	{
	}

	//设置棋盘
	m_cbChessBorad[cbXPos][cbYPos]=cbColor;
	m_cbStepCount[(cbColor==BLACK_CHESS)?0:1]++;
	m_cbIdentifier[cbXPos][cbYPos]=(BYTE)(m_ChessManualInfo.GetCount()+1);

	//记录棋谱
	tagChessManual ChessManual;
	ChessManual.cbXPos=cbXPos;
	ChessManual.cbYPos=cbYPos;
	ChessManual.cbColor=cbColor;
	m_ChessManualInfo.Add(ChessManual);

	return m_cbIdentifier[cbXPos][cbYPos];
}

//胜利判断
bool CGameLogic::WinEstimate(BYTE cbXPos, BYTE cbYPos)
{
	//变量定义
	int nMoveWay[4][2]={{1,0},{0,1},{1,-1},{1,1}};
	BYTE cbChess=m_cbChessBorad[cbXPos][cbYPos];
	BYTE cbXPosTemp=0,cbYPosTemp=0,cbChessCount=0;

	//胜利判断
	for (int i=0;i<sizeof(nMoveWay)/sizeof(nMoveWay[0]);i++)
	{
		//设置变量
		cbChessCount=0;

		//正向计数
		cbXPosTemp=cbXPos;
		cbYPosTemp=cbYPos;
		do
		{
			//移动棋点
			cbXPosTemp+=nMoveWay[i][0];
			cbYPosTemp+=nMoveWay[i][1];
			if ((cbXPosTemp>=15)||(cbYPosTemp>=15)) break;
			if (m_cbChessBorad[cbXPosTemp][cbYPosTemp]!=cbChess) break;

			//累计棋数
			cbChessCount++;
			if (cbChessCount==4) return true;

		} while (true);

		//反向计数
		cbXPosTemp=cbXPos;
		cbYPosTemp=cbYPos;
		do
		{
			//移动棋点
			cbXPosTemp-=nMoveWay[i][0];
			cbYPosTemp-=nMoveWay[i][1];
			if ((cbXPosTemp>=15)||(cbYPosTemp>=15)) break;
			if (m_cbChessBorad[cbXPosTemp][cbYPosTemp]!=cbChess) break;

			//累计棋数
			cbChessCount++;
			if (cbChessCount==4) return true;

		} while (true);
	};

	return false;
}

void CGameLogic::AnalyseChessBoard()
{
 	if( Defense301() ) return;
 	if( AttackFourLink() ) return;
 	if( Defense4() ) return;
 	if( Attack301() ) return;
 	if( Attack201() ) return;
 	if( Defense02010() ) return;
 	if( Attack3() ) return;
 	if( Attack2() ) return;
 	if( Defense030() ) return;
 	if( Defense201() ) return;
 	if( Defense3() ) return;
 	if( Defense2() ) return;
 	if( Defense1() ) return;
}

bool CGameLogic::SetPlaceChess( BYTE cbXPos, BYTE cbYPos )
{
	if (m_cbChessBorad[cbXPos][cbYPos]==NO_CHESS&&(cbXPos>0&&cbXPos<15&&cbYPos>0&&cbYPos<15))
	{
		m_cbXCursor = cbXPos;
		m_cbYCursor = cbYPos;

		return true;
	}

	return false;
}

bool CGameLogic::Defense301()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j+1]==cbColor&&m_cbChessBorad[i-1][j-1]==cbColor&&m_cbChessBorad[i-3][j-3]==cbColor)
			{
				if (m_cbChessBorad[i-2][j-2]==0)
				{
					if( SetPlaceChess(i-2,j-2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+2][j+2]==cbColor&&m_cbChessBorad[i-1][j-1]==cbColor&&m_cbChessBorad[i-2][j-2]==cbColor)
			{
				if (m_cbChessBorad[i+1][j+1]==0)
				{
					if( SetPlaceChess(i+1,j+1)) return true;
				}
			}


			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor&&m_cbChessBorad[i-1][j]==cbColor&&m_cbChessBorad[i+3][j]==cbColor)
			{
				if (m_cbChessBorad[i+2][j]==0)
				{
					if( SetPlaceChess(i+2,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor&&m_cbChessBorad[i-2][j]==cbColor&&m_cbChessBorad[i+2][j]==cbColor)
			{
				if (m_cbChessBorad[i-1][j]==0)
				{
					if( SetPlaceChess(i-1,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor&&m_cbChessBorad[i][j-1]==cbColor&&m_cbChessBorad[i][j+3]==cbColor)
			{
				if (m_cbChessBorad[i][j+2]==0)
				{
					if( SetPlaceChess(i,j+2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor&&m_cbChessBorad[i][j-2]==cbColor&&m_cbChessBorad[i][j+2]==cbColor)
			{
				if (m_cbChessBorad[i][j-1]==0)
				{
					if( SetPlaceChess(i,j-1) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor&&m_cbChessBorad[i-1][j+1]==cbColor&&m_cbChessBorad[i+3][j-3]==cbColor)
			{
				if (m_cbChessBorad[i+2][j-2]==0)
				{
					if( SetPlaceChess(i+2,j-2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor&&m_cbChessBorad[i-2][j+2]==cbColor&&m_cbChessBorad[i+2][j-2]==cbColor)
			{
				if (m_cbChessBorad[i-1][j+1]==0)
				{
					if( SetPlaceChess(i-1,j+1) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::AttackFourLink()
{
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i-1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-2][j-2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-3][j-3]==0)
				{
					if( SetPlaceChess(i-3,j-3) ) return true;
				}
				else if (m_cbChessBorad[i+2][j+2]==0)
				{
					if( SetPlaceChess(i+2,j+2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j]==m_cbAndroidColor&&m_cbChessBorad[i-1][j]==m_cbAndroidColor&&m_cbChessBorad[i+2][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-2][j]==0)
				{
					if( SetPlaceChess(i-2,j) ) return true;
				}
				else if (m_cbChessBorad[i+3][j]==0)
				{
					if( SetPlaceChess(i,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i][j+1]==m_cbAndroidColor&&m_cbChessBorad[i][j-1]==m_cbAndroidColor&&m_cbChessBorad[i][j+2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j-2]==0)
				{
					if( SetPlaceChess(i,j-2) ) return true;
				}
				else if (m_cbChessBorad[i][j+3]==0)
				{
					if( SetPlaceChess(i,j+3) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i+2][j-2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+3][j-3]==0)
				{
					if( SetPlaceChess(i+3,j-3) ) return true;
				}
				else if (m_cbChessBorad[i-2][j+2]==0)
				{
					if( SetPlaceChess(i-2,j+2) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Defense4()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j+1]==cbColor&&m_cbChessBorad[i-1][j-1]==cbColor&&m_cbChessBorad[i-2][j-2]==cbColor)
			{
				if (m_cbChessBorad[i-3][j-3]==0)
				{
					if( SetPlaceChess(i-3,j-3) ) return true;
				}
				else if (m_cbChessBorad[i+2][j+2]==0)
				{
					if( SetPlaceChess(i+2,j+2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor&&m_cbChessBorad[i-1][j]==cbColor&&m_cbChessBorad[i+2][j]==cbColor)
			{
				if (m_cbChessBorad[i-2][j]==0)
				{
					if( SetPlaceChess(i-2,j) ) return true;
				}
				else if (m_cbChessBorad[i+3][j]==0)
				{
					if( SetPlaceChess(i+3,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor&&m_cbChessBorad[i][j-1]==cbColor&&m_cbChessBorad[i][j+2]==cbColor)
			{
				if (m_cbChessBorad[i][j-2]==0)
				{
					if( SetPlaceChess(i,j-2) ) return true;
				}
				else if (m_cbChessBorad[i][j+3]==0)
				{
					if( SetPlaceChess(i,j+3) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor&&m_cbChessBorad[i-1][j+1]==cbColor&&m_cbChessBorad[i+2][j-2]==cbColor)
			{
				if (m_cbChessBorad[i+3][j-3]==0)
				{
					if( SetPlaceChess(i+3,j-3) ) return true;
				}
				else if (m_cbChessBorad[i-2][j+2]==0)
				{
					if( SetPlaceChess(i-2,j+2) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Attack301()
{
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i-1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-3][j-3]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-2][j-2]==0)
				{
					if( SetPlaceChess(i-2,j-2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+2][j+2]==m_cbAndroidColor&&m_cbChessBorad[i-1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-2][j-2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+1][j+1]==0)
				{
					if( SetPlaceChess(i-2,j-2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j]==m_cbAndroidColor&&m_cbChessBorad[i-1][j]==m_cbAndroidColor&&m_cbChessBorad[i+3][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+2][j]==0)
				{
					if( SetPlaceChess(i+2,j) ) return true;
				}

			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j]==m_cbAndroidColor&&m_cbChessBorad[i-2][j]==m_cbAndroidColor&&m_cbChessBorad[i+2][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-1][j]==0)
				{
					if( SetPlaceChess(i-1,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i][j+1]==m_cbAndroidColor&&m_cbChessBorad[i][j-1]==m_cbAndroidColor&&m_cbChessBorad[i][j+3]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j+2]==0)
				{
					if( SetPlaceChess(i,j+2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i][j+1]==m_cbAndroidColor&&m_cbChessBorad[i][j-2]==m_cbAndroidColor&&m_cbChessBorad[i][j+2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j-1]==0)
				{
					if( SetPlaceChess(i,j-1) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i+3][j-3]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+2][j-2]==0)
				{
					if( SetPlaceChess(i+2,j-2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-2][j+2]==m_cbAndroidColor&&m_cbChessBorad[i+2][j-2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-1][j+1]==0)
				{
					if( SetPlaceChess(i-1,j+1) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Attack201()
{
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+2][j+2]==m_cbAndroidColor&&m_cbChessBorad[i-1][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+1][j+1]==0)
				{
					if( SetPlaceChess(i+1,j+1) ) return true;
				}
			}			

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i-2][j-2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-1][j-1]==0)
				{
					if( SetPlaceChess(i-1,j-1) ) return true;
				}
			}			

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j]==m_cbAndroidColor&&m_cbChessBorad[i-2][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-1][j]==0)
				{
					if( SetPlaceChess(i-1,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+2][j]==m_cbAndroidColor&&m_cbChessBorad[i-1][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+1][j]==0)
				{
					if( SetPlaceChess(i+1,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i][j+2]==m_cbAndroidColor&&m_cbChessBorad[i][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j+1]==0)
				{
					if( SetPlaceChess(i,j+1) ) return true;
				}			
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i][j+1]==m_cbAndroidColor&&m_cbChessBorad[i][j-2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j-1]==0)
				{
					if( SetPlaceChess(i,j-1) ) return true;
				}			
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+2][j-2]==m_cbAndroidColor&&m_cbChessBorad[i-1][j+1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+1][j-1]==0)
				{
					if( SetPlaceChess(i+1,j-1) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-2][j+2]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-1][j+1]==0)
				{
					if( SetPlaceChess(i-1,j+1) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Defense030()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j+1]==cbColor&&m_cbChessBorad[i-1][j-1]==cbColor)
			{
				if (m_cbChessBorad[i+2][j+2]==0&&m_cbChessBorad[i-2][j-2]==0)
				{
					if( SetPlaceChess(i+2,j+2) ) return true;
				}
			}			

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor&&m_cbChessBorad[i-1][j]==cbColor)
			{
				if (m_cbChessBorad[i-2][j]==0&&m_cbChessBorad[i+2][j]==0)
				{
					if( SetPlaceChess(i-2,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor&&m_cbChessBorad[i][j-1]==cbColor)
			{
				if (m_cbChessBorad[i][j-2]==0&&m_cbChessBorad[i][j+2]==0)
				{
					if( SetPlaceChess(i,j-2) ) return true;
				}			
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor&&m_cbChessBorad[i-1][j+1]==cbColor)
			{
				if (m_cbChessBorad[i-2][j+2]==0&&m_cbChessBorad[i+2][j-2]==0)
				{
					if( SetPlaceChess(i-2,j+2) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Defense02010()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+2][j+2]==cbColor&&m_cbChessBorad[i-1][j-1]==cbColor)
			{
				if (m_cbChessBorad[i+1][j+1]==0)
				{
					if (m_cbChessBorad[i+3][j+3]==0&&m_cbChessBorad[i-2][j-2]==0)
					{
						if( SetPlaceChess(i+1,j+1) ) return true;
					}
				}
			}			

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j+1]==cbColor&&m_cbChessBorad[i-2][j-2]==cbColor)
			{
				if (m_cbChessBorad[i-1][j-1]==0)
				{
					if (m_cbChessBorad[i+2][j+2]==0&&m_cbChessBorad[i-3][j-3]==0)
					{
						if( SetPlaceChess(i-1,j-1) ) return true;
					}
				}
			}			

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor&&m_cbChessBorad[i-2][j]==cbColor)
			{
				if (m_cbChessBorad[i-1][j]==0)
				{
					if (m_cbChessBorad[i-3][j]==0&&m_cbChessBorad[i+2][j]==0)
					{
						if( SetPlaceChess(i-1,j) ) return true;
					}
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+2][j]==cbColor&&m_cbChessBorad[i-1][j]==cbColor)
			{
				if (m_cbChessBorad[i+1][j]==0)
				{
					if (m_cbChessBorad[i-2][j]==0&&m_cbChessBorad[i+3][j]==0)
					{
						if( SetPlaceChess(i+1,j) ) return true;
					}
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+2]==cbColor&&m_cbChessBorad[i][j-1]==cbColor)
			{
				if (m_cbChessBorad[i][j+1]==0)
				{
					if (m_cbChessBorad[i][j-2]==0&&m_cbChessBorad[i][j+3]==0)
					{
						if( SetPlaceChess(i,j+1) ) return true;
					}	
				}	

			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor&&m_cbChessBorad[i][j-2]==cbColor)
			{
				if (m_cbChessBorad[i][j-1]==0)
				{
					if (m_cbChessBorad[i][j-3]==0&&m_cbChessBorad[i][j+2]==0)
					{
						if( SetPlaceChess(i,j-1) ) return true;
					}
				}			
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+2][j-2]==cbColor&&m_cbChessBorad[i-1][j+1]==cbColor)
			{
				if (m_cbChessBorad[i+1][j-1]==0)
				{
					if (m_cbChessBorad[i-2][j+2]==0&&m_cbChessBorad[i+3][j-3]==0)
					{
						if( SetPlaceChess(i+1,j-1) ) return true;
					}
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor&&m_cbChessBorad[i-2][j+2]==cbColor)
			{
				if (m_cbChessBorad[i-1][j+1]==0)
				{
					if (m_cbChessBorad[i-3][j+3]==0&&m_cbChessBorad[i+2][j-2]==0)
					{
						if( SetPlaceChess(i-1,j+1) ) return true;
					}
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Attack3()
{
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i-1][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+2][j+2]==0)
				{
					if( SetPlaceChess(i+2,j+2) ) return true;

				}
				else if (m_cbChessBorad[i-2][j-2]==0)
				{
					if( SetPlaceChess(i-2,j-2) ) return true;
				}
			}			

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j]==m_cbAndroidColor&&m_cbChessBorad[i-1][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-2][j]==0)
				{
					if( SetPlaceChess(i-2,j) ) return true;
				}
				else if (m_cbChessBorad[i+2][j]==0)
				{
					if( SetPlaceChess(i+2,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i][j+1]==m_cbAndroidColor&&m_cbChessBorad[i][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j-2]==0)
				{
					if( SetPlaceChess(i,j-2) ) return true;
				}
				else if (m_cbChessBorad[i][j+2]==0)
				{
					if( SetPlaceChess(i,j+2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j-1]==m_cbAndroidColor&&m_cbChessBorad[i-1][j+1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-2][j+2]==0)
				{
					if( SetPlaceChess(i-2,j+2) ) return true;

				}
				else if (m_cbChessBorad[i+2][j-2]==0)
				{
					if( SetPlaceChess(i+2,j-2) ) return true;
				}
			}

			if (m_cbChessBorad[i+1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i-1][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j]==0&&m_cbChessBorad[i+2][j+2]==0&&m_cbChessBorad[i-2][j-2]==0)
				{	
					if( SetPlaceChess(i,j) ) return true;
				}
			}

			if (m_cbChessBorad[i+1][j]==m_cbAndroidColor&&m_cbChessBorad[i-1][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j]==0&&m_cbChessBorad[i+2][j]==0&&m_cbChessBorad[i-2][j]==0)
				{
					if( SetPlaceChess(i,j) ) return true;
				}
			}


			if (m_cbChessBorad[i][j+1]==m_cbAndroidColor&&m_cbChessBorad[i][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j]==0&&m_cbChessBorad[i][j+2]==0&&m_cbChessBorad[i][j-2]==0)
				{
					if( SetPlaceChess(i,j) ) return true;
				}
			}

			if (m_cbChessBorad[i-1][j+1]==m_cbAndroidColor&&m_cbChessBorad[i+1][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j]==0&&m_cbChessBorad[i-2][j+2]==0&&m_cbChessBorad[i+2][j-2]==0)
				{
					if( SetPlaceChess(i,j) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Attack2()
{
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j+1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i+2][j+2]==0&&m_cbChessBorad[i-1][j-1]==0)
				{
					if( SetPlaceChess(i+2,j+2) ) return true;
				}
			}			

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i+1][j]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-1][j]==0&&m_cbChessBorad[i+2][j]==0)
				{
					if( SetPlaceChess(i-1,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i][j-1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i][j-2]==0&&m_cbChessBorad[i][j+1]==0)
				{
					if( SetPlaceChess(i,j+1) ) return true;
				}			
			}

			if (m_cbChessBorad[i][j]==m_cbAndroidColor&&m_cbChessBorad[i-1][j+1]==m_cbAndroidColor)
			{
				if (m_cbChessBorad[i-2][j+2]==0&&m_cbChessBorad[i+1][j-1]==0)
				{
					if( SetPlaceChess(i-2,j+2) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Defense201()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+2][j+2]==cbColor&&m_cbChessBorad[i-1][j-1]==cbColor)
			{
				if (m_cbChessBorad[i+1][j+1]==0)
				{
					if( SetPlaceChess(i+1,j+1) ) return true;				
				}
			}			

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j+1]==cbColor&&m_cbChessBorad[i-2][j-2]==cbColor)
			{
				if (m_cbChessBorad[i-1][j-1]==0)
				{
					if( SetPlaceChess(i-1,j-1) ) return true;
				}
			}			

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor&&m_cbChessBorad[i-2][j]==cbColor)
			{
				if (m_cbChessBorad[i-1][j]==0)
				{	
					if( SetPlaceChess(i-1,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+2][j]==cbColor&&m_cbChessBorad[i-1][j]==cbColor)
			{
				if (m_cbChessBorad[i+1][j]==0)
				{
					if( SetPlaceChess(i+1,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+2]==cbColor&&m_cbChessBorad[i][j-1]==cbColor)
			{
				if (m_cbChessBorad[i][j+1]==0)
				{
					if( SetPlaceChess(i,j+1) ) return true;	
				}	
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor&&m_cbChessBorad[i][j-2]==cbColor)
			{
				if (m_cbChessBorad[i][j-1]==0)
				{
					if( SetPlaceChess(i,j-1) ) return true;
				}			
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+2][j-2]==cbColor&&m_cbChessBorad[i-1][j+1]==cbColor)
			{
				if (m_cbChessBorad[i+1][j-1]==0)
				{
					if( SetPlaceChess(i+1,j-1) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor&&m_cbChessBorad[i-2][j+2]==cbColor)
			{
				if (m_cbChessBorad[i-1][j+1]==0)
				{
					if( SetPlaceChess(i-1,j+1) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Defense3()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j+1]==cbColor&&m_cbChessBorad[i-1][j-1]==cbColor)
			{
				if (m_cbChessBorad[i+2][j+2]==0)
				{
					if( SetPlaceChess(i+2,j+2) ) return true;
				}
			}			

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor&&m_cbChessBorad[i-1][j]==cbColor)
			{
				if (m_cbChessBorad[i-2][j]==0)
				{
					if( SetPlaceChess(i-2,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor&&m_cbChessBorad[i][j-1]==cbColor)
			{
				if (m_cbChessBorad[i][j-2]==0)
				{
					if( SetPlaceChess(i,j-2) ) return true;
				}			
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor&&m_cbChessBorad[i-1][j+1]==cbColor)
			{
				if (m_cbChessBorad[i-2][j+2]==0)
				{
					if( SetPlaceChess(i-2,j+2) ) return true;
				}
				else if (m_cbChessBorad[i+2][j-2]==0)
				{
					if( SetPlaceChess(i+2,j-2) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Defense2()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j]==cbColor)
			{
				if(m_cbChessBorad[i+2][j]==0)
				{
					if( SetPlaceChess(i+2,j) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i][j+1]==cbColor)
			{
				if (m_cbChessBorad[i][j+2]==0)
				{
					if( SetPlaceChess(i,j+2) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j+1]==cbColor)
			{
				if (m_cbChessBorad[i-1][j-1]==0)
				{
					if( SetPlaceChess(i-1,j-1) ) return true;
				}
			}

			if (m_cbChessBorad[i][j]==cbColor&&m_cbChessBorad[i+1][j-1]==cbColor)
			{
				if (m_cbChessBorad[i+2][j-2]==0)
				{
					if( SetPlaceChess(i+2,j-2) ) return true;
				}
			}
		}
	}

	return false;
}

bool CGameLogic::Defense1()
{
	BYTE cbColor = (m_cbAndroidColor==BLACK_CHESS)?WHITE_CHESS:BLACK_CHESS;

	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
			if (m_cbChessBorad[i][j]==cbColor)
			{
				if (m_cbChessBorad[i+1][j+1]==0&&(i+1>0&&i+1<15&&j+1>0&&j+1<15))
				{
					if( SetPlaceChess(i+1,j+1) ) return true;
				}
				else if (m_cbChessBorad[i-1][j-1]==0&&(i-1>0&&i-1<15&&j-1>0&&j-1<15))
				{
					if( SetPlaceChess(i-1,j-1) ) return true;
				}
				else if (m_cbChessBorad[i-1][j+1]==0&&(i-1>0&&i-1<15&&j+1>0&&j+1<15))
				{
					if( SetPlaceChess(i-1,j+1) ) return true;
				}
				else if ((m_cbChessBorad[i+1][j-1]==0&&(i+1>0&&i+1<15&&j-1>0&&j-1<15)))
				{
					if( SetPlaceChess(i+1,j-1) ) return true;
				}
				else if (m_cbChessBorad[i+1][j]==0&&(i+1>0&&i+1<15&&j>0&&j<15))
				{
					if( SetPlaceChess(i+1,j) ) return true;
				}
				else if (m_cbChessBorad[i-1][j]==0&&(i-1>0&&i-1<15&&j>0&&j<15))
				{
					if( SetPlaceChess(i-1,j) ) return true;
				}
				else if (m_cbChessBorad[i][j+1]==0&&(i>0&&i<15&&j+1>0&&j+1<15))
				{
					if( SetPlaceChess(i,j+1) ) return true;
				}
				else if ((m_cbChessBorad[i][j-1]==0&&(i>0&&i<15&&j-1>0&&j-1<15)))
				{
					if( SetPlaceChess(i,j-1) ) return true;
				}
			}
		}
	}

	return false;
}



//////////////////////////////////////////////////////////////////////////

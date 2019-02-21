#include "StdAfx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameLogic::CGameLogic()
{

}

//析构函数
CGameLogic::~CGameLogic()
{

}

//统计消去分数
void CGameLogic::CheckConnectScore(BYTE ChessInfo[ROW_COUNT][COL_COUNT],CPoint ConnectChessPos[ALL_COUNT],int& nGameScore)
{
	int nbChessType1=0,nbChessType2=0,nbChessType3=0,nbChessType4=0,nbChessType5=0,nbChessType6=0;

	for(BYTE i=0;i<ROW_COUNT*COL_COUNT;i++)
	{
		if(ConnectChessPos[i].x==-1) break;
		
		BYTE bChessType=ChessInfo[ConnectChessPos[i].x][ConnectChessPos[i].y];
	
		switch(bChessType)
		{
		case 1:nbChessType1++;break;
		case 2:nbChessType2++;break;
		case 3:nbChessType3++;break;
		case 4:nbChessType4++;break;
		case 5:nbChessType5++;break;
		case 6:nbChessType6++;break;
		default:
			{
				ASSERT(FALSE);
				break;
			}
		}
	}

	nGameScore += (nbChessType1 + nbChessType2 + nbChessType3 + nbChessType4 + nbChessType5 + nbChessType6)*100;
}

//判断移动后是否可以消除
bool CGameLogic::IsValidMove(CPoint start,CPoint stop,BYTE ChessInfo[ROW_COUNT][COL_COUNT])
{
	//效验点是否在棋盘范围内
	ASSERT(start.x>=0&&start.x<ROW_COUNT&&stop.x>=0&&stop.x<ROW_COUNT);
	ASSERT(start.y>=0&&start.y<COL_COUNT&&stop.y>=0&&stop.y<COL_COUNT);

	//放大数组
	BYTE tempChessInfo[13][13];
	memset(tempChessInfo,INVALID_BYTE,sizeof(tempChessInfo));

	//偏移位置
	start.x+=2;	start.y+=2;
	stop.x+=2;	stop.y+=2;

	//拷贝数据
	for(int i=2;i<11;i++) for(int j=2;j<11;j++)		tempChessInfo[i][j]=ChessInfo[i-2][j-2];


	//判断开始点移动后有无可消除
	BYTE x0=tempChessInfo[start.x-2][start.y];
	BYTE x1=tempChessInfo[start.x-1][start.y];
	BYTE x2=tempChessInfo[start.x][start.y];
	BYTE x3=tempChessInfo[start.x+1][start.y];
	BYTE x4=tempChessInfo[start.x+2][start.y];
	
	BYTE y0=tempChessInfo[start.x][start.y-2];
	BYTE y1=tempChessInfo[start.x][start.y-1];
	BYTE y2=tempChessInfo[start.x][start.y];
	BYTE y3=tempChessInfo[start.x][start.y+1];
	BYTE y4=tempChessInfo[start.x][start.y+2];

	if(	(x0==x1&&x1==x2)	||	 (x1==x2&&x2==x3)  ||   (x2==x3&&x3==x4) )  return true;
	if(	(y0==y1&&y1==y2)	||	 (y1==y2&&y2==y3)  ||   (y2==y3&&y3==y4) )  return true;

	//判断结束点移动后有无可消除
	x0=tempChessInfo[stop.x-2][stop.y];
	x1=tempChessInfo[stop.x-1][stop.y];
	x2=tempChessInfo[stop.x][stop.y];
	x3=tempChessInfo[stop.x+1][stop.y];
	x4=tempChessInfo[stop.x+2][stop.y];
	
	y0=tempChessInfo[stop.x][stop.y-2];
	y1=tempChessInfo[stop.x][stop.y-1];
	y2=tempChessInfo[stop.x][stop.y];
	y3=tempChessInfo[stop.x][stop.y+1];
	y4=tempChessInfo[stop.x][stop.y+2];

	if(	(x0==x1&&x1==x2)	||	 (x1==x2&&x2==x3)  ||   (x2==x3&&x3==x4) )  return true;
	if(	(y0==y1&&y1==y2)	||	 (y1==y2&&y2==y3)  ||   (y2==y3&&y3==y4) )  return true;

	return false;
}

//检测消去
void CGameLogic::CheckConnect(BYTE ChessInfo[ROW_COUNT][COL_COUNT],CPoint ConnectChessPos[ALL_COUNT])
{
	BYTE ConnectCount=0;//连接个数;
	BYTE tempCounter=0;//临时计数器

	//横向检测 
	for(BYTE y=0;y<ROW_COUNT;y++) 
	{
		for(BYTE x=0;x<COL_COUNT-2;)
		{
			if(ChessInfo[x][y]!=0)
			{
				if(	ChessInfo[x+1][y]==ChessInfo[x][y]&&ChessInfo[x+2][y]==ChessInfo[x][y])
				{
					ConnectChessPos[ConnectCount++].SetPoint(x,y);
					ConnectChessPos[ConnectCount++].SetPoint(x+1,y);
					ConnectChessPos[ConnectCount++].SetPoint(x+2,y);
					tempCounter+=3;//下次不再检测此3个棋子
					if(x+3<COL_COUNT) if(ChessInfo[x+3][y]==ChessInfo[x][y])//第4连
					{
						ConnectChessPos[ConnectCount++].SetPoint(x+3,y);
						tempCounter++;//增加计数
						if(x+4<COL_COUNT) if(ChessInfo[x+4][y]==ChessInfo[x][y])//第5连
						{
							ConnectChessPos[ConnectCount++].SetPoint(x+4,y);
							tempCounter++;//增加计数
							if(x+5<COL_COUNT) if(ChessInfo[x+5][y]==ChessInfo[x][y])//第6连
							{
								ConnectChessPos[ConnectCount++].SetPoint(x+5,y);
								tempCounter++;//增加计数
								if(x+6<COL_COUNT) if(ChessInfo[x+6][y]==ChessInfo[x][y])//第7连
								{
									ConnectChessPos[ConnectCount++].SetPoint(x+6,y);
									tempCounter++;//增加计数
									if(x+7<COL_COUNT) if(ChessInfo[x+7][y]==ChessInfo[x][y])//第8连
									{
										ConnectChessPos[ConnectCount++].SetPoint(x+7,y);
										tempCounter++;//增加计数
										if(x+8<COL_COUNT) if(ChessInfo[x+8][y]==ChessInfo[x][y])//第9连
										{
											ConnectChessPos[ConnectCount++].SetPoint(x+8,y);
											tempCounter++;//增加计数
										}
									}
								}	
							}
						}
					}
				}
			}
			if(tempCounter>0) x+=tempCounter;//跳过已检测的棋子,避免重复检测 (例如7连时,7连内会包含6连5连4连这样)
			else x++;
			tempCounter=0;
		}
	}

	//纵向检测
	tempCounter=0;
	for(BYTE x=0;x<ROW_COUNT;x++)
	{
		for(BYTE y=0;y<COL_COUNT-2;)
		{
			if(ChessInfo[x][y]!=0)
			{
				if(	ChessInfo[x][y+1]==ChessInfo[x][y]&&ChessInfo[x][y+2]==ChessInfo[x][y])
				{
					ConnectChessPos[ConnectCount++].SetPoint(x,y);
					ConnectChessPos[ConnectCount++].SetPoint(x,y+1);
					ConnectChessPos[ConnectCount++].SetPoint(x,y+2);
					
					tempCounter+=3;
					if(y+3<COL_COUNT) if(ChessInfo[x][y+3]==ChessInfo[x][y])//第4连
					{
						ConnectChessPos[ConnectCount++].SetPoint(x,y+3);
						tempCounter++;
						if(y+4<COL_COUNT) if(ChessInfo[x][y+4]==ChessInfo[x][y])//第5连	
						{
							ConnectChessPos[ConnectCount++].SetPoint(x,y+4);
							tempCounter++;
							if(y+5<COL_COUNT) if(ChessInfo[x][y+5]==ChessInfo[x][y])//第6连
							{
								ConnectChessPos[ConnectCount++].SetPoint(x,y+5);
								tempCounter++;
								if(y+6<COL_COUNT) if(ChessInfo[x][y+6]==ChessInfo[x][y])//第7连
								{
									ConnectChessPos[ConnectCount++].SetPoint(x,y+6);
									tempCounter++;//增加计数
									if(y+7<COL_COUNT) if(ChessInfo[x][y+7]==ChessInfo[x][y])//第8连
									{
										ConnectChessPos[ConnectCount++].SetPoint(x,y+7);
										tempCounter++;//增加计数
										if(y+8<COL_COUNT) if(ChessInfo[x][y+8]==ChessInfo[x][y])//第9连
										{
											ConnectChessPos[ConnectCount++].SetPoint(x,y+8);
											tempCounter++;//增加计数
										}
									}
								}	
							}
						}
					}
				}
			}
			if(tempCounter>0) y+=tempCounter;
			else y++;
			tempCounter=0;
		}
	}
}
//////////////////////////////////////////////////////////////////////////

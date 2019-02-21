#include "StdAfx.h"
#include "GameLogic.h"
#include <time.h>

CGameLogic::CGameLogic(void)
{
	m_clChessMap = NULL;
}

CGameLogic::~CGameLogic(void)
{
	for(int i=0; i < m_nRowCount; i++)
		SafeDeleteArray(m_clChessMap[i]);
	SafeDeleteArray(m_clChessMap);
}

void CGameLogic::SetChessMap(int nRowCount,int nColCount,int nMineCount)
{
	//释放内存
	if ( m_clChessMap != NULL )
	{
		for(int i=0; i < m_nRowCount; i++)
			SafeDeleteArray(m_clChessMap[i]);
		SafeDeleteArray(m_clChessMap);
	}

	//设置变量
	m_nRowCount = nRowCount;
	m_nColCount = nColCount;

	//申请空间
 	m_clChessMap = new tagCell*[nRowCount];
 	for (int i=0;i<nRowCount;i++)
 	{
 		m_clChessMap[i] = new tagCell[nColCount];
 	}

	//初始化赋值
	for (int i=0;i<nRowCount;i++)
	{
		for (int j=0;j<nColCount;j++)
		{
			m_clChessMap[i][j].bVisible = false;
			m_clChessMap[i][j].bFlag = false;
			m_clChessMap[i][j].bWhy = false;
			m_clChessMap[i][j].nCount = 0;
		}
	}

	int nMineCountTemp = 0;

	srand(unsigned int(time(NULL)));

	//先设置雷区分布,单元格为-1，表示为雷
	while ( nMineCountTemp != nMineCount )
	{
		int nRandx = rand()%nRowCount;
		int nRandy = rand()%nColCount;

		if ( m_clChessMap[nRandx][nRandy].nCount != -1 )
		{
			m_clChessMap[nRandx][nRandy].nCount = -1;
			nMineCountTemp++;
		}
	}

	//统计整个地图单元格显示附近雷的个数
	for (int i=0;i<nRowCount;i++)
	{
		for (int j=0;j<nColCount;j++)
		{
			if( m_clChessMap[i][j].nCount == 0)
			{
				for (int x=i-1;x<i+2;x++)
				{
					for (int y=j-1;y<j+2;y++)
					{
						if( x>=0 && x<nRowCount && y>=0 && y<nColCount)
						{
							if (m_clChessMap[x][y].nCount == -1 )
							{
								m_clChessMap[i][j].nCount++;
							}
						}
					}
				}
			}
		}
	}

	return;
}

void CGameLogic::ShowNullLand(int nRow,int nCol)
{
	for (int x=nRow-1;x<nRow+2;x++)
	{
		for (int y=nCol-1;y<nCol+2;y++)
		{
			if( x>=0 && x<m_nRowCount && y>=0 && y<m_nColCount)
			{
				if ( m_clChessMap[x][y].nCount == 0 && !m_clChessMap[x][y].bVisible )
				{
					m_clChessMap[x][y].bVisible = true;
					ShowNullLand(x,y);
				}

				m_clChessMap[x][y].bVisible = true;
			}
		}
	}
}

bool CGameLogic::CheckGameEnd()
{
	for (int i=0;i<m_nRowCount;i++)
	{
		for (int j=0;j<m_nColCount;j++)
		{
			if ( m_clChessMap[i][j].nCount == -1 )
			{
				if ( !m_clChessMap[i][j].bFlag )
				{
					return false;
				}
			}
		}
	}

	return true;
}

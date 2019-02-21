#pragma once

struct tagCell
{
	INT		nCount;				//显示雷数
	bool	bVisible;			//显示状态
	bool	bFlag;				//棋子标志
	bool	bWhy;				//问号标志			
};

//////////////////////////////////////////////////////////////////////////

class CGameLogic
{
protected:
	INT				m_nRowCount;
	INT				m_nColCount;

public:
	tagCell			**m_clChessMap;

public:
	CGameLogic(void);
	~CGameLogic(void);

	//设置地图
	void SetChessMap(int nRowCount,int nColCount,int nMineCount=15);
	//显示空地
	void ShowNullLand(int nRow,int nCol);
	//检查游戏结束
	bool CheckGameEnd();
};

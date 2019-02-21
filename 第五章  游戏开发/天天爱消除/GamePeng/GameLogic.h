#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#define  ROW_COUNT			9
#define  COL_COUNT			9

#define  ALL_COUNT			(ROW_COUNT*COL_COUNT)

#define  INVALID_BYTE		0xFF

struct tagChooseInfo
{
	bool		bChoosed;			//是否选择
	CPoint		ptDownPoint;		//鼠标按下的点
	CPoint		ptDownIndex;		//鼠标按下的点索引
	CPoint		ptUpIndex;			//鼠标弹起的点索引
};

//////////////////////////////////////////////////////////////////////////

//游戏逻辑类
class CGameLogic
{
	//函数定义
public:
	//构造函数
	CGameLogic();
	//析构函数
	virtual ~CGameLogic();

	//功能函数
public:
	//检查移动
	bool IsValidMove(CPoint start,CPoint stop,BYTE ChessInfo[ROW_COUNT][COL_COUNT]);
	//检测消去(返回一个消去点位置的数组)
	void CheckConnect(BYTE ChessInfo[ROW_COUNT][COL_COUNT],CPoint ConnectChessPos[ALL_COUNT]);
	//统计消去分数
	void CheckConnectScore(BYTE ChessInfo[ROW_COUNT][COL_COUNT],CPoint ConnectChessPos[ALL_COUNT],int& nGameScore);
};

//////////////////////////////////////////////////////////////////////////

#endif
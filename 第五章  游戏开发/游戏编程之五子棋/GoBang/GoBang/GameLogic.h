#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

//棋子颜色
#define NO_CHESS					0									//没有棋子
#define BLACK_CHESS					1									//黑色棋子
#define WHITE_CHESS					2									//白色棋子

//////////////////////////////////////////////////////////////////////////

//棋谱结构
struct tagChessManual
{
	BYTE							cbXPos;								//下棋位置
	BYTE							cbYPos;								//下棋位置
	BYTE							cbColor;							//棋子颜色
};

//////////////////////////////////////////////////////////////////////////

typedef CArray<tagChessManual,tagChessManual>		CChessManualArray;

//游戏逻辑类
class CGameLogic
{
	//棋谱变量
public:
	BYTE							m_cbStepCount[2];					//棋子数目
	BYTE							m_cbIdentifier[15][15];				//棋子标识
	BYTE							m_cbChessBorad[15][15];				//棋子信息

	//机器人信息
public:
	BYTE							m_cbAndroidColor;
	BYTE							m_cbXCursor;						//光标位置
	BYTE							m_cbYCursor;						//光标位置

	//棋谱变量
public:
	CChessManualArray				m_ChessManualInfo;					//棋谱信息

	//函数定义
public:
	//构造函数
	CGameLogic();
	//析构函数
	virtual ~CGameLogic();

	//信息函数
public:
	//获取步数
	BYTE GetStepCount(BYTE cbColor);
	//获取棋谱
	const tagChessManual * GetLastChessManual();

	//控制函数
public:
	//初始逻辑
	void InitGameLogic();
	//悔棋控制
	bool RegretChess(WORD wStepCount);
	//放置棋子
	BYTE PlaceChess(BYTE cbXPos, BYTE cbYPos, BYTE cbColor);

	//逻辑函数
public:
	//胜利判断
	bool WinEstimate(BYTE cbXPos, BYTE cbYPos);

	//机器人逻辑
public:
	//分析棋盘
	void AnalyseChessBoard();
	//设置棋子
	bool SetPlaceChess(BYTE cbXPos, BYTE cbYPos);

	//攻击部分
	bool AttackFourLink();
	bool Attack301();
	bool Attack201();
	bool Attack3();
	bool Attack2();

	//防御部分
	bool Defense301();
	bool Defense4();
	bool Defense030();
	bool Defense3();
	bool Defense02010();
	bool Defense201();
	bool Defense2();
	bool Defense1();
};

//////////////////////////////////////////////////////////////////////////

#endif

#pragma once
#include <atlimage.h>
#include "GameLogic.h"

#define Row_X		40
#define Row_Y		80

#define Cell_Width	35
#define Cell_Height	35

//图片类
class CImageEx : public CImage
{
public:
	CImageEx(){}
	~CImageEx(){}

	//加载图片
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName,LPCTSTR pszResourceType=TEXT("PNG"));

	bool SetAlphaBit();

};

//////////////////////////////////////////////////////////////////////////
class CGameFrame
{
protected:
	CImageEx				m_ImageBack;				//节点图片
	CImageEx				m_ImageNum[12];				//数字资源
	CImageEx				m_ImageClock;				//钟表资源
	CImageEx				m_ImageClockItem;			//数字资源
	CImageEx				m_ImageFlag;				//地雷资源

	CGameLogic				m_GameLogic;				//游戏逻辑
	INT						m_nRowCount;				//横排总数
	INT						m_nColCount;				//纵排总数
	INT						m_nMineCount;				//地雷总数
	INT						m_nCurMineCount;			//剩余雷数
	bool					m_bGameOver;				//游戏结束
	INT						m_nGameTimer;				//游戏时间

public:
	CGameFrame(void);
	virtual ~CGameFrame(void);

	//功能函数
public:
	//资源加载
	void OnInitResource();
	//设置地图
	void SetChessMap(int nRowCount,int nColCount,int nMineCount=15);
	//重新开始
	void ReStartGame();
	//渲染
	void OnRender(CDC*pDC,int nWidth,int nHeight);
	//绘制时钟
	void DrawClock( HDC hDC,int nXDrawPos,int nYDrawPos );
	//左键按下
	void OnLButtonDown(CPoint pt);
	//右键按下
	void OnRButtonDown(CPoint pt);
	//计时器消息
	void OnTimer(UINT_PTR nIDEvent);
	//绘制数字
	void DrawNumberString(HDC hDC, LONG lNumber, INT nXPos, INT nYPos,BYTE cbAlign=TA_LEFT);
};

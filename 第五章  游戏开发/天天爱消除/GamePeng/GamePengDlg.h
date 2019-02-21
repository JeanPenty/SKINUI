// GamePengDlg.h : 头文件
//

#pragma once
#include "ScoreView.h"
#include "GameLogic.h"
#include "SpriteItem.h"

#define  		ITEM_WIDTH			48			//棋子宽度
#define  		ITEM_HEIGHT			48			//棋子高度
	
#define  		TYPE_COUNT			7			//棋子种类
#define			CHESS_DOWN_SPEED	8			//下落速度

#define			GAME_TIME			60			//游戏总时间，单位秒

// CGamePengDlg 对话框
class CGamePengDlg : public CGameFrameView,public CNumberString
{
	//纹理
protected:
	CD3DTexture							* m_pTextureBack;						//背景纹理
	CD3DTexture							* m_pTextureBomb;						//爆炸纹理
	CD3DTexture							* m_pTextureTime;						//时间纹理
	CD3DTexture							* m_pTextureTimeThumb;					//时间纹理
	CD3DTexture							* m_pTextureTimeNumber;					//时间纹理
	CD3DTexture							* m_pTextureGameScore;					//时间纹理
	CD3DTexture							* m_pTextureChoose;						//时间纹理

	CD3DSprite							m_SpriteChess[TYPE_COUNT];				//精灵资源

protected:
	CVirtualButton						m_btStart;								//开始按钮
	CScoreView							m_ScoreView;							//积分窗口

protected:
	CPoint								m_ptPosition;							//棋盘位置
	CGameLogic							m_GameLogic;							//游戏逻辑
	INT									m_nGameScore;							//游戏积分
	bool								m_bGameStart;							//游戏开始
	bool								m_bGameEnd;								//游戏结束
	BYTE								m_ChessInfo[ROW_COUNT][COL_COUNT];		//棋盘信息
	CPoint								m_ptConnectChess[ALL_COUNT];			//此数组保存消去棋子的位置

	//动作变量
protected:
	bool								m_bResumeFinish;						//还原结束标志
	bool								m_bDrawMoveFinish;						//移动动画结束标志
	bool								m_bMoveChessFinish[ALL_COUNT];			//棋子移动结束标志

	BYTE								m_bActionCount;							//活动棋子数量
	BYTE								m_bActionChessType[ALL_COUNT];			//活动棋子类型
	CSpriteItem							m_SpriteActionChess[ALL_COUNT];			//活动棋子图片

	bool								m_bResetEffect;							//重设效果
	tagChooseInfo						m_tagChooseInfo;						//动作标识
	
	//爆炸变量
protected:
	CLapseCount							m_LapseBomb;							//爆炸计时器
	INT									m_nBombFrame;							//爆炸帧数
	int									m_nBombAction;							//爆炸动作	
	int									m_nBatterCount;							//连击数目				

	//音效变量
protected:
	HSTREAM								m_SoundCombo[6];						//连击音效
	bool								m_bPlayBatter;							//是否播放

	HSTREAM								m_SoundReady;							//准备音效
	HSTREAM								m_SoundGameOver;						//结束音效
	HSTREAM								m_SoundBack;							//背景音乐

	//计时器
protected:
	INT									m_nGameTime;
	CLapseCount							m_LapGameTime;

// 构造
public:
	CGamePengDlg(CWnd* pParent = NULL);	// 标准构造函数

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//界面函数
private:
	//调整控件
	virtual VOID RectifyControl(INT nWidth, INT nHeight);
	//动画驱动
	virtual VOID CartoonMovie();
	//配置界面
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//绘画界面
	virtual VOID DrawGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//消息映射
protected:
	//左键按下消息
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	//左键弹起消息
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);

	//功能函数
public:
	//游戏开始
	void OnStartGame();
	//游戏结束
	void OnEndGame();
	//设置爆炸
	bool SetBombEffect(int x,int y);

	//逻辑函数
public:
	//检查连接
	bool CheckConnect();
	//停止动作
	bool ActToStop();
	//检查空白
	bool CheckBlank();
	//复原动作
	void ResumeAction();

	DECLARE_MESSAGE_MAP()
};

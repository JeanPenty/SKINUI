#pragma once

#include "NumberString.h"

class CScoreView : public CVirtualWindow,public CNumberString
{
	//控件变量
protected:
	CVirtualButton					m_btOK;							//关闭按钮
	LONG							m_lGameScore;

	//资源变量
protected:
	CD3DTexture						m_TextureBack;					//积分视图
	CD3DTexture						* m_pTextureBack;					//积分视图

	//函数定义
public:
	//构造函数
	CScoreView(void);
	//析构函数
	virtual ~CScoreView(void);

	//系统事件
protected:
	//动画消息
	virtual VOID OnWindowMovie();
	//创建消息
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice);
	//销毁消息
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice);

	//重载函数
protected:
	//按钮事件
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);
	//键盘事件
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam);
	//绘画窗口
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);
	
public:
	void SetGameScore(LONG lGameScore,CD3DTexture * pD3DTexture);
	//关闭窗口
	void OnBnClickClose();
};

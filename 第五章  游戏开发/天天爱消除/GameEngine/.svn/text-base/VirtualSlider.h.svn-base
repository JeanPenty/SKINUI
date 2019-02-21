#ifndef VIRTUAL_SLIDER_HEAD_FILE
#define VIRTUAL_SLIDER_HEAD_FILE

#pragma once

#include "D3DTexture.h"
#include "VirtualWindow.h"
#include "GameEngineHead.h"

//滑块控件
//////////////////////////////////////////////////////////////////////////
class GAME_ENGINE_CLASS CVirtualSlider : public CVirtualWindow
{
protected:
	CD3DTexture					* m_pTextureBack;				//背景纹理
	CD3DTexture					* m_pTextureChannel;			//轨迹纹理
	CD3DTexture					* m_pTextureButton;				//按钮纹理

protected:
	INT 						m_nMin;							//最小范围
	INT 						m_nMax;							//最大范围
	INT							m_nPos;							//当前位置
	INT							m_nButtonX;						//按钮位置

	CRect						m_rcButtonRect;					//按钮区域
	bool						m_bMouseDown;					//按下标志

	//函数定义
public:
	//构造函数
	CVirtualSlider(void);
	//析构函数
	~CVirtualSlider(void);

	//系统事件
protected:
	//动画消息
	virtual VOID OnWindowMovie(){}
	//创建消息
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice){}
	//销毁消息
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice);

	//重载函数
protected:
	//鼠标事件
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);
	//键盘事件
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam){ return FALSE;}
	//绘画窗口
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);

	//功能函数
public:
	//设置纹理
	void SetTexture(CD3DTexture*,CD3DTexture*,CD3DTexture*);
	//设置范围
	void SetRange( int nMin, int nMax );
	//设置位置
	void SetPos( int nPos );

	//获取属性
public:
	//获取范围
	void GetRange( int& nMin, int& nMax ) const;
	//获取位置
	INT GetPos();

	//辅助函数
private:
	//更新矩形
	void UpdateRects();
};

#endif
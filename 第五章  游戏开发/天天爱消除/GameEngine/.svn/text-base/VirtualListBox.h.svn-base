#ifndef VIRTUAL_LIST_HEAD_FILE
#define VIRTUAL_LIST_HEAD_FILE

#pragma once

#include "VirtualWindow.h"
#include "D3DTexture.h"

struct tagListBoxItem
{
	TCHAR		strText[MAX_PATH];
	void		* pData;

	INT			nItemHeight;
	bool		bSelected;
	D3DCOLOR	D3DColor;
};
//////////////////////////////////////////////////////////////////////////
typedef CArray<tagListBoxItem*,tagListBoxItem*>			CListBoxItemArray;

class GAME_ENGINE_CLASS CVirtualListBox : public CVirtualWindow
{
protected:
	CListBoxItemArray					m_ListBoxItemArray;
	CD3DTexture							* m_pTextureBack;
	CRect								m_rcActive;

	//函数定义
public:
	//构造函数
	CVirtualListBox(void);
	//析构函数
	virtual ~CVirtualListBox(void);

	//系统事件
protected:
	//动画消息
	virtual VOID OnWindowMovie();
	//创建消息
	virtual VOID OnWindowCreate(CD3DDevice * pD3DDevice);
	//销毁消息
	virtual VOID OnWindowDestory(CD3DDevice * pD3DDevice);
	//位置消息
	virtual VOID OnWindowPosition(CD3DDevice * pD3DDevice);

	//重载函数
protected:
	//鼠标事件
	virtual BOOL OnEventMouse(UINT uMessage, UINT nFlags, INT nXMousePos, INT nYMousePos);
	//键盘事件
	virtual BOOL OnEventKeyboard(UINT uMessage, WPARAM wParam, LPARAM lParam);
	//绘画窗口
	virtual VOID OnEventDrawWindow(CD3DDevice * pD3DDevice, INT nXOriginPos, INT nYOriginPos);

public:
	int AddString(LPCTSTR lpszItem);

	void ResetContent();

	void SetTexture(CD3DTexture *pBack);
};

#endif
#pragma once

//////////////////////////////////////////////////////////////////////////
//	
//	
//	音乐列表，重绘ListBox，本次重绘的主要目的是绘制滚动条，同时处理播放的事情
//	
//////////////////////////////////////////////////////////////////////////
// CMusicList
#include "ScrollBarEx.h"
#include "BassMusic.h"

typedef map<int,BOOL>				CSelItemArray;
typedef map<int,tagMusicInfo>		CMusicInfoArray;

class CMusicList : public CListBox,public ISkinControl
{
	DECLARE_DYNAMIC(CMusicList)

	//音乐辅助
public:
	int								m_nPlayItem;			//正在播放歌曲的ID

protected:
	CScrollBarEx					m_VScrollBar;	
	int								m_nTop;					//滚动距离
	int								m_nPressItem;			//按下节点
	int								m_nHovenItem;			//高亮节点
	bool							m_bMouseTracking;		//鼠标跟踪
	CSelItemArray					m_SelItemArray;			//选中队列--多选属性时有效
	CMusicInfoArray					m_MusicInfoArray;		//列表信息

	//资源定义
protected:
	CImageEx 						* m_pBackImgN;			//正常资源
	CImageEx 						* m_pBackImgH;			//正常资源
	CImageEx 						* m_pSelectImg;			//选中资源
	CImageEx 						* m_pPlayedImg;			//选中资源

	//函数定义
public:
	//构造函数
	CMusicList(void);
	//析构函数
	~CMusicList(void);

	//继承函数
public:
	//
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	//绘制函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//消息循环
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//功能函数
public:
	//是否单选
	bool IsSingleSel();
	//获取当前选择---单选有效
	int GetCurSel() const;
	//设置当前选择--单选有效
	int SetCurSel(int nSelect);
	//获取选择---多选有效
	int GetSel(int nIndex) const; 
	//设置选择--多选有效
	int SetSel(int nIndex, BOOL bSelect = TRUE);
	//删除节点
	int DeleteString( UINT nIndex );
	//添加节点
	int AddString(LPCTSTR lpszItem);

	//资源加载
public:
	//正常背景
	BOOL SetBackNormalImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	//选中资源
	BOOL SetSelectImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	//选中资源
	BOOL SetPlayedImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	//节点高亮
	BOOL SetHovenImage(LPCTSTR lpszFileName, CONST LPRECT lpNinePart = NULL);
	
	//界面辅助
	//调整滚动条
	void AdjustScrollBarSize();
	//检查滚动
	void CheckScrollBarStatus();
	//获取客户区
	BOOL GetItemPartRect(CRect& rect);
	//滚动节点
	void Scroll(int cx, int cy);
	//获取总结点高度
	int GetContentViewHeight();
	//获取节点矩形
	BOOL GetItemRect(int nIndex, CRect& rect);

public:
	//绘制消息
	afx_msg void OnPaint();
	//鼠标右键
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);	
	//窗口销毁
	afx_msg void OnDestroy();
	//鼠标离开
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//创建消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//尺寸消息
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//重绘消息
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//滚动消息
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//鼠标滑轮滚动
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//左键按下
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//鼠标移动
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//左键双击
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
};



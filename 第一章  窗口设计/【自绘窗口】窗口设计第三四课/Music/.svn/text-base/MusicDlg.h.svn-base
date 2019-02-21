// MusicDlg.h : 头文件
//
/*
我的个人博客近期将继续推出MFC实例课程讲解，如果你对此感兴趣，欢迎访问我的博客主页，http://www.gymsaga.com/

			MFC专栏请进 --- http://www.gymsaga.com/category/project/developc/mfc

如果你有什么不懂的，或者我讲的地方有那些不对或者不恰当的地方，也欢迎你批评指正
*/
#pragma once

#include "DialogEx.h"
#include "ListBoxEx.h"
#include "HyperLink.h"

// CMusicDlg 对话框
class CMusicDlg : public CDialogEx
{
	//控件变量
protected:
	CButtonEx					m_btPrev;				//前一首按钮
	CButtonEx					m_btPlay;				//播放按钮
	CButtonEx					m_btPause;				//暂停按钮
	CButtonEx					m_btNext;				//下一首按钮
	CListBoxEx					m_ListMusic;			//播放列表
	CHyperLink					m_HyperLink;			//文字按钮

	//控件变量
protected:
	CImageEx					m_ImageDefault;			//默认音乐图标
	CString						m_StrMusicName;			//当前音乐名称

// 构造
public:
	CMusicDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MUSIC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//客户区绘制
	virtual void OnClientDraw(CDC*pDC,INT nWidth,INT nHeight);
	//最大化
	virtual	bool OnMaxSize();
	//绘制文字
	void DrawText( CDC* pDC, CRect rcText,LPCTSTR lpszText,UINT uFormat,INT nHeight=18,bool bBold=true,LPCTSTR lpszName=TEXT("微软雅黑") );

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

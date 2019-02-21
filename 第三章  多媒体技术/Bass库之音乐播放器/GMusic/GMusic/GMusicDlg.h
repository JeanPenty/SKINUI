// GMusicDlg.h : 头文件
//

#pragma once
#include"BaseDialog.h"
#include "WebPublicize.h"
#include "MusicList.h"
#include "BassMusic.h"
#include "SkinDlg.h"

typedef map<int,tagMusicInfo*>				CMusicManagerMap;

// CGMusicDlg 对话框
class CGMusicDlg : public CBaseDialog,public IMusicState
{
protected:
	CSkinButton						m_btOption;
	CSkinButton						m_btSkin;

	CSkinButton						m_btPrev;
	CSkinButton						m_btOpen;
	CSkinButton						m_btPause;
	CSkinButton						m_btLast;

	CSkinButton						m_btAdd;
	CSkinButton						m_btDel;

	CSkinButton						m_btMute;

	CWebPublicize					m_WebPublicize;
	CMusicList						m_ListMusic;
	CImageEx						* m_pImageDefaultRes;
	CSkinDlg						m_SkinDlg;

	CSkinSliderCtrl					m_scProgress;
	CSkinSliderCtrl					m_scVolume;
	CBassMusicEngine				*m_pBassMusic;

	CMusicManagerMap				m_MusicManager;

	HSTREAM							m_hStream;

// 构造
public:
	CGMusicDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GMUSIC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//网络歌曲回调---目前没用
	static void CALLBACK DOWNLOADPROC(const void *buffer, DWORD length, void *user);


	//接口继承
public:
	//正在播放
	virtual void OnPlaying(){}
	//暂停状态
	virtual void OnPause(){}
	//停止播放
	virtual void OnStop();
	//加/慢 速播放
	virtual void OnStalled(){}

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void DrawView(CDC*pDC,int nWidth,int nHeight);

	//绘制标签
	void DrawMusicInfo(CDC*pDC,int nWidth,int nHeight);
	//遍历目标
	void BrowerFolder(CString strDir, int nDepth);
	//获取当前选择
	int GetCurSel();
	//插入列表
	void InsertMusicList( LPCTSTR lpFilePath,LPCTSTR lpFileName );
	//更新音量
	void UpdateVolume();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedMusicLast();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedMusicAdd();
	afx_msg void OnBnClickedMusicDel();
	afx_msg void OnBnClickedMusicPrev();
	afx_msg void OnBnClickedMusicPlay();
	afx_msg void OnBnClickedMusicPause();
	afx_msg void OnBnClickedMusicMute();
	afx_msg void OnBnClickedSkin();

protected:
	DECLARE_MESSAGE_MAP()
};

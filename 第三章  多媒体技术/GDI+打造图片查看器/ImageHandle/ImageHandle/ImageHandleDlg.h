// ImageHandleDlg.h : 头文件
//

#pragma once
#include "BaseDialog.h"
#include "GdiPlusImage.h"

//本篇代码使用的SkinUI库，请到【http://www.gymsaga.com】第二章 仿QQ实例中进行 下载源码

// CImageHandleDlg 对话框
class CImageHandleDlg : public CBaseDialog
{
protected:
	CSkinButton						m_btOpen;				//打开按钮
	CSkinButton						m_btSave;				//保存按钮
	CSkinButton						m_btLeft;				//左旋按钮
	CSkinButton						m_btRight;				//右旋按钮
	CSkinButton						m_btSize;				//大小按钮
	CSkinButton						m_btLarge;				//放大按钮
	CSkinButton						m_btShrink;				//缩小按钮
	CSkinSliderCtrl					m_scAlpha;
	CGdiPlusImage					m_Image;

	CPoint							m_ptPos;

	int								m_nAngle;
	float							m_fScale;

// 构造
public:
	CImageHandleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IMAGEHANDLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual void DrawView(CDC*pDC,int nWidth,int nHeight);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickSize();
	afx_msg void OnBnClickLarge();
	afx_msg void OnBnClickShrink();
	afx_msg void OnBnClickOpen();
	afx_msg void OnBnClickSave();
	afx_msg void OnBnClickLeft();
	afx_msg void OnBnClickRight();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};

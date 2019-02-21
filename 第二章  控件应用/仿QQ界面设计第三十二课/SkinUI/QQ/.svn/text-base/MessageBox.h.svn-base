#ifndef INFORMATION_HEAD_FILE
#define INFORMATION_HEAD_FILE

#pragma once

#include "ShareControlHead.h"

//////////////////////////////////////////////////////////////////////////////////

//消息窗口
class SHARE_CONTROL_CLASS CInformation : public CSkinDialog
{
	//属性变量
protected:
	UINT							m_uType;							//消息类型
	CString							m_strString;						//提示消息
	CString							m_strCaption;						//信息标题

	//辅助变量
protected:
	UINT							m_nElapse;							//剩余时间
	UINT							m_nBtCount;							//按钮数目
	CRect							m_rcString;							//字符位置
	HINSTANCE						m_hResInstance;						//资源句柄

	//控件变量
protected:
	CSkinButton						m_btButton[3];						//按钮控件

	//函数定义
public:
	//构造函数
	CInformation(CWnd * pParentWnd=NULL);
	//析构函数
	virtual ~CInformation();

	//重载函数
protected:
	//初始化消息
	virtual BOOL OnInitDialog();
	//命令消息
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//功能函数
public:
	//显示消息
	INT ShowMessageBox(LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0);
	//显示消息
	INT ShowMessageBox(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0);

	//内部函数
private:
	//创建按钮
	VOID CreateBoxButton();

	//消息映射
protected:
	//绘画消息
	VOID OnPaint();
	//时间消息
	VOID OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//全局函数
extern "C" SHARE_CONTROL_CLASS INT ShowInformation(LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0);
extern "C" SHARE_CONTROL_CLASS INT ShowInformationEx(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType=MB_OK, UINT nElapse=0);

//////////////////////////////////////////////////////////////////////////////////

#endif
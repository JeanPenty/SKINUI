// CalcFrameDlg.h : 头文件
//

#pragma once
#include <map>
using namespace std;

#include "CAboutDlg.h"
#include "ListBoxEx.h"

enum enWindowStyle
{
	en_Normal,
	en_Science,
};

enum enCalcType
{
	en_Null,
	en_Add,
	en_Sub,
	en_Mul,
	en_Div,
	en_Pow,
	en_Yroot,
	en_Calc
};


typedef map<UINT,CPoint>	CPosition;

// CCalcFrameDlg 对话框
class CCalcFrameDlg : public CDialog
{
	enum
	{
		en_Record_Add,
		en_Record_Sub,
		en_Record_Mul,
		en_Record_Div,
		en_Record_Equal,
		en_Record_Sqrt,
		en_Record_Reciproc,
		en_Record_Sqr,
		en_Record_Pow,
		en_Record_Cube,
		en_Record_PowTen,
		en_Record_Cuberoot,
		en_Record_Yroot,
		en_Record_Log,
		en_Record_Int,
		en_Record_Sin,
		en_Record_Cos,
		en_Record_Tan,
		en_Record_Asin,
		en_Record_Acos,
		en_Record_Atan,
		en_Record_Sinh,
		en_Record_Cosh,
		en_Record_Tanh,
		en_Record_ln,
		en_Record_fact
	};

	//实现
protected:
	HICON								m_hIcon;				//窗口图标
	enWindowStyle						m_enWindowStyle;		//窗口样式
	enCalcType							m_enCalcType;			//计算方式
	CPosition							m_Position;				//控件位置
	CString								m_strOutPut;			//输出信息	
	CString								m_strButtonOld;			//之前按键
	CString								m_strResultOld;			//之前结果
	CString								m_strResult;			//统计信息				
	bool								m_bShowSave;			//显示存储						
	bool								m_bFront;				//最前显示	
	bool								m_bPressNumber;			//按数字键
	bool								m_bPressEnable;			//按键失效
	bool								m_bIsBaseCalc;			//当前操作
	CListBoxEx							m_ListSave;				//存储列表					

	//构造
public:
	CCalcFrameDlg(CWnd* pParent = NULL);	// 标准构造函数
	
	//继承函数
protected:
	//DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);	
	//初始化
	virtual BOOL OnInitDialog();
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//消息映射
public:
	//系统命令
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//界面绘制
	afx_msg void OnPaint();
	//
	afx_msg HCURSOR OnQueryDragIcon();
	//窗口大小
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	DECLARE_MESSAGE_MAP()

	//界面函数
public:
	//调整控件
	void RectifyControl(int nWidth, int nHeight);
	//
	bool GetCalc();
	//效验数据--将数字后面无效的0去除
	void CheckData(CString &strData);
	//插入记录
	void InsertRecord(BYTE cbType);

	void InsertSpeRecord( CString str );

	afx_msg void OnBnClickedBtJia();
	afx_msg void OnBnClickedBtJian();
	afx_msg void OnBnClickedBtCheng();
	afx_msg void OnBnClickedBtChu();
	afx_msg void OnBnClickedBtDengyu();
	afx_msg void OnBnClickedBtDaoshu();
	afx_msg void OnBnClickedBtPai();
	afx_msg void OnBnClickedBtPingfang();
	afx_msg void OnBnClickedBtCifang();
	afx_msg void OnBnClickedBtLifang();
	afx_msg void OnBnClickedBtShicifang();
	afx_msg void OnBnClickedBtJiecheng();
	afx_msg void OnBnClickedBtKailifang();
	afx_msg void OnBnClickedBtKailifangn();
	afx_msg void OnBnClickedBtLog();
	afx_msg void OnBnClickedBtInt();
	afx_msg void OnBnClickedBtSin();
	afx_msg void OnBnClickedBtCos();
	afx_msg void OnBnClickedBtTan();
	afx_msg void OnBnClickedBtAsin();
	afx_msg void OnBnClickedBtAcos();
	afx_msg void OnBnClickedBtAtan();
	afx_msg void OnBnClickedBtSinh();
	afx_msg void OnBnClickedBtCosh();
	afx_msg void OnBnClickedBtTanh();
	afx_msg void OnBnClickedBtLn();
	afx_msg void OnBnClickedBtC();
	afx_msg void OnBnClickedBtMc();
	afx_msg void OnBnClickedBtDaxie();
	LRESULT OnRecifyView(WPARAM wParam,LPARAM lParam);
};

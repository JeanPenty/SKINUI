// WeatherDlg.h : 头文件
//

#pragma once

#include "ParseJson.h"
#include "ServiceThread.h"
#include "HttpWeather.h"
#include "ImageEx.h"
#include "OptionDlg.h"

struct tagWeather
{
	int			m_nTp;
	int			m_nWt;
	int			m_nWd;
	int			m_nWp;
	int			m_nPs;
	int			m_nVb;
	int			m_nHd;
	TCHAR		szCity[64];
};

// CWeatherDlg 对话框
class CWeatherDlg : public CDialog,public CServiceThread
{
protected:
	CParseJson					* m_pParseJson;
	CHttpWeather				m_HttpWeather;
	tagWeather					m_Weather;
	COptionDlg					m_OptionDlg;

protected:
	CImageEx					m_pImageBack;
	CImageEx					m_ImageWeather;

	CString						m_strProvince;
	CString						m_strCity;

	bool						m_bLoadFinished;
// 构造
public:
	CWeatherDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CWeatherDlg();

// 对话框数据
	enum { IDD = IDD_WEATHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual bool OnEventThreadRun();

	int GetValue( CString strData );

	void DrawText(CDC*pDC,LPCTSTR lpszText,int nPosX,int nPosY,int nFlag=DT_RIGHT,int nSize=17,int Weight=FW_MEDIUM,COLORREF colText=RGB(255,255,255));
	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();

	//更新窗口
	void UpdateLayered();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickOption();
};

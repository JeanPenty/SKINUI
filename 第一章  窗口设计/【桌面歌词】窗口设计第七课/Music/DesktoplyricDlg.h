#ifndef LYRIC_HEAD_FILE
#define LYRIC_HEAD_FILE

#pragma once

#include <vector>
using namespace std;

// CDesktoplyricDlg 对话框
typedef vector<CString>			CArraylyric;

class CDesktoplyricDlg : public CDialog
{
	DECLARE_DYNAMIC(CDesktoplyricDlg)

	//变量定义
protected:
	HBITMAP						m_hMemBmp;				//内存画布
	BYTE						* m_pBits;				//图像数据
	DWORD						m_dwSize;				//图像大小
	DWORD 						m_dwEffWidth;			//效果宽度	
	INT							m_nFontSize;			//文字大小
	TCHAR 						m_szText[MAX_PATH];		//当前显示
	CArraylyric					m_Arraylyric;			//歌词容器

	//函数定义
public:
	//构造函数
	CDesktoplyricDlg(CWnd* pParent = NULL);
	//析构函数
	virtual ~CDesktoplyricDlg();

	//功能函数
public:
	//更新窗口
	void UpdateLayered();
	//绘制文字
	void DrawTextString(LPTSTR lpszText,CRect rc,COLORREF clr1,COLORREF clr2,UINT nFontSize=30,DWORD dwFlag=DT_CENTER|DT_VCENTER|DT_SINGLELINE,CFont* pFont=NULL);
	//文字阴影
	void DrawTextShadow(LPTSTR lpszText,CRect rc,COLORREF clrText,UINT nFontSize=30,DWORD dwFlag=DT_CENTER|DT_VCENTER|DT_SINGLELINE,CFont* pFont=NULL);
	//设置歌词
	void SetLyric(CString lpszText);
	//打开歌词
	void OpenLyric(LPCTSTR lpPath);

protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange* pDX); 
	//初始化
	virtual BOOL OnInitDialog();

	//消息映射
public:
	//窗口尺寸
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//计时消息
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//左键消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif
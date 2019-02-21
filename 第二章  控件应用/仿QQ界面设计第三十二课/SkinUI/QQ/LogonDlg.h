#pragma once

#include "PasswordControl.h"
#define	WM_USER_LOGON			WM_USER+0x01
// CLogonDlg 对话框

class CLogonDlg : public CSkinDialog,public IFlashContrlSink
{
	DECLARE_DYNAMIC(CLogonDlg)
protected:
	CImageEx						*m_pImageBack;
	CImageEx						*m_pImageFace;
	CImageEx						*m_pImageLogo;
	CImageEx						*m_pImageShadow;

	CSkinButton						m_btClose;
	CSkinButton						m_btMin;

	CSkinButton						m_btFindPass;
	CSkinButton						m_btApplyAcoount;

	CSkinButton						m_btRemPass;
	CSkinButton						m_btAutoLogon;

	CSkinButton						m_btLogon;
	CSkinButton						m_btState;

	CSkinComboBox					m_ComAccount;
	CSkinEdit						m_EtPassWord;
	CPasswordKeyboard				m_PasswordKeyboard;					//密码键盘

	CFlashControl					m_FlashControl;

	bool							m_bLogoning;
	CGIFImage						m_GifLogon;
	int								m_nFrameIndex;

public:
	CLogonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogonDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);
	virtual void OnDraw(CDC*pDC,int nWidth,int nHeight);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void LoadFlash( int nWidth, int nHeight );

	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	void ShowControl(int nCmdShow);

	LRESULT OnClickPass(WPARAM wParam, LPARAM lParam);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

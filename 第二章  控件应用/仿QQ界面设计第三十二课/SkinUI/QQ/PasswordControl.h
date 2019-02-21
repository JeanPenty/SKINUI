#ifndef PASSWORD_CONTROL_HEAD_FILE
#define PASSWORD_CONTROL_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////////////

//密码键盘
class CPasswordKeyboard : public CDialog,public ISkinControl
{
	//配置变量
protected:
	INT								m_nRandLine[4];						//随机数字
	INT								m_nItemCount[4];					//字符数目
	TCHAR							m_szKeyboradChar[4][2][14];			//键盘字符

	//键盘状态
protected:
	bool							m_bShiftStatus;						//按键状态
	bool							m_bCapsLockStatus;					//按键状态

	//状态变量
protected:
	WORD							m_wHoverRow;						//盘旋列数
	WORD							m_wHoverLine;						//盘旋行数
	bool							m_bMouseDown;						//按下状态

	//资源大小
protected:
	CSize							m_SizeImageItem1;					//资源大小
	CSize							m_SizeImageItem2;					//资源大小
	CSize							m_SizeImageItem3;					//资源大小
	CSize							m_SizeBackGround;					//背景大小
	CSize							m_SizeImageButton;					//资源大小

	CImageEx 						*m_pImageItem1;
	CImageEx 						*m_pImageItem2;
	CImageEx 						*m_pImageItem3;
	CImageEx						*m_pImageButton;
	CImageEx						*m_pImageBackGround;

	CSkinEdit						*m_pEdit;

	//函数定义
public:
	//构造函数
	CPasswordKeyboard();
	//析构函数
	virtual ~CPasswordKeyboard();

	//绑定函数
public:
	void SetBuddy(CSkinEdit*pEdit);

	//重载函数
protected:
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK() { return; }
	//取消消息
	virtual VOID OnCancel() { return; }

	//辅助函数
protected:
	//更新位置
	VOID SetCurrentStation(CPoint MousePoint);
	//虚拟编码
	WORD GetVirualKeyCode(WORD wHoverLine, WORD wHoverRow);

	//消息定义
protected:
	//界面绘画
	VOID OnNcPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//失去焦点
	VOID OnKillFocus(CWnd * pNewWnd);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif
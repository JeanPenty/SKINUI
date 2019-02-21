#pragma once

#include "ScrollBarEx.h"

enum BLCTRL_STYLE					// 好友列表控件风格
{
	BLC_BIG_ICON_STYLE,				// 大头像风格
	BLC_SMALL_ICON_STYLE,			// 小头像风格
	BLC_STANDARD_ICON_STYLE			// 标准头像风格
};

//子节点
class CBuddyItem
{
public:
	CBuddyItem(void);
	~CBuddyItem(void);

public:
	int							m_nID;						// 项ID
	CString						m_strQQNum;					// QQ号码
	CString						m_strNickName;				// 昵称
	CString						m_strMarkName;				// 备注
	CString						m_strSign;					// 签名
	BOOL						m_bOnline;					// 是否在线标志
	BOOL						m_bOnlineAnim;				// 上线动画标志
	int							m_nOnlineAnimState;			// 上线动画状态
	BOOL						m_bOfflineAnim;				// 下线动画标志
	BOOL						m_bHeadFlashAnim;			// 头像闪动动画标志
	int							m_nHeadFlashAnimState;		// 头像闪动动画状态
	CImageEx					* m_lpHeadImg;				// 头像图片
	BOOL						m_bGender;					// 性别
};

//根节点
class CBuddyRootItem
{
public:
	CBuddyRootItem(void);
	~CBuddyRootItem(void);

public:
	int					m_nID;								// 项ID
	CString				m_strName;							// 好友分组名称
	int					m_nCurCnt;							// 当前在线好友数
	int					m_nMaxCnt;							// 该好友分组的好友数
	BOOL				m_bExpand;							// 是否展开标志
	int					m_nHeadFlashAnim;					// 头像闪烁动画标志
	int					m_nHeadFlashAnimState;				// 头像闪烁动画状态
	vector<CBuddyItem *> m_arrBuddys;						// 该好友分组的好友项
};

//////////////////////////////////////////////////////////////////////////

class CBuddyListBox : public CWnd,public ISkinControl
{
protected:
	CToolTipCtrl m_ToolTipCtrl;
	CScrollBarEx m_VScrollBar;

	CImageEx * m_lpBgImg;
	CImageEx * m_lpBuddyTeamBgImgH;
	CImageEx * m_lpArrowImgN, * m_lpArrowImgH, * m_lpArrowImgS;
	CImageEx * m_lpExpArrowImgN, * m_lpExpArrowImgH, * m_lpExpArrowImgS;
	CImageEx * m_lpBuddyItemBgImgH, * m_lpBuddyItemBgImgS;
	CImageEx * m_lpHeadFrameImg;
	CImageEx * m_lpStdGGHeadImg;
	CImageEx * m_lpStdMMHeadImg;

	int m_nSelTeamIndex, m_nSelIndex;
	int m_nHoverTeamIndex, m_nHoverIndex;
	int m_nHoverSmallIconIndex;
	int m_nPressTeamIndex, m_nPressIndex;
	int m_nLeft, m_nTop;
	BOOL m_bMouseTracking;
	BLCTRL_STYLE m_nStyle;
	BOOL m_bShowBigIconInSel;
	int m_nBuddyTeamHeight;
	int m_nBuddyItemHeightInBig;
	int m_nBuddyItemHeightInSmall;
	int m_nBuddyItemHeightInStd;
	int m_nBuddyTeamPadding;
	int m_nBuddyItemPadding;
	CRect m_rcMargin;
	DWORD m_dwOnlineAnimTimerId;			// 上线动画计时器
	DWORD m_dwOfflineAnimTimerId;			// 下线动画计时器
	DWORD m_dwHeadFlashAnimTimerId;			// 头像闪动动画计时器
	int						m_nCurrentPos;
	vector<CBuddyRootItem *> m_arrBuddyTeamItems;

public:
	CBuddyListBox(void);
	~CBuddyListBox(void);

public:
	BOOL SetBgPic(LPCTSTR lpszFileName);
	BOOL SetBuddyTeamHotBgPic(LPCTSTR lpszFileName);
	BOOL SetBuddyItemHotBgPic(LPCTSTR lpszFileName, RECT * lpNinePart = NULL);
	BOOL SetBuddyItemSelBgPic(LPCTSTR lpszFileName, RECT * lpNinePart = NULL);
	BOOL SetHeadFramePic(LPCTSTR lpszFileName, RECT * lpNinePart = NULL);
	BOOL SetNormalArrowPic(LPCTSTR lpszFileName);
	BOOL SetHotArrowPic(LPCTSTR lpszFileName);
	BOOL SetSelArrowPic(LPCTSTR lpszFileName);
	BOOL SetNormalExpArrowPic(LPCTSTR lpszFileName);
	BOOL SetHotExpArrowPic(LPCTSTR lpszFileName);
	BOOL SetSelExpArrowPic(LPCTSTR lpszFileName);
	BOOL SetStdGGHeadPic(LPCTSTR lpszFileName);
	BOOL SetStdMMHeadPic(LPCTSTR lpszFileName);

	void SetStyle(BLCTRL_STYLE nStyle);
	void SetShowBigIconInSel(BOOL bShowBigIconInSel);
	void SetBuddyTeamHeight(int nHeight);
	void SetBuddyItemHeightInBigIcon(int nHeight);
	void SetBuddyItemHeightInSmallIcon(int nHeight);
	void SetBuddyItemHeightInStandardIcon(int nHeight);
	void SetBuddyTeamPadding(int nPadding);
	void SetBuddyItemPadding(int nPadding);
	void SetMargin(const RECT * lpMargin);

	int AddBuddyTeam(int nID);
	int InsertBuddyTeam(int nTeamIndex, int nID);
	BOOL DelBuddyTeam(int nTeamIndex);

	int AddBuddyItem(int nTeamIndex, int nID);
	int InsertBuddyItem(int nTeamIndex, int nIndex, int nID);
	BOOL DelBuddyItem(int nTeamIndex, int nIndex);

	void DelAllItems();

	void SetBuddyTeamID(int nTeamIndex, int nID);
	void SetBuddyTeamName(int nTeamIndex, LPCTSTR lpszText);
	void SetBuddyTeamMaxCnt(int nTeamIndex, int nMaxCnt);
	void SetBuddyTeamCurCnt(int nTeamIndex, int nCurCnt);
	void SetBuddyTeamExpand(int nTeamIndex, BOOL bExpand);

	int GetBuddyTeamID(int nTeamIndex);
	CString GetBuddyTeamName(int nTeamIndex);
	int GetBuddyTeamMaxCnt(int nTeamIndex);
	int GetBuddyTeamCurCnt(int nTeamIndex);
	BOOL IsBuddyTeamExpand(int nTeamIndex);

	void SetBuddyItemID(int nTeamIndex, int nIndex, int nID);
	void SetBuddyItemQQNum(int nTeamIndex, int nIndex, LPCTSTR lpszText);
	void SetBuddyItemNickName(int nTeamIndex, int nIndex, LPCTSTR lpszText);
	void SetBuddyItemMarkName(int nTeamIndex, int nIndex, LPCTSTR lpszText);
	void SetBuddyItemSign(int nTeamIndex, int nIndex, LPCTSTR lpszText);
	void SetBuddyItemGender(int nTeamIndex, int nIndex, BOOL bGender);
	BOOL SetBuddyItemHeadPic(int nTeamIndex, int nIndex, LPCTSTR lpszFileName, BOOL bGray);
	void SetBuddyItemHeadFlashAnim(int nTeamIndex, int nIndex, BOOL bHeadFlashAnim);
	void SetBuddyItemOnline(int nTeamIndex, int nIndex, BOOL bOnline, BOOL bAnim);

	int GetBuddyItemID(int nTeamIndex, int nIndex);
	CString GetBuddyItemQQNum(int nTeamIndex, int nIndex);
	CString GetBuddyItemNickName(int nTeamIndex, int nIndex);
	CString GetBuddyItemMarkName(int nTeamIndex, int nIndex);
	CString GetBuddyItemSign(int nTeamIndex, int nIndex);
	BOOL GetBuddyItemGender(int nTeamIndex, int nIndex);
	BOOL IsBuddyItemHasMsg(int nTeamIndex, int nIndex);

	int GetBuddyTeamCount();
	int GetBuddyItemCount(int nTeamIndex);

	BOOL GetItemIndexByID(int nID, int& nTeamIndex, int& nIndex);
	BOOL GetItemRectByIndex(int nTeamIndex, int nIndex, CRect& rect);
	
	void GetCurSelIndex(int& nTeamIndex, int& nIndex);
	BLCTRL_STYLE GetStyle();
	BOOL IsShowBigIconInSel();

	int GetSelTeamIndex(){ return m_nSelTeamIndex; }
	int GetSelIndex(){ return m_nSelIndex; }

	CBuddyRootItem * GetBuddyTeamByIndex(int nIndex);
	CBuddyItem * GetBuddyItemByIndex(int nTeamIndex, int nIndex);

private:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	BOOL OnEraseBkgnd(CDC*pDC);
	void OnPaint();
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnMouseLeave();
	void OnTimer(UINT_PTR nIDEvent);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnSize(UINT nType, int cx, int cy);
	void OnDestroy();

	void DrawBuddyTeam(CDC*pDC, int nIndex);
	void DrawBuddyItem(CDC*pDC, int nTeamIndex, int nIndex);
	void DrawBuddyItemInBigIcon(CDC*pDC, int nTeamIndex, int nIndex);
	void DrawBuddyItemInSmallIcon(CDC*pDC, int nTeamIndex, int nIndex);
	void DrawBuddyItemInStdIcon(CDC*pDC, int nTeamIndex, int nIndex);

	void HitTest(POINT pt, int& nTeamIndex, int& nIndex);

	void CheckScrollBarStatus();
	void Scroll(int cx, int cy);
	void EnsureVisible(int nTeamIndex, int nIndex);

	void SortBuddyTeam(int nTeamIndex, int nIndex);
	void OnTimer_HeadFlashAnim(UINT_PTR nIDEvent);	// 头像闪动动画
	void OnTimer_OnlineAnim(UINT_PTR nIDEvent);		// 上线动画
	void OnTimer_OfflineAnim(UINT_PTR nIDEvent);	// 下线动画

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg UINT OnGetDlgCode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

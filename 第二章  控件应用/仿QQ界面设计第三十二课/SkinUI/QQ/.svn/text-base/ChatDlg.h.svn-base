#pragma once

#include "SkinManager.h"
#include "BuddyListBox.h"
#include "ChatRichEdit.h"
#include "Expression.h"
// CChatDlg 对话框

struct tagMsgInfo
{
	bool		bFace;
	CString		StrDescribe;
};

typedef vector<tagMsgInfo>	CMsgInfoArray;

class CChatDlg : public CSkinManager,public IExpressionSink
{
	DECLARE_DYNAMIC(CChatDlg)
protected:
	CImageEx				* m_pFacePadding;
	
	CImageEx				* m_pQQShow1;
	CImageEx				* m_pQQShow2;

public:
	CBuddyItem				* m_pBuddyItem;

	CChatRichEdit			m_SendEdit;
	CChatRichEdit			m_RecEdit;

	//Font
	CSkinButton				m_btBold;
	CSkinButton				m_btItalic;
	CSkinButton				m_btUnderLine;
	CSkinButton				m_btColor;

	CSkinComboBox			m_comFont;
	CSkinComboBox			m_comSize;

	//功能按钮
	CSkinButton				m_btFun[8];
	CSkinButton				m_btMsg;
// 	CSkinButton				m_btFont;
// 	CSkinButton				m_btFace;
// 	CSkinButton				m_btRichFace;
// 	CSkinButton				m_btShake;
// 	CSkinButton				m_btCut;

	CSkinButton				m_btSend;
	CSkinButton				m_btSendArrow;
	CSkinButton				m_btCancel;

	CSkinToolBar			m_tbTool;

	CHARFORMAT2				m_cfRich;
	CExpressionControl *	m_pExpressionControl;				//表情窗口

	CMsgInfoArray			m_MsgInfoArray;

public:
	CChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChatDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	void InsertReciveMsg();

	void OnDestroy();
	virtual void OnCancel();
	BOOL EnumerateFonts();

	//窗口绘制
	virtual void DrawClientArea(CDC*pDC,int nWidth,int nHeight);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickFont();
	void OnCbnSelchangeFont();
	void OnCbnSelchangeSize();

	void SetRichFormat();

	static BOOL CALLBACK EnumFamScreenCallBackEx(ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* lpntm, int FontType, LPVOID pThis);
	//选择表情
	virtual VOID OnExpressionSelect(CExpression * pExpression, tagExpressionInfo * pExpressionInfo);

	DECLARE_MESSAGE_MAP()
};

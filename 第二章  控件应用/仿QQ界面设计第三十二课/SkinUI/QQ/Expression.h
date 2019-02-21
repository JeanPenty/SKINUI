#ifndef EXPRESSION_HEAD_FILE
#define EXPRESSION_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////////////
//类型定义

//类说明
class CExpression;
class CExpressionManager;
class CExpressionControl;

//表情信息
struct tagExpressionInfo
{
	INT								nLength[3];							//描述长度
	TCHAR							szExpression[3][8];					//表情描述
};

//解释结果
struct tagTranslateResult
{
	//数据变量
	INT								nStartPos;							//开始位置
	INT								nDescribeLen;						//描述长度

	//对象变量
	CExpression *					pExpressionItem;					//表情信息
};

//数组定义
typedef CArray<CExpression *,CExpression *>		CExpressionArray;					//表情数组

//////////////////////////////////////////////////////////////////////////////////

//表情接口
interface IExpressionSink
{
	//选择表情
	virtual VOID OnExpressionSelect(CExpression * pExpression, tagExpressionInfo * pExpressionInfo)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

//聊天表情
class CExpression
{
	//友元定义
	friend class CExpressionControl;
	friend class CExpressionManager;

	//变量定义
protected:
	WORD							m_wIndex;							//索引标志
	CGIFImage						m_ExpressionItem;					//表情资源
	tagExpressionInfo				m_ExpressionInfo;					//表情信息

	//函数定义
protected:
	//构造函数
	CExpression();
	//析构函数
	virtual ~CExpression();

	//功能函数
public:
	//获取索引
	WORD GetIndex() { return m_wIndex; }
	//获取信息
	tagExpressionInfo *GetExpressionInfo(){ return &m_ExpressionInfo; }
	//获取路径
	bool GetExpressionPath(LPTSTR pszImagePath, WORD wMaxCount);
	//设置表情
	bool SetExpressionInfo(WORD wIndex, tagExpressionInfo&ExpressionInfo);
};

//////////////////////////////////////////////////////////////////////////////////

//表情管理
class CExpressionManager
{
	//组件变量
protected:
	CExpressionArray				m_ExpressionArray;					//表情数组
	
	//静态变量
protected:
	static CExpressionManager *		m_pExpressionManager;				//对象指针

	//函数定义
public:
	//构造函数
	CExpressionManager();
	//析构函数
	virtual ~CExpressionManager();

	//功能函数
public:
	//加载表情
	bool LoadExpression();
	//解释表情
	bool TranslateString(LPCTSTR pszString, tagTranslateResult&TranslateResult);

	//表情信息
public:
	//表情数目
	WORD GetExpressionCount();
	//枚举表情
	CExpression * GetExpressionItem(WORD wIndex);

	//静态函数
public:
	//获取对象
	static CExpressionManager * GetInstance() { return m_pExpressionManager; }
};

//////////////////////////////////////////////////////////////////////////////////

//表情窗口
class CExpressionControl : public CDialog
{
	//变量定义
protected:
	WORD							m_wItemCount;							//表情数目
	WORD							m_wSelectIndex;							//选择索引

	//组件变量
protected:
	IExpressionSink *				m_pIExpressionSink;						//表情接口

	//函数定义
public:
	//构造函数
	CExpressionControl();
	//析构函数
	virtual ~CExpressionControl();

	//功能函数
public:
	//显示控件
	VOID ShowExpression(CWnd * pParentWnd, INT nXPos, INT nYPos, IExpressionSink * pIExpressionSink);

	//辅助函数
protected:
	//绘画头像
	VOID DrawExpression(CDC * pDC, WORD wItemIndex, bool bSelected);

	//消息函数
public:
	//重画消息
	VOID OnPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//焦点消息
	VOID OnKillFocus(CWnd * pNewWnd);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif
#include "StdAfx.h"
#include "Resource.h"
#include "Expression.h"

//////////////////////////////////////////////////////////////////////////////////
//宏定义

//位置定义
#define ITEM_SPACE					6									//子项间隙
#define BORAD_SPACE					2									//边框间隙
#define EXPRESSION_WIDTH			25									//表情宽度
#define EXPRESSION_HEIGHT			25									//表情高度

//颜色定义
#define COLOR_BORAD					RGB(0,75,151)						//边框颜色
#define COLOR_FRAME					RGB(0,75,151)						//边框颜色
#define COLOR_BACK_GROUND			RGB(250,250,250)					//背景颜色

//常量定义
#define MAX_ROW_COUNT				10									//列项数目
#define MAX_LINE_COUNT				8									//行项数目

//////////////////////////////////////////////////////////////////////////////////
//静态变量

CExpressionManager * CExpressionManager::m_pExpressionManager=NULL;		//对象指针

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CExpressionControl, CDialog)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CExpression::CExpression()
{
	//设置变量
	m_wIndex=INVALID_WORD;
	ZeroMemory(&m_ExpressionInfo,sizeof(m_ExpressionInfo));

	return;
}

//析构函数
CExpression::~CExpression()
{
}

//获取路径
bool CExpression::GetExpressionPath(LPTSTR pszImagePath, WORD wMaxCount)
{
	//工作目录
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	RenderEngine->GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//构造地址
	_sntprintf(pszImagePath,wMaxCount,TEXT("%s\\QQ\\Face\\%03d.GIF"),szDirectory,m_wIndex);

	return true;
}

//设置表情
bool CExpression::SetExpressionInfo(WORD wIndex, tagExpressionInfo&ExpressionInfo)
{
	//效验状态
	ASSERT(m_ExpressionItem.IsNull()==true);
	if (m_ExpressionItem.IsNull()==false) return false;

	//设置变量
	m_wIndex=wIndex;
	m_ExpressionInfo=ExpressionInfo;

	//获取路径
	TCHAR szImagePath[MAX_PATH]=TEXT("");
	GetExpressionPath(szImagePath,CountArray(szImagePath));

	//加载图片
	if (m_ExpressionItem.LoadFromFile(szImagePath)==false)
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CExpressionManager::CExpressionManager()
{
	//设置对象
	ASSERT(m_pExpressionManager==NULL);
	if (m_pExpressionManager==NULL) m_pExpressionManager=this;

	return;
}

//析构函数
CExpressionManager::~CExpressionManager()
{
	//删除对象
	for (INT_PTR i=0;i<m_ExpressionArray.GetCount();i++)
	{
		SafeDelete(m_ExpressionArray[i]);
	}

	//删除数组
	m_ExpressionArray.RemoveAll();

	//释放对象
	ASSERT(m_pExpressionManager==this);
	if (m_pExpressionManager==this) m_pExpressionManager=NULL;

	return;
}

//初始表情
bool CExpressionManager::LoadExpression()
{
	//工作目录
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	RenderEngine->GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//构造路径
	TCHAR szInfoFile[MAX_PATH]=TEXT("");
	_sntprintf(szInfoFile,CountArray(szInfoFile),TEXT("%s\\QQ\\Face\\Face.INI"),szDirectory);

	//变量定义
	WORD wIndex=0L;
	LPCTSTR pszItemKey[]={TEXT("CN"),TEXT("EN"),TEXT("PY")};

	//读取表情
	do
	{
		//变量定义
		bool bSuccess=false;
		TCHAR szItemName[16]=TEXT("");

		//变量定义
		tagExpressionInfo ExpressionInfo;
		ZeroMemory(&ExpressionInfo,sizeof(ExpressionInfo));

		//读取解释
		for (INT i=0;i<CountArray(ExpressionInfo.szExpression);i++)
		{
			//读取信息
			_sntprintf(szItemName,CountArray(szItemName),TEXT("%s%03d"),pszItemKey[i],wIndex);
			GetPrivateProfileString(TEXT("Face"),szItemName,TEXT(""),ExpressionInfo.szExpression[i],CountArray(ExpressionInfo.szExpression[i]),szInfoFile);

			//结果判断
			if (ExpressionInfo.szExpression[i][0]!=0)
			{
				bSuccess=true;
				ExpressionInfo.nLength[i]=lstrlen(ExpressionInfo.szExpression[i]);
			}
			else ExpressionInfo.nLength[i]=0;
		}

		//构造表情
		if (bSuccess==true)
		{
			//构造表情
			CExpression * pExpression=NULL;
			try
			{
				pExpression=new CExpression;
				pExpression->SetExpressionInfo(wIndex++,ExpressionInfo);
			}
			catch (...)
			{
				ASSERT(FALSE);
				SafeDelete(pExpression);
			}

			//插入数组
			m_ExpressionArray.Add(pExpression);
		}

		//完成判断
		if (bSuccess==false)
		{
			break;
		}

	} while (true);

	return true;
}

//解释表情
bool CExpressionManager::TranslateString(LPCTSTR pszString, tagTranslateResult&TranslateResult)
{
	//效验参数
	ASSERT((pszString!=NULL)&&(pszString[0]!=0));
	if ((pszString==NULL)||(pszString[0]==0)) return false;

	//变量定义
	INT nHandleLength=0;
	INT nStringLength=lstrlen(pszString);

	//解释操作
	for (INT i=0;i<nStringLength-1;i++)
	{
		//解释判断
		if (pszString[i]!=TEXT('/')) continue;

		//解释搜索
		for (INT_PTR j=0;j<m_ExpressionArray.GetCount();j++)
		{
			//获取表情
			CExpression * pExpression=m_ExpressionArray[j];
			tagExpressionInfo * pExpressionInfo=&pExpression->m_ExpressionInfo;

			//描述对比
			for (INT k=0;k<CountArray(pExpressionInfo->szExpression);k++)
			{
				//长度判断
				INT nInfoLength=pExpressionInfo->nLength[k];
				if ((nInfoLength<=0)||((nStringLength-1-i)<nInfoLength)) continue;

				//字符对比
				if (memcmp(pExpressionInfo->szExpression[k],&pszString[i+1],sizeof(TCHAR)*nInfoLength)==0)
				{
					//设置结果
					TranslateResult.nStartPos=i;
					TranslateResult.nDescribeLen=nInfoLength+1;
					TranslateResult.pExpressionItem=pExpression;

					return true;
				}
			}
		}
	}

	//设置结果
	ZeroMemory(&TranslateResult,sizeof(TranslateResult));

	return false;
}

//表情数目
WORD CExpressionManager::GetExpressionCount()
{
	return (WORD)m_ExpressionArray.GetCount();
}

//枚举表情
CExpression * CExpressionManager::GetExpressionItem(WORD wIndex)
{
	//效验参数
	ASSERT(wIndex<m_ExpressionArray.GetCount());
	if (wIndex>=m_ExpressionArray.GetCount()) return NULL;

	//获取表情
	return m_ExpressionArray[wIndex];
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CExpressionControl::CExpressionControl()
{
	//设置变量
	m_wItemCount=0;
	m_wSelectIndex=0xFFFF;

	return;
}

//析构函数
CExpressionControl::~CExpressionControl()
{
}

//显示控件
VOID CExpressionControl::ShowExpression(CWnd * pParentWnd, INT nXPos, INT nYPos, IExpressionSink * pIExpressionSink)
{
	//效验状态
	ASSERT((m_hWnd==NULL)&&(pIExpressionSink!=NULL));
	if ((m_hWnd!=NULL)||(pIExpressionSink==NULL)) return;

	//设置变量
	m_pParentWnd=pParentWnd;
	m_pIExpressionSink=pIExpressionSink;

	//获取对象
	ASSERT(CExpressionManager::GetInstance()!=NULL);
	CExpressionManager * pExpressionManager=CExpressionManager::GetInstance();

	//获取信息
	m_wSelectIndex=INVALID_WORD;
	m_wItemCount=pExpressionManager->GetExpressionCount();
	m_wItemCount=__min(MAX_ROW_COUNT*MAX_LINE_COUNT,m_wItemCount);

	//创建窗口
	AfxSetResourceHandle(AfxGetInstanceHandle());
	Create(IDD_EXPRESSION,pParentWnd);
	AfxSetResourceHandle(GetModuleHandle(NULL));

	//获取位置
	INT nXScreen=GetSystemMetrics(SM_CXSCREEN);
	INT nYScreen=GetSystemMetrics(SM_CYSCREEN);

	//计算位置
	INT nLineCount=(m_wItemCount+MAX_ROW_COUNT-1)/MAX_ROW_COUNT;
	INT nControlHeight=2*BORAD_SPACE+nLineCount*(EXPRESSION_HEIGHT+ITEM_SPACE)+ITEM_SPACE;
	INT nControlWidth=(EXPRESSION_WIDTH+ITEM_SPACE)*MAX_ROW_COUNT+ITEM_SPACE+2*BORAD_SPACE;

	//设置位置
	if ((nXPos+nControlWidth)>=nXScreen) nXPos=nXScreen-nControlWidth;
	SetWindowPos(&CWnd::wndTopMost,nXPos,nYPos-nControlHeight,nControlWidth,nControlHeight,SWP_NOZORDER|SWP_SHOWWINDOW);

	return;
}

//绘画头像
VOID CExpressionControl::DrawExpression(CDC * pDC, WORD wItemIndex, bool bSelected)
{
	//获取表情
	CExpressionManager * pExpressionManager=CExpressionManager::GetInstance();
	CExpression * pExpression=pExpressionManager->GetExpressionItem(wItemIndex);

	//位置计算
	INT nFrameWidth=EXPRESSION_WIDTH+ITEM_SPACE;
	INT nFrameHeight=EXPRESSION_HEIGHT+ITEM_SPACE;

	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(nFrameWidth,nFrameHeight,32);

	//绘画框架
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//绘画表情
	pBufferDC->FillSolidRect(0,0,nFrameWidth,nFrameHeight,COLOR_BACK_GROUND);
	pExpression->m_ExpressionItem.DrawImageFrame(pBufferDC,ITEM_SPACE/2,ITEM_SPACE/2,0L);

	//绘画边框
	COLORREF rcColor=(bSelected==true)?COLOR_FRAME:COLOR_BACK_GROUND;
	pBufferDC->Draw3dRect(0,0,nFrameWidth,nFrameHeight,rcColor,rcColor);

	//绘画界面
	INT nXIndex=(wItemIndex%MAX_ROW_COUNT);
	INT nYIndex=(wItemIndex/MAX_ROW_COUNT);
	pDC->BitBlt(nXIndex*nFrameWidth+BORAD_SPACE+ITEM_SPACE/2,nYIndex*nFrameHeight+BORAD_SPACE+ITEM_SPACE/2,nFrameWidth,nFrameHeight,pBufferDC,0,0,SRCCOPY);

	return;
}

//重画消息
VOID CExpressionControl::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//绘画准备
	CDC * pDC=CDC::FromHandle(ImageBuffer.GetDC());

	//绘画背景
	pDC->FillSolidRect(&rcClient,COLOR_BACK_GROUND);
	pDC->Draw3dRect(&rcClient,COLOR_BORAD,COLOR_BORAD);

	//绘画表情
	for (WORD i=0;i<m_wItemCount;i++)
	{
		DrawExpression(pDC,i,m_wSelectIndex==i);
	}

	//绘画界面
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDC,0,0,SRCCOPY);

	//清理资源
	ImageBuffer.ReleaseDC();

	return;
}

//绘画背景
BOOL CExpressionControl::OnEraseBkgnd(CDC * pDC)
{
	//更新窗口
	Invalidate(FALSE);
	UpdateWindow();

	return TRUE;
}

//焦点消息
VOID CExpressionControl::OnKillFocus(CWnd * pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	//注销窗口
	DestroyWindow();

	return;
}

//鼠标消息
VOID CExpressionControl::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//发送消息
	if (m_wSelectIndex!=INVALID_WORD)
	{
		//获取表情
		CExpressionManager * pExpressionManager=CExpressionManager::GetInstance();
		CExpression * pExpression=pExpressionManager->GetExpressionItem(m_wSelectIndex);

		//事件通知
		ASSERT(m_pIExpressionSink!=NULL);
		m_pIExpressionSink->OnExpressionSelect(pExpression,&pExpression->m_ExpressionInfo);

		//关闭窗口
		DestroyWindow();
	}

	return;
}

//光标消息
BOOL CExpressionControl::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//获取光标
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//计算位置
	WORD wCurrentItem=INVALID_WORD;
	INT nXPos=MousePoint.x-BORAD_SPACE-ITEM_SPACE;
	INT nYPos=MousePoint.y-BORAD_SPACE-ITEM_SPACE;

	//选择判断
	if ((nXPos>=0)&&(nYPos>=0)&&(nXPos<MAX_ROW_COUNT*(EXPRESSION_HEIGHT+ITEM_SPACE)))
	{
		wCurrentItem=nYPos/(EXPRESSION_HEIGHT+ITEM_SPACE)*MAX_ROW_COUNT+nXPos/(EXPRESSION_WIDTH+ITEM_SPACE);
		if (wCurrentItem>=m_wItemCount) wCurrentItem=INVALID_WORD;
	}

	//选择判断
	if (wCurrentItem!=m_wSelectIndex)
	{
		//变量定义
		CClientDC ClientDC(this);

		//当前选择
		if (wCurrentItem!=INVALID_WORD)
		{
			DrawExpression(&ClientDC,wCurrentItem,true);
		}

		//历史选择
		if (m_wSelectIndex!=INVALID_WORD)
		{
			DrawExpression(&ClientDC,m_wSelectIndex,false);
		}

		//设置变量
		m_wSelectIndex=wCurrentItem;
	}

	//设置光标
	if (m_wSelectIndex!=INVALID_WORD)
	{
		SetCursor(LoadCursor(GetModuleHandle(SKINUI_DLL_NAME),MAKEINTRESOURCE(8000)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//////////////////////////////////////////////////////////////////////////////////

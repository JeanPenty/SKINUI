#include "StdAfx.h"

#include "Resource.h"
#include "PasswordControl.h"

//////////////////////////////////////////////////////////////////////////////////

//位置定义
#define ITEM_POS_S					3									//按钮间距
#define ITEM_POS_X					8									//按钮位置
#define ITEM_POS_Y					8									//按钮位置

//关闭按钮
#define POS_BUTTON_X				5									//按钮位置
#define POS_BUTTON_Y				8									//按钮位置

//常量定义
#define ROW_BACK					0									//退格按钮
#define ROW_SHIFT					1									//切换按钮
#define ROW_CAPITAL					2									//大写按钮
#define ROW_CLOSE_KEY				3									//关闭按钮
#define LINE_FUNCTION				4									//功能按钮

//控件标识
#define IDC_BT_KEYBOARD				100									//键盘按钮
#define IDC_ED_PASSWORD				200									//密码控件

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPasswordKeyboard, CDialog)
	ON_WM_NCPAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CPasswordKeyboard::CPasswordKeyboard() : CDialog(IDD_PASSWORD_KEYBOARD)
{
	//设置变量
	m_nRandLine[0]=rand()%11;
	m_nRandLine[1]=rand()%10;
	m_nRandLine[2]=rand()%13;
	m_nRandLine[3]=rand()%13;

	//键盘状态
	m_bShiftStatus=false;
	m_bCapsLockStatus=false;

	//状态变量
	m_bMouseDown=false;
	m_wHoverRow=INVALID_WORD;
	m_wHoverLine=INVALID_WORD;

	//键盘字符
	m_nItemCount[0]=11;
	lstrcpyn(m_szKeyboradChar[0][0],TEXT("`1234567890"),CountArray(m_szKeyboradChar[0][0]));
	lstrcpyn(m_szKeyboradChar[0][1],TEXT("~!@#$%^&*()"),CountArray(m_szKeyboradChar[0][1]));

	//键盘字符
	m_nItemCount[1]=10;
	lstrcpyn(m_szKeyboradChar[1][0],TEXT("-=[]\\;',./"),CountArray(m_szKeyboradChar[1][0]));
	lstrcpyn(m_szKeyboradChar[1][1],TEXT("_+{}|:\"<>?"),CountArray(m_szKeyboradChar[1][1]));

	//键盘字符
	m_nItemCount[2]=13;
	lstrcpyn(m_szKeyboradChar[2][0],TEXT("abcdefghijklm"),CountArray(m_szKeyboradChar[2][0]));
	lstrcpyn(m_szKeyboradChar[2][1],TEXT("ABCDEFGHIJKLM"),CountArray(m_szKeyboradChar[2][1]));

	//键盘字符
	m_nItemCount[3]=13;
	lstrcpyn(m_szKeyboradChar[3][0],TEXT("nopqrstuvwxyz"),CountArray(m_szKeyboradChar[3][0]));
	lstrcpyn(m_szKeyboradChar[3][1],TEXT("NOPQRSTUVWXYZ"),CountArray(m_szKeyboradChar[3][1]));

	//加载资源
	m_pImageItem1 = m_pImageItem2 = m_pImageItem3 = NULL;

	m_pImageItem1 = RenderEngine->GetImage(TEXT("QQ\\PassWnd\\KEYBOARD_ITEM1.bmp"));
	m_pImageItem2 = RenderEngine->GetImage(TEXT("QQ\\PassWnd\\KEYBOARD_ITEM2.bmp"));
	m_pImageItem3 = RenderEngine->GetImage(TEXT("QQ\\PassWnd\\KEYBOARD_ITEM3.bmp"));

	//设置大小
	m_SizeImageItem1.SetSize(m_pImageItem1->GetWidth()/3,m_pImageItem1->GetHeight());
	m_SizeImageItem2.SetSize(m_pImageItem2->GetWidth()/3,m_pImageItem2->GetHeight());
	m_SizeImageItem3.SetSize(m_pImageItem3->GetWidth()/3,m_pImageItem3->GetHeight());

	//关闭按钮
	m_pImageButton = NULL;
	m_pImageButton = RenderEngine->GetImage(TEXT("QQ\\PassWnd\\BT_KEYBOARD_CLOSE.bmp"));
	m_SizeImageButton.SetSize(m_pImageButton->GetWidth()/3,m_pImageButton->GetHeight());

	//背景大小
	m_pImageBackGround = NULL;
	m_pImageBackGround = RenderEngine->GetImage(TEXT("QQ\\PassWnd\\PASSWORD_KEYBORAD_BK.bmp"));
	m_SizeBackGround.SetSize(m_pImageBackGround->GetWidth(),m_pImageBackGround->GetHeight());

	return;
}

//析构函数
CPasswordKeyboard::~CPasswordKeyboard()
{
	RenderEngine->RemoveImage(m_pImageItem1);
	RenderEngine->RemoveImage(m_pImageItem2);
	RenderEngine->RemoveImage(m_pImageItem3);
	RenderEngine->RemoveImage(m_pImageButton);
	RenderEngine->RemoveImage(m_pImageBackGround);
}

//消息解释
BOOL CPasswordKeyboard::PreTranslateMessage(MSG * pMsg)
{
	//大写锁键
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_CAPITAL))
	{
		//设置变量
		bool bCapsLockStatus=m_bCapsLockStatus;
		m_bCapsLockStatus=(GetKeyState(VK_CAPITAL)&0x0F)>0;

		//更新界面
		if (bCapsLockStatus!=m_bCapsLockStatus)
		{
			RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
		}

		return TRUE;
	}

	//切换按钮
	if ((pMsg->wParam==VK_SHIFT)&&(pMsg->message==WM_KEYUP)||(pMsg->message==WM_KEYDOWN))
	{
		//设置变量
		bool bShiftStatus=m_bShiftStatus;
		m_bShiftStatus=(GetKeyState(VK_SHIFT)&0xF0)>0;

		//更新界面
		if (bShiftStatus!=m_bShiftStatus)
		{
			RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
		}

		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//创建函数
BOOL CPasswordKeyboard::OnInitDialog()
{
	__super::OnInitDialog();

	//设置变量
	m_bMouseDown=false;
	m_wHoverRow=INVALID_WORD;
	m_wHoverLine=INVALID_WORD;

	//获取状态
	m_bShiftStatus=(GetKeyState(VK_SHIFT)&0xF0)>0;
	m_bCapsLockStatus=(GetKeyState(VK_CAPITAL)&0x0F)>0;

	//构造位置
	CRect rcWindow;
	rcWindow.SetRect(0,0,m_SizeBackGround.cx,m_SizeBackGround.cy);

	//移动窗口
	CalcWindowRect(&rcWindow,CWnd::adjustBorder);
	SetWindowPos(NULL,0,0,rcWindow.Width(),rcWindow.Height(),SWP_NOMOVE|SWP_NOZORDER);

	return FALSE;
}

//更新位置
VOID CPasswordKeyboard::SetCurrentStation(CPoint MousePoint)
{
	//变量定义
	WORD wHoverRow=INVALID_WORD;
	WORD wHoverLine=INVALID_WORD;

	//字符按钮
	if ((MousePoint.x>=ITEM_POS_X)&&(MousePoint.y>=ITEM_POS_Y))
	{
		//列数计算
		if (((MousePoint.x-ITEM_POS_X)%(m_SizeImageItem1.cx+ITEM_POS_S))<=m_SizeImageItem1.cx)
		{
			wHoverRow=(WORD)((MousePoint.x-ITEM_POS_X)/(m_SizeImageItem1.cx+ITEM_POS_S));
		}

		//行数计算
		if (((MousePoint.y-ITEM_POS_Y)%(m_SizeImageItem1.cy+ITEM_POS_S))<=m_SizeImageItem1.cy)
		{
			wHoverLine=(WORD)((MousePoint.y-ITEM_POS_Y)/(m_SizeImageItem1.cy+ITEM_POS_S));
		}

		//参数调整
		if (wHoverLine>=CountArray(m_nItemCount)) wHoverLine=INVALID_WORD;
		if ((wHoverLine==INVALID_WORD)||(wHoverRow>=m_nItemCount[wHoverLine])) wHoverRow=INVALID_WORD;
	}

	//功能按钮
	if ((wHoverLine<2)&&(wHoverRow==INVALID_WORD))
	{
		//变量定义
		INT nEndLine1=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*m_nItemCount[0];
		INT nEndLine2=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*m_nItemCount[1];

		//原点位置
		CPoint ButtonPoint[4];
		ButtonPoint[0].SetPoint(nEndLine1,ITEM_POS_Y);
		ButtonPoint[1].SetPoint(nEndLine2,ITEM_POS_Y+ITEM_POS_S+m_SizeImageItem3.cy);
		ButtonPoint[2].SetPoint(nEndLine2+ITEM_POS_S+m_SizeImageItem2.cx,ITEM_POS_Y+ITEM_POS_S+m_SizeImageItem3.cy);
		ButtonPoint[3].SetPoint(m_SizeBackGround.cx-m_SizeImageButton.cx-POS_BUTTON_X,POS_BUTTON_Y);

		//按钮区域
		CRect rcBack(ButtonPoint[0],m_SizeImageItem3);
		CRect rcShift(ButtonPoint[1],m_SizeImageItem2);
		CRect rcCapital(ButtonPoint[2],m_SizeImageItem2);
		CRect rcCloseKey(ButtonPoint[3],m_SizeImageButton);

		//退格按钮
		if (rcBack.PtInRect(MousePoint))
		{
			wHoverRow=ROW_BACK;
			wHoverLine=LINE_FUNCTION;
		}

		//切换按钮
		if (rcShift.PtInRect(MousePoint))
		{
			wHoverRow=ROW_SHIFT;
			wHoverLine=LINE_FUNCTION;
		}

		//大写按钮
		if (rcCapital.PtInRect(MousePoint))
		{
			wHoverRow=ROW_CAPITAL;
			wHoverLine=LINE_FUNCTION;
		}

		//关闭按钮
		if (rcCloseKey.PtInRect(MousePoint))
		{
			wHoverRow=ROW_CLOSE_KEY;
			wHoverLine=LINE_FUNCTION;
		}
	}

	//设置变量
	m_wHoverRow=wHoverRow;
	m_wHoverLine=wHoverLine;

	return;
}

//虚拟编码
WORD CPasswordKeyboard::GetVirualKeyCode(WORD wHoverLine, WORD wHoverRow)
{
	//功能建区
	if (wHoverLine==LINE_FUNCTION)
	{
		switch (wHoverRow)
		{
		case ROW_BACK: { return VK_BACK; }
		case ROW_SHIFT: { return VK_SHIFT; }
		case ROW_CAPITAL: { return VK_CAPITAL; }
		}
	}

	//字符建区
	if ((wHoverLine<CountArray(m_nItemCount))&&(wHoverRow<m_nItemCount[wHoverLine]))
	{
		//计算索引
		bool bLowerChar=true;
		if (m_bShiftStatus==true) bLowerChar=!bLowerChar;
		if ((wHoverLine>=2)&&(m_bCapsLockStatus==true)) bLowerChar=!bLowerChar;

		//获取字符
		INT nItemCount=m_nItemCount[wHoverLine];
		INT nCharRowIndex=(wHoverRow+m_nRandLine[wHoverLine])%nItemCount;
		TCHAR chChar=m_szKeyboradChar[wHoverLine][(bLowerChar==true)?0:1][nCharRowIndex];

		return chChar;
	}

	return 0;
}

//界面绘画
VOID CPasswordKeyboard::OnNcPaint()
{
	__super::OnNcPaint();

	//获取位置
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//绘画边框
	CWindowDC WindowDC(this);
	COLORREF crBoradFrame=m_colFrameNormal;
	WindowDC.Draw3dRect(0,0,rcWindow.Width(),rcWindow.Height(),crBoradFrame,crBoradFrame);

	return;
}

//绘画背景
BOOL CPasswordKeyboard::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CMemoryDC BufferDC(pDC,rcClient);

	//设置环境
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SelectObject(GetCtrlFont());

	//绘画背景
	m_pImageBackGround->DrawImage(&BufferDC,0,0);

	//字符按钮
	for (INT nLine=0;nLine<CountArray(m_nItemCount);nLine++)
	{
		//绘画子项
		for (INT nRow=0;nRow<m_nItemCount[nLine];nRow++)
		{
			//计算位置
			INT nXImageIndex=0;
			INT nCharItemIndex=(nRow+m_nRandLine[nLine])%m_nItemCount[nLine];
			if ((m_wHoverLine==nLine)&&(m_wHoverRow==nRow)) nXImageIndex=(m_bMouseDown==false)?1:2;

			//绘画子项
			INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*nRow;
			INT nYDrawPos=ITEM_POS_Y+(m_SizeImageItem1.cy+ITEM_POS_S)*nLine;
			m_pImageItem1->DrawImage(&BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem1.cx,m_SizeImageItem1.cy,nXImageIndex*m_SizeImageItem1.cx,0);

			//构造颜色
			INT nColorIndex=0;
			COLORREF crTextColor[2]={RGB(0,0,0),RGB(125,125,125)};

			//颜色计算
			if (m_bShiftStatus==true) nColorIndex=(nColorIndex+1)%CountArray(crTextColor);
			if ((m_bCapsLockStatus==true)&&(nLine>=2)) nColorIndex=(nColorIndex+1)%CountArray(crTextColor);

			//绘画字符
			BufferDC.SetTextColor(crTextColor[nColorIndex]);
			BufferDC.TextOut(nXDrawPos+5,nYDrawPos+9,&m_szKeyboradChar[nLine][0][nCharItemIndex],1);

			//绘画字符
			BufferDC.SetTextColor(crTextColor[(nColorIndex+1)%CountArray(crTextColor)]);
			BufferDC.TextOut(nXDrawPos+15,nYDrawPos+3,&m_szKeyboradChar[nLine][1][nCharItemIndex],1);
		}
	}

	//退格按钮
	{
		//资源位置
		INT nXImageIndex=0;
		if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_BACK)) nXImageIndex=(m_bMouseDown==false)?1:2;

		//绘画背景
		INT nYDrawPos=ITEM_POS_Y;
		INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*m_nItemCount[0];
		m_pImageItem3->DrawImage(&BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem3.cx,m_SizeImageItem3.cy,nXImageIndex*m_SizeImageItem3.cx,0);

		//绘画字符
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(nXDrawPos+20,ITEM_POS_Y+7,TEXT("←"),2);
	}

	//切换按钮
	{
		//资源位置
		INT nXImageIndex=(m_bShiftStatus==true)?1:0;
		if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_SHIFT)) nXImageIndex=(m_bMouseDown==false)?1:2;

		//绘画背景
		INT nYDrawPos=ITEM_POS_Y+ITEM_POS_S+m_SizeImageItem1.cx;
		INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*m_nItemCount[1];
		m_pImageItem2->DrawImage(&BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem2.cx,m_SizeImageItem2.cy,nXImageIndex*m_SizeImageItem2.cx,0);

		//切换按钮
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(nXDrawPos+5,ITEM_POS_Y+ITEM_POS_S+m_SizeImageItem1.cx+6,TEXT("Shift"),5);
	}

	//大写按钮
	{
		//资源位置
		INT nXImageIndex=(m_bCapsLockStatus==true)?1:0;
		if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_CAPITAL)) nXImageIndex=(m_bMouseDown==false)?1:2;

		//绘画背景
		INT nYDrawPos=ITEM_POS_Y+ITEM_POS_S+m_SizeImageItem1.cx;
		INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*m_nItemCount[1]+m_SizeImageItem2.cx+ITEM_POS_S;
		m_pImageItem2->DrawImage(&BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem2.cx,m_SizeImageItem2.cy,nXImageIndex*m_SizeImageItem2.cx,0);

		//大写按钮
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(nXDrawPos+8,ITEM_POS_Y+ITEM_POS_S+m_SizeImageItem1.cx+6,TEXT("Caps"),4);
	}

	//关闭按钮
	{
		//资源位置
		INT nXImageIndex=0;
		if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_CLOSE_KEY)) nXImageIndex=(m_bMouseDown==false)?1:2;

		//绘画背景
		INT nXDrawPos=rcClient.Width()-m_SizeImageButton.cx-POS_BUTTON_X;
		m_pImageButton->DrawImage(&BufferDC,nXDrawPos,POS_BUTTON_Y,m_SizeImageButton.cx,m_SizeImageButton.cy,nXImageIndex*m_SizeImageButton.cx,0);
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	return TRUE;
}

//失去焦点
VOID CPasswordKeyboard::OnKillFocus(CWnd * pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	//销毁窗口
	DestroyWindow();

	return;
}

//鼠标消息
VOID CPasswordKeyboard::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//取消捕获
	if (m_bMouseDown==true)
	{
		//取消捕获
		ReleaseCapture();

		//设置变量
		m_bMouseDown=false;

		//获取光标
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		ScreenToClient(&MousePoint);

		//更新位置
		WORD wHoverRow=m_wHoverRow;
		WORD wHoverLine=m_wHoverLine;
		SetCurrentStation(MousePoint);

		//点击处理
		if ((m_wHoverRow==wHoverRow)&&(m_wHoverLine==wHoverLine))
		{
			//关闭按钮
			if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_CLOSE_KEY))
			{
				//设置焦点
				if ( m_pEdit != NULL && m_pEdit->GetSafeHwnd() != NULL )
				{
					m_pEdit->SetFocus();
				}

				//销毁窗口
				DestroyWindow();

				return;
			}

			//虚拟编码
			WORD wViraulCode=GetVirualKeyCode(m_wHoverLine,m_wHoverRow);

			//按钮处理
			switch (wViraulCode)
			{
			case VK_SHIFT:		//切换按钮
				{
					//设置变量
					m_bShiftStatus=!m_bShiftStatus;

					break;
				}
			case VK_CAPITAL:	//大写按钮
				{
					//变量定义
					INPUT Input[2];
					ZeroMemory(Input,sizeof(Input));

					//设置变量
					Input[1].ki.dwFlags=KEYEVENTF_KEYUP;   
					Input[0].type=Input[1].type=INPUT_KEYBOARD;
					Input[0].ki.wVk=Input[1].ki.wVk=wViraulCode;

					//模拟输入
					SendInput(CountArray(Input),Input,sizeof(INPUT));

					break;
				}
			default:			//默认按钮
				{
					//设置变量
					m_bShiftStatus=(GetKeyState(VK_SHIFT)&0xF0)>0;

					//发送消息
					if ( m_pEdit != NULL && m_pEdit->GetSafeHwnd() != NULL )
					{
						m_pEdit->SetDefaultTextMode(FALSE);
						m_pEdit->SendMessage(WM_CHAR,wViraulCode,0L);
					}

					break;
				}
			}
		}

		//更新界面
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//鼠标消息
VOID CPasswordKeyboard::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//点击按钮
	if ((m_wHoverLine!=INVALID_WORD)&&(m_wHoverRow!=INVALID_WORD))
	{
		//捕获鼠标
		SetCapture();

		//设置变量
		m_bMouseDown=true;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//光标消息
BOOL CPasswordKeyboard::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//获取光标
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//更新位置
	WORD wHoverRow=m_wHoverRow;
	WORD wHoverLine=m_wHoverLine;
	SetCurrentStation(MousePoint);

	//更新界面
	if ((m_wHoverRow!=wHoverRow)||(m_wHoverLine!=wHoverLine))
	{
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//设置光标
	if ((m_wHoverRow!=INVALID_WORD)&&(m_wHoverLine!=INVALID_WORD))
	{
		SetCursor(LoadCursor(GetModuleHandle(SKINUI_DLL_NAME),MAKEINTRESOURCE(8000)));
		return true;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

void CPasswordKeyboard::SetBuddy( CSkinEdit*pEdit )
{
	m_pEdit = pEdit;
}

//////////////////////////////////////////////////////////////////////////////////

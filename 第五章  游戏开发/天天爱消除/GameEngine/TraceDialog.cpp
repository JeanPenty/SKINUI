// TraceDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TraceDialog.h"
#include "resource.h"

// CTraceDialog 对话框


IMPLEMENT_DYNAMIC(CTraceRichEdit, CRichEditCtrl)
IMPLEMENT_DYNAMIC(CTraceDialog, CDialog)

//////////////////////////////////////////////////////////////////////////
CTraceRichEdit::CTraceRichEdit()
{
}

CTraceRichEdit::~CTraceRichEdit()
{
}


BEGIN_MESSAGE_MAP(CTraceRichEdit, CRichEditCtrl)
END_MESSAGE_MAP()

bool CTraceRichEdit::TraceString( LPCTSTR pszString, enTraceLevel TraceLevel )
{
	if ( GetSafeHwnd() == NULL ) return false;
	
	//设置格式
	CHARFORMAT2 CharFormat;
	memset(&CharFormat,0,sizeof(CharFormat));
	CharFormat.cbSize=sizeof(CharFormat); 
	CharFormat.dwMask=CFM_COLOR|CFM_FACE|CFM_SIZE;
	CharFormat.yHeight=180;
	lstrcpyn(CharFormat.szFaceName,TEXT("宋体"),sizeof(CharFormat.szFaceName));

	//获取时间
	SYSTEMTIME SystemTime;
	TCHAR szTimeBuffer[512] = {0};
	GetLocalTime(&SystemTime);
	_sntprintf_s(szTimeBuffer, sizeof(szTimeBuffer), TEXT("[%02d:%02d:%02d] "), SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);
	_sntprintf_s(szTimeBuffer, sizeof(szTimeBuffer), TEXT("%s%s\n"), szTimeBuffer, pszString);
	CharFormat.crTextColor = GetTraceColor(TraceLevel);

	return InsertString(szTimeBuffer, CharFormat);
}

bool CTraceRichEdit::TraceString(enTraceLevel TraceLevel, LPCTSTR pszString, ... )
{
	CString StrTraceString;

	va_list argList;
	va_start( argList, pszString );
	StrTraceString.FormatV( pszString, argList );
	va_end( argList );

	return TraceString(StrTraceString,TraceLevel);
}

COLORREF CTraceRichEdit::GetTraceColor( enTraceLevel TraceLevel )
{
	switch (TraceLevel)
	{
	case TraceLevel_Info:
		return RGB(133, 124, 129);
		break;
	case TraceLevel_Normal:
		return RGB(205, 215, 225);
		break;
	case TraceLevel_Warning:
		return RGB(255, 0, 0);
		break;
	case TraceLevel_Exception:
		return RGB(255, 0, 0);
		break;
	case TraceLevel_Debug:
		return RGB(19, 127, 140);
		break;
	}

	return RGB(0, 0, 0);
}

//字符判断
bool EfficacyUrlChar(TCHAR chChar)
{
	//特殊字符
	if (chChar == TEXT('.')) return true;
	if (chChar == TEXT('=')) return true;
	if (chChar == TEXT('+')) return true;
	if (chChar == TEXT('?')) return true;
	if (chChar == TEXT('#')) return true;
	if (chChar == TEXT('%')) return true;
	if (chChar == TEXT('/')) return true;
	if (chChar == TEXT(':')) return true;
	if (chChar == TEXT('&')) return true;

	//字符范围
	if ((chChar >= TEXT('a')) && (chChar <= TEXT('z'))) return true;
	if ((chChar >= TEXT('A')) && (chChar <= TEXT('Z'))) return true;
	if ((chChar >= TEXT('0')) && (chChar <= TEXT('9'))) return true;

	return false;
}

//地址判断
bool EfficacyUrlString(LPCTSTR pszUrl)
{
	for (WORD i = 0; i < _tcslen(pszUrl); i++)
	{
		if (!EfficacyUrlChar(pszUrl[i])) return false;
	}

	return true;
}

bool CTraceRichEdit::InsertString( LPCTSTR pszString, CHARFORMAT2 & CharFormat )
{
	if (GetTextLength() >= 1024 * 512)
		SetWindowText(NULL);

	//插入消息
	//变量定义
	bool bResumeSelect;
	CHARRANGE CharRange;

	//保存状态
	SetSel(-1L, -1L);
	GetSel(CharRange.cpMin, CharRange.cpMax);
	bResumeSelect = (CharRange.cpMax != CharRange.cpMin);

	//搜索变量
	LPCTSTR pszHttp = TEXT("http://");
	const INT nHttpLength = lstrlen(pszHttp);
	const INT nStringLength = lstrlen(pszString);

	//索引定义
	INT nStringStart = 0;
	INT nStringPause = 0;

	//字符解释
	for (INT i = 0; i < nStringLength; i++)
	{
		//变量定义
		INT nUrlPause = i;

		//地址判断
		if (((i + nHttpLength) < nStringLength) && (memcmp(&pszString[i], pszHttp, nHttpLength*sizeof(TCHAR)) == 0))
		{
			//设置索引
			nUrlPause = i + nHttpLength;

			//地址搜索
			while (nUrlPause < nStringLength)
			{
				//字符判断
				if (EfficacyUrlChar(pszString[nUrlPause]) == true)
				{
					nUrlPause++;
					continue;
				}

				break;
			}
		}

		//终止字符
		if (nUrlPause <= (i + nHttpLength)) nStringPause = (i + 1);

		//插入字符
		if ((i == (nStringLength - 1)) || (nUrlPause > (i + nHttpLength)))
		{
			//普通字符
			if (nStringPause > nStringStart)
			{
				//获取缓冲
				CString strNormalString;
				LPTSTR pszNormalString = strNormalString.GetBuffer(nStringPause - nStringStart + 1);

				//拷贝字符
				pszNormalString[nStringPause-nStringStart] = 0;
				CopyMemory(pszNormalString, &pszString[nStringStart], (nStringPause - nStringStart)*sizeof(TCHAR));

				//释放缓冲
				strNormalString.ReleaseBuffer();

				//插入消息
				SetSel(-1L, -1L);
				SetWordCharFormat(CharFormat);
				ReplaceSel((LPCTSTR)strNormalString);
			}

			//连接地址
			if (nUrlPause > (i + nHttpLength))
			{
				//获取缓冲
				CString strUrlString;
				LPTSTR pszUrlString = strUrlString.GetBuffer((nUrlPause - i) + 1);

				//拷贝字符
				pszUrlString[nUrlPause-i] = 0;
				CopyMemory(pszUrlString, &pszString[i], (nUrlPause - i)*sizeof(TCHAR));

				//释放缓冲
				strUrlString.ReleaseBuffer();

				//构造格式
				CHARFORMAT2 CharFormatHyper;
				CharFormatHyper = CharFormat;

				//效验地址
				if (EfficacyUrlString(strUrlString) == true)
				{
					CharFormatHyper.dwMask |= CFM_LINK;
					CharFormatHyper.dwEffects |= CFE_LINK;
				}

				//插入消息
				SetSel(-1L, -1L);
				SetWordCharFormat(CharFormatHyper);
				ReplaceSel((LPCTSTR)strUrlString);
			}

			//设置索引
			nStringStart = __max(i, nUrlPause);
		}

		//设置索引
		i += (nUrlPause - i);
	}

	//状态设置
	if (bResumeSelect == true) SetSel(CharRange);
	else PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

	return true;
}

void CTraceRichEdit::InitService()
{
	TraceService->SetInterFace(this);
}

//////////////////////////////////////////////////////////////////////////


CTraceDialog::CTraceDialog(CWnd* pParent /*=NULL*/): CDialog(IDD_DEBUG, pParent)
{

}

CTraceDialog::~CTraceDialog()
{
}

void CTraceDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_RICHDEBUG,m_TraceEdit);
}


BEGIN_MESSAGE_MAP(CTraceDialog, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTraceDialog 消息处理程序

BOOL CTraceDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_TraceEdit.SetBackgroundColor(FALSE,RGB(0,0,0));
	m_TraceEdit.InitService();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTraceDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	DeferWindowPos(hDwp,m_TraceEdit,NULL,0,0,cx,cy,uFlags|SWP_NOMOVE);

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();
}

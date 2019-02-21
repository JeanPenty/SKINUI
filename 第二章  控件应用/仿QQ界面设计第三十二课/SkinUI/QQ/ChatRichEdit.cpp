// ChatRichEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "ChatRichEdit.h"


// CChatRichEdit

IMPLEMENT_DYNAMIC(CChatRichEdit, CSkinRichEdit)

CChatRichEdit::CChatRichEdit()
{
}

CChatRichEdit::~CChatRichEdit()
{
}


BEGIN_MESSAGE_MAP(CChatRichEdit, CSkinRichEdit)
	ON_WM_CREATE()
END_MESSAGE_MAP()

bool CChatRichEdit::TranslateInsertString( LPCTSTR pszString, CHARFORMAT2 & CharFormat )
{
	CExpressionManager * pExpressionManager = CExpressionManager::GetInstance();
	if( pExpressionManager == NULL ) return false;

	//变量定义
	tagTranslateResult TranslateResult;
	ZeroMemory(&TranslateResult,sizeof(TranslateResult));

	//字符变量
	INT nTranslateIndex=0;
	INT nStringLength=lstrlen(pszString);

	while ((nStringLength-nTranslateIndex)>0)
	{
		//解释字符
		bool bSuccess=pExpressionManager->TranslateString(&pszString[nTranslateIndex],TranslateResult);

		//结果处理
		if (bSuccess==true)
		{
			//插入字符
			if (TranslateResult.nStartPos>0)
			{
				//变量定义
				TCHAR szString[8192]=TEXT("");
				WORD wCopyCount=__min(TranslateResult.nStartPos,CountArray(szString));

				//构造字符
				szString[wCopyCount]=0;
				CopyMemory(szString,&pszString[nTranslateIndex],wCopyCount*sizeof(TCHAR));

				//插入字符
				InsertString(szString,CharFormat);
			}

			//构造路径
			TCHAR ImagePath[MAX_PATH]=TEXT("");
			TranslateResult.pExpressionItem->GetExpressionPath(ImagePath,CountArray(ImagePath));

			//插入表情
			InsertImage(ImagePath);

			//设置索引
			nTranslateIndex+=TranslateResult.nStartPos+TranslateResult.nDescribeLen;
		}
		else
		{
			//插入字符
			InsertString(&pszString[nTranslateIndex],CharFormat);
			break;
		}

	}

	return true;
}

BOOL CChatRichEdit::PreTranslateMessage( MSG * pMsg )
{
	//按键过虑
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}



// CChatRichEdit 消息处理程序

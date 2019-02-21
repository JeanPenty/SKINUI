// ListBoxEx.cpp : 实现文件
//

#include "stdafx.h"
#include "CalcFrame.h"
#include "ListBoxEx.h"


// CListBoxEx

IMPLEMENT_DYNAMIC(CListBoxEx, CListBox)

#define IDM_COPY		WM_USER+100
#define IDM_REMOVE		WM_USER+101
#define IDM_CLEAR		WM_USER+102

CListBoxEx::CListBoxEx()
{

}

CListBoxEx::~CListBoxEx()
{
}


BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()



// CListBoxEx 消息处理程序

void CListBoxEx::OnRButtonUp(UINT nFlags, CPoint point)
{
	CMenu PopMenu;
	if (PopMenu.CreatePopupMenu()==FALSE) return;

	PopMenu.AppendMenu(0,IDM_COPY,TEXT("复制"));
	PopMenu.AppendMenu(0,IDM_REMOVE,TEXT("清除"));
	PopMenu.AppendMenu(0,IDM_CLEAR,TEXT("清除所有"));

	//弹出菜单
	CPoint pt;
	GetCursorPos(&pt);
	PopMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,pt.x,pt.y,this);

	CListBox::OnRButtonUp(nFlags, point);
}

BOOL CListBoxEx::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_COPY:
		{
			//打开剪切板
			if (OpenClipboard()==FALSE) return TRUE;
			if (EmptyClipboard()==FALSE) { CloseClipboard(); return TRUE; }

			CString strName;
			int nSelIndex = GetCurSel();
			if ( nSelIndex == -1 )
			{
				nSelIndex = 0;
				SetSel(0);
			}
			GetText(nSelIndex,strName);

			if(strName.GetLength() == 0 ) return TRUE;
			//复制数据
			HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,strName.GetLength()+1);
			if (hData==NULL) 
			{
				CloseClipboard();
				return TRUE;
			}

			
			LPTSTR szMemName=(LPTSTR)GlobalLock(hData);
			lstrcpy(szMemName,strName);
			SetClipboardData(CF_TEXT,hData);
			GlobalUnlock(hData);
			CloseClipboard();
		}
		break;
	case IDM_REMOVE:
		{
			int nSelIndex = GetCurSel();
			if ( nSelIndex == -1 ) 
			{
				MessageBox(TEXT("请选择一项"),TEXT("Error"),MB_ICONSTOP);
				return TRUE;
			}

			if( AfxMessageBox(TEXT("您确定要删除这项记录么？"),MB_YESNO) == IDYES )
			{
				DeleteString(nSelIndex);

				if ( GetCount() == 0 )
				{
					//通知主窗口，调整界面布局
					AfxGetMainWnd()->PostMessage(WM_RECTIFY);
				}
			}

		}
		break;
	case IDM_CLEAR:
		{
			if( AfxMessageBox(TEXT("您确定要删除全部记录么？"),MB_YESNO) == IDYES )
			{
				ResetContent();
				//通知主窗口，调整界面布局
				AfxGetMainWnd()->PostMessage(WM_RECTIFY);
			}
		}
		break;
	}

	return CListBox::OnCommand(wParam, lParam);
}

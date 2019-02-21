// RichEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RichEditDlg.h"
#include "Resource.h"

// CRichEditDlg 对话框

//菜单命令
#define IDM_CLEAR_ALL				(WM_USER+201)						//删除信息
#define IDM_SELECT_ALL				(WM_USER+202)						//全部选择
#define IDM_COPY_STRING				(WM_USER+203)						//拷贝字符


IMPLEMENT_DYNAMIC(CRichEditDlg, CDlgControlItem)

CRichEditDlg::CRichEditDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_RICHEDIT, pParent)
{
	ZeroMemory(&m_cf2, sizeof(CHARFORMAT2));
}

CRichEditDlg::~CRichEditDlg()
{
}

void CRichEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_RICHEDIT21,m_RichEditCtrl);
	DDX_Control(pDX,IDC_RICHEDIT22,m_SkinRichEdit);
}


BEGIN_MESSAGE_MAP(CRichEditDlg, CDlgControlItem)
	ON_BN_CLICKED(IDC_BUTTON1, &CRichEditDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRichEditDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CRichEditDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CRichEditDlg::OnBnClickedButton5)
	ON_NOTIFY(EN_LINK, IDC_RICHEDIT21, OnURLClick )
	ON_BN_CLICKED(IDC_BUTTON6, &CRichEditDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON10, &CRichEditDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON7, &CRichEditDlg::OnBnClickedButton7)
	ON_RBN_DBLCLK(IDC_RICHEDIT22,OnRClicked)

	//菜单命令
	ON_COMMAND(IDM_CLEAR_ALL, OnClearAll)
	ON_COMMAND(IDM_SELECT_ALL, OnSelectAll)
	ON_COMMAND(IDM_COPY_STRING, OnCopyString)
END_MESSAGE_MAP()


// CRichEditDlg 消息处理程序

void CRichEditDlg::OnBnClickedButton1()
{
	CFontDialog dlg;

	if (dlg.DoModal() == IDOK )
	{
		LOGFONT lFont;
		dlg.GetCurrentFont(&lFont);

		CHARFORMAT cf;
		ZeroMemory(&cf, sizeof(CHARFORMAT));

		m_RichEditCtrl.GetDefaultCharFormat(cf);

		cf.yHeight = -15 * lFont.lfHeight;
		cf.dwMask = CFM_COLOR|CFM_SIZE |CFM_FACE;
		cf.dwEffects = CFE_BOLD;
		cf.crTextColor = dlg.GetColor();
		lstrcpyn(cf.szFaceName,lFont.lfFaceName,CountArray(lFont.lfFaceName));

		m_RichEditCtrl.SetSelectionCharFormat(cf);
		m_RichEditCtrl.SetSel(-1,-1);
	}
}

BOOL CRichEditDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	m_SkinRichEdit.SetScrollImage(&m_SkinRichEdit,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));
	m_SkinRichEdit.GetDefaultCharFormat(m_cf2);
	m_SkinRichEdit.SetBackColor(RGB(255,255,0));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRichEditDlg::OnBnClickedButton2()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,TEXT("RTF文件;txt文件|*.rtf;*.txt||"));
	if ( dlg.DoModal() == IDOK )
	{
		CString strFileName = dlg.GetPathName();

		//打开文件
		CFile File;
		if (File.Open(strFileName,CFile::modeRead,NULL)==FALSE) return;

		//构造数据
		EDITSTREAM EditStream;
		EditStream.pfnCallback=LoadCallBack;
		EditStream.dwCookie=(DWORD_PTR)(&File);

		//读取文件
		if( StrCmp(File.GetFileName().Right(3),TEXT("rtf")) == 0 )
			m_RichEditCtrl.StreamIn(SF_RTF,EditStream);
		else
			m_RichEditCtrl.StreamIn(SF_TEXT,EditStream);

		File.Close();
	}
}

void CRichEditDlg::OnBnClickedButton4()
{
	CFileDialog FileDlg(FALSE,TEXT("RTF"),0,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,TEXT("信息文件(*.RTF)|*.RTF||"),this);
	
	if ( FileDlg.DoModal() == IDOK )
	{
		CString strFileName = FileDlg.GetPathName();

		//打开文件
		CFile File;
		if (File.Open(strFileName,CFile::modeWrite|CFile::modeCreate,NULL)==FALSE) return;

		//构造数据
		EDITSTREAM EditStream;
		EditStream.pfnCallback=SaveCallBack;
		EditStream.dwCookie=(DWORD)(LONGLONG)(&File);

		//写入文件
		m_RichEditCtrl.StreamOut(SF_RTF,EditStream);
	}
}

DWORD CALLBACK CRichEditDlg::LoadCallBack( DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb )
{
 	//读取文件
 	*pcb=((CFile *)(LONGLONG)(dwCookie))->Read(pbBuff,cb);
 
 	return 0;
}

//保存回调
DWORD CALLBACK CRichEditDlg::SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb)
{
	//写入文件
	((CFile *)(LONGLONG)(dwCookie))->Write(pbBuff,cb);

	return 0;
}


void CRichEditDlg::OnBnClickedButton5()
{
	CHARFORMAT2 cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT2));
	cf2.cbSize = sizeof(CHARFORMAT2);
	cf2.dwMask = CFM_LINK;
	cf2.dwEffects |= CFE_LINK;
	m_RichEditCtrl.SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf2);

	//添加点击事件
	m_RichEditCtrl.SetEventMask(ENM_LINK);
}

void CRichEditDlg::OnURLClick(NMHDR *pNmhdr, LRESULT *pResult)
{
	ENLINK* pENLink = ( ENLINK* )pNmhdr ;
	*pResult = 0 ;

	if (pENLink->msg == WM_LBUTTONUP)
	{

		CString StrURL ;
		CHARRANGE l_CharRange ;
	
		m_RichEditCtrl.GetSel( l_CharRange ) ;
		m_RichEditCtrl.SetSel( pENLink->chrg ) ;
		StrURL = m_RichEditCtrl.GetSelText() ;
		m_RichEditCtrl.SetSel( l_CharRange ) ;

		ShellExecute( GetSafeHwnd(), TEXT( "open" ), StrURL, NULL, NULL, SW_SHOWNORMAL ) ;
		*pResult = 1 ;

	}
}

void CRichEditDlg::InsertTips()
{
	CString strTime;

	CTime tm =CTime::GetCurrentTime();

	strTime=tm.Format(TEXT("丄偙寵ル %Y/%m/%d %X\n"));

	CHARFORMAT2 cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT2));
	cf2.cbSize = sizeof(CHARFORMAT2);
	cf2.dwMask = CFM_COLOR|CFM_SIZE |CFM_FACE;
	cf2.dwEffects = CFE_BOLD;
	cf2.yHeight = 60;
	cf2.crTextColor = RGB(0,151,164);

	m_SkinRichEdit.InsertString(strTime,cf2);
}

void CRichEditDlg::OnBnClickedButton6()
{
	CString str;
	GetDlgItemText(IDC_EDIT1,str);

	InsertTips();

	m_SkinRichEdit.InsertString(str,m_cf2);

	m_SkinRichEdit.InsertString(TEXT("\n"),RGB(0,0,0));
}

void CRichEditDlg::OnBnClickedButton10()
{
	CFileDialog FileDlg(TRUE,TEXT("插入图片"),0,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,TEXT("图像文件*.BMP;*.JPG;*.JPEG;*.GIF|*.BMP;*.JPG;*.JPEG;*.GIF||"),this);

	if ( FileDlg.DoModal() == IDOK )
	{
		InsertTips();
		m_SkinRichEdit.InsertImage(FileDlg.GetPathName());
		m_SkinRichEdit.InsertString(TEXT("\n"),RGB(0,0,0));
	}
}


void CRichEditDlg::OnBnClickedButton7()
{
	CFontDialog dlg;

	if (dlg.DoModal() == IDOK )
	{
		LOGFONT lFont;
		dlg.GetCurrentFont(&lFont);

		ZeroMemory(&m_cf2, sizeof(CHARFORMAT));

		m_SkinRichEdit.GetDefaultCharFormat(m_cf2);

		m_cf2.yHeight = -15 * lFont.lfHeight;
		m_cf2.dwMask = CFM_COLOR|CFM_SIZE |CFM_FACE;
		m_cf2.dwEffects = CFE_BOLD;
		m_cf2.crTextColor = dlg.GetColor();
		lstrcpyn(m_cf2.szFaceName,lFont.lfFaceName,CountArray(lFont.lfFaceName));
	}	
}

void CRichEditDlg::OnRClicked()
{
	CMenu menu;
	if (menu.CreatePopupMenu()==FALSE) return;
	menu.AppendMenu(0,IDM_COPY_STRING,TEXT("复制(&C)"));
	menu.AppendMenu(0,IDM_SELECT_ALL,TEXT("全部选择(&A)"));
	menu.AppendMenu(0,IDM_CLEAR_ALL,TEXT("清屏"));

	//显示菜单
	CPoint pt;
	GetCursorPos(&pt);

	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,pt.x,pt.y,this);
}

//删除信息
VOID CRichEditDlg::OnClearAll()
{
	//删除信息
	m_SkinRichEdit.SetSel(0L,-1L);
	m_SkinRichEdit.ReplaceSel(NULL);

	return;
}

//全部选择
VOID CRichEditDlg::OnSelectAll()
{
	//全部选择
	m_SkinRichEdit.SetSel(0L,-1L);

	return;
}

//拷贝字符
VOID CRichEditDlg::OnCopyString()
{
	//拷贝字符
	m_SkinRichEdit.Copy();

	return;
}

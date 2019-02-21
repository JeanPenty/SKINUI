// ComBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "ComBoxDlg.h"

struct tagStudent
{
	TCHAR	szName[33];		//姓名
	int		nScore;			//成绩
	int		nID;			//学号
};

// CComBoxDlg 对话框

IMPLEMENT_DYNAMIC(CComBoxDlg, CDlgControlItem)

CComBoxDlg::CComBoxDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(CComBoxDlg::IDD, pParent)
{

}

CComBoxDlg::~CComBoxDlg()
{
}

void CComBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_COMBO1,m_ComboBox1);
	DDX_Control(pDX,IDC_COMBO2,m_ComboBox2);
	DDX_Control(pDX,IDC_COMBO3,m_ComboBox3);
	DDX_Control(pDX,IDC_COMBO4,m_ComboBox4);
	DDX_Control(pDX,IDC_COMBO5,m_SkinComboBox);
	DDX_Control(pDX,IDC_COMBO6,m_SkinComboBox2);
}


BEGIN_MESSAGE_MAP(CComBoxDlg, CDlgControlItem)
	ON_BN_CLICKED(IDC_BUTTON1, &CComBoxDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CComBoxDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CComBoxDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON14, &CComBoxDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CComBoxDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON15, &CComBoxDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON17, &CComBoxDlg::OnBnClickedButton17)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON4, &CComBoxDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CComBoxDlg::OnBnClickedButton8)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CComBoxDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON5, &CComBoxDlg::OnBnClickedButton5)

	ON_MESSAGE(WM_CBO_RBUTTONUP,OnRButtonUp)
END_MESSAGE_MAP()

void CComBoxDlg::DrawClientArea( CDC*pDC,int nWidth,int nHeight )
{
}


// CComBoxDlg 消息处理程序

BOOL CComBoxDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	CString strItem=TEXT("");

	for (int i=0;i<10;i++)
	{
		strItem.Format(TEXT("Item%d"),i);
		m_ComboBox1.AddString(strItem);
	}
	
	for (int i=0;i<10;i++)
	{
		strItem.Format(TEXT("Item%d"),i);
		m_ComboBox2.InsertString(i,strItem);
	}

	m_ComboBox2.InsertString(2,TEXT("InsertString"));

	m_ComboBox2.DeleteString(3);

	m_ComboBox1.SetCurSel(5);
	m_ComboBox2.SetCurSel(0);

	int nCurSel = m_ComboBox1.GetCurSel();

	int nCount = m_ComboBox1.GetCount();

	//经典用法
	SetCombox(TEXT("city"),TEXT("CityCount"),TEXT("city"), &m_ComboBox3);
	OnCbnSelchangeCombo3();

	HDC hParentDC = GetBackDC();

	m_SkinComboBox.SetBgNormalPic(TEXT("Res\\ComboBox\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_SkinComboBox.SetBgHotPic(TEXT("Res\\ComboBox\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_SkinComboBox.SetArrowNormalPic(TEXT("Res\\ComboBox\\login_inputbtn_normal.png"));
	m_SkinComboBox.SetArrowHotPic(TEXT("Res\\ComboBox\\login_inputbtn_highlight.png"));
	m_SkinComboBox.SetArrowPushedPic(TEXT("Res\\ComboBox\\login_inputbtn_down.png"));
	m_SkinComboBox.SetParentBack(hParentDC);
	m_SkinComboBox.SetArrowWidth(23);
	m_SkinComboBox.SetDefaultText(TEXT("请输入帐号"));
	m_SkinComboBox.SetItemHeight(-1, 22);

	for (int i=0;i<100;i++)
	{
		m_SkinComboBox.AddString(TEXT("Item"));
	}

	m_SkinComboBox2.SetBgNormalPic(TEXT("Res\\ComboBox\\frameBorderEffect_normalDraw.png"), CRect(3,3,3,3));
	m_SkinComboBox2.SetBgHotPic(TEXT("Res\\ComboBox\\frameBorderEffect_mouseDownDraw.png"), CRect(3,3,3,3));
	m_SkinComboBox2.SetArrowNormalPic(TEXT("Res\\ComboBox\\inputbtn_normal.png"));
	m_SkinComboBox2.SetArrowHotPic(TEXT("Res\\ComboBox\\inputbtn_highlight.png"));
	m_SkinComboBox2.SetArrowPushedPic(TEXT("Res\\ComboBox\\inputbtn_down.png"));
	m_SkinComboBox2.SetParentBack(hParentDC);
	m_SkinComboBox2.SetArrowWidth(23);
	m_SkinComboBox2.SetItemHeight(-1, 22);
	m_SkinComboBox2.SetDropList();
	m_SkinComboBox2.SetEditTextColor(RGB(255,0,0));
	RenderEngine->AddFont(TEXT("宋体"),20,false,false,false);
	m_SkinComboBox2.SetCtrlFont(RenderEngine->GetEndFont());
	m_SkinComboBox2.SetAllItemHeight(20);
	//m_SkinComboBox2.SetItemHeight(-1,50);
	//m_SkinComboBox2.SetScrollImage(TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));

	CSkinComboBox_ListBox *pListBox = m_SkinComboBox2.GetListBoxWnd();
	if ( pListBox != NULL )
	{
		pListBox->SetBackNormalImage(TEXT("Res\\Edit\\frameBorderEffect_mouseDownDraw.png"),CRect(3,3,3,3));
		pListBox->SetSelectImage(TEXT("Res\\ComboBox\\listitem_select.png"),CRect(3,3,3,3));
		pListBox->SetFrameColor(RGB(55,141,192));
	}

	for (int i=0;i<5;i++)
	{
		m_SkinComboBox2.AddString(TEXT("Item"));
	}

	m_SkinComboBox2.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE   
}

void CComBoxDlg::OnBnClickedButton1()
{
	CString strText;
	//方法1
	m_ComboBox1.GetLBText(m_ComboBox1.GetCurSel(),strText);
	//方法2
	//m_ComboBox1.GetWindowText(strText);

	MessageBox(strText);
}

void CComBoxDlg::OnBnClickedButton2()
{
	CString str;
	str.Format(TEXT("总数：%d"),m_ComboBox1.GetCount());
	MessageBox(str);
}

void CComBoxDlg::OnBnClickedButton3()
{
	m_ComboBox1.ResetContent();
}

void CComBoxDlg::OnBnClickedButton14()
{
	m_ComboBox1.ResetContent();

	CString strName;	//学生姓名
	int nScore;			//学生成绩

	srand(unsigned int(time(NULL)));

	for (int i=0;i<10;i++)
	{
		strName.Format(TEXT("学生%d"),i);
		nScore = 1+(rand()%100);

		m_ComboBox1.InsertString(i,strName);
		m_ComboBox1.SetItemData(i,nScore);
	}

	m_ComboBox1.SetCurSel(0);
}

void CComBoxDlg::OnBnClickedButton16()
{
	CString strName;	//学生姓名

	int nScore = m_ComboBox1.GetItemData(m_ComboBox1.GetCurSel());
	m_ComboBox1.GetWindowText(strName);
	
	strName.Format(TEXT("%s的成绩：%d"),strName,nScore);

	MessageBox(strName);
}

void CComBoxDlg::OnBnClickedButton15()
{
	m_ComboBox1.ResetContent();

	tagStudent *pStudent = NULL;

	srand(unsigned int(time(NULL)));

	CString str;

	for (int i=0;i<10;i++)
	{
		pStudent = new tagStudent;
		str.Format(TEXT("学生%d"),i);
		lstrcpyn(pStudent->szName,str,CountArray(pStudent->szName));

		pStudent->nScore = 1+(rand()%100);
		pStudent->nID = 10*rand()%1000;

		m_ComboBox1.InsertString(i,pStudent->szName);
		m_ComboBox1.SetItemDataPtr(i,pStudent);
	}

	m_ComboBox1.SetCurSel(0);
}

void CComBoxDlg::OnBnClickedButton17()
{
	tagStudent *pStudent = NULL;
	pStudent = (tagStudent *)m_ComboBox1.GetItemDataPtr(m_ComboBox1.GetCurSel());

	if( pStudent != NULL)
	{
		CString strOut;
		strOut.Format(TEXT("编号为：%d的学生[%s]的成绩：%d"),pStudent->nID,pStudent->szName,pStudent->nScore);

		MessageBox(strOut);
	}
}

void CComBoxDlg::OnDestroy()
{
	tagStudent *pStudent = NULL;

	for (int i=0;i<m_ComboBox1.GetCount();i++)
	{
		pStudent = (tagStudent *)m_ComboBox1.GetItemDataPtr(i);

		SafeDelete(pStudent);
	}

	m_ComboBox1.ResetContent();

	CDlgControlItem::OnDestroy();	
}

void CComBoxDlg::OnBnClickedButton4()
{
	m_ComboBox1.SetItemHeight(-1,20);
}

void CComBoxDlg::OnBnClickedButton8()
{
	for (int i=0;i<m_ComboBox1.GetCount();i++)
	{
		m_ComboBox1.SetItemHeight(i,25);
	}
}

void CComBoxDlg::OnCbnSelchangeCombo3()
{
	//清空城市
	m_ComboBox4.ResetContent();

	//获取省份
	CString szProvince;
	m_ComboBox3.GetWindowText(szProvince);

	//设置数据
	SetCombox(szProvince,TEXT("AreaCount"),TEXT("Area"), &m_ComboBox4);
}

void CComBoxDlg::SetCombox(LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpItemKeyName,CComboBox * pCComboBox )
{
	if ( pCComboBox == NULL ) return;

	TCHAR szWorkDirectory[MAX_PATH];
	RenderEngine->GetWorkDirectory(szWorkDirectory,CountArray(szWorkDirectory));
	StrCat(szWorkDirectory,TEXT("\\RegionCfg.ini"));

	//读取文件
	TCHAR szCount[MAX_PATH];
	GetPrivateProfileString(lpAppName,lpKeyName,TEXT("0"),szCount,MAX_PATH,szWorkDirectory);

	//设置城市
	CString szTemp;
	TCHAR szCity[MAX_PATH];

	for (int i=1;i<_tcstol(szCount,NULL,10);i++)
	{
		szTemp.Format(TEXT("%s%d"),lpItemKeyName,i);
		GetPrivateProfileString(lpAppName,szTemp,TEXT(""),szCity,MAX_PATH,szWorkDirectory);
		pCComboBox->AddString(szCity);
	}

	pCComboBox->SetCurSel(0);
}

void CComBoxDlg::OnBnClickedButton5()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/419.html"));
}

LRESULT CComBoxDlg::OnRButtonUp( WPARAM wParam, LPARAM lParam )
{
	CString str;
	str.Format(TEXT("选中的节点：%d"),int(wParam));
	MessageBox(str);

	return 0L;
}

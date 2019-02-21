// CalcFrameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CalcFrame.h"
#include "CalcFrameDlg.h"
#include <math.h>
#include "apsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//删除数组
#define  SafeDeleteArray(pData) { try { delete [] pData; } catch (...) { ASSERT(FALSE); } pData=NULL; } 
//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

#define ITOA(x)		(((x>=0) && (x<=9)) ? (char)(x+'0') : 0)

#define PI	3.1415926535897932384626433832795


// CCalcFrameDlg 对话框

CCalcFrameDlg::CCalcFrameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CALCFRAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_enWindowStyle = en_Science;
	m_enCalcType = en_Null;
	m_bShowSave = false;
	m_bFront = false;
	m_bPressNumber = false;
	m_bPressEnable = true;
	m_bIsBaseCalc=false;
	m_strOutPut = TEXT("0");
	m_strButtonOld = TEXT("");
	m_strResultOld = TEXT("");
}

void CCalcFrameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_STATIC_MAIN,m_strOutPut);
	DDX_Text(pDX,IDC_STATIC_LIST,m_strResult);
	DDX_Control(pDX,IDC_LIST_SAVA,m_ListSave);
}

BEGIN_MESSAGE_MAP(CCalcFrameDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_JIA, &CCalcFrameDlg::OnBnClickedBtJia)
	ON_BN_CLICKED(IDC_BT_JIAN, &CCalcFrameDlg::OnBnClickedBtJian)
	ON_BN_CLICKED(IDC_BT_CHENG, &CCalcFrameDlg::OnBnClickedBtCheng)
	ON_BN_CLICKED(IDC_BT_CHU, &CCalcFrameDlg::OnBnClickedBtChu)
	ON_BN_CLICKED(IDC_BT_DENGYU, &CCalcFrameDlg::OnBnClickedBtDengyu)
	ON_BN_CLICKED(IDC_BT_DAOSHU, &CCalcFrameDlg::OnBnClickedBtDaoshu)
	ON_BN_CLICKED(IDC_BT_PAI, &CCalcFrameDlg::OnBnClickedBtPai)
	ON_BN_CLICKED(IDC_BT_PINGFANG, &CCalcFrameDlg::OnBnClickedBtPingfang)
	ON_BN_CLICKED(IDC_BT_CIFANG, &CCalcFrameDlg::OnBnClickedBtCifang)
	ON_BN_CLICKED(IDC_BT_LIFANG, &CCalcFrameDlg::OnBnClickedBtLifang)
	ON_BN_CLICKED(IDC_BT_SHICIFANG, &CCalcFrameDlg::OnBnClickedBtShicifang)
	ON_BN_CLICKED(IDC_BT_JIECHENG, &CCalcFrameDlg::OnBnClickedBtJiecheng)
	ON_BN_CLICKED(IDC_BT_KAILIFANG, &CCalcFrameDlg::OnBnClickedBtKailifang)
	ON_BN_CLICKED(IDC_BT_KAILIFANGN, &CCalcFrameDlg::OnBnClickedBtKailifangn)
	ON_BN_CLICKED(IDC_BT_LOG, &CCalcFrameDlg::OnBnClickedBtLog)
	ON_BN_CLICKED(IDC_BT_INT, &CCalcFrameDlg::OnBnClickedBtInt)
	ON_BN_CLICKED(IDC_BT_SIN, &CCalcFrameDlg::OnBnClickedBtSin)
	ON_BN_CLICKED(IDC_BT_COS, &CCalcFrameDlg::OnBnClickedBtCos)
	ON_BN_CLICKED(IDC_BT_TAN, &CCalcFrameDlg::OnBnClickedBtTan)
	ON_BN_CLICKED(IDC_BT_ASIN, &CCalcFrameDlg::OnBnClickedBtAsin)
	ON_BN_CLICKED(IDC_BT_ACOS, &CCalcFrameDlg::OnBnClickedBtAcos)
	ON_BN_CLICKED(IDC_BT_ATAN, &CCalcFrameDlg::OnBnClickedBtAtan)
	ON_BN_CLICKED(IDC_BT_SINH, &CCalcFrameDlg::OnBnClickedBtSinh)
	ON_BN_CLICKED(IDC_BT_COSH, &CCalcFrameDlg::OnBnClickedBtCosh)
	ON_BN_CLICKED(IDC_BT_TANH, &CCalcFrameDlg::OnBnClickedBtTanh)
	ON_BN_CLICKED(IDC_BT_LN, &CCalcFrameDlg::OnBnClickedBtLn)
	ON_BN_CLICKED(IDC_BT_C, &CCalcFrameDlg::OnBnClickedBtC)
	ON_BN_CLICKED(IDC_BT_MC, &CCalcFrameDlg::OnBnClickedBtMc)
	ON_BN_CLICKED(IDC_BT_DAXIE, &CCalcFrameDlg::OnBnClickedBtDaxie)
	ON_MESSAGE(WM_RECTIFY,OnRecifyView)
END_MESSAGE_MAP()


// CCalcFrameDlg 消息处理程序

BOOL CCalcFrameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CheckDlgButton(IDC_JIAODU,BST_CHECKED);
	
	CWnd *pWnd = NULL;
	CRect rcControl(0,0,0,0);

	//统计所有控件的位置，存入map中
	for (UINT i=IDC_BT_MC;i<=IDC_STATIC_JIAOHU;i++)
	{
		pWnd = GetDlgItem(i);
		if( pWnd == NULL )continue;
	
		pWnd->GetWindowRect(&rcControl);
		
		m_Position.insert(std::pair<UINT,CPoint>(i,CPoint(rcControl.left,rcControl.top)));
	}

	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	//CString str;
	//str.Format("%c",ITOA(1));
	//MessageBox(str);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalcFrameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalcFrameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalcFrameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CCalcFrameDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);

	switch ( LOWORD(wParam) )
	{
	case ID_32771:			//标准型
		{
			CMenu *pMenu = GetMenu()->GetSubMenu(0);
			if( pMenu != NULL )
			{
				pMenu->CheckMenuItem(ID_32771,MF_CHECKED);
				pMenu->CheckMenuItem(ID_32772,MF_UNCHECKED);
			}

			OnBnClickedBtC();
			if( m_enWindowStyle == en_Normal ) return TRUE;
			m_enWindowStyle = en_Normal;
			PostMessage(WM_SIZE);
		}
		break;
	case ID_32772:			//科学型
		{
			CMenu *pMenu = GetMenu()->GetSubMenu(0);
			if( pMenu != NULL )
			{
				pMenu->CheckMenuItem(ID_32772,MF_CHECKED);
				pMenu->CheckMenuItem(ID_32771,MF_UNCHECKED);
			}

			OnBnClickedBtC();
			if( m_enWindowStyle == en_Science ) return TRUE;
			m_enWindowStyle = en_Science;
			PostMessage(WM_SIZE);
		}
		break;
	case ID_32773:			//最前显示
		{
			m_bFront = !m_bFront;

			GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_32773,m_bFront?MF_CHECKED:MF_UNCHECKED);

			SetWindowPos(m_bFront? &wndTopMost : &wndNoTopMost,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);
		}
		break;
	case ID_32775:
		{
			//打开剪切板
			if (OpenClipboard()==FALSE) return TRUE;
			if (EmptyClipboard()==FALSE) { CloseClipboard(); return TRUE; }

			//复制数据
			HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,m_strOutPut.GetLength()+1);
			if (hData==NULL) 
			{
				CloseClipboard();
				return TRUE;
			}

			LPTSTR szMemName=(LPTSTR)GlobalLock(hData);
			lstrcpy(szMemName,m_strOutPut);
			SetClipboardData(CF_TEXT,hData);
			GlobalUnlock(hData);
			CloseClipboard();

			break;
		}
	case ID_32776:
		{
			//判断剪贴板的数据格式是否可以处理。
			if (!IsClipboardFormatAvailable(CF_TEXT)) return TRUE;

			//打开剪贴板。
			if (!OpenClipboard()) return TRUE;

			//获取UNICODE的数据。
			HGLOBAL hMem = GetClipboardData(CF_TEXT);
			if (hMem != NULL)
			{
				LPTSTR lpStr = (LPTSTR)GlobalLock(hMem);
				if (lpStr != NULL)
				{
					for (int i=0;i<strlen(lpStr);i++)
					{
						BYTE bTemp = lpStr[i]-'0';
						if(bTemp<0 || bTemp>9) 
						{
							AfxMessageBox(TEXT("黏贴的字符不符合标准！"),MB_ICONSTOP);
							return TRUE;
						}
					}
					m_strOutPut = lpStr;

					//释放锁内存。
					GlobalUnlock(hMem);
				}
			}

			//关闭剪贴板。
			CloseClipboard();
		}
		break;
	case ID_ABOUTBOX:		//关于窗口
		{
			CAboutDlg dlgAbout;
			dlgAbout.DoModal();
		}
		break;
	case IDC_BT_0:
	case IDC_BT_1:
	case IDC_BT_2:
	case IDC_BT_3:
	case IDC_BT_4:
	case IDC_BT_5:
	case IDC_BT_6:
	case IDC_BT_7:
	case IDC_BT_8:
	case IDC_BT_9:
		{
			UpdateData(TRUE);

			if ( !m_bPressEnable ) break;

			CString str;
			str.Format(TEXT("%d"),LOWORD(wParam)-IDC_BT_0);

			//之前是用+-*/做的运算结果，那么显示的结果在这里清除
			if ( !m_bPressNumber ) 
			{
				m_strOutPut = str;
				m_bPressNumber = true;
			}
			else
			{
				if ( (m_strOutPut.GetAt(0) == '0') && (m_strOutPut.GetAt(1) != '.')) 
					m_strOutPut = str;
				else m_strOutPut+=str;
			}

			m_bIsBaseCalc = false;
		}
		break;
	case IDC_BT_DIAN:
		{
			bool bInsertPoint = true;
			m_bIsBaseCalc = false;
			//查询输入的字符串中是否有小数点
			for(int i=0;i<m_strOutPut.GetLength();i++)
			{
				if( m_strOutPut.GetAt(i) == '.')
				{
					bInsertPoint = false;
					break;;
				}
			}

			if( bInsertPoint ) m_strOutPut+=TEXT(".");
		}
		break;
	case IDC_BT_SAVE:		//存储
		{
			m_ListSave.AddString(m_strOutPut);
			GetDlgItem(IDC_STATIC_M)->ShowWindow(SW_SHOW);
			if( m_bShowSave == false )
			{
				m_bShowSave = true;

				CRect rcClient;
				GetClientRect(&rcClient);
				RectifyControl(rcClient.Width(),rcClient.Height());
			}
		}
		break;
	case IDC_BT_CE:
		{
			if( !m_bPressNumber ) break;

			m_strOutPut = TEXT("0");
		}
		break;
	case IDC_BT_LEFT:	//退位
		{
			if( !m_bPressNumber ) break;
			m_strOutPut = m_strOutPut.Left(m_strOutPut.GetLength()-1);
			if ( m_strOutPut.GetLength() == 0 )
			{
				m_strOutPut=TEXT("0");
			}
		}
		break;
	case IDC_BT_FUSHU:	//负数符号
		{
			if( m_strOutPut.GetAt(0) == '-' ) m_strOutPut = m_strOutPut.Right(m_strOutPut.GetLength()-1);
			else m_strOutPut.Insert(0,'-');
		}
		break;
	case IDC_BT_KAIFANG:
		{					
			InsertRecord(en_Record_Sqrt);

			m_strOutPut.Format(TEXT("%.15lf"),sqrt(strtod(m_strOutPut,NULL)));

			//去除后面没用的0
			CheckData(m_strOutPut);

			m_bPressEnable = false;
		}
		break;
	}

	UpdateData(FALSE);

	return CDialog::OnCommand(wParam, lParam);
}

void CCalcFrameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	RectifyControl(cx,cy);
}

void CCalcFrameDlg::RectifyControl(int nWidth, int nHeight)
{
	CRect rcControl;
	CWnd *pWnd = NULL;
	CPoint pt(0,0);

	//根据窗口样式，调整控件位置
	for (int i=IDC_BT_MC;i<=IDC_STATIC_JIAOHU;i++)
	{
		pWnd = GetDlgItem(i);
		if( pWnd == NULL )continue;

		if ( m_enWindowStyle == en_Normal )
		{
			if ( i<=IDC_BT_9 )
			{
				CPosition::iterator iter = m_Position.find(i);
				if ( iter != m_Position.end() )
				{
					pWnd->SetWindowPos(NULL,iter->second.x-275,iter->second.y-50,0,0,SWP_NOSIZE);
				}
			}
			else
			{
				pWnd->ShowWindow(SW_HIDE);
			}
		}
		else
		{
			if ( i<=IDC_BT_9 )
			{
				CPosition::iterator iter = m_Position.find(i);
				if ( iter != m_Position.end() )
				{
					pWnd->SetWindowPos(NULL,iter->second.x,iter->second.y-50,0,0,SWP_NOSIZE);
				}
			}
			else
			{
				pWnd->ShowWindow(SW_SHOW);
			}
		}
	}
	
 	//移动控件
 	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;
 	HDWP hDwp=BeginDeferWindowPos(20);
 	
 	DeferWindowPos(hDwp,GetDlgItem(IDC_STATIC_EDIT)->GetSafeHwnd(),NULL,0,0,nWidth-25,60,SWP_NOMOVE);
 	DeferWindowPos(hDwp,GetDlgItem(IDC_STATIC_LIST)->GetSafeHwnd(),NULL,0,0,nWidth-40,15,SWP_NOMOVE);
 	DeferWindowPos(hDwp,GetDlgItem(IDC_STATIC_MAIN)->GetSafeHwnd(),NULL,0,0,nWidth-50,15,SWP_NOMOVE);

 	EndDeferWindowPos(hDwp);

	if ( m_enWindowStyle == en_Normal )
	{
		if( m_bShowSave )
			SetWindowPos(NULL,0,0,420,380,SWP_NOMOVE);
		else SetWindowPos(NULL,0,0,300,380,SWP_NOMOVE);
	}
	else if ( m_enWindowStyle == en_Science )
	{
		if( m_bShowSave )
			SetWindowPos(NULL,0,0,700,380,SWP_NOMOVE);
		else SetWindowPos(NULL,0,0,568,380,SWP_NOMOVE);
	}

	Invalidate(FALSE);
}

bool CCalcFrameDlg::GetCalc()
{
	//过滤无运算操作
	if( m_enCalcType == en_Null ) return false;

	UpdateData(TRUE);

	//这里没有用atof转换，因为此函数精度只能保证小数点后6位
	//为了保证更多的精度，这里选择了strtod函数
	double dNum1 = strtod(m_strResultOld,NULL);
	double dNum2 = strtod(m_strOutPut,NULL);

	double dResult = 0;

	//先将之前的输出结果保存起来
	m_strResultOld = m_strOutPut;

	switch ( m_enCalcType )
	{
	case en_Add:				//加法运算
		{
			dResult = dNum1+dNum2;
		}
		break;
	case en_Sub:				//减法运算
		{
			dResult = dNum1-dNum2;
		}
		break;
	case en_Mul:				//乘法运算
		{
			dResult = dNum1*dNum2;
		}
		break;
	case en_Div:				//除法运算
		{
			//除数不能为0
			if(dNum2 == 0 ) 
			{
				m_strOutPut = TEXT("结果未定义");
				UpdateData(FALSE);
				return true;
			}

			dResult = dNum1/dNum2;
		}
		break;
	case en_Pow:				//乘法运算
		{
			dResult = pow(dNum1,dNum2);
		}
	case en_Yroot:				//乘法运算
		{
			dResult = pow(dNum1,1/dNum2);
		}
		break;
	}

	//这里并没有使用dobule的全部精度，因为cpu对浮点数计算不是很好，
	//就算是strtod这个函数，仍然存在精度丢失的情况，但是问题不大，
	//所以舍弃最后的一个精度
	m_strOutPut.Format(TEXT("%.15lf"),dResult);

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);

	return true;
}

void CCalcFrameDlg::CheckData( CString &strData )
{
	int nIndex = 0;
	CString strTemp = strData;

	//如果没有小数点，即为整数，无需在做处理
	if ( strData.Find('.') == -1 ) return;
	
	for (nIndex=strTemp.GetLength();nIndex>=0;nIndex--)
	{
		if( (strTemp.GetAt(nIndex) != '0') && (strTemp.GetAt(nIndex) != '\0'))
		{
			//小数点后面的全是0，小数点也没有必要存在
			if ( strTemp.GetAt(nIndex) == '.')
			{
				nIndex--;
			}

			break;
		}
	}

	strData = strTemp.Left(nIndex+1);
}

void CCalcFrameDlg::InsertRecord( BYTE cbType )
{
	UpdateData(TRUE);

	switch (cbType)
	{
	case en_Record_Add:	
		{
			if( m_bIsBaseCalc )
			{
				if(m_strResult.GetAt(m_strResult.GetLength()-1)!=')')
					m_strResult.Delete(m_strResult.GetLength()-1,1);
				m_strResult+=TEXT("+");
			}
			else
			{
				m_strResult += m_strButtonOld;
				m_strResult += TEXT("+");
			}

			break;		
		}
	case en_Record_Sub:	
		{
			if( m_bIsBaseCalc )
			{
				if(m_strResult.GetAt(m_strResult.GetLength()-1)!=')')
					m_strResult.Delete(m_strResult.GetLength()-1,1);
				m_strResult+=TEXT("-");
			}
			else
			{
				m_strResult += m_strButtonOld;
				m_strResult += TEXT("-");
			}

			break;		
		}
	case en_Record_Mul:	
		{
			if( m_bIsBaseCalc )
			{
				if(m_strResult.GetAt(m_strResult.GetLength()-1)!=')')
					m_strResult.Delete(m_strResult.GetLength()-1,1);
				m_strResult+=TEXT("*");
			}
			else
			{
				m_strResult += m_strButtonOld;
				m_strResult += TEXT("*");
			}

			break;		
		}
	case en_Record_Div:	
		{
			if( m_bIsBaseCalc )
			{
				if(m_strResult.GetAt(m_strResult.GetLength()-1)!=')')
					m_strResult.Delete(m_strResult.GetLength()-1,1);
				m_strResult+=TEXT("/");
			}
			else
			{
				m_strResult += m_strButtonOld;
				m_strResult += TEXT("/");
			}

			break;		
		}
	case en_Record_Pow:	
		{
			m_strResult += m_strButtonOld;
			m_strResult += TEXT("^");

			break;		
		}
	case en_Record_Yroot:	
		{
			m_strResult += m_strButtonOld;
			m_strResult += TEXT("yroot");

			break;		
		}
	case en_Record_Equal:
		{
			m_strResultOld = TEXT("");
			m_strResult = TEXT("");
			break;
		}
	case en_Record_Sqrt:		InsertSpeRecord(TEXT("sqrt("));		break;		//开方
	case en_Record_Reciproc:	InsertSpeRecord(TEXT("Reciproc(")); break;		//倒数
	case en_Record_fact:		InsertSpeRecord(TEXT("fact("));		break;		//倒数
	case en_Record_Sqr:			InsertSpeRecord(TEXT("sqr("));		break;		//倒数
	case en_Record_Cube:		InsertSpeRecord(TEXT("cube("));		break;		//倒数
	case en_Record_PowTen:		InsertSpeRecord(TEXT("powten("));	break;		//倒数
	case en_Record_Cuberoot:	InsertSpeRecord(TEXT("cuberoot("));	break;		//倒数
	case en_Record_Log:			InsertSpeRecord(TEXT("log("));		break;		//倒数
	case en_Record_Int:			InsertSpeRecord(TEXT("Int("));		break;		//倒数
	case en_Record_Sin:			InsertSpeRecord(TEXT("sind("));		break;		//倒数
	case en_Record_Cos:			InsertSpeRecord(TEXT("cosd("));		break;		//倒数
	case en_Record_Tan:			InsertSpeRecord(TEXT("tand("));		break;		//倒数
	case en_Record_Asin:		InsertSpeRecord(TEXT("asin("));		break;		//倒数
	case en_Record_Acos:		InsertSpeRecord(TEXT("acos("));		break;		//倒数
	case en_Record_Atan:		InsertSpeRecord(TEXT("atan("));		break;		//倒数
	case en_Record_Sinh:		InsertSpeRecord(TEXT("sinh("));		break;		//倒数
	case en_Record_Cosh:		InsertSpeRecord(TEXT("cosh("));		break;		//倒数
	case en_Record_Tanh:		InsertSpeRecord(TEXT("tanh("));		break;		//倒数
	case en_Record_ln:			InsertSpeRecord(TEXT("ln("));		break;		//倒数
	}

	UpdateData(FALSE);
}

void CCalcFrameDlg::InsertSpeRecord( CString str )
{
	int nIndex = 0;
	if ( m_enCalcType == en_Add )  nIndex = m_strResult.ReverseFind('+')+1;
	else if ( m_enCalcType == en_Sub )  nIndex = m_strResult.ReverseFind('-')+1;
	else if ( m_enCalcType == en_Mul )  nIndex = m_strResult.ReverseFind('*')+1;
	else if ( m_enCalcType == en_Sub ) nIndex =  m_strResult.ReverseFind('/')+1;


	m_strResult.Insert(nIndex,str);

	if ( m_bPressNumber )
	{
		m_strResult+=m_strOutPut;
		m_bPressNumber = false;
	}
	else 
	{
		if( m_bIsBaseCalc )
		{
			m_strResult+=m_strOutPut;
			m_bPressNumber = false;
		}
	}
	
	m_strResult+=TEXT(")");
}

void CCalcFrameDlg::OnBnClickedBtJia()
{
	//保存之前按键数字的记录，用来计算,注意一点只是用户输出的数字才能在这里赋值，
	//计算出来的结果不能显示在记录里面
	if( m_bPressNumber )
		m_strButtonOld = m_strOutPut;

	//因为加法具有等于的作用，所以每次执行这个操作的时候，先计算一下值
	//m_bIsBaseCalc的作用，防止用户来回切换+-*/运算，同时可以去修改记录里面的运算符号
	if( !m_bIsBaseCalc ) GetCalc();

	//先将之前的输出结果保存起来
	m_strResultOld = m_strOutPut;

	m_enCalcType = en_Add;

	InsertRecord(en_Record_Add);

	m_bPressNumber = false;
	m_bPressEnable = true;
	m_bIsBaseCalc = true;
}

void CCalcFrameDlg::OnBnClickedBtJian()
{
	if( m_bPressNumber ) m_strButtonOld = m_strOutPut;

	if( !m_bIsBaseCalc ) GetCalc();

	m_strResultOld = m_strOutPut;

	m_enCalcType = en_Sub;

	InsertRecord(en_Record_Sub);

	m_bPressNumber = false;
	m_bPressEnable = true;
}

void CCalcFrameDlg::OnBnClickedBtCheng()
{
	if( m_bPressNumber ) m_strButtonOld = m_strOutPut;

	if( !m_bIsBaseCalc ) GetCalc();

	m_strResultOld = m_strOutPut;

	m_enCalcType = en_Mul;

	InsertRecord(en_Record_Mul);

	m_bPressNumber = false;
	m_bPressEnable = true;
}

void CCalcFrameDlg::OnBnClickedBtChu()
{
	if( m_bPressNumber ) m_strButtonOld = m_strOutPut;

	if( !m_bIsBaseCalc ) GetCalc();

	GetCalc();

	m_strResultOld = m_strOutPut;

	m_enCalcType = en_Div;

	InsertRecord(en_Record_Div);

	m_bPressNumber = false;
	m_bPressEnable = true;
}

void CCalcFrameDlg::OnBnClickedBtDengyu()
{
	GetCalc();

	m_bPressNumber = false;

	InsertRecord(en_Record_Equal);

	m_strButtonOld = m_strOutPut;
}

/////////////////////////////////////////////////////////
//以下是特殊算法

void CCalcFrameDlg::OnBnClickedBtDaoshu()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Reciproc);

	m_strOutPut.Format(TEXT("%.15lf"),1/strtod(m_strOutPut,NULL));

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtPai()
{
	//int a=10000,b,c=2800,d,e,f[2801],g; 

	//for(;b-c;) f[b++]=a/5; 

	//for(;d=0,g=c*2;c-=14,printf("%.4d",e+d/a),e=d%a) 
	//	for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b);
	UpdateData(TRUE);

	if ( !m_bPressNumber ) 
	{
		m_strOutPut = TEXT("3.1415926535897932384626433832795");
		m_bPressNumber = true;
	}

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtPingfang()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Sqr);

	m_strOutPut.Format(TEXT("%.15lf"),pow(strtod(m_strOutPut,NULL),2));

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtCifang()
{
	if( m_bPressNumber )
		m_strButtonOld = m_strOutPut;

	GetCalc();

	m_strResultOld = m_strOutPut;

	m_enCalcType = en_Pow;

	InsertRecord(en_Record_Pow);

	m_bPressNumber = false;
}

void CCalcFrameDlg::OnBnClickedBtLifang()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Cube);

	m_strOutPut.Format(TEXT("%.15lf"),pow(strtod(m_strOutPut,NULL),3));

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtShicifang()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_PowTen);

	m_strOutPut.Format(TEXT("%.15lf"),pow(10.0,strtod(m_strOutPut,NULL)));

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtJiecheng()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_fact);

	if ( (m_strOutPut.Find('.') != -1) || (m_strOutPut.Find('-') != -1) )
	{
		m_strOutPut = TEXT("无效输入");
		return;
	}

	int nInput = atoi(m_strOutPut);

	if ( nInput*5 > 10000 ) 
	{
		m_strOutPut = TEXT("溢出");
		UpdateData(FALSE);
		return;
	}

	int *pArray = new int[nInput*5];

	for (int i=0;i<nInput*5;i++) pArray[i] = 1;

	int i=0,c=0,m=0;
	for(;nInput;nInput--)
	{
		for(c=i=0;i<=m;i++)
			pArray[i]=(c+=pArray[i]*nInput)%10,c/=10;

		while(c)pArray[++m]=c%10,c/=10;
	}

	m_strOutPut = TEXT("");

	int nValue=0;

	//数字大于28位，用科学表示法显示
	if( m>=32 )
	{
		for (int i=0;i<=32;i++)
		{
			nValue = pArray[m--];
			m_strOutPut.Insert(i,ITOA(nValue));
		}

		m_strOutPut.Insert(1,'.');
		m_strOutPut+=TEXT("e+");

		CString str;
		str.Format(TEXT("%d"),m+33);
		m_strOutPut+=str;
	}
	else
	{
		for(int nIndex=0;m>=0;nIndex++)
		{
			nValue = pArray[m--];
			m_strOutPut.Insert(nIndex,ITOA(nValue));
		}
	}

	SafeDeleteArray(pArray);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtKailifang()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Cuberoot);

	m_strOutPut.Format(TEXT("%.15lf"),pow(strtod(m_strOutPut,NULL),1/3.0));

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtKailifangn()
{
	if( m_bPressNumber )
		m_strButtonOld = m_strOutPut;

	GetCalc();

	m_strResultOld = m_strOutPut;

	m_enCalcType = en_Yroot;

	InsertRecord(en_Record_Pow);

	m_bPressNumber = false;
}

void CCalcFrameDlg::OnBnClickedBtLog()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Log);

	m_strOutPut.Format(TEXT("%.15lf"),log(strtod(m_strOutPut,NULL)));

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtInt()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Int);

	int nIndex = m_strOutPut.Find('.');
	
	if(nIndex!= -1)
		m_strOutPut = m_strOutPut.Left(nIndex);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtSin()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Sin);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),sin(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),sin(180*strtod(m_strOutPut,NULL)/PI));
	}

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtCos()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Cos);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),cos(strtod(m_strOutPut,NULL)));	
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),cos(180*strtod(m_strOutPut,NULL)/PI));
	}
	
	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtTan()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Tan);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),tan(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),tan(180*strtod(m_strOutPut,NULL)/PI));
	}
	
	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtAsin()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Asin);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),asin(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),asin(180*strtod(m_strOutPut,NULL)/PI));
	}

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);	
}

void CCalcFrameDlg::OnBnClickedBtAcos()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Acos);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),acos(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),acos(180*strtod(m_strOutPut,NULL)/PI));
	}
	
	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);	
}

void CCalcFrameDlg::OnBnClickedBtAtan()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Atan);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),atan(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),atan(180*strtod(m_strOutPut,NULL)/PI));
	}
	
	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);	
}

void CCalcFrameDlg::OnBnClickedBtSinh()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Sinh);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),sinh(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),sinh(180*strtod(m_strOutPut,NULL)/PI));
	}

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtCosh()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Cosh);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),cosh(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),cosh(180*strtod(m_strOutPut,NULL)/PI));
	}

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);	
}

void CCalcFrameDlg::OnBnClickedBtTanh()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_Tanh);

	if ( IsDlgButtonChecked(IDC_JIAODU) == BST_CHECKED )
	{
		m_strOutPut.Format(TEXT("%.15lf"),tanh(strtod(m_strOutPut,NULL)));
	}
	else
	{
		m_strOutPut.Format(TEXT("%.15lf"),tanh(180*strtod(m_strOutPut,NULL)/PI));
	}
	
	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);	
}

void CCalcFrameDlg::OnBnClickedBtLn()
{
	UpdateData(TRUE);

	InsertRecord(en_Record_ln);

	m_strOutPut.Format(TEXT("%.15lf"),log(strtod(m_strOutPut,NULL))/log(2.718281828));

	//去除后面没用的0
	CheckData(m_strOutPut);

	UpdateData(FALSE);	
}

LRESULT CCalcFrameDlg::OnRecifyView( WPARAM wParam,LPARAM lParam )
{	
	m_bShowSave = false;

	CRect rcClient;
	GetClientRect(&rcClient);

	RectifyControl(rcClient.Width(),rcClient.Height());

	GetDlgItem(IDC_STATIC_M)->ShowWindow(SW_HIDE);

	return TRUE;
}

void CCalcFrameDlg::OnBnClickedBtC()
{
	UpdateData(TRUE);

	m_enCalcType = en_Null;
	m_strResult = TEXT("");
	m_strButtonOld = TEXT("");
	m_strOutPut = TEXT("0");
	m_bPressEnable = true;

	UpdateData(FALSE);
}

void CCalcFrameDlg::OnBnClickedBtMc()
{
	if( AfxMessageBox(TEXT("您确定要删除全部记录么？"),MB_YESNO) == IDYES )
	{
		m_ListSave.ResetContent();
		OnRecifyView(0,0);
	}
}

void CCalcFrameDlg::OnBnClickedBtDaxie()
{
	CapsDlg _CapsDlg(m_strOutPut);
	_CapsDlg.DoModal();
}

// apsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CalcFrame.h"
#include "apsDlg.h"

//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

// CapsDlg 对话框
//变量定义
LPCTSTR pszNumber[]={TEXT("零"),TEXT("壹"),TEXT("贰"),TEXT("叁"),TEXT("肆"),TEXT("伍"),TEXT("陆"),TEXT("柒"),TEXT("捌"),TEXT("玖")};
LPCTSTR pszWeiName[]={TEXT("拾"),TEXT("佰"),TEXT("仟"),TEXT("万"),TEXT("拾"),TEXT("佰"),TEXT("仟"),TEXT("亿"),TEXT("拾"),TEXT("佰"),TEXT("仟"),TEXT("万")};

IMPLEMENT_DYNAMIC(CapsDlg, CDialog)

CapsDlg::CapsDlg(CString Str,CWnd* pParent /*=NULL*/): CDialog(IDD_CAPITAL, pParent)
{
	m_strCap = Str;
}

CapsDlg::~CapsDlg()
{
}

void CapsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CapsDlg, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BT_COPY, &CapsDlg::OnBnClickedBtCopy)
END_MESSAGE_MAP()

// CapsDlg 消息处理程序

BOOL CapsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if ( m_strCap.GetLength() >13 )
	{
		AfxMessageBox(TEXT("数据太长，无法转换！"),MB_ICONSTOP);
		return TRUE;
	}

	TCHAR szBuffer[128]={0};

	int nPointIndex = m_strCap.Find('.');
	if( nPointIndex != -1)
	{
		CString strLeft = m_strCap.Left(nPointIndex);
		CString strRight = m_strCap.Right(m_strCap.GetLength()-nPointIndex-1);

		SwitchScoreString(_atoi64(strLeft),szBuffer,CountArray(szBuffer));
		strcat(szBuffer,TEXT("点"));

		for (int i=0;i<strRight.GetLength();i++)
		{
			strcat(szBuffer,pszNumber[strRight.GetAt(i)-'0']);
		}
	}
	else SwitchScoreString(_atoi64(m_strCap),szBuffer,CountArray(szBuffer));

	SetDlgItemText(IDC_EDIT_CAP,szBuffer);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

VOID CapsDlg::SwitchScoreString( __int64 lScore, LPTSTR pszBuffer, WORD wBufferSize )
{
	//转换数值
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//变量定义
	bool bNeedFill=false;
	bool bNeedZero=false;
	UINT uTargetIndex=0,uSourceIndex=0;

	//字符长度
	UINT uItemLength=lstrlen(pszNumber[0]);
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//转换操作
	for (UINT i=0;i<uSwitchLength;i++)
	{
		//变量定义
		WORD wNumberIndex=szSwitchScore[i]-TEXT('0');

		//补零操作
		if ((bNeedZero==true)&&(wNumberIndex!=0L))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszNumber[0],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//拷贝数字
		if (wNumberIndex!=0L)
		{
			_tcsncat(pszBuffer,pszNumber[wNumberIndex],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//拷贝位名
		if ((wNumberIndex!=0L)&&((uSwitchLength-i)>=2))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//补零判断
		if ((bNeedZero==false)&&(wNumberIndex==0))
		{
			bNeedZero=true;
		}

		//补位判断
		if ((bNeedFill==false)&&(wNumberIndex!=0))
		{
			bNeedFill=true;
		}

		//填补位名
		if (((uSwitchLength-i)==5)||((uSwitchLength-i)==9))
		{
			//拷贝位名
			if ((bNeedFill==true)&&(wNumberIndex==0L))
			{
				_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
			}

			//设置变量
			bNeedZero=false;
			bNeedFill=false;
		}
	}
}

void CapsDlg::OnBnClickedBtCopy()
{
	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CAP);
	pEdit->Copy();
}

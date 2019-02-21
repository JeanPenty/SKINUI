// apsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CalcFrame.h"
#include "apsDlg.h"

//����ά��
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

// CapsDlg �Ի���
//��������
LPCTSTR pszNumber[]={TEXT("��"),TEXT("Ҽ"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("½"),TEXT("��"),TEXT("��"),TEXT("��")};
LPCTSTR pszWeiName[]={TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��")};

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

// CapsDlg ��Ϣ�������

BOOL CapsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if ( m_strCap.GetLength() >13 )
	{
		AfxMessageBox(TEXT("����̫�����޷�ת����"),MB_ICONSTOP);
		return TRUE;
	}

	TCHAR szBuffer[128]={0};

	int nPointIndex = m_strCap.Find('.');
	if( nPointIndex != -1)
	{
		CString strLeft = m_strCap.Left(nPointIndex);
		CString strRight = m_strCap.Right(m_strCap.GetLength()-nPointIndex-1);

		SwitchScoreString(_atoi64(strLeft),szBuffer,CountArray(szBuffer));
		strcat(szBuffer,TEXT("��"));

		for (int i=0;i<strRight.GetLength();i++)
		{
			strcat(szBuffer,pszNumber[strRight.GetAt(i)-'0']);
		}
	}
	else SwitchScoreString(_atoi64(m_strCap),szBuffer,CountArray(szBuffer));

	SetDlgItemText(IDC_EDIT_CAP,szBuffer);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

VOID CapsDlg::SwitchScoreString( __int64 lScore, LPTSTR pszBuffer, WORD wBufferSize )
{
	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	bool bNeedFill=false;
	bool bNeedZero=false;
	UINT uTargetIndex=0,uSourceIndex=0;

	//�ַ�����
	UINT uItemLength=lstrlen(pszNumber[0]);
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת������
	for (UINT i=0;i<uSwitchLength;i++)
	{
		//��������
		WORD wNumberIndex=szSwitchScore[i]-TEXT('0');

		//�������
		if ((bNeedZero==true)&&(wNumberIndex!=0L))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszNumber[0],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//��������
		if (wNumberIndex!=0L)
		{
			_tcsncat(pszBuffer,pszNumber[wNumberIndex],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//����λ��
		if ((wNumberIndex!=0L)&&((uSwitchLength-i)>=2))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//�����ж�
		if ((bNeedZero==false)&&(wNumberIndex==0))
		{
			bNeedZero=true;
		}

		//��λ�ж�
		if ((bNeedFill==false)&&(wNumberIndex!=0))
		{
			bNeedFill=true;
		}

		//�λ��
		if (((uSwitchLength-i)==5)||((uSwitchLength-i)==9))
		{
			//����λ��
			if ((bNeedFill==true)&&(wNumberIndex==0L))
			{
				_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
			}

			//���ñ���
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

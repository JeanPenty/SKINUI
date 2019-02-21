// ProgressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProgressDlg.h"
#include "Resource.h"

// CProgressDlg 对话框

IMPLEMENT_DYNAMIC(CProgressDlg, CDlgControlItem)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_PROGRESS, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_PROGRESS1,m_ProgressCtrl1);
	DDX_Control(pDX,IDC_PROGRESS2,m_ProgressCtrl2);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDlgControlItem)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CProgressDlg::OnTimer( UINT_PTR nIDEvent )
{
	if ( nIDEvent == 0 )
	{
		m_ProgressCtrl1.StepIt();
		m_ProgressCtrl2.StepIt();
	}
}


// CProgressDlg 消息处理程序
BOOL CProgressDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	m_ProgressCtrl1.SetRange(0,100);
	m_ProgressCtrl1.SetPos(10);
	m_ProgressCtrl1.SetStep(20);

	m_ProgressCtrl1.SetBackImage(TEXT("Res\\progress\\progress_bg.png"));
	m_ProgressCtrl1.SetStepImage(TEXT("Res\\progress\\Contrast.png"));
	m_ProgressCtrl1.SetFloatImage(TEXT("Res\\progress\\Sip.png"),30);
	m_ProgressCtrl1.SetPos(100);

	m_ProgressCtrl2.SetRange(0,200);
	m_ProgressCtrl2.SetParentBack(GetBackDC());
	m_ProgressCtrl2.SetBackImage(TEXT("Res\\progress\\Vprogress_bg.png"));
	m_ProgressCtrl2.SetStepImage(TEXT("Res\\progress\\VContrast.png"));
	m_ProgressCtrl2.SetFloatImage(TEXT("Res\\progress\\VSip.png"),30);
	m_ProgressCtrl2.SetPos(200);
	m_ProgressCtrl2.SetStep(10);

	SetTimer(0,500,NULL);

	return TRUE;
}
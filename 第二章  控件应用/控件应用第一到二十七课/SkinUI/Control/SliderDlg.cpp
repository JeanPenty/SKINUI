// SliderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SliderDlg.h"
#include "resource.h"

// CSliderDlg 对话框

IMPLEMENT_DYNAMIC(CSliderDlg, CDlgControlItem)

CSliderDlg::CSliderDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(IDD_SLIDER, pParent)
{

}

CSliderDlg::~CSliderDlg()
{
}

void CSliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_SLIDER3,m_SliderCtrl);
	DDX_Control(pDX,IDC_SLIDER2,m_SliderCtrl2);
	DDX_Control(pDX,IDC_SLIDER1,m_SliderCtrl3);
	DDX_Control(pDX,IDC_SLIDER5,m_SliderCtrl4);
}


BEGIN_MESSAGE_MAP(CSliderDlg, CDlgControlItem)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1,OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON14,OnBnClickedButton2)
END_MESSAGE_MAP()

BOOL CSliderDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	m_SliderCtrl.SetRange(0,40);
	m_SliderCtrl.SetPos(20);


	m_SliderCtrl2.SetTicFreq(10);
	m_SliderCtrl2.SetTic(15);

	m_SliderCtrl2.SetBuddy(GetDlgItem(IDC_EDIT2),FALSE);
	SetDlgItemInt(IDC_EDIT2,m_SliderCtrl2.GetPos());

	m_SliderCtrl3.SetParentBack(GetBackDC());
	m_SliderCtrl3.SetBackImage(TEXT("Res\\SliderCtrl\\individuation.png"));
	m_SliderCtrl3.SetThumImage(TEXT("Res\\SliderCtrl\\individuation_bar.png"));
	m_SliderCtrl3.SetDisImage(TEXT("Res\\SliderCtrl\\individuation_disable.png"));
	m_SliderCtrl3.SetRange(0,100);
	m_SliderCtrl3.SetPos(10);

	m_SliderCtrl4.SetParentBack(GetBackDC());
	m_SliderCtrl4.SetBackImage(TEXT("Res\\SliderCtrl\\sound_back.png"));
	m_SliderCtrl4.SetButtonImage(TEXT("Res\\SliderCtrl\\sound_button.png"));
	m_SliderCtrl4.SetTraceImage(TEXT("Res\\SliderCtrl\\sound_Trace.png"));
	m_SliderCtrl4.SetRange(0,100);
	m_SliderCtrl4.SetPos(100);


	return TRUE;
}


void CSliderDlg::OnBnClickedButton1()
{
	SetDlgItemInt(IDC_EDIT1,m_SliderCtrl.GetPos());
}

void CSliderDlg::OnBnClickedButton2()
{
	SetDlgItemInt(IDC_EDIT1,m_SliderCtrl2.GetNumTics());
}

// CSliderDlg 消息处理程序
void CSliderDlg::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	if( (pScrollBar != NULL) && ((CSliderCtrl*)pScrollBar == &m_SliderCtrl2) )
		SetDlgItemInt(IDC_EDIT2,m_SliderCtrl2.GetPos());

	if( (pScrollBar != NULL) && ((CSliderCtrl*)pScrollBar == &m_SliderCtrl4) )
		SetDlgItemInt(IDC_EDIT2,m_SliderCtrl4.GetPos());

	CDlgControlItem::OnHScroll(nSBCode, nPos, pScrollBar);
}

// ListBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "ListBoxDlg.h"


// CListBoxDlg �Ի���

IMPLEMENT_DYNAMIC(CListBoxDlg, CDlgControlItem)

CListBoxDlg::CListBoxDlg(CWnd* pParent /*=NULL*/)
	: CDlgControlItem(CListBoxDlg::IDD, pParent)
{

}

CListBoxDlg::~CListBoxDlg()
{
}

void CListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgControlItem::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_ListBox);
	DDX_Control(pDX,IDC_LIST2,m_ListBox2);
}


BEGIN_MESSAGE_MAP(CListBoxDlg, CDlgControlItem)
	ON_BN_CLICKED(IDC_BUTTON1, &CListBoxDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON14, &CListBoxDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CListBoxDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CListBoxDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON15, &CListBoxDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON18, &CListBoxDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON2, &CListBoxDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CListBoxDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CListBoxDlg::OnBnClickedButton4)
	ON_RBN_DBLCLK(IDC_LIST1, &CListBoxDlg::OnRbnDblclkList1)
	ON_RBN_DBLCLK(IDC_LIST2, &CListBoxDlg::OnRbnDblclkList2)
END_MESSAGE_MAP()


// CListBoxDlg ��Ϣ�������



BOOL CListBoxDlg::OnInitDialog()
{
	CDlgControlItem::OnInitDialog();

	m_ListBox.SetBackNormalImage(TEXT("Res\\Edit\\frameBorderEffect_mouseDownDraw.png"),CRect(3,3,3,3));
	m_ListBox.SetSelectImage(TEXT("Res\\ComboBox\\listitem_select.png"),CRect(3,3,3,3));
	m_ListBox.SetHovenImage(TEXT("Res\\ListBox\\highlight.png"),CRect(3,3,3,3));


	m_ListBox2.SetBackNormalImage(TEXT("Res\\Edit\\frameBorderEffect_mouseDownDraw.png"),CRect(3,3,3,3));
	m_ListBox2.SetSelectImage(TEXT("Res\\ComboBox\\listitem_select.png"),CRect(3,3,3,3));
 	m_ListBox2.SetHovenImage(TEXT("Res\\ListBox\\highlight.png"),CRect(3,3,3,3));
	m_ListBox2.SetScrollImage(&m_ListBox2,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));

	m_ListBox2.AddString(TEXT("�ҵĺ���"));
	m_ListBox2.AddString(TEXT("MFC"));
	m_ListBox2.AddString(TEXT("C++"));
	m_ListBox2.AddString(TEXT("VC"));
	m_ListBox2.AddString(TEXT("C#"));
	m_ListBox2.AddString(TEXT("İ����"));
	m_ListBox2.AddString(TEXT("Dephi"));
	m_ListBox2.AddString(TEXT("python"));
	m_ListBox2.AddString(TEXT("Lua"));
	m_ListBox2.AddString(TEXT("java"));

	for (int i=1;i<m_ListBox2.GetCount();i++)
	{
		if ( i==5) continue;

		m_ListBox2.SetItemHeight(i,50);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CListBoxDlg::OnBnClickedButton1()
{
	static int i=0;
	CString str;
	str.Format(TEXT("Item_%d"),++i);
	m_ListBox.AddString(str);

	m_ListBox.SetItemHeight(1,40);
}

void CListBoxDlg::OnBnClickedButton14()
{
	for (int i=m_ListBox.GetCount();i>=0;i--)
	{
		if ( m_ListBox.GetSel(i) )
		{
			m_ListBox.DeleteString(i);
		}
	}
}

void CListBoxDlg::OnBnClickedButton16()
{
	CString str=TEXT("��ǰѡ�еĽڵ�����Ϊ��"),strTemp;
	for (int i=0;i<m_ListBox.GetCount();i++)
	{
		if ( m_ListBox.GetSel(i) )
		{
			strTemp.Format(TEXT("[ %d ]"),i);
			str+=strTemp;
		}
	}

	MessageBox(str);
}

void CListBoxDlg::OnBnClickedButton17()
{
	CString str;
	str.Format(TEXT("ѡ�нڵ�������� %d ��"),m_ListBox.GetSelCount());
	MessageBox(str);
}

void CListBoxDlg::OnBnClickedButton15()
{
	CString str;
	str.Format(TEXT("�ڵ��������Ϊ %d ��"),m_ListBox.GetCount());
	MessageBox(str);
}

void CListBoxDlg::OnBnClickedButton18()
{
	CString str=TEXT("��ǰѡ�еĽڵ���ı�����Ϊ��"),strTemp,strItem;
	for (int i=0;i<m_ListBox.GetCount();i++)
	{
		if ( m_ListBox.GetSel(i) )
		{
			m_ListBox.GetText(i,strItem);
			strTemp.Format(TEXT("[ %s ]"),strItem);
			str+=strTemp;
		}
	}

	MessageBox(str);
}

void CListBoxDlg::OnBnClickedButton2()
{
	CString str,strTemp,strItem=TEXT("���ҵ��ַ���ƥ����ֱ�Ϊ��");
	GetDlgItemText(IDC_EDIT1,str);

	bool bHave = false;

	for (int i=0;i<m_ListBox.GetCount();i++)
	{
		if( m_ListBox.FindStringExact(i,str)!= LB_ERR )
		{
			bHave = true;
			strTemp.Format(TEXT("[ %d ]"),i);
			strItem+=strTemp;
		}
	}

	if(bHave)
		MessageBox(strItem);
	else MessageBox(TEXT("û�к��ʵ�ƥ����"));
}

void CListBoxDlg::OnBnClickedButton3()
{
	CString str,strTemp,strItem=TEXT("���ҵ��ַ���ƥ����ֱ�Ϊ��");
	GetDlgItemText(IDC_EDIT1,str);

	bool bHave = false;

	for (int i=0;i<m_ListBox.GetCount();i++)
	{
		if( m_ListBox.SelectString(i,str)!= LB_ERR )
		{
			bHave = true;
			strTemp.Format(TEXT("[ %d ]"),i);
			strItem+=strTemp;
		}
	}

	if(bHave)
		MessageBox(strItem);
	else MessageBox(TEXT("û�к��ʵ�ƥ����"));
}

void CListBoxDlg::OnBnClickedButton4()
{
	OpenLink(TEXT("http://www.gymsaga.com/project/444.html"));
}

void CListBoxDlg::OnRbnDblclkList1()
{
	CString str;
	str.Format(TEXT("ѡ�еĽڵ�Ϊ��%d"),m_ListBox.GetCurSel());

	MessageBox(str);
}

void CListBoxDlg::OnRbnDblclkList2()
{
	CString str;
	str.Format(TEXT("ѡ�еĽڵ�Ϊ��%d"),m_ListBox2.GetCurSel());

	MessageBox(str);
}

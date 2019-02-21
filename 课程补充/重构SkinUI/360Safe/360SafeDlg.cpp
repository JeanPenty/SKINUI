
// 360SafeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "360Safe.h"
#include "360SafeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy360SafeDlg �Ի���




CMy360SafeDlg::CMy360SafeDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CMy360SafeDlg::IDD,TEXT("360Safe.xml"), pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy360SafeDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy360SafeDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(5006,OnBnClickCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CMy360SafeDlg ��Ϣ�������

BOOL CMy360SafeDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	((CSkinTabCtrl*)GetDlgItem(5900))->SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy360SafeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CSkinDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy360SafeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy360SafeDlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

	__super::OnLButtonDown(nFlags,point);
}

void CMy360SafeDlg::OnBnClickCheck()
{
	for (int i=2;i<7;i++)
	{
		GetString(i)->bVisible = false;
	}

	GetString(7)->bVisible = true;
	GetImage(7)->bVisible = false;

	GetDlgItem(5006)->ShowWindow(SW_HIDE);

	Invalidate(FALSE);
}


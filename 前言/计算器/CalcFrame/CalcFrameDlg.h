// CalcFrameDlg.h : ͷ�ļ�
//

#pragma once
#include <map>
using namespace std;

#include "CAboutDlg.h"
#include "ListBoxEx.h"

enum enWindowStyle
{
	en_Normal,
	en_Science,
};

enum enCalcType
{
	en_Null,
	en_Add,
	en_Sub,
	en_Mul,
	en_Div,
	en_Pow,
	en_Yroot,
	en_Calc
};


typedef map<UINT,CPoint>	CPosition;

// CCalcFrameDlg �Ի���
class CCalcFrameDlg : public CDialog
{
	enum
	{
		en_Record_Add,
		en_Record_Sub,
		en_Record_Mul,
		en_Record_Div,
		en_Record_Equal,
		en_Record_Sqrt,
		en_Record_Reciproc,
		en_Record_Sqr,
		en_Record_Pow,
		en_Record_Cube,
		en_Record_PowTen,
		en_Record_Cuberoot,
		en_Record_Yroot,
		en_Record_Log,
		en_Record_Int,
		en_Record_Sin,
		en_Record_Cos,
		en_Record_Tan,
		en_Record_Asin,
		en_Record_Acos,
		en_Record_Atan,
		en_Record_Sinh,
		en_Record_Cosh,
		en_Record_Tanh,
		en_Record_ln,
		en_Record_fact
	};

	//ʵ��
protected:
	HICON								m_hIcon;				//����ͼ��
	enWindowStyle						m_enWindowStyle;		//������ʽ
	enCalcType							m_enCalcType;			//���㷽ʽ
	CPosition							m_Position;				//�ؼ�λ��
	CString								m_strOutPut;			//�����Ϣ	
	CString								m_strButtonOld;			//֮ǰ����
	CString								m_strResultOld;			//֮ǰ���
	CString								m_strResult;			//ͳ����Ϣ				
	bool								m_bShowSave;			//��ʾ�洢						
	bool								m_bFront;				//��ǰ��ʾ	
	bool								m_bPressNumber;			//�����ּ�
	bool								m_bPressEnable;			//����ʧЧ
	bool								m_bIsBaseCalc;			//��ǰ����
	CListBoxEx							m_ListSave;				//�洢�б�					

	//����
public:
	CCalcFrameDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
	//�̳к���
protected:
	//DDX/DDV ֧��
	virtual void DoDataExchange(CDataExchange* pDX);	
	//��ʼ��
	virtual BOOL OnInitDialog();
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//��Ϣӳ��
public:
	//ϵͳ����
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//�������
	afx_msg void OnPaint();
	//
	afx_msg HCURSOR OnQueryDragIcon();
	//���ڴ�С
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	DECLARE_MESSAGE_MAP()

	//���溯��
public:
	//�����ؼ�
	void RectifyControl(int nWidth, int nHeight);
	//
	bool GetCalc();
	//Ч������--�����ֺ�����Ч��0ȥ��
	void CheckData(CString &strData);
	//�����¼
	void InsertRecord(BYTE cbType);

	void InsertSpeRecord( CString str );

	afx_msg void OnBnClickedBtJia();
	afx_msg void OnBnClickedBtJian();
	afx_msg void OnBnClickedBtCheng();
	afx_msg void OnBnClickedBtChu();
	afx_msg void OnBnClickedBtDengyu();
	afx_msg void OnBnClickedBtDaoshu();
	afx_msg void OnBnClickedBtPai();
	afx_msg void OnBnClickedBtPingfang();
	afx_msg void OnBnClickedBtCifang();
	afx_msg void OnBnClickedBtLifang();
	afx_msg void OnBnClickedBtShicifang();
	afx_msg void OnBnClickedBtJiecheng();
	afx_msg void OnBnClickedBtKailifang();
	afx_msg void OnBnClickedBtKailifangn();
	afx_msg void OnBnClickedBtLog();
	afx_msg void OnBnClickedBtInt();
	afx_msg void OnBnClickedBtSin();
	afx_msg void OnBnClickedBtCos();
	afx_msg void OnBnClickedBtTan();
	afx_msg void OnBnClickedBtAsin();
	afx_msg void OnBnClickedBtAcos();
	afx_msg void OnBnClickedBtAtan();
	afx_msg void OnBnClickedBtSinh();
	afx_msg void OnBnClickedBtCosh();
	afx_msg void OnBnClickedBtTanh();
	afx_msg void OnBnClickedBtLn();
	afx_msg void OnBnClickedBtC();
	afx_msg void OnBnClickedBtMc();
	afx_msg void OnBnClickedBtDaxie();
	LRESULT OnRecifyView(WPARAM wParam,LPARAM lParam);
};

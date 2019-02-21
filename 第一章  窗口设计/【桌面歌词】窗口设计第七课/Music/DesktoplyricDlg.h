#ifndef LYRIC_HEAD_FILE
#define LYRIC_HEAD_FILE

#pragma once

#include <vector>
using namespace std;

// CDesktoplyricDlg �Ի���
typedef vector<CString>			CArraylyric;

class CDesktoplyricDlg : public CDialog
{
	DECLARE_DYNAMIC(CDesktoplyricDlg)

	//��������
protected:
	HBITMAP						m_hMemBmp;				//�ڴ滭��
	BYTE						* m_pBits;				//ͼ������
	DWORD						m_dwSize;				//ͼ���С
	DWORD 						m_dwEffWidth;			//Ч�����	
	INT							m_nFontSize;			//���ִ�С
	TCHAR 						m_szText[MAX_PATH];		//��ǰ��ʾ
	CArraylyric					m_Arraylyric;			//�������

	//��������
public:
	//���캯��
	CDesktoplyricDlg(CWnd* pParent = NULL);
	//��������
	virtual ~CDesktoplyricDlg();

	//���ܺ���
public:
	//���´���
	void UpdateLayered();
	//��������
	void DrawTextString(LPTSTR lpszText,CRect rc,COLORREF clr1,COLORREF clr2,UINT nFontSize=30,DWORD dwFlag=DT_CENTER|DT_VCENTER|DT_SINGLELINE,CFont* pFont=NULL);
	//������Ӱ
	void DrawTextShadow(LPTSTR lpszText,CRect rc,COLORREF clrText,UINT nFontSize=30,DWORD dwFlag=DT_CENTER|DT_VCENTER|DT_SINGLELINE,CFont* pFont=NULL);
	//���ø��
	void SetLyric(CString lpszText);
	//�򿪸��
	void OpenLyric(LPCTSTR lpPath);

protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange* pDX); 
	//��ʼ��
	virtual BOOL OnInitDialog();

	//��Ϣӳ��
public:
	//���ڳߴ�
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��ʱ��Ϣ
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif
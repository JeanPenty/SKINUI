#ifndef LAYERED_HEAD_FILE
#define LAYERED_HEAD_FILE

#pragma once
#include "ImageEx.h"
#include <atlimage.h>

//�ֲ㴰��
class CLayeredWindow : public CWnd
{
	DECLARE_DYNAMIC(CLayeredWindow)
	
	//��������
protected:
	CWnd *							m_pWndControl;						//�ؼ�����

	//��������
public:
	//���캯��
	CLayeredWindow();
	//��������
	virtual ~CLayeredWindow();

	//���ܺ���
public:
	//��������
	VOID CreateLayered(CWnd * pWndControl, CRect & rcWindow);
	//��������
	VOID InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);
	//��������
	VOID InitLayeredArea(CImageEx & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);

	//��Ϣӳ��
protected:
	//�ر���Ϣ
	VOID OnClose();
	//������Ϣ
	VOID OnSetFocus(CWnd * pOldWnd);

	//��̬����
protected:
	//ö�ٺ���
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
class CLayeredDialog : public CDialog
{
	DECLARE_DYNAMIC(CLayeredDialog)

	//��������
protected:
	CImageEx					m_ImageBack;			//����ͼƬ
	CLayeredWindow				m_LayeredWindow;		//�ֲ㴰��

	//��������
public:
	//���캯��
	CLayeredDialog(UINT uTemplate, CWnd* pParent = NULL); 
	//��������
	virtual ~CLayeredDialog();

protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange* pDX);
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight){}

	//��������
public:
	//��ʼ��
	void SetLayeredDialog(HINSTANCE hInstance,LPCTSTR lpResource,CSize szSizeLT,CSize szSizeRB);
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//ȥ���߿�
	void RemoveBorder();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
#endif

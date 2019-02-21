#pragma once


// CTraceDialog �Ի���
#include "TraceDebug.h"
#include "GameEngineHead.h"

class CTraceRichEdit : public CRichEditCtrl,public ITraceService
{
	DECLARE_DYNAMIC(CTraceRichEdit)

public:
	CTraceRichEdit();
	virtual ~CTraceRichEdit();

public:
	//���÷���
	void InitService();
	//�ִ����
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//�ִ����
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);

	//��������
private:
	//��ȡ��ɫ
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
	//�����ִ�
	bool InsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);

protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

class CTraceDialog : public CDialog
{
	DECLARE_DYNAMIC(CTraceDialog)

protected:
	CTraceRichEdit					m_TraceEdit;

public:
	CTraceDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTraceDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


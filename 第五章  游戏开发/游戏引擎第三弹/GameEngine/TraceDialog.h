#ifndef TRACE_HEAD_FILE
#define TRACE_HEAD_FILE

#pragma once

class GAME_ENGINE_CLASS IRichEditState
{
protected:
	HINSTANCE				m_hInstRichEdit;

public:
	IRichEditState();
	~IRichEditState();

	static IRichEditState*GetInstance();
};

//�����Ҫʹ��RichEdit�ؼ������ȵ���InitRichEdit��ſ��Դ����ɹ�
#define InitRichEdit	IRichEditState::GetInstance()

//////////////////////////////////////////////////////////////////////////

// CTraceDialog �Ի���
#include <Richedit.h>

class CTraceRichEdit : public ITraceService, public cCWnd
{
public:
	CTraceRichEdit();
	virtual ~CTraceRichEdit();

	//��������
public:
	//��������
	BOOL Create( HINSTANCE hInstance,DWORD dwStyle, const RECT& rect, HWND hParentWnd, UINT nID);

	//���ܺ���
public:
	//���÷���
	void InitService();
	//�ִ����
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//�ִ����
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);

	//�ؼ�����
public:
	//����ѡ��
	void SetSel(long nStartChar, long nEndChar);
	//���ø�ʽ
	BOOL SetWordCharFormat(CHARFORMAT2 &cf);
	//�����ı�
	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE);
	//���ñ�����ɫ
	COLORREF SetBackgroundColor(BOOL bSysColor, COLORREF cr);

	//��������
private:
	//��ȡ��ɫ
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
};

//////////////////////////////////////////////////////////////////////////
//���Դ���
class CTraceDialog : public cCWnd
{
protected:
	CTraceRichEdit					m_TraceEdit;				//RichEdit�ؼ�

public:
	CTraceDialog();
	virtual ~CTraceDialog();
	
	//�����¼�
public:
	//��������
	BOOL Create(HINSTANCE hInstance, HWND hParentWnd);
	//���ڻص�
	virtual LRESULT WindowProc( HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam );
};

#endif
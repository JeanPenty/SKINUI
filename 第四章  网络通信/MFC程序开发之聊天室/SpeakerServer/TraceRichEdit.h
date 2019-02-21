#pragma once


//����ȼ�
enum enTraceLevel
{
	TraceLevel_Info					=0,									//��Ϣ��Ϣ
	TraceLevel_Normal				=1,									//��ͨ��Ϣ
	TraceLevel_Warning				=2,									//������Ϣ
	TraceLevel_Exception			=3,									//�쳣��Ϣ
	TraceLevel_Debug				=4,									//������Ϣ
};

// CTraceRichEdit
//////////////////////////////////////////////////////////////////////////

class CTraceRichEdit : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CTraceRichEdit)

public:
	CTraceRichEdit();
	virtual ~CTraceRichEdit();

	//�ִ����
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//�ִ����
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);

	//��������
private:
	//���÷���
	VOID InitializeService();
	//��ȡ��ɫ
	COLORREF GetTraceColor(enTraceLevel TraceLevel);
	//�����ִ�
	bool InsertString(LPCTSTR pszString, CHARFORMAT2 & CharFormat);

protected:
	DECLARE_MESSAGE_MAP()
};



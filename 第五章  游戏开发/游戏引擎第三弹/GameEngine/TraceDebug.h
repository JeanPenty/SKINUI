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

//�¼����
interface ITraceService
{
	//�ִ����
	virtual bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel)=NULL;
	//�ִ����
	virtual bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...)=NULL;
};


// CTraceRichEdit
//////////////////////////////////////////////////////////////////////////
//׷�ٷ���
class GAME_ENGINE_CLASS CTraceService
{
protected:
	ITraceService						* m_pTraceService;
	TCHAR								m_szLogFile[MAX_PATH];

public:
	CTraceService();

	static CTraceService*GetInstance();

public:
	//���ýӿ�
	void SetInterFace(ITraceService *pTraceService);
	//�����ļ�
	void SetLogFile(LPCTSTR lpszFileName);
	//�ִ����
	bool TraceString(LPCTSTR pszString, enTraceLevel TraceLevel);
	//�ִ����
	bool TraceString(enTraceLevel TraceLevel,LPCTSTR pszString, ...);
};

#define TraceService	CTraceService::GetInstance()
//////////////////////////////////////////////////////////////////////////



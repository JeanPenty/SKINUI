#include "StdAfx.h"
#include <Process.h>
#include "ServiceThread.h"

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//��������
struct tagThreadParameter
{
	bool							bSuccess;							//�Ƿ����
	HANDLE							hEventFinish;						//�¼����
	CServiceThread	*				pServiceThread;						//�߳�ָ��
};

//////////////////////////////////////////////////////////////////////////

//���캯��
CThreadLock::CThreadLock(CCriticalSection & CriticalSection, bool bLockAtOnce) 
	: m_CriticalSection(CriticalSection)
{
	//���ñ���
	m_nLockCount=0;

	//��������
	if (bLockAtOnce==true)
	{
		Lock();
	}

	return;
}

//��������
CThreadLock::~CThreadLock()
{
	//�������
	while (m_nLockCount>0)
	{
		UnLock();
	}

	return;
}

//��������
VOID CThreadLock::Lock()
{
	//��������
	m_nLockCount++;
	m_CriticalSection.Lock();

	return;
}

//��������
VOID CThreadLock::UnLock()
{
	//Ч��״̬
	ASSERT(m_nLockCount>0);
	if (m_nLockCount==0) return;

	//�������
	m_nLockCount--;
	m_CriticalSection.Unlock();

	return;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CServiceThread::CServiceThread()
{
	//���ñ���
	m_bRun=false;
	m_uThreadID=0;
	m_hThreadHandle=NULL;

	return;
}

//��������
CServiceThread::~CServiceThread()
{
	//ֹͣ�߳�
	ConcludeThread(INFINITE);

	return;
}

//״̬�ж�
bool CServiceThread::IsRuning()
{
	//���м��
	if (m_hThreadHandle==NULL) return false;
	if (WaitForSingleObject(m_hThreadHandle,0)!=WAIT_TIMEOUT) return false;

	return true;
}

//�����߳�
bool CServiceThread::StartThread()
{
	//Ч��״̬
	ASSERT(IsRuning()==false);
	if (IsRuning()==true) return false;

	//�������
	if (m_hThreadHandle!=NULL) 
	{
		//�رվ��
		CloseHandle(m_hThreadHandle);

		//���ñ���
		m_uThreadID=0;
		m_hThreadHandle=NULL;
	}

	//��������
	tagThreadParameter ThreadParameter;
	ZeroMemory(&ThreadParameter,sizeof(ThreadParameter));

	//���ñ���
	ThreadParameter.bSuccess=false;
	ThreadParameter.pServiceThread=this;
	ThreadParameter.hEventFinish=CreateEvent(NULL,FALSE,FALSE,NULL);

	//Ч��״̬
	ASSERT(ThreadParameter.hEventFinish!=NULL);
	if (ThreadParameter.hEventFinish==NULL) return false;

	//�����߳�
	m_bRun=true;
	m_hThreadHandle=(HANDLE)::_beginthreadex(NULL,0,ThreadFunction,&ThreadParameter,0,&m_uThreadID);

	//�����ж�
	if (m_hThreadHandle==INVALID_HANDLE_VALUE)
	{
		CloseHandle(ThreadParameter.hEventFinish);
		return false;
	}

	//�ȴ��¼�
	WaitForSingleObject(ThreadParameter.hEventFinish,INFINITE);
	CloseHandle(ThreadParameter.hEventFinish);

	//�жϴ���
	if (ThreadParameter.bSuccess==false)
	{
		ConcludeThread(INFINITE);
		return false;
	}

	return true;
}

//ֹͣ�߳�
bool CServiceThread::ConcludeThread(DWORD dwMillSeconds)
{
	//ֹͣ�߳�
	if (IsRuning()==true)
	{
		//���ñ���
		m_bRun=false;

		//ֹͣ�ȴ�
		if (WaitForSingleObject(m_hThreadHandle,dwMillSeconds)==WAIT_TIMEOUT)
		{
			return false;
		}
	}

	//���ñ���
	if (m_hThreadHandle!=NULL)
	{
		//�رվ��
		CloseHandle(m_hThreadHandle);

		//���ñ���
		m_uThreadID=0;
		m_hThreadHandle=NULL;
	}

	return true;
}

//Ͷ����Ϣ
LRESULT CServiceThread::PostThreadMessage(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	//״̬Ч��
	ASSERT((m_uThreadID!=0)&&(m_hThreadHandle!=NULL));
	if ((m_uThreadID==0)||(m_hThreadHandle==NULL)) return false;

	//Ͷ����Ϣ
	if (::PostThreadMessage(m_uThreadID,uMessage,wParam,lParam)==FALSE)
	{
		DWORD dwLastError=GetLastError();
		return dwLastError;
	}

	return 0L;
}

//�̺߳���
unsigned __stdcall CServiceThread::ThreadFunction(LPVOID pThreadData)
{
	//Ч�����
	ASSERT(pThreadData!=NULL);

	//��������
	tagThreadParameter * pThreadParameter=(tagThreadParameter *)pThreadData;
	CServiceThread * pServiceThread=pThreadParameter->pServiceThread;

	//��������
	srand((DWORD)time(NULL));

	//����֪ͨ
	try
	{
		pThreadParameter->bSuccess=pServiceThread->OnEventThreadStrat(); 
	} 
	catch (...)
	{
		//���ñ���
		ASSERT(FALSE);
		pThreadParameter->bSuccess=false;
	}

	//�����¼�
	bool bSuccess=pThreadParameter->bSuccess;
	ASSERT(pThreadParameter->hEventFinish!=NULL);
	if (pThreadParameter->hEventFinish!=NULL) SetEvent(pThreadParameter->hEventFinish);

	//�̴߳���
	if (bSuccess==true)
	{
		//�߳�����
		while (pServiceThread->m_bRun)
		{
#ifndef _DEBUG
			//���а汾
			try
			{
				if (pServiceThread->OnEventThreadRun()==false)
				{
					break;
				}
			}
			catch (...)	{ }
#else
			//���԰汾
			if (pServiceThread->OnEventThreadRun()==false)
			{
				break;
			}
#endif
		}

		//ֹ֪ͣͨ
		try
		{ 
			pServiceThread->OnEventThreadConclude();
		} 
		catch (...)	{ ASSERT(FALSE); }
	}

	//��ֹ�߳�
	_endthreadex(0L);

	return 0L;
}

//////////////////////////////////////////////////////////////////////////

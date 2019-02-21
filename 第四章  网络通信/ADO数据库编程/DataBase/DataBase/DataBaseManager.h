#ifndef DATABASE_HEAD_FILE
#define DATABASE_HEAD_FILE

#include <ICrsint.h>
//////////////////////////////////////////////////////////////////////////
//ADO ����

#import "MSADO15.DLL" rename_namespace("ADOCG") rename("EOF","EndOfFile")
using namespace ADOCG;

typedef _com_error						CComError;						//COM ����
typedef _variant_t						CDBVarValue;					//���ݿ���ֵ

//SQL �쳣����
enum enSQLException
{
	SQLException_None				=0,									//û���쳣
	SQLException_Connect			=1,									//���Ӵ���
	SQLException_Syntax				=2,									//�﷨����
};

//////////////////////////////////////////////////////////////////////////

//ADO ������
class CADOError
{
	//��������
protected:
	enSQLException					m_enErrorType;						//�������
	CString							m_strErrorDescribe;					//������Ϣ

	//��������
public:
	//���캯��
	CADOError();
	//��������
	virtual ~CADOError();

	//���ܽӿ�
public:
	//��������
	virtual enSQLException  GetExceptionType()
	{
		return m_enErrorType;
	}

	//��������
	virtual LPCTSTR  GetExceptionDescribe()
	{
		return m_strErrorDescribe;
	}

	//�쳣����
	virtual HRESULT  GetExceptionResult()
	{
		return (HRESULT)0;    
	}

	//���ܺ���
public:
	//���ô���
	void SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe);
};

//////////////////////////////////////////////////////////////////////////

//���ݿ����
class CDataBase
{
	//��Ϣ����
protected:
	CADOError						m_ADOError;							//�������
	CString							m_strConnect;						//�����ַ���
	CString							m_strErrorDescribe;					//������Ϣ

	//״̬����
protected:
	DWORD							m_dwConnectCount;					//���Դ���
	DWORD							m_dwConnectErrorTime;				//����ʱ��
	const DWORD						m_dwResumeConnectCount;				//�ָ�����
	const DWORD						m_dwResumeConnectTime;				//�ָ�ʱ��

	//�ں˱���
protected:
	_CommandPtr						m_DBCommand;						//�������
	_RecordsetPtr					m_DBRecordset;						//��¼������
	_ConnectionPtr					m_DBConnection;						//���ݿ����

	//��������
public:
	//���캯��
	CDataBase();
	//��������
	virtual ~CDataBase();

	//����ӿ�
public:
	//������
	virtual VOID OpenConnection();
	//�رռ�¼
	virtual VOID CloseRecordset();
	//�ر�����
	virtual VOID CloseConnection();
	//��������
	virtual bool TryConnectAgain(bool bFocusConnect, CComError * pComError);
	//������Ϣ
	virtual bool SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword);
	//������Ϣ
	virtual bool SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword);
	//�л���¼
	virtual VOID NextRecordset();

	//״̬�ӿ�
public:
	//�Ƿ����Ӵ���
	virtual bool IsConnectError();
	//�Ƿ��
	virtual bool IsRecordsetOpened();

	//��¼���ӿ�
public:
	//�����ƶ�
	virtual void MoveToNext();
	//�Ƶ���ͷ
	virtual void MoveToFirst();
	//�Ƿ����
	virtual bool IsRecordsetEnd();
	//��ȡ��Ŀ
	virtual long GetRecordCount();
	//��ȡ��С
	virtual long GetActualSize(LPCTSTR pszParamName);
	//�󶨶���
	virtual VOID BindToRecordset(CADORecordBinding * pBind);
	//��ȡ����
	virtual VOID GetRecordsetValue(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//�ֶνӿ�
public:
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, BYTE & bValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, WORD & wValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, INT & nValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, LONG & lValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, DWORD & ulValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, UINT & ulValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, DOUBLE & dbValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, __int64 & llValue);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, TCHAR szBuffer[], UINT uSize);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, COleDateTime & Time);
	//��ȡ����
	virtual bool GetFieldValue(LPCTSTR lpFieldName, bool & bValue);

	//�������ӿ�
public:
	//�������
	virtual void AddParameter(LPCTSTR pszName, DataTypeEnum Type, ParameterDirectionEnum Direction, LONG lSize, CDBVarValue & DBVarValue);
	//ɾ������
	virtual void ClearParameters();
	//��ò���
	virtual void GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue);
	//��ȡ������ֵ
	virtual long GetReturnValue();

	//ִ�нӿ�
public:
	//ִ�����
	virtual VOID ExecuteProcess(LPCTSTR pszSPName, bool bRecordset);
	//ִ������
	virtual VOID ExecuteSentence(LPCTSTR pszCommand, bool bRecordset);

	//�ڲ�����
private:
	//��ȡ����
	LPCTSTR GetComErrorDescribe(CComError & ComError);
	//���ô���
	void SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe);
};

//////////////////////////////////////////////////////////////////////////

//���ݿ�����
class CDataBaseHelper
{
	//��������
protected:
	CDataBase *						m_pIDataBase;						//���ݶ���

	//��������
public:
	//���캯��
	CDataBaseHelper();
	//��������
	virtual ~CDataBaseHelper();

	//������
public:
	//���ö���
	bool SetDataBase(CDataBase * pIDataBase);

	//��ȡ����
public:
	//��ȡ����
	INT GetValue_INT(LPCTSTR pszItem);
	//��ȡ����
	UINT GetValue_UINT(LPCTSTR pszItem);
	//��ȡ����
	LONG GetValue_LONG(LPCTSTR pszItem);
	//��ȡ����
	BYTE GetValue_BYTE(LPCTSTR pszItem);
	//��ȡ����
	WORD GetValue_WORD(LPCTSTR pszItem);
	//��ȡ����
	DWORD GetValue_DWORD(LPCTSTR pszItem);
	//��ȡ����
	FLOAT GetValue_FLOAT(LPCTSTR pszItem);
	//��ȡ����
	DOUBLE GetValue_DOUBLE(LPCTSTR pszItem);
	//��ȡ����
	LONGLONG GetValue_LONGLONG(LPCTSTR pszItem);
	//��ȡ����
	VOID GetValue_VarValue(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//��ȡ����
	VOID GetValue_SystemTime(LPCTSTR pszItem, SYSTEMTIME & SystemTime);
	//��ȡ�ַ�
	VOID GetValue_String(LPCTSTR pszItem, LPSTR pszString, UINT uMaxCount);
	//��ȡ�ַ�
	VOID GetValue_String(LPCTSTR pszItem, LPWSTR pszString, UINT uMaxCount);

	//��������
public:
	//���ò���
	VOID ResetParameter();
	//��ȡ����
	VOID GetParameter(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//��ȡ����
	VOID GetParameter(LPCTSTR pszItem, LPSTR pszString, UINT uSize);
	//��ȡ����
	VOID GetParameter(LPCTSTR pszItem, LPWSTR pszString, UINT uSize);

	//�������
public:
	//�������
	VOID AddParameter(LPCTSTR pszItem, INT nValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, UINT uValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LONG lValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LONGLONG lValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, BYTE cbValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, WORD wValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, DWORD dwValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, FLOAT fValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, DOUBLE dValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LPCSTR pszString, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, LPCWSTR pszString, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameter(LPCTSTR pszItem, SYSTEMTIME & SystemTime, ParameterDirectionEnum ParameterDirection=adParamInput);
	//�������
	VOID AddParameterOutput(LPCTSTR pszItem, LPSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection=adParamInputOutput);
	//�������
	VOID AddParameterOutput(LPCTSTR pszItem, LPWSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection=adParamInputOutput);

	//ִ�и���
public:
	//������ֵ
	LONG GetReturnValue();
	//�洢����
	LONG ExecuteProcess(LPCTSTR pszSPName, bool bRecordset);
	//ִ������
	LONG ExecuteSentence(LPCTSTR pszSPName, bool bRecordset);
};


#endif
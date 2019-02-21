#include "StdAfx.h"
#include "DataBaseManager.h"
#include <math.h>

//�궨��
_COM_SMARTPTR_TYPEDEF(IADORecordBinding, __uuidof(IADORecordBinding));
//Ч������
#define EfficacyResult(hResult) { if (FAILED(hResult)) _com_issue_error(hResult); }

//////////////////////////////////////////////////////////////////////////
//���캯��
CADOError::CADOError()
{
	m_enErrorType = SQLException_None;
}

//��������
CADOError::~CADOError()
{
}

//���ô���
void CADOError::SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe)
{
	//���ô���
	m_enErrorType = enErrorType;
	m_strErrorDescribe = pszDescribe;

	//�׳�����
	throw this;
}

//////////////////////////////////////////////////////////////////////////
//���캯��
CDataBase::CDataBase() : m_dwResumeConnectCount(30L), m_dwResumeConnectTime(30L)
{
	//״̬����
	m_dwConnectCount = 0;
	m_dwConnectErrorTime = 0L;

	//��������
	m_DBCommand.CreateInstance(__uuidof(Command));
	m_DBRecordset.CreateInstance(__uuidof(Recordset));
	m_DBConnection.CreateInstance(__uuidof(Connection));

	//Ч������
	ASSERT(m_DBCommand != NULL);
	ASSERT(m_DBRecordset != NULL);
	ASSERT(m_DBConnection != NULL);
	if (m_DBCommand == NULL) throw TEXT("���ݿ�������󴴽�ʧ��");
	if (m_DBRecordset == NULL) throw TEXT("���ݿ��¼�����󴴽�ʧ��");
	if (m_DBConnection == NULL) throw TEXT("���ݿ����Ӷ��󴴽�ʧ��");

	//���ñ���
	m_DBCommand->CommandType = adCmdStoredProc;

	return;
}

//��������
CDataBase::~CDataBase()
{
	//�ر�����
	CloseConnection();

	//�ͷŶ���
	m_DBCommand.Release();
	m_DBRecordset.Release();
	m_DBConnection.Release();

	return;
}

//������
VOID  CDataBase::OpenConnection()
{
	//�������ݿ�
	try
	{
		//�ر�����
		CloseConnection();

		//�������ݿ�
		EfficacyResult(m_DBConnection->Open(_bstr_t(m_strConnect), L"", L"", adConnectUnspecified));
		m_DBConnection->CursorLocation = adUseClient;
		m_DBCommand->ActiveConnection = m_DBConnection;

		//���ñ���
		m_dwConnectCount = 0L;
		m_dwConnectErrorTime = 0L;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//�رռ�¼
VOID  CDataBase::CloseRecordset()
{
	try
	{
		if (IsRecordsetOpened()) EfficacyResult(m_DBRecordset->Close());
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//�ر�����
VOID  CDataBase::CloseConnection()
{
	try
	{
		CloseRecordset();
		if ((m_DBConnection != NULL) && (m_DBConnection->GetState() != adStateClosed))
		{
			EfficacyResult(m_DBConnection->Close());
		}
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//��������
bool  CDataBase::TryConnectAgain(bool bFocusConnect, CComError * pComError)
{
	try
	{
		//�ж�����
		bool bReConnect = bFocusConnect;
		if (bReConnect == false)
		{
			DWORD dwNowTime = (DWORD)time(NULL);
			if ((m_dwConnectErrorTime + m_dwResumeConnectTime) > dwNowTime) bReConnect = true;
		}
		if ((bReConnect == false) && (m_dwConnectCount > m_dwResumeConnectCount)) bReConnect = true;

		//���ñ���
		m_dwConnectCount++;
		m_dwConnectErrorTime = (DWORD)time(NULL);
		if (bReConnect == false)
		{
			if (pComError != NULL) SetErrorInfo(SQLException_Connect, GetComErrorDescribe(*pComError));
			return false;
		}

		//��������
		OpenConnection();
		return true;
	}
	catch (CADOError * pIDataBaseException)
	{
		//�������Ӵ���
		if (pComError != NULL) SetErrorInfo(SQLException_Connect, GetComErrorDescribe(*pComError));
		else throw pIDataBaseException;
	}

	return false;
}

//������Ϣ
bool  CDataBase::SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword)
{
	//Ч�����
	ASSERT(dwDBAddr != 0);
	ASSERT(szDBName != NULL);
	ASSERT(szUser != NULL);
	ASSERT(szPassword != NULL);

	BYTE a = (BYTE)((dwDBAddr >> 24) & 0xFF);
	BYTE b = (BYTE)((dwDBAddr >> 16) & 0xFF);
	BYTE c = (BYTE)((dwDBAddr >> 8) & 0xFF);
	BYTE d = (BYTE)(dwDBAddr & 0xFF);
	
	try
	{
		//���������ַ���
		m_strConnect.Format(TEXT("Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%d.%d.%d.%d;Data Source=%s,%ld;"),
			szPassword, szUser, szDBName, a, b, c, d, wPort);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return true;
}

//�л���¼
VOID  CDataBase::NextRecordset()
{
	try
	{
		VARIANT lngRec;
		m_DBRecordset->NextRecordset(&lngRec);
		return;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//������Ϣ
bool  CDataBase::SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword)
{
	//Ч�����
	ASSERT(szDBAddr != NULL);
	ASSERT(szDBName != NULL);
	ASSERT(szUser != NULL);
	ASSERT(szPassword != NULL);
	
	try
	{
		//���������ַ���
		m_strConnect.Format(TEXT("Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Data Source=%s,%ld;"),
			szPassword, szUser, szDBName, szDBAddr, wPort);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return true;
}

//�Ƿ����Ӵ���
bool  CDataBase::IsConnectError()
{
	try
	{
		//״̬�ж�
		if (m_DBConnection == NULL) return true;
		if (m_DBConnection->GetState() == adStateClosed) return true;

		//�����ж�
		long lErrorCount = m_DBConnection->Errors->Count;
		if (lErrorCount > 0L)
		{
			ErrorPtr pError = NULL;
			for (long i = 0; i < lErrorCount; i++)
			{
				pError = m_DBConnection->Errors->GetItem(i);
				if (pError->Number == 0x80004005) return true;
			}
		}

		return false;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//�Ƿ��
bool  CDataBase::IsRecordsetOpened()
{
	if (m_DBRecordset == NULL) return false;
	if (m_DBRecordset->GetState() == adStateClosed) return false;
	return true;
}

//�����ƶ�
void  CDataBase::MoveToNext()
{
	try
	{
		m_DBRecordset->MoveNext();
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return;
}

//�Ƶ���ͷ
void  CDataBase::MoveToFirst()
{
	try
	{
		m_DBRecordset->MoveFirst();
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return;
}

//�Ƿ����
bool  CDataBase::IsRecordsetEnd()
{
	try
	{
		return (m_DBRecordset->EndOfFile == VARIANT_TRUE);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return true;
}

//��ȡ��Ŀ
long  CDataBase::GetRecordCount()
{
	try
	{
		if (m_DBRecordset == NULL) return 0;
		return m_DBRecordset->GetRecordCount();
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return 0;
}

//��ȡ��С
long  CDataBase::GetActualSize(LPCTSTR pszParamName)
{
	ASSERT(pszParamName != NULL);
	try
	{
		return m_DBRecordset->Fields->Item[pszParamName]->ActualSize;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return -1;
}

//�󶨶���
VOID  CDataBase::BindToRecordset(CADORecordBinding * pBind)
{
	ASSERT(pBind != NULL);
	try
	{
		IADORecordBindingPtr pIBind(m_DBRecordset);
		pIBind->BindToRecordset(pBind);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//��ȡ����
VOID  CDataBase::GetRecordsetValue(LPCTSTR pszItem, CDBVarValue & DBVarValue)
{
	ASSERT(pszItem != NULL);
	try
	{
		DBVarValue = m_DBRecordset->Fields->GetItem(pszItem)->Value;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, BYTE & bValue)
{
	try
	{
		bValue = 0;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		switch (vtFld.vt)
		{
		case VT_BOOL:
			{
				bValue = (vtFld.boolVal != 0) ? 2 : 0;
				break;
			}
		case VT_I2:
		case VT_UI1:
			{
				bValue = (vtFld.iVal > 0) ? 2 : 0;
				break;
			}
		case VT_NULL:
		case VT_EMPTY:
			{
				bValue = 0;
				break;
			}
		default:
			bValue = (BYTE)vtFld.iVal;
		}
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, UINT & ulValue)
{
	try
	{
		ulValue = 0L;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		if ((vtFld.vt != VT_NULL) && (vtFld.vt != VT_EMPTY)) ulValue = vtFld.lVal;
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, DOUBLE & dbValue)
{
	try
	{
		dbValue = 0.0L;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		switch (vtFld.vt)
		{
		case VT_R4:
			{
				dbValue = vtFld.fltVal;
				break;
			}
		case VT_R8:
			{
				dbValue = vtFld.dblVal;
				break;
			}
		case VT_DECIMAL:
			{
				dbValue = vtFld.decVal.Lo32;
				dbValue *= (vtFld.decVal.sign == 128) ? -1 : 1;
				dbValue /= pow((double)10, vtFld.decVal.scale);
				break;
			}
		case VT_UI1:
			{
				dbValue = vtFld.iVal;
				break;
			}
		case VT_I2:
		case VT_I4:
			{
				dbValue = vtFld.lVal;
				break;
			}
		case VT_NULL:
		case VT_EMPTY:
			{
				dbValue = 0.0L;
				break;
			}
		default:
			dbValue = vtFld.dblVal;
		}
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, LONG & lValue)
{
	try
	{
		lValue = 0L;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		if ((vtFld.vt != VT_NULL) && (vtFld.vt != VT_EMPTY)) lValue = vtFld.lVal;
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, DWORD & ulValue)
{
	try
	{
		ulValue = 0L;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		if ((vtFld.vt != VT_NULL) && (vtFld.vt != VT_EMPTY)) ulValue = vtFld.ulVal;
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, INT & nValue)
{
	try
	{
		nValue = 0;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		switch (vtFld.vt)
		{
		case VT_BOOL:
			{
				nValue = vtFld.boolVal;
				break;
			}
		case VT_I2:
		case VT_UI1:
			{
				nValue = vtFld.iVal;
				break;
			}
		case VT_NULL:
		case VT_EMPTY:
			{
				nValue = 0;
				break;
			}
		default:
			nValue = vtFld.iVal;
		}
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, __int64 & llValue)
{
	try
	{
		llValue = 0L;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		if ((vtFld.vt != VT_NULL) && (vtFld.vt != VT_EMPTY)) llValue = vtFld.llVal;
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, TCHAR szBuffer[], UINT uSize)
{
	try
	{
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		if (vtFld.vt == VT_BSTR)
		{
			_tcscpy(szBuffer, _bstr_t(vtFld));
			return true;
		}
		return false;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, WORD & wValue)
{
	try
	{
		wValue = 0L;
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		if ((vtFld.vt != VT_NULL) && (vtFld.vt != VT_EMPTY)) wValue = (WORD)vtFld.ulVal;
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, COleDateTime & Time)
{
	try
	{
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		switch (vtFld.vt)
		{
		case VT_DATE:
			{
				COleDateTime TempTime(vtFld);
				Time = TempTime;
				break;
			}
		case VT_EMPTY:
		case VT_NULL:
			{
				Time.SetStatus(COleDateTime::null);
				break;
			}
		default:
			return false;
		}
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ����
bool  CDataBase::GetFieldValue(LPCTSTR lpFieldName, bool & bValue)
{
	try
	{
		_variant_t vtFld = m_DBRecordset->Fields->GetItem(lpFieldName)->Value;
		switch (vtFld.vt)
		{
		case VT_BOOL:
			{
				bValue = (vtFld.boolVal == 0) ? false : true;
				break;
			}
		case VT_EMPTY:
		case VT_NULL:
			{
				bValue = false;
				break;
			}
		default:
			return false;
		}
		return true;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return false;
}

//��ȡ������ֵ
long  CDataBase::GetReturnValue()
{
	try
	{
		_ParameterPtr Parameter;
		long lParameterCount = m_DBCommand->Parameters->Count;
		for (long i = 0; i < lParameterCount; i++)
		{
			Parameter = m_DBCommand->Parameters->Item[i];
			if (Parameter->Direction == adParamReturnValue) return Parameter->Value.lVal;
		}
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return 0;
}

//ɾ������
void  CDataBase::ClearParameters()
{
	try
	{
		long lParameterCount = m_DBCommand->Parameters->Count;
		if (lParameterCount > 0L)
		{
			for (long i = lParameterCount; i > 0; i--)
			{
				m_DBCommand->Parameters->Delete(i - 1);
			}
		}
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return;
}

void delspace(WCHAR s[])
{
	for(; *s; s++)
		;
	while(*--s == ' ')
		;
	*++s = '\0';
}

//��ò���
void  CDataBase::GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue)
{
	//Ч�����
	ASSERT(pszParamName != NULL);

	//��ȡ����
	try
	{
		DBVarValue.Clear();
		DBVarValue = m_DBCommand->Parameters->Item[pszParamName]->Value;

		if ( DBVarValue.vt != VT_NULL )
			delspace(DBVarValue.bstrVal);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return;
}

//�������
void  CDataBase::AddParameter(LPCTSTR pszName, DataTypeEnum Type, ParameterDirectionEnum Direction, LONG lSize, CDBVarValue & DBVarValue)
{
	ASSERT(pszName != NULL);
	try
	{
		_ParameterPtr Parameter = m_DBCommand->CreateParameter(pszName, Type, Direction, lSize, DBVarValue);
		m_DBCommand->Parameters->Append(Parameter);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//ִ�����
VOID  CDataBase::ExecuteProcess(LPCTSTR pszSPName, bool bRecordset)
{
	ASSERT(pszSPName != NULL);
	try
	{
		//�رռ�¼��
		CloseRecordset();

		m_DBCommand->CommandText = pszSPName;

		//ִ������
		if (bRecordset )
		{
			m_DBRecordset->PutRefSource(m_DBCommand);
			m_DBRecordset->CursorLocation = adUseClient;
			EfficacyResult(m_DBRecordset->Open((IDispatch *)m_DBCommand, vtMissing, adOpenForwardOnly, adLockReadOnly, adOptionUnspecified));
		}
		else
		{
			m_DBConnection->CursorLocation = adUseClient;
			EfficacyResult(m_DBCommand->Execute(NULL, NULL, adExecuteNoRecords));
		}
	}
	catch (CComError & ComError)
	{
		if (IsConnectError() == true)	TryConnectAgain(false, &ComError);
		else SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//ִ������
VOID  CDataBase::ExecuteSentence(LPCTSTR pszCommand, bool bRecordset)
{
	ASSERT(pszCommand != NULL);
	try
	{
		//�رռ�¼��
		CloseRecordset();

		//ִ������
		if (bRecordset )
		{
			m_DBRecordset->PutRefSource(m_DBCommand);
			m_DBRecordset->CursorLocation = adUseClient;
			EfficacyResult(m_DBRecordset->Open(pszCommand, m_DBConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText));
		}
		else
		{
			m_DBConnection->CursorLocation = adUseClient;
			EfficacyResult(m_DBCommand->Execute(NULL, NULL, adExecuteNoRecords));
		}
	}
	catch (CComError & ComError)
	{
		if (IsConnectError() == true)	TryConnectAgain(false, &ComError);
		else SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//��ȡ����
LPCTSTR CDataBase::GetComErrorDescribe(CComError & ComError)
{
	_bstr_t bstrDescribe(ComError.Description());
	m_strErrorDescribe.Format(TEXT("ADO ����0x%8x��%s"), ComError.Error(), (LPCTSTR)bstrDescribe);
	
	return m_strErrorDescribe;
}

//���ô���
void CDataBase::SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe)
{
	m_ADOError.SetErrorInfo(enErrorType, pszDescribe);
}

//////////////////////////////////////////////////////////////////////////
//���캯��
CDataBaseHelper::CDataBaseHelper()
{
}
//��������
CDataBaseHelper::~CDataBaseHelper()
{
}

bool CDataBaseHelper::SetDataBase(CDataBase * pIDataBase)
{
	if ( pIDataBase == NULL ) return false;

	m_pIDataBase = pIDataBase;

	return m_pIDataBase?true:false;
}

INT CDataBaseHelper::GetValue_INT(LPCTSTR pszItem)
{
	INT nValue;
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, nValue);
		return nValue;
	}

	return 0;
}

UINT CDataBaseHelper::GetValue_UINT(LPCTSTR pszItem)
{
	UINT ulValue;
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, ulValue);
		return ulValue;

	}

	return 0;
}

DOUBLE CDataBaseHelper::GetValue_DOUBLE(LPCTSTR pszItem)
{
	DOUBLE  dbValue;
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, dbValue);
		return dbValue;

	}

	return 0;
}

BYTE CDataBaseHelper::GetValue_BYTE(LPCTSTR pszItem)
{
	CDBVarValue DBVarValue;
	GetValue_VarValue(pszItem,DBVarValue);
	return DBVarValue.bVal;

	return 0;
}

LONG CDataBaseHelper::GetValue_LONG(LPCTSTR pszItem)
{
	LONG lValue;
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, lValue);
		return lValue;

	}

	return 0;
}

WORD CDataBaseHelper::GetValue_WORD(LPCTSTR pszItem)
{
	WORD  wValue;
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, wValue);
		return wValue;

	}

	return 0;
}

DWORD CDataBaseHelper::GetValue_DWORD(LPCTSTR pszItem)
{
	DWORD  ulValue;
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, ulValue);
		return ulValue;

	}
	return 0;
}

FLOAT CDataBaseHelper::GetValue_FLOAT(LPCTSTR pszItem)
{
	CDBVarValue DBVarValue;
	GetValue_VarValue(pszItem,DBVarValue);
	return DBVarValue.fltVal;
}

LONGLONG CDataBaseHelper::GetValue_LONGLONG(LPCTSTR pszItem)
{
	CDBVarValue DBVarValue;
	GetValue_VarValue(pszItem,DBVarValue);

	if( VT_DECIMAL == DBVarValue.vt )   
	{   
		DECIMAL decVal = DBVarValue.decVal; 

		//�ж���������
		int nSign = 1;

		//���ݷ���λ�жϷ���
		if ( decVal.sign < 128 ) nSign = 1;

		if ( decVal.sign >= 128 )nSign = -1;

		__int64 nReturnVal = decVal.Lo64;   

		return nReturnVal*nSign;
	}

	return 0;//DBVarValue.llVal;
}

VOID CDataBaseHelper::GetValue_VarValue(LPCTSTR pszItem, CDBVarValue & DBVarValue)
{
	m_pIDataBase->GetRecordsetValue(pszItem,DBVarValue);
}

VOID CDataBaseHelper::GetValue_SystemTime(LPCTSTR pszItem, SYSTEMTIME & SystemTime)
{
	_variant_t  vtValue;
	GetValue_VarValue(pszItem,vtValue);
	VariantTimeToSystemTime(vtValue.dblVal,&SystemTime);
}

//��ȡ����
VOID CDataBaseHelper::GetParameter(LPCTSTR pszItem, CDBVarValue & DBVarValue)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetParameter(pszItem, DBVarValue);
	}
}

//��ȡ����
VOID CDataBaseHelper::GetParameter(LPCTSTR pszItem, LPSTR pszString, UINT uSize)
{
	if (m_pIDataBase != NULL)
	{
		CDBVarValue DBVarValue;
		((CDataBase*)m_pIDataBase)->GetParameter(pszItem, DBVarValue);
		strncpy(pszString, _bstr_t(DBVarValue), uSize);
	}
}

//��ȡ����
VOID CDataBaseHelper::GetParameter(LPCTSTR pszItem, LPWSTR pszString, UINT uSize)
{
	if (m_pIDataBase != NULL)
	{
		CDBVarValue DBVarValue;
		((CDataBase*)m_pIDataBase)->GetParameter(pszItem, DBVarValue);
		wcsncpy(pszString, _bstr_t(DBVarValue), uSize);
	}
}

//���ò���
VOID CDataBaseHelper::ResetParameter()
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->ClearParameters();
		((CDataBase*)m_pIDataBase)->AddParameter(TEXT("RETURN_VALUE"), adInteger, adParamReturnValue, sizeof(long), _variant_t((long)0));
	}
}

//��ȡ�ַ�
VOID CDataBaseHelper::GetValue_String(LPCTSTR pszItem, LPSTR pszString, UINT uMaxCount)
{
	if (m_pIDataBase != NULL)
	{
		TCHAR *chTmp = new TCHAR[uMaxCount];
		memset(chTmp, 0, sizeof(TCHAR)*uMaxCount);
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, chTmp, uMaxCount);
		strncpy(pszString, _bstr_t(chTmp), uMaxCount);
		delete []chTmp;
	}
}

//��ȡ�ַ�
VOID CDataBaseHelper::GetValue_String(LPCTSTR pszItem, LPWSTR pszString, UINT uMaxCount)
{
	if (m_pIDataBase != NULL)
	{
		TCHAR *chTmp = new TCHAR[uMaxCount];
		memset(chTmp, 0, sizeof(TCHAR)*uMaxCount);
		((CDataBase*)m_pIDataBase)->GetFieldValue(pszItem, chTmp, uMaxCount);
		wcsncpy(pszString, _bstr_t(chTmp), uMaxCount);
		delete []chTmp;
	}
}

LONG CDataBaseHelper::GetReturnValue()
{
	if (m_pIDataBase != NULL)
	{
		return ((CDataBase*)m_pIDataBase)->GetReturnValue();
	}

	return -1;
}

//�洢����
LONG CDataBaseHelper::ExecuteProcess(LPCTSTR pszSPName, bool bRecordset)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->ExecuteProcess(pszSPName, bRecordset);
		return ((CDataBase*)m_pIDataBase)->GetReturnValue();
	}

	return -1;
}

//ִ������
LONG CDataBaseHelper::ExecuteSentence( LPCTSTR pszSPName, bool bRecordset )
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->ExecuteSentence(pszSPName, bRecordset);
		return ((CDataBase*)m_pIDataBase)->GetReturnValue();
	}

	return -1;
}


//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, INT nValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)nValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, UINT uValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)uValue));
	}

}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, LONG lValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)lValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, LONGLONG lValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)lValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, BYTE cbValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)cbValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, WORD wValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)wValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, DWORD dwValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)dwValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, FLOAT fValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)fValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, DOUBLE dValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)dValue));
	}
}

//�������
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, LPCTSTR pszString, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		if (_tcslen(pszString) != 0)
		{
			CDBVarValue value_(pszString);

#ifdef _UNICODE
			m_pIDataBase->AddParameter(pszItem,adWChar,ParameterDirection,(LONG)wcslen(pszString),value_);
#else
			m_pIDataBase->AddParameter(pszItem,adWChar,ParameterDirection,(LONG)strlen(pszString) + 1,value_);
#endif

		}
		else
		{
			//TCHAR szString[64]=" ";
			((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adChar, adParamInput, lstrlen(pszString) + 1, _variant_t(pszString));
		}
	}
}

#if 0  //
//�������
VOID CDataBaseAide::AddParameter(LPCTSTR pszItem, LPCWSTR pszString, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adParamInput, adVarChar, lstrlen(pszString), _variant_t(pszString));
	}
}
#endif

VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, SYSTEMTIME & SystemTime, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		//double dTime;
		//SystemTimeToVariantTime(&SystemTime,&dTime);
		//CDBVarValue DBVarValue(dTime,VT_DATE);//var_time����ת�����
		//
		//((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adLongVarBinary, ParameterDirection, sizeof SYSTEMTIME, DBVarValue);

		TCHAR szDateTime[24] = {0};
		_sntprintf(szDateTime,sizeof szDateTime, TEXT("%02d-%02d-%02d %02d:%02d:%02d.%03d"), SystemTime.wYear,SystemTime.wMonth,
			SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond,SystemTime.wMilliseconds);

		AddParameter(pszItem,szDateTime,ParameterDirection);

		return;
	}
}

//�������
VOID CDataBaseHelper::AddParameterOutput(LPCTSTR pszItem, LPSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection)
{
	CDBVarValue value_(pszString);
	m_pIDataBase->AddParameter(pszItem,adChar,ParameterDirection,uSize,value_);
}

//�������
VOID CDataBaseHelper::AddParameterOutput(LPCTSTR pszItem, LPWSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection)
{
	CDBVarValue value_(pszString);
	m_pIDataBase->AddParameter(pszItem,adWChar,ParameterDirection,uSize,value_);
}


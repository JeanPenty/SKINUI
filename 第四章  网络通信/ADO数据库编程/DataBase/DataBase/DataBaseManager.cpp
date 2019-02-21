#include "StdAfx.h"
#include "DataBaseManager.h"
#include <math.h>

//宏定义
_COM_SMARTPTR_TYPEDEF(IADORecordBinding, __uuidof(IADORecordBinding));
//效验结果宏
#define EfficacyResult(hResult) { if (FAILED(hResult)) _com_issue_error(hResult); }

//////////////////////////////////////////////////////////////////////////
//构造函数
CADOError::CADOError()
{
	m_enErrorType = SQLException_None;
}

//析构函数
CADOError::~CADOError()
{
}

//设置错误
void CADOError::SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe)
{
	//设置错误
	m_enErrorType = enErrorType;
	m_strErrorDescribe = pszDescribe;

	//抛出错误
	throw this;
}

//////////////////////////////////////////////////////////////////////////
//构造函数
CDataBase::CDataBase() : m_dwResumeConnectCount(30L), m_dwResumeConnectTime(30L)
{
	//状态变量
	m_dwConnectCount = 0;
	m_dwConnectErrorTime = 0L;

	//创建对象
	m_DBCommand.CreateInstance(__uuidof(Command));
	m_DBRecordset.CreateInstance(__uuidof(Recordset));
	m_DBConnection.CreateInstance(__uuidof(Connection));

	//效验数据
	ASSERT(m_DBCommand != NULL);
	ASSERT(m_DBRecordset != NULL);
	ASSERT(m_DBConnection != NULL);
	if (m_DBCommand == NULL) throw TEXT("数据库命令对象创建失败");
	if (m_DBRecordset == NULL) throw TEXT("数据库记录集对象创建失败");
	if (m_DBConnection == NULL) throw TEXT("数据库连接对象创建失败");

	//设置变量
	m_DBCommand->CommandType = adCmdStoredProc;

	return;
}

//析构函数
CDataBase::~CDataBase()
{
	//关闭连接
	CloseConnection();

	//释放对象
	m_DBCommand.Release();
	m_DBRecordset.Release();
	m_DBConnection.Release();

	return;
}

//打开连接
VOID  CDataBase::OpenConnection()
{
	//连接数据库
	try
	{
		//关闭连接
		CloseConnection();

		//连接数据库
		EfficacyResult(m_DBConnection->Open(_bstr_t(m_strConnect), L"", L"", adConnectUnspecified));
		m_DBConnection->CursorLocation = adUseClient;
		m_DBCommand->ActiveConnection = m_DBConnection;

		//设置变量
		m_dwConnectCount = 0L;
		m_dwConnectErrorTime = 0L;
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}
}

//关闭记录
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

//关闭连接
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

//重新连接
bool  CDataBase::TryConnectAgain(bool bFocusConnect, CComError * pComError)
{
	try
	{
		//判断重连
		bool bReConnect = bFocusConnect;
		if (bReConnect == false)
		{
			DWORD dwNowTime = (DWORD)time(NULL);
			if ((m_dwConnectErrorTime + m_dwResumeConnectTime) > dwNowTime) bReConnect = true;
		}
		if ((bReConnect == false) && (m_dwConnectCount > m_dwResumeConnectCount)) bReConnect = true;

		//设置变量
		m_dwConnectCount++;
		m_dwConnectErrorTime = (DWORD)time(NULL);
		if (bReConnect == false)
		{
			if (pComError != NULL) SetErrorInfo(SQLException_Connect, GetComErrorDescribe(*pComError));
			return false;
		}

		//重新连接
		OpenConnection();
		return true;
	}
	catch (CADOError * pIDataBaseException)
	{
		//重新连接错误
		if (pComError != NULL) SetErrorInfo(SQLException_Connect, GetComErrorDescribe(*pComError));
		else throw pIDataBaseException;
	}

	return false;
}

//连接信息
bool  CDataBase::SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword)
{
	//效验参数
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
		//构造连接字符串
		m_strConnect.Format(TEXT("Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%d.%d.%d.%d;Data Source=%s,%ld;"),
			szPassword, szUser, szDBName, a, b, c, d, wPort);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return true;
}

//切换记录
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

//设置信息
bool  CDataBase::SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword)
{
	//效验参数
	ASSERT(szDBAddr != NULL);
	ASSERT(szDBName != NULL);
	ASSERT(szUser != NULL);
	ASSERT(szPassword != NULL);
	
	try
	{
		//构造连接字符串
		m_strConnect.Format(TEXT("Provider=SQLOLEDB.1;Password=%s;Persist Security Info=True;User ID=%s;Initial Catalog=%s;Data Source=%s,%ld;"),
			szPassword, szUser, szDBName, szDBAddr, wPort);
	}
	catch (CComError & ComError)
	{
		SetErrorInfo(SQLException_Syntax, GetComErrorDescribe(ComError));
	}

	return true;
}

//是否连接错误
bool  CDataBase::IsConnectError()
{
	try
	{
		//状态判断
		if (m_DBConnection == NULL) return true;
		if (m_DBConnection->GetState() == adStateClosed) return true;

		//参数判断
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

//是否打开
bool  CDataBase::IsRecordsetOpened()
{
	if (m_DBRecordset == NULL) return false;
	if (m_DBRecordset->GetState() == adStateClosed) return false;
	return true;
}

//往下移动
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

//移到开头
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

//是否结束
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

//获取数目
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

//获取大小
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

//绑定对象
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

//获取数据
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取参数
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

//获取返回数值
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

//删除参数
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

//获得参数
void  CDataBase::GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue)
{
	//效验参数
	ASSERT(pszParamName != NULL);

	//获取参数
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

//插入参数
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

//执行语句
VOID  CDataBase::ExecuteProcess(LPCTSTR pszSPName, bool bRecordset)
{
	ASSERT(pszSPName != NULL);
	try
	{
		//关闭记录集
		CloseRecordset();

		m_DBCommand->CommandText = pszSPName;

		//执行命令
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

//执行命令
VOID  CDataBase::ExecuteSentence(LPCTSTR pszCommand, bool bRecordset)
{
	ASSERT(pszCommand != NULL);
	try
	{
		//关闭记录集
		CloseRecordset();

		//执行命令
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

//获取错误
LPCTSTR CDataBase::GetComErrorDescribe(CComError & ComError)
{
	_bstr_t bstrDescribe(ComError.Description());
	m_strErrorDescribe.Format(TEXT("ADO 错误：0x%8x，%s"), ComError.Error(), (LPCTSTR)bstrDescribe);
	
	return m_strErrorDescribe;
}

//设置错误
void CDataBase::SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe)
{
	m_ADOError.SetErrorInfo(enErrorType, pszDescribe);
}

//////////////////////////////////////////////////////////////////////////
//构造函数
CDataBaseHelper::CDataBaseHelper()
{
}
//析构函数
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

		//判断正数负数
		int nSign = 1;

		//根据符号位判断符号
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

//获取参数
VOID CDataBaseHelper::GetParameter(LPCTSTR pszItem, CDBVarValue & DBVarValue)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->GetParameter(pszItem, DBVarValue);
	}
}

//获取参数
VOID CDataBaseHelper::GetParameter(LPCTSTR pszItem, LPSTR pszString, UINT uSize)
{
	if (m_pIDataBase != NULL)
	{
		CDBVarValue DBVarValue;
		((CDataBase*)m_pIDataBase)->GetParameter(pszItem, DBVarValue);
		strncpy(pszString, _bstr_t(DBVarValue), uSize);
	}
}

//获取参数
VOID CDataBaseHelper::GetParameter(LPCTSTR pszItem, LPWSTR pszString, UINT uSize)
{
	if (m_pIDataBase != NULL)
	{
		CDBVarValue DBVarValue;
		((CDataBase*)m_pIDataBase)->GetParameter(pszItem, DBVarValue);
		wcsncpy(pszString, _bstr_t(DBVarValue), uSize);
	}
}

//重置参数
VOID CDataBaseHelper::ResetParameter()
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->ClearParameters();
		((CDataBase*)m_pIDataBase)->AddParameter(TEXT("RETURN_VALUE"), adInteger, adParamReturnValue, sizeof(long), _variant_t((long)0));
	}
}

//获取字符
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

//获取字符
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

//存储过程
LONG CDataBaseHelper::ExecuteProcess(LPCTSTR pszSPName, bool bRecordset)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->ExecuteProcess(pszSPName, bRecordset);
		return ((CDataBase*)m_pIDataBase)->GetReturnValue();
	}

	return -1;
}

//执行命令
LONG CDataBaseHelper::ExecuteSentence( LPCTSTR pszSPName, bool bRecordset )
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->ExecuteSentence(pszSPName, bRecordset);
		return ((CDataBase*)m_pIDataBase)->GetReturnValue();
	}

	return -1;
}


//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, INT nValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)nValue));
	}
}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, UINT uValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)uValue));
	}

}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, LONG lValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)lValue));
	}
}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, LONGLONG lValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)lValue));
	}
}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, BYTE cbValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)cbValue));
	}
}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, WORD wValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)wValue));
	}
}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, DWORD dwValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)dwValue));
	}
}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, FLOAT fValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)fValue));
	}
}

//插入参数
VOID CDataBaseHelper::AddParameter(LPCTSTR pszItem, DOUBLE dValue, ParameterDirectionEnum ParameterDirection)
{
	if (m_pIDataBase != NULL)
	{
		((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adInteger, adParamInput, sizeof(long), _variant_t((long)dValue));
	}
}

//插入参数
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
//插入参数
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
		//CDBVarValue DBVarValue(dTime,VT_DATE);//var_time就是转换结果
		//
		//((CDataBase*)m_pIDataBase)->AddParameter(pszItem, adLongVarBinary, ParameterDirection, sizeof SYSTEMTIME, DBVarValue);

		TCHAR szDateTime[24] = {0};
		_sntprintf(szDateTime,sizeof szDateTime, TEXT("%02d-%02d-%02d %02d:%02d:%02d.%03d"), SystemTime.wYear,SystemTime.wMonth,
			SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond,SystemTime.wMilliseconds);

		AddParameter(pszItem,szDateTime,ParameterDirection);

		return;
	}
}

//插入参数
VOID CDataBaseHelper::AddParameterOutput(LPCTSTR pszItem, LPSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection)
{
	CDBVarValue value_(pszString);
	m_pIDataBase->AddParameter(pszItem,adChar,ParameterDirection,uSize,value_);
}

//插入参数
VOID CDataBaseHelper::AddParameterOutput(LPCTSTR pszItem, LPWSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection)
{
	CDBVarValue value_(pszString);
	m_pIDataBase->AddParameter(pszItem,adWChar,ParameterDirection,uSize,value_);
}


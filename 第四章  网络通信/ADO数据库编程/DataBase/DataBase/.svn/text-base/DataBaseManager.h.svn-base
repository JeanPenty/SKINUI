#ifndef DATABASE_HEAD_FILE
#define DATABASE_HEAD_FILE

#include <ICrsint.h>
//////////////////////////////////////////////////////////////////////////
//ADO 定义

#import "MSADO15.DLL" rename_namespace("ADOCG") rename("EOF","EndOfFile")
using namespace ADOCG;

typedef _com_error						CComError;						//COM 错误
typedef _variant_t						CDBVarValue;					//数据库数值

//SQL 异常类型
enum enSQLException
{
	SQLException_None				=0,									//没有异常
	SQLException_Connect			=1,									//连接错误
	SQLException_Syntax				=2,									//语法错误
};

//////////////////////////////////////////////////////////////////////////

//ADO 错误类
class CADOError
{
	//变量定义
protected:
	enSQLException					m_enErrorType;						//错误代号
	CString							m_strErrorDescribe;					//错误信息

	//函数定义
public:
	//构造函数
	CADOError();
	//析构函数
	virtual ~CADOError();

	//功能接口
public:
	//错误类型
	virtual enSQLException  GetExceptionType()
	{
		return m_enErrorType;
	}

	//错误描述
	virtual LPCTSTR  GetExceptionDescribe()
	{
		return m_strErrorDescribe;
	}

	//异常代码
	virtual HRESULT  GetExceptionResult()
	{
		return (HRESULT)0;    
	}

	//功能函数
public:
	//设置错误
	void SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe);
};

//////////////////////////////////////////////////////////////////////////

//数据库对象
class CDataBase
{
	//信息变量
protected:
	CADOError						m_ADOError;							//错误对象
	CString							m_strConnect;						//连接字符串
	CString							m_strErrorDescribe;					//错误信息

	//状态变量
protected:
	DWORD							m_dwConnectCount;					//重试次数
	DWORD							m_dwConnectErrorTime;				//错误时间
	const DWORD						m_dwResumeConnectCount;				//恢复次数
	const DWORD						m_dwResumeConnectTime;				//恢复时间

	//内核变量
protected:
	_CommandPtr						m_DBCommand;						//命令对象
	_RecordsetPtr					m_DBRecordset;						//记录集对象
	_ConnectionPtr					m_DBConnection;						//数据库对象

	//函数定义
public:
	//构造函数
	CDataBase();
	//析构函数
	virtual ~CDataBase();

	//管理接口
public:
	//打开连接
	virtual VOID OpenConnection();
	//关闭记录
	virtual VOID CloseRecordset();
	//关闭连接
	virtual VOID CloseConnection();
	//重新连接
	virtual bool TryConnectAgain(bool bFocusConnect, CComError * pComError);
	//连接信息
	virtual bool SetConnectionInfo(DWORD dwDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword);
	//设置信息
	virtual bool SetConnectionInfo(LPCTSTR szDBAddr, WORD wPort, LPCTSTR szDBName, LPCTSTR szUser, LPCTSTR szPassword);
	//切换记录
	virtual VOID NextRecordset();

	//状态接口
public:
	//是否连接错误
	virtual bool IsConnectError();
	//是否打开
	virtual bool IsRecordsetOpened();

	//记录集接口
public:
	//往下移动
	virtual void MoveToNext();
	//移到开头
	virtual void MoveToFirst();
	//是否结束
	virtual bool IsRecordsetEnd();
	//获取数目
	virtual long GetRecordCount();
	//获取大小
	virtual long GetActualSize(LPCTSTR pszParamName);
	//绑定对象
	virtual VOID BindToRecordset(CADORecordBinding * pBind);
	//获取数据
	virtual VOID GetRecordsetValue(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//字段接口
public:
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, BYTE & bValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, WORD & wValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, INT & nValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, LONG & lValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, DWORD & ulValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, UINT & ulValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, DOUBLE & dbValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, __int64 & llValue);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, TCHAR szBuffer[], UINT uSize);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, COleDateTime & Time);
	//获取参数
	virtual bool GetFieldValue(LPCTSTR lpFieldName, bool & bValue);

	//命令对象接口
public:
	//插入参数
	virtual void AddParameter(LPCTSTR pszName, DataTypeEnum Type, ParameterDirectionEnum Direction, LONG lSize, CDBVarValue & DBVarValue);
	//删除参数
	virtual void ClearParameters();
	//获得参数
	virtual void GetParameter(LPCTSTR pszParamName, CDBVarValue & DBVarValue);
	//获取返回数值
	virtual long GetReturnValue();

	//执行接口
public:
	//执行语句
	virtual VOID ExecuteProcess(LPCTSTR pszSPName, bool bRecordset);
	//执行命令
	virtual VOID ExecuteSentence(LPCTSTR pszCommand, bool bRecordset);

	//内部函数
private:
	//获取错误
	LPCTSTR GetComErrorDescribe(CComError & ComError);
	//设置错误
	void SetErrorInfo(enSQLException enErrorType, LPCTSTR pszDescribe);
};

//////////////////////////////////////////////////////////////////////////

//数据库助手
class CDataBaseHelper
{
	//变量定义
protected:
	CDataBase *						m_pIDataBase;						//数据对象

	//函数定义
public:
	//构造函数
	CDataBaseHelper();
	//析构函数
	virtual ~CDataBaseHelper();

	//管理函数
public:
	//设置对象
	bool SetDataBase(CDataBase * pIDataBase);

	//获取数据
public:
	//获取数据
	INT GetValue_INT(LPCTSTR pszItem);
	//获取数据
	UINT GetValue_UINT(LPCTSTR pszItem);
	//获取数据
	LONG GetValue_LONG(LPCTSTR pszItem);
	//获取数据
	BYTE GetValue_BYTE(LPCTSTR pszItem);
	//获取数据
	WORD GetValue_WORD(LPCTSTR pszItem);
	//获取数据
	DWORD GetValue_DWORD(LPCTSTR pszItem);
	//获取数据
	FLOAT GetValue_FLOAT(LPCTSTR pszItem);
	//获取数据
	DOUBLE GetValue_DOUBLE(LPCTSTR pszItem);
	//获取数据
	LONGLONG GetValue_LONGLONG(LPCTSTR pszItem);
	//获取数据
	VOID GetValue_VarValue(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//获取数据
	VOID GetValue_SystemTime(LPCTSTR pszItem, SYSTEMTIME & SystemTime);
	//获取字符
	VOID GetValue_String(LPCTSTR pszItem, LPSTR pszString, UINT uMaxCount);
	//获取字符
	VOID GetValue_String(LPCTSTR pszItem, LPWSTR pszString, UINT uMaxCount);

	//参数函数
public:
	//重置参数
	VOID ResetParameter();
	//获取参数
	VOID GetParameter(LPCTSTR pszItem, CDBVarValue & DBVarValue);
	//获取参数
	VOID GetParameter(LPCTSTR pszItem, LPSTR pszString, UINT uSize);
	//获取参数
	VOID GetParameter(LPCTSTR pszItem, LPWSTR pszString, UINT uSize);

	//插入参数
public:
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, INT nValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, UINT uValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, LONG lValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, LONGLONG lValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, BYTE cbValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, WORD wValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, DWORD dwValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, FLOAT fValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, DOUBLE dValue, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, LPCSTR pszString, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, LPCWSTR pszString, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameter(LPCTSTR pszItem, SYSTEMTIME & SystemTime, ParameterDirectionEnum ParameterDirection=adParamInput);
	//插入参数
	VOID AddParameterOutput(LPCTSTR pszItem, LPSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection=adParamInputOutput);
	//插入参数
	VOID AddParameterOutput(LPCTSTR pszItem, LPWSTR pszString, UINT uSize, ParameterDirectionEnum ParameterDirection=adParamInputOutput);

	//执行辅助
public:
	//返回数值
	LONG GetReturnValue();
	//存储过程
	LONG ExecuteProcess(LPCTSTR pszSPName, bool bRecordset);
	//执行命令
	LONG ExecuteSentence(LPCTSTR pszSPName, bool bRecordset);
};


#endif